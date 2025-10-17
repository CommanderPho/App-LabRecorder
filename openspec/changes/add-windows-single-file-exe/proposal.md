## Why
Distributing LabRecorder on Windows currently requires a directory with numerous Qt and support DLLs alongside the executable. This complicates deployment, user installation, and portability. The goal is to enable a distributable single-file `.exe` variant that runs on stock Windows without a companion DLL tree.

## What Changes
- Introduce a Windows build option that produces a single self-contained `.exe` bundling required Qt and support libraries.
- Support two packaging strategies, starting with the least complex:
  - Static/monolithic linking where licensing and toolchain permit; otherwise
  - Appending/embedding deployed DLLs and Qt plugins into a single executable container (e.g., using official Qt deployment followed by pack-into-exe tooling) with runtime extraction to a temp dir.
- Keep the current multi-file install path intact as the default; the single-file exe is an additional artifact.
- Document licensing implications (Qt LGPL, plugin loading) and how we comply (e.g., offer separate dynamic build and provide notices/source links).
- Update `BUILD.md` to include a step-by-step guide for producing and verifying the single-file `.exe` artifact.

## Impact
- Affected specs: `build-process` (Windows packaging requirements).
- Affected code/docs:
  - `CMakeLists.txt`, `CMakePresets.json`
  - Optional packaging scripts (PowerShell, CMake packaging, or third-party packers) gated behind an opt-in preset/option
  - `BUILD.md`, `README.md` (distribution guidance, licensing notes)
- No runtime behavior change to core app; only packaging and distribution options are extended.


