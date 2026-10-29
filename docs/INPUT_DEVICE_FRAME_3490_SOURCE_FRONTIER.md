# CORE/RECON-497 — whole 3,490-byte InputDevice frame, typed source frontier

The only comparison executable is the user-selected Japanese TH20 v1.00a
Steamless `resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This work advances an entire game-authored input-frame boss, not just its
small callees. **The boss remains NONEXACT and contributes zero new canonical
exact bytes.** The existing 400 exact authored functions are unchanged.

## Original PE and complete maintained owner

The original physical entry `0x00421B00..0x004228A1` contains **3,490
bytes / 747 decoded complete i386 instructions**, SHA-256
`78ed183ee4a2d240f179feedd8e8d94b7d2ffa4b8bbdc263f45aa486ca395cef`.
Its **21 original direct E8 calls and 18 independent PE HIGHLOW fields** were
previously inventoried, and the whole span was freshly decoded from the
hash-attested executable here. These observations are separate from
compiler-candidate relocations; the two counts must not be conflated.

`src/InputDeviceFrame.cpp` now contains the *entire original game-state
protocol* as ordinary typed C++20 `std::uint32_t InputDevice::poll()`:

- Clear 256 bytes of genuine `InputDevice::raw` at +`0x2D0` before acquiring
  `process_locks.slot(15)` under the real `std::recursive_mutex` guard.
- Resolve the physical logical view using the existing whole-exact 49-byte
  routing method at `0x00421990` and 27-byte 48-stride binding accessor at
  `0x004217F0`, rather than inventing another input-manager object.
- For keyboard kind 0, use the actual `GetKeyboardState` import and all
  eight signed 16-bit keyboard bindings. Preserve native fixed keyboard
  shortcuts, alternate numeric-pad diagonals, and accumulated bit masks.
- For XInput kind 2, use the 16-byte native `XINPUT_STATE`, ordinal-2
  `XInputGetState` import, signed `0x1EA8` thumbstick and `0x1D` trigger
  thresholds, and the original externally owned mask table at `0x005AE220`.
  Preserve its 12 output raw-byte assignments.
- For DirectInput kind 1, call the actual `IDirectInputDevice8W::Poll`,
  `Acquire` and `GetDeviceState` interfaces. Keep the input-lost retry limit,
  RAII cleanup and early failures that do **not** update button history.
  Use the real 272-byte `DIJOYSTATE2`, four exact `map_input_byte` calls,
  signed Graphics configuration axis thresholds at `0x005C4F78` and
  `0x005C4F7A`, and the 32 native joystick-button bytes.
- Publish previous/current button words and invoke the separately whole-exact
  583-byte `InputButtonState::update()` only after a successful frame path.

The original XInput and DirectInput physical blocks are laid out in that order
after keyboard, despite dispatching by logical device kind 2 and 1. The
maintained source uses an ordinary switch in physical block order 0/2/1;
no copied Ghidra body, arbitrary padding, assembly, fake returns or
build-configuration branches were introduced.

The original `InputDevice::raw` really is contiguous 256-byte C-array
storage. Replacing `std::array` with `std::uint8_t raw[256]` keeps the
original 0x3D4 owner and 0x2D0 raw offset **and** avoids generated `std::array`
accessor calls under native `/Od`. The original entire **102-byte
InputDevice constructor remained strict exact** after this source change.

## Exact 22-byte shared setter morphology (no duplicated physical unit)

The original input-frame call sites at `0x0041DE90` receive the real
`InputInf*` stored at `0x005B8898`, and pass the device kind to a method
that writes the +`0x18` field. The original entire 22-byte body has been
independently decoded. The new natural
`InputInf::set_last_input_kind(std::int32_t)` preserves that precise data
write, with its own correctly typed member declaration and definition.

Locked MSVC x86 emits **22/22 identical nonrelocated bytes, with no
relocations**, against the original physical function. This is a
**structural comparison**, not a new strict canonical replay receipt;
the physical address was already listed as the template-interpolation
`set_duration()` contribution in the provisional ledger. Both source
owners can explain the machine-code behavior; do not double-claim one
native physical body or reinterpret one match as whole-program linkage.

## Entire boss's native compiler frontier, not an exact claim

Fresh low-priority MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` builds (all original WinSDK COM
headers, no substitute host interfaces) establish:

| Measure | Original PE | Current maintained C++ candidate |
| --- | ---: | ---: |
| Entire function bytes | **3,490** | **3,720** |
| Entire decoded instruction count | **747** | **759** |
| Ordered identical mnemonic kinds | — | **691/747** original kinds |
| Original direct E8 fields | **21** | Not a comparable original-field count |
| Original PE HIGHLOW fields | **18** | Not a comparable original-field count |
| Object COFF relocation fields | Not applicable | **37** |

The earlier initial typed candidate emitted **4,260 bytes** due to genuine
`std::array` `/Od` accessor calls. Switching to the native C array reduced
this to 3,750 bytes; the native switch order and directly named binding
members reduced the final candidate to **3,720 bytes / 759 instructions**.
Both the **230-byte length gap** and the **56 unmatched original opcode
kinds** preclude exactness. No manifest unit or fabricated partial extent
was added. Independent full-original and final compiler counts are saved in
`.analysis/core497-input-boss-final-codegen.json`, and the intermediate
compiler variants under `.analysis/core497-input-*` and
`build/core497-probes/` are private reproducible hypotheses.

## Strict native regression scope and next task

Before changing `InputState.hpp` and `InputInf.hpp`, existing canonical
compiler receipts identified **exactly 30 affected strict units in eight
source/object providers**: `InputState`, `InputInf`, `InputInfConstruction`,
`InputInfShutdown`, `InputInfStart`, `InputInfDeviceInitialization`,
`InputInfDirectInputDiscovery`, and `InputDeviceDirectInput`. All eight
objects were rebuilt with locked low-priority MSVC, then the entire
**30/30 affected original units passed strict complete relocation replay**
with fresh receipts, using only explicit `--source` filters and
`--existing-objects`. No full cold replay was run.

The seven changed compiler-private `$SG` labels were reconciled only after
independent verification of each immutable original PE DIR32 field,
original string bytes, candidate string bytes, all other unrelocated body
bytes and original target address. Only the spelling in
`config/match-units.toml` changed; original anchor destinations did not.
Verification and source-closure evidence:
`.analysis/core497-input-poll-preedit-closure.json`,
`.analysis/core497-input-private-symbol-proof.json`,
`.analysis/core497-input-private-audit-final.log`, and
`.analysis/core497-input-30unit-replay.log`.

**Next:** compare each remaining opcode/stack-lifetime difference in the
complete 3,490-byte parent, especially its EH, binding-index reads,
DirectInput error exits and XInput flag assembly. Resolve the original
18 PE HIGHLOW locations and 21 E8 fields independently in any eventual
candidate manifest. Do not credit the parent until an entire canonical
zero-difference relocation replay succeeds. The separate 555-byte Player
movement / 3,111-byte frame bosses remain open and independent.
