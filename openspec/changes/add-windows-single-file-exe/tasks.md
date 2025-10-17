## 1. Implementation

- [ ] 1.1 Add a CMake option/preset `windows-single-file` to enable packaging
- [ ] 1.2 Script Windows deploy step (windeployqt) into a staging dir
- [ ] 1.3 Package staging dir into a single `.exe` (select packer; add script)
- [ ] 1.4 Ensure runtime extracts to a private cache dir and launches app
- [ ] 1.5 Include LICENSE and notices in the packaged artifact
- [ ] 1.6 Update `BUILD.md` with end-to-end instructions and validation steps
- [ ] 1.7 Smoke test on a clean Windows VM without Qt installed
- [ ] 1.8 (Optional) Produce CLI single-file exe variant
- [ ] 1.9 (Optional) Code sign and publish checksums

## 2. Validation

- [ ] 2.1 Verify the single-file `.exe` launches with no adjacent DLLs
- [ ] 2.2 Verify that multi-file build path is unchanged
- [ ] 2.3 Verify Qt plugins (platforms, styles, imageformats) load correctly
- [ ] 2.4 Verify `lsl.dll` availability within single-file flow
- [ ] 2.5 Verify licensing notices and source references are present


