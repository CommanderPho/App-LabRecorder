## Why
When loading a config that lists streams already discovered on the network, the UI can show duplicated entries because config-listed required streams are merged with discovered streams without a consistent identity check and deduplication.

## What Changes
- Define a canonical identity for streams used in the UI list (`name (hostname)`), and deduplicate entries when merging config-required streams with discovered streams.
- Ignore required entries that already correspond to resolved streams in `knownStreams` to prevent duplicate rows.
- Persist and load required streams using the same canonical list name format to ensure round-tripping without duplication.

## Impact
- Affected specs: `stream-selection`
- Affected code: `src/mainwindow.cpp` (`load_config`, `refreshStreams`, `save_config`), `src/mainwindow.h` (`StreamItem`, state sets)

