# TH20 reconstruction — live handoff for the next agent

**Reconciled 2026-10-30 (CORE/MAINT-896).** This is the **current-work**
entry point, not a chronological log. Start with [AGENTS.md](../AGENTS.md),
then this page, [the evidence index](EVIDENCE_INDEX.md), and the actual
[function ledgers](../config/matches.csv) and
[strict-unit manifest](../config/match-units.toml). Historical reports
preserve observations **at the time of the experiment**: their old
`SOURCE-ABSENT`, `NONEXACT`, object counts, and parent status labels do
not override current source, Git history, or a fresh canonical receipt.

## Locked target and verified progress

| Property | Current fact |
| --- | --- |
| Executable | Japanese TH20 v1.00a **Steamless**, `resources/th20.exe` (1,858,560 bytes) |
| Immutable SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Embedded title/replay version | **1.00c in the same v1.00a target**, not a replacement executable |
| Provisional Ghidra function inventory | **6,928**, not all native-confirmed function boundaries |
| Source-present function mappings | **1,344** (authored game **plus** compiler/library and unaccepted sources) |
| Whole-native strict units | **1,343**, from **313** pinned MSVC object/receipt providers |
| Credited original authored-game whole exact | **645 distinct function heads /235,772 original `.text` bytes** |
| Whole game builds/links/plays | **No** |

The exact authored totals come from `config/matches.csv`, not the sum
of source-present methods, aliases, `.rdata`, library implementations or
unaccepted parent candidates. **Never infer an exact parent from its
exact children.** The above numbers are a dated snapshot: query the live
inventory before any new source admission:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Active large original functions — next native work

The addresses and original sizes below are independently original-PE
scoped; candidate size is noted separately. **None of these parents
is whole strict exact.** Read the linked original proof before trusting
older local-variable names or assumptions.

