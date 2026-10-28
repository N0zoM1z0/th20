# CORE/EXACT-487 — complete original 465-byte InputInf device initialization boss

Immutable comparison original: Japanese TH20 v1.00a Steamless PE,
entire SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete native game-authored `InputInf::initialize_devices()` at
`0x00420D80` is now **465/465 original-byte strict exact**, all
**118/118 original i386 instructions**, under the pinned
MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /sdl /EHsc` source profile.
The immutable whole body SHA-256 is
`2b252897fbb438e3ac5e59aaa101f35590ade38b19f2cbcde260e6d0482f34c4`.

The typed maintained C++ is `src/InputInfDeviceInitialization.cpp`.
This checkpoint contributes **one entire original game-owned
465-byte body**, distinct from the already exact 265B
InputInf startup, 466B shutdown and input child constructors.

## Entire real native device initialization and gameplay routing

The actual `InputInf` class identity is established by original
PE RTTI `.?AVInputInf@@`, type descriptor at `0x005B41F8`.
The complete original 465B method executes the following protocol:

1. Calls the **separately exact 466B**
   `InputInf::shutdown()` at `0x004202C0`, releasing
   prior keyboard/pad devices and the actual native
   `IDirectInput8W*` with genuine original COM ABI.
2. Acquires `process_locks.slot(15)` at original
   global `0x005C0240` using an authentic
   `std::lock_guard<std::recursive_mutex>`,
   preserving original exception handler, RAII
   release and native compiler security cookie.
3. Initializes native signed device count
   `InputInf::state_14` to zero, constructs the
   first keyboard device at actual
   `InputInf+0x20 + state_14*0x3D4` through the
   previously exact whole `InputDevice::initialize_keyboard`
   at `0x00421AB0`, then increments the
   actual device count.
4. Calls the genuine **726B** native DirectInput
   discovery routine at `0x00420AA0` and **170B**
   XInput discovery routine at `0x004210D0`.
   Both are separate **NONEXACT** native children;
   this checkpoint does not claim or credit them.
5. Emits the real `Pad Num : %d` diagnostic
   with the current native device count.
6. Recovers the selected input route from
   original `process_graphics.configuration.values_68[0]`
   at `0x005C4F70`, sets native
   `InputInf::routing_2e24[1]` to `-1`, then
   limits/reassigns `routing_2e24[0]` based on
   **signed** comparisons of the number of
   discovered devices (including the original
   special case for second routing slot `1`).
   Finally writes the selected value back to
   the true Graphics configuration array index zero.
7. Ends the original lock guard's lexical lifetime
   and returns integer zero, following the original
   native exception/cookie cleanup protocol.

The game-owned member offsets, recursive mutex type,
keyboard ctor receiver, actual two-slot Graphics
configuration source, signed device count and native
routing rules are all corroborated by the independently
original i386 body; none are inferred solely from a
Ghidra C decompiler pseudotype.

## Corrected two original C++ type assumptions by comparing the PE

The previous maintained `ConfigurationCounterPair`
described two 32-bit fields as `first, second`.
The actual original 465B native code accesses
the first element using **a C-array index zero**,
twice, through independent original address arithmetic.
Representing the eight-byte counter pair as
`std::uint32_t values[2]` preserves exactly the
same complete object size and offsets and naturally
generates the original two separate `4 * 0`
address calculations. A scalar `.first` read/write
emitted a shorter 448-byte wrong candidate and was
rejected. Both existing ConfigurationCounterPair
members at offsets +0x68 and +0xA8 retain their
eight-byte storage extents and initialization semantics.

Independently, `InputInf+0x14` is a true
**signed** device count under native comparisons.
The originally maintained unsigned declaration
emitted `ja/jbe` in three sites where the original
PE executes `jl/jle`. Reconstructing
`std::int32_t state_14` and comparing the
route value before that count restores native
operand evaluation, branch direction and
the entire original register/stack sequence.

The resulting maintained function is not padded,
a decompiler byte transcription, an inline-assembly
body, or a shortened original prefix. It emits
exactly **465/465 original bytes** naturally.
These two public-header type corrections were
then checked against all previous exact canonical
units affected by the real include graphs.

## Original 9 E8 and 6 PE HIGHLOW references

The immutable original function was freshly decoded
before canonical admission. Exactly **nine native
direct-call E8/REL32** and **six native PE
.reloc HIGHLOW/DIR32** fields were independently
collected, all agreeing with the actual emitted
compiler COFF symbol identities and true addends:

| Native field | Type | Immutable original destination | Genuine role |
| --- | --- | --- | --- |
| `+0x006` | DIR32 | `0x0056808D` | original EH handler descriptor |
| `+0x015` | DIR32 | `0x005B25C0` | native compiler security cookie |
| `+0x02F` | REL32 | `0x004202C0` | exact 466B InputInf shutdown |
| `+0x036` | DIR32 | `0x005C0240` | original LockRegistry object |
| `+0x03B` | REL32 | `0x0040C310` | exact recursive mutex slot 15 selector |
| `+0x044` | REL32 | `0x0040B730` | genuine recursive lock_guard constructor |
| `+0x078` | REL32 | `0x00421AB0` | exact InputDevice keyboard constructor |
| `+0x08F` | REL32 | `0x00420AA0` | separate still-nonexact 726B DirectInput discovery |
| `+0x097` | REL32 | `0x004210D0` | separate still-nonexact 170B XInput discovery |
| `+0x0A3` | DIR32 | `0x0056D6D4` | original Pad Num diagnostic string |
| `+0x0A8` | REL32 | `0x0040C6B0` | exact game diagnostic emitter |
| `+0x0C4` | DIR32 | `0x005C4F70` | `process_graphics` original base +`0x230` |
| `+0x19B` | DIR32 | `0x005C4F70` | same original graphics base +`0x230` |
| `+0x1B1` | REL32 | `0x0040B900` | native recursive lock_guard destructor |
| `+0x1C9` | REL32 | `0x005429EE` | native security-cookie check |

The two original Graphics PE destinations both
encode `0x005C4F70`. The actual COFF relocations
refer to **one** previously original-attested
`process_graphics` object at `0x005C4D40`
with two real **`+0x230` addends**.
The canonical manifest records the actual base,
not an invented global absolute variable at
`0x005C4F70`.

The actual maintained compiler-private
`Pad Num` literal is `$SG171361` at the
independently original `0x0056D6D4`
location, compared to an earlier private
probe label `$SG171360`. The immutable
original literal and exact field location/type
were reread before accepting the maintained
private symbol. Full original immutable PE
proof:
`.analysis/core487-inputinf-initialize-original-pe-proof.json`;
maintained source symbol reconciliation:
`.analysis/core487-maintained-source-original-pe-audit.json`.

**All 405/405 original nonrelocation bytes and
60/60 original relocated bytes** agree with the
immutable whole 465-byte original body.

## Only actually affected compiler-receipt closure

Before touching either shared native header,
existing locked MSVC compiler receipts were
independently enumerated. The previous real
`Configuration.hpp` include graph contained
**17 canonical source objects / 60 old strict
native units**; `InputInf.hpp` contained
four objects / 11 old strict units, all within
the first set. Their **actual union** was
therefore exactly **17 old sources / 60 strict
native units**, not the entire reconstruction
repository.

Adding `src/InputInfDeviceInitialization.cpp`
as one new original source owner produced
**18 source providers / 61 strict native units**.
Exactly that original-receipt union was cold
recompiled serially at reduced scheduling
priority in five bounded batches, with
**13/13 + 14/14 + 23/23 + 6/6 + 5/5 =
61/61 native strict units exact**, all
**18/18 cold objects**. Other original
Graphics, Bullet, Enemy, render, Configuration,
InputInf lifecycle and sound canonical
methods remained full exact.

Both header changes naturally renumbered
six MSVC-private `$SG` source-local diagnostics
in existing InputInf constructor/destructor,
shutdown and startup owners. A separately
bounded reconciliation routine accepted
**only** private label spellings after verifying
the **same immutable PE absolute literal target,
same relocated field offset/type, and complete
unchanged nonrelocation original byte equality**
under the locked compiler receipt. No
original PE target, code length, C++ behavior
or acceptance rule was changed to hide a
mismatch. Evidence:
`.analysis/core487-reconciled-private-symbols.json`.

Old original receipt scope:
`.analysis/core487-inputinf-initialize-preedit-closure.json`.
Exact source groups:
`.analysis/core487-actual-source-replay-groups.json`;
five full strict logs:
`.analysis/core487-scope-replay-batch0.log`
through `batch4.log`.

This newly credits **one complete 465-byte
game-authored native function**, without
double counting its existing 466B shutdown,
265B startup, 261B constructor, 120B destructor
or 49B compiler-generated deleting support.
The original 726B DirectInput discovery,
170B XInput discovery, 3,490B InputDevice
frame polling, 555B Player motion and
3,111B Player main frame are independent
open original functions and remain
**NONEXACT**. No unfiltered whole-repository
cold replay, binary patch or linked-game
runtime equivalence is asserted.


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
