# TH20 reconstruction — current handoff

**Current: 2026-10-29, after CORE/EXACT-507.** This is a live navigation
and risk summary, not a checkpoint transcript. Use the authoritative
`config/match-units.toml`, `config/functions.csv` and
`config/function-origins.csv` for current per-function status. The
previous **1,253-line handoff** is preserved without loss by Git at
`git show 9eed65c:docs/RE_HANDOFF.md`. Historical checkpoint details
remain in the [focused evidence index](EVIDENCE_INDEX.md); dated
historical NONEXACT claims there must not override later exact proofs.

## Target and current accepted original bytes

| Property | Current verified value |
| --- | --- |
| Locked original | Japanese TH20 v1.00a Steamless, ignored `resources/th20.exe` |
| Original length | 1,858,560 bytes |
| Original SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Provisional PE boundaries | 6,928 |
| Source-present mappings | **1,176** |
| Strict canonical complete native units | **1,177** |
| Unique canonical MSVC object/receipt providers | **237** |
| Exact game-authored whole original functions | **437**, covering **143,806 original body bytes** |

These are not whole-game linkage or runtime equivalence claims. The exact
unit count includes compiler-generated or library-support bodies that are
not separately credited as hand-authored game functions. Linker-folded
functions at one physical address receive **one** original-body credit.
Some complete compiler contributions include real PE `CC` alignment
bytes; compare them fully, but credit only actual original game-body
bytes. Original package v1.00a and embedded title/replay version
1.00c are both observed in the **same locked executable**.


## Newly origin-admitted complete collision geometry: strict native exact

**CORE/EXACT-503:** 19 original entire collision-geometry functions,
**13,360 distinct original game-body bytes / 3,530 instructions**,
including **1,452B rectangle/rectangle**, **1,439B line/rectangle**,
**1,250B rectangle/star** and **1,195B rectangle/polygon** bosses. Their
actual maintained C++ and manifest units were already present but earlier
authored-origin classification was pending, so prior records did not count
them. Fresh pinned `/fp:strict` MSVC builds of exactly two source objects
strictly replay **19/19 original units**, including **160 original E8** and
**181 original PE HIGHLOW** fields separately independently audited.
Original game-owned DamageRegion/Bullet/Player callers prove active custom
geometry roles; four currently anonymous caller roots remain medium-confidence
authored classifications. See the [origin and whole-PE exactness audit](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md).
Canonical unit/provider counts stay **1,177 / 237** because these preexisted.
No whole-repository cold replay, linked executable or game-runtime claim.

## Newly origin-reviewed Animation frame and VM helpers

**CORE/EXACT-507:** 17 complete Animation gameplay functions totaling
**5,527 original authored bytes**, including the 1,106B reset, 931B motion
update, 944B interpolation update and 835B float-value interpreter. The
original 39,470B Animation VM directly calls the integer and float evaluator
117 and 156 times respectively; the giant parent remains **NONEXACT**.
Three existing source providers were cold rebuilt and 50/50 affected strict
units replayed. Original code yielded 93 E8 calls and 140 PE HIGHLOW fields,
all independently verified. Existing canonical counts stay 1,177 units and
237 objects. [Full origin/whole-PE proof](ANIMATION_FRAME_5527_EXACT_ORIGIN_AUDIT.md).

## Recently solved input system — do not reopen as nonexact

