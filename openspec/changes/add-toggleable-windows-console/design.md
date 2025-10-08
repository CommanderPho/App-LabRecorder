## Context
The GUI build of LabRecorder on Windows currently starts with a visible console window due to the process subsystem and/or console allocation behavior. Users prefer a clean GUI experience while still having access to console logs for troubleshooting.

## Goals / Non-Goals
- Goals:
  - Hide console window at GUI startup on Windows
  - Provide a runtime toggle via menu
  - Keep CLI behavior unchanged
- Non-Goals:
  - Cross-platform console management beyond hiding menu on non-Windows
  - Redirecting logs to files (future enhancement)

## Decisions
- Encapsulate Win32 console operations in a small helper: `win_console.h/.cpp` using `GetConsoleWindow`, `ShowWindow(SW_HIDE/SW_SHOW)`, `AllocConsole`, `FreeConsole`, and `AttachConsole(ATTACH_PARENT_PROCESS)` when appropriate.
- On GUI startup, if a console is present, hide it; if not present and user toggles on, allocate one (attach if launched from console; otherwise create new).
- Menu action is checkable; state reflects current visibility. Optionally persist visibility to `LabRecorder.cfg` under a new key (e.g., `ConsoleVisible=0|1`).

## Risks / Trade-offs
- Allocating/freeing a console at runtime may affect stdout/stderr handles; mitigation: after `AllocConsole`, call `freopen("CONOUT$","w",stdout)` and `freopen("CONOUT$","w",stderr)` to route output.
- If other modules expect a console at startup, they may access invalid handles; mitigation: GUI build should avoid writing to console before user toggles it on.

## Migration Plan
1. Add helper and integrate into `MainWindow` with a new View menu action.
2. Default hidden on Windows GUI; no change for CLI.
3. Add optional persistence.

## Open Questions
- Should we expose a keyboard shortcut (e.g., F12) to toggle the console?
- Should visibility be persisted per-user or per-app? Default: per config file.


