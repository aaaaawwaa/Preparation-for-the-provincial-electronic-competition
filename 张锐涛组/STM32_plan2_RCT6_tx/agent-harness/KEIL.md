# Keil MDK-ARM SOP — CLI Harness

## Software Analysis

- **Name:** Keil MDK-ARM (Vision)
- **Backend CLI:** UV4.exe (bundled with Vision IDE)
- **Native format:** `.uvproj` (Vision 4), `.uvprojx` (Vision 5), both XML
- **Platform:** Windows only
- **Hard dependency:** Keil MDK-ARM installation (v4 or v5)

## Architecture

```
cli-anything-keil              # User-facing CLI (Click)
  ├── core/build.py            # UV4Runner — subprocess wrapper for UV4.exe
  ├── core/project.py          # KeilProject — .uvprojx XML parser
  ├── core/session.py          # SessionManager — JSON state persistence
  ├── core/export.py           # Artifact export/copy
  └── utils/log_parser.py      # BuildResult, log parsing (error/warning counts)
       └── UV4.exe              # Real Keil build engine
```

### UV4.exe CLI flags (documented):

| Flag         | Meaning               |
|--------------|-----------------------|
| `-b <.uvproj>` | Build (incremental) |
| `-r <.uvproj>` | Rebuild all         |
| `-cr <.uvproj>`| Clean + rebuild     |
| `-f <.uvproj>` | Flash download      |
| `-d <.uvproj>` | Start debug         |
| `-j0`          | Silent mode (no GUI)|
| `-t <name>`    | Select target       |
| `-o <file>`    | Output log file     |

## Command Mapping

| CLI command   | UV4 invocation                       |
|---------------|--------------------------------------|
| `build`       | `UV4.exe -b project.uvprojx -j0`    |
| `rebuild`     | `UV4.exe -r project.uvprojx -j0`    |
| `clean-build` | `UV4.exe -cr project.uvprojx -j0`   |
| `flash`       | `UV4.exe -f project.uvprojx -j0`    |
| `clean`       | filesystem removal (no UV4 flag)    |
| `project info`| XML parse of .uvprojx               |
| `project targets` | XML parse of .uvprojx           |
| `project sources` | XML parse of .uvprojx           |
| `discover`    | filesystem walk                     |
| `export`      | file copy                           |

## Exit Codes

| Code | Meaning |
|------|---------|
| 0 | No errors or warnings |
| 1 | Warnings only |
| 2 | Errors |
| 3 | Fatal errors |
| 11 | Cannot open project file |
| 12 | Device not found in database |
| 13 | Error writing project file |
| 15 | Error reading import XML |
| 20 | Project conversion error |

**Note:** Exit codes 0 and 1 can be ambiguous. The harness parses the build log for accurate error/warning counts using regex: `r"(\d+)\s*Error\(s\),\s*(\d+)\s*Warning\(s\)"`.

## Import Conventions

```python
from cli_anything.keil.core.build import UV4Runner
from cli_anything.keil.core.project import parse_project, KeilProject
from cli_anything.keil.core.session import SessionManager
from cli_anything.keil.core.export import export_artifacts
from cli_anything.keil.utils.log_parser import BuildResult, parse_build_log
```

## Session State

State file: `~/.cli-anything-keil/state.json`

```json
{
  "project_path": "/path/to/project.uvprojx",
  "target_name": "Target 1",
  "uv4_path": "C:/Keil_v5/UV4/UV4.exe",
  "updated_at": "2026-06-16T17:18:30"
}
```

Auto-save after build/flash/rebuild/clean-build commands. Suppressed with `--dry-run`.
