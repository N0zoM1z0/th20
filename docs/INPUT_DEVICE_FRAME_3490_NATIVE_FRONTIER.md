# CORE/EXACT-480 — four InputInf native accessors and the complete 3,490-byte InputDevice frame frontier

Immutable original: Japanese TH20 v1.00a Steamless
PE, full SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Important scope distinction:** the entire original
`InputDevice` frame processing function at
`0x00421B00` is still **NONEXACT**. This checkpoint
independently decodes and audits its entire original
native body and reconstructs **four distinct whole
game-owned InputInf methods** in its true owner.
The exact callees do not confer 3,490 original
game-body byte credit on their unfinished parent.

## Complete original input frame: 3,490 bytes / 747 instructions

Fresh independent Capstone decoding of the original PE
`0x00421B00..0x004228A1` establishes **3,490
full original bytes / 747 complete i386 instruction heads**,
whole original SHA-256
`78ed183ee4a2d240f179feedd8e8d94b7d2ffa4b8bbdc263f45aa486ca395cef`.
There are **21 original direct E8 call fields to 11 unique
native addresses**, plus **18 independent original PE
HIGHLOW/DIR32 absolute fields**, audited from the
original executable rather than inferred from a
candidate compiler object. Original complete call
sites, true destinations and all 18 native .reloc
records are in
`.analysis/core480-input-update-native-proof.json`.

The original receiver is truly a 0x3D4-byte
`InputDevice`. The native code operates on
`kind` at +0x00, logical index at +0x04,
native `IDirectInputDevice8W*` at +0x08,
XInput physical index at +0x0C,
the real `InputButtonState` at +0x10 and
256 raw input bytes at +0x2D0. These offsets
were already independently corroborated by
the whole 102-byte exact InputDevice ctor,
340-byte exact nested InputButtonState ctor,
and exact 583-byte button updater.
The enclosing 3,490-byte method has not yet
been promoted to a whole exact source unit.

The original does the following complete
control phases, not simply a one-bit getter:

1. Clear the actual 256-byte raw device state,
   acquire native global `process_locks` mutex
   slot 15 via real `std::lock_guard`, inspect
   the logical device index and resolve the
   native InputInf routing/configuration view.
2. **Device kind 0 (keyboard):** use the original
   Windows `GetKeyboardState` API to populate
   actual 256 raw key bytes when keyboard input
   is enabled, then convert a full set of native
   keyboard scan indices from the true
   `InputBindings` into game button bitmasks,
   including movement, action, menu and
   alternate diagonal keys. The original
   InputInf bindings pointer is indexed in
   0x30-byte steps, not the 0x3D4 device stride.
3. **Device kind 1 (DirectInput pad):** invoke
   the live COM device's actual
   `Acquire()`/`GetDeviceState()` vtable slots,
   retry the original input-lost acquire path
   within its native **400-attempt limit**,
   and return via the genuine RAII lock cleanup
   on failure. Four calls to the previously
   exact 105-byte `map_input_byte` convert
   signed binding fields into game bitmasks;
   signed analog axis thresholds determine
   the original directional flags. Pressed
   pad button bytes populate actual device
   raw state, and the global input routing
   record is updated on state changes.
4. **Device kind 2 (XInput):** call the true
   XInput DLL ordinal 2 state provider, interpret
   the genuine native button, thumbstick and
   trigger fields, apply original signed
   thumbstick threshold **0x1EA8** and
   trigger threshold **0x1D**, and map selected
   actions through the original per-button
   table at `0x005AE220`. Its resulting
   button flags and raw pressed bytes are
   materialized into the same game input
   state as the other device modes.
5. On successful mode processing, update
   previous/current button bitfields on the
   real `InputButtonState` at +0x10 and invoke
   its independently exact **583-byte**
   `InputButtonState::update`
   at `0x004228B0`. Unwind the real
   recursive-mutex guard, native EH record
   and original security-cookie check.

This is a bounded original-PE/Ghidra source
hypothesis report, not a mechanically copied
decompiler source or an acceptance claim
for 3,490B. Read-only, separately
target-hash-attested Ghidra 12.1.3 analysis
is retained privately at
`.analysis/core478-input-device-update-3490-decompile.txt`.
Real PE bytes, actual call offsets and original
HIGHLOW locations remain the match authority.

## Four complete game-owned InputInf helpers now strict exact

