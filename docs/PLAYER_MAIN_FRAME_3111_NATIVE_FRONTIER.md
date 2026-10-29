# CORE/RECON-432 / CORE/EXACT-433 — full original 3,111B Player frame call graph and two exact native callees

**CORE/RECON-508 correction:** The 3,111B Player main-frame method is now [source-present but NONEXACT](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md). Original InputInf `for_view` returns a signed integer used to index `process_input_views[4]`; historical `InputInf+0x2E30` pointer claims below were mistaken. The earlier complete original callgraph/child exactness evidence stays valid. See the independent [signed-index proof](INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md).


Immutable original: Japanese TH20 v1.00a Steamless executable,
whole SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The complete 3,111-byte enclosing Player main-frame routine remains
NONEXACT.** The present work independently audits its *whole original*
machine-code flow and closes two separate game-owned methods it
actually calls. No bytes of the 3,111-byte parent are credited
by exactness of its children.

## Complete original 3,111-byte body and corrected identity

The original physical interval `0x004F9C30..0x004FA856` contains
**3,111 bytes / 783 fully decoded i386 instructions**, SHA-256
`7f0bff5c2e175ff3d223c9e958fd908e39016b136fd1ff0eb0e1ce0cf6672467`.
Independent native E8 displacement decoding yields **67 direct call sites**
to **36 unique native addresses**; the original PE `.reloc` section
has **37 original HIGHLOW absolute fields** in this entire function.
Each site and target is recorded in
`.analysis/core432-player-main-native-original-callgraph.json`.

**Critical correction of old notes:** this 3,111B routine was previously
loosely called `Player::frame_changed`. That name is already the
distinct existing **25-byte strict canonical** `Player::frame_changed()`
at **`0x004C0CE0`**, unit `player_frame_changed`. It reads
the actual Player Timer at `+0x644`. Never assign that decorated
name/ABI to the still-unnamed 3,111B parent at `0x004F9C30`.
An attested read-only Ghidra 12.1.3 decompilation of only this
original parent is preserved privately as
`.analysis/core430-player-main-frame-decompile.txt`;
it is a research hypothesis, not the original-byte oracle.

## Audited entire gameplay phases

1. **Input and movement modes:** resolve the true Player input source
   through native `view_index` at `Player+0x14854`, process movement
   mode bits 6–7 and `timer_2070` transitions, call the complete
   75-byte native movement-mode setter and 90-byte option-delay
   broadcaster. Input masks 0x50, 0x60, 0x90, 0xA0, 0x20, 0x10,
   0x40, 0x80 and focus bit 8 use the genuine InputButtonState.
2. **Focus and animation:** consume live Context and `timer_654`,
   update focused byte at `+0x204C`, previous fixed positions and
   the true Player AnimationHandle and movement effects.
3. **Game movement and speed:** select x/y directions from original
   `0x00572C48` table indexed by `Player+0x67C`, apply focused/
   unfocused speed fields at `+0x20B4..+0x20C0` and original
   `+0x20EC` motion scale. Call the separate real
   `Player::apply_move_delta(int,int)` at original parent offset
   **`+0x9EF`**. That 555B original has complete maintained
   C++ source, but remains **NONEXACT** (561B/136 instructions
   versus 555B/135; one extra SSE spill), so receives zero exact
   credit. [Independent full motion source](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md).
4. **33-point history:** shift genuine 8-byte `IntPoint` values
   in the 33-entry `Player+0x20FC` coordinate history.
   The previously exact 16B size method at `0x004FFFE0`
   is called three times, at parent `+0xA58`, `+0xA81`,
   `+0xAC0`. The new exact 22B indexed accessor is called
   at **`+0xA93`, `+0xAD2` and `+0xB1C`**. Store the actual
   Player fixed coordinate at history index zero.
5. **Two full option arrays:** walk the true ten-primary and
   twelve-secondary 300-byte `PlayerOption` records and call
   the independently exact **1,081-byte Player per-option frame**
   at `0x004FA860`, twice at `+0xBA4` and `+0xBFD`.
   Maintain the original option frame counter and state flags.

This analysis is of the full original native body. The source
implementation of the entire 3,111B parent is still open.

## Two independently complete native methods admitted in CORE/EXACT-433

| Physical game-owned original | Entry | Entire original | Original instructions | Direct parent calls |
| --- | --- | ---: | ---: | ---: |
| `PlayerValues<IntPoint,33>::at(int)` | `0x0045D670` | **22/22B** | **10/10** | 3 |
| `InputButtonState::replay_current_bits(uint32_t) const` | `0x004973A0` | **25/25B** | **10/10** | 10 |

