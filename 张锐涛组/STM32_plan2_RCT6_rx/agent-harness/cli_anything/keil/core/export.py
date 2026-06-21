import os
import shutil
import glob as gb
from pathlib import Path
from typing import Dict, List, Optional


def export_artifacts(project_path: str, output_dir: str,
                     types: Optional[List[str]] = None) -> Dict:
    """Copy build artifacts to output_dir.

    Args:
        project_path: Path to .uvprojx file.
        output_dir: Destination directory.
        types: List of extensions to include (e.g. ['hex', 'bin', 'axf']).
               None means all.
    """
    project_dir = os.path.dirname(os.path.abspath(project_path))
    os.makedirs(output_dir, exist_ok=True)

    patterns = {
        "hex": "*.hex",
        "bin": "*.bin",
        "axf": "*.axf",
        "elf": "*.elf",
        "map": "*.map",
        "lst": "*.lst",
        "htm": "*.htm",
    }

    if types is None:
        extensions = list(patterns.keys())
    else:
        extensions = [t for t in types if t in patterns]

    copied = []
    for ext in extensions:
        pat = patterns[ext]
        for f in gb.glob(os.path.join(project_dir, "**", pat), recursive=True):
            dest = os.path.join(output_dir, os.path.basename(f))
            shutil.copy2(f, dest)
            copied.append(dest)

    return {
        "success": len(copied) > 0,
        "output_dir": os.path.abspath(output_dir),
        "copied": copied,
        "count": len(copied),
    }


def find_artifacts(project_path: str) -> List[str]:
    """Find all build artifact paths for a project."""
    project_dir = os.path.dirname(os.path.abspath(project_path))
    patterns = ["*.hex", "*.bin", "*.axf", "*.elf", "*.map", "*.lst"]
    found = []
    for pat in patterns:
        for f in gb.glob(os.path.join(project_dir, "**", pat), recursive=True):
            found.append(os.path.abspath(f))
    return found
