#!/usr/bin/env python3
"""CLI harness for Keil MDK-ARM (Vision). Build, flash, and manage STM32 projects.

Usage:
    cli-anything-keil build                     # build in current directory
    cli-anything-keil build -p path/to/test.uvprojx
    cli-anything-keil rebuild --target "Target 1"
    cli-anything-keil flash
    cli-anything-keil clean
    cli-anything-keil project info --json
    cli-anything-keil discover
    cli-anything-keil export -o ./release
    cli-anything-keil session show
    cli-anything-keil repl
"""

import os
import sys
import json
import time
from pathlib import Path

import click

# Ensure the namespace package works when run directly
_here = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
if _here not in sys.path:
    sys.path.insert(0, _here)

from cli_anything.keil.core.build import UV4Runner
from cli_anything.keil.core.project import parse_project, KeilProject
from cli_anything.keil.core.session import SessionManager
from cli_anything.keil.core.export import export_artifacts, find_artifacts
from cli_anything.keil.utils.log_parser import BuildResult, parse_build_log

PROJECT_EXTENSIONS = (".uvproj", ".uvprojx")


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _find_project(start_dir: str = ".") -> str:
    """Search for a Keil project file in the directory tree."""
    start = os.path.abspath(start_dir)
    for f in os.listdir(start):
        if f.lower().endswith(PROJECT_EXTENSIONS):
            return os.path.join(start, f)
    for root, dirs, files in os.walk(start):
        for f in files:
            if f.lower().endswith(PROJECT_EXTENSIONS):
                return os.path.join(root, f)
    return ""


def _resolve_project(ctx, project_arg: str) -> str:
    """Resolve project path from CLI arg, session, or auto-detect."""
    if project_arg:
        p = os.path.abspath(project_arg)
        if os.path.isfile(p):
            return p
        raise click.BadParameter(f"Project file not found: {project_arg}")
    session = ctx.obj.get("session_manager", SessionManager()).state
    if session.project_path and os.path.isfile(session.project_path):
        return session.project_path
    found = _find_project()
    if found:
        return found
    raise click.UsageError(
        "No Keil project file (.uvproj/.uvprojx) found. "
        "Use -p to specify the project path."
    )


def _resolve_target(target_arg: str, ctx) -> str:
    """Resolve target name from CLI arg or session."""
    if target_arg:
        return target_arg
    session = ctx.obj.get("session_manager", SessionManager()).state
    return session.target_name or ""


def _maybe_save_session(ctx, project_path: str, target: str):
    """Save session state if not dry-run."""
    sm = ctx.obj.get("session_manager")
    if sm is None:
        return
    state = sm.state
    state.project_path = project_path
    if target:
        state.target_name = target
    sm.save(state)


def _format_result(result, use_json: bool):
    """Print result in human-readable or JSON format."""
    if use_json:
        click.echo(json.dumps(result, indent=2, ensure_ascii=False))
        return

    if result.get("uv4_path"):
        click.secho(f"UV4: {result['uv4_path']}", fg="blue")
    if result.get("project"):
        click.secho(f"Project: {result['project']}", fg="blue")
    if result.get("target"):
        click.secho(f"Target: {result['target']}", fg="blue")
    if "elapsed" in result:
        click.secho(f"Time: {result['elapsed']:.1f}s", fg="blue")

    if "device" in result:
        click.echo(f"Device: {result['device']}  |  CPU: {result.get('cpu', '')}")
        click.echo(f"Targets: {', '.join(result.get('targets', []))}")
        click.echo(f"Sources: {result.get('source_file_count', 0)} files")
        if result.get("defines"):
            click.echo(f"Defines: {', '.join(result['defines'])}")
        return

    if "errors" in result:
        errors = result["errors"]
        warnings = result["warnings"]
        color = "green" if result["success"] else "red"
        click.secho(f"Result: {errors} error(s), {warnings} warning(s)", fg=color)
        log_content = result.get("log", "")
        if log_content and log_content.strip():
            click.secho("--- Build Log ---", fg="blue")
            click.echo(log_content)

    if "removed_count" in result:
        click.echo(f"Removed: {result['removed_count']} file(s)")

    if "would_remove" in result:
        count = result.get("count", len(result["would_remove"]))
        click.echo(f"Would remove {count} file(s):")
        for f in result["would_remove"][:30]:
            click.echo(f"  {f}")
        if count > 30:
            click.echo(f"  ... and {count - 30} more")

    if "copied" in result:
        click.echo(f"Exported: {result['count']} file(s) to {result['output_dir']}")
        for f in result["copied"]:
            click.echo(f"  {os.path.basename(f)}")

    if "projects" in result:
        for p in result["projects"]:
            click.echo(f"  {p}")


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

