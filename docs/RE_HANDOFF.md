# TH20 reconstruction — current agent handoff

**Reconciled 2026-10-30, CORE/RECON-840.** Start here, then consult the
[evidence index](EVIDENCE_INDEX.md) for dated native experiments and original
PE proofs. The old 813-line handoff is in Git history at
git show 3e0f343:docs/RE_HANDOFF.md. **Historical checkpoint numbers and old
NONEXACT labels are not current acceptance facts.**

## Locked original target and accepted native coverage

| Verified item | Current state |
| --- | --- |
| Original PE | Japanese TH20 v1.00a **Steamless**, resources/th20.exe, 1,858,560 bytes |
| Required SHA-256 | a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897 |
| Embedded title/replay label | 1.00c in that **same** locked file, not a separate target |
| Provisional Ghidra function heads | **6,928**, not all native-confirmed boundaries |
| Source-present mapped methods | **1,243** across game, compiler and STL/library |
| Complete native strict units | **1,244**, supplied by **263** distinct canonical MSVC objects with **263** matching receipts |
| **Original authored-game whole-function exact** | **597 distinct physical game functions /199,566 original .text bytes** |
| Whole game linked/playable | **No** |

Get live status with:
scripts/repo-python scripts/report-reconstruction-status.py --summary

The origin ledger, provisional function inventory, full-native match manifest
and credited authored ledger are different facts. Exactly one physical
original function body may be counted once, even if distinct C++ template or
member aliases produce the same bytes. STL/compiler code remains excluded
from authored game-code totals. Progress percentages are **not** percentages
of the entire game binary.

## Already complete exact original bosses — do not reopen on old notes

