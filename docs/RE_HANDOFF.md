# TH20 native reconstruction — current working handoff

**Reconciled 2026-10-31.** This is the short, current entry point for
the next agent, **not** the 100KB chronological checkpoint log.
Read [AGENTS.md](../AGENTS.md) first, then this page, the
[open Boss backlog](RE_OPEN_BOSS_BACKLOG.md), the
[native evidence index](EVIDENCE_INDEX.md), and the live
[game-authored exact ledger](../config/matches.csv) and
[strict unit graph](../config/match-units.toml). Earlier versions
of this handoff are preserved in Git history and dated detailed proofs;
old status labels are **historical observations**, not current facts.

## Locked target and current accepted coverage

| Property | Verified state at this checkpoint |
| --- | --- |
| Executable | `resources/th20.exe` — Japanese Steamless TH20 v1.00a, **1,858,560 bytes** |
| Immutable SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Embedded labels | Title/replay strings say **1.00c inside this same locked v1.00a file**; do not change targets based on the embedded label |
| Ghidra provisional candidates | **6,928** (not all physical function boundaries independently established) |
| Accepted source-tracked units | **1,578 whole strict units**; `functions.csv` has **1,595** nonempty source-file rows |
| Canonical build providers | **432 pinned MSVC object + receipt pairs**; all currently protected |
| Credited *game-authored* whole-native exact | **769 distinct original function heads /264,067 `.text` bytes** |
| Whole game compiles, links or plays | **No** — native matching and standalone source coverage are different milestones |

Those figures are a **dated snapshot**, not a counter to increment
manually. `config/matches.csv` counts only independently proven
original game-authored exact function heads, while
`config/match-units.toml` also accepts separate compiler/STL code
and compared native data boundaries. Recompute the current status:

