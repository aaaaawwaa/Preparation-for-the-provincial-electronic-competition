# Test Plan & Results — cli-anything-keil

## Test Plan

### Unit Tests (test_core.py)

| Module | Test Class | What It Covers |
|--------|-----------|----------------|
| `log_parser` | `TestBuildResult` | BuildResult dataclass defaults, to_dict serialization |
| `log_parser` | `TestParseBuildLog` | Canonical summary line, spacing variation, fallback count, empty log, case insensitivity |
| `log_parser` | `TestParseErrorsFromLog` | Error extraction, empty log |
| `project` | `TestParseProject` | Real .uvprojx parsing, to_dict output, file-not-found handling |
| `session` | `TestSessionState` | Round-trip serialization, default values |
| `session` | `TestSessionManager` | Dry-run suppression, save/load persistence, clear |

### E2E Tests (test_full_e2e.py)

| Test Class | What It Covers |
|-----------|----------------|
| `TestCLIBasic` | --help, discover (text+JSON), project info/text+JSON, targets, sources, where, clean --dry, session flow (set/show/clear), session --dry-run |
| `TestCLIJSONOutput` | JSON flag acceptance, valid JSON structure for discover and project info |
| `TestCLISubprocess` | Installed CLI via subprocess (gated by CLI_ANYTHING_FORCE_INSTALLED=1) |

### Workflow Scenarios

1. **First-time user**: `discover` → `project info` → `build` → `flash`
2. **Session user**: `session set` → `build` → `rebuild` → `clean`
3. **CI pipeline**: `--json project info` → `--json clean-build` → `--json export -o artifacts/`

## Test Results

```
============================= test session starts =============================
platform win32 -- Python 3.8.6, pytest-8.3.5, pluggy-1.5.0
rootdir: agent-harness
collected 32 items

test_core.py::TestBuildResult::test_defaults ...................... PASSED
test_core.py::TestBuildResult::test_to_dict ....................... PASSED
test_core.py::TestParseBuildLog::test_canonical_summary_line ...... PASSED
test_core.py::TestParseBuildLog::test_spacing_variation ........... PASSED
test_core.py::TestParseBuildLog::test_fallback_count .............. PASSED
test_core.py::TestParseBuildLog::test_no_matches .................. PASSED
test_core.py::TestParseBuildLog::test_case_insensitive ............ PASSED
test_core.py::TestParseErrorsFromLog::test_extracts_entries ....... PASSED
test_core.py::TestParseErrorsFromLog::test_empty_log .............. PASSED
test_core.py::TestParseProject::test_parse_real_project ........... PASSED
test_core.py::TestParseProject::test_to_dict ...................... PASSED
test_core.py::TestParseProject::test_file_not_found ............... PASSED
test_core.py::TestSessionState::test_roundtrip .................... PASSED
test_core.py::TestSessionState::test_defaults ..................... PASSED
test_core.py::TestSessionManager::test_dry_run_does_not_persist ... PASSED
test_core.py::TestSessionManager::test_save_and_load .............. PASSED
test_core.py::TestSessionManager::test_clear ...................... PASSED
test_full_e2e.py::TestCLIBasic::test_help ......................... PASSED
test_full_e2e.py::TestCLIBasic::test_discover ..................... PASSED
test_full_e2e.py::TestCLIBasic::test_discover_json ................ PASSED
test_full_e2e.py::TestCLIBasic::test_project_info ................. PASSED
test_full_e2e.py::TestCLIBasic::test_project_info_json ............ PASSED
test_full_e2e.py::TestCLIBasic::test_project_targets .............. PASSED
test_full_e2e.py::TestCLIBasic::test_project_sources .............. PASSED
test_full_e2e.py::TestCLIBasic::test_where ........................ PASSED
test_full_e2e.py::TestCLIBasic::test_clean_dry .................... PASSED
test_full_e2e.py::TestCLIBasic::test_session_flow ................. PASSED
test_full_e2e.py::TestCLIBasic::test_session_dry_run .............. PASSED
test_full_e2e.py::TestCLIJSONOutput::test_* (3 tests) ............. PASSED
test_full_e2e.py::TestCLISubprocess::test_help_via_subprocess ..... SKIPPED

======================== 31 passed, 1 skipped in 0.43s ========================
```

## Coverage Summary

- **Unit tests**: 17 passed — all core module functions covered
- **E2E tests**: 14 passed, 1 skipped — all CLI commands covered via CliRunner
- **Subprocess tests**: 1 skipped (requires CLI in PATH and CLI_ANYTHING_FORCE_INSTALLED=1)
- **Total**: 31/32 passed (96.9%)