@click.group(invoke_without_command=True)
@click.option("--json", "use_json", is_flag=True, help="Machine-readable JSON output.")
@click.option("-p", "--project", "project_arg", default="", help="Path to .uvproj/.uvprojx file.")
@click.option("--dry-run", is_flag=True, help="Do not persist session state.")
@click.option("--color/--no-color", default=True, help="Colored output.")
@click.pass_context
def cli(ctx, use_json, project_arg, dry_run, color):
    """cli-anything-keil — CLI harness for Keil MDK-ARM (Vision).

    Wraps UV4.exe for build, rebuild, flash, clean, and project management.
    Auto-detects project file in current directory tree.
    """
    ctx.ensure_object(dict)
    ctx.obj["json"] = use_json
    ctx.obj["project_arg"] = project_arg
    ctx.obj["session_manager"] = SessionManager(dry_run=dry_run)

    if ctx.invoked_subcommand is None:
        click.echo(ctx.get_help())


# ---------------------------------------------------------------------------
# Build commands
# ---------------------------------------------------------------------------

@cli.command()
@click.option("-t", "--target", default="", help="Build target name.")
@click.option("-o", "--output", default="", help="Output log file path.")
@click.option("--timeout", default=300, type=int, help="Max build time (seconds).")
@click.pass_context
def build(ctx, target, output, timeout):
    """Build the Keil project (incremental)."""
    project = _resolve_project(ctx, ctx.obj["project_arg"])
    target = _resolve_target(target, ctx)
    runner = UV4Runner()
    result = runner.build(project, target=target or None,
                          output_log=output or None, timeout=timeout)
    _maybe_save_session(ctx, project, target)
    _format_result(result.to_dict(), ctx.obj["json"])
    if not result.success:
        raise SystemExit(max(result.returncode, 1))


@cli.command()
@click.option("-t", "--target", default="", help="Build target name.")
@click.option("-o", "--output", default="", help="Output log file path.")
@click.option("--timeout", default=300, type=int, help="Max build time (seconds).")
@click.pass_context
def rebuild(ctx, target, output, timeout):
    """Rebuild all targets from scratch."""
    project = _resolve_project(ctx, ctx.obj["project_arg"])
    target = _resolve_target(target, ctx)
    runner = UV4Runner()
    result = runner.rebuild(project, target=target or None,
                            output_log=output or None, timeout=timeout)
    _maybe_save_session(ctx, project, target)
    _format_result(result.to_dict(), ctx.obj["json"])
    if not result.success:
        raise SystemExit(max(result.returncode, 1))


@cli.command()
@click.option("-t", "--target", default="", help="Build target name.")
@click.option("-o", "--output", default="", help="Output log file path.")
@click.option("--timeout", default=300, type=int, help="Max build time (seconds).")
@click.pass_context
def clean_build(ctx, target, output, timeout):
    """Clean then rebuild the Keil project."""
    project = _resolve_project(ctx, ctx.obj["project_arg"])
    target = _resolve_target(target, ctx)
    runner = UV4Runner()
    result = runner.clean_build(project, target=target or None,
                                output_log=output or None, timeout=timeout)
    _maybe_save_session(ctx, project, target)
    _format_result(result.to_dict(), ctx.obj["json"])
    if not result.success:
        raise SystemExit(max(result.returncode, 1))


@cli.command()
@click.option("-t", "--target", default="", help="Build target name.")
@click.option("--timeout", default=120, type=int, help="Max flash time (seconds).")
@click.pass_context
def flash(ctx, target, timeout):
    """Download firmware to target via debug probe."""
    project = _resolve_project(ctx, ctx.obj["project_arg"])
    target = _resolve_target(target, ctx)
    runner = UV4Runner()
    result = runner.flash(project, target=target or None, timeout=timeout)
    _maybe_save_session(ctx, project, target)
    _format_result(result.to_dict(), ctx.obj["json"])
    if not result.success:
        raise SystemExit(max(result.returncode, 1))


# ---------------------------------------------------------------------------
# Clean command
# ---------------------------------------------------------------------------

