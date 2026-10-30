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
| Source-present function mappings | **1,443** (authored game **plus** compiler/library and unaccepted sources) |
| Whole-native strict units | **1,443**, from **390** pinned MSVC object/receipt providers |
| Credited original authored-game whole exact | **712 distinct function heads /249,793 original `.text` bytes** |
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

| Three original 75B `Vector2[60]/[64]/[61]` constructors | **ORIGINAL PE VERIFIED, SOURCE NONEXACT**. Native 75B/27 x86 each and five real `INT3` each; one genuine E8/3 HIGHLOW and independent ctor parent calls. Isolated MSVC `Vector2() noexcept` matches all three **80B structural contributions**, but real global ODR/class declaration remains unchanged (**230 strict provider/871-unit affected closure**). No false exact admission or game code credit. [Evidence and original verifier](ANIMATION_VECTOR2_ARRAY_60_64_61_NOEXCEPT_FRONTIER.md). |
| Original 202B 3D vector normalize `0x0045CF10` | **202B/58-i386 whole strict exact**: native square_root/absolute E8 and PE 0.01f HIGHLOW, real `comiss/jbe` copy-versus-3-divide semantics. **+202 authored game bytes**, one local object only. [Original proof](ANIMATION_PARTICLE_NORMALIZE202_STRICT_EXACT.md). |
| 39B/26B/23B original four-byte generation counter leaf chain | **39B postfix `++`, 26B AND mask, 23B high-word shift**, entire three original physical functions, genuine 187B parent E8 and all **39/39 +26/26 +23/23** exact. Generic operator source ownership review/uncredited; old Ghidra Concurrency name at 0x449690 misleading. [Actual original/code proof](ANIMATION_RENDERER_GENERATION_COUNTER_39_26_23_STRICT_EXACT.md). |
| Native generation counter helpers `0x00449570/0x00449690/0x004493E0` | **39B/26B/23B all whole strict exact**, original postfix increment, AND masking and left shift, all four real E8 sites in 187B registration Boss; zero original PE relocations. Source owner provenance unresolved, **zero new authored game byte credit**. [Full original evidence](ANIMATION_RENDERER_GENERATION_COUNTER_39_26_23_STRICT_EXACT.md). |
| Original 187B RendererPool Handle register `0x0044C8F0` | **187B/56-i386 complete strict exact**, original six E8/zero HIGHLOW and four true Renderer-mode parent calls. Native counter `+0x07D40E88`, original postfix `++`, `&=0xFFFF`, zero guard, high generation plus 16-bit Animation index into Handle+0x4C0. **+187 game-authored bytes**, 5/5 affected-only strict replay. [Full original/native proof](ANIMATION_RENDERER_HANDLE_REGISTER_187_STRICT_EXACT.md). |
| Three original RendererPool selector leaves `0x00449490/0x0044C8A0/0x0044C8C0` | **20B/20B/38B whole strict exact**: native `0x48` stride index, `+0x6C4` mode flag and `+0x6C8` slot-indexed Renderer selection. Three complete physical bodies, genuine 922B parent 3 E8, **+58 authored game bytes** for the custom 20B+38B pool methods; 20B array index generated origin uncredited. [Proof](ANIMATION_SPAWN_POOL_SELECTION_20_38_STRICT_EXACT.md). |
| Four native Renderer registration modes `0x0044B7F0/0x0044B840/0x0044B8E0/0x0044B890` | **72B+72B+75B+75B all whole strict exact**. One shared two-24B-list Renderer view, real append/prepend, Animation+4E8/+4EC, four parent 922B E8 and original AnimationHandle hidden return. **+4 authored game heads/294 native bytes**, 922B parent recompiled 922/922 local exact. [Full original evidence](ANIMATION_SPAWN_RENDERER_FOUR_MODES_STRICT_EXACT.md). |
| Resource-name binary equality and `memcmp` `0x00447200/0x0044BE00` | **73B/29-i386 and 34B/16-i386 whole strict exact**, original PMR stem 77B caller E8 and native `memcmp` E8; zero in-body PE HIGHLOW, 21 authentic alignment INT3 outside code. **+2 strict units/107 native bytes**, original STL origin uncredited. [Original proof](ANIMATION_SPAWN_STEM_BYTE_EQUAL_73_34_STRICT_EXACT.md). |
| 922B `AnimationFile::spawn` stem-check leaves `0x00446DE0/0x0044B400` | Real **17B free PMR-string forward and 77B content compare both whole strict exact**; original nested E8 and 922B caller original physical targets, genuine string data+0x04 and length+0x14. **2 new strict units/94 native bytes**, generic/library provenance unknown and zero authored credit. Parent 922B replays exact. [Original proof](ANIMATION_SPAWN_STEM_77_17_STRICT_EXACT.md). |
| Original 108B/127B AnimationHandle child-query chain `0x0044C830/0x0044C7B0` | **Both whole strict exact**, native 108B/37-i386 live Animation child query plus 127B/45-i386 handle-resolve forwarding, true `AnimationHandle` class-value return and 9 E8/2 HIGHLOW cookie fields. **+2 authored heads /235 native bytes**; 241B `find_child` original already exact, not recounted. [Original proof](ANIMATION_CHILD_HANDLE_LOOKUP108127_STRICT_EXACT.md). |
| 2,884B particle Update native Timer/Color accessors `0x0045D0A0/0x0045D0E0` | **25B/10-i386 plus 19B/9-i386 whole strict exact**, real Animation+0x4D8 Timer int and Animation+0x490 native color word, physical parent E8 at 0x45CC7D and 0x45C713; **+2 authored heads/+44 bytes**. [Original and COFF proof](ANIMATION_PARTICLE_ANIMATION_ACCESS_25_19_STRICT_EXACT.md). |
| Original recursive Animation raw-world-position `0x0044CB80` | Whole **236B/77-i386 strict exact**, two Vector3 sum E8, real parent_558 flags/rotate, self-recursion E8, parent addition and one PE cookie HIGHLOW; all 8 native E8 exactly anchored and 236/236 C++20. **+236 original authored game bytes**, enclosing larger position paths separate. [Native proof](ANIMATION_RAW_WORLD_POSITION236_STRICT_EXACT.md). |
| Native `std::array<AnimationFile*,42>::size` `0x00450870` | **16B/8-i386 full original strict exact**, real original return 42 and native E8 in 209B RendererPool release; library-generated, excluded from game-authored credit. Parent 209/209 still exact in scoped 2/2 replay. [Evidence](ANIMATION_FILE_SLOT_SIZE16_STRICT_EXACT.md). |
| Native original 103B file-object pointer release `0x00447330` | Whole **103B/36-i386 strict exact** with true source `std::destroy_at<AnimationFile>` E8 to **pre-existing 16B** library exact, lock slot1 and native delete; original template provenance unknown, **zero authored-game credit**. Duplicate 16B proposed unit discarded after inspecting real repo. Affected lifecycle 5/5 scoped replay. [Evidence](ANIMATION_FILE_ENTRY_RELEASE103_STRICT_EXACT.md). |
| Native 30B wide-text format `0x00447940` | **30B/13-i386 whole strict exact** C ABI utility forwarding original `0x500` limit and `va_list` into native `_vswprintf_s` (one original E8); real 417B Animation text Boss E8 verifies the caller. **+1 library/utility strict unit, zero authored-game credit**. [PE/COFF proof](ANIMATION_TEXT_FORMAT30_STRICT_EXACT.md). |
| Original Renderer locked RNG pulse `0x00449D20` | **92B/30-i386 whole strict exact**, source-native `RandomState` at receiver+0x04, output word+0x14 and byte return, actual slot10 lock and 5 PE E8/2 HIGHLOW. No C++ EH frame in original; pinned C++20 `/GS` without `/EHsc` yields **92/92 exact**, **+92 authored native bytes**; separate `0x004235F0` library PRNG callee uncredited. [Proof](ANIMATION_RENDERER_RANDOM_PULSE92_STRICT_EXACT.md). |
| Original 230B Renderer third-list draw/owner count `0x00449FA0` | **230B/69-i386 whole strict exact**, physically invoked twice by 347B dispatcher after 382B/394B classification; original 10 E8/5 PE HIGHLOW, staged list Renderer+0x30, actual global pool `+0xD8` three loads. The original 5,993B Animation draw callee is still NONEXACT. **+230 authored bytes**, entire classifying chain scoped 4/4 strict. [Original evidence](ANIMATION_RENDERER_STAGING_APPLY230_STRICT_EXACT.md). |
| Original 30B viewport-mode forwarding `0x0044F700` | Native **30B/14-i386 whole strict exact**, two true original 806B category Boss E8 to this method, full real original E8 to the exact 280B Graphics viewport selector. One shared Graphics class ABI, original natural postcall NOP and native return. **+30 authored original bytes**, 3/3 targeted replay, no duplicate 280B/806B credit. [Proof](ANIMATION_GRAPHICS_VIEWPORT_FORWARD30_STRICT_EXACT.md). |
| Original **280B Graphics viewport switch** `0x0044F720` | Native **280B/66-i386 whole strict exact**, actual Graphics ViewportState 0x16C array at +0x278, current_viewport+0xB00, D3D9 SetViewport vtable+0xBC, 2 E8/4 HIGHLOW, four true physical 806B parent E8. Unified one shared Graphics class decorated symbol in both sources; **+280 authored bytes** and entire 806B/347B/382B/394B/230B chain still exact 6/6. [Proof](ANIMATION_GRAPHICS_VIEWPORT_SWITCH280_STRICT_EXACT.md). |
| Entire **806B Renderer graphics classification action Boss** `0x0044F3D0` | Native **806B/211-i386 whole strict exact**, original category-state branches at pool+0x6C0, real Graphics global at 0x005C4D40 and pool at 0x005C0028, **22 genuine E8/28 PE HIGHLOW** including six original XORPS/MOVSS pool float resets. **+806 original game-authored bytes**; 347B/382B/394B/230B parents/adjacent functions remain exact 5/5. [Original proof](ANIMATION_RENDERER_CLASSIFY_ACTION806_STRICT_EXACT.md). |
| Original 347B Renderer classification dispatch Boss `0x00449E40` | **347B/105-i386 whole strict exact**, lock slot9 and native 14 E8/3 PE HIGHLOW including all four physical Renderer lookups, both new 382B/394B exact primary/secondary filters and two genuine calls each to independently NONEXACT 806B action/230B staging. **+347 game-authored bytes**, 3/3 affected replay. [Proof](ANIMATION_RENDERER_CLASSIFY_DISPATCH347_STRICT_EXACT.md). |
| Original **382B/394B Renderer classification Bosses** `0x0044A090/0x0044A210` | Both **whole strict exact** with two original active list heads at 0/+0x18, third staging list +0x30, real `Animation+0x500` link publication, native 16 E8/2 PE HIGHLOW each and **347B parent two actual E8**. The precise nested `node_access()` call evaluation fixes 21 byte differences each. **+2 authored heads /776 original bytes**; 2/2 one-object replay. [Proof](ANIMATION_RENDERER_CLASSIFY382394_STRICT_EXACT.md). |
| Original 188B Direct3D9 texture surface clear `0x00449D80` | Native **188B/75-i386 whole strict exact**, actual COM surface vtable methods, pitch×height memset, true empty null arm and post-Release local pointer reset; original 2 E8/1 PE HIGHLOW. **+188 authored bytes**, scoped 1/1 replay. [Native proof](ANIMATION_TEXTURE_SURFACE_CLEAR188_STRICT_EXACT.md). |
| Original 164B secondary Renderer list-update `0x00449A70` | Whole **164B/46-i386 strict exact**, real ECX owner and locked pool flag+0xD8 clear before actual Renderer+0x6C8 72B slot selection, native call to separate **511B still NONEXACT** second-list loop. Original 6 E8/3 HIGHLOW; **+164 authored native bytes**, previously exact 150B/59B replay 3/3. [Proof](ANIMATION_RENDERER_UPDATE_SECONDARY164_STRICT_EXACT.md). |
| Original 59B GameController-gated Renderer entry `0x00450880` | Native **59B/18-i386 whole strict exact**: GameController native global 3 HIGHLOW at `0x005BA828`, two actual E8 Game status predicates, native 150B renderer update E8 and original return one. **+59 authored game bytes**, 150B wrapper still exact 2/2 local replay. [Evidence](ANIMATION_RENDERER_UPDATE_GATE59_STRICT_EXACT.md). |
| Original 411B recursive Animation retirement staging `0x0044F840` | **411B/116-i386 whole strict exact**, real recursive child-link traversal, staged **57B native append 0x411EA0** distinct from 76B pool insert-after; 18 native E8 and two EH/cookie HIGHLOW, called twice by still NONEXACT 508B update. **+411 authored original bytes**, 1/1 local exact replay. [Proof](ANIMATION_QUEUE_RETIREMENT411_STRICT_EXACT.md). |
| Original 150B Renderer list update lock/forward `0x004497D0` | Native **150B/44-i386 whole strict exact**, true `__fastcall` ECX pool receiver, lock slot9, typed Renderer index at +0x6C8, one original E8 to separate **508B Update still NONEXACT**. All 6 physical E8/3 PE HIGHLOW, **+150 authored game bytes**. [Native proof](ANIMATION_RENDERER_UPDATE150_STRICT_EXACT.md). |
| Correct native 35B Handle child-event bridge `0x0044F0D0` | **35B/15-i386 whole strict exact**; the older 29B `AnimationHandle::interrupt_offset_7` E8 physically targets this new **261B** child event path, *not* older distinct `0x0044EF90` 35B → 246B ordinary interrupt. C++ symbols now faithfully separated and verified, entire Handle chain 8/8 scoped strict. **+35 game-authored bytes**. [PE correction proof](ANIMATION_HANDLE_EVENT_DESCENDANTS_BRIDGE35_STRICT_EXACT.md). |
| Original 261B child event+VM traversal `0x0044EFC0` | **261B/81-i386 whole strict exact**, real `AnimationPoolOwner::resolve_handle` exact 456B, original child-links[1] iterator, native 14 E8/2 HIGHLOW, genuine interrupt and 39,470B **still NONEXACT** VM E8. **+261 game-authored bytes**, original resolver chain scoped 5/5. [Evidence](ANIMATION_POOL_EVENT_DESCENDANTS261_STRICT_EXACT.md). |
| Original 56B/39B Handle live-or-resident and callback pair `0x0044CF10/0x0044F100` | Native **56B/19-i386+39B/15-i386 both whole strict exact**, genuine 51B Handle resolve, authentic resident Animation fallback at pool+0xDC consistent with 138B owner destructor, original callback setter E8 at 0x438A50. **+2 game-authored heads/+95 original bytes**, all 10 Handle sources 10/10 scoped replay. [Proof](ANIMATION_HANDLE_RESOLVE_RESIDENT56_CALLBACK39_STRICT_EXACT.md). |
| Native **138B AnimationPool owner destructor** `0x00449260` | Original **138B/41-i386 whole strict exact + genuine 5B PE INT3** (143/143); fully typed original Worker+4, resident Animation+0xDC, 72B Renderer+0x6C8, 65,536 PooledAnimation array+0x710 and trailing Animation+0x6000818. All actual 6 E8/2 HIGHLOW and correct C++ automatic reverse destruction; **+138 game-authored bytes**, 12/12 scope with Worker and 339B/308B. [Proof](ANIMATION_POOL_DESTRUCTOR138_STRICT_EXACT.md). |
| Original **339B Renderer two-list retirement** `0x0044A3A0` | Whole **339B/106-i386 strict exact**, real +0x18 second `IntrusiveList<Animation>` and both real E8 into accepted 308B pool release. All 19 native E8/4 PE HIGHLOW and six natural compiler NOPs verified. **+339 authored game bytes**, 339B/308B/82B/90B/23B targeted regression 5/5 with 3 objects. [Evidence](ANIMATION_RENDERER_ALL_RETIRE339_STRICT_EXACT.md). |
| Original **308B AnimationPool release Boss** with 82B geometry, 90B membership and 23B STL record index | Four complete source-typed native exact units **308/308+82/82+90/90+23/23**; 11 physical E8/2 HIGHLOW in actual 308B game Boss, pool+0x710 original 65,536x0x600 records, sentinel +0x06000718 and actual `insert_after` free-list operation. **+3 game-authored functions/+480 bytes**; 23B index generic STL uncredited. [Original full proof](ANIMATION_POOL_RELEASE_308_AND_HELPERS_STRICT_EXACT.md). |
| Original **691B RendererPool file-detachment Boss** `0x0044FD30` | Complete native **691B/205-i386 whole strict exact**, two original Animation IntrusiveList 24B group arms per 72B slot, real 29 E8/2 PE HIGHLOW including EH and cookie, byte bit1 filter at Animation+0x4B0 and mark at +0x570. **+691 authored game bytes**; local lifecycle 691B/284B/94B/209B **4/4 original exact**. [Original full evidence](ANIMATION_RENDERER_FILE_DETACH691_STRICT_EXACT.md). |
| Original 209B RendererPool AnimationFile slot release `0x0044C430` | **209B/61-i386 whole strict exact**. Actual `std::array<AnimationFile*,42>` at pool+0x06000730, real original eight E8 and one PE allocator HIGHLOW; source lexical invalid-index branch explains native short jumps rather than 212B near-branch candidate. **+209 authored bytes**, 284B file clear and 94B texture cleanup replay exact 3/3. [Original full proof](ANIMATION_FILE_SLOT_RELEASE209_STRICT_EXACT.md). |
| Real original texture COM/buffer release `0x0044C510` | **94B/33-i386 whole strict exact** with actual Direct3D9 vtbl+8 `Release`, double external-byte guard, PE allocator HIGHLOW and genuine E8, shared pool/File view with 284B `AnimationFile::clear()`. **+94 authored native bytes**, 284B parent recompiled 284/284. [Original proof](ANIMATION_TEXTURE_RELEASE94_STRICT_EXACT.md). |
| Original 284B `AnimationFile::clear()` `0x0044AB00` | **284B/81-i386 whole strict exact** using real native 24B TextureRecord loop, pool detach, texture destruction, three array/three buffer retirements. All **8 genuine E8/8 physical HIGHLOW**, destructor and renderer caller proven. **+284 original game-authored bytes**; native child Renderer detach 691B remains independently source absent. [Original PE/COFF proof](ANIMATION_FILE_CLEAR284_STRICT_EXACT.md). |
| Original complete 922B AnimationFile::spawn Boss `0x00450CB0` | **922B/269-i386 whole strict exact**, real C++20 resource lock/Animation allocation/expected-stem check/script bind/positions/flags/4 renderer creation branches and typed `AnimationHandle` hidden return. All native **20 E8/14 PE HIGHLOW**, original `ret 0x20`, **+922 game-authored bytes**. Existing 83B caller retyped and original 83/83 replayed alongside 922/922. [Whole native proof](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md). |
| Original 83B particle AnimationFile spawn wrapper `0x0045D210` | **83B/30-i386 whole strict exact**, special==1 selects flag16, one original E8 to distinct 922B spawn at 0x450CB0, four physical 2,884B Update E8 sites, no HIGHLOW. **+83 authored game bytes**; enclosing 2,884B parent remains source absent, but 922B callee later became whole exact in CORE/RECON-958. [Original exact proof](ANIMATION_PARTICLE_SPAWN_WRAPPER_83_STRICT_EXACT.md). |
| Original 57B Animation interpolation forwarder `0x0045D150` | **57B/24-i386 strict exact**, real `AnimationBase::interpolation_8c` and native mode 8, one E8 to separately exact 124B setter and two original E8 from the 2,884B Update Boss. **+57 game-authored bytes**; 124B callee replays unchanged. [Original native +COFF proof](ANIMATION_PARTICLE_INTERPOLATION_FORWARD_57_STRICT_EXACT.md). |
| Original 124B interpolation configuration `0x0045D190` | **124B/45-i386 whole strict exact**, six real Vector3 interpolation setters (duration/mode/start/end/tangent pair), current+0x30 and Timer+0x3C; original seven E8 and zero HIGHLOW plus genuine 57B parent E8. **+124 authored game bytes**, Update 2,884B still open. [PE/COFF proof](ANIMATION_PARTICLE_INTERPOLATION_124_STRICT_EXACT.md). |
| Original 20B Vector3×200 native index `0x0045C2C0` | **20B/9-i386 whole strict exact**, natural STL `std::array<Vector3,200>::operator[]`, four genuine E8 from 2,884B Update parent, zero PE relocations. Generated/template source origin unknown: **zero new authored-game bytes**. [Original PE and complete replay](ANIMATION_PARTICLE_GRID_VECTOR_INDEX_20_STRICT_EXACT.md). |
| 200-particle virtual Update Boss `0x0045C360` | **ORIGINAL PE VERIFIED, CANONICAL SOURCE ABSENT / NONEXACT:** entire 2,884B/768-i386 via true vtable, 99 original E8/25 HIGHLOW and 12 INT3. **CORE/RECON-966** now includes temporary read-only Ghidra decompilation and a **whole C++20 research probe** compiling to **2,953B/764 i386 with 99 REL32/25 DIR32**, but still **69B too long and not exact**. Original integer particle stage flags at +0x15E8 contradict legacy float field naming; canonical header remains unchanged pending scoped regression. **Zero authored-game byte credit**. [Typed and original-native frontier](ANIMATION_PARTICLE_GRID_UPDATE_2884_TEMP_GHIDRA_AND_TYPED_FRONTIER.md). |
| Original 51B particle-grid virtual event `0x0045D060` | **ORIGINAL PE VERIFIED, SOURCE NONEXACT**. Event1 forwards 300 at Timer+0x1930 through **0x0045C300 folded 26B wrapper**, not Timer += at 0x4297A0. A private derived clock emits matching 51B but changes the already exact 172B group ctor E8 symbol from native Timer ctor 0x422D90 to a new 23B subclass ctor; rejected. Authoritative class restored, **8/8 existing units replay exact**, zero credit. [Detailed ABI frontier](ANIMATION_PARTICLE_GRID_EVENT51_FOLDED_TIMER_ABI_FRONTIER.md). |
| 200-particle original 92B virtual stop `0x0045CEB0` | **92B/32-i386 strict exact**, original 200-element AnimationHandle resolve/conditional stop flow, 3 original E8 and real vtable 0x56EC14 slot, zero in-body HIGHLOW. Natural direct `resolve()` fixes unwanted 4B compiler local; class-pointer mangling verified. **+92 game-authored bytes**; 5/5 local replay. [Original/native proof](ANIMATION_PARTICLE_GRID_STOP92_STRICT_EXACT.md). |
| 200-particle original 47B create wrapper `0x0045D000` and 31B Timer config `0x0045CFE0` | **47B/18-i386 +31B/12-i386 whole strict exact**, actual marker0x56EC30/process pool0x5B8894, real 156B factory and group Timer+0x1930 reset. Original two-argument RET8 config ignores both values. **+2 authored heads/+78 bytes**, affected-only 7/7 strict replay. [Original full proof](ANIMATION_PARTICLE_GRID_CREATE47_CONFIG31_STRICT_EXACT.md). |
| 200-particle C++17 factory `0x0045C090` | **156B/46-i386 full strict exact**, true `0x1940` operator new, original `/sdl` class autozero, forwarded Animation and independently exact 172B ctor. All 4 native E8/2 HIGHLOW, physical 47B parent; ODR-consistent provisional float/pointer view at `+0x192C` restores original codegen, actual pointer lifecycle unknown. Template origin uncredited. [Full proof](ANIMATION_PARTICLE_GRID_FACTORY156_STRICT_EXACT.md). |
| 0x1940-byte 200-particle native group ctor `0x0045C1F0` and deleting wrapper `0x0045C320` | **172B/46-i386 +49B/18-i386 strict exact** from one natural class, 9 ctor E8/one PE HIGHLOW to real 0x56EC14 vtable, 200 color and 2×200 Vector3, 800B float zero, 3 Vector3 and Timer. **+172 game-authored bytes**, generated 49B uncredited; 156B factory separate. [Native and COFF proof](ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md). |
| 200-cell native color/Vector3 array constructors `0x0045C190/0x0045C130` | Two independent **78B/27-i386 +5 real INT3** complete array constructors, true 200×4B color words and 200×12B Vector3 elements, native C++20 **83/83 each strict exact**. One real 172B group parent invokes color once, Vector3 twice; 172B parent subsequently independently whole exact in CORE/RECON-947. Compiler/template origins review, no authored-game credit. [Original+COFF proof](ANIMATION_PARTICLE_GRID_ARRAYS200_78_STRICT_EXACT.md). |
| 64-point ribbon color-cell array ctor `0x0045DE30` | **75B/27-i386 + five real INT3 whole exact**, true 64×4-byte `AnimationHandle` records, actual original EH/cookie/callback and 103B parent. Full **80/80 compared bytes**, generated origin pending/uncredited. 75B Vector2[64] constructor remains separately open. [Full PE/COFF proof](ANIMATION_RIBBON_TRAIL_COLOR_ARRAY75_STRICT_EXACT.md). |
| 64-point ribbon original gray/magenta creation entry wrappers `0x0045E520/0x0045E550` | **47B/18-i386 and 49B/19-i386 whole strict exact**, both original 2 E8/2 HIGHLOW marker/pool/factory/real configuration, pink returns explicit zero while gray forwards result. **+2 authored heads /96 bytes**, 5/5 local replay. [Whole PE+COFF proof](ANIMATION_RIBBON_TRAIL_WRAPPERS_47_49_STRICT_EXACT.md). |
| 64-point ribbon magenta config Boss `0x0045E3A0` | **382B/113-i386 whole strict exact**, real 11 E8/2 HIGHLOW, original token+0x31C, 64 magenta/blue/alpha cells and Animation layer15/flag1/style64. **+382 authored game bytes**, local 7/7 strict replay. [Complete original proof](ANIMATION_RIBBON_TRAIL_PINK382_STRICT_EXACT.md). |
| 64-point ribbon gray config Boss `0x0045E240` | **340B/101-i386 whole strict exact**, 10 native E8/two HIGHLOW, real 64-point gray/alpha gradient and Animation layer19/flag0. Corrected genuine *unused second argument* to produce original RET8. **+340 authored game bytes**; alternate 382B config also whole exact in CORE/RECON-941. [Strict PE/COFF proof](ANIMATION_RIBBON_TRAIL_GRAY340_STRICT_EXACT.md). |
| 64-point ribbon trail factory `0x0045DD90` | Complete **156B/46-i386 C++17 allocation strict exact**, native 0x320 class new/autozero/forward and already exact 103B ctor, two real wrapper E8, all four E8/two HIGHLOW verified; template provenance unknown, **zero authored-game byte credit**. [Original native proof](ANIMATION_RIBBON_TRAIL_FACTORY156_STRICT_EXACT.md). |
| 64-point ribbon trail draw Boss `0x0045E190` | **165B/53-i386 whole strict exact**, eight authentic E8/three HIGHLOW, true 0x56ED1C virtual draw slot, 64 color/geometry cells, Timer point count and real colored LINESTRIP backend. **+165 game-authored bytes**, 4/4 scoped exact replay. [Original/COFF proof](ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md). |
| 64-point ribbon trail 520B update Boss `0x0045DF80` | **520B/149-i386 whole strict exact**, original 15 E8 + five HIGHLOW and actual alpha decay/64-point polar/cumulative geometry, RNG and Timer. **+520 authored game bytes**, 3/3 affected-unit cold replay; 165B draw subsequently exact in CORE/RECON-938; configuration remains open. [Full PE and strict proof](ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md). |
| 64-point ribbon trail group ctor `0x0045DED0` and deleting wrapper `0x0045DF40` | **103B/28-i386 +49B/18-i386 whole strict exact**, true 0x320 object and 0x56ED1C vtable, two independent 64-element arrays and Timer +0x30C. **+103 authored game bytes**; 49B generated wrapper uncredited; 520B update later accepted in CORE/RECON-937, 165B draw still open. [Complete original/COFF proof](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md). |
| 123B solo-ribbon palette Boss `0x0045DBF0` | **123B/39-i386 whole strict exact**, five real native E8/one HIGHLOW, three genuine NOPs, real `0x80FFFF80` first-cell override and original 32.0f radius. Original 182B parent call independently checked. **+123 authored game bytes**. [Complete native proof](ANIMATION_RIBBON_SOLO_PALETTE_123_STRICT_EXACT.md). |
| 182B solo-ribbon config Boss `0x0045DB30` | **182B/57-i386 whole strict exact**, 7 original native E8/zero HIGHLOW, actual 0x3DC token, Timer+0x3CC, real 23B segment index and 123B palette child, Animation position/layer/style/flag. **+182 authored game bytes**; palette child separately accepted in CORE/RECON-935. [Whole native proof](ANIMATION_RIBBON_SOLO_CONFIG_182_STRICT_EXACT.md). |
| 47B solo-ribbon create wrapper `0x0045DC70` | **47B/18-i386 strict exact**, real native marker 0x56ECC0 and process allocator 0x5B8894, original E8 to exact 156B allocation and separate 182B config. **+47 authored game bytes**; 182B remains independent. [Whole proof](ANIMATION_RIBBON_SOLO_WRAPPER_47_STRICT_EXACT.md). |
| Solo ribbon 156B C++17 factory `0x0045D2C0` | **156B/46-i386 original allocation whole strict exact**, genuine 0x3E0 new/autozero, 4 native E8/2 HIGHLOW and real 89B ctor. Natural polymorphic `class`/pointer ABI triggers actual `/sdl` clearing; eight affected providers replay 9/9. Template origin unresolved, **zero game-authored credit**. [Native original/COFF proof](ANIMATION_RIBBON_SOLO_FACTORY_156_STRICT_EXACT.md). |
| Solo ribbon 89B group ctor and 49B deleting wrapper | **89B/25-i386 original polymorphic group ctor strict exact** with actual 0x56ECA4 vtable, 0x3E0 size, inherited base/78B array/Timer; **49B native scalar deleting wrapper** also whole exact. **+89 authored game bytes**; 49B compiler origin unknown and shared folded 20B destructor uncredited. [Complete PE/COFF proof](ANIMATION_RIBBON_SOLO_GROUP_CTOR_89_DELETE_49_STRICT_EXACT.md). |
| Solo ribbon single-segment array ctor `0x0045D550` | **78B/27-i386 +5 genuine `INT3` whole strict exact** with actual count1/stride0x3C0, native EH/60B element callback. One C++20 provider reproduces 83/83 complete bytes. Template source origin unproven; **zero authored game credit**. [Whole original and canonical proof](ANIMATION_RIBBON_SOLO_ARRAY_CTOR_78_STRICT_EXACT.md). |
| Original solo ribbon 697B dynamics Boss `0x0045D780` | **697B/190-i386 whole strict exact**, 17 real E8/13 HIGHLOW, two random 60-cell passes, native color byte+2, radius ±limit/4, polar 2π/58 and vertex1→59 close. **+697 authored game bytes**, 5/5 affected solo strict replay. [Original/whole PE+COFF proof](ANIMATION_RIBBON_SOLO_DYNAMICS_697_STRICT_EXACT.md). |
| Solo ribbon 76B TRIANGLEFAN renderer | Complete **76B/27-i386 strict exact**, real 60-point fan, +0x1E0 packed-color stream, all three physical E8/one HIGHLOW, genuine native 156B parent E8; **+76 authored game bytes**. [Original + strict proof](ANIMATION_RIBBON_SOLO_FAN_76_STRICT_EXACT.md). |
| Solo ribbon virtual draw Boss `0x0045DA40` | Complete **156B/53-i386 strict exact**, original independent 0x56ECA4 vtable, seven E8, two HIGHLOW, genuine +0x42 scope NOP, one 0x3C0 segment. **+156 authored game bytes**, separate 76B fan now also strict exact; the 697B dynamics became whole strict exact in CORE/RECON-929. [Whole original/COFF proof](ANIMATION_RIBBON_SOLO_DRAW_156_STRICT_EXACT.md). |
| Separate one-segment ribbon update Boss `0x0045D6F0` /end `0x0045DCE0` | **140B/46-i386 update and 19B/9-i386 end strict exact**, real distinct vtable 0x56ECA4, Timer +0x3CC and 0x3C0 stride. **+140 authored game bytes**, 19B template origin unknown. The 76B renderer was accepted independently in CORE/RECON-928; the 697B updater was later whole strict exact in CORE/RECON-929; 156B draw has now been independently accepted in CORE/RECON-927. [Complete original proof](ANIMATION_RIBBON_SOLO_UPDATE_140_END19_STRICT_EXACT.md). |
| Native C++20 `std::fill_n` color/radius `0x0045D430`/`0x0045D360` | **123B/45-x86 and 202B/73-x86 whole strict exact**, authentic unsigned `jbe`, all 11 native E8/two HIGHLOW original roles and actual 31B callers. Template origins unknown, **zero authored game credit**. [Whole PE/COFF proof](ANIMATION_RIBBON_FILL_N_123_202_STRICT_EXACT.md). |
| Ribbon color-array constructor `0x0045D4B0` | **75B/27-i386 + five real INT3 strict exact**, original 60×4-byte `AnimationHandle` array and 60B parent constructor call, all native EH/cookie/callback/E8 roles. 80/80 full contribution; compiler/template origin unverified and **zero authored game credit**. The separate 75B Vector2[60] ctor remains open. [Whole PE/COFF proof](ANIMATION_RIBBON_COLOR_ARRAY_75_STRICT_EXACT.md). |
| **Ribbon segment palette `0x0045EC10`, 88B** | **88B/29-i386 whole strict exact**, two real 31B color/radius forwarding children 31/31 exact; +0x2C/+0x51 native NOP, three original E8/one physical HIGHLOW 32.0f, three real 252B caller E8. **+88 game authored bytes**; 31B helpers origin unknown/uncredited. [Full source/PE/COFF proof](ANIMATION_RIBBON_PALETTE_88_31_STRICT_EXACT.md). |
| **Polygon outline caller `0x0045FAA0`, 104B /36 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationPolygonMotionCall104.cpp` (102B /34 x86); original saves ESI and computes a stride before `Motion::position_ref`, whereas source computes it afterward. Eight source indexing variants did **not** fix it. Its 233B caller and 1,204B callee **are exact**, independently. [Caller frontier](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md). |
| **Rotated four-corner projection `0x0043EF20`, 1,486B /372 x86** | **WHOLE STRICT EXACT**: **1,486/1,486**, real original `+0x41` NOP from natural post-Angle lexical scope; all **13 E8/9 HIGHLOW** true original roles and 96B source-owned corner table. **+1,486 authored game bytes**, 985B exact sibling still 985/985; original physical WindowState scale has 0x20C0 COFF addend. [Whole new proof](ANIMATION_CORNER_ROTATED_1486_STRICT_EXACT.md), [earlier nonexact investigation](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md). |
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
| Ribbon C++17 allocation factory `0x0045E5D0` | **156B/46-i386 whole native strict exact**, genuine 0xB60 allocation, `__autoclassinit2`, folded `std::forward`, real exact 89B group constructor, four original E8 and two HIGHLOW. Pointer-bearing +0xB5C natural type is compiler-corroborated, historic name/ownership unresolved; zero authored credit. Nine affected cold objects, eleven units **11/11 exact**. [Full original PE and native proof](ANIMATION_RIBBON_GROUP_FACTORY_156_STRICT_EXACT.md). |
| Ribbon polymorphic group ctor `0x0045E6D0` plus generated destructor pair | **89B/25-i386 whole native strict exact**; original 0x56EDDC derived vtable, 3x0x3C0 array and Timer/float/tail members. Separate **20B ordinary folded destructor and 49B scalar-deleting wrapper whole strict exact** but excluded from authored game credit. **+89 game-authored bytes**; local 8 affected object/10 unit cold replay. [Entire native proof](ANIMATION_RIBBON_GROUP_CTOR_89_STRICT_EXACT.md). |
| Ribbon 252B config Boss and 23B segment index helper | Original **252B/77-i386 game-specific configuration** and complete **23B/9-i386 array index**, both whole strict exact. Eleven true native E8, zero HIGHLOW; **+252 authored game bytes**, 23B likely template uncredited. The separate 88B palette child was subsequently accepted whole exact in CORE/RECON-923. [252B whole native proof](ANIMATION_RIBBON_GROUP_CONFIG_252_STRICT_EXACT.md). |
| Ribbon allocation/configuration CDECL wrapper `0x0045EC70` | **47B/18-i386 whole strict exact**, native type marker/allocator global and real 156B factory/252B group configure E8; **+47 authored game bytes**. [Complete proof](ANIMATION_RIBBON_CONFIG_WRAPPER_47_STRICT_EXACT.md). |
| Ribbon three-segment array ctor `0x0045E670` | **78B/27-i386 plus five genuine `INT3` whole strict exact**, real 3×0x3C0 C++20 array, independent EH-vector callback to 60B ctor. Compiler/STL attribution unknown, no new authored-game credit. [83B full proof](ANIMATION_RIBBON_SEGMENT_ARRAY_CTOR_78_STRICT_EXACT.md). |
| Ribbon 60B segment constructor `0x0045D610` | **60B/20-i386 whole native exact**, real 60 Vector2/60 `AnimationHandle` word arrays, 60-float zeroing and actual original 78B parent callback; **+60 game authored bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_CTOR_60_STRICT_EXACT.md). |
| Ribbon segment dynamics Boss `0x0045E800` | **538B/149-i386 whole strict exact**, actual 60 radii/60 Vector2 loop, signed RNG, clamp +/-4, polar step 2*pi/59, authentic scope NOP and vertex 59 closure. Independently **13 E8/10 HIGHLOW** original physical roles. **+538 authored game bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md). |
| Ribbon segment LINESTRIP wrapper `0x0045EAC0` | **76B/27-i386 whole native exact**, genuine `+0x1E0` color stream, 60-point primitive, all three original E8/one HIGHLOW roles and original 156B parent E8 confirmed. **+76 authored game bytes**. [Whole native proof](ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md). |
| Ribbon/polygon virtual draw Boss `0x0045EA20` | **156B/53-i386 whole native strict exact**, seven real E8/two HIGHLOW, three original 0x3C0 segments and genuine native scope NOP. **+156 authored game bytes**. [Complete native proof](ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md). |
| Separate ribbon/polygon update Boss `0x0045E770` | **140B /46-i386 whole native exact**, independent 0x56EDDC vtable, real 3x0x3C0 segments, six physical E8 and Timer +0xB4C; **+140 newly credited authored game bytes**. Its 19B array end remains strict exact and origin unproven; 538B update child and 156B draw were subsequently whole-exact at later checkpoints. [Complete native proof](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md). |
| Original polygon group construction Boss | **113B/30-i386 whole native strict exact**, genuine `AnimationCallback` base/vtable, 78B segment array, Timer/Vector3. **49B compiler scalar-deleting wrapper also strict exact**; the shared original physical 20B ordinary destructor has since been matched as a folded contribution from the ribbon-group class; unique polygon-class destructor source ownership remains unproven. [113B/49B proof](ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md). |
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

The original 89B ribbon constructor now preserves all six real vtable entries
and generates the 49B deleting wrapper plus the folded 20B ordinary destructor
without breaking the 140B/156B virtual methods.
[Complete proof](ANIMATION_RIBBON_GROUP_CTOR_89_STRICT_EXACT.md).

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

Original three **75B Vector2[60]/[64]/[61] position array constructors** remain **NONEXACT**, despite independently verified native boundaries and diagnostic `noexcept`/MSVC 80B structural matches. The 60/64 packed-color array constructors and 123B/202B C++20 `std::fill_n` helpers are separately already whole strict exact; do not count them again. A real `Vector2() noexcept` header change would impact **230 canonical source providers /871 strict units** and requires careful affected-closure regression proof, not blind admission. [Full original ABI frontier](ANIMATION_VECTOR2_ARRAY_60_64_61_NOEXCEPT_FRONTIER.md).

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
