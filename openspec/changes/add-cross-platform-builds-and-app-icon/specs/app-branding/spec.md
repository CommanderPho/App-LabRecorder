## ADDED Requirements

### Requirement: Application Icon Embedding
The system SHALL apply the project icon to platform‑specific application outputs so that the correct icon appears in system UIs.

#### Scenario: Windows icon applied
- **WHEN** the GUI target is built on Windows
- **THEN** the resulting `.exe` embeds `res/app.ico` via a `.rc` file and shows the icon in Explorer and the taskbar

#### Scenario: macOS icon applied
- **WHEN** the GUI bundle is built on macOS
- **THEN** the `.app` contains `res/app.icns` and `Info.plist` references it; Finder shows the icon

#### Scenario: Linux icon applied
- **WHEN** the application is installed or packaged on Linux
- **THEN** icon assets are installed to standard locations and a `.desktop` file references them so desktop launchers display the icon


