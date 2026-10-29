# TH20 reconstruction — current agent handoff

**Reconciled 2026-10-30, CORE/RECON-819.** Start here, then consult the
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
| Source-present mapped methods | **1,238** across game, compiler and STL/library |
| Complete native strict units | **1,238**, supplied by **259** distinct canonical MSVC objects with **259** matching receipts |
| **Original authored-game whole-function exact** | **589 distinct physical game functions /193,512 original .text bytes** |
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
| 0x00539550 LZSS compressor | **1,036B** exact (historical 964B attempt was NONEXACT), [native compressor](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md) |
| 0x00447800 Animation factory | **73B** exact with coherent class tag and SDL ABI, [native allocation proof](ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x0044C9B0 Animation pool allocation | **298B** exact, [pool allocator](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) |
| 0x0044CD00 Animation pool handle resolver | **456B /141 x86** whole strict exact, plus [159B/154B exact linked-list predicate and wrapper](ANIMATION_LINK_FIND_159_154_EXACT_RECONSTRUCTION.md), [original SprtID identity and 20 E8 proof](ANIMATION_POOL_RESOLVER_456_STRICT_EXACT_RECONSTRUCTION.md) |
| Other completed original methods | [Geometry](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md), [Interpolation](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md), [game owner constructors](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md), [Laser lifetimes](LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md), [ECL argument/ScriptStack](ECL_ARGUMENT_TAGGED_STACK_2073_ORIGINAL_GAME_EXACT_ORIGIN.md); historical group sums are not additional current byte credit. |

**11,110B ECL runtime and 41,967B Enemy ECL opcode dispatcher are
different functions.** The 3,735B Bullet emitter is already whole exact,
although the 12,140B Bullet command parent which it calls remains NONEXACT.

## Unfinished big functions and precise next moves

| Priority and immutable original head | Current evidence and next task |
| --- | --- |
| **1. Bullet command Boss 0x0047DCF0, 12,140B /2,490 x86** | **Parent source-absent and NONEXACT.** Full original 210 E8 call audit now verifies **208/210 original direct-call targets have complete native exact child source**. Both new batches added 4 whole original Animation flag/interrupt helpers (85B) plus whole **282B recursive Animation retire subtree**, **43B pool handle release** and **37B AnimationHandle retirement**, all **7/7** new methods exact (**447 game bytes**). Remaining **two** original E8 gaps are the compiler-runtime-only 14B `__security_check_cookie` and 31B `__allshl`, not missing game logic. Three original main/nested switch tables still have **34+8+11 pointers /53 original PE HIGHLOW** and 38 in-function HIGHLOW. **Main 34-case/8-case/11-case command dispatcher itself still must be reconstructed and matched.** [New recursive retire proof](ANIMATION_RETIRE_SUBTREE_362_EXACT_RECONSTRUCTION.md), [four helper proof](BULLET_COMMAND_ANIMATION_HELPERS_EXACT_RECONSTRUCTION.md), [whole native call/switch verifier](../scripts/verify-bullet-command-call-coverage.py). |
| **2. Animation draw Boss 0x00443880, 5,993B /1,501 x86** | **Entire 49-mode C++ parent is now SOURCE-PRESENT but NONEXACT.** Independently original-PE-verified **123 E8 /43 destinations**, **49 +31** original mode/nested HIGHLOW code pointers (**80** fields; 17+29 unique heads), plus **32 true in-body HIGHLOW**. Four earlier whole strict Animation helpers (**20+20+26+93 =159B**) are joined by three complete **92B D3D9 Graphics state/cache methods** (Fog enable/disable and Z-write disable, **276B**) from another single new source/object. Each Graphics body has real original PE HIGHLOW global `0x005C0028`, original E8 flush `0x004455C0` and D3D9 virtual `SetRenderState`. The **separate full 192B queued-draw flush at `0x004455C0` is now strict exact**, after recovering natural D3D9 function-pointer-before-argument evaluation: **192/192B, 55/55 x86, four independently attested original PE fields**, through one new canonical source/object. No old exact unit changed. [Full original-native 192B proof](ANIMATION_DRAW_QUEUE_FLUSH_192_STRICT_EXACT_RECONSTRUCTION.md). **Original full 49-mode x86 CFG and mode-selected E8 call paths have now been independently mapped**: 47 modes have a reachable action E8, using **43 distinct physical call sites /29 selected callees**, while modes 10/23 do not. Original main→nested routing occurs for **28 modes**; 24/25 bypass it. This is a maintained 49-row PE-backed manifest and does **not** make the 5,993B parent source-present or exact. Three genuine separate **97B /32-x86 quad-draw mode methods** for cases **0,1/3,2** are newly **3/3 strict exact (291B)**, with four original PE HIGHLOW pointers to a real 4x28B vertex array and two true original setup/submission E8 per function. Two additional native whole mode methods are now strict exact: **48B mode 4 guard** (original integer return and short branch) and **142B mode 5 quad result/perspective-W reset** (ten original relocations including four vertex member addends). All five mode functions pass **5/5** strictly in the same source/object, **+190B**. [Original mode4/mode5 full exact and addend proof](ANIMATION_DRAW_MODE4_48_MODE5_142_STRICT_EXACT.md). A new maintained [full 49-case typed C++ parent](ANIMATION_DRAW_BOSS_5993_TYPED_49_MODE_PARENT_FRONTIER.md) now compiles and covers **123/123 native E8 target roles with exactly correct per-callee counts across 43/43 original targets** and all **29/29 mode-specific render backends**, but it emits **5,141 real executable bytes/1,358 i386 vs original 5,993B/1,501**, plus 247B of compiler table/index data. Main switch lowering differs: compiler **17-pointer+49-index** vs original direct **49-pointer**. All 24 remaining backend implementations, physical operand ordering and the executable body still need exact reconstruction. Only the one existing five-function quad-source object was replayed 5/5 after a declaration-only local header extraction; no whole cold replay. [Original three 97B quad-mode exact proof](ANIMATION_DRAW_QUAD_THREE_97B_STRICT_EXACT.md). [Original whole 49-mode E8 CFG](ANIMATION_DRAW_BOSS_49_MODE_ORIGINAL_E8_CFG.md), [full Boss original and 159B exact children](ANIMATION_DRAW_BOSS_5993_NATIVE_DISPATCH_AND_EXACT_ACCESSORS.md), [three Graphics 276B strict proof](GRAPHICS_DRAW_RENDERSTATES_276_STRICT_EXACT_RECONSTRUCTION.md), [original PE verifier](../scripts/verify-animation-draw-boss-native.py). |
| **3. Renderer quad submit Boss 0x0043F6A0, 3,159B /763 x86** | **Entire typed C++ parent now SOURCE-PRESENT but NONEXACT.** Complete immutable original 41 E8/11 destination and 96 true PE HIGHLOW/10 destination census now independently proven; `0x00443F...` not an owner guess. Two custom game per-channel blend methods now whole strict exact **45B at 0x0043F520 (24 direct calls)** and **35B at 0x0043F4F0 (4 calls)**, plus previously exact 192B flush used twice. **Native exact new texture lookup at `0x00445A00`: 60B/21 x86** with actual `std::array<AnimationFile*,42>::at` 34B and its original 16B `_Xran` checked-library helper. The latter two strict original STL methods are LIBRARY-EXCLUDED; only the 60B game method adds game bytes. Original Ghidra guessed `_Xran` 13B but real original is 16B. [Original 60+34+16 exact proof](ANIMATION_TEXTURE_LOOKUP_60_STL_ARRAY_34_16_EXACT.md). The original native **352B/98-x86 six-vertex batch append** at `0x0043E9B0` and **26B/12-x86 texture-state forwarding wrapper** at `0x00445BA0` are also now separately whole strict exact **2/2, +378B**, with the genuine shared receiver and native E8 target at `0x00445BC0`. [Original 352B+26B strict code and array-index lifetime proof](ANIMATION_QUAD_BATCH_APPEND_352_AND_TEXTURE_PREPARE_26_EXACT.md). The original +0x005AEF10 28B vertex buffer and 0.5f snap math were attested. **Crucial full-Boss child now whole strict exact:** the separate **1,163B/343-x86 4-mode `select_render_color_mode` D3D9 state machine at 0x00446690** is **1,163/1,163 real code +17/17 original after-return NOP/4-way PE switch data** from one natural C++ body, with **54/54** true original 25 E8 +29 HIGHLOW. [Full exact 1163B state-machine proof](ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md). The maintained [whole 3,159B semantic C++ parent](ANIMATION_QUAD_RENDER_3159_TYPED_SOURCE_FRONTIER_AND_COLOR_80_EXACT.md) now compiles: typed four 28B vertices, `Graphics::current_viewport` at the genuine original +0xB00, actual SpriteData ID, DrawPrimitiveUP batching, original color-mode blend/UV pathways. Another distinct **2,725B/699-i386 ten-mode texture and sampler-state backend at `0x00445BC0` is now whole strict exact**, including original **50 native E8, 57 genuine PE HIGHLOW** and the original **3-byte alignment/40-byte ten-pointer switch table**, full **2,768/2,768** strict. Native local bitfield source and actual case 6 before case 5 order restored original code; only one new source/object replayed. [Complete original 2,725B proof](ANIMATION_QUAD_TEXTURE_STATES_2725_STRICT_EXACT.md). Its separate native **1,163B/343-i386 D3D9 quad blend state machine at `0x00446690` is now whole strict exact**, including all **25 native E8, 29 genuine PE HIGHLOW, plus four original PE jump-table target fields and one-byte alignment in a full 1,180B comparison**; one new source/object only. [Complete 1,163B original state-machine proof](ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md). **Current whole C++ candidate now contains 40/40 original GAME E8 call roles across all ten physical game targets**, including 24/24 saturation, 4/4 divide-255, 4/4 native snap and 1/1 six-vertex append; the original 41st E8 is compiler security cookie, not falsely inserted. **The genuine 60B custom texture lookup is now strict exact**, alongside the authentic 34B checked `std::array<AnimationFile*,42>::at` STL library unit (excluded from game authored counts), with one native lookup E8 at `0x00445A1E→0x0043EB10` and range error E8 at `0x0043EB1D→0x00428C80`. [Full exact original 60+34B proof](ANIMATION_TEXTURE_LOOKUP_60_AND_STL_ARRAY_34_STRICT.md). The C++ emits **3,796B/973 real x86 plus 20B compiled five-pointer table =3,816B COFF**, compared with original **3,159B/763 x86 and its own five PE HIGHLOW pointers**; code, relocations and compiler cookie still DIFFER. **Parent remains NONEXACT; no original bytes credited.** [40/40 game call-role evidence and remaining machine-code gap](ANIMATION_QUAD_RENDER_3159_40_GAME_E8_SOURCE_CLOSURE.md), [Current whole source/original call-role verifier](../scripts/verify-animation-quad-submit-source-roles.py). Next recover original channel evaluation order/stack lifetime, actual snap routine source and original 96-field relocation pattern. [Extended original PE viewport and five-pointer color-switch proof](../scripts/verify-animation-quad-submit-native.py). [3159B original census +80B exact proof](ANIMATION_RENDER_3159_COLOR_MATH_80_EXACT.md), [live PE verifier](../scripts/verify-animation-render-quad-native.py). |
| **4. Player main 0x004F9C30, 3,111B /783 x86** | Source present, **3,114B/783** under MSVC, 783/783 mnemonic order, 67 E8 /37 whole-frame data roles, **NONEXACT**. Seven differing ADD register encodings account for the **net +3B**, but other register/stack/branch fields remain different. Next: natural C++ temporary/receiver lifetimes. [Native operand proof](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [72B genuine 9x2 data table](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |
| **5. Player movement 0x004FFA10, 555B** | Source present, **561B/136 vs 555B/135**, one excess 6B SSE spill; **NONEXACT**. Two world-coordinate denominators already correctly refer to real native_128. Next: correct compiler SSE value lifetime, not fabricated register hints. [Original data and code frontier](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **6. Bullet draw group 0x0047DB70, 273B** | Source present, about **283B/84 vs273B/82**, excess SSE offset spill; **NONEXACT**. [Full method study](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md). |
| **7. Enemy ECL dispatcher 0x0048C010, 41,967B /8,896 x86** | **NONEXACT**. Integer opcode base 300, 704-byte compressed indices and 174 real PE HIGHLOW case pointers; genuine Laser opcode 702/703/711/713 object lifetimes proven. [Original opcode paths](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md). |
| **8. Animation VM update 0x0042B5D0, 39,470B** | **NONEXACT** despite exact parsers/loaders/interpolation children. [Source map](SOURCE_MAP.md). |
| **9. Enemy mesh 0x004A4190, 1,649B** | Natural C++ source present but **NONEXACT**, transient lifetime unresolved. [Mesh evidence](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **10. STL counted-range 0x0047A8D0, 470B** | **Library, NONEXACT**. Actual 470B/174 x86/12 E8 vs coherent pinned C++17 **458B/170/11**; native extra call to std::is_constant_evaluated at 0x0047A99F. Do not patch installed STL, fake the call, or mix conflicting C++17/C++20 COMDATs. [Real child proofs](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md). |

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

For **documentation and ignored-cache cleanup only**, there are **zero
native compiler-input changes and zero cold replay units**. Check target
hash, protected original/canonical file hashes, Markdown links, the
actual live ledger, edited tooling's focused tests and git diff --check.

## Protected source, data and storage

Keep original resources/th20.exe, private provenance, _reference/, attested
ghidra-project/, installed MSVC/Wine/D3DX in .tools/, .venv/, source,
Git history, original PE native research and unique .analysis/*.json.gz
frozen snapshots. Do **not** delete build/ or .analysis/ as a whole.
All **259 protected canonical .obj plus 259 matching receipt files** are
taken from the **live** match-units.toml, not hardcoded old 243/236/212
counts.

For reproducible **noncanonical generated probes only**, run the guarded
dry-run-first cleanup tool and inspect its protected scope:

    scripts/repo-python scripts/prune-generated-artifacts.py
    # After auditing its actual candidate set:
    scripts/repo-python scripts/prune-generated-artifacts.py --apply --inventory .analysis/NEW-UNIQUE-AUDIT.json

The tool must retain all manifest objects, original native evidence,
active Player/Bullet/Mesh probes, file-specific documented evidence and
original PE hashes. See [artifact cleanup record](MAINTENANCE_STORAGE_2026_10_29.md)
and [prior retirement guards](ARTIFACT_RETIREMENT_CORE628.md).
No cleanup demands MSVC/Ghidra or full replay. Do not push unless requested.
