## 1. Implementation
- [ ] 1.1 Add `%hostname` expansion in `replaceFilename(...)` with filename-safe sanitization
- [ ] 1.2 Update `doc/templates.md` to document `%hostname` with examples
- [ ] 1.3 Verify preview reflects `%hostname` in UI and CLI where applicable
- [ ] 1.4 Add manual/automated validation steps for `%hostname` expansion
- [ ] 1.5 Validate OpenSpec change with `openspec validate add-hostname-filename-token --strict`

## 2. Validation
- [ ] 2.1 Confirm `%hostname` works in both legacy and BIDS templates
- [ ] 2.2 Confirm cross-platform filename safety (Windows/macOS/Linux)
