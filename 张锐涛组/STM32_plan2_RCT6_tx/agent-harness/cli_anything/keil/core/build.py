import os
import time
import subprocess
import tempfile
from pathlib import Path
from typing import Optional

from cli_anything.keil.utils.log_parser import BuildResult, parse_build_log


class UV4Runner:
    """Wraps UV4.exe subprocess calls with log capture."""

    KNOWN_PATHS = [
        "C:/Keil_v5/UV4/UV4.exe",
        "C:/Keil_v4/UV4/UV4.exe",
        "C:/Keil/UV4/UV4.exe",
    ]

    def __init__(self, uv4_path: Optional[str] = None):
        self._uv4_path = uv4_path

    @property
    def path(self) -> str:
        if self._uv4_path is None:
            self._uv4_path = self._find_uv4()
        return self._uv4_path

    def _find_uv4(self) -> str:
        env = os.environ.get("KEIL_UV4_PATH", "")
        if env and os.path.isfile(env):
            return env

        import shutil
        which = shutil.which("UV4.exe")
        if which:
            return which

        for p in self.KNOWN_PATHS:
            if os.path.isfile(p):
                return p

        for base in ["C:/Keil_v5", "C:/Keil_v4", "C:/Keil"]:
            if not os.path.isdir(base):
                continue
            for root, dirs, files in os.walk(base):
                for f in files:
                    if f.lower() == "uv4.exe":
                        return os.path.join(root, f)

        raise RuntimeError(
            "UV4.exe not found. Install Keil MDK-ARM or set KEIL_UV4_PATH env var."
        )

    def build(self, project_path: str, target: Optional[str] = None,
              output_log: Optional[str] = None, timeout: int = 300) -> BuildResult:
        return self._run(["-b", project_path, "-j0"], target, output_log, timeout)

    def rebuild(self, project_path: str, target: Optional[str] = None,
                output_log: Optional[str] = None, timeout: int = 300) -> BuildResult:
        return self._run(["-r", project_path, "-j0"], target, output_log, timeout)

    def clean_build(self, project_path: str, target: Optional[str] = None,
                    output_log: Optional[str] = None, timeout: int = 300) -> BuildResult:
        return self._run(["-cr", project_path, "-j0"], target, output_log, timeout)

    def flash(self, project_path: str, target: Optional[str] = None,
              output_log: Optional[str] = None, timeout: int = 120) -> BuildResult:
        return self._run(["-f", project_path, "-j0"], target, output_log, timeout)

    def _run(self, base_cmd: list, target: Optional[str],
             output_log: Optional[str], timeout: int) -> BuildResult:
        cmd = [self.path] + base_cmd
        if target:
            cmd.extend(["-t", target])

        project_path = base_cmd[1]
        start = time.time()

        keep_log = bool(output_log)
        log_path = os.path.abspath(output_log) if keep_log else None

        if not log_path:
            fd, log_path = tempfile.mkstemp(suffix=".txt", prefix="keil_build_")
            os.close(fd)

        cmd.extend(["-o", log_path])

        try:
            proc = subprocess.run(
                cmd, capture_output=True, text=True,
                encoding="gbk", errors="replace", timeout=timeout,
            )
        except subprocess.TimeoutExpired:
            log_content = _read_file(log_path)
            if not keep_log:
                _safe_unlink(log_path)
            return BuildResult(
                success=False, returncode=-1, errors=0, warnings=0,
                stderr=f"Command timed out after {timeout}s",
                log=log_content, project=project_path, target=target,
                uv4_path=self.path, elapsed=time.time() - start,
            )

        log_content = _read_file(log_path)
        if not keep_log:
            _safe_unlink(log_path)

        errors, warnings = parse_build_log(log_content)

        return BuildResult(
            success=proc.returncode == 0,
            returncode=proc.returncode,
            errors=errors, warnings=warnings,
            stdout=proc.stdout, stderr=proc.stderr,
            log=log_content, project=project_path, target=target,
            uv4_path=self.path, elapsed=time.time() - start,
        )


def _read_file(path: str) -> str:
    if not os.path.isfile(path):
        return ""
    # Try utf-8 first, then common Windows encodings
    for enc in ("utf-8", "gbk", "utf-16", "cp1252"):
        try:
            with open(path, "r", encoding=enc, errors="replace") as f:
                return f.read()
        except (UnicodeDecodeError, UnicodeError):
            continue
    return ""


def _safe_unlink(path: str):
    try:
        os.unlink(path)
    except Exception:
        pass