| Priority / head | Current frontier and concrete next action |
| --- | --- |
| **Bullet extended command `0x0047DCF0`, 12,140B /2,490 x86** | **SOURCE-ABSENT.** Original 210 E8 calls: 208 have exact game-callee sources, two are compiler-runtime helpers; original three 34/8/11 pointer switches and 38 in-body HIGHLOW. Recover all switch cases as one genuine parent before strict replay. [Original native CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md), [call verifier](../scripts/verify-bullet-command-call-coverage.py). |
| **Enemy ECL opcode dispatcher `0x0048C010`, 41,967B /8,896 x86** | **SOURCE-ABSENT.** Original 174 PE switch fields and large opcode CFG need a complete parent source; exact Laser children do not close it. [Original graph](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md). |
| **Animation VM update `0x0042B5D0`, 39,470B** | **SOURCE-ABSENT.** Parser and helper leaves already exist; interpreter parent remains unresolved. [Source map](SOURCE_MAP.md). |
| **Animation 49-mode Draw `0x00443880`, 5,993B /1,501 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationDrawBoss.cpp`. Current candidate has original *length, mnemonic count and `0x204` frame* but **not identical code bytes**: 86/123 true E8 site/targets, 23/32 in-body HIGHLOW sites/targets. First mode35/36 inherited-scale x87 spill and later operand/stack slots remain wrong. Full 49+31 direct tables and exact backend children do not imply parent exact. [Current frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md), [focused role verifier](../scripts/verify-animation-draw-boss-source-roles.py). |

| **Polygon outline caller `0x0045FAA0`, 104B /36 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationPolygonMotionCall104.cpp` (102B /34 x86); original saves ESI and computes a stride before `Motion::position_ref`, whereas source computes it afterward. Eight source indexing variants did **not** fix it. Its 233B caller and 1,204B callee **are exact**, independently. [Caller frontier](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md). |
| **Rotated four-corner projection `0x0043EF20`, 1,486B /372 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationCornerRotated1486.cpp` (1,485B /371 x86). One genuine original NOP follows the Angle constructor; in-memory alignment is diagnostic **only**. The shared **96B 2×3×4 `.rdata` table is exact**. Do not fake compiler padding. [Original proof](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md). |
| **Player main `0x004F9C30`, 3,111B /783 x86** | **SOURCE-PRESENT, NONEXACT**, candidate 3,114B/783 x86; real register/stack/branch differences despite instruction-count agreement. [Operand frontier](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md). |
| **Player movement `0x004FFA10`, 555B** | **SOURCE-PRESENT, NONEXACT**; maintained candidate 561B/136 x86 vs original 555B/135; alternate 559B experiments affected stack layout and were **not** accepted. [Original evidence](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **Bullet group drawing `0x0047DB70`, 273B** | **SOURCE-PRESENT, NONEXACT**; original SSE expression/spill layout is unresolved. [Frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md). |
| **Enemy mesh `0x004A4190`, 1,649B** | **SOURCE-PRESENT, NONEXACT**; temporary/retirement lifetimes differ. [Source evidence](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **STL counted range `0x0047A8D0`, 470B** | **LIBRARY, NONEXACT**, not authored game code. Missing native `std::is_constant_evaluated` call is a toolchain/STL issue; do not invent a game instruction. [Library evidence](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md). |

### High-value directions

1. The **5,993B Animation Draw dispatcher** still has unresolved x87
   return spill and SSE/stack lifetimes despite its whole-exact backends.
   Fix genuine source expressions and verify all 123 E8/32 HIGHLOW original
   call/data roles, not just equal function length.
2. The **104B polygon outline wrapper** still has incorrect saved-ESI
   lifetime around the 8-byte point stride and `Motion::position_ref`.
   Its enclosing 233B and sibling 827B/1,204B Bosses are now whole exact.
3. The **12,140B Bullet extended command** is still source absent. Its
   original three native switch tables and almost entirely known exact
   callees make a genuine full-parent reconstruction worthwhile.
4. The **41,967B Enemy ECL dispatcher** and **39,470B Animation VM update**
   remain major source-absent Bosses; do not mistake exact children for
   accepted parent coverage.

## Recently confirmed whole-native exact — do not undo

The detailed original PE calls, body boundaries, true HIGHLOW data
roles, compiler flags and historical attempts are linked in the
[evidence index](EVIDENCE_INDEX.md). The live [authored exact ledger](../config/matches.csv)
and [canonical units](../config/match-units.toml) are authoritative.

| Original head / subsystem | Whole strict status |
| --- | --- |
| Ribbon original radius/vertex end helpers `0x0045DCA0` / `0x0045DCC0` | **19B/19B whole native exact**, true 60 float/60 Vector2 array ends. Confirmed two genuine E8 edges from now exact 538B updater. Authorship still unknown; no game-code credit. [Complete original and strict proofs](ANIMATION_RIBBON_ARRAY_END_HELPERS_19_STRICT_EXACT.md). |
| Ribbon three-segment array ctor `0x0045E670` | **78B/27-i386 plus five genuine `INT3` whole strict exact**, real 3×0x3C0 C++20 array, independent EH-vector callback to 60B ctor. Compiler/STL attribution unknown, no new authored-game credit. [83B full proof](ANIMATION_RIBBON_SEGMENT_ARRAY_CTOR_78_STRICT_EXACT.md). |
| Ribbon 60B segment constructor `0x0045D610` | **60B/20-i386 whole native exact**, real 60 Vector2/60 `AnimationHandle` word arrays, 60-float zeroing and actual original 78B parent callback; **+60 game authored bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_CTOR_60_STRICT_EXACT.md). |
| Ribbon segment dynamics Boss `0x0045E800` | **538B/149-i386 whole strict exact**, actual 60 radii/60 Vector2 loop, signed RNG, clamp +/-4, polar step 2*pi/59, authentic scope NOP and vertex 59 closure. Independently **13 E8/10 HIGHLOW** original physical roles. **+538 authored game bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md). |
| Ribbon segment LINESTRIP wrapper `0x0045EAC0` | **76B/27-i386 whole native exact**, genuine `+0x1E0` color stream, 60-point primitive, all three original E8/one HIGHLOW roles and original 156B parent E8 confirmed. **+76 authored game bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md). |
| Ribbon/polygon virtual draw Boss `0x0045EA20` | **156B/53-i386 whole native strict exact**, seven real E8/two HIGHLOW, three original 0x3C0 segments and genuine native scope NOP. **+156 authored game bytes**. [Complete native proof](ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md). |
| Separate ribbon/polygon update Boss `0x0045E770` | **140B /46-i386 whole native exact**, independent 0x56EDDC vtable, real 3x0x3C0 segments, six physical E8 and Timer +0xB4C; **+140 newly credited authored game bytes**. Its 19B array end remains strict exact and origin unproven; 538B update child and 156B draw were subsequently whole-exact at later checkpoints. [Complete native proof](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md). |
| Original polygon group construction Boss | **113B/30-i386 whole native strict exact**, genuine `AnimationCallback` base/vtable, 78B segment array, Timer/Vector3. **49B compiler scalar-deleting wrapper also strict exact**; its separate 20B ordinary destructor remains NONEXACT. [113B/49B proof](ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md). |
| Original polygon three-segment array ctor | Original **78B +5B INT3** C++20 `std::array<Segment,3>` complete **83/83 strict exact**, with 60B child and original 75B color-cell array ctor preserved; 113B parent is separate and NONEXACT. [Native proof](ANIMATION_POLYGON_SEGMENT_ARRAY_78_STRICT_EXACT.md). |
| Polygon native C++20 range closure | **27 additional whole strict exact C++20 STL-like helpers /811 original physical bytes**, spanning `std::array`, ref-view, iterators and shared `std::min`. **No authored game credit**; all origins remain review. [27-body proof](ANIMATION_POLYGON_DROP_CLOSURE_27_STRICT_EXACT.md). |
| `0x0045F0A0` group allocation factory | **156B /46-i386 whole-native strict exact**, C++17 diagnostic allocator + true 0xBAC pointer-bearing class auto-zero, forward and constructor call; unknown library-template origin. [Complete proof](ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md). |
| `0x0045F3C0` polygon segment ctor | **60B /20-i386 whole strict exact** from natural 61-vertex and 61-word array construction plus 62-radius value initialization, and independent **75B/80B with real INT3** array wrapper (origin review). The **113B polymorphic group ctor, 78B array ctor and 75B vector ctor remain open**. [60B source proof](ANIMATION_POLYGON_SEGMENT_CONSTRUCTION_60_75_NATIVE_EXACT.md), [group ABI frontier](ANIMATION_POLYGON_GROUP_CTOR_113_ARRAY_78_FRONTIER.md). |
| `0x0045F670` polygon dynamics update | **827B /237-i386 whole strict exact**, all **31 E8 and ten HIGHLOW** physical sites/targets; both original C++20 `drop(1)` arrays, 62/61 bounds, float clamp and closing point. [Complete original proof](ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md). |
| `0x0053B5C0` ECL runtime tick | **11,110B** [exact](EXACT_ECL_TICK_RECONSTRUCTION.md) |
| `0x004818E0` Bullet emitter | **3,735B original body** and **3,832B compiler contribution** [exact](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md) |
| `0x0043F6A0` Animation quad submission | **3,159B body /3,180B with original NOP+table** [exact](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md); genuine adjacent **20B `round(float)` is library**, [not authored game credit](ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md) |
| Animation renderer backends | **4,347B Mode8**, **2,769B Mode6**, **1,378B Mode6 setup**, **1,996B Mode7 setup**, **753B Mode7**, and **2,136B mesh24/25** independently exact. [Mode8](ANIMATION_DRAW_MODE8_4347_STRICT_EXACT.md), [Mode6](ANIMATION_DRAW_MODE6_2769_STRICT_EXACT.md), [setup](ANIMATION_DRAW_MODE6_SETUP_1378_STRICT_EXACT.md), [Mode7](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md). Only enclosing 5,993B Draw is open. |
| Polygon shape and Motion group chain | **1,204B** outline Boss, **827B** dynamics Boss, **296B** group configuration, **233B** group draw, **140B** group tick, **120B** palette, **76B** fan caller and **47B** registry wrapper all individually whole exact. [Polygon proof](ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md), [group](ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md), [tick](ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md), [palette](ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md). The **104B wrapper remains NONEXACT**; the 156B original group allocation factory is now **whole exact**, with library/template authorship unresolved. [Factory proof](ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md). [827B proof](ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md). |
| Shape draw backend catalog | **2,169B LINESTRIP, 1,980B rectangle, 1,601B triangle, 1,468B ring**, plus several whole exact **375B–1,174B ellipse/fan/strip** sources. [Closed line](ANIMATION_SHAPE_LINESTRIP_2169_STRICT_EXACT.md), [shape ring](ANIMATION_SHAPE_RING_1468_STRICT_EXACT.md), [remaining original PE proofs](EVIDENCE_INDEX.md). |
| Exact original game data | **96B corner axes**, **8B polygon scalar constants**, **72B Player direction table** are genuine `.rdata` data, **not additional authored `.text` code credit**. [Corner data](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md), [polygon data](ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md), [Player table](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |

The 538B ribbon updater also has **two separately exact 19B array-end leaves**
with true 60-element radii and vertices; original attribution remains unknown.
[Native helper proofs](ANIMATION_RIBBON_ARRAY_END_HELPERS_19_STRICT_EXACT.md).

The original **19B ribbon three-segment array-end pointer** `0x0045ECA0`
is whole **19/19 strict exact**, independently called by the now exact 140B
update and 156B draw. Its original STL/compiler authorship remains
review-pending. [Physical E8 + canonical evidence](POLYGON_SLOT_B40_ACCESSOR_19_STRICT_EXACT.md).

The original **42B nested forwarding/ref-slot constructor** at `0x0045ECC0` is
whole strict exact under a single C++17 provider, with two true folded-helper
E8 relocations; original STL/template authorship remains unknown.
[Original and canonical native proof](CXX_FORWARD_REF_SLOT_42_STRICT_EXACT.md).

Original-sourced **23B/19B native array helpers**, **31B/31B tag
forwarders**, **seven 19B–32B counted-range helpers**, **four 16B/93B
drop-view helpers**, and **27 more 17B–48B range closure helpers** are
independently strict exact but may be STL/compiler instantiations. Their provenance
stays `unknown/review`; **do not add them to authored game totals** without
proof. Likewise the genuine 20B standard-header `round(float)` wrapper
is `library/exclude`.

Original ribbon **75B/75B position/color array constructors, 89B group constructor, 156B allocation factory and 49B deleting wrapper** remain independent native reconstruction candidates; do not claim exactness of these parents from the accepted 60B child.

## Working discipline and scoped validation

- **Inspect the entire dirty worktree**: all edits and experiments belong
  to this operator. Save meaningful hypotheses and resolve drift; never
  silently reset user work. Use commit messages `gpt-web: ...` after
  substantial source/PE-backed progress.
- Original `.text` body and PE `.reloc` are independent evidence;
  source syntax, decompiler names, mnemonic-count alignment, E8 target
  *order*, or a patched/in-memory alignment test **do not imply exactness**.
  Strict acceptance requires a fresh pinned i386 MSVC canonical object,
  correct physical relocation site/target roles and **zero difference
  over the entire original function contribution**.
- For C++/header/profile changes, derive the actual affected source
  closure, cold-compile **only that source** at low priority, and replay
  only its selected units. **Never run unfiltered whole-graph cold
  replay.** Library/CRT and game-authored code credits remain separate.
- For **docs/comments that do not change native semantics and ignored
  artifact cleanup**, the native graph is unchanged: **zero cold
  replays**. Validate target hash, link paths, tracking, Git diff,
  protected canonical objects and receipts. Do not run Ghidra or MSVC
  just to update a dated paragraph.

```bash
# Examples only when source or its affected include closure has changed:
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_tick_140
scripts/repo-python scripts/build.py --check
scripts/repo-python scripts/progress.py --check
```

## Protected data and storage

Protect `resources/th20.exe`, its original backup/provenance, `_reference/`,
`ghidra-project/`, `.tools/` (pinned MSVC/Wine/D3DX), `.venv/`, Git history,
source, and historical original PE research/snapshot inputs in `.analysis/`.
Do **not** delete `build/` or `.analysis/` wholesale. The protected
canonical object/receipt set comes from the **live**
`config/match-units.toml`, not historical hardcoded 259/260/243 totals.
Current unfinished Boss probe directories are also protected.

For generated **noncanonical `build/*.obj` and `*.receipt.json` only**, use
[`scripts/prune-generated-artifacts.py`](../scripts/prune-generated-artifacts.py)
**dry run first**, inspect actual candidate directories, then explicitly
apply with a **new** private `.analysis/*.json` inventory. The cleaner
SHA-256-verifies the original target and every protected build file,
retains documented individual proof objects and current active Boss
probes, and leaves `.analysis` evidence untouched. The
[latest storage audit](MAINTENANCE_STORAGE_2026_10_30_CORE896.md) explains
what was retired; the [October 30 earlier audit](MAINTENANCE_STORAGE_2026_10_30.md)
is a *historical* snapshot with older canonical/game counts.