```sh
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Important recent *whole exact* Bosses — do not reclassify as open

- Original D3D9 **alpha-fringe texture finalizer** `0x00451910`:
  **2,745B/759-i386 WHOLE STRICT EXACT**. Canonical native code
  covers **2,745/2,745** actual original machine-code bytes; the
  *complete* **2,798/2,798** COFF contribution also compares
  the real following **53B** alignment/jump/mapping tables and
  all **25** physical relocation roles (17 E8 +8 HIGHLOW).
  Only the 2,745B *code* is credited; the table is never counted as
  a second function. [Independent complete proof](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md).
- D3D9 texture upload **562B**, surface RECT copy **439B**, and
  random-color surface effect **581B** are **all separately exact**.
  [Uploader](ANIMATION_TEXTURE_UPLOAD562_STRICT_EXACT.md),
  [surface copy](ANIMATION_SURFACE_BLIT439_STRICT_EXACT.md),
  [surface effect](ANIMATION_SURFACE_EFFECT581_STRICT_EXACT.md).
- AnimationFile native loader **1,022B**, Renderer preload **269B**,
  find/wait **182B**, animation handle restart **118B** and
  file-table index **40B** are each independently exact.
  [Loader](ANIMATION_FILE_LOAD1022_STRICT_EXACT.md),
  [preload](ANIMATION_FILE_PRELOAD269_STRICT_EXACT.md),
  [find/wait](ANIMATION_FILE_FIND_OR_LOAD182_STRICT_EXACT.md),
  [handle restart](ANIMATION_HANDLE_REFRESH_118_29_STRICT_EXACT.md),
  [file table](ANIMATION_FILE_BY_INDEX40_STRICT_EXACT.md).
- Four original **139B/183B/183B/187B** texel alpha/RGB neighbor
  functions were *already exact* under historical REF-042.
  Their original game ownership was subsequently established at
  **medium confidence** by four physical E8 per format in the
  2,745B finalizer. The **692B attribution correction did NOT
  create new strict units**. [Original ancestry proof](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md).
- **InputDevice keyboard/DirectInput/XInput polling `0x00421B00`
  (3,490B/747-i386)** is also [WHOLE STRICT EXACT](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md),
  not source-present/NONEXACT as a few historical `InputState.hpp`
  and source comments once claimed. Canonical unit: `input_device_poll`.
- Other very large already accepted native bodies include **11,110B
  ECL tick**, **3,735B Bullet emitter**, **3,159B quad submit**,
  **4,347B Mode8 draw**, **2,769B Mode6 draw** and
  **827B polygon dynamics**. Do not rely on dated documents saying
  these exact functions are `SOURCE-ABSENT` or `NONEXACT`.
  [Complete proof catalog](EVIDENCE_INDEX.md).

## High-priority unfinished work

**Attack large Bosses and small callees together.** The detailed
[open-function backlog](RE_OPEN_BOSS_BACKLOG.md) records actual
source files, native extents, unresolved compiler/ABI issues and
links to original PE evidence. The immediate priorities are:

1. **508B/511B Renderer list-update Bosses:** real two-pass source
   is still 10B short because of an MSVC `/sdl` list initialization.
   The shared `IntrusiveList` class-tag experiment must be scoped;
   do *not* break hundreds of exact include consumers to gain one Boss.
2. **5,993B Animation Draw** (native x87/SSE/local-operand roles),
   **2,245B glyph mask compositor** (GDI bitmap/PMR growth),
   **2,227B Unicode glyph text core**, and **1,896B Card start**.
   These are all source-present but remain **NONEXACT**.
3. **336B ANM per-group parser**: now source-present, 336B/83 i386
   but **278/280 ordinary bytes**, with two outstanding stack/frame
   differences. Its 1,022B loader parent is already exact.
4. **417B/586B Renderer formatted-text callers**: neither has an
   accepted maintained source. A genuine unfinished **418B** C++
   candidate for original **417B `0x0044AC20`** was transferred
   from an untracked `src/` path into protected private notes
   `.analysis/gptweb-open-animation-formatted-text417.cpp`;
   investigate the real byte flag at `Animation+0x49A` versus
   provisional member at `+0x4A2` before promoting it.
5. Source-absent **12,140B Bullet command dispatcher**, **41,967B
   Enemy ECL opcode dispatcher** and **39,470B Animation VM**.
   Their independently exact descendants do not make these
   parents exact. The backlog also covers Player/particle/mesh
   frontiers and smaller exact-leaf opportunities.

## Workflow and verification boundary

- **Every** code/metadata change starts from the live `git status`;
  staged, dirty and untracked work belongs to the active agent.
  Preserve unfinished work under `.analysis/` with its SHA and
  reason if it cannot yet be admitted to maintained source.
- Read original PE SHA, whole native boundaries and physical
  E8/HIGHLOW **independently** before accepting source exactness.
  Keep actual ABI, C++ ownership, EH, vtable, COM and original
  data/code separation. No fake padding, copied machine bytes,
  assembly, inert locals, truncated function or duplicated game credit.
- For **native source, shared headers or exact-manifest changes**:
  identify actual affected providers and replay **only those sources**
  using `scripts/repo-python scripts/replay-exact-units.py --source
  src/Relevant.cpp`. Keep compiler work serialized at low priority;
  **never run an unfiltered full cold replay**.
- For **docs and regenerable-artifact cleanup with unchanged native
  graph**: **zero affected native units and zero cold replay**.
  Validate target hashes, Markdown relative links, tracking and
  `git diff --check` instead.
- Commit meaningful checkpoints promptly and make multiple commits
  when warranted, always **`gpt-web: ...`**. Maintain English source
  comments, docs and commit messages.

## Protected storage and last retirement

Protect `resources/th20.exe`, original game provenance, `_reference/`,
`ghidra-project/`, `.tools/` pinned MSVC/Wine/SDK, `.venv/`,
original-native `.analysis/` proof/snapshots and all current canonical
`.obj`/`.receipt.json`. Do not remove either `build/` or `.analysis/`
wholesale. [2026-10-31 guarded retirement](MAINTENANCE_STORAGE_2026_10_31.md)
removed **2,875 noncanonical compiler products, 127,712,939 bytes
(121.80 MiB)**, retaining every protected SHA. `build/` reduced
from ~228MB to ~100MB. The one-time private SHA audit is
`.analysis/gptweb-cleanup-2026-10-31-build-retirement.json`.
Future cleanup uses the existing guarded
[`scripts/prune-generated-artifacts.py`](../scripts/prune-generated-artifacts.py)
**dry-run first**, with a *new* private inventory on application.
The installed ~4.2GB toolchain and ~308MB retained native analysis
archives were **deliberately not deleted**.