@cli.command()
@click.option("-p", "--project-override", default="", help="Project path (overrides session/auto-detect).")
@click.option("--dry", is_flag=True, help="List files that would be removed without deleting.")
@click.pass_context
def clean(ctx, project_override, dry):
    """Remove build artifacts (OBJ, Listings, etc.)."""
    project = _resolve_project(ctx, project_override or ctx.obj["project_arg"])
    project_dir = os.path.dirname(os.path.abspath(project))
    # Also search parent dir (project root) for artifacts like OBJ/
    root_dir = os.path.dirname(project_dir)

    patterns = ["*.o", "*.obj", "*.hex", "*.axf", "*.elf", "*.lst",
                "*.map", "*.plg", "*.bak", "*.dep", "*.crf", "*.d",
                "*.lnp", "*.htm", "*.tra", "*.iex", "*.JLinkLog.txt",
                "*.build_log.htm", "*.sct"]

    to_remove = []
    seen = set()
    for search_base in (project_dir, root_dir):
        for pat in patterns:
            for f in Path(search_base).rglob(pat):
                fp = str(f)
                if fp not in seen:
                    to_remove.append(fp)
                    seen.add(fp)
        for d_name in ["OBJ", "Listings"]:
            d = os.path.join(search_base, d_name)
            if os.path.isdir(d):
                for root, dirs, files in os.walk(d, topdown=False):
                    for f in files:
                        fp = os.path.join(root, f)
                        if fp not in seen:
                            to_remove.append(fp)
                            seen.add(fp)

    if dry:
        result = {"project": project, "would_remove": to_remove,
                  "count": len(to_remove), "success": True}
        _format_result(result, ctx.obj["json"])
        return

    removed = []
    failed = []
    for f in to_remove:
        try:
            os.remove(f)
            removed.append(f)
        except OSError as e:
            failed.append(str(e))

    result = {"project": project, "removed_count": len(removed),
              "removed": removed, "failed": failed,
              "success": len(failed) == 0}
    _format_result(result, ctx.obj["json"])


# ---------------------------------------------------------------------------
# Project commands
# ---------------------------------------------------------------------------

@cli.group()
def project():
    """Project inspection commands."""


@project.command("info")
@click.option("-p", "--project-override", default="", help="Path to .uvproj/.uvprojx file.")
@click.pass_context
def project_info(ctx, project_override):
    """Show detailed project information."""
    project_path = _resolve_project(ctx, project_override or ctx.obj["project_arg"])
    proj = parse_project(project_path)
    _format_result(proj.to_dict(), ctx.obj["json"])


@project.command("targets")
@click.option("-p", "--project-override", default="", help="Path to .uvproj/.uvprojx file.")
@click.pass_context
def project_targets(ctx, project_override):
    """List available build targets."""
    project_path = _resolve_project(ctx, project_override or ctx.obj["project_arg"])
    proj = parse_project(project_path)
    if ctx.obj["json"]:
        click.echo(json.dumps({"project": project_path, "targets": proj.targets},
                              indent=2, ensure_ascii=False))
    else:
        click.secho(f"Project: {project_path}", fg="blue")
        for i, t in enumerate(proj.targets, 1):
            click.echo(f"  [{i}] {t}")


@project.command("sources")
@click.option("-p", "--project-override", default="", help="Path to .uvproj/.uvprojx file.")
@click.pass_context
def project_sources(ctx, project_override):
    """List source files grouped by group."""
    project_path = _resolve_project(ctx, project_override or ctx.obj["project_arg"])
    proj = parse_project(project_path)
    if ctx.obj["json"]:
        click.echo(json.dumps({
            "project": project_path,
            "groups": [{"name": g["name"], "files": g["files"]} for g in proj.source_groups]
        }, indent=2, ensure_ascii=False))
    else:
        click.secho(f"Project: {project_path}", fg="blue")
        for g in proj.source_groups:
            click.secho(f"  [{g['name']}]", fg="yellow")
            for f in g["files"]:
                click.echo(f"    {f}")


# ---------------------------------------------------------------------------
# Discover command
# ---------------------------------------------------------------------------

@cli.command()
@click.option("-d", "--directory", default=".", type=click.Path(exists=True),
              help="Directory to scan.")
@click.pass_context
def discover(ctx, directory):
    """Discover all Keil project files in a directory tree."""
    found = []
    start = os.path.abspath(directory)
    for root, dirs, files in os.walk(start):
        for f in files:
            if f.lower().endswith(PROJECT_EXTENSIONS):
                found.append(os.path.join(root, f))
    result = {"directory": start, "projects": found, "count": len(found)}
    _format_result(result, ctx.obj["json"])


# ---------------------------------------------------------------------------
# Export command
# ---------------------------------------------------------------------------

