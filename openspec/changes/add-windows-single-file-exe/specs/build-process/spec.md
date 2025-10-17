## ADDED Requirements

### Requirement: Windows Single-File Executable Packaging
The system SHALL provide an optional Windows build that produces a self-contained single `.exe` artifact for the GUI (`LabRecorder.exe`) that can be distributed and launched without placing Qt DLLs, plugins, or auxiliary files next to it.

#### Scenario: Single-file exe build succeeds
- **WHEN** the developer runs the documented Windows single-file preset or packaging target
- **THEN** a single `LabRecorder.exe` is produced in the release output directory
- **AND** launching it on a clean Windows machine succeeds without adjacent Qt DLLs or plugin directories

#### Scenario: Multi-file build remains available
- **WHEN** the developer runs the standard Windows release preset
- **THEN** the existing multi-file deployment (with DLLs and plugin dirs) is still produced unchanged

#### Scenario: Licensing compliance documented
- **WHEN** the single-file packaging is enabled
- **THEN** the distribution includes licensing notices and, where required, provides access to corresponding source or dynamic build instructions to satisfy Qt LGPL obligations


