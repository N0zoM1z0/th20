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
| Source-present function mappings | **1,297** (authored game **plus** compiler/library and unaccepted sources) |
| Whole-native strict units | **1,295**, from **299** pinned MSVC objects and **299** matching receipts |
| Credited original authored-game whole exact | **637 distinct function heads /233,802 original `.text` bytes** |
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
| **Polygon dynamics `0x0045F670`, 827B /237 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationPolygonDynamics827.cpp` (513B /137 x86 candidate). Original **31 E8 /10 HIGHLOW**, two counted-range loops, GameRandom radius clamp, 59-step polar geometry. **Seven directly related 19B–32B iterator helpers are strict exact**, but true range-construction/zip/sentinel code and bounds are still missing. [Original full native/semantic frontier](ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md). |
| **Polygon outline caller `0x0045FAA0`, 104B /36 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationPolygonMotionCall104.cpp` (102B /34 x86); original saves ESI and computes a stride before `Motion::position_ref`, whereas source computes it afterward. Eight source indexing variants did **not** fix it. Its 233B caller and 1,204B callee **are exact**, independently. [Caller frontier](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md). |
| **Rotated four-corner projection `0x0043EF20`, 1,486B /372 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationCornerRotated1486.cpp` (1,485B /371 x86). One genuine original NOP follows the Angle constructor; in-memory alignment is diagnostic **only**. The shared **96B 2×3×4 `.rdata` table is exact**. Do not fake compiler padding. [Original proof](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md). |
| **Player main `0x004F9C30`, 3,111B /783 x86** | **SOURCE-PRESENT, NONEXACT**, candidate 3,114B/783 x86; real register/stack/branch differences despite instruction-count agreement. [Operand frontier](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md). |
| **Player movement `0x004FFA10`, 555B** | **SOURCE-PRESENT, NONEXACT**; maintained candidate 561B/136 x86 vs original 555B/135; alternate 559B experiments affected stack layout and were **not** accepted. [Original evidence](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **Bullet group drawing `0x0047DB70`, 273B** | **SOURCE-PRESENT, NONEXACT**; original SSE expression/spill layout is unresolved. [Frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md). |
| **Enemy mesh `0x004A4190`, 1,649B** | **SOURCE-PRESENT, NONEXACT**; temporary/retirement lifetimes differ. [Source evidence](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **STL counted range `0x0047A8D0`, 470B** | **LIBRARY, NONEXACT**, not authored game code. Missing native `std::is_constant_evaluated` call is a toolchain/STL issue; do not invent a game instruction. [Library evidence](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md). |

### High-value directions

1. For the **827B polygon dynamics Boss**, the first five native
   range helpers and their two pointer steppers already compile strict
   exact. Reconstruct the remaining original C++ range factories,
   counted end iterators, comparison and true loop bounds; preserve
   native COMISS/NaN semantics. Its original **140B group tick caller
   is already whole exact**, including a separate four-byte INT3 gap.
2. For the **104B polygon wrapper**, recover the original pointer
   stride's register lifetime by real source expression/ABI evidence;
   changing signatures solely to manufacture instructions is invalid.
3. For the **5,993B Animation Draw parent**, the actual missing x87
   return spill and later SSE/local stack roles are more useful than
   re-opening its already exact 1,378B/1,996B/2,769B/4,347B children.
4. The larger **12,140B Bullet** and **41,967B Enemy ECL** parents
   remain real source-absent bosses; do not spend an entire session
   matching only unrelated tiny leaves.

## Recently confirmed whole-native exact — do not undo

The detailed original PE calls, body boundaries, true HIGHLOW data
roles, compiler flags and historical attempts are linked in the
[evidence index](EVIDENCE_INDEX.md). The live [authored exact ledger](../config/matches.csv)
and [canonical units](../config/match-units.toml) are authoritative.

| Original head / subsystem | Whole strict status |
| --- | --- |
| `0x0053B5C0` ECL runtime tick | **11,110B** [exact](EXACT_ECL_TICK_RECONSTRUCTION.md) |
| `0x004818E0` Bullet emitter | **3,735B original body** and **3,832B compiler contribution** [exact](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md) |
| `0x0043F6A0` Animation quad submission | **3,159B body /3,180B with original NOP+table** [exact](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md); genuine adjacent **20B `round(float)` is library**, [not authored game credit](ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md) |
| Animation renderer backends | **4,347B Mode8**, **2,769B Mode6**, **1,378B Mode6 setup**, **1,996B Mode7 setup**, **753B Mode7**, and **2,136B mesh24/25** independently exact. [Mode8](ANIMATION_DRAW_MODE8_4347_STRICT_EXACT.md), [Mode6](ANIMATION_DRAW_MODE6_2769_STRICT_EXACT.md), [setup](ANIMATION_DRAW_MODE6_SETUP_1378_STRICT_EXACT.md), [Mode7](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md). Only enclosing 5,993B Draw is open. |
| Polygon shape and Motion group chain | **1,204B** outline Boss, **296B** group configuration, **233B** group draw, **140B** group tick, **120B** palette, **76B** fan caller and **47B** registry wrapper all individually whole exact. [Polygon proof](ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md), [group](ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md), [tick](ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md), [palette](ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md). The 827B update, 104B wrapper and 156B registry resolver are **not exact**. |
| Shape draw backend catalog | **2,169B LINESTRIP, 1,980B rectangle, 1,601B triangle, 1,468B ring**, plus several whole exact **375B–1,174B ellipse/fan/strip** sources. [Closed line](ANIMATION_SHAPE_LINESTRIP_2169_STRICT_EXACT.md), [shape ring](ANIMATION_SHAPE_RING_1468_STRICT_EXACT.md), [remaining original PE proofs](EVIDENCE_INDEX.md). |
| Exact original game data | **96B corner axes**, **8B polygon scalar constants**, **72B Player direction table** are genuine `.rdata` data, **not additional authored `.text` code credit**. [Corner data](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md), [polygon data](ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md), [Player table](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |

Original-sourced **23B/19B native array helpers**, **31B/31B tag
forwarders** and **seven 19B–32B counted-range helpers** are independently
strict exact but may be STL/compiler instantiations. Their provenance
stays `unknown/review`; **do not add them to authored game totals** without
proof. Likewise the genuine 20B standard-header `round(float)` wrapper
is `library/exclude`.

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
