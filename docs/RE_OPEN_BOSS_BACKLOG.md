
**Window scheduler 884B CLOSED whole strict exact:** Original 0x004193E0 now [884B/239-i386 strict native source exact](WINDOW_FRAME_SCHEDULER_BOSS884_STRICT_EXACT.md), all 32 native E8 and 21 HIGHLOW physical locations/destinations, 672/672 ordinary bytes. The old 866B/236-instruction D3D9 source and NONEXACT records in earlier backlog sections are superseded research history. Restoring the original observed scanline local, real double clock sample and scoped D3D9 Reset yields an authentic original NOP and all 884 bytes. One 1/1 scoped cold replay, +884 unique game-authored bytes, no double counting exact callees.
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

**Card FunctionChain registration also closed:** Original 121B Card register `0x00487B10` and its two original 13B update/draw callback wrappers `0x004885D0`/`0x00488680` are [whole source strict exact](CARD_REGISTRATION121_CALLBACK_BRIDGES13_STRICT_EXACT.md): six original calls and three physical HIGHLOW pointer roles, real FunctionChain priority 40/12, 147 newly accepted authored bytes. Exact update/draw callbacks enter the now exact 875B Card Update and [797B Card Draw Bosses](CARD_DRAW_BOSS797_AND_ASCII_SETTERS75_STRICT_EXACT.md); only the separate Card Start and other large controllers remain open.

**Card dispatch callback provenance:** The original 121B Card registration `0x00487B10` and its 13B update/draw bridges at `0x004885D0` / `0x00488680` are now [whole strict exact](CARD_REGISTRATION121_CALLBACK_BRIDGES13_STRICT_EXACT.md). The registered update bridge targets the already exact 875B tick; the draw bridge targets the [now whole-exact 797B Card Draw `0x00487590`](CARD_DRAW_BOSS797_AND_ASCII_SETTERS75_STRICT_EXACT.md) with three exact 25B AsciiInf setters; no duplicate byte credit is assigned to its 13B bridge.

**797B Card Draw is now closed:** `0x00487590` has [797/797B whole strict exact C++](CARD_DRAW_BOSS797_AND_ASCII_SETTERS75_STRICT_EXACT.md), together with three distinct original 25B font/layer/alpha setters (new 872B total). Remaining genuine Card Boss frontier: **1,896B Card Start**, **6,073B battle control**.

**Card clock Boss closed:** [Original 645B Card clock and 37B callback whole strict exact](CARD_CLOCK_BOSS645_CALLBACK37_STRICT_EXACT.md) at 0x004872D0/0x00487560: 14 E8/12 HIGHLOW original sites and targets, 541 ordinary bytes, native exception-mode FWAIT and 2/2 source-scoped cold replay. The original 38B/41B child accessors are now [independently whole exact](CARD_TIME_ARCHIVE_ACCESSORS_38_41_NATIVE_EXACT.md); their 20B generic index helper stays origin-review and uncredited. Larger open parents include 1,896B Card Start and 6,073B battle controller.

**Card archive children closed:** [Original 38B primary and 41B alternate archive selectors at 0x00488740 / 0x00488770 are whole exact](CARD_TIME_ARCHIVE_ACCESSORS_38_41_NATIVE_EXACT.md), using the true 50-pointer array, 44-byte stride record index and existing folded 22B primitive. New 20B generic record-index helper has a strict source receipt but unresolved authorship; game-authored credit increases by only **79B**. One affected source cold replay 3/3.

**Window clock upstream also closed:** The [original WindowState 346B seconds clock 0x0041CB10](WINDOW_SECONDS_CLOCK346_STRICT_EXACT.md) is now whole strict exact with real QPC/timeGetTime and original 64-bit conversion, 8 E8/19 data targets and 238 ordinary bytes matching. The already exact 645B Card-clock parent calls this head twice; +346 genuine authored game bytes, one unit scoped replay.

**Window frame callback frontier:** 32B Window/Frame dispatch 0x004193C0 is [strict whole exact](WINDOW_FRAME_CLOCK_DISPATCH32_STRICT_EXACT.md); its genuine 437B device frame-clock callee 0x004ABD50 is [now whole strict exact](WINDOW_FRAME_DEVICE_CLOCK437_STRICT_EXACT.md). The 37B Card timer callback child and 346B WindowState clock are separately exact; one new 32B authored physical head, 1/1 cold replay.

**Window device 437B frame-timing Boss closed:** [Original 0x004ABD50 whole strict exact](WINDOW_FRAME_DEVICE_CLOCK437_STRICT_EXACT.md), 105 instructions with 2 E8/14 PE HIGHLOW positions/targets and 373 ordinary bytes. Scoped 2/2 original MSVC replay also retained the 32B frame dispatch. The 113B native pipeline child 0x004AC0E0 is [now whole strict exact](WINDOW_FRAME_PIPELINE113_STRICT_EXACT.md); 46B/42B/21B subordinate time helpers and larger scheduling callers remain open.

