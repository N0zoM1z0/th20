# CORE/EXACT-495 — entire original 726B DirectInput discovery and 218B pad attachment

Comparison original: immutable Japanese TH20 v1.00a Steamless PE,
whole original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Three distinct whole, game-authored native functions are now strict exact:

| Original game function | Original entry | Whole original body | Native x86 instructions | E8 / PE HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `InputInf::discover_directinput_devices` | `0x00420AA0` | **726/726B** | 209 | 16 / 18 |
| `InputDevice::initialize_directinput` | `0x004219D0` | **218/218B** | 68 | 3 / 8 |
| `InputInf::direct_input_handle_slot` | `0x00421830` | **17/17B** | 9 | 0 / 0 |

They contribute **961 distinct original game-authored bytes**,
and all **45 immutable original E8/HIGHLOW relocation fields** agree
with actual MSVC i386 COFF symbol offsets, types and addends.
The complete original native SHA-256 digests are respectively
`4351b5a7e36130d706bb64bbd046c7b8f8252100b8641868fd3f89d1f01d1101`,
`ed2172a0e5cc6057d641101737cd8f8aa24c2467268f56ed9821c2450e1a41ba`,
and
`d2784e2c65576cf45a1787167c999137dc4e42ffac4aa6fe643d9e64218a7655`.

## Entire game-owned DirectInput creation boss: real SDK and error rollback

The actual `InputInf` owner is established by original RTTI
`.?AVInputInf@@` and true manager layout. The original whole
726B native function obtains the Win32 instance from the
real `WindowState.instance` field at +0x0C of
`window_state`, whose original global address is `0x005B6758`.
It then invokes the actual imported
`DirectInput8Create(instance,0x800,IID_IDirectInput8W,...,nullptr)`
at original thunk `0x00540660`, writing through the genuine
`InputInf::direct_input_handle_slot` at manager offset +0x1C.
Original IID reference `0x00576B78` is the actual
`IID_IDirectInput8W`.

On failure the original clears the real DirectInput interface,
logs the genuine Shift-JIS resource through `DiagnosticLog`
at `0x005C0678`, and returns -1. On success it creates the
keyboard via the actual SDK `GUID_SysKeyboard`
at `0x00576C18`, sets the original
`c_dfDIKeyboard` format at `0x00576B48`, and uses
`SetCooperativeLevel` with the true HWND and
`DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY`,
native flags **0x16**. Native COM virtual dispatch uses
real SDK interfaces, not guessed vtable offsets or hand
emitted calls.

Every unsuccessful keyboard setup stage follows the original
separate resource lifecycle: release the active device where
the native original does, clear the live native pointer, call
the previously exact `InputInf::release_direct_input`
at `0x004216E0` where required, log the original
failure diagnostic and return -1. The diagnostic original
PE literal addresses include `0x0056D5A8`
(twice for creation errors), `0x0056D5C8` for format
failure, `0x0056D5F8` for cooperative level failure
and `0x0056D62C` for successful startup.

The successful path acquires the real keyboard COM device,
writes its success log, enumerates game-controller devices with
`IDirectInput8W::EnumDevices`, original
`DI8DEVCLASS_GAMECTRL` and `DIEDFL_ATTACHEDONLY` flags,
and authentic original callback at `0x00420220`.
It walks the **four genuine native
`IDirectInputDevice8W*` pad slots** in
`InputInf+0x2E14`, publishes the current
pad through original global `0x005B88AC`,
calls real device `EnumObjects` with the original
callback at `0x00420180`, and constructs each
actual 0x3D4-byte `InputDevice` by invoking
the separate whole-exact **218B**
`InputDevice::initialize_directinput`.
Each successful pad increments the actual signed
`InputInf+0x14` device count. It then returns zero.

