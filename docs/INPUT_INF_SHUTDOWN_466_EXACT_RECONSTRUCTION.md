# CORE/EXACT-476 — complete 466B InputInf device shutdown boss and 50B DirectInput release

Immutable original comparison target: Japanese TH20 v1.00a
Steamless PE, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-owned `InputInf::shutdown()`
at `0x004202C0` is now **466/466 strict exact**
with all **127 original i386 instructions**,
**nine original E8/REL32 calls and six original
PE HIGHLOW/DIR32 references**. Entire native
original body SHA-256:
`5b10ae770906321b767ddb7b162d68a7827c0600f3a27fb908424b26e507d170`.

The separate original game-owned
`InputInf::release_direct_input()` at
`0x004216E0` is independently **50/50 strict
exact**, all **20 native instructions**, with
zero original direct E8 or PE HIGHLOW references.
Full original body SHA-256:
`5a2f9b6447e62a8b16c4123fe016b4c27450b79bceff8ae25d315b62a812a5cd`.

**516 new physically distinct original
game-authored native bytes** are credited.
The actual original `InputInf` constructor (261B),
destructor (120B), compiler-generated deleting wrapper
(49B strict support) and Player view selector (26B)
remain separate complete exact units; none receives
duplicate native credit here.

## Whole original shutdown lifecycle and true COM types

The real `InputInf` class is independently established
by native MSVC RTTI `.?AVInputInf@@` at `0x005B41F8`.
Its genuine native 0x2EF8-byte prefix contains
12 real 0x3D4-byte `InputDevice` objects at +0x20,
the main native `IDirectInputDevice8W*` at
**+0x2E10**, four actual pad device pointers
as a **C array at +0x2E14**, two live
`InputButtonState*` view pointers at +0x2E30
and four 0x30-byte InputBindings at +0x2E38.
Original COM interface pointer at **+0x1C**
is a genuine `IDirectInput8W*`, not a scalar
device state word. These are real native types
using the actual Microsoft DirectInput SDK ABI.

The exact 466B shutdown acquires lock slot **15**
through the real global `process_locks`
at **`0x005C0240`**, preserving the native
`std::lock_guard<std::recursive_mutex>`
constructor, lexical lifetime, exception
unwinding and destructor. It sets the live
`InputInf+0x14` state word to zero, then
iterates **all 12 real InputDevice records**,
calling the previously exact
`InputDevice::reset_header` member at
`0x00421720` with a native 0x3D4 stride.

If the main DirectInput device pointer at
`+0x2E10` is present, it emits the real
`DirectInput Release` diagnostic, invokes
the SDK virtual `Unacquire()` method at
**vtable+0x20**, rechecks the live pointer,
calls `Release()` at **vtable+0x08** and
clears that pointer. It then iterates the
four pad pointers at `+0x2E14+i*4`,
emits the native `DirectInput(Pad) Release`
diagnostic for each live device, performs
the same Unacquire/recheck/Release sequence
and zeroes the actual source array slot.
Each virtual COM call has the original
indirect call and receiver-passing ABI,
not fabricated direct E8 calls.

After the loops, the method emits
`DirectInput Device Release`, calls the
separate exact 50B
`InputInf::release_direct_input`, destroys
its original lock guard and returns integer
zero. The 50B callee reads the real
`IDirectInput8W*` at offset +0x1C,
conditionally invokes its true IUnknown
`Release()` (vtable+8) and sets the field
to nullptr. Neither method invents device
allocation, additional cleanup branches
or hidden resource handling.

The original **3,490B** native device/input
frame processing at `0x00421B00` remains
separately open and NONEXACT. An exact shutdown
does not prove input polling or linked runtime
equivalence.

## Independently attested original PE fields

All **15/15 immutable original relocation field
offsets, types, physical targets and compiler
COFF symbol identities** were independently
recovered from the actual PE before canonical
admission:

| Original field | Type | Original PE target | Real role |
| --- | --- | --- | --- |
| `+0x006` | DIR32 | `0x005676ED` | EH descriptor |
| `+0x015` | DIR32 | `0x005B25C0` | security cookie |
| `+0x02E` | DIR32 | `0x005C0240` | global lock registry |
| `+0x033` | REL32 | `0x0040C310` | exact lock slot selector |
| `+0x03C` | REL32 | `0x0040B730` | recursive lock guard ctor |
| `+0x078` | REL32 | `0x00421720` | exact InputDevice reset |
| `+0x08C` | DIR32 | `0x0056D6E4` | main device diagnostic |
| `+0x091` | REL32 | `0x0040C6B0` | diagnostic emitter |
| `+0x113` | DIR32 | `0x0056D6FC` | pad device diagnostic |
| `+0x118` | REL32 | `0x0040C6B0` | diagnostic emitter |
| `+0x18B` | DIR32 | `0x0056D718` | final device diagnostic |
| `+0x190` | REL32 | `0x0040C6B0` | diagnostic emitter |
| `+0x19B` | REL32 | `0x004216E0` | new exact 50B COM release |
| `+0x1B2` | REL32 | `0x0040B900` | recursive lock guard dtor |
| `+0x1CA` | REL32 | `0x005429EE` | native security cookie check |

