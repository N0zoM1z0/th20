# CORE/EXACT-429 and CORE/RECON-429 — exact 16-byte Player history size; entire 555-byte movement C++ frontier

Comparison original: the immutable Japanese TH20 v1.00a Steamless
`resources/th20.exe`, original whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
**There are two strictly different status claims below.** The physical
16-byte history-array capacity accessor is wholly original-byte exact;
the genuine 555-byte gameplay movement routine has a maintained
complete C++20 implementation but remains **NONEXACT** and
contributes **zero newly accepted native exact bytes**.

## Whole original 16-byte PlayerValues<IntPoint,33>::size() — strict exact

The native original at `0x004FFFE0..0x004FFFEF`
is the entire **16-byte / 8-instruction** member
`PlayerValues<IntPoint,33>::size() const`. The complete original
SHA-256 is
`b5f2903b9179be30628a4b2315e5b982d0b738eacb0eba34b016ab45ad15e36e`.
Its authentic MSVC x86 `__thiscall` prologue saves the real
template-container receiver in the 4-byte local stack slot,
returns the integral constant **33** through EAX, and returns
normally with no stack arguments and no external relocations.

The already game-authored `Player::points_20fc` field is
a true `PlayerValues<IntPoint,33>` array. The original
**3,111-byte** Player main frame routine at `0x004F9C30`
calls its capacity function at three **independently observed**
direct native call sites `+0xA58`, `+0xA81` and `+0xAC0`,
consuming the actual values `33 - 1` and `33 - 2 - i`
as history-array indices. The body is therefore genuinely
owned by the original game's fixed-position history and
is not an unrelated synthesized constant-return helper.

The exact maintained source is the existing
`src/PlayerAccessors.cpp` with a real C++ template
definition and explicit `IntPoint,33` instantiation,
and a method declaration on the real `PlayerValues` type
in `src/Player.hpp`. It compiles under the previous locked
source profile MSVC 19.44.35211 i386 C++20
`/Od /Ob0 /GS /sdl /EHsc /fp:precise` and is admitted
as `player_option_history_capacity` into the already
canonical `build/core307-canonical/PlayerAccessors.obj`
owner. Complete independently original 16 bytes and
**zero E8/PE HIGHLOW fields** are compared; all
**16/16 strictly exact**. This is the **only newly
accepted original exact byte count** in the checkpoint.

## Complete 555-byte original Player movement boss — maintained NONEXACT source

The separate game-owned `Player::apply_move_delta(int,int)`
at `0x004FFA10..0x004FFC3A` is a genuine whole
**555-byte / 135-instruction** original `__thiscall`
movement update, original whole SHA-256
`eef3217c41849ecd607fb36bf0d760b83cddaee6a97050c845bbf751b9bef1bf`.
It is independently called by the original
3,111-byte Player main frame at `+0x9EF` and by
the native Player state routine at `0x004F7430`.
The maintained, whole, typed semantic body
is `src/PlayerMovement.cpp`, with a genuine
`void Player::apply_move_delta(int,int)` method declaration
in `Player.hpp`. There is no canonical strict unit
for this original function yet.

The entire maintained method computes x/y float motion
using actual input integers and **two separate**
`ClockScalar::operator float()` reads of the real original
global `default_timer_clock` at `0x005AEFE4`. It updates
`Player::vector_20c4` at `+0x20C4`, optionally
copies the complete 12-byte vector into `vector_20d0`
when `field_67c` is nonzero, converts both float
components to signed low-32-bit fixed coordinate increments
at `point_20dc`, and adds them to the true Player
`fixed_position_ref()` x/y lanes, preserving native
wrapping 32-bit arithmetic rather than inducing signed
C++ overflow undefined behavior.

When the native `Player::movement_mode()` is zero, it
clamps x to **[-0x5C00,+0x5C00]** and y to a
minimum of **0x1000**. The upper y boundary is
not a compile-time-folded magic integer: the original
**twice** reads native 448.0f
at `0x0056D7C0`, subtracts 16.0f at
`0x0056CD90` and multiplies by 128.0f at
`0x0056CD98` before signed integer conversion.
These three native float targets are separately
observed in the original PE and are preserved as
typed external scalar references. Finally, the method
writes actual `position_ref().x` and `.y` in
floating coordinates, dividing each newly fixed
coordinate by 128.0f, without touching unrelated Z.

### Original-binary provenance versus incomplete code generation

