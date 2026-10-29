# TH20 reconstruction — current handoff

**Current: 2026-10-29, after CORE/EXACT-512.** This is a live navigation
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
| Source-present mappings | **1,177** |
| Strict canonical complete native units | **1,178** |
| Unique canonical MSVC object/receipt providers | **238** |
| Exact game-authored whole original functions | **452**, covering **153,901 original body bytes** |

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

**CORE/EXACT-508 ABI correction:** InputInf at `+0x2E30` owns two
**signed process-view indices, not InputButtonState pointers**. Three
original Player/controller callers independently use its 26B getter result
as a signed index into the distinct process pointer array at `0x005B889C`.
The getter remains 26/26 exact with its corrected integer return signature;
**33 header-dependent C++ objects / 89 strict units** were cold rebuilt
and replayed without a full-graph run. See the [three-caller proof](INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md).

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

## Newly admitted complete game-owned Player-frame leafs

**CORE/EXACT-510:** Four existing whole native strict game leafs with
original physical heads `0x00449430` (45B handle-word equality),
`0x0041CAD0` (17B Context effect manager), `0x0045D100` (38B effect
animation file) and `0x00478080` (20B EnemyController count) are now
independently original-PE/caller origin-reviewed. They add **four
game-authored exact original bodies / 120 nonoverlapping bytes**. The
full original Player main-frame calls every one of them; both actual
canonical C++ provider objects were freshly rebuilt and **20/20** strict
units passed. The Player main frame is still **NONEXACT**. Two other
original main-frame calls to physical `0x0040BDA0` are now proven to
share the same exact 14B body as typed PlayerValues primary/secondary
`begin()` compilers; this is **not** additional physical byte credit.
The original 45B equality and typed 45B inequality helpers are distinct
physical code, so their parent call-target mismatch remains open.
See [full leaf origin, PE calls, binary fold and precise replay proof](PLAYER_FRAME_LEAF_120_EXACT_RECONSTRUCTION.md).

## Ten whole interpolation gameplay routines — independent native exact

**CORE/EXACT-511:** Ten existing whole game interpolation bodies,
**8,571 disjoint original bytes / 2,421 original instructions**, now
independently PE-verified, freshly source-provider rebuilt and authored-origin
admitted. This is a **source-origin admission**, not a claim of writing
ten new C++ functions. Largest original roots include **1,489B
IntegerTriple, 1,129B Vector3, 1,074B Fog, 1,022B Vector2 and 923B
Angle**; additional full float/int/byte sample and evaluate bodies are
included. Actual original E8 callers include previously exact Animation,
Enemy, ECL Runtime, Bullet and identifiable Wonder Stone game scene code.
All **117 native E8** and **90 PE HIGHLOW** fields plus all original
nonrelocated bytes were independently reaudited. The one real
`src/Interpolation.cpp` compiler source was cold built; **41/41 strict
units replayed exact**. Four original user roots are unclassified, so
those particular bodies retain medium-confidence authored origin.
[Full independent whole-PE/caller evidence](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md).
The previous 1,177 strict units, 237 compiler object providers and
1,177 source-present functions remain unchanged. No parent exactness,
folded-helper double credit, game runtime or full cold replay claim.

## Closed whole Bullet command-11 boss — 1,404B strict native exact

**CORE/EXACT-512:** Entire original `0x00481200` Bullet command-11
four-corner edge-ray state machine, **1,404 original bytes / 357 x86
instructions**, is now a fresh strict canonical **1,404/1,404 exact**
whole-function unit. Recovered two authentic original 384.0f/448.0f
stack-local initializations at original `+0x105..+0x11E` instead of
mistaking them for artificial padding. All original **33 E8 call sites
and 35 PE HIGHLOW absolute fields** were independently read from the
locked original; every original target and remaining byte agrees with
the pinned real MSVC source. The previously unresolved `polar2` symbol
is now defined as an actual typed Vector2 helper whose complete **89B
original code is physically folded with the already strict Vector3
polar** at `0x00439330`, with no duplicate original credit. Only
`src/BulletCommand11.cpp` and `src/MotionMath.cpp` were cold built:
**12/12 entire native units strict exact**, two real objects. [Complete
original source, folded ABI and immutable PE relocation proof](BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md).
The distinct **12,140B Bullet controller dispatcher and 3,735B Bullet
emitter remain NONEXACT**. New canonical count is **1,178 units / 238
object providers**. No full cold replay, link or runtime claim.

## Actual open whole-function bosses (priority, NOT exact)

| Native address / original bytes | Known C++ / exact frontier | Immediate next investigation |
| --- | --- | --- |
| `0x004FFA10` **555B** Player movement | `src/PlayerMovement.cpp` emits **561B / 136 instructions** against 555B/135; [original movement frontier](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md) | Recover one extra SSE y-bound float spill through real source lifetime/ABI, not artificial locals. |
| `0x004F9C30` **3,111B** Player main frame | [Full typed source](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md) now compiles **3,235B / 807 instructions / 67 REL32**, versus native 3,111B/783/67 E8/37 HIGHLOW. [Original 783-head audit](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md) | Enclosing boss remains **NONEXACT**, no exact credit. Resolve original full source control-flow and 35/37 absolute-reference mismatch; its separate 555B movement callee remains NONEXACT. |
| `0x0047DB70` **273B** Bullet group drawing | `src/BulletDrawGroup.cpp` emits 283B/84 vs 273B/82; [typed original drawing ABI](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md) | Two extra native SSE spills remain. Parent `draw_groups` 81B is already exact. |
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
