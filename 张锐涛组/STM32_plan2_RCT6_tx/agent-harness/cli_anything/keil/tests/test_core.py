"""Unit tests for cli-anything-keil core modules."""
import os
import sys
import json
import tempfile

import pytest

# Ensure package is importable
_here = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
if _here not in sys.path:
    sys.path.insert(0, _here)

from cli_anything.keil.utils.log_parser import (
    BuildResult,
    parse_build_log,
    parse_errors_from_log,
)
from cli_anything.keil.core.project import parse_project, KeilProject
from cli_anything.keil.core.session import SessionManager, SessionState


# ---------------------------------------------------------------------------
# Log Parser tests
# ---------------------------------------------------------------------------

class TestBuildResult:
    def test_defaults(self):
        br = BuildResult(success=True)
        assert br.errors == 0
        assert br.warnings == 0
        assert br.elapsed == 0.0

    def test_to_dict(self):
        br = BuildResult(success=True, errors=0, warnings=2,
                         project="/tmp/test.uvprojx", target="Release")
        d = br.to_dict()
        assert d["success"] is True
        assert d["errors"] == 0
        assert d["warnings"] == 2
        assert d["project"] == "/tmp/test.uvprojx"


class TestParseBuildLog:
    def test_canonical_summary_line(self):
        log = """
compiling main.c...
linking...
Program Size: Code=1234 RO-data=56 RW-data=12 ZI-data=256
".\\obj\\test.axf" - 0 Error(s), 2 Warning(s).
"""
        errors, warnings = parse_build_log(log)
        assert errors == 0
        assert warnings == 2

    def test_spacing_variation(self):
        log = "42 Error(s), 7 Warning(s)"
        errors, warnings = parse_build_log(log)
        assert errors == 42
        assert warnings == 7

    def test_fallback_count(self):
        log = "Warning: unused variable\nWarning: implicit declaration"
        errors, warnings = parse_build_log(log)
        assert errors == 0
        assert warnings == 2

    def test_no_matches(self):
        errors, warnings = parse_build_log("")
        assert errors == 0
        assert warnings == 0

    def test_case_insensitive(self):
        log = "0 error(s), 0 warning(s)"
        errors, warnings = parse_build_log(log)
        assert errors == 0
        assert warnings == 0


class TestParseErrorsFromLog:
    def test_extracts_entries(self):
        log = (
            "main.c(42): error: expected ';' after expression\n"
            "utils.c(10): warning: implicit declaration\n"
        )
        entries = parse_errors_from_log(log)
        assert len(entries) == 2
        assert entries[0] == {
            "file": "main.c", "line": 42,
            "severity": "error", "message": "expected ';' after expression",
        }
        assert entries[1]["severity"] == "warning"

    def test_empty_log(self):
        assert parse_errors_from_log("") == []


# ---------------------------------------------------------------------------
# Project Parser tests
# ---------------------------------------------------------------------------

class TestParseProject:
    def test_parse_real_project(self):
        project_path = os.path.join(
            os.path.dirname(_here), "USER", "test.uvprojx"
        )
        if not os.path.isfile(project_path):
            pytest.skip("Real project file not found")
        proj = parse_project(project_path)
        assert proj.name == "test"
        assert "STM32F103RC" in proj.device
        assert "Target 1" in proj.targets
        assert len(proj.source_groups) > 0
        assert len(proj.source_files) > 0
        assert proj.create_hex is True
        assert "STM32F10X_HD" in proj.defines

    def test_to_dict(self, tmp_path):
        proj = KeilProject(
            path=str(tmp_path / "test.uvprojx"),
            name="test",
            device="STM32F103RC",
            targets=["Debug", "Release"],
            source_files=["main.c", "lib.c"],
            source_groups=[
                {"name": "App", "files": ["main.c"]},
                {"name": "Lib", "files": ["lib.c"]},
            ],
        )
        d = proj.to_dict()
        assert d["name"] == "test"
        assert d["targets"] == ["Debug", "Release"]
        assert d["source_file_count"] == 2

    def test_file_not_found(self):
        with pytest.raises(FileNotFoundError):
            parse_project("/nonexistent/project.uvprojx")


# ---------------------------------------------------------------------------
# Session tests
# ---------------------------------------------------------------------------

class TestSessionState:
    def test_roundtrip(self):
        s = SessionState(
            project_path="/tmp/test.uvprojx",
            target_name="Release",
            uv4_path="C:/Keil_v5/UV4/UV4.exe",
        )
        d = s.to_dict()
        s2 = SessionState.from_dict(d)
        assert s2.project_path == s.project_path
        assert s2.target_name == s.target_name
        assert s2.uv4_path == s.uv4_path

    def test_defaults(self):
        s = SessionState()
        assert s.project_path == ""
        assert s.target_name == ""


class TestSessionManager:
    def test_dry_run_does_not_persist(self):
        sm = SessionManager(dry_run=True)
        state = sm.load()
        state.project_path = "/tmp/test.uvprojx"
        result = sm.save(state)
        assert result is False

    def test_save_and_load(self, tmp_path, monkeypatch):
        state_dir = str(tmp_path / ".cli-anything-keil")
        state_file = os.path.join(state_dir, "state.json")
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_DIR", state_dir
        )
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_FILE", state_file
        )

        sm = SessionManager(dry_run=False)
        state = sm.load()
        state.project_path = "/tmp/test.uvprojx"
        state.target_name = "Debug"
        assert sm.save(state) is True
        assert os.path.isfile(state_file)

        sm2 = SessionManager()
        loaded = sm2.load()
        assert loaded.project_path == "/tmp/test.uvprojx"
        assert loaded.target_name == "Debug"

    def test_clear(self, tmp_path, monkeypatch):
        state_dir = str(tmp_path / ".cli-anything-keil")
        state_file = os.path.join(state_dir, "state.json")
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_DIR", state_dir
        )
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_FILE", state_file
        )

        sm = SessionManager()
        sm.load()
        sm.save()
        assert os.path.isfile(state_file)
        assert sm.clear() is True
        assert not os.path.isfile(state_file)