The entire immutable original was independently decoded
to **135/135 x86 instruction heads**. There are
**17 original E8/REL32 direct-call fields** and **10
independently original PE HIGHLOW/DIR32 fields**,
all audited from the native original, not the candidate.
The complete C++20 candidate compiled with the real
pinned MSVC i386 `/Od /Ob0 /GS /sdl /EHsc /fp:precise`
profile emits **561 bytes / 136 x86 instructions**,
with **all 135/135 original mnemonic kinds aligned in order**
and **27 COFF relocation fields with matching type/count**.

**It is NOT exact.** The best natural source preserves
a genuine live y-upper-bound float value across the
call to `fixed_position_ref()`. MSVC emits
`movss [ebp-0x30],xmm0` as **one additional 6-byte SSE
temporary spill** before converting that float to a
signed integer in the preserved ESI register. The
original directly performs `cvttss2si esi,xmm0`
and never makes that extra float spill. The source
does not claim the original 555 bytes, even though
all opcode kinds align. Its original E8/HIGHLOW
**positions diverge after the extra instruction**;
same reference counts alone do not constitute
strict native relocation matching. The repository's
native exact ledger therefore credits **0/555
original bytes** for this entire function.

Private independent native evidence and precise codegen
measurement:
`.analysis/core429-player-frame-native-independent-audit.json`
and
`.analysis/core427-movement-nonexact-score.json`;
complete semantic source variant,
`.analysis/core427-movement-wrap-safe.cpp` and
MSVC locked-compiler probe
`build/core428-probes/PlayerMovement.obj`.
Other private probes in `.analysis/core421-*`
through `core425-*` test genuine scoped coordinate
locals, boundary values, live register lifetimes
and original compiler flags, without hand-padded
instructions or invented game callbacks.

The **3,111-byte Player main frame** remains
independently NONEXACT and does not gain exact
credit merely because its 16-byte history
capacity callee is complete and its 555-byte
motion callee now has source.

## Strictly affected source-provider replay and ledger status

The **only changed shared interface** is `src/Player.hpp`,
which adds the actual Player motion method and
the genuine `PlayerValues::size()` template signature.
The existing `src/PlayerAccessors.cpp` source gains
the exact explicit size instantiation. The new
`src/PlayerMovement.cpp` is an independently
compiled, maintained NONEXACT complete-function
source and **is not a canonical exact owner**.
No other public layout, native target, compiler
profile, or exact game body was changed.

Before editing, locked canonical compiler receipts
were inspected for `Player.hpp`: the exact include
closure comprised **25 older source/object providers
and 69 original strict units**. Adding one exact
function to the existing PlayerAccessors owner yields
**70/70 actual affected native strict units in
25 freshly cold-built objects**, in five serialized
low-priority batches of **5 + 34 + 8 + 13 + 10**.
The full original 1,081B option-frame boss,
1,518B Player option rebuilding, 966B Player
initialization and existing Bullet collision
function remain strictly exact. The newly
compiled 555-byte source was separately probed
in its entirety and received no match unit.

One MSVC-private Player constructor `$SG`
string counter renumbered. Its immutable
native string destination **`0x00572BB8`**,
original relocation field offset/type and
complete nonrelocation native bytes were
independently checked before updating only
the private compiler label and rerunning
the unchanged strict comparator.
Actual prior receipt closure, six original
PE-anchor/score records and complete exact
replay evidence:
`.analysis/core427-player-size-preedit-closure.json`,
`.analysis/core429-player-history-replay-groups.json`,
`.analysis/core429-player-history-replay-batch0.log`
through `batch4.log`, and
`.analysis/core429-reconciled-private-symbols.json`.

No unfiltered full repository cold replay was run.


## CORE/EXACT-433 — subsequent actual native history index/input callee closure

The entire original **3,111-byte Player main frame**
at `0x004F9C30` is now independently audited
as **783 original x86 instruction heads, 67
direct E8 fields and 37 PE HIGHLOW sites**.
The newly exact **22-byte**
`PlayerValues<IntPoint,33>::at(int)` at
`0x0045D670` is called three times by the
native 33-history shifter. The genuine
`InputButtonState::replay_current_bits` at
`0x004973A0`, 25B whole exact, is called ten times
by the same original parent. Both complete bodies
have no external relocations and were independently
native x86 verified; **17/17 strict units in two
cold source objects** pass. These new separate
functions do not credit extra bytes to the exact 16B
size accessor or the **still nonexact** 555B
movement C++ source from the earlier checkpoint.
Historical naming of the 3,111B parent as
`Player::frame_changed` is mistaken: that is
already a **different** 25B canonical method at
`0x004C0CE0`.
See [the immutable 3,111B native call graph and
two exact original callees](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md).