**47 new nonoverlapping exact original bytes**; full immutable SHA-256
values respectively
`dfb4f7584787b079a479a612acfdfe25e88554f36f15b23a16e771443d887b78`
and
`2fe8bdf4fdc96bdc23b57337fc6eb66bae8f9537376e754e49cf400210023b53`.

The 22B getter has the actual `PlayerValues<IntPoint,33>`
receiver in ECX and a stack index, returning `IntPoint&` via
`lea eax,[ecx+eax*8]`, then native `ret 4`.
Its class template method was already declared, and is now
implemented by natural `values[index]` in the existing
`src/PlayerAccessors.cpp` original canonical provider.

The 25B input getter is an actual `InputButtonState`
member: it reads the live `replay_current` word at
**receiver+0x29C**, intersects it with a by-value
input mask and returns the result. Its true 0x2C0-byte
source class and the newly added field offset assertion
are in `src/InputState.hpp`; the method lives in the
existing `src/InputState.cpp` canonical object.
The original 3,111B parent calls this method ten times
as independently decoded original E8 sites, not from
compiler-generated test scaffolding.

The complete original 22B and 25B functions each have
**zero original direct E8 calls and zero PE HIGHLOW fields**.
Their 20 original instruction heads and full bytes match
the same pinned MSVC 19.44 i386 `/Od /Ob0` source profiles
as the preexisting real game owners. Immutable whole
original boundaries, SHA and true parent call offsets:
`.analysis/core433-history-input-original-pe-proof.json`.

## Subsequent CORE/EXACT-436 whole native option suspension

The entire separate `Player::suspend_option_animations`
at `0x004BD0C0` is now **237/237 native strict exact**,
called by the 3,111-byte Player main frame at
original `+0x75`. It **sets** Player flag bit 1,
interrupts mode-3 on both handles of all ten primary
and twelve secondary options, and resets the option
frame counter. This is a **different original physical
function** from the 237B mode-2
`Player::clear_option_animations` at `0x004FF8F0`.
All eight independently attested original E8 targets
are previously strict exact: four index calls to
`0x004BA3E0` and four mode-3 wrapper calls to
`0x00486350`. The actual Player.hpp receipt closure
passed **72/72 strict units in 25 cold source objects**,
with no unfiltered whole-graph cold replay.
The original 3,111B parent remains independently
nonexact; only its callee's whole 237B original
bytes are newly credited. Read the
[complete mode-3 native proof](PLAYER_OPTION_MODE3_SUSPEND_237_EXACT_RECONSTRUCTION.md).

## Subsequent CORE/EXACT-439 AnimationHandle callback closure

The distinct full native `AnimationHandle::is_valid`
at `0x0047A340` (**45/45B**, called twice)
and `AnimationHandle::set_position_forward` at
`0x004645E0` (**26/26B**, called once) are
now **separately strict exact**. Their immutable
original E8 targets are the previously exact
`AnimationHandle::resolve` at `0x0044CED0`
and `AnimationHandle::set_position` at
`0x004502C0`; the two full original bodies
have **27 instruction heads and zero PE HIGHLOW**
sites. At CORE/EXACT-436 the Player parent had
59/67 direct call sites to exact native
callees. These original three additional
call sites give **62/67**, leaving five still
unclosed. The real `AnimationHandle.hpp`
old receipt include closure was **106
source objects/471 strict units**; the
two new whole units yielded **473/473**
strict native units in those same 106 cold
objects, run in 22 source-scoped serial
batches, **not a full-repository cold replay**.
The 3,111B parent remains independently
NONEXACT. See [both complete original game
handle methods](ANIMATION_HANDLE_PLAYER_FRAME_71_EXACT_RECONSTRUCTION.md).

## Subsequent CORE/EXACT-445 complete native SoundInf queue callee

The real `SoundInf::request_effect(int,int)` at
`0x00426D70` is now **320/320 strict native exact**,
called twice from the original 3,111B Player
main-frame at offsets `+0xC5` and `+0x139`.
Its entire 102-instruction original does 12-slot
effect request merge and max-60 pan buffering
with correct real 90-channel cooldown selection.
All seven native E8 fields and original one
HIGHLOW field (sound table base+8) agree.
True sound header source closure passed **25/25
strict native units in 12 cold objects**,
not a whole-graph cold replay.
The independently exact direct call-site count
for the still-open 3,111B parent is now **64/67**,
leaving three separate unresolved called functions:
input provider, Animation VM interrupt/update and
the 555B Player motion clamp. The main 3,111B
parent itself remains **NONEXACT**, with no
inferred exact native byte credit.
[Original 320B SoundInf request proof](SOUND_EFFECT_REQUEST_QUEUE_320_EXACT_RECONSTRUCTION.md).

