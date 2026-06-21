"""End-to-end tests for cli-anything-keil CLI.

These tests invoke the CLI via subprocess (where available) or test
the Click CliRunner directly. Tests requiring UV4.exe are skipped
when the toolchain is not installed.
"""
import os
import sys
import json
import subprocess

import pytest
from click.testing import CliRunner

_here = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
if _here not in sys.path:
    sys.path.insert(0, _here)

from cli_anything.keil.keil_cli import cli

PROJECT_FILE = os.path.join(os.path.dirname(_here), "USER", "test.uvprojx")


def _resolve_cli() -> str:
    """Resolve the installed CLI command, or fall back to module invocation."""
    import shutil
    which = shutil.which("cli-anything-keil")
    if which:
        return "cli-anything-keil"
    # Fall back: run via python -m
    return None


# ---------------------------------------------------------------------------
# CliRunner tests (no UV4.exe needed)
# ---------------------------------------------------------------------------

class TestCLIBasic:
    def test_help(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--help"])
        assert result.exit_code == 0
        assert "build" in result.output
        assert "flash" in result.output

    def test_discover(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["discover", "-d", os.path.dirname(_here)])
        assert result.exit_code == 0
        assert "test.uvprojx" in result.output

    def test_discover_json(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--json", "discover", "-d", os.path.dirname(_here)])
        assert result.exit_code == 0
        data = json.loads(result.output)
        assert data["count"] > 0
        assert any("test.uvprojx" in p for p in data["projects"])

    def test_project_info(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["project", "info", "-p", PROJECT_FILE])
        assert result.exit_code == 0
        assert "STM32F103RC" in result.output
        assert "Target 1" in result.output

    def test_project_info_json(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--json", "project", "info", "-p", PROJECT_FILE])
        assert result.exit_code == 0
        data = json.loads(result.output)
        assert data["device"] == "STM32F103RC"
        assert "Target 1" in data["targets"]

    def test_project_targets(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["project", "targets", "-p", PROJECT_FILE])
        assert result.exit_code == 0
        assert "Target 1" in result.output

    def test_project_sources(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["project", "sources", "-p", PROJECT_FILE])
        assert result.exit_code == 0
        assert "test.c" in result.output
        assert "delay.c" in result.output

    def test_where(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["where"])
        assert result.exit_code == 0
        assert "UV4" in result.output

    def test_clean_dry(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["clean", "--dry", "-p", PROJECT_FILE])
        assert result.exit_code == 0
        assert "Would remove" in result.output

    def test_session_flow(self, tmp_path, monkeypatch):
        state_file = str(tmp_path / "state.json")
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_FILE", state_file
        )
        runner = CliRunner()

        r1 = runner.invoke(cli, ["session", "set",
                                 "--project-path", PROJECT_FILE,
                                 "--target-name", "Target 1"])
        assert r1.exit_code == 0

        r2 = runner.invoke(cli, ["session", "show"])
        assert r2.exit_code == 0
        assert "test.uvprojx" in r2.output
        assert "Target 1" in r2.output

        r3 = runner.invoke(cli, ["session", "clear"])
        assert r3.exit_code == 0

    def test_session_dry_run(self, tmp_path, monkeypatch):
        state_file = str(tmp_path / "state.json")
        monkeypatch.setattr(
            "cli_anything.keil.core.session.STATE_FILE", state_file
        )
        runner = CliRunner()

        r1 = runner.invoke(cli, ["--dry-run", "session", "set",
                                 "--project-path", PROJECT_FILE])
        assert r1.exit_code == 0
        assert not os.path.isfile(state_file)


class TestCLIJSONOutput:
    def test_build_help_json_flag_accepted(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--json", "--help"])
        assert result.exit_code == 0

    def test_discover_json_is_valid(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--json", "discover", "-d", os.path.dirname(_here)])
        data = json.loads(result.output)
        assert isinstance(data["projects"], list)
        assert isinstance(data["count"], int)

    def test_project_info_json_is_valid(self):
        runner = CliRunner()
        result = runner.invoke(cli, ["--json", "project", "info", "-p", PROJECT_FILE])
        data = json.loads(result.output)
        assert "name" in data
        assert "device" in data
        assert "targets" in data
        assert "source_file_count" in data


# ---------------------------------------------------------------------------
# Subprocess tests (when CLI is installed in PATH)
# ---------------------------------------------------------------------------

class TestCLISubprocess:
    @pytest.mark.skipif(
        os.environ.get("CLI_ANYTHING_FORCE_INSTALLED") != "1",
        reason="Set CLI_ANYTHING_FORCE_INSTALLED=1 to run subprocess tests."
    )
    def test_help_via_subprocess(self):
        cli_path = _resolve_cli()
        if cli_path is None:
            pytest.skip("cli-anything-keil not in PATH")
        proc = subprocess.run(
            [cli_path, "--help"], capture_output=True, text=True, timeout=10
        )
        assert proc.returncode == 0
        assert "build" in proc.stdout
