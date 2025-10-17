## Context
We need a consistent, minimal‑complexity process to produce runnable, platform‑specific binaries and ensure the application icon is applied everywhere. The project already uses CMake and Qt; deployment differs by OS.

## Goals / Non-Goals
- Goals: repeatable builds via CMake presets, simple deploy steps, consistent icon application, concise documentation
- Non‑Goals: code signing/notarization, advanced packaging ecosystems, changing the app’s runtime behavior

## Decisions
- Use CMake presets to unify invocation across OSes
- Use Qt deployment tools (windeployqt/macdeployqt) or install rules where appropriate
- Use existing assets: `res/app.ico`, `res/app.icns`, `res/app.rc`

## Risks / Trade-offs
- Packaging depth vs simplicity: we’ll default to deploy/copy steps first, CPack optional

## Migration Plan
1) Land CMake/icon changes behind non‑breaking defaults
2) Update `BUILD.md` and verify on each OS
3) Optionally add CI build jobs

## Open Questions
- Should Linux use a `.desktop` entry installed by `make install`, or only documented in `BUILD.md`?
- Do we want CPack archives by default, or keep it optional?


