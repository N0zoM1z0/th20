# CORE/EXACT-467 — entire native InputInf manager constructor, 261B plus five original CC alignment bytes

Original comparison target: immutable Japanese TH20 v1.00a Steamless,
whole executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original complete **261-byte / 72-instruction** game-owned
`InputInf::InputInf()` at `0x0041F8A0` is now strict whole-native exact
as genuine C++ in `src/InputInfConstruction.cpp`. Its original
whole-body SHA-256 is
`927c68af53c8c087d55a6f44f0d57278f5b48fbdce9229cb6e8fc22bcb187598`.
The native MSVC compiler's physical function contribution also includes
**five genuine `CC` alignment bytes** immediately following the actual
261-byte return. These five bytes are present in the *immutable original
PE*, not invented or ignored. The protected canonical unit declares
`size = 261` and `compare_size = 266`, so the **entire 266/266
original comparison interval** must match while only the **261-byte
game-authored body** contributes to native game-exact statistics.

## Real RTTI, owned data and complete native gameplay initialization

Independent original PE RTTI at `0x005B41F8` identifies
`.?AVInputInf@@`; the InputInf native vtable at
`0x0056D4D0` is independently established. The true receiver
inherits 16-byte `TaskInfo` and owns actual game fields, not a
fabricated 0x2E30-byte dummy object:

| Original receiver offset | Native construction |
| --- | --- |
| `+0x00` | call real `TaskInfo::TaskInfo()` at `0x0041FD20` and publish real derived vtable |
| `+0x10..+0x1C` | clear four 32-bit state words individually |
| `+0x20` | construct **12 native `InputDevice` objects**, real element stride `0x3D4` |
| `+0x2E10,+0x2E14` | clear two retained 32-bit values |
| `+0x2E18,+0x2E24` | clear each of two 3×32-bit retained/routing arrays |
| `+0x2E30` | clear two actual `InputButtonState*` view pointers |
| `+0x2E38` | construct **four actual `InputBindings` objects**, real element stride `0x30` |
| original global `0x005B8898` | publish this live manager pointer after diagnostic initialization |

The native `InputDevice::InputDevice` body at `0x0041FCB0`
is separately **102/102 exact** and its nested actual
`InputButtonState` ctor at `0x0041F9B0` separately
**340/340 exact**, both from CORE/EXACT-463. The 0x30-byte
`InputBindings::InputBindings` ctor at `0x0041FB10` is also
independently exact in its preexisting canonical unit.
The real source uses **two actual C arrays**,
`InputDevice devices[12]` and `InputBindings bindings[4]`,
rather than adding extra `std::array` wrapper code. All original
member offsets survive the type correction, including
`InputInf+0x2E30` used by the independently exact 26-byte
`InputInf::for_view`.

The original emits a diagnostic request for
`initialize InputInf` and then writes `this` to the real
global manager pointer, naturally completing the 261-byte
ctor's published lifetime protocol. Original runtime
startup order and the rest of the game's linked executable
are independent open questions.

## Why the original source emits exactly the exception-aware 261-byte boss

Using `std::array<InputDevice,12>` under MSVC 19.44
generated a two-argument internal array initializer
helper, **not** the four-argument native
`_eh vector constructor iterator` at `0x0040BC20`
observed in the original. Changing only to the real
C-array types with `devices()`/`bindings()` produced
the original native four-argument vector constructor
calls, but with an extra **two seven-byte exception
cleanup state stores** (275 bytes / 74 instructions).

Declaring and defining the real derived constructor as
`InputInf() noexcept` allowed the same pinned MSVC
`/Od /Ob0 /GS /sdl /EHsc` profile to generate
exactly the original body: **261 complete native bytes /
72 original instruction heads**, without the two
unobserved EH cleanup stores. The genuine exception
handler registration, compiler security cookie and
checks, base class construction, vector constructor
calls and destructor-safe boundaries remain present.
The original disassembly, not hypothetical C++ exception
design, determines the accepted binary ABI; source-level
exception guarantees outside the original program's
exercised paths remain a distinct validation concern.

The actual locked compiler COFF function contributes **266
bytes**: 261 game instructions and five final `CC` bytes.
The original PE also contains these five `CC` bytes at
`0x0041F9A5..0x0041F9A9`, and the next independently
original game function begins at `0x0041F9B0`.
No previous canonical game unit occupies this tail.
The complete **266/266 strict original bytes** are
accepted by the *unchanged* oracle with **only 261/261
game-authored native coverage bytes**. No shortened
prefix comparison, compiler-byte injection or manually
inserted NOP/CC was used.

## Eleven independently original PE relocation fields

The whole 261-byte original game body was freshly decoded as
72 native instructions; direct E8 operands and original
`.reloc` HIGHLOW fields were collected before admission.
There are exactly **four original E8/REL32** and
**seven original PE HIGHLOW/DIR32** references, all at
real immutable original locations:

| Original field | Type | Original physical target | Genuine native role |
| --- | --- | --- | --- |
| `+0x06` | DIR32 | `0x00567600` | original exception handler |
| `+0x13` | DIR32 | `0x005B25C0` | security cookie |
| `+0x2A` | REL32 | `0x0041FD20` | already exact TaskInfo constructor |
| `+0x33` | DIR32 | `0x0056D4D0` | RTTI-proven derived InputInf vtable |
| `+0x60` | DIR32 | `0x0041FCB0` | separately exact 102B InputDevice ctor |
| `+0x73` | REL32 | `0x0040BC20` | original native vector constructor iterator |
| `+0xC7` | DIR32 | `0x0041FB10` | independently exact InputBindings ctor |
| `+0xDA` | REL32 | `0x0040BC20` | second native vector constructor iterator |
| `+0xDF` | DIR32 | `0x0056D4DC` | true `initialize InputInf` diagnostic literal |
| `+0xE4` | REL32 | `0x0040C6B0` | real ecl diagnostic function |
| `+0xEF` | DIR32 | `0x005B8898` | original global InputInf publication |

