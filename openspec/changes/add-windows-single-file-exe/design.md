## Context
Windows builds currently ship as a directory containing the `.exe` plus Qt, LSL, and other runtime DLLs and plugin subfolders. Users want a single-file `.exe` for simpler distribution. Qt does not natively produce truly static single-file GUI apps in common setups; practical approaches involve embedding and extracting runtime files at launch.

## Goals / Non-Goals
- Goals: Provide an optional single-file `.exe` artifact that runs on a clean Windows system without sidecar DLLs. Keep the existing multi-file build.
- Non-Goals: Replace or remove the standard multi-file deployment; modify core app behavior.

## Decisions
- Decision: Prefer a wrapper-based pack-into-exe approach over attempting full static Qt, due to toolchain and licensing complexity. Keep it opt-in behind a CMake preset/flag.
- Alternatives considered: Full static Qt build; self-extracting archive with launcher; external installer packages. Chosen approach balances developer effort with user convenience.

## Risks / Trade-offs
- Startup overhead from extraction; increased exe size; antivirus false positives for self-extracting binaries. Mitigation: cache extraction under `%LOCALAPPDATA%`, sign binaries, publish hashes.
- Licensing obligations for Qt when bundling dynamic components. Mitigation: include notices and provide dynamic build path/source links.

## Migration Plan
1. Add packaging preset and script to create single-file `.exe` from the standard deployed tree.
2. Document usage in `BUILD.md` and artifact validation steps.
3. Optional: add code-signing and hash publication steps.

## Open Questions
- Preferred packaging tool (CMake + 7zip SFX, makesfx, or a maintained open-source packer)?
- Whether to produce both GUI and CLI single-file binaries or GUI-only initially?


