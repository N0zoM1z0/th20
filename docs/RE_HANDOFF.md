# TH20 reconstruction — current handoff

**Current: 2026-10-29, after CORE/EXACT-540.** This is a live navigation
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
| Source-present mappings | **1,181** |
| Strict canonical complete native units | **1,182** |
| Unique canonical MSVC object/receipt providers | **242** |
| Exact game-authored whole original functions | **476**, covering **168,855 original body bytes** |

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

## Newly maintained complete Bullet emitter source — whole nonexact boss

**CORE/RECON-514:** Original `0x004818E0` Bullet emitter is a real
**3,735-byte / 935-instruction** author-owned boss, called directly
from the already whole-exact **339B BulletController::fire** at
`0x00481839`. Its original **60 E8 calls**, 13+11 original switch
cases, 1Nop/96B tables, and eight CC alignment bytes were
independently rechecked from the immutable original. The previous
complete private C++ source has now been corrected and promoted to
**`src/BulletEmitter.cpp`** in the actual maintained tree, with real
`Bullet`, `ShotParameters`, `ShotMetadata` shared_ptr move, all 13
shot patterns and 11 cancel types, Animation, command and bullet
retirement logic. The original signed `rows > 1` speed-branch ordering
was restored, improving ordered opcode alignment from **787/935 to
792/935**. The pinned C++ builds a complete **3,516B/890-instruction**
method and 3,612B generated method/table contribution, versus original
3,735B/935 and 3,832B. It is emphatically **NONEXACT** with zero
new exact bytes and no accepted unit. The original 298B Animation
pool allocator ABI is now declared, but its source and final linked
runtime remain open. The header edit touched exactly **38 original
source providers / 91 strict units**; all were freshly cold built and
**91/91 native full units replayed exact**, including original 1,404B
command11 and 1,846B physics. One private compiler `$SG` label shift
was independently original PE/string-attested at `0x0056FD14` and
reconciled without changing its original relocation destination.
[Entire original function, compilation, ownership and scoped proof](BULLET_EMITTER_3735_MAINTAINED_SOURCE_FRONTIER.md).
Source-present mapping count rises to **1,178**, while game-authored
exact remains **452 / 153,901B** and canonical units/object providers
stay **1,178 / 238**. No unfiltered full replay.

## Newly exact direct Animation script loader and VM-forward wrapper

**CORE/EXACT-520:** Reconstructed the entire **338B / 93-instruction**
original direct `AnimationFile` VM script loader at `0x004383A0`
(**338/338 strict native bytes**) and distinct **21B / 9-instruction**
Renderer-owner VM forwarding wrapper at `0x00435500` (**21/21 exact**).
This fixes a true error in the maintained **3,735B Bullet emitter**:
its original E8 at `0x004822C5` calls the 338B *direct script loader*,
not the unrelated previously exact **32B** `bind_animation` wrapper at
`0x00438380` or the separate **194B** parent-binding method at
`0x004382B0`. The new loaded-script source preserves the original
atomic stage/boolean branch, 0x5E4-byte Animation zeroing,
original **two-stage mode bitfield mutation**, real Timer and callback
updates, three Renderer global loads and actual +0xB8 native script
counter. The 21B wrapper preserves the original integer return of
`Animation::update`, avoiding a spurious compiler NOP; the called
**39,470B Animation VM remains NONEXACT**. All **six original E8** and
**three original PE HIGHLOW** fields plus every original nonrelocated
byte are independently checked. New source/profiles are canonical
and fully replayed **2/2 strict exact**.

Frozen pre-edit public-header receipt closure: exactly **61 real
source providers / 266 previously exact original units**. All 61 were
cold rebuilt under their existing pinned profiles, and **266/266 full
original units replayed exact**. Twelve MSVC-private `$SG` label changes
were individually original-PE/site/full-string attested before
reconciling only the compiler-private names; no original targets
changed. [Complete 338+21 original-PE and scoped receipt proof](ANIMATION_DIRECT_SCRIPT_359_EXACT_RECONSTRUCTION.md).
Source-present/strict units increase to **1,180**, canonical source
object providers to **240**, authored original exact code to
**454 functions / 154,260 disjoint bytes**. The original Bullet emitter
3,735B and Animation VM 39,470B are *still whole NONEXACT* and do not
inherit their child's accepted bytes. No global cold replay, full
link or game-runtime claim.

## Newly solved entire Animation pool allocate/reuse boss — native 298B exact