The Win32 instance must be evaluated into an authentic
`HINSTANCE` local **before** calling `DirectInput8Create`:
an inline expression changed native argument evaluation.
The `CreateDevice` and `SetDataFormat` HRESULT results
must be tested **directly**, whereas the final
`SetCooperativeLevel` HRESULT must be retained in a
real local. All are meaningful original COM error-flow
semantics. Private naturally compiled variants in
`.analysis/core492-directinput-726-variants.py`
show why the other evaluation forms emitted wrong
native instructions. This exact form generates the
complete **726B / 209-instruction** original body
without synthetic branch, artificial variable or machine bytes.

## Whole 218B InputDevice pad registration

The actual 218B source-owned member first queries the
real `process_input_inf` at `0x005B8898` for
the physical pad at `InputInf::pad_device(physical)`,
already separately 26/26 native exact at `0x00421850`.
If present, it uses genuine
`IDirectInputDevice8W::SetDataFormat(&c_dfDIJoystick2)`
with the original Windows SDK data-format object
`0x00576B60`, then sets the real window HWND
cooperative level to
`DISCL_NONEXCLUSIVE | DISCL_BACKGROUND`, native 0x0A.
It sets the real
`process_graphics.input_device_caps.dwSize`
and calls `GetCapabilities` with that same
`DIDEVCAPS` field at original `0x005C4D5C`.
Both references have one actual
`process_graphics` symbol base `0x005C4D40`
and **COFF addend +0x1C**, not a fabricated
extra global.

The device pointer is stored in real
`InputDevice.direct_input` at +0x08. The native
`EnumObjects` call receives the original callback
at `0x00420180` and real `DIDFT_ALL`; its original
Shift-JIS pad-attachment diagnostic at `0x0056D654`
is passed through the real `report_log_error`.
The original sets device kind to 1,
physical XInput index to -1, and logical
input index to the caller's second argument,
with the original native `ret 8` calling convention.
The source naturally emits **218B / 68 instructions**,
including all genuine COM indirect calls.

## New 17B native input pointer-slot accessor and four folded aliases

The third distinct original whole body
`InputInf::direct_input_handle_slot` at
`0x00421830` returns the address of the
real `IDirectInput8W*` at `InputInf+0x1C`.
It is **17/17 bytes / nine instructions**,
with no original E8 or HIGHLOW fields.

Four other genuine C++ methods were also
naturally recovered to support the boss,
but each maps to a **previously accepted
exact original physical body shared by
the linker**. Their implementations live
in existing `src/InputInf.cpp` and
`src/WindowState.cpp`, and receive
**zero additional native byte credit**:

| Correct original owner/method | Original physical address | Already-credited strict original unit |
| --- | --- | --- |
| `WindowState::window_handle` | `0x0040C300`, 16B | `identifier_get` |
| `WindowState::instance_handle` | `0x0041CAB0`, 17B | `context_item_controller` |
| `InputInf::direct_input_handle` | `0x00421810`, 17B | `player_animation_file_ref` |
| `InputInf::set_direct_input_handle` | `0x0041DE70`, 22B | `player_record_set_field_1c` |

Each folded alias was separately built from its genuine
typed source and compared to **every original physical
byte**, not inferred from superficial source similarity.
There is one physical original address, one
previous exact byte credit; this checkpoint adds no
duplicated matching row/unit for any folded alias.
The historical names are previously adopted roles,
not evidence that those four original caller
receivers are identical C++ classes.

## Independently original PE and all 45 references

Whole immutable original PE functions were disassembled
with Capstone, and every original `.reloc` HIGHLOW
was collected before creating manifest units.
The 726B boss has **16 true direct E8**
and **18 HIGHLOW**, the 218B member has
**3 E8 and 8 HIGHLOW**, and the 17B
slot getter has zero. All **45** original
offsets/types/physical destinations and the
actual compiler COFF source symbols/addends
are independently attested in
`.analysis/core494-original-directinput-726-and-218-proof.json`.

