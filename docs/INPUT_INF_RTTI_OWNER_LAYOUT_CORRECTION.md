# CORE/EXACT-455 — original InputInf RTTI and constructor-proven input owner correction

**CORE/RECON-508 correction:** The original `+0x2E30` pair are signed integer process-view selectors, **not** InputButtonState pointers. The previous pointer interpretation and related claims below were mistaken; the same 26-byte getter remains whole strict exact. See the independent [signed-index proof](INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md).


This is an **original-native ownership and C++ type accuracy correction** of an
**already exact** original function. The immutable comparison target remains
Japanese TH20 v1.00a Steamless, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The physical original `0x00498FB0` has always been the same complete
**26-byte / 10-instruction** game input source lookup, SHA-256
`ad0717a1cf2afc2f9bac7c9fef0f32b4bdcd9a34b04e30d36cdd1b8239116ef2`.
CORE/EXACT-454 earlier accepted it as
`InputController::for_view(int)` on an intentionally partial, guessed
owner because no complete object prefix had been established then.
**That earlier class attribution is superseded by real original PE
RTTI and original constructor data.** This checkpoint does **not**
discover another 26-byte native body, increase native exact bytes, or
claim the manager constructor is exact.

## Immutable executable identifies the original class name

The original `InputInf` vtable at **`0x0056D4D0`** has a
genuine MSVC complete-object-locator pointer at vtable[-1]
**`0x005A36C0`**. That locator points to the native type
descriptor at **`0x005B41F8`**, whose original decorated RTTI
name is exactly **`.?AVInputInf@@`**. Independent original
diagnostic strings mention `initialize InputInf`,
`start InputInf`, `shutdown InputInf` and
`D:\cygwin\home\zun\prog\th20\src\core\pad.cpp`.
These immutable observations prove the actual enclosing game class is
`InputInf`, not the provisional `InputController` spelling.

## Actual 261-byte native InputInf constructor proves the members

The separate original constructor at **`0x0041F8A0`**,
**261 complete bytes**, SHA-256
`927c68af53c8c087d55a6f44f0d57278f5b48fbdce9229cb6e8fc22bcb187598`,
constructs the already authenticated 16-byte TaskInf/TaskInfo base,
publishes the real InputInf vtable and initializes the following
**actual physically observed members**:

| Native InputInf offset | Proven storage | Independent original evidence |
| --- | --- | --- |
| `+0x00` | 16-byte TaskInfo-compatible virtual base | original constructor calls native `0x0041FD20`; RTTI vtable |
| `+0x10..+0x1C` | four 32-bit state words | constructor individually writes all four |
| `+0x20` | 12 `InputDevice` elements, each **0x3D4** bytes | compiler's native vector constructor: count 12, stride 0x3D4, start +0x20 |
| `+0x2E10, +0x2E14` | two retained 32-bit fields | constructor clears both |
| `+0x2E18` | three 32-bit retained state entries | constructor clears all three |
| `+0x2E24` | three 32-bit device routing entries | constructor clears all three |
| `+0x2E30` | **two `InputButtonState*` view pointers** | constructor zeros both, and original 26B accessor indexes them |
| `+0x2E38` | four `InputBindings` elements, each **0x30** bytes | original vector constructor: four records, 0x30 stride, start +0x2E38 |

The true `InputDevice` is already independently reconstructed as a
**0x3D4-byte** object with native button state at +0x10 and raw input
bytes at +0x2D0; `InputBindings` is already a true **0x30-byte**
triple of 0x10-byte signed binding sets. All now appear as real typed
members of `src/InputInf.hpp`, without a single byte of fabricated
anonymous prefix or arbitrary compiler-shaping filler.

The source uses an actual `TaskInfo` base, typed twelve-element
`std::array<InputDevice,12>`, the two proven pointer slots and
four native bindings. MSVC x86 compile-time assertions verify all
observed offsets, including the crucial pointer table
**`offsetof(InputInf,active_buttons)==0x2E30`** and
binding array `+0x2E38`. The source representation currently
covers the constructor-attested prefix through `+0x2EF8`;
whether original game storage extends further remains **unclassified**
and is **not** asserted from this prefix alone.
The separate 261B constructor remains **NONEXACT** and is not claimed
reconstructed by these declarations.

## Exact original runtime consumer and its true type

The original complete 3,111-byte Player main frame at
`0x004F9C30`, itself still NONEXACT, loads the
global input-owner pointer at **`0x005B8898`** and the Player's
`view_index` at `Player+0x14854`. At original direct-call
offset **`+0x3D`** it passes the input owner in ECX and one
signed index on the stack to `0x00498FB0`. The returned object
is a real `InputButtonState*` and is consumed by ten separate
original calls to the already exact input replay-bitmask reader at
`InputButtonState+0x29C`.

