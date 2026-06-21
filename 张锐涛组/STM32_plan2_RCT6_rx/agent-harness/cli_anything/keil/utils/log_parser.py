import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Tuple


@dataclass
class BuildResult:
    success: bool
    errors: int = 0
    warnings: int = 0
    returncode: int = 0
    log: str = ""
    stderr: str = ""
    stdout: str = ""
    project: str = ""
    target: Optional[str] = None
    uv4_path: str = ""
    artifacts: list = field(default_factory=list)
    elapsed: float = 0.0

    def to_dict(self) -> dict:
        return {
            "success": self.success,
            "errors": self.errors,
            "warnings": self.warnings,
            "returncode": self.returncode,
            "log": self.log,
            "project": self.project,
            "target": self.target,
            "uv4_path": self.uv4_path,
            "artifacts": self.artifacts,
            "elapsed": self.elapsed,
        }


_ERROR_WARNING_RE = re.compile(r"(\d+)\s*Error\(s\),\s*(\d+)\s*Warning\(s\)", re.IGNORECASE)


def parse_build_log(log_text: str) -> Tuple[int, int]:
    """Parse Keil build log for error and warning counts.

    Priority: match the canonical summary line, then fall back to
    counting individual Error:/Warning: prefixes.
    """
    match = _ERROR_WARNING_RE.search(log_text)
    if match:
        return int(match.group(1)), int(match.group(2))

    errors = log_text.count("Error:") + log_text.count("error:")
    warnings = log_text.count("Warning:") + log_text.count("warning:")
    return errors, warnings


def parse_errors_from_log(log_text: str) -> List[Dict]:
    """Extract individual error entries from build log."""
    results = []
    for m in re.finditer(r"^(.*?)\((\d+)\):\s*(error|warning):\s*(.*?)$",
                         log_text, re.MULTILINE | re.IGNORECASE):
        results.append({
            "file": m.group(1).strip(),
            "line": int(m.group(2)),
            "severity": m.group(3).lower(),
            "message": m.group(4).strip(),
        })
    return results