| Original entry | Whole strict body | Source / decisive evidence |
| --- | ---: | --- |
| `0x00421B00` InputDevice whole keyboard/DirectInput/XInput poll | **3,490B**, 747 instructions | [Complete original PE 21 E8/18 HIGHLOW and strict fresh MSVC proof](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md); previous source frontier is superseded |
| `0x00420AA0` InputInf DirectInput discovery | **726B**, 209 instructions | [Windows COM creation, GUID, errors and enumeration](INPUT_INF_DIRECTINPUT_DISCOVERY_726_EXACT_RECONSTRUCTION.md) |
| `0x004219D0` InputDevice DirectInput pad registration | **218B**, 68 instructions | Same original 726B/218B PE proof |
| `0x00421830` InputInf DirectInput COM pointer slot | **17B** | Same proof; distinct physical address |
| `0x004210D0` InputInf XInput discovery | **170B**, 57 instructions | [Windows XINPUT_STATE and original import](INPUT_INF_XINPUT_DISCOVERY_170_EXACT_RECONSTRUCTION.md) |
| `0x00420D80` InputInf initialization and device routing | **465B**, 118 instructions | [Signed device count and actual Graphics configuration array](INPUT_INF_INITIALIZE_DEVICES_465_EXACT_RECONSTRUCTION.md) |
| `0x00420990` InputInf startup and bindings | **265B**, 75 instructions | [Native separate 16B binding copies](INPUT_INF_START_265_EXACT_RECONSTRUCTION.md) |
| `0x004202C0` and `0x004216E0` InputInf shutdown / COM release | **466B / 50B** | [Native lock and DirectInput lifecycle](INPUT_INF_SHUTDOWN_466_EXACT_RECONSTRUCTION.md) |
| `0x0041F8A0` InputInf constructor | **261B** + 5 real aligned CC | [RTTI, C-array devices and noexcept construction](INPUT_INF_CONSTRUCTOR_261_EXACT_RECONSTRUCTION.md) |
| `0x0041FD70` and `0x0041FE10` InputInf virtual destructor / MSVC delete glue | **120B** + 5 CC / **49B compiler support** | [Actual callback unregister and deleting wrapper](INPUT_INF_DESTRUCTOR_120_EXACT_RECONSTRUCTION.md) |
| `0x0041F9B0` and `0x0041FCB0` button/device constructors | **340B / 102B** | [Entire original nested-input construction](INPUT_DEVICE_BUTTON_CTORS_442_EXACT_RECONSTRUCTION.md) |
| `0x00454150` vs `0x00454230` normal append-only vs error-flag diagnostic | **215B new / 221B prior** | [True distinct log semantics and original six DirectInput call sites](DIAGNOSTIC_LOG_MESSAGE_215_EXACT_RECONSTRUCTION.md) |

Original input route/bindings/pad/view getters are also exact:
`0x00421990` (49B), `0x004217F0` (27B),
`0x00421850` and `0x00421870` (26B each),
and `0x00498FB0` (26B). The **real native class is
`InputInf`**, original RTTI `.?AVInputInf@@`, **not**
the earlier speculative partial `InputController`.
The actual manager has 12 × 0x3D4 InputDevice records, true
`IDirectInput8W*`/`IDirectInputDevice8W*` fields and
four 0x30-byte bindings. Some native getters/setters have
physically folded aliases: `0x0040C300`, `0x0041CAB0`,
`0x00421810` and `0x0041DE70` are **already** strict
units; do not create duplicate physical matches.

## Actual open whole-function bosses (priority, NOT exact)

| Native address / original bytes | Known C++ / exact frontier | Immediate next investigation |
| --- | --- | --- |
| `0x004FFA10` **555B** Player movement | `src/PlayerMovement.cpp` emits **561B / 136 instructions** against 555B/135; [original movement frontier](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md) | Recover one extra SSE y-bound float spill through real source lifetime/ABI, not artificial locals. |
| `0x004F9C30` **3,111B** Player main frame | [Whole original E8/HIGHLOW caller audit](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md) | Enclosing frame is NONEXACT despite most child calls being exact. Verify remaining E8 target and movement callee independently. |
| `0x0047DB70` **273B** Bullet group drawing | `src/BulletDrawGroup.cpp` emits 283B/84 vs 273B/82; [typed original drawing ABI](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md) | Two extra native SSE spills remain. Parent `draw_groups` 81B is already exact. |
| `0x00481200` **1,404B** Bullet command 11 | `src/BulletCommand11.cpp`; [whole boss C++ frontier](BULLET_COMMAND11_FULL_SOURCE_FRONTIER.md) | Four missing original instruction kinds; distinguish true state/lifetimes from compiler shaping. |
| `0x004818E0` **3,735B** Bullet emitter | Switch-table/CC comparison extends physical compiler contribution; [whole emitter frontier](BULLET_EMITTER_FULL_CXX_FRONTIER.md) | Actual STL move ownership, emitter arrays, native switch-table relocations. |
| `0x004A4190` **1,649B** Enemy mesh update | `src/EnemyMesh.cpp` previous native probe 1,548B; [lifetime frontier](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) | Recover complete radius/byte conversion, original clamp and register flow. |
| `0x00539550` **1,036B** Archive LZSS encoder | `src/ArchiveLzssEncode.cpp` previous private 964B probe; [historical encoder evidence](ARCHIVE_WRITE_RECONSTRUCTION.md) | Original byte-flush accumulation has unverified observable use; do not introduce dead scalar solely for matching. |
| `0x0047DCF0` **12,140B** Bullet controller dispatcher and `0x0048C010` **41,967B** Enemy ECL dispatcher | [Enemy dispatch layout](CORE_ENEMY_DISPATCH_LAYOUT.md) and [source map](SOURCE_MAP.md) | Major real gameplay ownership and complete control-flow work; historical host/sanitizer counts are **not** current native exactness. |
| `0x0042B5D0` **39,470B** Animation VM update | [Animation source map](SOURCE_MAP.md) | Separate large nonexact controller from already exact smaller Animation geometry and support routines. |

