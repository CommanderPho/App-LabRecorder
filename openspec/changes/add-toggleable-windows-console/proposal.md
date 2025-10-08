## Why
On Windows, the LabRecorder GUI currently launches with a console window visible by default. This is distracting for end users and not consistent with typical GUI app behavior. However, the console output is valuable for troubleshooting and monitoring. We need a way to suppress the console at startup while still allowing users to toggle it on demand from the GUI.

## What Changes
- Add a Windows-only capability to hide the console by default on GUI startup.
- Add a menu item (e.g., View → Show Console) with a checkable state to toggle the Windows console window visibility at runtime.
- Persist the last chosen visibility state in the existing configuration file if feasible.
- Ensure console output continues to be written when the console is shown; when hidden, output is not lost and can be re-shown.

## Impact
- Affected specs: `ui/console-visibility`
- Affected code:
  - `src/main.cpp` (Windows subsystem / console attachment behavior)
  - `src/mainwindow.*` (menu creation, action handling, persistence)
  - Potential helper in a new Windows-only module (e.g., `src/win_console.cpp/.h`) to encapsulate Win32 ShowWindow/AllocConsole/FreeConsole logic.


