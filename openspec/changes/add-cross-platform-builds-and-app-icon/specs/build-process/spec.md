## ADDED Requirements

### Requirement: Cross-Platform Build Standardization
The system SHALL provide a repeatable, documented process to produce platform‑specific binaries for Windows, macOS, and Linux using CMake presets and platform‑appropriate deployment steps so the resulting artifacts are runnable on a stock system for that OS.

#### Scenario: Windows build succeeds
- **WHEN** the developer runs the documented Windows release preset
- **THEN** `LabRecorder.exe` and `LabRecorderCLI.exe` are produced in a release directory with required Qt/LSL runtimes present (via deployment or documented steps)

#### Scenario: macOS build succeeds
- **WHEN** the developer runs the documented macOS release preset
- **THEN** a `.app` bundle for the GUI and a CLI binary are produced, with required Qt runtimes bundled via `macdeployqt` (or equivalent documented step)

#### Scenario: Linux build succeeds
- **WHEN** the developer runs the documented Linux release preset
- **THEN** installed binaries (or a staged install tree/package) are produced, with clear instructions to satisfy runtime dependencies and an optional `.desktop` entry for the GUI


