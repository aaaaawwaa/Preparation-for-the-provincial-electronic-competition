import os
import xml.etree.ElementTree as ET
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional


@dataclass
class KeilProject:
    path: str
    name: str
    device: str = ""
    vendor: str = ""
    cpu: str = ""
    targets: list = field(default_factory=list)
    source_files: list = field(default_factory=list)
    source_groups: list = field(default_factory=list)
    output_dir: str = ""
    output_name: str = ""
    create_hex: bool = False
    defines: list = field(default_factory=list)
    include_paths: list = field(default_factory=list)
    pack_id: str = ""

    def to_dict(self) -> dict:
        return {
            "path": self.path,
            "name": self.name,
            "device": self.device,
            "vendor": self.vendor,
            "cpu": self.cpu,
            "targets": self.targets,
            "source_groups": [
                {"name": g["name"], "file_count": len(g["files"])}
                for g in self.source_groups
            ],
            "source_file_count": len(self.source_files),
            "output_dir": self.output_dir,
            "output_name": self.output_name,
            "create_hex": self.create_hex,
            "defines": self.defines,
            "include_paths": self.include_paths,
            "pack_id": self.pack_id,
        }


def parse_project(project_path: str) -> KeilProject:
    """Parse a Keil .uvproj/.uvprojx file and return a KeilProject."""
    project_path = os.path.abspath(project_path)
    if not os.path.isfile(project_path):
        raise FileNotFoundError(f"Project file not found: {project_path}")

    tree = ET.parse(project_path)
    root = tree.getroot()
    project_dir = os.path.dirname(project_path)

    proj = KeilProject(
        path=project_path,
        name=os.path.splitext(os.path.basename(project_path))[0],
    )

    for device_el in root.iter("Device"):
        proj.device = device_el.text or ""
        break
    for vendor_el in root.iter("Vendor"):
        proj.vendor = vendor_el.text or ""
        break
    for cpu_el in root.iter("Cpu"):
        proj.cpu = cpu_el.text or ""
        break

    for t in root.iter("Target"):
        name = t.findtext("TargetName", "")
        proj.targets.append(name)

    for el in root.iter("OutputDirectory"):
        proj.output_dir = _resolve_relative(el.text or "", project_dir)
    for el in root.iter("OutputName"):
        proj.output_name = el.text or ""
    for el in root.iter("CreateHexFile"):
        proj.create_hex = el.text == "1"

    for el in root.iter("Define"):
        text = (el.text or "").strip()
        if text:
            proj.defines = [d.strip() for d in text.split(",") if d.strip()]
    for el in root.iter("IncludePath"):
        text = (el.text or "").strip()
        if text:
            proj.include_paths = [
                _resolve_relative(p.strip(), project_dir)
                for p in text.split(";") if p.strip()
            ]

    for el in root.iter("PackID"):
        proj.pack_id = el.text or ""
        break

    for group in root.iter("Group"):
        gname = group.findtext("GroupName", "")
        files = []
        for f_el in group.iter("File"):
            fname = f_el.findtext("FileName", "")
            fpath = f_el.findtext("FilePath", "")
            resolved = _resolve_relative(fpath or "", project_dir)
            files.append(resolved)
            proj.source_files.append(resolved)
        proj.source_groups.append({"name": gname, "files": files})

    return proj


def _resolve_relative(path_str: str, base_dir: str) -> str:
    if not path_str:
        return ""
    p = path_str.replace("\\", "/")
    if os.path.isabs(p):
        return os.path.normpath(p)
    resolved = os.path.normpath(os.path.join(base_dir, p))
    return resolved
