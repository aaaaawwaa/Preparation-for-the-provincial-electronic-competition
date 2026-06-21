# cli-anything-keil

CLI harness for **Keil MDK-ARM (Vision 4/5)**. Build, rebuild, flash, clean, and manage STM32/ARM projects from the command line — no GUI required.

## Prerequisites

- **Keil MDK-ARM v4 or v5** installed on Windows
- Python 3.8+

## Install

```bash
cd agent-harness
pip install -e .
```

Verify:

```bash
cli-anything-keil --help
```

If UV4.exe is not auto-detected, set the env var:

```bash
set KEIL_UV4_PATH=C:/Keil_v5/UV4/UV4.exe
```

## Quick Start

```bash
# Discover projects
cli-anything-keil discover

# View project info
cli-anything-keil project info

# Build incrementally
cli-anything-keil build

# Rebuild from scratch
cli-anything-keil rebuild

# Clean + rebuild
cli-anything-keil clean-build

# Flash to target
cli-anything-keil flash

# Clean artifacts (dry-run first)
cli-anything-keil clean --dry
cli-anything-keil clean

# Export artifacts
cli-anything-keil export -o ./release

# Machine-readable output
cli-anything-keil --json project info
cli-anything-keil --json build
```

## Command Reference

| Command | Description |
|---------|-------------|
| `build` | Incremental build (`-b -j0`) |
| `rebuild` | Full rebuild (`-r -j0`) |
| `clean-build` | Clean then rebuild (`-cr -j0`) |
| `flash` | Download firmware to MCU (`-f -j0`) |
| `clean` | Remove build artifacts (file removal) |
| `project info` | Show device, targets, sources |
| `project targets` | List build targets |
| `project sources` | List source files by group |
| `discover` | Find .uvproj/.uvprojx files recursively |
| `export` | Copy build artifacts to directory |
| `session show` | Display saved session state |
| `session set` | Set default project/target |
| `session clear` | Clear session state |
| `where` | Show UV4.exe installation path |
| `repl` | Interactive REPL mode (requires click-repl) |

## Global Options

| Option | Description |
|--------|-------------|
| `--json` | Machine-readable JSON output |
| `-p, --project` | Path to .uvproj/.uvprojx |
| `--dry-run` | Do not persist session state |
| `--color/--no-color` | Toggle colored output |

## Session State

Session state is persisted in `~/.cli-anything-keil/state.json`. It remembers your last project path, target name, and UV4 path so you don't need to specify them repeatedly.

Use `--dry-run` to skip saving, or `session clear` to reset.

## UV4.exe Discovery

1. `KEIL_UV4_PATH` environment variable
2. `UV4.exe` on system PATH
3. Well-known install locations (`C:/Keil_v5/UV4/`, `C:/Keil_v4/UV4/`, `C:/Keil/UV4/`)
4. Recursive search under `C:/Keil_v5/`
