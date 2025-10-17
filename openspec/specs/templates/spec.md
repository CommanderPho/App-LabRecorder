# templates Specification

## Purpose
TBD - created by archiving change add-hostname-filename-token. Update Purpose after archive.
## Requirements
### Requirement: Hostname token expansion in filename templates
The system SHALL support `%hostname` in filename templates, expanding it to the local machine hostname.

#### Scenario: Replace %hostname in legacy template
- **WHEN** the template includes `%hostname` (e.g., `runs/%hostname_%date_%time.xdf`)
- **THEN** the resulting filename contains the machine's hostname in place of `%hostname`
- **AND** any characters not safe for filenames are sanitized (e.g., spaces → `_`, path separators removed)

#### Scenario: Replace %hostname in BIDS-like paths
- **WHEN** the template includes `%hostname` within a BIDS-style path
- **THEN** `%hostname` is expanded consistently and remains filename-safe across platforms

