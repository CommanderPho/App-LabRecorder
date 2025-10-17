## Why
Users recording on shared or remote machines need the hostname encoded in filenames to disambiguate recordings and improve traceability. Current templates support participant/session/date/time but lack a hostname token.

## What Changes
- Add new filename template token `%hostname` that expands to the local machine hostname.
- Define safe expansion semantics (sanitize to filename-safe characters).
- Document `%hostname` in `doc/templates.md` and user-facing help.

## Impact
- Affected specs: `templates` capability (filename token expansion)
- Affected code: `src/mainwindow.cpp` (`replaceFilename(...)`), any shared templating utilities
- Affected docs: `doc/templates.md`, possibly `README.md` references


