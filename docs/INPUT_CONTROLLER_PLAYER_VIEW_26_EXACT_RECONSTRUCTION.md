# CORE/EXACT-454 — exact whole 26-byte Player input controller view lookup

Original comparison target: immutable TH20 Japanese v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00498FB0` game-owned input manager lookup is now
**26/26 original bytes exact**, all **10/10 whole native
i386 instructions**, in the existing source owner
`src/InputState.cpp` as `InputController::for_view(int)`.
Complete original function SHA-256 is
`ad0717a1cf2afc2f9bac7c9fef0f32b4bdcd9a34b04e30d36cdd1b8239116ef2`.

## Independent original runtime controller / Player input ABI

This function receives the live `InputController` receiver
in ECX and a single signed logical player/view index on
the stack. The actual original loads exactly one
`InputButtonState*` from the controller's pointer table
at native byte offset **`+0x2E30 + index*4`**,
returns it through EAX and ends with original
`ret 4`. The full interval contains no external
E8 calls and **no original PE `.reloc` HIGHLOW
fields**.

The separate original **3,111-byte Player main frame**
at `0x004F9C30` independently reads the actual
Player `view_index` at `Player+0x14854`,
then passes that value to this function at its
original callsite **`+0x3D`**, using the
global runtime controller pointer stored at
**`0x005B8898`** as the ECX receiver.
The returned `InputButtonState*` is consumed
by ten calls to the already exact
`InputButtonState::replay_current_bits`
at `0x004973A0`, reading the actual
input replay current field at **`+0x29C`**.
This establishes game-specific source ownership
and the true pointer return type, rather
than relying on a speculative Ghidra class label.

The original runtime controller has other independently
observed intrusive device/observer storage, including
a real intrusive list at `+0x10` in its
separate 230-byte controller method at
`0x00498FF0`, but its **whole 0x2E30-byte
preceding memory layout is not yet reconstructed**.
The maintained source therefore declares only a
partial `InputController` with the real method.
It expresses the actual known pointer-table byte address
with `std::uintptr_t` and 32-bit modulo index
arithmetic, then reads a correctly typed
`InputButtonState*` pointer from that native
slot. It **does not invent a 0x2E30-byte
dummy padding array, fictitious member fields,
a fabricated complete sizeof(InputController),
or fake lifecycle behavior**. The normal
C++ source is target-specific to the locked
MSVC PE32 runtime and requires an actual
live, correctly laid-out controller and valid index.

A probe first stored the intermediate byte address
in a local value, which generated 36 bytes under
native `/Od`, not the target. Natural in-line address
calculation with the same real source semantics
emits the entire original **26 bytes and ten
instructions** with no artificial stack-shaping
variable, manual NOP or copied code.

## Whole original PE and exact source validation

The immutable original 26-byte range was fully decoded
separately from the source and from the Ghidra
decompiler hypothesis. Both original E8/REL32 and
PE HIGHLOW/DIR32 collections are empty,
as are the source's COFF external relocation
fields. Therefore this match compares **all
26 original bytes directly**, no relocation
masking or unknown target resolution is needed.
Original native SHA, this-pointer slot addressing,
actual 3,111B original caller and original
global manager / Player view-index addresses are
in
`.analysis/core454-input-manager-original-proof.json`.

The maintained definition was added to
`src/InputState.cpp` and its partial receiver
declaration to `src/InputState.hpp`, using the same
previously locked MSVC 19.44 i386 C++20
`/Od /Ob0 /GS- /Gy /Zl /arch:SSE2
/fp:precise /Gd` profile and unchanged
`build/core141-canonical/InputState.obj` owner.

**Before changing the header**, actual canonical
compiler include receipts selected exactly
**one existing source provider with twelve
old strict native units**. The one newly
admitted complete original 26B input lookup
gives **13/13 strict original units
in one freshly cold-built object**; all
existing input/replay lookup, native frame
updaters and button state functions remain
whole exact. Private old source scope:
`.analysis/core454-input-manager-preedit-closure.json`;
full focused replay:
`.analysis/core454-input-controller-scoped-replay.log`.

This checkpoint credits **one game-owned
whole native function and 26 original
bytes**. The 3,111-byte original Player
main frame now has **66/67 direct native
E8 call sites** pointing to separately
canonical-exact native callees. The sole
remaining nonexact called body is the entire
555-byte `Player::apply_move_delta` at
`0x004FFA10`. The enclosing 3,111-byte
parent remains **NONEXACT**, and its
unreconstructed code is not credited
from these callees. No unfiltered
whole-repository cold replay was run.
