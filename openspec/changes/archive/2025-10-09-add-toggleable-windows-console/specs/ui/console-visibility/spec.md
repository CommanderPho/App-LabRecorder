## ADDED Requirements

### Requirement: Windows Console Visibility Toggle
The application SHALL allow users on Windows to toggle the visibility of the process console window at runtime and SHALL start with the console hidden when running the GUI build.

#### Scenario: Console hidden by default on GUI startup (Windows)
- **WHEN** the user starts the GUI application on Windows
- **THEN** the console window is not visible

#### Scenario: Toggle console from menu
- **WHEN** the user clicks View → Show Console
- **THEN** the console window becomes visible
- **AND** the menu item is checked to reflect visibility state

#### Scenario: Hide console from menu
- **WHEN** the user unchecks View → Show Console
- **THEN** the console window is hidden
- **AND** the menu item is unchecked

#### Scenario: Persist console visibility preference (optional)
- **WHEN** the user changes the console visibility
- **THEN** the last chosen setting is persisted to the configuration and restored on next launch (if feasible without introducing platform-specific config divergence)

#### Scenario: Non-Windows platforms unaffected
- **WHEN** the app runs on macOS or Linux
- **THEN** the menu item is hidden or disabled
- **AND** behavior is unchanged

#### Scenario: CLI build unaffected
- **WHEN** running `LabRecorderCLI`
- **THEN** console visibility behavior is unchanged and always shows the console


