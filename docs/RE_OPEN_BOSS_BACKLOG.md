# TH20 — open native reconstruction Bosses and source frontiers

**Live backlog checked 2026-10-31.** This is a *working priority map*;
original native addresses/sizes and status are corroborated against
`config/functions.csv` and the original PE evidence named below.
For authoritative admission status, consult `config/match-units.toml`,
`config/matches.csv` and the [short handoff](RE_HANDOFF.md). A game
function is **not exact** merely because its caller or all children
are exact. Historical proof documents preserve their original
source/byte mismatches; some old status prose predates later commits.

## A. Major source-present, still NONEXACT game functions

| Original physical Boss | What is recovered; genuine next work |
| --- | --- |
| **Renderer primary and secondary animation-list updates** `0x00449870` **508B/152-i386**, `0x00449B20` **511B/153-i386** | Source: `src/AnimationRendererListUpdate508.cpp` and `511.cpp`. Both complete two-pass deferred retirement algorithms and native E8/HIGHLOW edges are known. Modern C++ `IntrusiveList<Animation>` emits **498B/501B**: one real **10B compiler `/sdl` preclear** is absent; a private `struct`→`class` tag test emits original sizes but alters shared ABI/decorations and many canonical units. Find genuine, *scoped* class initialization without blindly editing `src/IntrusiveLink.hpp` or falsely padding. [Whole original proof](ANIMATION_RENDERER_LIST_UPDATE_508_511_NATIVE_FRONTIER.md). Exact 150B/164B wrapper and 411B retirement callee do not make either loop exact. |
| **Animation main Draw** `0x00443880`, **5,993B/1,501-i386** | `src/AnimationDrawBoss.cpp`; native 123 E8/32 HIGHLOW. Whole candidate has real native length but wrong x87 inherited-scale spills and some register/stack roles; **not byte exact**. Repair actual mode35/36 expression/lifetime and verify every native role, not just size or exact mode backends. [Current frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md). |
| **Glyph mask compositor** `0x00416420`, **2,245B/612-i386** | `src/GlyphMaskComposite2245.cpp`; real BGRA32/ARGB4444 GDI mask, bitmap stride and PMR offset vector. Prior candidate around 2,061B/545 instructions, not accepted. Remaining original vector insertion/growth and MSVC allocation/ABI details; do not claim whole exact from exact pixel leaves. [Whole original and bitmap frontier](GLYPH_MASK_BOSS2245_LIVE_BITMAP_FRONTIER.md), [PMR insertion](GLYPH_MASK_EMPLACE35_NATIVE_FRONTIER.md). |
| **Glyph Unicode/GDI text core** `0x00415830`, **2,227B/470-i386** | `src/GlyphTextCore2227.cpp`; font metrics, glyph mask, queued task and Alpha producer/consumer typed. Native original 25 E8/43 HIGHLOW, modern candidate still shorter/different. The 542B canvas Alpha and many PMR/GDI children are already exact. [Core frontier](GLYPH_TEXT_CORE2227_TYPED_NATIVE_FRONTIER.md). |
| **Card spell-start Boss** `0x00487C30`, **1,896B/512-i386** | `src/CardStartSpell1896.cpp`; genuine spell metadata, animation, PMR display-string capture and exact 153B locked ASCII queue. Whole body/EH and generated std::function producer still differ. The 111B text callback, 602B finish and 1,522B HUD result are **independently exact**. [Native frontier](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md). |
| **Renderer ANM resource group decoder** `0x0044EBF0`, **336B/83-i386** | `src/AnimationFileGroupParse336.cpp`; real 0x28B group header with **BYTE flag +0x20**, global Renderer owner, CP932 diagnostics, external texture loader. Compiler emits 336B/83 and correct 6 E8/8 HIGHLOW, but **278/280 ordinary bytes**, two local-stack/frame byte differences. Do not invent an inert stack local. Its 1,022B loader and 269B preloader are whole exact. [Full proof](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md). |
| **ASCII text render and submit** `0x0044B020` **578B**, `0x0044FFF0` **294B** | `src/AsciiTextRender578.cpp` and `src/AsciiTextSubmit294.cpp`. Genuine variadic call/hidden result/std::function ownership reconstructed. 578B still has SSE/local-operand differences; 294B is only two original post-destructor compiler NOPs apart. **Both still NONEXACT**, while 93B/20B std::function copy/destructor and other children are independently strict exact. [578B native proof](ASCII_TEXT_RENDER578_NATIVE_FRONTIER.md), [294B frontier](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md). |
| **Renderer formatted-text callers** `0x0044AC20` **417B/114-i386**, `0x0044ADD0` **586B/140-i386** | **No accepted maintained source** for either head. A meaningful untracked 417B caller draft was intentionally preserved at `.analysis/gptweb-open-animation-formatted-text417.cpp` and private notes, SHA `17f9cd952e3a8849e09e1761c30264f14edb9ab6caca52284181e6f016a3d8dd`, with **418B/114** natural MSVC candidate and wrong byte flag `Animation+0x4A2` vs original **`+0x49A`**. Confirm true flag owner and variadic ABI before promoting from private hypothesis. The sibling 586B has real float text-width/length layout to investigate. Do not count either as source-present or exact yet. |
| **Player main/update** `0x004F9C30` **3,111B**, movement `0x004FFA10` **555B** | Source-present/NOT whole exact, historically unresolved input/position operands and movement prologue/SSE effects. [Frame proof](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [movement proof](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **200-particle virtual grid update** `0x0045C360`, **2,884B** | Private original analysis and whole candidate available, but still nonexact (older 2,953B/764-instruction probe). Original field `+0x15E8` is integer particle stage, not proven float; do not broaden shared owner changes without a scoped include-closure audit. [Native/full source probe](ANIMATION_PARTICLE_GRID_UPDATE_2884_TEMP_GHIDRA_AND_TYPED_FRONTIER.md). |
| **Enemy mesh lifetime** `0x004A4190`, **1,649B** | `src/EnemyMesh.cpp` has reconstructed behavior but is not whole strict exact. [Original work](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |

## B. Very large native dispatcher Bosses still source-absent

- **Bullet extended command** `0x0047DCF0`, **12,140B**. Original tables
  and some exact callees known; whole command dispatch not accepted.
  Keep the target's actual branch/table boundaries and check the
  [original command coverage verifier](../scripts/verify-bullet-command-call-coverage.py).
- **Enemy ECL opcode dispatcher** `0x0048C010`, **41,967B**. Distinguish
  original laser and scripting opcodes from shared helpers.
  [Native case graph](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md).
- **Animation VM update** `0x0042B5D0`, **39,470B**. Core animation
  execution/update remains source-absent; accepted per-mode renderer
  children do not prove this parent. [Architecture/source map](SOURCE_MAP.md).

## C. Smaller outstanding ABI and ownership frontiers

These should be addressed *alongside* major Bosses, not instead of them.

- The **104B polygon draw wrapper** has an original saved-ESI lifetime
  mismatch despite surrounding 233B/827B/1,204B exact parents.
  [Scoped proof](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md).
- **Three separate 75B Vector2 array constructors** retain a
  `struct`/`class`/`noexcept` and shared-header ABI issue; changing
  the global declaration affects a huge existing exact include closure.
  [Whole original evidence](ANIMATION_VECTOR2_ARRAY_60_64_61_NOEXCEPT_FRONTIER.md).
- **157B game filesystem path existence** has unresolved original STL
  constructor/move effects. [PE/typed frontier](GAME_FILE_EXISTS157_NATIVE_FRONTIER.md).
- **35B PMR glyph offset vector insertion**, 108B/488B growth and
  original 158B glyph task-node constructor differ under modern STL.
  Preserve genuine PMR allocator/ownership behavior.
  [35B](GLYPH_MASK_EMPLACE35_NATIVE_FRONTIER.md),
  [growth](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md),
  [158B node](GLYPH_QUEUE_NODE_CTOR158_NATIVE_FRONTIER.md).

## D. Recent large exact closures — do NOT rework as pending

- **Texture alpha-fringe finalizer `0x00451910`, 2,745B/759-i386:**
  [WHOLE STRICT EXACT](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md),
  *including* full `compare_size=2798` compiler contribution and its
  original **53B post-ret jump/mapping data** (data not credited as code).
  All 17 E8 and all 8 PE HIGHLOW in that comparison are verified.
- **D3D9 texture uploader** `0x0044E8F0`, **562B**; two D3D9
  surface-copy/effect Bosses **439B and 581B** — all strict exact.
  [Upload](ANIMATION_TEXTURE_UPLOAD562_STRICT_EXACT.md),
  [copy](ANIMATION_SURFACE_BLIT439_STRICT_EXACT.md),
  [effect](ANIMATION_SURFACE_EFFECT581_STRICT_EXACT.md).
- **AnimationFile resource loader** **1,022B**, **269B** preloader,
  **182B** find/wait and **40B** file table lookup — all original
  gameplay heads are whole exact.
  [Loader](ANIMATION_FILE_LOAD1022_STRICT_EXACT.md),
  [preload](ANIMATION_FILE_PRELOAD269_STRICT_EXACT.md),
  [find/wait](ANIMATION_FILE_FIND_OR_LOAD182_STRICT_EXACT.md),
  [lookup](ANIMATION_FILE_BY_INDEX40_STRICT_EXACT.md).
- **Four BGRA/ARGB texel helper heads** 139B/183B/183B/187B were
  already whole exact since REF-042. Their **692B** were subsequently
  *reclassified*, not newly matched, as custom game code with medium
  authorship confidence; do not count the same original bytes twice.
  [Provenance and native call graph](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md).

## Safe continuation contract

The canonical status source is the live CSV/TOML, not this dated list.
Use the original immutable target with hash checks and exact physical
E8/PE HIGHLOW proof before accepting an original body. Keep meaningful
C++ with correct owner, ABI, original branches, EH and return semantics;
no padding, asm, fabricated locals, shortened extent or false authored
credit. `git status` dirt belongs to the active agent and must be
resolved, not ignored. Commit stable source work with **`gpt-web:`**;
only replay source units actually touched, never a full cold replay.
For documentation/ignored-artifact-only cleanup there are **zero affected
native units** and no reason to rebuild MSVC objects.
