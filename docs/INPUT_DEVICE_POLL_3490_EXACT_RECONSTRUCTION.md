# CORE/EXACT-501 — complete original 3,490-byte InputDevice polling boss, strict native exact

Comparison target: the immutable user-selected Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The entire original InputDevice::poll() at `0x00421B00..0x004228A1` is
strict canonical native exact: 3,490/3,490 original bytes, 747/747 native
x86 instructions and all 39 original PE-relative or absolute fields independently
reconciled.** This admission adds one complete game-authored original
function and 3,490 disjoint game-body bytes. It is not a whole-game link,
resource initialization, runtime-equivalence, or original translation-unit
identification claim.

## Original owner and full gameplay protocol

The genuine `InputDevice` receiver is a 0x3D4-byte x86 object. Its first
four words encode device kind, logical index, native `IDirectInputDevice8W*`
and XInput physical index. It owns the actual +0x10 `InputButtonState`, and
+0x2D0 direct 256-byte `raw` buffer. The `raw` member is now a genuine
C array, which preserves the same 0x3D4 layout as well as the native direct
CRT `memset` call rather than adding `/Od` `std::array` wrappers. Its
separately accepted 102-byte constructor remains strictly exact.

The whole maintained `src/InputDeviceFrame.cpp` body performs the native
pre-lock raw reset, uses `process_locks.slot(15)` and the actual recursive
`std::lock_guard` cleanup, selects the real `InputInf` routing/bindings,
and then handles all three original device types in physical code order:

1. **Keyboard 0:** the genuine imported `GetKeyboardState` fills the
   256-byte buffer when enabled; all eight signed keyboard binding fields,
   fixed Windows-key shortcuts and numeric keypad diagonals accumulate
   original individual button flags. A second native `kind` dispatch
   remains in the source rather than being optimized away by hand.
2. **XInput 2:** zero a genuine 16-byte Windows `XINPUT_STATE`, call the
   real ordinal-2 XInput import, combine the actual thumbstick/trigger
   thresholds with the 32-bit input masks at `0x005AE220`, then populate
   the twelve raw button/trigger byte slots and update device selection on
   a changed mask. Native threshold comparisons are emitted as signed
   `>= 0x1EA9`, `<= -0x1EA9`, and unsigned `>= 0x1E`, preserving the
   precise original boundary and instruction encoding without relying on
   misleading decompiler comparison orientation.
3. **DirectInput 1:** invoke genuine COM `Poll`, `Acquire`, and
   `GetDeviceState` vtable slots, including the original input-lost retry
   with its 400-attempt ceiling. Failed polling/acquisition exits through
   the real lock guard without modifying saved button history. On success,
   process the 272-byte `DIJOYSTATE2`, call the four original
   `map_input_byte` helpers in their correct physical order, independently
   reload signed Graphics axis thresholds at `0x005C4F78`/`0x005C4F7A`,
   mirror the first 32 native joystick button bytes and publish the device
   selection on changes.

Successful frames publish the previous/current bitfields, invoke the
separately exact 583-byte `InputButtonState::update()` at `0x004228B0`,
then release the actual mutex and return the accumulated 32-bit button mask.
The native physical 22-byte setter at `0x0041DE90` also carries the typed
`InputInf::set_last_input_kind` role; this is a linker-folded/shared body,
**not** another 22-byte unique exact-function credit. It was previously
known from the byte-interpolation instantiation.

## Closing the complete compiler frontier

The earlier whole-body source frontier in
[CORE/RECON-497](INPUT_DEVICE_FRAME_3490_SOURCE_FRONTIER.md)
emitted 3,720 bytes / 759 instructions, and was explicitly nonexact.
Independent new source probes recovered the original use of individually
accumulated keyboard flags, direct native C-array accesses, original order
of kind 0/2/1 dispatch, a stored XInput call-result variable and direct
signed/unsigned threshold comparisons. The function then compiled to
3,473 bytes / 743 instructions. An authentic nested kind dispatch and
properly scoped COM retry returns brought it to 3,490 bytes / 747
instructions but left 42 distinct nonrelocated bytes different due to a
reordered retry branch.

