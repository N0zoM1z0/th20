# 東方錦上京 ～ Fossilized Wonders.

<p align="center">
  <img
    src="resources/title-screen.png"
    width="640"
    alt="Original Japanese TH20 title screen">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="TH20 exact source reconstruction progress">
</p>

Source reconstruction of the original Japanese TH20 v1.00a **Steamless**
executable. Function-level exactness requires reproducible comparison against
one hash-attested target. The workflow follows [TH095](https://github.com/N0zoM1z0/th095),
with Ghidra and a separate modern MSVC environment for TH20.

> [!IMPORTANT]
> Reconstruction is in progress. Verified source components and exact function
> comparisons are available; the repository does not yet build a playable game.
> Origin review, source presence, exactness, linkage and runtime behavior are
> separate statuses.

## Exact target

Supply your own executable as `resources/th20.exe`:

| Property | Required value |
| --- | --- |
| Version | Japanese 1.00a, user-selected Steamless variant |
| Embedded title/replay label | 1.00c; recorded separately from registry/package identification |
| Size | `1,858,560` bytes |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| MD5 | `e7ccdbd2f319ba868ce386e484fff1d3` |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |

```bash
scripts/import-target.sh /path/to/th20.exe
scripts/repo-python scripts/verify-target.py
```

The Steam-original backup is retained locally as provenance evidence. Its
code differs from the comparison target. See [target provenance](docs/TARGET_PROVENANCE.md)
for official Japanese release and independent executable identification.
Game executables, assets, private databases, toolchains and reference checkouts
are excluded from Git.

## Repository status

At the October 30, 2026 checkpoint the maintained graph has **1,443
source-present mappings**, **1,443 strict canonical native units** and
**390 canonical MSVC object/receipt providers**. Independently verified
game-authored whole-function exactness is **752 complete functions /
256,261 original native bytes**. These are dated values, not a
whole-game buildability or playable-game claim: always run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`
for the live inventory and consult the
[current concise handoff](docs/RE_HANDOFF.md) for the unfinished bosses.

| Area | Verified live state and detailed evidence |
| --- | --- |
| **Large exact game functions** | Original [11,110B ECL runtime tick](docs/EXACT_ECL_TICK_RECONSTRUCTION.md), [3,735B Bullet emitter](docs/BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md), [3,490B InputDevice polling](docs/INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md), and other accepted whole bodies; the complete physical credit is in [`config/matches.csv`](config/matches.csv). |
| **Animation quad-submit Boss** | Original **3,159B body /3,180B complete relocated contribution** [strict exact](docs/ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md). Its separate [20B standard `round(float)` header wrapper](docs/ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md) is strict exact but **library**, not authored game code. |
| **Animation rendering backends** | Original **4,347B Mode8**, **2,769B Mode6**, **1,378B Mode6 setup**, **1,996B Mode7 setup**, **753B Mode7**, and **2,136B mesh24/25** each independently whole strict exact. [Mode8](docs/ANIMATION_DRAW_MODE8_4347_STRICT_EXACT.md), [Mode6](docs/ANIMATION_DRAW_MODE6_2769_STRICT_EXACT.md), [Mode6 setup](docs/ANIMATION_DRAW_MODE6_SETUP_1378_STRICT_EXACT.md), [Mode7 setup](docs/ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md), [mesh](docs/ANIMATION_DRAW_MESH2425_2136_STRICT_EXACT.md). Their enclosing **5,993B Draw dispatcher remains NONEXACT**. |
| **Animation geometry Bosses** | Independently exact **2,169B closed line, 1,980B rectangle, 1,601B triangle, 1,468B ring**, and many 375B–1,174B fan/ellipse/strip renderers. [Source-native proof index](docs/EVIDENCE_INDEX.md) supplies the individual original heads and relocation roles; exact children do **not** complete the 5,993B Draw dispatcher. |
| **Separate ribbon Motion-group pipeline** | Separate native **538B segment dynamics Boss**, **140B group update**, **156B draw**, **76B LINESTRIP wrapper**, **89B polymorphic ctor**, **60B segment ctor** and **47B allocation/config wrapper** are independently whole strict exact game-authored functions. Their **78B triple-array ctor**, **156B diagnostic allocation factory**, **20B/49B destructor pair**, **two 19B radius/point ends** and **19B group array-end** are whole native exact with unresolved compiler/template or source ownership, hence not duplicate authored credit. Three 0x3C0-byte segments and the pointer-bearing +0xB5C member preserve real native vtable/auto-zero ABI. The separate **252B ribbon configuration Boss**, its **23B segment-array index**, and the **88B palette with two 31B forwarding helpers**, plus the **75B ribbon 60-color array constructor**, are independently whole strict exact; the whole game does not link or play. [538B dynamics](docs/ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md), [89B/20B/49B ctor and deletion](docs/ANIMATION_RIBBON_GROUP_CTOR_89_STRICT_EXACT.md), [78B array](docs/ANIMATION_RIBBON_SEGMENT_ARRAY_CTOR_78_STRICT_EXACT.md), [156B factory](docs/ANIMATION_RIBBON_GROUP_FACTORY_156_STRICT_EXACT.md), [47B wrapper](docs/ANIMATION_RIBBON_CONFIG_WRAPPER_47_STRICT_EXACT.md), [252B configuration](docs/ANIMATION_RIBBON_GROUP_CONFIG_252_STRICT_EXACT.md), [88B palette and 31B forwarding](docs/ANIMATION_RIBBON_PALETTE_88_31_STRICT_EXACT.md), [75B color array](docs/ANIMATION_RIBBON_COLOR_ARRAY_75_STRICT_EXACT.md), [23B index](docs/ANIMATION_RIBBON_SEGMENT_AT23_STRICT_EXACT.md), [140B update](docs/ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md), [156B draw](docs/ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md), [76B renderer](docs/ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md). |
| **64-point ribbon trail object** | Original **103B polymorphic ctor and 49B scalar deletion** independently whole strict exact under one 0x320-byte native class at original vtable 0x56ED1C. The **520B update Boss is now whole strict exact**, and **165B draw Boss is also whole strict exact**, and **340B gray configuration now also whole strict exact**; **382B magenta alternate configuration is now also whole strict exact**. [103B ctor/49B delete](docs/ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md), [520B update Boss](docs/ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md), [165B draw](docs/ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md), [156B factory](docs/ANIMATION_RIBBON_TRAIL_FACTORY156_STRICT_EXACT.md), [340B gray config](docs/ANIMATION_RIBBON_TRAIL_GRAY340_STRICT_EXACT.md), [382B magenta config](docs/ANIMATION_RIBBON_TRAIL_PINK382_STRICT_EXACT.md), [47B/49B entry wrappers](docs/ANIMATION_RIBBON_TRAIL_WRAPPERS_47_49_STRICT_EXACT.md), [75B color-array ctor](docs/ANIMATION_RIBBON_TRAIL_COLOR_ARRAY75_STRICT_EXACT.md). |
| **Separate one-segment ribbon pipeline** | Original **140B virtual update, 156B virtual draw** and **19B one-past-end pointer** all whole strict exact at separate 0x56ECA4 polymorphic vtable; original 697B segment dynamics and 76B renderer are now independently whole exact. Separately, original **123B packed-color and 202B float `std::fill_n`** C++20 bodies are whole strict exact with real unsigned `jbe` branching, **not authored game credit**. [140B/19B proof](docs/ANIMATION_RIBBON_SOLO_UPDATE_140_END19_STRICT_EXACT.md), [89B ctor and 49B delete](docs/ANIMATION_RIBBON_SOLO_GROUP_CTOR_89_DELETE_49_STRICT_EXACT.md), [156B solo factory](docs/ANIMATION_RIBBON_SOLO_FACTORY_156_STRICT_EXACT.md), [47B solo wrapper](docs/ANIMATION_RIBBON_SOLO_WRAPPER_47_STRICT_EXACT.md), [182B solo configuration](docs/ANIMATION_RIBBON_SOLO_CONFIG_182_STRICT_EXACT.md), [123B solo palette](docs/ANIMATION_RIBBON_SOLO_PALETTE_123_STRICT_EXACT.md), [156B draw proof](docs/ANIMATION_RIBBON_SOLO_DRAW_156_STRICT_EXACT.md), [76B fan](docs/ANIMATION_RIBBON_SOLO_FAN_76_STRICT_EXACT.md), [697B dynamics Boss](docs/ANIMATION_RIBBON_SOLO_DYNAMICS_697_STRICT_EXACT.md), [123B/202B library proof](docs/ANIMATION_RIBBON_FILL_N_123_202_STRICT_EXACT.md). |
| **Polygon stroke and group pipeline** | Whole strict exact **1,204B polygon outline**, **827B dynamics Boss**, **60B segment ctor**, **296B configuration**, **233B group draw**, **140B timer tick**, **120B palette**, **76B fan wrapper**, and **47B configuration wrapper**. [Outline](docs/ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md), [group](docs/ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md), [tick/827B frontier](docs/ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md), [palette](docs/ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md). The **827B segment updater is now whole strict exact**, including both `std::views::drop(1)` loops and original 62/61 array sizes. [Whole native proof](docs/ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md). The original **60B segment ctor** and its 75B 4-byte-cell array ctor are now strict exact; [construction and genuine padding evidence](docs/ANIMATION_POLYGON_SEGMENT_CONSTRUCTION_60_75_NATIVE_EXACT.md). The enclosing **113B group constructor** and its **78B three-segment array constructor are now whole strict exact**. [Array native proof](docs/ANIMATION_POLYGON_SEGMENT_ARRAY_78_STRICT_EXACT.md). [Inheritance/ABI frontier](docs/ANIMATION_POLYGON_GROUP_CTOR_113_ARRAY_78_FRONTIER.md). The generated **49B group scalar-deleting wrapper is also strict exact** (compiler code, not authored credit); its ordinary 20B physical destructor was later matched by the genuine ribbon-group folded destructor chain (original polygon-specific source owner still unresolved). [Complete 113B/49B proof](docs/ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md). The separate **104B outline wrapper remains NONEXACT**. The previously missing **156B C++17 group allocation factory is now whole strict exact** but counted as an origin-unverified template, not authored game bytes. [Factory proof](docs/ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md). |
| **Compiler/STL-like exact helpers** | Seven polygon counted-range leaves, four strict 16B/93B C++20 drop-view helpers, **27 more entire 17B–48B C++20 polygon-range helpers**, two 31B palette tag wrappers and two 23B/19B array access helpers are **whole native strict exact**, but their original authorship is unproven and they are **excluded from authored game totals**. [27-function range-closure proof](docs/ANIMATION_POLYGON_DROP_CLOSURE_27_STRICT_EXACT.md). |
| **Native 39B/26B/23B generation counter operations** | Original true 4B counter postfix increment, `&=mask` and left-shift generation, three complete strict native **39/39 + 26/26 + 23/23** plus independently exact 187B parent. Compiler/utility provenance still unproven, zero additional game-authored byte credit. [Original source/code proof](docs/ANIMATION_RENDERER_GENERATION_COUNTER_39_26_23_STRICT_EXACT.md). |
| **187B original RendererPool AnimationHandle registration** | Full **187B/56-i386 whole strict exact**, native pool `+0x07D40E88` generation post-increment/AND0xFFFF/zero guard and `Animation+0x4C0/0x4C4` combined 32-bit Handle. Four parent 72/75B registration paths remain strict exact. **+187 authored game bytes**. [PE/COFF proof](docs/ANIMATION_RENDERER_HANDLE_REGISTER_187_STRICT_EXACT.md). |
| **RendererPool mode/selection/stride chain** | Original **20B mode getter, 38B pool selector and 20B 72-stride slot index all whole strict exact**; shared actual `+0x6C4/+0x6C8` pool views, parent 922B original still exact, **+58 authored game bytes** (index20 uncredited as compiler-like source). [Complete proof](docs/ANIMATION_SPAWN_POOL_SELECTION_20_38_STRICT_EXACT.md). |
| **Four exact Renderer spawn modes** | Original complete **72B/72B/75B/75B** primary/secondary `IntrusiveList<Animation>` append/prepend and handle publication, all C++ ABI original; **294 native authored bytes /4 heads** and full 922B parent remained 922/922. [Original four-mode proof](docs/ANIMATION_SPAWN_RENDERER_FOUR_MODES_STRICT_EXACT.md). |
| **Particle Update animation timer/color accessors** | Full **25B/19B** original Timer+0x4D8 and color+0x490 getters with true native PE caller E8 from 2,884B Update; **+44 authored-game bytes**. [Complete native strict evidence](docs/ANIMATION_PARTICLE_ANIMATION_ACCESS_25_19_STRICT_EXACT.md). |
| **AnimationHandle child lookup path** | Entire original **108B/37-i386 child query plus 127B/45-i386 Handle forwarder**, original four+five E8 and real security cookies, true hidden `AnimationHandle` result. **+235 game-authored bytes**, both 108/108+127/127 strict exact. [Complete native evidence](docs/ANIMATION_CHILD_HANDLE_LOOKUP108127_STRICT_EXACT.md). |
| **236B recursive Animation raw-world-position Boss** | Genuine original **236B/77-i386 whole strict exact** with three Vector3 component operands, native parent Z rotation and original recursive self E8 plus cookie, **+236 authored native bytes**. [Complete original proof](docs/ANIMATION_RAW_WORLD_POSITION236_STRICT_EXACT.md). |
| **16B STL file-slot capacity leaf** | Native **16B/8-i386** real `std::array<AnimationFile*,42>::size()`, 0x2A return, original 209B file-slot parent E8. **16/16 strict exact**, compiler/STL source excluded from game-authored credit; 2/2 local replay. [Proof](docs/ANIMATION_FILE_SLOT_SIZE16_STRICT_EXACT.md). |
| **103B original file pointer retirement, no duplicate STL head** | Entire **103B/36-i386 strict exact**, original lock slot1, existing `std::destroy_at<AnimationFile>` E8 to **already exact original 16B** physical address, and actual `operator delete`; 103B original unknown template origin **uncredited**. Full 691B/284B/209B/94B lifecycle 5/5 local replay. [Original proof](docs/ANIMATION_FILE_ENTRY_RELEASE103_STRICT_EXACT.md). |
| **92B Renderer locked PRNG pulse** | Real native **92B/30-i386 whole strict exact**, genuine `RandomState::next()` (library callee uncredited), lock slot10, Game Renderer counter+0x04/output+0x14. Native 5 E8/2 HIGHLOW; **+92 authored game bytes** under original no-EH `/GS` MSVC profile. [Full PE/COFF proof](docs/ANIMATION_RENDERER_RANDOM_PULSE92_STRICT_EXACT.md). |
| **230B Renderer staging draw/owner counter application** | Entire native **230B/69-i386 strict exact**, true third intrusive list at Renderer+0x30, E8 into original **5,993B draw Boss still NONEXACT**, and three original pool+0xD8 HIGHLOW; **+230 game-authored bytes**. Original 347B/382B/394B chain remains 4/4 exact in 3-object scoped replay. [Complete proof](docs/ANIMATION_RENDERER_STAGING_APPLY230_STRICT_EXACT.md). |
| **30B Graphics viewport-mode forwarding** | Entire original **30B/14-i386 strict exact**, genuine two E8 sites from 806B category Boss, true E8 to the separately exact 280B viewport setter. All 3 matching single-class Graphics symbols, original compiler NOP and `ret 8`, **+30 authored bytes** and 3/3 local replay. [Native proof](docs/ANIMATION_GRAPHICS_VIEWPORT_FORWARD30_STRICT_EXACT.md). |
| **280B Graphics viewport switch, integrated 806B caller ABI** | Whole native **280B/66-i386 strict exact**, original ViewportState 0x16C stride, genuine device SetViewport vtable+0xBC, four PE pool HIGHLOW and four native caller E8 from 806B Graphics category Boss. **+280 authored bytes**, one unified C++ graphics view and affected 6/6 replay. [Native proof](docs/ANIMATION_GRAPHICS_VIEWPORT_SWITCH280_STRICT_EXACT.md). |
| **806B Renderer Graphics mode/classification Boss** | Full original **806B/211-i386 strict exact**, physical **22 E8/28 HIGHLOW** to real Graphics global `0x005C4D40` and pool `0x005C0028`, genuine state+0x6C0 and six float-zero stores; **+806 game-authored bytes** and Renderer classification chain 5/5 scoped original replay. [Complete native proof](docs/ANIMATION_RENDERER_CLASSIFY_ACTION806_STRICT_EXACT.md). |
| **347B Renderer layer-classification dispatch Boss** | Full native **347B/105-i386 strict exact**, true 14 E8/3 HIGHLOW and lock9, real original 382B+394B classifications, four 0x48-stride renderer lookups and authentic 806B/230B separate children. **+347 authored bytes**, 3/3 scoped chain replay. [Whole proof](docs/ANIMATION_RENDERER_CLASSIFY_DISPATCH347_STRICT_EXACT.md). |
| **382B/394B dual Renderer classification Bosses** | Both game-owned classification and +0x500 link-staging methods **382/382 +394/394 whole strict exact**, true 347B parent E8, 16 native E8/2 HIGHLOW each, first/second 24B lists and third list+0x30. **+776 authored game bytes** and 2/2 affected unit replay. [Complete native proof](docs/ANIMATION_RENDERER_CLASSIFY382394_STRICT_EXACT.md). |
| **188B Direct3D9 surface clearing** | Native **188B/75-i386 whole strict exact**, real texture GetSurfaceLevel/Surface GetDesc/LockRect/UnlockRect/Release, original locked pitch×height `memset`; 2 original E8/one PE HIGHLOW, **+188 game-authored bytes**. [Original proof](docs/ANIMATION_TEXTURE_SURFACE_CLEAR188_STRICT_EXACT.md). |
| **164B Renderer second-list update wrapper** | Native complete **164B/46-i386 strict exact**, genuine lock9, pool+0xD8 reset and typed 0x48 Renderer first slot, E8 into distinct **511B NONEXACT** secondary update. **+164 authored game bytes**, 3/3 scoped replay. [PE/COFF evidence](docs/ANIMATION_RENDERER_UPDATE_SECONDARY164_STRICT_EXACT.md). |
| **59B GameController-gated Renderer update** | Original entire **59B/18-i386 strict exact**, genuine current GameController original 3 PE HIGHLOW, two independently exact status checks, E8 to existing exact 150B Renderer gate. **+59 authored bytes**, 2/2 scoped replay. [Full proof](docs/ANIMATION_RENDERER_UPDATE_GATE59_STRICT_EXACT.md). |
| **411B recursive Animation retirement queue** | Whole original **411B/116-i386 strict exact**: real self recursion, child list traversal and 57B staged `append` instead of distinct 76B free-list `insert_after`, all native 18 E8/2 HIGHLOW. **+411 game-authored bytes**. [Complete evidence](docs/ANIMATION_QUEUE_RETIREMENT411_STRICT_EXACT.md). |
| **150B Renderer locked list-update wrapper** | Whole original **150B/44-i386 strict exact**, true slot9 lock and pool+0x6C8 first Renderer, native 6 E8/3 HIGHLOW, directly calls still NONEXACT 508B update Boss. **+150 authored game bytes**, 1/1 scoped replay. [Original proof](docs/ANIMATION_RENDERER_UPDATE150_STRICT_EXACT.md). |
| **35B Handle event forwarding and 29B caller ABI correction** | Whole distinct **35B/15-i386 strict exact** at original `0x0044F0D0` → exact 261B child-event/VM traversal; **29B Dialogue offset+7** originally calls this 35B, not separate older 35B → 246B ordinary interrupt. Shared decorated symbol corrected, 8/8 scoped exact, **+35 authored bytes**. [Original PE evidence](docs/ANIMATION_HANDLE_EVENT_DESCENDANTS_BRIDGE35_STRICT_EXACT.md). |
| **261B Animation child interrupt/VM visit** | Whole original **261B/81-i386 strict exact**, true 456B handle resolver, real child-links[1] iteration, native `Animation::interrupt(event)` followed by real **39,470B VM** E8 (VM still NONEXACT), **14 E8/2 HIGHLOW**, +261 game-authored bytes. Resolver dependency 5/5 scoped strict. [PE native proof](docs/ANIMATION_POOL_EVENT_DESCENDANTS261_STRICT_EXACT.md). |
| **56B Handle fallback resolver +39B callback forward** | Real native 51B Handle resolver followed by genuine **resident Animation at pool+0xDC** fallback, then original Animation callback write. **56/56 and 39/39 whole strict exact**, 3 original E8/one PE HIGHLOW, **+95 authored bytes**, 10/10 scoped replay; corroborates real 138B pool destructor layout. [Complete proof](docs/ANIMATION_HANDLE_RESOLVE_RESIDENT56_CALLBACK39_STRICT_EXACT.md). |
| **138B native AnimationPool owner destructor with genuine 96MiB typed array** | Complete original **138B/41-i386** plus physical **5B INT3** (143/143 compared), real Worker+4, Animation+0xDC, Renderer+0x6C8, typed 65,536 × 0x600 PooledAnimation array+0x710 and trailing Animation+0x6000818. True native 6 E8/2 HIGHLOW, **+138 authored bytes**; Worker/339B/308B scoped **12/12** replay. [Full PE and layout proof](docs/ANIMATION_POOL_DESTRUCTOR138_STRICT_EXACT.md). |
| **339B Renderer two-list Animation full retirement Boss** | Whole original **339B/106-i386 strict exact**, native primary/secondary list traversal, all 19 E8/4 HIGHLOW including two genuine 308B pool-retirement calls; **+339 game-authored bytes**. Strict scoped regression **5/5** across the Renderer and pool chain. [Native PE evidence](docs/ANIMATION_RENDERER_ALL_RETIRE339_STRICT_EXACT.md). |
| **308B AnimationPool release Boss and two game-specific helpers** | Original whole **308B/80, 82B/22, 90B/27 i386 strict exact**, plus uncredited 23B STL 0x600-step index; original 11 E8/2 HIGHLOW in 308B parent. **+3 authored game heads/+480 bytes**, source-affected 4/4 replay. [Native original proof](docs/ANIMATION_POOL_RELEASE_308_AND_HELPERS_STRICT_EXACT.md). |
| **691B Renderer file-detachment Boss** | **691B/205-i386 whole strict exact**, two 24B Animation intrusive lists and genuine 72B renderer slot, native 29 E8 and 2 HIGHLOW including EH/cookie. Real Animation file-ID/byte-flag checks and `+0x570` retirement state; **+691 authored game bytes** with entire 284B/94B/209B file lifecycle replay **4/4**. [Complete proof](docs/ANIMATION_RENDERER_FILE_DETACH691_STRICT_EXACT.md). |
| **209B RendererPool AnimationFile slot release** | Whole native **209B/61-i386 strict exact**, 42-entry `AnimationFile*` table at original pool+0x06000730, correct original `jl/jb/jmp` source branch, 8 E8/1 HIGHLOW, actual 284B file clear and object retirement. **+209 authored bytes**; three-unit local lifecycle replay. [Full original proof](docs/ANIMATION_FILE_SLOT_RELEASE209_STRICT_EXACT.md). |
| **94B texture record COM/allocator retirement** | Original **94B/33-i386 whole strict exact**, typed Direct3D9 `Release()`, buffer owner reset and original 284B file-clear parent E8; **+94 authored game bytes**, 2/2 local replay. [Native proof](docs/ANIMATION_TEXTURE_RELEASE94_STRICT_EXACT.md). |
| **284B `AnimationFile::clear()` resource-retirement Boss** | Entire **284B/81-i386 native whole strict exact**, real renderer file detach/texture release and allocator arrays/bytes retirement, all original **8 E8 and 8 HIGHLOW** anchored. **+284 game-authored bytes**, 1/1 affected-only replay. [Whole proof](docs/ANIMATION_FILE_CLEAR284_STRICT_EXACT.md). |
| **922B AnimationFile spawn Boss whole strict exact** | **922B/269-i386 full native original exact**, actual seven visible args plus compiler-hidden `AnimationHandle` return, original lock/allocate/script/position/flag/render selection. **20 E8 and 14 HIGHLOW** entirely verified. The 83B caller was retyped to the same actual original member and replayed 83/83 exact. **+922 authored game bytes**. [Complete PE/COFF proof](docs/ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md). |
| **83B particle AnimationFile spawn wrapper** | Original **83B/30-i386 whole strict exact**, mode 1 selects flag16, six incoming arguments passed to native 922B Animation file spawn with additional fixed flags; called four times from 2,884B particle Boss. **+83 authored-game bytes**. [Whole original proof](docs/ANIMATION_PARTICLE_SPAWN_WRAPPER_83_STRICT_EXACT.md). |
| **57B original Animation interpolation forwarding** | Native **57B/24-i386 whole strict exact**, Animation `+0x8C` interpolator with mode8 and five original arguments, E8 to already exact 124B configuration; called twice in original 2,884B Boss. **+57 authored game bytes**, 2/2 local affected replay. [Whole proof](docs/ANIMATION_PARTICLE_INTERPOLATION_FORWARD_57_STRICT_EXACT.md). |
| **124B Vector3 interpolation configuration** | Whole original **124B/45-i386** with seven genuine E8 setter/Timer targets, original `+0x30` current and `+0x3C` Timer, typed natural C++20 **124/124 strict exact**. **+124 authored-game bytes**; enclosing 2,884B Update remains source absent. [Full proof](docs/ANIMATION_PARTICLE_INTERPOLATION_124_STRICT_EXACT.md). |
| **202B original Vector3 normalized geometry** | Whole **202B/58-i386** three-component vector normalization/copy exact, two native E8 and real 0.01f epsilon HIGHLOW; **+202 authored game bytes**. [Original full proof](docs/ANIMATION_PARTICLE_NORMALIZE202_STRICT_EXACT.md). |
| **200-particle polymorphic native group constructor** | Whole **172B/46-i386** original game ctor and **49B/18-i386** generated deleting wrapper now strict exact under one real **0x1940-byte** class with two 200-element Vector3 arrays. Original `0x56EC14` vtable and all 9 ctor E8/1 HIGHLOW independently audited. **+172 authored-game bytes**; generated wrappers uncredited. [Whole original proof](docs/ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md), [156B C++17 factory](docs/ANIMATION_PARTICLE_GRID_FACTORY156_STRICT_EXACT.md), [47B create/31B configuration](docs/ANIMATION_PARTICLE_GRID_CREATE47_CONFIG31_STRICT_EXACT.md), [92B virtual stop](docs/ANIMATION_PARTICLE_GRID_STOP92_STRICT_EXACT.md). |
| **1,486B rotated sprite corner Boss now whole exact** | **1,486/1,486 original x86 exact** with all 13 E8, nine native HIGHLOW and an authentic compiler-emitted `+0x41` NOP from the post-Angle lexical scope. The separately exact 985B corner sibling remains unchanged. [Complete strict proof](docs/ANIMATION_CORNER_ROTATED_1486_STRICT_EXACT.md). |
| **Source-present, NONEXACT parents** | Original [5,993B Animation Draw](docs/ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md), [104B polygon wrapper](docs/ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md), [3,111B Player main](docs/PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), and [555B Player movement](docs/PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **Source-absent large parents** | Original [12,140B Bullet extended command](docs/BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md), [41,967B Enemy ECL opcode dispatcher](docs/ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md), and **39,470B Animation VM update**. Their exact callees are not parent-body credit. |
| **Exact original `.rdata`** | The **96B 2×3×4 quad corner table**, **8B polygon widths (16.0f/32.0f)** and **72B Player direction table** each have attested original data bytes; **none** increases game `.text` coverage. [Corner table](docs/ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md), [polygon scalars](docs/ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md), [Player data](docs/PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |
| **Whole-program result** | **Not linked or playable yet.** Source mapping, canonical strict acceptance, original authorship credit, static data and runtime integration are different claims. |

[Generated progress](docs/PROGRESS.md) and the status reporter provide live
authored totals. [The current handoff](docs/RE_HANDOFF.md) records remaining work
and local verification; [the evidence index](docs/EVIDENCE_INDEX.md) routes dated
investigations without mixing historical counts into current status.

The pinned toolchain candidate is MSVC 19.44.35211 x86, Windows SDK 10.0.26100.0
and D3DX 9.29.952.8. Accepted units use explicit per-source profiles. These results
do not establish executable-wide compiler flags, SDK or CRT identity.

## Build and verify

Documentation and artifact-cleanup handoffs use diff/link checks and protected
product hashes. An unchanged native compiler-input graph needs no replay,
compiler, Ghidra or full CI run. Shared-header text edits can invalidate
pinned compiler receipt hashes: replay only the actual pre-edit receipt include
closure in that case. Use the `gpt-web:` commit prefix.

When code or infrastructure changes warrant broader checks, public CI needs
Python 3.11+, with no original game or C++ compiler:

```bash
scripts/repo-python scripts/ci.py
```

Default CI checks the exact oracle and repository metadata. The historical
portable C++ semantic suite has been retired; [retained tests](tests/README.md)
cover exact comparison and repository tools. Exact checkpoints require affected
native builds and complete strict replay. A specific unresolved behavior or ABI
question can use a temporary probe under `.analysis/`.

Private preflight for reconstruction changes is:

```bash
scripts/bootstrap-tools.sh
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

On a fresh private workspace, provision tools as described in
[Tools](docs/TOOLS.md), then run `scripts/repo-python scripts/ghidra.py import` once.
Every query re-attests the executable and complete mapped code section;
inventory refreshes never overwrite reviewed ledgers.
For source changes, derive the actual affected providers from captured include
closures and manifest dependencies. Build and replay only those units, with
individual unit commands or explicit `--source` filters. New exact acceptance
requires affected cold builds; see [build and matching](docs/BUILD_MATCHING.md).

## Reference review

[Oracatt/Touhou20](https://github.com/Oracatt/Touhou20) is pinned locally under
ignored `_reference/Touhou20`. Its target hash matches ours. Its v1.00c label
comes from embedded strings; our v1.00a identification follows the independent
hash registry and supplied package. Both observations are preserved in provenance.

The [review](docs/REFERENCE_REVIEW.md) records the repository-wide evidence audit,
module dispositions, stale reports and independently verified absorption.
Validated source diagnostics route further analysis; reference source, build
layout and completion claims are not imported wholesale.

The [function-by-function review](docs/REFERENCE_FUNCTION_REVIEW.md) is complete
for all 6,945 indexed implementations, including one parser omission recovered
during manual review. All 113 parser-gap files are manually reconciled. The
[final audit](docs/REFERENCE_SUPPORT_REVIEW.md) records coverage and evidence
limits; nonexact implementations remain documented for further reconstruction.

## Documentation

- [Current handoff](docs/RE_HANDOFF.md)
- [Focused evidence index](docs/EVIDENCE_INDEX.md)
- [Architecture and target inventory](docs/ARCHITECTURE.md)
- [Reconstruction workflow](docs/RE_WORKFLOW.md)
- [Latest source/document cleanup and protected storage audit](docs/MAINTENANCE_STORAGE_2026_10_30.md)
- [Historical CORE628 artifact-retirement checkpoint](docs/ARTIFACT_RETIREMENT_CORE628.md)
- [Independent oracles](docs/ORACLES.md)
- [Build and strict matching](docs/BUILD_MATCHING.md)
- [Ghidra setup and attestation](docs/GHIDRA.md)
- [Tool routing](docs/TOOLS.md)
- [Source ownership](docs/SOURCE_MAP.md)
- [Semantic reconstruction policy](docs/SEMANTIC_RECONSTRUCTION.md)
- [Reference review](docs/REFERENCE_REVIEW.md)
- [Function-by-function reference review](docs/REFERENCE_FUNCTION_REVIEW.md)
- [Complete reference review and final tooling batch](docs/REFERENCE_SUPPORT_REVIEW.md)
- [Enemy movement, spawn and variable review](docs/REFERENCE_ENEMY_MOVEMENT_REVIEW.md)
- [Runtime invincibility launcher](docs/RUNTIME_PATCH.md)
- [Verified knowledge base](docs/KNOWLEDGE_BASE.md)
- [Roadmap](docs/ROADMAP.md)
- [Generated progress](docs/PROGRESS.md)
- [Agent rules](AGENTS.md)

## Credits

- [Oracatt/Touhou20](https://github.com/Oracatt/Touhou20): reference
  reconstruction, source diagnostics and behavioral investigations that guide
  our independent, function-by-function review.
- [N0zoM1z0/th095](https://github.com/N0zoM1z0/th095): reconstruction workflow,
  exact-oracle control plane, tracking conventions and README/progress layout.

## License

[MIT](LICENSE) for this repository's original code and TH095-derived control
plane. It grants no rights to the original game, downloaded tools or external
reference material. Maintained prose and commit messages are in English;
official names and original target evidence retain their original language.