| Whole original method | Original physical entry | Strict native bytes | Original instructions |
| --- | --- | ---: | ---: |
| `InputInf::routing_for_view(int) const` | `0x00421990` | **49/49** | **16** |
| `InputInf::bindings_for_view(int)` | `0x004217F0` | **27/27** | **10** |
| `InputInf::pad_device(int) const` | `0x00421850` | **26/26** | **10** |
| `InputInf::pad_device_slot(int)` | `0x00421870` | **26/26** | **10** |

**128 disjoint whole original game-owned native bytes**
are newly admitted to the existing
`src/InputInf.cpp` canonical source provider.
Their complete original SHA-256 digests
in the same order are:
`a1bacdc4d0a40e504257af319f24f60a6f8af11eaa6df6b9dc564f2aac1d025a`;
`4cb99a91257ad2336b2f70f0c62e14abbe7116bbd118e1a27869d3dc65f26370`;
`a9c7a95eab63f554f4eeb0365a4d4fd8d6359beaab74f81f6401d5dd1567ceb7`;
`7784b7f2fd24da6cef0430d260817c56ccbf0057419cc884eb41d1e6e20b45e1`.

The real 49B route resolver returns **-1 for
logical view 1**, otherwise returns the genuine
`InputInf::routing_2e24[view]` at original
+0x2E24 + view×4. The natural C++ conditional
expression `view == 1 ? -1 : routing_2e24[view]`
produces the original 16 instructions. A
semantically similar early-return form emitted
only 37 bytes instead of the native 49 and was
rejected. The original 3,490B device frame calls
this exact method at its native **+0x081** call
site.

The original 27B bindings accessor returns
the genuine `InputBindings*` located at
`InputInf+0x2E38 + view×0x30`, using the
same full 48-byte game-owned binding class
constructed by the exact InputInf constructor.
It is called by the original large frame
at **+0x0C0**.

The two separate 26B pad accessors read and
take the address, respectively, of the
native `IDirectInputDevice8W*` pointer array
at `InputInf+0x2E14 + index×4`.
Both preserve the true four-element
DirectInput COM resource layout already
established by the independently exact
466B `InputInf::shutdown` boss and the
261B InputInf ctor. They are distinct physical
native functions, not duplicate aliases.

All four original whole functions have
**zero native direct E8 and zero PE HIGHLOW
fields**, independently verified from
the immutable original .text/.reloc.
Each strict comparison checks **every byte**
unmasked: **49/49, 27/27, 26/26 and
26/26**. Independently original
native SHA and complete instruction counts:
`.analysis/core480-input-update-native-proof.json`.

## Parent's remaining native call frontier

Before these new methods, **9/21** of the
original 3,490B frame's direct E8 call
sites led to separately accepted strict
native unit bodies. The two real frame
calls to the new 49B routing and 27B
bindings methods now raise that to
**11/21**. Remaining native direct
destinations include the original CRT
`memset`, compiler
`std::lock_guard<std::recursive_mutex>`
ctor/dtor, native XInput ordinal wrapper
and the original security-cookie check.
Original API indirect COM calls are
separate and already present in the
whole original 747-instruction audit.
No original byte of the still-unimplemented
3,490B enclosing function is inferred
exact from these exact callees.

## Real changed-header-receipt scoped replay

Only the real four method declarations in
`src/InputInf.hpp` and genuine source
definitions in the previously canonical
`src/InputInf.cpp` owner changed. Before
editing, actual locked compiler receipts
identified exactly **three old source
providers with six native strict units**:
`src/InputInf.cpp`,
`src/InputInfConstruction.cpp` and
`src/InputInfShutdown.cpp`.
The four complete new original helper
functions in the existing InputInf
accessor source give **10/10 strict
original units in three freshly
cold-built source objects**, replayed
serially at low priority.

All earlier real original 261B constructor,
120B destructor, 49B compiler deleting
support, 466B DirectInput shutdown,
50B interface release and 26B view
accessor remain whole strict exact.
Source-scoped exact proof:
`.analysis/core480-input-helpers-complete-scoped-replay.log`;
previous real receipt closure:
`.analysis/core480-input-update-preedit-closure.json`.

Three original diagnostic strings in the
unchanged 466B InputInf shutdown and two
ctor/destructor diagnostics had only
MSVC compiler-private `$SG` label number
changes because the class header changed.
Their immutable original PE destinations
and complete unrelocated body bytes were
independently checked before updating only
the private symbol spellings. Evidence:
`.analysis/core480-shutdown-private-label-original-proof.json`
and
`.analysis/core480-compiler-private-labels-pe-proof.json`.

No global cold replay, new original bytes
credited to the 3,490B input frame,
manual padding, or linked runtime
equivalence is claimed.


