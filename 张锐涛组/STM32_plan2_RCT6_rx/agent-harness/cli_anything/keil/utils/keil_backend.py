"""Backend that finds and invokes Keil μVision UV4.exe.

UV4.exe writes build output to a file (via -o), not to stdout/stderr.
We use a temp file to capture it.
"""

import os
import sys
import subprocess
import shutil
import tempfile
from pathlib import Path
from typing import Optional


_KNOWN_PATHS = [
    "C:/Keil_v5/UV4/UV4.exe",
    "C:/Keil_v4/UV4/UV4.exe",
    "C:/Keil/UV4/UV4.exe",
]

_UV4_PATH = None


def find_uv4() -> str:
    """Locate UV4.exe. Caches result after first call."""
    global _UV4_PATH
    if _UV4_PATH is not None:
        return _UV4_PATH

    env_path = os.environ.get("KEIL_UV4_PATH", "")
    if env_path and os.path.isfile(env_path):
        _UV4_PATH = env_path
        return _UV4_PATH

    which = shutil.which("UV4.exe")
    if which:
        _UV4_PATH = which
        return _UV4_PATH

    for p in _KNOWN_PATHS:
        if os.path.isfile(p):
            _UV4_PATH = p
            return _UV4_PATH

    for base in ["C:/Keil_v5", "C:/Keil_v4", "C:/Keil"]:
        for root, dirs, files in os.walk(base):
            for f in files:
                if f.lower() == "uv4.exe":
                    _UV4_PATH = os.path.join(root, f)
                    return _UV4_PATH

    raise RuntimeError(
        "UV4.exe not found. Install Keil MDK-ARM (v4 or v5) from "
        "https://www.keil.com/download/product/ or set KEIL_UV4_PATH env var."
    )


def _escape_path(path: str) -> str:
    return str(Path(path)).replace("\\", "/")


def _run_with_log(cmd: list, timeout: int) -> dict:
    """Run UV4 command with temp log file, read log contents after."""
    fd, log_path = tempfile.mkstemp(suffix=".txt", prefix="keil_build_")
    os.close(fd)
    log_path = _escape_path(log_path)
    cmd.extend(["-o", log_path])

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        _safe_unlink(log_path)
        return {
            "returncode": -1,
            "stdout": "",
            "stderr": f"Command timed out after {timeout}s",
            "log": "",
        }

    # Read the log file UV4 wrote
    log_content = ""
    try:
        with open(log_path, "r", encoding="utf-8", errors="replace") as f:
            log_content = f.read()
    except Exception:
        pass
    _safe_unlink(log_path)

    combined = result.stdout + result.stderr + log_content
    errors = combined.count("Error:") + combined.count("error:")
    warnings = combined.count("Warning:") + combined.count("warning:")

    return {
        "returncode": result.returncode,
        "stdout": result.stdout,
        "stderr": result.stderr,
        "log": log_content,
        "errors": errors,
        "warnings": warnings,
    }


def _safe_unlink(path: str):
    try:
        os.unlink(path)
    except Exception:
        pass


def build(project_path: str, target: Optional[str] = None,
          output: Optional[str] = None, timeout: int = 300) -> dict:
    """Build (incremental) a Keil project."""
    uv4 = find_uv4()
    project_path = _escape_path(os.path.abspath(project_path))

    if not os.path.isfile(project_path):
        return {
            "success": False, "returncode": -1,
            "stdout": "", "stderr": f"Project file not found: {project_path}",
            "log": "", "errors": 0, "warnings": 0,
            "project": project_path, "target": target, "uv4_path": uv4,
        }

    cmd = [uv4, "-b", project_path, "-j0"]
    if target:
        cmd.extend(["-t", target])

    if output:
        # User specified an output file — keep it after build
        cmd.extend(["-o", _escape_path(os.path.abspath(output))])
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return {
                "success": False, "returncode": -1,
                "stdout": "", "stderr": f"Build timed out after {timeout}s",
                "log": "", "errors": 0, "warnings": 0,
                "project": project_path, "target": target, "uv4_path": uv4,
            }
        log_content = ""
        try:
            with open(output, "r", encoding="utf-8", errors="replace") as f:
                log_content = f.read()
        except Exception:
            pass
    else:
        r = _run_with_log(cmd, timeout)
        result = type('obj', (object,), {'returncode': r['returncode']})()
        result.stdout = r['stdout']
        result.stderr = r['stderr']
        log_content = r['log']

    combined = result.stdout + result.stderr + log_content
    errors = combined.count("Error:") + combined.count("error:")
    warnings = combined.count("Warning:") + combined.count("warning:")

    return {
        "success": result.returncode == 0,
        "returncode": result.returncode,
        "stdout": result.stdout,
        "stderr": result.stderr,
        "log": log_content,
        "errors": errors,
        "warnings": warnings,
        "project": project_path,
        "target": target,
        "uv4_path": uv4,
    }


