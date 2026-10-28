# CORE/EXACT-455 — original InputInf RTTI and constructor-proven input owner correction

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
