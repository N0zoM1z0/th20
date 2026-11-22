# Enemy ECL opcode 620 — shared queued-vector update

## Status and boundary

Opcode 620 is now represented by natural C++ in
`src/EnemyStateSharedQueuedParametersOpcode.cpp`, linked into the maintained
`EnemyState::execute_opcode` root host, and covered by focused native and
COFF checks. This is an inline case fragment in the original 41,967-byte
`EnemyState::execute_opcode` body at `0x0048C010`; it is **not** a standalone
native function or an independently replayable function unit. The 41,967-byte
parent remains **NONEXACT** and receives no byte-extent credit from this case.

## Locked native case

Target: `resources/th20.exe`, Japanese TH20 1.00a Steamless image,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- ECL selector: opcode `620`, selector index `138`.
- Original case: `0x00492D4D`, 250 bytes, 57 x86 instructions.
- Original case SHA-256:
  `8f8b5e30c38cf65b1e12317a2968d16922826c6078745e2524911ae0cd296a3d`.
- Eight ordered direct calls:

| Call site | Target | Recovered role |
|---|---:|---|
| `0x00492D55` | `0x004AB080` | `integer_argument(0)` selector |
| `0x00492D74` | `0x00498D10` | ensure-only `shared_shot` selection |
| `0x00492D80` | `0x0040B280` | `std::move(pair)` |
| `0x00492D89` | `0x0048B180` | pair rvalue first-element access (`get<0>`) |
| `0x00492D9E` | `0x0040B280` | `std::move(pair)` |
| `0x00492DA7` | `0x0048B160` | pair rvalue second-element access (`get<1>`) |
| `0x00492DBD` | `0x004AAFB0` | `float_argument(1)` |
| `0x00492DE5` | `0x004AAFB0` | `float_argument(2)` |

The Ghidra decompilation of the pair accessors shows the first accessor
moving from the pair's first word and the second accessor moving from its
second word (`param_1 + 4`). The natural source expression is therefore
`std::get<0>(std::move(selected))` followed by
`std::get<1>(std::move(selected))`, not custom pair-address wrapper templates.
The locked MSVC COFF profile emits the two `std::get` relocations and inlines
the outer `std::move` expressions; this compiler-profile difference is not
papered over with artificial helper calls.

## Recovered behavior

1. Read the integer selector from VM argument 0.
2. Call `EnemyState::shared_shot(selector)`. This selects/ensures the real
   queued record and its metadata association; it does not call
   `writable_shot` and does not trigger metadata COW.
3. Extract the queued-record and metadata pointers from the returned pair
   through the native pair-rvalue access path. The metadata pointer is not
   subsequently used by this case, but its extraction is retained.
4. Read float argument 1 and immediately write `vector_40.x` at record offset
   `+0x40`.
5. Read float argument 2 and immediately write `vector_40.y` at offset
   `+0x44`.
6. Compare the newly written X value with the native `-990.0f` threshold at
   `0x0056FD74`. Write Z at offset `+0x48`: zero when X is strictly below the
   threshold, otherwise the native `1.0f` value at `0x0056C8CC`.

The compare at `0x00492E15` is `COMISS XMM0, [EDX+0x40]`, followed at
`0x00492E19` by `JBE 0x00492E2D`. `COMISS` sets CF and ZF for an unordered
comparison; `JBE` therefore takes the one-valued path for NaN as well as for
X greater than or equal to `-990.0f`. The natural C++ condition
`if (x < native_speed_override_threshold) ... else ...` preserves this
behavior. A superficially equivalent `x >= threshold` conditional would not:
C++ ordered comparisons return false for NaN, while the native unordered path
writes one.

## Focused tests and build integration

The false-returning root-test stub was removed. The production helper is now
part of `HOST_SOURCES`, the locked-profile COFF compile list, and the
ASan/UBSan root host.

The root test covers:

- X exactly `-990.0f` selects Z = `1.0f`.
- X `-991.0f` selects Z = `0.0f`.
- X = NaN selects Z = `1.0f`, matching `COMISS/JBE` unordered behavior.
- A second-float read exception occurs after X is written but before Y/Z are
  changed.
- The real queued record retains the same `ShotMetadata` owner and its
  `shared_ptr` use count remains unchanged across all cases.

The maintained focused verifier passes:

```sh
scripts/repo-python scripts/verify-enemy-shared-queued-opcode-source.py
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```

The root verifier compiles 36 locked-profile i386 COFF source units and runs
the root host under ASan/UBSan. The opcode-620 COFF check verifies ordered
`integer_argument` / `shared_shot` / `std::get<0>` / `std::get<1>` / float
operand relocations, the `COMISS/JBE` threshold path, and direct X/Y/Z stores.
The native case verifier independently checks the locked PE selector, extent,
SHA-256, all eight original direct call sites/targets and the two data values.

No full cold replay was run. No standalone unit, strict exact-byte claim, or
whole-parent exactness claim is made by this fragment.
