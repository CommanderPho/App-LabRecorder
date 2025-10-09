## ADDED Requirements

### Requirement: Stream List Deduplication on Config Load
The system SHALL prevent duplicate stream entries in the UI when loading a configuration that contains streams which are already discovered.

#### Scenario: Config required stream already discovered
- **WHEN** a config is loaded that lists a required stream by `name (hostname)`
- **AND** a stream with the same identity is already present in `knownStreams`
- **THEN** the UI SHALL show a single entry for that stream
- **AND** the single entry SHALL be marked checked (required) if present in the config

#### Scenario: Config required stream not currently discovered
- **WHEN** a config is loaded with a required stream not present among discovered streams
- **THEN** the UI SHALL show a single red, checked entry for that required stream in the missing list
- **AND** the system SHALL watch for it during recording startup via a query derived from `name (hostname)`

#### Scenario: Saving and re-loading configuration
- **WHEN** the user saves configuration and later reloads it
- **THEN** streams SHALL retain deduplicated representation using the canonical `name (hostname)` format
- **AND** reloading SHALL not create duplicates even after discovery refreshes

## MODIFIED Requirements

### Requirement: Stream Selection Persistence
The system SHALL persist the set of required streams using the canonical list name (`name (hostname)`) and SHALL ignore adding a missing-required entry when a matching resolved entry already exists.

#### Scenario: Persist and rehydrate without duplicates
- **WHEN** the user saves settings containing required streams
- **AND** later loads them while the same streams are discovered
- **THEN** the UI SHALL show each stream only once, checked

