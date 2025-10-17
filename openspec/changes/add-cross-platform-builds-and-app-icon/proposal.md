## Why
Current build steps differ by platform and rely on ad‑hoc, manual instructions. This leads to inconsistent binary artifacts and occasional missing runtime dependencies. In addition, the application icon is not guaranteed to be applied consistently across Windows, macOS, and Linux outputs, which hurts polish and brand recognition.

## What Changes
- Standardize a cross‑platform build process using CMake presets for Windows, macOS, and Linux to produce release‑ready binaries.
- Integrate platform deployment steps (e.g., Qt deploy tools) into the documented flow or scripted targets to ensure shipped artifacts are runnable.
- Apply and verify the application icon on all supported platforms:
  - Windows: `.ico` via `.rc` linked into the GUI executable
  - macOS: `.icns` referenced via `Info.plist` and `MACOSX_BUNDLE_ICON_FILE`
  - Linux: install icon assets and reference them from a `.desktop` entry
- Update `BUILD.md` with a single, authoritative, step‑by‑step section per platform.
- Optionally add packaging steps (CPack or platform deploy tools) to simplify artifact creation without introducing unnecessary complexity.

No breaking changes to runtime behavior are intended.

## Impact
- Affected specs: `build-process`, `app-branding`
- Affected code/docs:
  - `CMakeLists.txt`, `CMakePresets.json`
  - `cmake/MacOSXBundleInfo.plist.in`
  - `res/app.ico`, `res/app.icns`, `res/app.rc`
  - `BUILD.md`, `README.md`
  - Optional CI/deployment scripts


