## 1. Implementation
- [ ] 1.1 Add Windows console helper (`win_console.h/.cpp`) to: detect console, alloc/free, show/hide, attach to parent if present.
- [ ] 1.2 GUI startup: Hide console by default on Windows builds (`BUILD_GUI`) while preserving CLI behavior.
- [ ] 1.3 Add menu action `View → Show Console` (checkable) in `MainWindow` and wire to toggle function.
- [ ] 1.4 Persist visibility preference in `LabRecorder.cfg` (optional) and restore on startup.
- [ ] 1.5 Disable/hide menu action on non-Windows platforms and for CLI build.
- [ ] 1.6 Manual tests: startup hidden, toggle show/hide, persistence, CLI unaffected.
- [ ] 1.7 Update `README.md` (Features) and `BUILD.md` (no new steps required) if needed.

## 2. Validation
- [ ] 2.1 Verify spec scenarios under `ui/console-visibility` manually on Windows.
- [ ] 2.2 Ensure no regressions in stream recording and logging behavior.

## 3. Release
- [ ] 3.1 Add change log entry for Windows console toggle feature.