## CORE/EXACT-484 — adjacent entire InputInf startup boss closed

A distinct genuine InputInf **265-byte / 75-instruction**
startup routine at `0x00420990`, which copies two
native 48-byte Graphics.InputBindings records into
the input manager, calls the still-open original
465B `initialize_devices` at `0x00420D80`, and
publishes four original InputButtonState process
pointers, is now **entirely 265/265 original native
byte exact**, with two E8 and six HIGHLOW fields.
This is a substantive earlier stage in the same
input-device ownership/protocol as the still-open
**3,490B input polling update** at `0x00421B00`;
it does not imply that polling routine is exact.
Actual preedit `InputInf.hpp` source receipt closure
passed **11/11 strict native units across four
cold objects**, with no full cold replay.
[Complete InputInf startup proof](INPUT_INF_START_265_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-487 complete original input device initialization

The original **465-byte / 118-instruction**
`InputInf::initialize_devices` at `0x00420D80`
now is **entirely 465/465 strict native exact**, with
**9 independently original E8 and 6 original
PE HIGHLOW** fields. It closes a real stage in
the same input system: previous InputInf COM
shutdown, native keyboard device creation, DirectInput
and XInput device discovery calls, signed device
routing and persistent Graphics configuration.
Its genuine **726B/170B** discovery callees
still remain **NONEXACT**. The separately
original **3,490-byte InputDevice polling frame**
at `0x00421B00` also remains **NONEXACT**;
the 465B initialization does not imply any of that
parent/other-root original byte credit. Previous
Configuration/InputInf header compiler receipts
yielded **61/61 strict original units across 18
freshly cold-built source objects**, and no full
repository replay was performed.
[Original 465B game device initialization proof](INPUT_INF_INITIALIZE_DEVICES_465_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-489 — exact whole native XInput discovery

Earlier descriptions of the separate original
`InputInf::discover_xinput_devices` at `0x004210D0`
as NONEXACT were historical. This native
**170-byte / 57-instruction** complete original
game function is now **170/170 strict exact**.
The actual Windows SDK `XINPUT_STATE`
has 16 native bytes; an original local
`DWORD` result preserves the exact native
`mov` and `cmp` after original
`XInputGetState`. All **4 native E8
plus 1 PE HIGHLOW** fields are separately
original-attested, including the genuine
imported XInputGetState thunk at
`0x005406C6`. It compiles naturally in
the same original profile and existing
InputInf device-initialization source as
the previously exact **465B** parent.
**2/2 strict native units in one actual
cold source object** passed with no
shared-header change and no full replay.
The separate **726B DirectInput discovery**
and **3,490B InputDevice polling** remain
NONEXACT, without inherited exact byte
credit. See [whole original XInput discovery
proof](INPUT_INF_XINPUT_DISCOVERY_170_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-495 — actual original DirectInput boss closed

**Current status:** the entire original game-owned
`InputInf::discover_directinput_devices` at
`0x00420AA0` (**726/726B, 209 original x86
instructions, 16 native E8 + 18 PE HIGHLOW**)
and `InputDevice::initialize_directinput`
at `0x004219D0` (**218/218B, 68 original
instructions, 3 E8 + 8 HIGHLOW**) are now
separately whole strict exact. The distinct
17B `InputInf::direct_input_handle_slot`
at `0x00421830` is also 17/17 exact.
All three contribute **961 unique native
game-authored original bytes**. Four source-level
WindowState/InputInf C++ getters/setters whose
original physical addresses were *already*
strict exact remain native folded aliases:
**zero duplicate original byte credit**.

They recover the actual Windows DirectInput8
SDK COM device creation, keyboard format/cooperative
level and failure rollback, native game-controller
enumeration, real 0x2EF8-byte InputInf layout,
true COM pad attachment, Graphics DIDEVCAPS
and original diagnostic strings.
Actual previous locked compiler receipt union
of InputState.hpp, WindowState.hpp and InputInf.hpp
was **17 old source providers/82 strict units**.
Two new entire game method source owners and one
new method in existing InputInf owner yield
**85/85 strict native units in 19 serial
source-only cold objects**, no full replay.
All original targets were independently PE-attested
before canonical admission. **Historical claims**
above that the 726B DirectInput discovery remains
NONEXACT are superseded. The separate
3,490B InputDevice polling boss at
`0x00421B00` remains **NONEXACT**.
[Whole original 726B DirectInput and 218B
native pad methods](INPUT_INF_DIRECTINPUT_DISCOVERY_726_EXACT_RECONSTRUCTION.md).
