# TH20 reconstruction — current handoff

**Current: 2026-10-29, after CORE/RECON-624.** This is a live navigation
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
| Source-present mappings | **1,183** |
| Strict canonical complete native units | **1,184** |
| Unique canonical MSVC object/receipt providers | **243** |
| Exact game-authored whole original functions | **498**, covering **175,709 original body bytes** |

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

## Twenty-one complete ECL/Bullet/Animation game-owned original roots — 6,836B exact

**CORE/ORIGIN-555:** Independently revalidated and origin-admitted **21
complete original ECL/Bullet/Animation/GameConfig/Item/Player/Archive
functions**, each **251–556B**, totaling **6,836 disjoint original
project-authored bytes / 1,829 native i386 instruction heads**.
These are existing real game source and pinned strict canonical units,
not a claim of writing 21 new C++ functions. Whole game methods include
the **556B EclFileLoader::load**, 473B Configuration constructor,
440B PlayerOption, 413B PlayerShot, 386B BulletController, 348B Card,
330B Item controller, 312B EnemyController, four 272B recursive
Animation child/flag updates, 287/261B ECL float argument/consume,
265B ScriptStack push, 284B game LZSS match-tree insertion, 255B
ShotMetadata and 251B Enemy lookup.

Original-game provenance is independently confirmed by real **11,110B
whole-exact EclRuntime::tick** (35 float operand and 45 stack-push E8s),
original 41,967B Enemy ECL opcode calls, real exact 1,036B Archive
compressor, Player/Graphics/Animation/Session owners, and original
73–92B constructor wrappers. **13** functions have high-confidence
original gameplay callers; **eight** retain medium confidence
because of anonymous original constructor wrappers or missing native
direct E8 (not assumed absent from the game's runtime). All **187
original E8 and 62 PE HIGHLOW fields** are original-PE-attested,
with every remaining byte exact. The entire original C++ comparison
spans **6,876B**, but **40 compiler CC/alignment bytes** are
not double counted as game function-body credit.

Only **14 real C++ source/object providers** were cold rebuilt under
their existing compiler profiles; **122/122 affected old strict units
replayed exact**. No changes to those C++ sources or public headers,
no global cold replay. [Complete original PE/caller provenance](ECL_BULLET_ANIMATION_6836_EXACT_ORIGIN_AUDIT.md).
Authored exact grows **476 / 168,855B -> 497 / 175,691B**;
source-present mappings **1,181**, native canonical units **1,182**
and compiler object providers **242** remain unchanged. The enclosing
**41,967B Enemy ECL dispatcher remains NONEXACT**; original direct E8
child calls do not prove the whole parent or linked game runtime.

## Player 3,111B whole main frame: original postfix Timer E8 corrected

**CORE/RECON-557:** Independently original-PE decoded E8 at
`0x004F9CBC` directly calls **22B `Timer::operator++(int)`**
`0x00423540` (real push-zero and native `ret 4`), whereas the prior
maintained source's `++timer_2070` wrongly called the distinct
**20B prefix** `0x00429400`. Repaired real source to
`timer_2070++;`, with no fake shim or altered original callee.
Complete locked i386 compiler output is **3,254B / 808 heads**
against original 3,111B / 783, with **733/783** original ordered
mnemonic heads aligned versus 730 before this correction. Original
67 E8/37 PE HIGHLOW and candidate 67 E8/37 DIR32 still match by
**count only**, not full original positions/bytes. New native call
identity census shows **60/67 known physical call identities matched
in order**; original 45B effect-handle equality vs source inequality
is a real independent call mismatch requiring valid C++ owner type
work, not an undefined reinterpret cast. Twenty focus-lifetime probe
variants failed to improve this whole-body codegen and remain private.
[Exact original source ABI/call comparison](PLAYER_MAIN_TIMER_POSTFIX_3111_NATIVE_ABI.md).
The 3,111B parent and its separate 555B movement child both remain
**NONEXACT**, zero new exact bytes. Only noncanonical
`src/PlayerMainFrame.cpp` was edited; no existing strict unit or
public header was touched, so no unrelated cold replay was performed.

## Bullet emitter 3,735B: four real native E8 game calls restored, 18B script leaf exact

**CORE/EXACT-563 / CORE/RECON-563:** Entire original game-native
`0x004856C0` 18-byte `type_to_script(int)` now has whole-source
**18/18 strict canonical exact** in existing `src/BulletStyle.cpp`.
Its independent original PE HIGHLOW field at `0x004856CC` targets
the real BulletStyle table `0x005C06A8`; original Bullet emitter
`0x00482297` calls it directly. The entire maintained 3,735B Bullet
emitter also now restores original `Animation::reset()` E8 at
`0x00482252` and both physical **24B** Bullet color assignment calls
at `0x00482390` and `0x00482481`. The latter share the original
`0x0045D650` physical whole 24B code with already exact
`PackedColor::operator=(uint32_t)`, so the new type-safe
`BulletColor::operator=` source contributes **zero duplicate native
bytes**. All four call positions/destinations were independently read
from original immutable E8 x86 operands, not compiler candidate
references.

The full C++ emitter source now emits **3,561B / 904 x86 instructions**
with **809/935 ordered native mnemonic kinds aligned**, and **57
real source direct E8** versus the original 60; it remains a
**NONEXACT** 3,735B whole parent. The header dependency closure was
frozen before changing `Bullet.hpp` and `BulletStyle.hpp`:
**32 actual MSVC source providers / 71 previous strict original units**.
All were freshly cold built under unchanged native compiler profiles.
Six compiler-private `$SG` name renumberings were independently
original-PE site/target/full-payload attested; only private label
spellings changed. Final **72/72 whole native units**, including the
new 18B unit, strictly replay exact in those 32 existing compiled
objects. The original game exact count rises to **498 / 175,709B**,
canonical native units to **1,183**, mapped whole-source units to
**1,182**, compiler objects stay **242**.
[Full original PE E8/HIGHLOW, folded typed alias, whole emitter frontier
and 32-object scoped strict proof](BULLET_EMITTER_REAL_CALLS_18_EXACT_RECONSTRUCTION.md).
No global cold replay or whole linked game/runtime claim.

## Bullet emitter 3,735B — native signed opcode-1, original cross-Context file and game math

**CORE/RECON-571:** The maintained whole game Bullet emitter
`src/BulletEmitter.cpp` now restores original **cross-Context child
Animation file** selection (E8 `0x00482310 -> 0x0040C300`), native
ellipse **`geometry::norm_xy` and `scalar_math::arctangent`** calls
rather than CRT hypot/atan2, original **`absolute(sine)`** wave speed
instead of signed sine, additive old heading and **subtractive
Vector3::operator-=`** on the first opcode-1 command velocity step.
The original opcode-1 branch also reads a signed **16-bit** event
field with original `movsx word` at `0x004825F1/0x00482624`, and uses
**three separate** native pmr::vector index calls at `0x004825C4`,
`0x004825EC`, `0x0048261F` instead of a cached two-call
`BulletCommand&`. These changes correct real gameplay semantics
and actual original `E8` callee identities, not only code shape.
The original Context getter has genuine **16/16B** typed source
physically folded with already exact original `0x0040C300` (no
duplicate authored bytes). [Complete original-PE E8, signed
operand/movement and whole-source evidence](BULLET_EMITTER_3735_COMMAND_AND_MATH_GAMEPLAY_CORRECTION.md).
The one source object was freshly compiled with the locked local C++
profile, giving **3,628B / 919 native candidate instructions,
828/935 original ordered mnemonics aligned**, up from
3,561B/904/809. **60 candidate E8 vs 60 original E8 by count only**:
the original old-STL `std::move` E8 at `0x00481989` is still absent
and the original 63B legacy shared_ptr move-assignment implementation
still differs. Entire **3,735B original parent remains NONEXACT**,
and the distinct 12,140B Bullet dispatcher is also nonexact. No
previous native exact units are configured in modified
`src/BulletEmitter.cpp`, no shared headers/accepted sources were
changed and **no full cold replay** is relevant. Exact inventory
remains **498 complete game bodies / 175,709 original bytes**, with
1,183 strict units and 242 source objects.

## Old MSVC STL shared_ptr move assignment: complete 63B native exact, library only

**CORE/STL-577:** The full original library-support
`std::shared_ptr<EtamaArgInf>::operator=(shared_ptr&&)` at native
`0x0047C530`, **63B / 23 complete x86 instructions**, now has a
strict **63/63 exact native C++20 compatibility translation unit**
`src/ShotSharedPtrMoveLegacy.cpp`. Its actual historical expression
`shared_ptr(std::move(other)).swap(*this)` creates an **anonymous
move temporary**, not the earlier incorrect named `temporary` local.
A narrow, typed noninlined old `std::move` source-level specialization
reproduces the original **8/8B** physical wrapper at `0x0040B280`,
already canonical via another folded source; it is not credited again.
All **four original PE E8** callee targets and **47/47 other native
bytes** match independently, with **zero PE HIGHLOW** fields. The
original STL 63B method is now a real **single-source canonical strict
unit** with fresh locked MSVC `/GS- /sdl-` compilation and **1/1
scoped strict replay**. It is **library/compiler origin**,
`disposition=exclude`, deliberately **not** new authored-game exact
credit; standard-library specialization/whole linker ODR behavior
is still unverified. [Native PE/COFF, anonymous temporary ABI
and library classification proof](SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md).

Canonical native units **1,183 → 1,184**, unique actual compiler
providers **242 → 243**, source-present mappings **1,182 → 1,183**.
**Game-authored exact remains 498 whole originals / 175,709B**.
The entire **3,735B Bullet emitter parent remains NONEXACT**:
its own legacy `std::move` call in that translation unit and final
whole-program template/COMDAT selection have not been restored.
No public-header edits or global cold replay.

## Bullet emitter 3,735B — all 60 original physical E8 call targets now align

**CORE/RECON-583:** The complete maintained Bullet emitter source
`src/BulletEmitter.cpp` has now been corrected to emit **every one of
the original 60 native E8 physical callee identities, in the exact
original x86 E8 order**. Unlike the older 60/60 *count-only* result,
the independent immutable PE source decoder resolves all original
60 signed relative E8 destinations and compares them to the
*actual maintained C++* original COFF symbol roles one-by-one:
**60 original physical call identities correct, 0 wrong, 0 unmapped**.
Original physical folded aliases at `0x0040C300`, `0x0045D650`,
`0x0040B280` and original 134-source-confirmed MSVC cookie callee
`0x005429EE` were independently corroborated; none adds duplicate
game-authored original code credit.

The new real C++ source forwards the concrete old-STL 8B `std::move`
and whole exact **63B shared_ptr move-assignment** symbols through
the separate already strict `ShotSharedPtrMoveLegacy.cpp` library
provider, so original `0x00481989` and `0x0048199B` E8 calls now
both emit naturally. The original native **out-of-range**
`0x004825A5` and **non-opcode-1** `0x004825CD` branches share one
`Animation::interrupt(2)` error E8 at original `0x004826AC`;
the old C++ emitted two separate failure E8 calls, now merged with
one real natural `if (... && ...) else interrupt(2)` branch.

Current full codegen: **3,609B/914 instructions, 831/935 original
mnemonic kinds aligned**, versus original **3,735B/935**. **Whole
parent still NONEXACT**: physical E8 positions, nonrelocated bytes,
legacy exception state and native 13+11 switch-label tables are not
yet identical. This is a *complete correct original call graph* proof,
not a whole-body exact claim or successful linked executable.
[Complete original E8 60/60 ordinal target audit and whole C++
source ABI evidence](BULLET_EMITTER_60_ORIGINAL_E8_CALL_IDENTITY.md).
Only `src/BulletEmitter.cpp` was changed; it has **zero previously
accepted strict canonical units**, so only its whole locked source
was cold compiled, **no global cold replay**. Game authored exact
stays **498 whole functions / 175,709B**, canonical units **1,184**,
source-present **1,183**, real compiler providers **243**.

## Original odd-first Bullet emitter shooting parity restored — 875/935 native heads

**CORE/RECON-587:** Native original Bullet emitter `0x004818E0`
uses **odd-first** game shot parity checks for both modes 0/1 and
9/10. Original `+0x1AD je +0x1CD` on `ShotParameters::count` and
`+0x48A je +0x4FE` on `ShotParameters::rows` branch to the
**second** even path, leaving the real odd path as the first
fallthrough. The prior maintained C++ reversed both branches:
it was numerically equivalent for ordinary inputs, but the locked
`/Od` native control flow was opposite. Restoring original
`if (shot.count & 1)` and `if (shot.rows & 1)` with the correct
branch bodies and signed-half/rate arithmetic improves complete
**3,735B parent original mnemonic alignment from 831/935 to
875/935**, in fresh complete source recompilation. Actual candidate
size **3,609B/914 instructions**, E8 source count **60** unchanged;
independent immutable-original PE audit confirms **all 60/60
physical original E8 callee identities still match in order** after
source correction. Four full-source parity variants prove the
alignment improvement is due to **real native branch shape** and
not shorter prefix or fake compiler flags. [Complete native x86
and four whole-compiler proof](BULLET_EMITTER_3735_PARITY_BRANCH_875_NATIVE_FRONTIER.md).
The original 3,735B/935 whole method is STILL **NONEXACT**:
its machine bytes, source stack lifetimes, EH/13+11 switch tables
and relocation **sites** differ; E8 destination agreement does not
prove full source equality. Only noncanonical
`src/BulletEmitter.cpp` was compiled, with zero existing strict units
in that source and no public header change; no unrelated cold replay.
Game-authored exact stays **498/175,709B**, canonical units **1,184**,
compiled providers **243**.

## Bullet emitter 3,735B — six native SSE pi×2 groups and three angle-accumulation orders

**CORE/RECON-594:** Following the separately accepted odd-parity branch
source correction CORE/RECON-587, independent immutable PE x86 audit
confirmed **three original cumulative floating angle orderings** in
modes 2/3, 4/5 and 7, **six genuine `pi*two`-before-column SSE
triples**, two separately initialized original speed stack locals
and independent unsigned 16-bit metadata mode re-reads at method
`+0x223` and `+0x596`. The maintained entire emitter's natural C++
now reproduces these original operations and evaluates floats in
original IEEE source order. The pinned full native source generates
**3,685B /930 x86 instructions, 911/935 original ordered mnemonic
heads aligned**, versus earlier 3,609B/914/831 (and separately
committed odd-first 3,609B/914/875). All **60/60 immutable original
physical E8 callee identities remain correct in native ordinal order**.

**The original 3,735B/935 parent remains NONEXACT**: current 50B and
five net instructions short, original E8 byte positions, remaining
register/stack SSE code, 13+11 native switch-table labels and EH
lifetime not yet fully identical. No parent exact-byte credit.
Only the noncanonical `src/BulletEmitter.cpp` C++ was cold compiled;
there are **zero previously accepted strict units** in that source,
no public header/accepted source changed, and no global cold replay.
[Complete six native SSE groups, mode math/stack source proof](BULLET_EMITTER_3735_ORIGINAL_FLOAT_ORDER_911_FRONTIER.md).
Current exact authored totals unchanged **498 /175,709B**, canonical
units **1,184**, source mappings **1,183** and compiler providers
**243**.

## Bullet emitter 3,735B — original cancel-script table, native metadata fields and uncached styles

**CORE/RECON-605:** The immutable TH20 game PE contains an original
**eight-element writable 32-bit cancel-script lookup table** at
`0x005AEFF8` containing exactly **6,10,14,18,22,26,30,36**,
followed by a distinct packed-color palette at `0x005AF018`.
Original emitter cancel mode 1 reads this table at native instruction
`+0xAFA` / **PE HIGHLOW field `+0xAFD`**, while the previous
source incorrectly used the raw shot color index. The newly typed
`bullet_cancel_scripts_by_color[8]` C++ `.data` section independently
matches **32/32 original PE bytes**. Original whole emitter
**45 native code PE HIGHLOW plus 24 native switch-label HIGHLOW**
fields total **69**; with this missing real table reference restored,
the C++ object has **69 DIR32 fields by count**, not yet original
field-offset/target exactness.

The original also recomputes native `0x158`-stride BulletStyle on
successive uses instead of a cached `BulletStyle&`. Two mode6
palette accesses use **signed16 stored `Bullet+0x4C` type** (`movsx`
at `+0xB48/+0xB74`) and 32-bit ShotParameters.color index. Actual
`Bullet+0x40 <- ShotMetadata+0x40`, zero `Bullet+0x3C`, then
`Bullet+0x38 <- full 32-bit ShotMetadata+0x44` repair real wrong
metadata fields and missing game state reset. One native x87 radius
value is stored, then MOVSS writes Bullet size **Y before X**.
The native uint16 ECL mode switch consumes the direct owner value
without the previous extra named uint32 switch copy.

Complete pinned C++ source now compiles to **3,742B / 938 x86 heads,
928/935 original ordered mnemonic heads**, vs original 3,735B/935.
All **60/60 original physical E8 callee identities still match in
original ordinal order**. The 3,735B parent remains **NONEXACT**:
7B/3 net instructions longer, original call/relocation field sites,
compiler EH/SSE stack and 13+11 switch table code labels still
differ; **zero new authored original-body credit**. Only
`src/BulletEmitter.cpp` was modified and compiled, with no shared
header or previously canonical exact units affected; no global
cold replay. [Independent original PE `.data`/HIGHLOW proof, source
semantics and whole C++ frontier](BULLET_EMITTER_3735_CANCEL_TABLE_AND_METADATA_928_FRONTIER.md).
Authored original whole exact remains **498 functions / 175,709B**,
canonical strict units **1,184**, source mappings **1,183**,
compiled providers **243**.

## Bullet emitter 3,735B — real 16-bit row mask and direct Player reference ABI

**CORE/RECON-615:** Complete original Bullet emitter's native
`+0x4BF` and `+0x53F` are actual **6-byte `and r32,0x0000FFFE`**
instructions, unlike earlier C++ `&~1` emitting 3-byte
`and r32,0xFFFFFFFE`. This changes real game row speed indices for
out-of-range/negative values, not just compiler byte counts. The
current source uses `&0xfffe` twice and emits both complete original
6-byte instructions with actual native opcode/imm bytes. Also,
Player-position squared-distance receives `context->player()->position_ref()`
**directly**, as original E8 returns EAX and is immediately pushed,
not through a compiler-only const-reference stack temporary.
Removing two original-absent `mov` instructions takes 12B away.
[Independent original PE, full C++ and negative NOP experiments](BULLET_EMITTER_3735_NATIVE_ROW_MASK_AND_PLAYER_DIRECT_ABI.md).

Current entire maintained game C++ **3,736B/936 x86 instructions**
versus immutable original **3,735B/935**; original ordered
mnemonic score remains 928/935. Full original game compiler section
is **3,832B** and current COFF section also **3,832B**. The
**60/60 native physical original E8 callee identities remain correct
in original ordinal order**. However only the **first 11** E8 field
offsets are identical; the subsequent **49** original E8 sites
are shifted **+1 byte** in candidate because of a single extra
`nop` after the second Timer float setter at game relative `+0x112`.
Both original and candidate have 69 whole code/table absolute
references **by count**; physical offsets, original stack/SSE values,
EH and switch-label destinations still differ. **Entire parent
remains NONEXACT**, with zero new accepted authored game code bytes.

Private whole-function MSVC tests moving base-speed declarations to
ten positions and changing Timer assignment and rows predicates in
fifteen variants all failed to naturally eliminate that NOP. We
deliberately did **not** patch machine bytes, inject assembly or
label the parent exact. Only noncanonical `src/BulletEmitter.cpp`
changed; no previous strict units are configured in it, no public
header edits or whole-graph cold replay. Current exact authored
stays **498 /175,709B**, native strict units **1,184**, mapped
functions **1,183**, compiler providers **243**.

## Bullet emitter 3,735B — original RNG/x87 return lifetimes now 934/935 aligned

**CORE/RECON-624:** The original entire Bullet emitter contains **six**
real `fstp` return-local → ShotParameters pointer `mov` → SSE `movss`
chains at relative `+0x357/+0x389/+0x40C/+0x439/+0x612/+0x63A`.
The old source fused RNG/cosine/sine calls with ShotParameters member
arithmetic and reversed their actual original float return lifetime.
The maintained C++ now independently stores real game RNG angle in
mode6, RNG speed in mode7, both angle and speed in mode8, and native
cosine/sine returns in mode11. Entire pinned MSVC native codegen:
**3,736B /936 instructions, 934/935 original mnemonic heads aligned**
(up from 928). The all-source **60/60 original physical E8 callees**
remain correct in native ordinal order; original and CXX whole code
plus table contributions both have **3,832B** and 69 absolute fields
by count only. [Complete original PE x87 result chain and source
compiler proof](BULLET_EMITTER_3735_X87_RETURNS_934_FRONTIER.md).

The original mode12 `absolute(sine(...))` value reloads its x87
float BEFORE the ShotParameters pointer; current ordinary C++ does
the reverse and has a seventh nonoriginal `fstp`→pointer→`movss`
ordering. Adding an unsupported `volatile` could align 935 mnemonic
kinds but is rejected without original source evidence. The one
compiler-only `nop` at +0x112 remains, shifting 49 E8 sites +1B;
EH/stack/switch-label bytes are also nonexact. Entire **3,735B boss
remains NONEXACT**; only `src/BulletEmitter.cpp` (zero existing
canonical exact units) was compiled; no header change or global
cold replay, no new authored game exact bytes.

## Actual open whole-function bosses (priority, NOT exact)

| Native address / original bytes | Known C++ / exact frontier | Immediate next investigation |
| --- | --- | --- |
| `0x004FFA10` **555B** Player movement | `src/PlayerMovement.cpp` emits **561B / 136 instructions** against 555B/135; [original movement frontier](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md) | Recover one extra SSE y-bound float spill through real source lifetime/ABI, not artificial locals. |
| `0x004F9C30` **3,111B** Player main frame | [Complete typed C++ source](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md) with [current original gameplay/call ABI correction](PLAYER_FRAME_3111_GAMEPLAY_ABI_CORRECTION.md): **3,254B/808 instructions, 733/783 original mnemonic heads aligned**. Real two EnemyController getter calls and separately computed two native sprite scale float args. Candidate **67 E8 + 37 DIR32** now matches original **67 E8 + 37 HIGHLOW by count**, after removing mistaken `/sdl` cookie. | **NONEXACT**: original 3,111B/783 and candidate code/relocation positions still differ; separate 555B Player movement and handle equality/folded ABI remain unresolved. No exact parent body credit., [original Timer postfix E8 and remaining handle equality ABI](PLAYER_MAIN_TIMER_POSTFIX_3111_NATIVE_ABI.md) |
| `0x0047DB70` **273B** Bullet group drawing | `src/BulletDrawGroup.cpp` emits 283B/84 vs 273B/82; [typed original drawing ABI](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md) | Two extra native SSE spills remain. Parent `draw_groups` 81B is already exact. |
| `0x004818E0` **3,735B** Bullet emitter | [Six original RNG/cosine/sine x87 return lifetimes](BULLET_EMITTER_3735_X87_RETURNS_934_FRONTIER.md) yield current **3,736B/936 C++ instructions, 934/935 original mnemonic heads aligned**, all [60 real original physical E8 targets in order](BULLET_EMITTER_60_ORIGINAL_E8_CALL_IDENTITY.md). | **NONEXACT**: case12 original float reload order, extra +0x112 compiler NOP, 49 E8 field offsets +1B, EH/SSE and 13+11 original native switch tables differ. No whole-parent exact credit or global cold replay. |
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