## Subsequent CORE/EXACT-449 whole pool child interruption closure

The original **246B** `AnimationPoolOwner::interrupt_handle`
at `0x0044EE90` is now whole strict exact with all
**77 original instructions, 12 E8 and 2 HIGHLOW**
fields. It correctly has two stack arguments:
the live pool handle and the child-interrupt event,
and uses real exception-safe IntrusiveIterator
lifetime rather than a fabricated AnimationHandle
receiver. The distinct **35B**
`AnimationHandle::interrupt` at `0x0044EF90`
also now strict matches its complete 15 original
instructions and native global pool forwarding.
One more native original call from this 3,111B
Player main frame is therefore independently
closed: **65/67** exact direct E8 callees.
The original 26B input lookup, 555B movement
function and separate 456B pool handle resolver
remain nonexact/uncredited. The actual
AnimationRuntimeOwner.hpp receipt-source
closure passed **27/27 units in 11 cold
objects**, with no whole-repo replay.
[Whole 281B pool/handle animation original proof](ANIMATION_POOL_INTERRUPT_246_EXACT_RECONSTRUCTION.md).

## Subsequent CORE/EXACT-454 whole Player input-source accessor

The genuine input lookup (now RTTI-corrected as `InputInf::for_view(int)`)
at `0x00498FB0` is now a separate complete
**26-byte / 10-instruction strict native exact**
method. It receives the actual runtime controller
global from `0x005B8898`, and indexes its
`InputButtonState*` pointer table at controller
`+0x2E30` using the Player's real `view_index`
(`Player+0x14854`). This native input lookup
is called at original frame `+0x3D`.
The full 26-byte original has zero E8 and
zero PE HIGHLOW fields; no invented large
class padding or unsupported full controller
size is introduced. The caller's ten native
uses of exact `replay_current_bits` follow
from this actual pointer. The only changed
existing source provider was `src/InputState.cpp`:
**13/13 strict original units in one
source-only cold object** passed. The main
frame now has **66/67 original E8 call
sites to separately exact native functions**.
The sole remaining nonexact called body
is the distinct 555-byte `Player::apply_move_delta`,
while the entire 3,111-byte enclosing main
frame stays NONEXACT.
[Whole original input controller native proof](INPUT_CONTROLLER_PLAYER_VIEW_26_EXACT_RECONSTRUCTION.md).

## Whole parent call-graph status and focused strict replay

Before these two native methods were admitted, 45 of
the original parent's 67 direct call sites led to
already canonical-exact native function bodies.
The **3+10** original call sites to these two real
new methods bring that count to **58/67 original
direct calls**. **Nine** calls remain to noncanonical
callees, including the still-nonexact 555-byte Player
movement function, input provider dispatch,
gameplay-state event and animation state methods.
The 3,111-byte parent remains **NONEXACT**.

The Player history `at(int)` method requires **no new
shared Player header**, because it was already declared;
its existing `PlayerAccessors.cpp` owner grows from
four to **five** exact units. The Input replay mask
getter adds its true declaration and field-offset assertion
in `InputState.hpp`. Actual *pre-edit compiler receipts*
for that header established exactly **one affected
source provider with eleven old strict units**, namely
`InputState.cpp`. Its owner now has twelve exact units.
Thus only **two** real source providers were cold rebuilt:
**17/17 strict original units across two cold objects**.
The complete scoped proof is
`.analysis/core433-history-input-scoped-replay.log`;
the original include closure is
`.analysis/core431-input-preedit-closure.json`.
No global cold replay, original executable patching,
duplicate native credit or manual instruction padding.


## Subsequent CORE/EXACT-455 original InputInf owner correction

Fresh independent original PE RTTI at `0x005B41F8`
names the owner of the already exact 26-byte
`0x00498FB0` input source accessor **`InputInf`**,
not the provisional `InputController` owner
recorded at CORE/EXACT-454 time. The complete
original 261B constructor `0x0041F8A0` actually
builds twelve 0x3D4 InputDevice records at +0x20,
two 32-bit view pointers at +0x2E30, and four
0x30 InputBindings records at +0x2E38.
The maintained 26B method now indexes genuine
`InputInf::active_buttons[logical_index]`,
with strict x86 offsets and original bytes unchanged.
This is a **type/source ownership correction**;
it adds **zero new exact game-original bytes**.
Affected cold sources passed **13/13 strict
units in two objects**, plus the separate
1,081B exact Player option frame was rechecked.
The 3,111B main-frame still has **66/67**
exact callees, and its remaining 555B motion
callee and entire parent stay NONEXACT.
[Original RTTI and typed input owner proof](INPUT_INF_RTTI_OWNER_LAYOUT_CORRECTION.md).