| Original physical function | Whole-native strict proof |
| --- | --- |
| 0x0053B5C0 ECL runtime tick | **11,110B** exact, [ECL runtime](EXACT_ECL_TICK_RECONSTRUCTION.md) |
| 0x004818E0 Bullet emitter | **3,735B** original, **3,832B** whole compiler extent exact, [emitter proof](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x00481200 Bullet command-11 | **1,404B** exact, [state machine](BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md) |
| 0x00421B00 InputDevice polling | **3,490B** exact, [input source](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md) |
| 0x0043F6A0 Animation quad-submit renderer Boss | **3,159B /763 x86** whole original game body strict exact; **3,180/3,180B** including genuine NOP and five native relocated case-table pointers, 41 E8 plus 101 DIR32 independent roles, [full parent proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md) |
| 0x00539550 LZSS compressor | **1,036B** exact (historical 964B attempt was NONEXACT), [native compressor](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md) |
| 0x00447800 Animation factory | **73B** exact with coherent class tag and SDL ABI, [native allocation proof](ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x0044C9B0 Animation pool allocation | **298B** exact, [pool allocator](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) |
| 0x0044CD00 Animation pool handle resolver | **456B /141 x86** whole strict exact, plus [159B/154B exact linked-list predicate and wrapper](ANIMATION_LINK_FIND_159_154_EXACT_RECONSTRUCTION.md), [original SprtID identity and 20 E8 proof](ANIMATION_POOL_RESOLVER_456_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x00441430 Animation mode7 preparation Boss | **1,996B/459 x86 whole-native strict exact**, complete original matrix setup/rotation/viewport-position/quad bound routine, native 11 E8 and 26 original PE HIGHLOW physical targets; [independent native and whole canonical proof](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md). Same receiver as strict 753B mode7 caller; both source/relocation contracts freshly replayed. |
| 0x00441430 Animation draw mode7 setup / matrix + corners Boss | **1,996B/459 i386 full original game-authored strict exact**, all original 11 E8 and 26 HIGHLOW physical sites, actual 3×64B matrix copies, D3DX XYZ rotations/multiplications, original parent/window translation and four Vector3 corners. [Full original PE/native strict proof](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md). Already strict 753B caller remains 753/753 after real int-return ABI symbol correction. |
| 0x00441C00 Animation draw mode7 fog/projection Boss | **753B /178 x86 whole-native strict exact**, 7 actual E8 calls +29 in-body HIGHLOW original sites, true D3DX four-corner transform, native 25B depth/math and exact 3,159B quad-submit; [complete original/COFF proof](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md). Main 5,993B parent stays NONEXACT. |
| 0x00445700 /0x00445720 Animation vector depth /squared-depth | **25B+70B =95B original game-authored strict exact**, real x87/SSE Vector3 math; native mode6/7 original callers and two genuine E8 targets independently PE-attested. [Full original/canonical proof](ANIMATION_DEPTH_MATH_25_70_STRICT_EXACT.md). The 753B mode7 caller remains source-absent/NONEXACT. |
| 0x00437930 /0x004379A0 /0x004379C0 Animation gameplay value getters | **3 ×17B =51B original game-authored strict exact**; original full nine-instruction thiscall FLD and 12 native E8 game-caller sites; previously strict but origin unreviewed, [independent authorship proof](ANIMATION_VALUE_GETTERS_51_AUTHORED_ORIGIN.md) |
| Other completed original methods | [Geometry](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md), [Interpolation](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md), [game owner constructors](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md), [Laser lifetimes](LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md), [ECL argument/ScriptStack](ECL_ARGUMENT_TAGGED_STACK_2073_ORIGINAL_GAME_EXACT_ORIGIN.md); historical group sums are not additional current byte credit. |

The [complete 3,159B quad submission Boss](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md)
is still whole strict exact. Its genuine `0x00445B80` callee has now been
independently identified as the C++ `round(float)` standard-header overload:
[20B/9-x86 library exact](ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md),
forwarding to native `_roundf` at `0x00550060`. The pinned shared
`/fp:strict` compilation naturally emits both from
`src/AnimationQuadSubmit.cpp`: **3,180/3,180B parent +20/20B library**, one
canonical source object and **two scoped units**. The 20B library wrapper
is excluded from **590 original authored game functions /196,671B**; it
adds a source-present mapping and strict unit, not game byte credit.

**11,110B ECL runtime and 41,967B Enemy ECL opcode dispatcher are
different functions.** The 3,735B Bullet emitter is already whole exact,
although the 12,140B Bullet command parent which it calls remains NONEXACT.

## Unfinished large original functions — active source and next evidence

**All sizes and instruction counts below refer to the locked original unless
explicitly marked as candidate output.** The status is per *parent function*;
strict-exact children cannot be counted as matched parent bytes. Historical
compiler sizes, source-absence labels and batch totals in linked dated reports
are not current. Verify each claim against the original PE and live ledgers.

| Priority / original head | Current parent state and immediate next work |
| --- | --- |
| **1. Bullet extended-command Boss `0x0047DCF0` — 12,140B /2,490 x86** | **SOURCE-ABSENT, NONEXACT.** Original 210 E8 occurrences: **208** have whole-native-exact game-callee source; remaining **two are compiler runtime** (`__security_check_cookie`, `__allshl`), not game-function gaps. Original 34+8+11 switch pointers (53 PE HIGHLOW) and 38 body HIGHLOW. Next: author the **complete 34/8/11-switch command parent**, verify each native case and its source, then match full x86/relocations. [Immutable original CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md), [current native 210-call verifier](../scripts/verify-bullet-command-call-coverage.py), [exact recursive Animation children](ANIMATION_RETIRE_SUBTREE_362_EXACT_RECONSTRUCTION.md). |
| **2. Animation 49-mode draw Boss `0x00443880` — 5,993B /1,501 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationDrawBoss.cpp`. The current pinned C++ source naturally emits **exactly 5,993B/1,501 x86** with original **`0x204` stack frame**, identical **3B after-body alignment**, and original **49+31 direct pointer table positions** (6,316B total COFF). **All 123 native E8 target roles in exact original order**; first 81 sites consecutive, **86/123 physical E8 site-and-target pairs exact**, **32/32 original PE in-body HIGHLOW target counts with 23/32 physical site+target matches**. Provisional 3,819/5,376 nonrelocation byte match is **NOT full exact**. Original mode35/36, 29/30 and 46 color/count/half-height/aux-scale observable evaluation order restored through meaningful used locals; private inert x87 spill experiment rejected. Native **first mode35 inherited-scale return spill** and late nested SSE/relocation operands remain different. Next: establish actual x87 result ownership, align remaining nine PE HIGHLOW sites and 37 E8 offsets, then canonical zero-difference acceptance only. [Current native-length/stack frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md); [exact 753B mode7 child](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md); [strict 1,996B mode7 setup child](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md), [complete 49+31 table and 18-backend ABI proof](ANIMATION_DRAW_BOSS_5993_NATIVE_80_TABLE_ABI_FRONTIER.md), [focused original PE/source verifier](../scripts/verify-animation-draw-boss-source-roles.py). One isolated NONEXACT object only, zero exact-provider replay; no game exact credit. |
| **3. Player main `0x004F9C30` — 3,111B /783 x86** | **SOURCE-PRESENT, NONEXACT.** Source candidate **3,114B /783 x86**, 67 actual call roles and 37 frame-data references; differences persist in register/stack/branch encoding despite matching mnemonic count. Next: expression and receiver lifetime. [Full operand evidence](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [independent 72B input data table](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |
| **4. Player movement `0x004FFA10` — 555B** | **SOURCE-PRESENT, NONEXACT.** Candidate **561B /136 x86** vs original **555B /135**; one excess 6B SSE lifetime spill remains. [Native movement source evidence](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **5. Bullet group drawing `0x0047DB70` — 273B** | **SOURCE-PRESENT, NONEXACT.** Candidate approximately **283B /84 x86** vs original **273B /82**, extra SSE expression spill. [Full source frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md). |
| **6. Enemy ECL opcode dispatcher `0x0048C010` — 41,967B /8,896 x86** | **SOURCE-ABSENT, NONEXACT.** Original opcode base 300, 704B compressed mode index, 174 actual PE HIGHLOW case pointers. Next: complete parent opcode source/CFG; separate exact Laser children do not close it. [Original native opcode graph](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md). |
| **7. Animation VM update `0x0042B5D0` — 39,470B** | **SOURCE-ABSENT, NONEXACT.** Native child script parsers and Animation helpers are exact, but whole interpreter source and codegen are not. [Source ownership](SOURCE_MAP.md). |
| **8. Enemy mesh `0x004A4190` — 1,649B** | **SOURCE-PRESENT, NONEXACT.** Coherent C++ exists, but original temporary/retirement lifetime codegen differs. [Native mesh frontier](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **9. STL counted-range `0x0047A8D0` — 470B** | **LIBRARY, NONEXACT (not authored game credit).** Real original **470B /174 x86 /12 E8** vs modern C++17 **458B /170 x86 /11 E8**; real missing `std::is_constant_evaluated` call is a toolchain/STL issue. Do not fabricate a game call. [Library proof](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md). |

The **3,159B quad submission parent is now entire whole-native strict exact**,
not merely source-present with exact children. Its natural 20B `std::round(float)`
callee is independently strict exact but library-excluded. The 5,993B Animation draw
parent calling it remains separate and NONEXACT. See the
[complete renderer parent proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md).

Completed Bullet library support includes **610B PMR vector functions**
([proof](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md)) and **100B
shared_ptr moves** ([proof](BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md)),
correctly **excluded from authored game credit**. Seven game-authored
Bullet interpolation tangent/mode/reset methods add **199B strict**
([original whole-native and 114-object closure](BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md)).
Exact children never imply exact big parents.

## Native acceptance, scope and proof discipline

- Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md), [build
  matching](BUILD_MATCHING.md), [source map](SOURCE_MAP.md) and [evidence
  index](EVIDENCE_INDEX.md). Native original PE bytes / real E8 / .reloc
  HIGHLOW are the source of truth, not old Ghidra names or prose.
- Use natural shared C++ source, genuine type layout and real original
  compiler calling convention. No assembly, no padding, no deliberately
  inert register temporaries, no fake ABI wrappers, no binary/COFF patches.
- Strict whole native acceptance needs entire original byte extent,
  independently PE-attested relocated targets, real pinned i386 MSVC
  source and **zero-difference canonical replay**. Structural-exact
  diagnostics or aligned mnemonic counts alone are not acceptance.
- Inspect all dirty, staged and untracked files: **they are our work**.
  Preserve useful private hypotheses, repair actual compiler fallout,
  commit checkpoints with prefix **gpt-web:**.

### Targeted validation only — do NOT run whole-graph cold replay

For native source/header/manifest/profile changes, calculate the actual
affected provider closure **before** editing, then build/replay only its
sources/units at low priority. Example:

    git status --short --branch -uall
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/validate-tracking.py --require-target
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/Interpolation.cpp
    scripts/repo-python scripts/compare-coff-function.py --unit UNIT_NAME
    scripts/repo-python scripts/build.py --check
    scripts/repo-python scripts/progress.py --check

A previous real interpolation header edit affected **114 objects /542 old
whole strict units**, all separately replayed with 25 original-PE-proven
private compiler string symbol renames; that was a **historical change
closure**, not a reason to replay it again on an unchanged graph.

The latest `src/AnimationQuadSubmit.cpp` changes affect only its **one
canonical provider/two exact units** under `/fp:strict`: the original 3,159B
quad parent and 20B C++ library `round(float)` wrapper. No other canonical
source, header, profile or original target changed; no unfiltered replay.

For **documentation and ignored-cache cleanup only**, there are **zero
native compiler-input changes and zero cold replay units**. Check target
hash, protected original/canonical file hashes, Markdown links, the
actual live ledger, edited tooling's focused tests and git diff --check.

## Protected source, data and storage

Keep original resources/th20.exe, private provenance, _reference/, attested
ghidra-project/, installed MSVC/Wine/D3DX in .tools/, .venv/, source,
Git history, original PE native research and unique .analysis/*.json.gz
frozen snapshots. Do **not** delete build/ or .analysis/ as a whole.
All **260 protected canonical .obj plus 260 matching receipt files** are
taken from the **live** match-units.toml, not hardcoded old 243/236/212
counts.

For reproducible **noncanonical generated probes only**, run the guarded
dry-run-first cleanup tool and inspect its protected scope:

    scripts/repo-python scripts/prune-generated-artifacts.py
    # After auditing its actual candidate set:
    scripts/repo-python scripts/prune-generated-artifacts.py --apply --inventory .analysis/NEW-UNIQUE-AUDIT.json

The tool must retain all manifest objects, original native evidence,
active Player/Bullet/Mesh probes, file-specific documented evidence and
original PE hashes. See the [latest protected retirement audit](MAINTENANCE_STORAGE_2026_10_30.md),
[historical October 29 audit](MAINTENANCE_STORAGE_2026_10_29.md) and
[prior retirement guards](ARTIFACT_RETIREMENT_CORE628.md).
No cleanup demands MSVC/Ghidra or full replay. Do not push unless requested.
