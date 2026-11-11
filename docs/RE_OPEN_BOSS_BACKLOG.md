# TH20 — open native reconstruction Bosses and source frontiers

**Live backlog checked 2026-11-11.** This is a *working priority map*;
original native addresses/sizes and status are corroborated against
`config/functions.csv` and the original PE evidence named below.
For authoritative admission status, consult `config/match-units.toml`,
`config/matches.csv` and the [short handoff](RE_HANDOFF.md). A game
function is **not exact** merely because its caller or all children
are exact. Historical proof documents preserve their original
source/byte mismatches; some old status prose predates later commits.

## A. Major source-present, still NONEXACT game functions

The former **508B/511B Renderer list-update pair is no longer open**:
[CORE/RECON-1110 whole native strict exact proof](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md)
recovered the original `/sdl` class-key preclear, with **82/82** prior
strict units preserved. Keep the original 40B list constructor and 42B reset
on their *separate* NONEXACT helper backlog; they were not credited here.
A [bounded 40B constructor double-tail probe](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md)
now reproduces all 40 original code bytes in length/16 i386 instructions,
34/36 ordinary bytes, original folded E8; two ModRM bytes and the reason
for the same-address duplicate tail write remain open and are **not**
canonically accepted.

| Original physical Boss | What is recovered; genuine next work |
| --- | --- |
| **Animation main Draw** `0x00443880`, **5,993B/1,501-i386** | `src/AnimationDrawBoss.cpp` now preserves the original full 6,316B code+switch-pointer contribution, `0x204` stack, **123 ordered real E8 target roles**, 32 body HIGHLOW role multiplicities and both 49+31 jump-table alias partitions. A used mode35 width value and ordered mode45 real color/count values improved **native E8 site equality 86/123 → 113/123**, body HIGHLOW site/target equality **23/32 → 26/32**, and unchanged whole 5,993B/1,501-i386 length; **4,801/5,376 ordinary bytes** agree. **NONEXACT:** unresolved original x87 first-scale spill and later SSE/mode45 local lifetimes, ten E8 sites and six body data locations. [Current whole-source convergence and proof](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md); [earlier native frame/table source frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md). |
| **Glyph mask compositor** `0x00416420`, **2,245B/612-i386** | Maintained `src/GlyphMaskComposite2245.cpp` now restores the genuine **RGBA4444 per-pixel live stride** at native `+0x5E7`, a mutable source-stencil pointer and signed multiply-before-divide neighbor addressing. Full current compiler candidate **2,141B/565 i386**, **all 37 E8 roles in original native order**, **nine stride E8**, five real body data roles and all four folded 22B array-index calls. The entire parent is still **NONEXACT**; only **2/37 physical E8 sites** align, and 104B/47 native instructions remain. Scoped source replay passed **24/24** existing exact PMR/color descendants. [Full native call-role frontier](GLYPH_MASK_BOSS2245_RGBA4444_SOURCE_STRIDE_37_CALLS.md), [prior row increment](GLYPH_MASK_BOSS2245_ROW_INCREMENT_FRONTIER.md). |
| **Glyph Unicode/GDI text core** `0x00415830`, **2,227B/470-i386** | Maintained `src/GlyphTextCore2227.cpp` reconstructs the 22 genuine font-switch pointers/17 alias groups, allocator/font/GDI color semantics, native completion pointer slot `+0x2C`, and a named glyph task alive until after queue submission. The 8B folded canvas-reference helper is exact as an existing library alias; original E8 `+0x7BC/+0x7E7` both align. Full current candidate **2,296B** versus original **2,316B** contribution; all 25 original call roles and 43 body data roles agree, with **17/25 E8 sites, 41/43 data sites, 1,626/1,936 ordinary bytes** aligned. Still **NONEXACT**, no parent credit. The 132B constructor/23B destructor stay exact (2/2 scoped replay); 294B submit remains its independently verified 292B frontier. [Current task/ABI proof](GLYPH_TEXT_CORE2227_QUEUE_TASK_ABI_FRONTIER.md), [earlier canvas/GDI source](GLYPH_TEXT_CORE2227_COLOR_AND_CANVAS_ABI_FRONTIER.md). |
| **Card spell-start Boss** `0x00487C30`, **1,896B/512-i386** | `src/CardStartSpell1896.cpp` now reproduces all **62/62 original E8 target roles** and **26/26 PE HIGHLOW data-target roles**, in native sequence: two real 20B renderer file getters, one 16B shared text getter, original `"text"` spawn, seven fresh script-table global loads, original boss-position branch order, and PMR display name destroyed after effect/script work. Whole current candidate **1,848B/490 i386**, still **NONEXACT** (zero new parent exact credit), while 128B PMR+7B callable and original 1,522B HUD+20B getter pass focused exact checks. [Current whole 62-call/26-data evidence](CARD_START1896_FULL_CALL_DATA_ROLES_FRONTIER.md), [prior text-task frontier](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md). |
| **Renderer ANM resource group decoder** `0x0044EBF0`, **336B/83-i386** | `src/AnimationFileGroupParse336.cpp`; real 0x28B group header with **BYTE flag +0x20**, global Renderer owner, CP932 diagnostics, external texture loader. Compiler emits 336B/83 and correct 6 E8/8 HIGHLOW, but **278/280 ordinary bytes**, two local-stack/frame byte differences. Do not invent an inert stack local. Its 1,022B loader and 269B preloader are whole exact. [Full proof](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md). |
| **ASCII text render and submit** `0x0044B020` **578B**, `0x0044FFF0` **294B** | `src/AsciiTextRender578.cpp` and `src/AsciiTextSubmit294.cpp`. Genuine variadic call/hidden result/std::function ownership reconstructed. 578B still has SSE/local-operand differences; 294B is only two original post-destructor compiler NOPs apart. **Both still NONEXACT**, while 93B/20B std::function copy/destructor and other children are independently strict exact. [578B native proof](ASCII_TEXT_RENDER578_NATIVE_FRONTIER.md), [294B frontier](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md). |
| **Centered Unicode Renderer text** `0x0044ADD0` **586B/140-i386** | Source now maintained in `src/AnimationRendererCenteredText586.cpp` under the same borrowed Renderer owner as the separately **417B WHOLE STRICT EXACT** Unicode formatted-text function. Native E8 (11) and HIGHLOW (9) sites were independently decoded. Pinned C++20 now yields **586B/140**, 10/11 native physical E8 positions and 399/506 ordinary bytes; four of nine original HIGHLOW positions agree. The full expression changes advance/strlen evaluation order, so SSE register lifetime and physical relocations still differ (**NONEXACT**). [Whole 586B frontier](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md); [417B accepted proof](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md). |
| **Player main/update** `0x004F9C30` **3,111B**, movement `0x004FFA10` **555B** | Source-present/NOT whole exact, historically unresolved input/position operands and movement prologue/SSE effects. [Frame proof](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [movement proof](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **200-particle virtual grid update** `0x0045C360`, **2,884B/768-i386** | The complete game method is **now SOURCE-PRESENT, NONEXACT** in `src/AnimationParticleGridUpdate2884.cpp`. All **99 native E8 call roles/25 HIGHLOW fields** were independently attested, and the prior false four file/palette calls were repaired to the genuine Session→Context→EffectInfo→AnimationFile→83B spawn pipeline; existing 26B owner, 83B spawn, 25B age and 19B color accessors are separately exact. The distinct **51B virtual Event** is also now [whole strict exact](ANIMATION_PARTICLE_GRID_EVENT51_AGGREGATE_TIMER_STRICT_EXACT.md), with a true aggregate Timer forwarding ABI; all eight dependent exact units survived a focused six-object rebuild. The natural original-sized caller is **not** yet matched: pinned C++20 emits **2,924B/760 i386**, with correct typed 200-element handle/stage arrays and Timer calls. The [ESI/polar convergence](ANIMATION_PARTICLE_GRID_UPDATE_2884_ESI_POLAR_LIFETIME_CONVERGENCE.md) restores original ESI lifetime, aligns six E8 sites and closes 45B of the former gap without losing any original call/data role; the remaining stack/SSE/argument ABI is still open. [Full source/native frontier](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md). |
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
- **35B PMR glyph offset vector insertion**, 108B/488B growth and
  original 158B glyph task-node constructor differ under modern STL.
  Preserve genuine PMR allocator/ownership behavior.
  [35B](GLYPH_MASK_EMPLACE35_NATIVE_FRONTIER.md),
  [growth](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md),
  [158B node](GLYPH_QUEUE_NODE_CTOR158_NATIVE_FRONTIER.md).

## D. Recent large exact closures — do NOT rework as pending

- **Game-specific filesystem existence** `0x004107A0`, **157/157B
  exact**: true `const char*` input, existing 44B path-from-narrow-string
  ctor and real path destructor, all 7 E8/3 HIGHLOW roles.
  [Current native source proof](GAME_FILE_EXISTS157_NATIVE_FRONTIER.md).


- **Renderer wide formatted-text caller `0x0044AC20`, 417B/114-i386:**
  [WHOLE STRICT EXACT](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md),
  with the complete 10 E8 and three PE HIGHLOW physical roles; the nearby
  586B Unicode sibling and separately called 294B submit remain open.
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

**Card tick Boss closed:** Original `0x00486F60` 875B Card Update is now [whole strict exact](CARD_TICK_BOSS875_AND_UI32_STRICT_EXACT.md), along with distinct `0x00487B90` 32B HUD bit0 leaf. All 28 E8/8 HIGHLOW physical roles and 731 ordinary bytes match; 3/3 affected canonical units pass scoped replay including the preexisting `0x004888A0` 23B Card bit8 getter. The **6,073B battle controller** `0x004B2C90`, which calls the flag getter four times, and 1,896B Card Start remain genuine large **NONEXACT** parents; no whole exactness is inferred for them.