All **11/11 native field offsets, types, original destinations,
COFF symbols and true addends** agree. No fields are suppressed
when comparing the five native trailing alignment bytes.
The full original interval SHA-256, independent original E8
decoding, independent PE HIGHLOW scan, every original
compiler symbol and original aligned tail are in
`.analysis/core467-inputinf-ctor-original-pe-proof.json`.
Under the unchanged strict comparison, **222/222
nonrelocation and 44/44 relocation bytes** across the
266-byte original physical contribution are accepted.

## Scoped compiler-receipt replay and zero duplicate child credit

The only existing public declaration changed is
`src/InputInf.hpp`, to expose the actual `noexcept` ctor
and native C array of 12 input devices. The newly
completed function is kept in its own canonical source
`src/InputInfConstruction.cpp`, because its original
`/GS /sdl /EHsc` profile differs from the existing
26-byte `src/InputInf.cpp` accessor's locked
`/GS- /Gd` profile. It gains a **new native canonical
source/object provider** without changing the existing
InputInf accessor's original code or class layout.

**Before editing**, old locked compiler receipts for
`InputInf.hpp` identified exactly **one prior
provider / one strict unit**, `src/InputInf.cpp`.
Adding the new original ctor in one new source gives
**2/2 strict original units across exactly two
freshly cold-built sources**, replayed at reduced
priority:
`.analysis/core467-inputinf-preedit-closure.json`
and
`.analysis/core467-inputinf-constructor-scoped-replay.log`.
The original 26B `for_view` remains 26/26 exact, and
the separately original 340B/102B input child ctors
remain exact in their unchanged source owner.

**Only 261 newly accepted original game-authored bytes**
are credited. The five real aligned CC bytes are
strictly compared but not counted as additional
gameplay instructions, and previously exact child
constructor bodies are never recredited. The
still-open whole **555B Player movement** and
**3,111B Player main-frame** routines do not gain
exactness from this InputInf ctor. No unfiltered
whole-repository cold replay was run.


## CORE/EXACT-472 — subsequent native InputInf lifetime closure

The original 120B `InputInf::~InputInf` at `0x0041FD70`
is now **120/120 game body +125/125 full original compiler
alignment bytes strictly exact**. Its separate compiler-emitted
49B scalar deleting wrapper at `0x0041FE10` is **49/49
strictly exact support**, not a second authored game function.
They share this existing canonical translation unit with the
still exact 261B constructor. The only compiler-private
string renumber preserved its independent original native target
`0x0056D4DC` and the full unchanged original body.
**4/4 strict units in two source-scoped cold objects** passed,
no full replay. The separate 466B InputInf shutdown remains
NONEXACT.
[Whole original destructor and deleting-wrapper proof](INPUT_INF_DESTRUCTOR_120_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-476 original InputInf device shutdown closure

**CURRENT STATUS:** earlier assertions in this document
that the native **466B `InputInf::shutdown`
at `0x004202C0`** is still nonexact are now
historical and superseded. Its entire original
**466/466 native bytes, 127 instructions,
nine immutable E8 fields and six PE HIGHLOW
fields** are now independently strict exact
using genuine DirectInput SDK methods, native
recursive-mutex guard, 12 InputDevices and four
typed pad-device COM pointers. The separate
**50B `InputInf::release_direct_input`
at `0x004216E0`** is also whole 50/50 exact.
Original native memory types now include
a `IDirectInput8W*` at +0x1C and
`IDirectInputDevice8W*` at +0x2E10 and
four genuine pad pointers at +0x2E14.
Actual old `InputInf.hpp` receipts selected
two source providers/four protected units;
with two new complete methods in one new
source, **6/6 strict original units in three
cold objects** passed. Old 261B constructor
(including its five real CC alignment bytes),
120B destructor, 49B compiler deleting
support and 26B view lookup are still
whole exact. Only private MSVC diagnostic
`$SG` identities were renumbered after
independently verifying the unchanged original
PE string targets and entire native bytes.
The separate 3,490B input frame processing
remains NONEXACT; no global cold replay ran.
[Whole native 466B+50B InputInf shutdown and COM release proof](INPUT_INF_SHUTDOWN_466_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-484 complete original InputInf start

The real original 265B `InputInf::start` at
`0x00420990` is now **265/265 native strict exact**,
with all 75 original x86 instructions,
two immutable E8 and six original HIGHLOW fields.
Its three graphics-configuration accesses
share one true original global `process_graphics`
base `0x005C4D40` with authentic +0x1D0/+0x1E0/+0x1F0
relocation addends, and its process input global
view pointers are independently native-attested.
Natural source copies the three 16B InputBindings
submembers independently to preserve exact codegen.
The original 465B device initializer it invokes
remains NONEXACT. Actual original `InputInf.hpp`
compiler receipts identified three prior providers
with ten earlier strict units; the new one-source
native start method yields **11/11 whole strict
units across four serial cold objects**, including
this unchanged exact 261B constructor.
No full-repository cold replay was used.
[Whole original 265B InputInf startup](INPUT_INF_START_265_EXACT_RECONSTRUCTION.md).
