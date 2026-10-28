# CORE/EXACT-489 — complete original 170-byte InputInf XInput device discovery

The immutable comparison target is Japanese TH20 v1.00a Steamless
PE, full SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete game-owned
`InputInf::discover_xinput_devices()` at
`0x004210D0` is now **170/170 original-byte strict
exact**, all **57 original i386 instructions**.
Original complete body SHA-256:
`801694fc89d8b68329bc8480ec941321b322135ddcf6fdea099a8ca26db507c0`.

## Real XInput SDK ABI and original gameplay loop

This method belongs to the original
`InputInf` owner, whose identity is independently
proved by original RTTI `.?AVInputInf@@`.
The original method counts how many of four
physical XInput controllers are available.
It iterates physical slots **0..3**, clears
the actual **16-byte Windows SDK
`XINPUT_STATE`** record with native
`memset` for each controller, and calls
the actual Windows SDK
`XInputGetState(slot, &state)`.

A successful XInput result is saved as a
real local `DWORD` before comparing it
with `ERROR_SUCCESS`. This native
result local is necessary for the original
machine-code structure: a naïve
`if (XInputGetState(...) == ERROR_SUCCESS)`
candidate emitted **165B/56 instructions**
and replaced the original separate
`mov` plus `cmp` with one `test`. The
natural local-result form reproduces the
**full original 170B/57 instructions**,
without padding, handwritten assembly
or an artificial extra operation.

For each successfully connected controller,
the game chooses the next real
`InputInf::devices[state_14]`, calls the
separately whole-exact
`InputDevice::initialize_xinput(physical,logical)`
at `0x00421AD0`, increments the
**signed** count of discovered input devices
at original `InputInf+0x14`, and increments
a separate local number of XInput controllers.
It returns that local discovery count.
The actual `InputDevice` has a separately
verified 0x3D4-byte stride, native physical
index field at +0x0C and true logical device
index field at +0x04.

The Windows SDK architecture setup uses
the existing `GraphicsApi.hpp` DirectInput
umbrella before `Xinput.h`, with
`std::memset` and native `XINPUT_STATE`.
The result is a real typed Windows
gameplay implementation rather than a
manual emulation of XInput DLL memory.

## Original immutable PE references and import thunk

Fresh original complete-instruction decoding
and an independent original `.reloc` scan
identified **four native direct E8/REL32
and one PE HIGHLOW/DIR32** fields:

| Field within 170B | Type | Original PE destination | Role |
| --- | --- | --- | --- |
| `+0x007` | DIR32 | `0x005B25C0` | native security cookie |
| `+0x03B` | REL32 | `0x00544760` | original CRT memset |
| `+0x04B` | REL32 | `0x005406C6` | original XInputGetState imported thunk |
| `+0x07B` | REL32 | `0x00421AD0` | separately exact InputDevice::initialize_xinput |
| `+0x0A2` | REL32 | `0x005429EE` | native security-cookie check |

The immutable original imported thunk
`0x005406C6` begins with
`FF 25 F0 C2 56 00`, an indirect
jump through the actual original PE import
table, independently corroborating that
the original native E8 destination is an
imported XInput interface and not an
arbitrary local gameplay function.
Ghidra's target-attested import analysis
calls this the XInput state DLL's
ordinal 2. The genuine Windows SDK
compiler symbol is `_XInputGetState@8`,
with zero COFF addend. Its original
physical link destination is retained
as `0x005406C6`, not invented
from the candidate COFF.

All **five original PE fields**, original
absolute/relative types, native destinations,
authentic SDK/native COFF symbols and
zero addends are independently attested
in
`.analysis/core489-xinput-discovery-original-pe-proof.json`.
The unchanged strict comparator accepts
**150/150 original nonrelocation bytes
and 20/20 relocated bytes**, totalling
**170/170 original code bytes**.

## Existing original compiler owner, one-source replay

The complete C++ method was added to the
**already canonical**
`src/InputInfDeviceInitialization.cpp`,
which also owns the previously exact
**465B** `InputInf::initialize_devices`
game boss at `0x00420D80`.
Its genuine pinned MSVC C++20 i386
`/Od /Ob0 /GS /sdl /EHsc` profile
matches both original methods. No shared
source headers or external global types
were changed, and no second body or
synthetic translation unit was introduced.

Before changing the source, its canonical
object contained **one earlier exact 465B
unit**. The new whole XInput method adds
exactly one more original strict unit:
**2/2 strict whole original native units
in one freshly cold-compiled object**,
run at reduced scheduling priority,
not a global cold replay.
The original source's compiler-private
`Pad Num : %d` diagnostic label
renumbered from `$SG171361` to
`$SG171489` when the XInput source
method was added. The original immutable
PE relocation still targets **`0x0056D6D4`**
at the same native initializer `+0xA3`
field. The original text, field type,
unchanged nonrelocation bytes and
full original 465B parent body were
independently checked before only
updating the compiler-private symbol
name. That proof is retained at
`.analysis/core489-maintained-original-string-reconciliation.json`.

Actual one-source replay:
`.analysis/core489-xinput-source-scoped-replay.log`.
Both original game-owned complete functions
(465B initialization and 170B XInput
discovery) remain strict exact without
double-counting any child body.

This checkpoint newly credits **one
original game-authored 170-byte function**.
The original **726B DirectInput discovery**
at `0x00420AA0` and complete
**3,490B InputDevice frame polling** at
`0x00421B00` remain separately
**NONEXACT**. Exact XInput discovery is
not proof that the whole game's
input polling/linked runtime is complete.