The physically original 26B routine directly loads
`[ecx + eax*4 + 0x2E30]` and returns using `ret 4`.
The correct maintained source now expresses
`return active_buttons[logical_index];`
as a genuine member of the original RTTI-proven
`InputInf`, not an undefined-behavior-prone raw
`reinterpret_cast` from an incompletely modeled owner.
It naturally emits the **same 26/26 native original bytes**,
all ten instructions and **no E8 or original PE HIGHLOW**
fields. Its source-level method name `for_view` remains
descriptive; the original compiler's exact C++ spelling is
not independently proven merely by RTTI.

Immutable evidence in
`.analysis/core452-input-inf-original-layout-proof.json`
records the true vtable/COL/type descriptor, original
261B constructor SHA, typed offsets, original 26B original bytes,
global owner and Player callsite. The previous 26B original
byte proof remains separately valid; only its speculative
C++ owning type and source implementation were corrected.

## Real-source-only canonical migration, no duplicate credit

One already accepted canonical physical 26B unit formerly belonged to
`src/InputState.cpp` under `InputController`. Its exact **same
physical native address and bytes** are now maintained as
`th20::InputInf::for_view` in `src/InputInf.cpp` with the
new canonical object `build/core455-canonical/InputInf.obj`.
The existing `InputState.cpp` retains its other **12 native
strict units** and its true button/device source methods. Its
old provisional `InputController` declaration and raw
pointer-cast implementation were retired, not hidden or reset.

**Before editing**, real old compiler receipts for the changed
`src/InputState.hpp` selected exactly **one source provider /
13 previous strict units**. The new typed InputInf owner adds
**one separate cold source provider**, but **zero new physical
exact units**. The two affected sources passed **13/13 strict
units in two cold objects**: 12/12 in InputState and 1/1 in
InputInf. A further separate single-provider cold replay of the
unchanged full 1,081-byte Player option-frame boss passed
**1/1 strict original exact** after detecting its old broad
compiler-input inventory receipt was stale.
Evidence:
`.analysis/core455-inputinf-preedit-closure.json`,
`.analysis/core455-inputinf-scoped-replay.log`,
and `.analysis/core455-player-option-extra-replay.log`.

The canonical unit label was updated from
`input_controller_for_view` to `input_inf_for_view` and its source,
MSVC symbol and object receipt were corrected, including the
original function, origin, implementation, reccmp and matches
ledgers. There is still **exactly one** strict 26B native unit
at `0x00498FB0` and it contributes **exactly 26** original bytes
to the already-accepted game total. The canonical provider count
rises by one solely because the real input owner now has its own
translation unit. No full-repository cold replay or linked-game
runtime claim is made.


## Subsequent CORE/EXACT-463 two genuine InputInf child constructors

The constructor-attested `InputInf+0x20` array
has now gained both real whole native element
constructors as separate strict exact game functions:
`InputButtonState::InputButtonState()`
at `0x0041F9B0` (**340/340B**, 81 original
instructions, six original CRT memset E8 fields);
and `InputDevice::InputDevice()` at
`0x0041FCB0` (**102/102B**, 28 instructions,
a true E8 to the ButtonState ctor and a raw
0x100-byte memset). The two complete original
functions total **442 new disjoint native exact bytes**.
They use the class layout proven above, with
source-derived constructor interfaces and all
eight independently attested native PE E8 targets.
The full native **261B InputInf constructor** is
still separate and **NONEXACT**, with no inferred
byte credit. Real previous `InputState.hpp`
receipt closure passed **15/15 strict native
units in two cold source objects**; no
unfiltered full replay was run.
[Full original input child-constructor proof](INPUT_DEVICE_BUTTON_CTORS_442_EXACT_RECONSTRUCTION.md).


## Subsequent CORE/EXACT-467 complete original InputInf manager constructor

**CURRENT STATUS:** the original 261-byte `InputInf::InputInf()`
at `0x0041F8A0`, previously open in this historical
checkpoint, is now **261/261 complete strict original
native exact** (72 i386 instruction heads, 4 independent
E8 call fields and 7 independent PE HIGHLOW fields).
The source's **real C-array construction** and
`noexcept` ABI naturally invoke the original
four-argument native vector constructor iterator,
without the two unobserved compiler EH cleanup
state writes. The entire source compiler contribution
of **266 bytes** including the **five actual
original PE trailing CC alignment bytes** is
**266/266 strictly exact**, while **only 261
native game-body bytes** are credited.
The actual original `InputInf.hpp` compiler
receipt include closure passed **2/2 strict units
in two cold sources**. All earlier exact 26B
input accessor, 340B ButtonState and 102B Device
constructors remain separately full exact and
are not recredited. Historical statements above
that the 261B manager ctor remains nonexact
are **superseded**. See
[the entire InputInf manager construction PE proof](INPUT_INF_CONSTRUCTOR_261_EXACT_RECONSTRUCTION.md).


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