The final maintained source uses a bounded `retry_input_lost` label to
express the *real original* restart condition: if `Acquire()` reports
`DIERR_INPUTLOST`, acquire again and increment the actual attempt count;
return with lock cleanup when a different status occurs or the attempt
limit is reached. This is a real branch and two real failure exits,
not an inert compiler-shaping local, artificial byte, partial match,
assembly routine or forged return. The resulting native object gives
**3,334/3,334 identical nonrelocated bytes in their original positions**.

The pinned native compiler is Microsoft MSVC 19.44.35211 x86 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The source has one semantic body; its canonical unit is `input_device_poll`
on `src/InputDeviceFrame.cpp` with independent output
`build/core501-canonical/InputDeviceFrame.obj` and its pinned fresh receipt.

## Strict independently anchored relocation verification

The immutable original target's *entire* `0x00421B00` span was decoded
into 747 complete x86 instruction heads. Every original direct E8 field
was read from its instruction/displacement, producing **21 independent
REL32 call destinations**. The actual original PE `.reloc` blocks were
parsed separately, yielding **18 original HIGHLOW fields** within this
exact function, not assumed from the compiled candidate.

The independently identified globals, native function entries, IAT slots,
EH/security support and actual four Graphics field addends were then
compared to all **39** emitted COFF relocation offsets, types, symbols and
addends. The original `process_graphics` base `0x005C4D40` and original
16-bit threshold fields at base+`0x238` and +`0x23A` are independently
known; no target relocation field was solved backwards from candidate
bytes. The actual native XInput call resolves to `0x005406C6`, the true
original keyboard API IAT slot to `0x0056C294`, the three set-kind call sites
to `0x0041DE90` and the native security check to `0x005429EE`.

Result: **21/21 original E8 positions and 18/18 original PE HIGHLOW
positions and native targets agree**. With a fresh MSVC x86 build, strict
`compare-coff-function.py --unit input_device_poll --json` reports
**`exact`, 3,490/3,490** unmasked full original bytes after only these
independently justified relocation rewrites. Original code SHA-256 is
`78ed183ee4a2d240f179feedd8e8d94b7d2ffa4b8bbdc263f45aa486ca395cef`.

Private reproducible evidence (not committed executable/decompiler/toolchain):
`.analysis/core501-input-poll-native-independent-anchors.py`,
`.analysis/core501-input-poll-native-original-anchors.json`,
`.analysis/core501-input-poll-anchor-proof.log`,
`.analysis/core501-input-poll-cold-build.log` and
`.analysis/core501-input-poll-strict-exact.json`. Intermediate genuine
source variants and full opcode/byte-difference reports are retained
under `.analysis/core498-*`, `.analysis/core499-*`,
`.analysis/core500-*`, `.analysis/core501-*` and `build/core497-probes/`.

## Scope, regression and remaining work

This checkpoint changes only the newly source-present
`src/InputDeviceFrame.cpp` body, its one new canonical unit and exact
ledger/docs. The shared `InputInf.hpp` and `InputState.hpp` layout/header
changes were made and freshly replayed in the preceding CORE/RECON-497
checkpoint: **30/30 previously affected strict native units in eight
fresh compiled objects**. Those same exact source/header inputs are unchanged
here; reusing their passing evidence is correct. Only the newly admitted
3,490-byte source/object was cold built and strictly compared in this
checkpoint. **No whole-graph replay was run.**

Further gameplay work remains in the 3,111-byte Player main frame,
555-byte Player movement, 1,404-byte Bullet command-11, 3,735-byte Bullet
emitter, Enemy/Animation opcode dispatchers and whole-game executable
link/runtime. Exact polling alone proves no real-time Windows input
availability or playable assembled game.
