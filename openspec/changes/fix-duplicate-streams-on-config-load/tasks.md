## 1. Implementation
- [ ] 1.1 Normalize required stream entries to canonical `name (hostname)` during load
- [ ] 1.2 In `refreshStreams`, skip adding missing-required entry if a matching resolved `StreamItem` exists
- [ ] 1.3 Ensure `save_config` writes required streams as canonical list names
- [ ] 1.4 Add basic manual test plan in README or developer notes

## 2. Validation
- [ ] 2.1 Load config with required streams while they are online → no duplicates
- [ ] 2.2 Load same config with streams offline → single red entries only
- [ ] 2.3 Save and reload config after discovery refresh → still no duplicates

