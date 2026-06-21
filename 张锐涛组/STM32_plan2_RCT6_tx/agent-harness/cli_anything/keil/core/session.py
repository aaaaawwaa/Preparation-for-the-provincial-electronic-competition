import os
import json
import time
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import Optional


STATE_DIR = os.path.join(os.path.expanduser("~"), ".cli-anything-keil")
STATE_FILE = os.path.join(STATE_DIR, "state.json")


@dataclass
class SessionState:
    project_path: str = ""
    target_name: str = ""
    uv4_path: str = ""
    last_build_result: Optional[dict] = None
    updated_at: str = ""

    def to_dict(self) -> dict:
        return asdict(self)

    @classmethod
    def from_dict(cls, d: dict) -> "SessionState":
        return cls(**{k: v for k, v in d.items() if k in cls.__dataclass_fields__})


class SessionManager:
    """Manages persistent session state for the Keil CLI harness."""

    def __init__(self, dry_run: bool = False):
        self.dry_run = dry_run
        self._state: Optional[SessionState] = None

    def load(self) -> SessionState:
        """Load state from disk, or return a fresh state."""
        if self._state is not None:
            return self._state
        if os.path.isfile(STATE_FILE):
            try:
                with open(STATE_FILE, "r", encoding="utf-8") as f:
                    data = json.load(f)
                self._state = SessionState.from_dict(data)
            except (json.JSONDecodeError, TypeError):
                self._state = SessionState()
        else:
            self._state = SessionState()
        return self._state

    def save(self, state: Optional[SessionState] = None) -> bool:
        """Persist state to disk. No-op if dry_run is True."""
        if self.dry_run:
            return False
        if state is not None:
            self._state = state
        if self._state is None:
            return False
        self._state.updated_at = time.strftime("%Y-%m-%dT%H:%M:%S")
        os.makedirs(STATE_DIR, exist_ok=True)
        with open(STATE_FILE, "w", encoding="utf-8") as f:
            json.dump(self._state.to_dict(), f, indent=2, ensure_ascii=False)
        return True

    def clear(self) -> bool:
        """Remove persisted state."""
        self._state = SessionState()
        if self.dry_run:
            return False
        if os.path.isfile(STATE_FILE):
            os.remove(STATE_FILE)
        return True

    @property
    def state(self) -> SessionState:
        return self.load()