The 50B release helper contains **no external
relocation fields**, so its entire original body
is directly byte compared. The locked compiler
source matches **406/406 nonrelocation bytes
plus 60/60 relocation bytes** for the 466B boss,
and **50/50** original bytes for the direct
COM release helper. The original PE hashes,
native E8 operands, PE HIGHLOW records,
COFF symbol names, zero addends and independent
original destination evidence are preserved in
`.analysis/core476-inputinf-shutdown-original-pe-proof.json`.

## How natural original input data layout recovered the full boss

The first full native C++ candidate already
implemented lock ownership, 12 input devices,
main device, four pad devices, diagnostics,
COM release and return 0. It emitted 446B
and 130 instructions, including three additional
array-address operations. The true original
uses direct `[this + index*4 + 0x2E14]`
addressing. Replacing the temporary pointer
cast with real
`IDirectInputDevice8W* pad_devices[4]`
and the keyboard pointer with a genuine
`IDirectInputDevice8W*` naturally generated
**466B / 127 original instructions**, with
all 15 original field locations exact.

Crucially, this type correction must not break
the previously strict 261B InputInf constructor.
A naïve whole-pad-array `pad_devices{}`
initializer generated incorrect native original
stores. The legitimate array
`pad_devices{nullptr}` value-initializes
the first and remaining pad pointer elements
and naturally emits the original constructor's
distinct first-pointer/remaining-three
initialization pattern. With that source,
the previous 261B ctor still passes its entire
**266/266** original aligned physical bytes.
Further using a genuine `IDirectInput8W*`
member at +0x1C removes the earlier integer
pointer cast without changing **any** of
the six original exact lifetime/view bodies.

No hand assembly, copied binary bytes, fake
return, duplicate class or inert compiler
shaping operation is present in the maintained
code. Native SDK interface methods, C-array
initialization and actual RAII are used.

## Entire actual affected source receipt closure

Only `src/InputInf.hpp` shared ownership
types/declarations and the authentic
`src/InputInfConstruction.cpp` initializer
changed; `src/InputInfShutdown.cpp` is a
new separately canonical source for the
two newly exact methods, with the actual
pinned MSVC 19.44 i386
`/Od /Ob0 /GS /sdl /EHsc /fp:precise`
profile.

Before editing the shared header, actual
compiler receipt includes selected **two
old canonical source providers / four old
strict units**, namely InputInf constructor
and InputInf view sources. Adding one real
shutdown source provider with two complete
game-authored units yields **6/6 strict
native units across exactly three freshly
cold-built objects**, replayed serially at
reduced priority. All six pass, including
the separately existing 261B constructor,
120B virtual destructor, 49B compiler deletion
wrapper and 26B input-view member. The original
pre-edit receipt scope is saved in
`.analysis/core476-inputinf-shutdown-preedit-receipt-closure.json`;
complete filtered native replay is
`.analysis/core476-inputinf-shutdown-final-scoped-replay.log`.

The type/header edits renumbered two unrelated
MSVC compiler-private diagnostic labels in
the original constructor/destructor source:
`$SG78649 -> $SG78651` at original
ctor `+0xDF`, preserving exact native
`initialize InputInf` address `0x0056D4DC`,
and `$SG78653 -> $SG78655` at original
dtor `+0x30`, preserving exact native
`shutdown InputInf` address `0x0056D684`.
Both unchanged original PE fields and the
full nonrelocation bytes were independently
verified before only updating the private
compiler symbol spelling in the manifest.
Private original proof:
`.analysis/core476-inputinf-sg-renumber-proof.json`.

**New original game credit is exactly two
complete functions / 516 unique native body
bytes**. Original adjacent 49B compiler deleting
support remains strict but not falsely credited.
The 3,490B input processing, 555B Player motion,
3,111B Player frame and whole-game linkage remain
open. No unfiltered whole-repository cold
replay was run.


## Subsequent CORE/EXACT-480 InputInf routing, bindings, pad ABI

The entire original 3,490-byte InputDevice polling frame at
`0x00421B00` was independently decoded as **747 original
i386 instructions with 21 direct E8 and 18 PE HIGHLOW fields**,
but still remains **NONEXACT**. Four separately original whole
`InputInf` methods are now strict exact:
`routing_for_view` (**49B**), `bindings_for_view` (**27B**),
`pad_device` (**26B**) and `pad_device_slot` (**26B**).
All have zero native E8/HIGHLOW fields, and two are actual
callee destinations of the 3,490B input frame, raising
its original exactly matched direct-call targets to **11/21**.
The four unique game-original bodies total **128B**.
The genuine prior `InputInf.hpp` compiler receipts
covered **3 sources/6 strict units**; the actual affected
source-only cold replay passed **10/10 units in 3 objects**,
including the existing 466B InputInf shutdown, 261B ctor,
120B dtor, 49B compiler deleting support, 50B interface
release and 26B view lookup. Five compiler-private `$SG`
symbol renumberings were audited against real original PE
literal targets, fields and complete native code before
updating only private spelling. No global cold replay.
[Complete original frame frontier](INPUT_DEVICE_FRAME_3490_NATIVE_FRONTIER.md).