**113B frame pipeline closed:** [Original 0x004AC0E0 113B /34 i386 whole strict exact](WINDOW_FRAME_PIPELINE113_STRICT_EXACT.md), native three E8 helpers, 101 ordinary bytes, no security cookie. Its existing 437B parent/32B caller stay exact under 3/3 affected source cold replay. The 46B/42B/21B helpers at 0x004AC170 /0x004AC200 /0x004AC270 now have [whole-exact typed source](WINDOW_FRAME_TIME_LEAVES109_NATIVE_EXACT.md), with origin review and no new game-authored credit.

**Time-wrapper dependent leaves source exact:** [46B/42B/21B whole-source exact](WINDOW_FRAME_TIME_LEAVES109_NATIVE_EXACT.md) for the original 113B frame-pipeline caller; 6/6 affected units strict replay. Original source provenance remains under review because these wrappers may be chrono/CRT-generated; no additional authored-game byte credit.

**884B Window scheduler frontier:** 0x004193E0 calls the [new whole-exact 31B RepeatCounter selector 0x0041CA50](WINDOW_ACTIVE_REPEAT31_STRICT_EXACT.md) 14 times and the already exact 346B WindowState clock. Parent still NONEXACT; typed source next, do not credit parent bytes through this leaf.

**884B Window scheduler now source-present:** [Whole typed 866B/236-i386 source](WINDOW_FRAME_SCHEDULER884_FULL_SOURCE_FRONTIER.md) reconstructs original 884B/239-i386 device poll using real IDirect3DDevice9::GetRasterStatus on native D3DRASTER_STATUS(InVBlank,ScanLine), real Present/Reset and WinMM pacing, 14 exact 31B repeat calls and six exact 346B clock calls. All 32 original E8 callee roles and 21 data destination roles are in order; 13 E8 and 7 data sites now align physically and 367 positional ordinary bytes agree. Parent remains NONEXACT; no new exact parent-game byte credit. Pursue genuine raster scanline/wait-loop lifetime, not dummy local stack padding.

**Historical 574B Window screenshot frontier, now closed:** The earlier [551B/125-instruction source](WINDOW_SNAPSHOT_SCENE574_FULL_SOURCE_FRONTIER.md) had all 20 callee/12 data target roles but misaligned fields. Its input guard and c_str pointer lifetimes are now [574/574B full native exact](WINDOW_SNAPSHOT_SCENE574_STRICT_EXACT.md), with all fields and 446/446 ordinary bytes. Only 884B enclosing frame scheduler remains open.

**Screenshot Renderer pending leaf now closed:** The 574B Window scene Boss first calls whole-exact [88B Renderer pending blit queue](WINDOW_CAPTURE_PENDING88_STRICT_EXACT.md) at original 0x0041BFC0, which itself calls the previously strict-exact 439B D3D9 surface transfer. Both child functions are distinct whole exact, and the screenshot parent 574B subsequently reached whole strict exact; only the 884B frame scheduler remains NONEXACT. Reproduce new 88B via only src/WindowCapturePending88.cpp cold replay.

**Window Present/Reset 164B now strictly closed:** Original 0x004199A0 has [complete 164B/49-i386 exact natural source](WINDOW_PRESENT_NO_WAIT164_STRICT_EXACT.md) with original nine E8 +eight HIGHLOW physical fields and 96/96 ordinary bytes; MSVC original post-scene NOP arises from the real Present lexical scope and separate Reset device lifetime. Its 574B Window screenshot callee subsequently reached whole strict exact; only the separate 884B Window scheduler remains NONEXACT. The two exact original heads have independent byte credit.

**Paced Window Present 385B now strict exact:** Original 0x00419A50 has [385/385B whole natural-source exact](WINDOW_PACED_PRESENT385_STRICT_EXACT.md) with real 1/60-second pacing, positive Win32 Sleep budget, genuine D3D9 Present/Reset, 12/12 physical E8 and 17/17 PE data fields/targets, 269/269 ordinary bytes. The companion 164B no-wait Presenter is also strictly exact; both call whole-exact 574B screenshot scene. The separate 884B Window scheduler remains NONEXACT.

**Window screenshot Boss resolved:** Original 0x00419760 now [574B whole strict exact](WINDOW_SNAPSHOT_SCENE574_STRICT_EXACT.md), including 20 E8/12 HIGHLOW sites, 446 ordinary bytes and 1/1 scoped cold replay. Prior screenshot NONEXACT notes are historical; only the enclosing 884B Window scheduler remains open.

**Window frame controller 433B now closed:** [Original 0x00419C20 whole 433B strict exact](WINDOW_FRAME_CONTROLLER_BOSS433_STRICT_EXACT.md), 15 E8 and 18 PE data fields/targets plus all 301 ordinary bytes exactly, original FunctionChain frame callback and real D3D9 scene flow. The original 884B Window scheduler is a separate callee still NONEXACT; its 866B typed D3D9 raster polling source stays open.