def rebuild(project_path: str, target: Optional[str] = None,
            timeout: int = 300) -> dict:
    """Rebuild (clean + build) a Keil project."""
    uv4 = find_uv4()
    project_path = _escape_path(os.path.abspath(project_path))

    if not os.path.isfile(project_path):
        return {
            "success": False, "returncode": -1,
            "stdout": "", "stderr": f"Project file not found: {project_path}",
            "log": "", "errors": 0, "warnings": 0,
            "project": project_path, "target": target, "uv4_path": uv4,
        }

    cmd = [uv4, "-r", project_path, "-j0"]
    if target:
        cmd.extend(["-t", target])

    r = _run_with_log(cmd, timeout)

    return {
        "success": r["returncode"] == 0,
        "returncode": r["returncode"],
        "stdout": r["stdout"],
        "stderr": r["stderr"],
        "log": r["log"],
        "errors": r["errors"],
        "warnings": r["warnings"],
        "project": project_path,
        "target": target,
        "uv4_path": uv4,
    }


def flash(project_path: str, target: Optional[str] = None,
          timeout: int = 60) -> dict:
    """Flash (download) to target via debug probe."""
    uv4 = find_uv4()
    project_path = _escape_path(os.path.abspath(project_path))

    if not os.path.isfile(project_path):
        return {
            "success": False, "returncode": -1,
            "stdout": "", "stderr": f"Project file not found: {project_path}",
            "log": "", "errors": 0, "warnings": 0,
            "project": project_path, "target": target, "uv4_path": uv4,
        }

    cmd = [uv4, "-f", project_path, "-j0"]
    if target:
        cmd.extend(["-t", target])

    r = _run_with_log(cmd, timeout)

    return {
        "success": r["returncode"] == 0,
        "returncode": r["returncode"],
        "stdout": r["stdout"],
        "stderr": r["stderr"],
        "log": r["log"],
        "errors": r["errors"],
        "warnings": r["warnings"],
        "project": project_path,
        "target": target,
        "uv4_path": uv4,
    }


def clean(project_path: str) -> dict:
    """Remove build output files for a Keil project."""
    build_dir = os.path.dirname(os.path.abspath(project_path))
    removed = []
    failed = []

    patterns = ["*.o", "*.obj", "*.hex", "*.axf", "*.elf", "*.lst",
                "*.map", "*.plg", "*.bak", "*.dep", "*.crf", "*.d",
                "*.lnp", "*.htm", "*.tra", "*.iex", "*.JLinkLog.txt",
                "*.build_log.htm"]

    import glob as gb
    for pat in patterns:
        for f in gb.glob(os.path.join(build_dir, "**", pat), recursive=True):
            try:
                os.remove(f)
                removed.append(f)
            except OSError as e:
                failed.append(str(e))

    for d_name in ["OBJ", "Listings"]:
        d = os.path.join(build_dir, d_name)
        if os.path.isdir(d):
            for root, dirs, files in os.walk(d, topdown=False):
                for f in files:
                    fp = os.path.join(root, f)
                    try:
                        os.remove(fp)
                        removed.append(fp)
                    except OSError as e:
                        failed.append(str(e))

    return {
        "success": len(failed) == 0,
        "removed_count": len(removed),
        "removed": removed,
        "failed": failed,
        "project": _escape_path(os.path.abspath(project_path)),
    }


def info(project_path: str) -> dict:
    """Extract basic info from a Keil project file (.uvproj/.uvprojx)."""
    import xml.etree.ElementTree as ET

    project_path = os.path.abspath(project_path)

    if not os.path.isfile(project_path):
        return {
            "success": False,
            "error": f"Project file not found: {project_path}",
            "project": _escape_path(project_path),
        }

    try:
        tree = ET.parse(project_path)
        root = tree.getroot()

        targets = []
        device = ""

        for t in root.iter("Target"):
            name = t.findtext("TargetName", "")
            targets.append(name)

        for d in root.iter("Device"):
            device = d.text or ""
            break

        return {
            "success": True,
            "project": _escape_path(project_path),
            "project_name": os.path.splitext(os.path.basename(project_path))[0],
            "device": device,
            "targets": targets,
            "target_count": len(targets),
        }
    except ET.ParseError as e:
        return {
            "success": False,
            "error": f"XML parse error: {e}",
            "project": _escape_path(project_path),
        }