**CORE/EXACT-525:** The full original `0x0044C9B0` native Animation
allocation and recycled-slot game owner, called directly from the
3,735B Bullet emitter at original `0x00482241`, is now a complete
**298/298 original bytes, 78 instructions strict canonical exact**
C++ source in `src/AnimationPoolAllocate.cpp`. Original **14 E8** and
**two PE HIGHLOW** fields independently match original native callee
and writable/debug global addresses, with **234/234** remaining
nonrelocated bytes identical. True Renderer free-list member
`+0x06000718`, `PooledAnimation` 0x600 stride, its free-link `+0x5E4`,
active bit `+0x5F8`, saved index `+0x5FC` and Animation index
`+0x4C4` are naturally typed; prior private source wrongly assigned
that index to the handle at `+0x4C0`. The original two free-list
`front()` calls and actual second-call result lifetime now reproduce
the native instructions. Specialized 17B `front()` plus genuine 16B
`node_value`, 55B `detach` and 61B `initialize` exact compiler
contributions are physically folded with prior native heads and
receive **zero extra authored byte credit**.

Only one new canonical source/object and **one complete 298B unit**
were added. The existing Renderer-owner declaration comment was
corrected after freezing its **14-source/30-unit** actual compiler
receipt closure; all 14 source objects were cold rebuilt and **30/30
strict original native units replayed exact**. No full cold replay.
[Original PE field-by-field, folded ABI and complete strict C++
evidence](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md).
New exact total **455 full game bodies / 154,558 disjoint original
bytes**, **1,181 source functions and strict canonical units / 241
compiled providers**. The distinct 73B Animation factory at
`0x00447800`, entire 3,735B Bullet emitter and 39,470B Animation VM
remain separate **NONEXACT** fronts.

## Ten independently origin-audited full Enemy and Motion gameplay bosses

**CORE/ORIGIN-529:** Ten existing complete Enemy, EnemyState and Motion
methods **416B–967B**, totaling **7,204 original nonoverlapping game
body bytes and 1,930 actual native instruction heads**, now have
independently original-PE-validated authored origins. Large whole methods
include **967B Enemy animation opcode dispatcher**, **844B multi-Motion
combiner**, **818B Enemy float variable destination**, **809B Motion
position update**, **780B Enemy spawn application**, **765B EnemyState
construction**, **694B velocity update** and **663B integer destination**.
Their native user call graph includes the real **41,967B original Enemy
ECL dispatcher** and separately whole-exact 1,675B Enemy movements.
The original immutable game has **247 E8 and 128 PE HIGHLOW fields**
across the complete original comparisons, all 375 independently
reconciled. The actual method code is 7,204B; **622 extra original
compiler switch/CC/table bytes** are fully compared in 7,826B strict
canonical contributions but **not credited as additional game bytes**.
Two negative-ID variable resolver roots have no discovered *incoming*
original direct E8 call and deliberately retain **medium authored
confidence**; the other eight have **high** original game-origin
confidence from direct game parent callers.

Exactly **six existing source/object providers** were freshly cold
built and **24/24 configured whole native strict units replayed exact**
using only those six source filters. These ten bodies already had
exact native source and canonical units: this checkpoint audits and
admits their **original game-authored ownership**; it does not invent
new C++ implementations. [Original whole-game E8/HIGHLOW, source and
scope evidence](ENEMY_MOTION_7204_EXACT_ORIGIN_AUDIT.md).
Current authored exact rises **455 / 154,558B -> 465 / 161,762B**.
Strict canonical units/source mappings stay **1,181**, real compiled
providers **241**. The 41,967B parent Enemy ECL dispatcher remains
independently **NONEXACT**; no whole cold replay or game-runtime claim.

## Ten newly original-origin-reviewed custom game object/codec/graphics bosses

**CORE/ORIGIN-535:** Independent original whole-PE/ABI review accepts
**ten existing native strict-exact custom game/project methods**, **6,057
original disjoint game-body bytes / 1,479 native x86 instructions**.
Largest whole roots: **941B Graphics::Graphics**, **794B Player
construction**, **712B PlayerRecord**, **706B LZSS decompressor**,
**612B ProgressMetadata**, **596B Item pool initialization**, **556B
Bullet construction**, plus Input replay 475B, PBG file open 346B and
Viewport 319B. Actual original game callers include the separately exact
ArchiveOwner read/catalog and Progress parser, Item controller,
progress snapshot constructor and Player/graphics constructor wrappers.
Original PE **106 native E8 / 17 genuine HIGHLOW** reference fields
and all other native code bytes were independently checked; **10
original compiler alignment bytes** in the Graphics/Player constructor
comparisons were compared but excluded from authored-body byte totals.
Four roots have **high-confidence original game-owned** provenance; six
(anonymous constructor wrappers, virtual/indirect PBG, absent direct E8)
retain **medium confidence**. This is an **origin audit of existing
source**, not ten newly typed C++ bodies or proof of the full linker.