**Window no-wait frame controller 583B now strictly closed:** Original 0x00419DE0 has [whole native 583B/138-i386 exact](WINDOW_FRAME_NO_WAIT_BOSS583_STRICT_EXACT.md), with real time sync/Sleep, 16 E8 +20 HIGHLOW native physical fields, 439 ordinary bytes, and distinct 164B no-wait Presenter. This joins 433B and 574B closed Window Bosses; the separate 884B Window scheduler remains NONEXACT.

**Paced Window controller 370B now strictly closed:** Original 0x0041A030 is [whole 370B/97-i386 strict exact](WINDOW_FRAME_PACED_BOSS370_STRICT_EXACT.md) including 15 native E8, 15 HIGHLOW physical positions and 250 original ordinary bytes; the genuine constant-true guard and existing 385B paced Presenter compose its source. Window 433B, 583B, 574B and 370B bosses are exact; the separate 884B scheduler is still NONEXACT.

**Window paced frame controller 370B closed whole strict exact:** Original 0x0041A030 is [370/370B native source-exact](WINDOW_FRAME_PACED_BOSS370_STRICT_EXACT.md), with 97 instructions, 15 E8 and 15 PE HIGHLOW site/target matches, and 250 ordinary bytes. Its genuine 13B always-true entry guard, FunctionChain and D3D9 render path naturally match MSVC. The separately exact 385B Presenter is reused; the 884B Window scheduler remains NONEXACT.

**Graphics viewport clip 284B now strictly closed:** Native 0x0041DCE0 is [284/284B full strict exact](GRAPHICS_VIEWPORT_CLIP284_STRICT_EXACT.md), two original E8 +four native PE data fields and all 260 ordinary bytes; separate original 280B Graphics mode setter remains exactly credited only once. This is an original shared callee of 433B, 583B and 370B Window controller Bosses. The 884B scheduler remains source-present and NONEXACT.

**Graphics frame cleanup leaf now closed:** Original 0x004D9E30 [whole strict 53B exact](GRAPHICS_WORKER_CLOSE53_STRICT_EXACT.md): real Graphics+0xD90 Worker, native diagnostic and original 3 E8/1 HIGHLOW, distinct 53 game bytes. The 370B/433B/583B Window frame controller callers remain separately exact. The 884B scheduler is still open.

**Graphics D3D9 transform stage 194B closed exact:** Original 0x004DA120 now [whole 194B strict exact](GRAPHICS_PREPARE_DEVICE194_STRICT_EXACT.md), 3 native E8 +7 PE data sites/targets, 154 ordinary bytes; the actual process-global Graphics device and native D3D9 View/Projection matrices. The camera recompute 846B original at 0x004DA1F0 remains independently open, including D3DXMatrixLookAtLH/PerspectiveFovLH.

**Graphics D3DX9 camera Boss 846B now closed:** Original 0x004DA1F0 [846/846B whole native strict exact](GRAPHICS_CAMERA_MATRIX_BOSS846_STRICT_EXACT.md), 194 instructions, original 7 E8 +20 HIGHLOW site identities and 738/738 ordinary bytes, true 0/2^32 unsigned-double correction table and three Vector3 constructors. The 194B device transform and 284B viewport mode caller remain independently exact, but the 884B Window scheduler is still NONEXACT.

**Graphics D3D9 resource release 136B now closed:** Original 0x004DD840 is [136/136B original strict exact](GRAPHICS_D3D_RESOURCE_RELEASE136_STRICT_EXACT.md), 35 instructions, native 13 PE HIGHLOW physical resource references with process Graphics+0x19C/0x1A0/0x1A4 true COFF addends, 84 ordinary bytes. This is a real resource cleanup leaf called by the now whole-exact 884B Window frame scheduler, 164B and 385B Presenters.

**Window device state reset Boss 1,954B — now source-present, NONEXACT:** Original 0x0041A2C0 has [complete compiled C++20 1,911B/499-i386 source](WINDOW_DEVICE_RESET_STATES_BOSS1954_FULL_SOURCE_FRONTIER.md), 24 RenderState, eight TextureStageState, six SamplerState real D3D9 calls and five native Renderer recovery hooks. 43/43 game E8 callee target roles and 47/47 PE data target roles match in original order, but original native 1,954B/507 instructions includes a genuine GS cookie/stack lifetime not yet reproduced. Zero new exact 1,954B parent bytes, no full cold replay.

**Five Renderer D3D9 reset leaves closed exact:** Original 0x0041DB40/60/80/A0/C0 now have [five strict whole-native exact bodies /108 original bytes](RENDERER_DEVICE_RESET_HOOKS108_STRICT_EXACT.md), native large AnimationPoolOwner state bytes at +0x6000E08/+0x6000E0C/+0x6000E0D/+0x6000E0E/+0x6000E10. One source-scoped cold object, 5/5 units. Their larger 1,954B D3D9 device reset-state caller remains NONEXACT and uncredited.