Additional completed whole large game bosses include the **13,684B**
ProgressProfile constructor, **5,388B** Animation geometry,
**4,154B** easing dispatcher, **2,433B** Enemy interpolation,
**1,675B** Enemy movement update
([large-body independent proof](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md)),
**1,518B** Player option rebuild
([proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md)),
and **1,081B** Player option frame
([proof](PLAYER_OPTION_FRAME_1081_EXACT_RECONSTRUCTION.md)).
Do **not** use historical “NONEXACT” descriptions of those
already closed functions as current status.

## Worktree, native verification and source closure

- This is a **single-worker repository**. Always inspect all staged,
  unstaged and untracked files; continue any dirty experiments instead
  of hiding, resetting or assigning them to another session.
- Commit meaningful verified work immediately using
  **`gpt-web: ...`**. Keep all source comments, documentation and
  commit subjects in English; respond to the user in Chinese.
- Every exact claim requires **entire original function / all genuine
  attached compiler bytes** as applicable, a locked MSVC object,
  fresh receipt and independently original-attested E8/HIGHLOW
  targets; `structural-exact` alone is only diagnostic.
- **Never run an unfiltered whole-repository cold replay.**
  Before editing a shared header, derive real affected sources
  from existing canonical `.receipt.json` include graphs.
  Cold replay only that source closure with serial
  `nice -n 15 scripts/repo-python scripts/replay-exact-units.py
  --source src/ChangedOwner.cpp`; source-specific compiler profiles
  are pinned in `config/match-units.toml` and may differ.
- When MSVC renumbers private `$SG` labels, first verify unchanged
  **immutable original PE** destination, field offset/type and all
  nonrelocated bytes, then change **only** compiler-private
  symbol spelling. Never infer a PE target from the candidate.
- For **documentation or ignored build-artifact cleanup only**,
  do not recompile an unchanged native source graph. Verify hashes,
  tracking, links and diffs. If a public-header comment changes
  its locked receipt input hash, cold replay **only its actual
  compiler-receipt source closure**.

Quick native preflight:

```sh
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
```

## Storage and historical traceability

**Protect:** `resources/th20.exe`, original user-provided
`../game_exe/`, `.tools/`, `ghidra-project/`, **all 236
manifest-referenced canonical MSVC objects and sibling
receipts**, original PE-native private proof files,
and private sources required by open whole bosses.
`.analysis/` contains historical scripts and explicitly
referenced compressed snapshots; do not assume age means
unused. Historical discarded compiler probes are
reproducible from retained private C++ sources.

For build-only retirement use the **default dry-run**
`scripts/repo-python scripts/prune-generated-artifacts.py`,
review its active-boss probe allowlist and apply only with
explicit `--apply`. Its private per-file SHA/size inventory and
hash-protected canonical checks are documented in the
[artifact retirement report](ARTIFACT_RETIREMENT_2026_10_29.md)
and the [workflow](RE_WORKFLOW.md).
**Never** run `git clean -fdx` or delete whole
`build/`, `.analysis/` or original/proprietary tools.
Prior storage cleanup is documented
[separately](ARTIFACT_RETIREMENT_2026_10_28.md).