Notable original anchors include:
`0x00420AA0+0x00A -> 0x005B6758` real
window state; `+0x00F -> 0x0041CAB0`
folded instance getter; `+0x01C -> 0x00421830`
new complete input slot getter; `+0x022 ->
0x00576B78` original IID; `+0x030 ->
0x00540660` actual DirectInput8Create thunk;
`+0x084 -> 0x00576C18` keyboard GUID;
`+0x0D3 -> 0x00576B48` keyboard format;
`+0x15A -> 0x0040C300` folded HWND getter;
`+0x213 -> 0x00420220` enumeration callback;
`+0x28A -> 0x00420180` real object callback;
and `+0x2B8 -> 0x004219D0` the new exact
pad registration member.

The 218B original references include
`+0x00F -> 0x005B8898` live InputInf pointer;
`+0x014 -> 0x00421850` exact pad getter;
`+0x031 -> 0x00576B60` joystick format;
`+0x048 -> 0x005B6758` true window state;
`+0x04D -> 0x0040C300` HWND getter;
`+0x063/+0x077 -> 0x005C4D5C`
Graphics capabilities (+0x1C COFF addend);
`+0x09B -> 0x00420180` COM enumeration callback;
`+0x0A7 -> 0x0056D654` actual original
diagnostic and `+0x0B1 -> 0x00454150`
the original, still independently nonexact,
full diagnostic log function.

The unchanged strict comparator agrees on
**590/590 original nonrelocated plus 136/136
relocated bytes** for 726B, **174/174
nonrelocated plus 44/44 relocated bytes**
for 218B, and **17/17 fully unmasked bytes**
for the slot getter. The native source
uses actual Windows SDK types:
`IDirectInput8W`, `IDirectInputDevice8W`,
`GUID_SysKeyboard`, `IID_IDirectInput8W`,
`DIDEVCAPS`, `c_dfDIKeyboard` and
`c_dfDIJoystick2`. No original target was
derived by solving the compiled relocation field.

## Actual prior compiler-receipt include closure: 85/85

Only three real shared headers were edited:
`src/InputState.hpp`, `src/WindowState.hpp`
and `src/InputInf.hpp`.
**Before those edits**, real locked compiler
receipt include graphs selected:
`InputState.hpp`: **6 old source objects /27 units**;
`WindowState.hpp`: **11/55**; and
`InputInf.hpp`: **5/13**.
Their union was exactly **17 existing source
objects and 82 old strict native units**,
not their sum and not all of TH20.

Adding two new original source owners
`src/InputDeviceDirectInput.cpp` and
`src/InputInfDirectInputDiscovery.cpp`
and one physically distinct original 17B
method in the existing InputInf source gives
exactly **19 truly affected source objects /
85 strict native units**. Their real
original-PE comparator replay was serial,
low-priority and source-filtered in five
batches: **23/23 + 12/12 + 27/27 +
9/9 + 14/14 = 85/85**. Complete source
lists and native logs:
`.analysis/core494-directinput-preedit-header-closure.json`,
`.analysis/core495-directinput-replay-groups.json`
and `.analysis/core495-directinput-replay-batch0.log`
through `batch4.log`.
Previously exact entire InputInf lifecycle,
465B signed device initialization, 170B XInput
discovery, large Enemy/Animation/RenderMesh
functions and original WindowState users
remain whole strict exact.

The broader header additions renumbered
several MSVC compiler-private `$SG`
diagnostic symbols in prior Dialogue,
InputInf and RenderMesh translation units.
For every accepted private renumber,
the original immutable PE absolute destination,
field offset/type and full unrelocated
function bytes were independently checked
before updating **only** the compiler-private
name in the manifest. No original literal
target, original native code byte, true ABI
or strict acceptance condition was altered.
The original-grounded changes are logged in
`.analysis/core495-reconciled-private-symbols.json`.

**New game-original exact credit:
3 distinct complete native functions /
961 bytes**, not four additional folded
aliases. The original **3,490B input polling
boss** remains **NONEXACT**, as do the
still-open callback bodies and 215B error
logger where not separately accepted.
A byte-exact device creation method is not
proof of whole-game linked/runtime equivalence.
No unfiltered whole-repository cold replay
was performed.
