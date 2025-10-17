## 1. Implementation

- [ ] 1.1 Create/align CMake presets for release builds on Windows, macOS, Linux
- [ ] 1.2 Windows: ensure `.rc` links `res/app.ico` into GUI target
- [ ] 1.3 macOS: set `MACOSX_BUNDLE_ICON_FILE`, ensure `Info.plist` references `app.icns`
- [ ] 1.4 Linux: add `.desktop` entry and install icon assets to standard paths
- [ ] 1.5 Add optional packaging/deploy steps (windeployqt, macdeployqt, Linux install rules or CPack)
- [ ] 1.6 Update `BUILD.md` with authoritative per‑platform steps and artifact expectations
- [ ] 1.7 Smoke test artifacts on each OS (launch GUI, run CLI)
- [ ] 1.8 Document artifact naming/versioning scheme
- [ ] 1.9 (Optional) Add CI/job scripts to build and package per platform