@cli.command()
@click.option("-p", "--project-override", default="", help="Path to .uvproj/.uvprojx file.")
@click.option("-o", "--output-dir", required=True, type=click.Path(),
              help="Output directory for artifacts.")
@click.option("--type", "artifact_types", default="hex,bin,axf",
              help="Comma-separated artifact types: hex,bin,axf,elf,map,lst (default: hex,bin,axf).")
@click.pass_context
def export(ctx, project_override, output_dir, artifact_types):
    """Export build artifacts to a directory."""
    project = _resolve_project(ctx, project_override or ctx.obj["project_arg"])
    types = [t.strip() for t in artifact_types.split(",") if t.strip()]
    result = export_artifacts(project, output_dir, types)
    _format_result(result, ctx.obj["json"])


# ---------------------------------------------------------------------------
# Session commands
# ---------------------------------------------------------------------------

@cli.group()
def session():
    """Session state management commands."""


@session.command("show")
@click.pass_context
def session_show(ctx):
    """Show current session state."""
    sm = ctx.obj.get("session_manager", SessionManager())
    state = sm.state
    result = {
        "project_path": state.project_path,
        "target_name": state.target_name,
        "uv4_path": state.uv4_path,
        "last_build_result": state.last_build_result,
        "updated_at": state.updated_at,
    }
    if ctx.obj["json"]:
        click.echo(json.dumps(result, indent=2, ensure_ascii=False))
    else:
        click.secho("Session State", fg="blue", bold=True)
        click.echo(f"  Project:     {state.project_path or '(not set)'}")
        click.echo(f"  Target:      {state.target_name or '(not set)'}")
        click.echo(f"  UV4 Path:    {state.uv4_path or '(auto-detect)'}")
        click.echo(f"  Updated:     {state.updated_at or '(never)'}")


@session.command("set")
@click.option("--project-path", default="", help="Set default project path.")
@click.option("--target-name", default="", help="Set default target name.")
@click.option("--uv4-path", default="", help="Set UV4.exe path.")
@click.pass_context
def session_set(ctx, project_path, target_name, uv4_path):
    """Set session defaults."""
    sm = ctx.obj.get("session_manager", SessionManager())
    state = sm.load()
    if project_path:
        state.project_path = os.path.abspath(project_path)
    if target_name:
        state.target_name = target_name
    if uv4_path:
        state.uv4_path = uv4_path
    sm.save(state)

    if ctx.obj["json"]:
        click.echo(json.dumps({"success": True, "state": state.to_dict()},
                              indent=2, ensure_ascii=False))
    else:
        click.secho("Session updated.", fg="green")
        click.echo(f"  Project:  {state.project_path or '(not set)'}")
        click.echo(f"  Target:   {state.target_name or '(not set)'}")
        click.echo(f"  UV4 Path: {state.uv4_path or '(auto-detect)'}")


@session.command("clear")
@click.pass_context
def session_clear(ctx):
    """Clear saved session state."""
    sm = ctx.obj.get("session_manager", SessionManager())
    sm.clear()
    if ctx.obj["json"]:
        click.echo(json.dumps({"success": True, "message": "Session cleared."}))
    else:
        click.secho("Session cleared.", fg="green")


# ---------------------------------------------------------------------------
# Where command
# ---------------------------------------------------------------------------

@cli.command()
@click.pass_context
def where(ctx):
    """Show UV4.exe installation path."""
    try:
        runner = UV4Runner()
        path = runner.path
        result = {"uv4_path": path, "success": True}
    except RuntimeError as e:
        result = {"uv4_path": None, "success": False, "error": str(e)}
    _format_result(result, ctx.obj["json"])
    if not result["success"]:
        raise SystemExit(1)


# ---------------------------------------------------------------------------
# REPL command
# ---------------------------------------------------------------------------

@cli.command()
@click.option("--prompt", default="keil> ", help="REPL prompt string.")
@click.pass_context
def repl(ctx, prompt):
    """Start interactive REPL mode."""
    try:
        import click_repl
    except ImportError:
        click.secho(
            "REPL mode requires click-repl. Install with: pip install click-repl",
            fg="red",
        )
        raise SystemExit(1)

    click.secho("cli-anything-keil REPL", fg="blue", bold=True)
    click.secho(f"Project: {_find_project() or '(not found)'}", fg="yellow")
    click.secho('Type "help" for commands, "exit" to quit.', dim=True)

    click_repl.repl(ctx, click_repl.ExitRepl())


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    cli()


if __name__ == "__main__":
    main()