Only **nine real MSVC source/object providers** were cold rebuilt;
**119/119 source-scoped complete original canonical units replayed
strict exact**, without source/header edits or an unfiltered global
cold replay. [Entire original PE and caller audit](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md).
Authored exact **465 / 161,762B -> 475 / 167,819B**, strict units and
source-present functions remain **1,181**, compiler providers **241**.
The separate **73B Animation factory** was retested under real C++
value/placement construction and MSVC `/sdl` flags; it remains
**NONEXACT** and is not masked with an artificial constructor ABI.
The full Bullet emitter, Enemy ECL dispatcher and Player/Animation
whole-frame bosses remain open.

## Newly exact entire 1,036-byte Archive LZSS compressor boss

**CORE/EXACT-540:** The entire original game-authored Archive compressor
`0x00539550..0x0053995B`, **1,036 native bytes / 315 original x86
instructions**, is now maintained as a **strict 1,036/1,036 original
exact** canonical C++20 unit. The old 964B/293-instruction hypothesis
omitted the actual original sum initialized at stack `[EBP-0x1C]` and
persistently read/add/written during **all seven complete encoded-byte
flush sites**. The original /Od genuinely retains that local although
its eventual consumer is still unknown. Restoring **one genuine init +
seven genuine three-instruction update chains** reproduces the native
whole extent; correcting the commutative match-bit expression to
original `weight & match` fixes the last **two original stack operand
displacement bytes**. This is a real native accumulator and original
expression-evaluation order, not artificial padding, source-fake
checksum output, assembly or shortened prefix.

The independently immutable PE whole-body audit covers **all six
original E8 direct calls and six original PE HIGHLOW fields**, every
native call/data target including the original LzssUtil label and
8192-byte dictionary, plus **988/988 remaining native bytes**.
Only `src/ArchiveLzssEncode.cpp` changed, no public/shared headers
or old canonical objects; the one new whole source unit was cold
compiled, with **1/1 strict native replay exact**. The existing
**706B whole original LZSS decoder**, ArchiveOwner and Progress
save-file semantics are untouched.
[Whole original 315-instruction source, seven sum chains, PE field
and canonical proof](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md).
Authored exact moves to **476 functions / 168,855 disjoint native
bytes**, canonical strict units **1,182**, unique compiler providers
**242**; source-present mappings stay **1,181**. The original
SaveManager load/write/save/whole archive runtime remains open.
No unfiltered whole-repository cold replay or linked game claim.

## Actual open whole-function bosses (priority, NOT exact)

| Native address / original bytes | Known C++ / exact frontier | Immediate next investigation |
| --- | --- | --- |
| `0x004FFA10` **555B** Player movement | `src/PlayerMovement.cpp` emits **561B / 136 instructions** against 555B/135; [original movement frontier](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md) | Recover one extra SSE y-bound float spill through real source lifetime/ABI, not artificial locals. |
| `0x004F9C30` **3,111B** Player main frame | [Full typed source](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md) now compiles **3,235B / 807 instructions / 67 REL32**, versus native 3,111B/783/67 E8/37 HIGHLOW. [Original 783-head audit](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md) | Enclosing boss remains **NONEXACT**, no exact credit. Resolve original full source control-flow and 35/37 absolute-reference mismatch; its separate 555B movement callee remains NONEXACT. |
| `0x0047DB70` **273B** Bullet group drawing | `src/BulletDrawGroup.cpp` emits 283B/84 vs 273B/82; [typed original drawing ABI](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md) | Two extra native SSE spills remain. Parent `draw_groups` 81B is already exact. |
| `0x004818E0` **3,735B** Bullet emitter | [Complete maintained real-owner C++20](BULLET_EMITTER_3735_MAINTAINED_SOURCE_FRONTIER.md) now emits 3,516B / 890 instructions / 792 aligned mnemonic kinds, against original 3,735B/935. Emitter original `0x00482241` now calls exact 298B native Animation pool allocation, and `0x004822C5` calls exact 338B direct script loader (rather than distinct old 32B wrapper); genuine 13/11 original table cases and 3,832B original compiler contribution separately attested | Whole parent **NONEXACT**: finish historical 63B shared_ptr move-assignment ABI and original native 60 E8 vs candidate call/branch lifetimes and switch target positions; do not credit until entire exact original replay. |
| `0x004A4190` **1,649B** Enemy mesh update | `src/EnemyMesh.cpp` previous native probe 1,548B; [lifetime frontier](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) | Recover complete radius/byte conversion, original clamp and register flow. |
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
