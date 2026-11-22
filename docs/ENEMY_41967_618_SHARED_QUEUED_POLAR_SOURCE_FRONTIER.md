# Enemy ECL opcode 618 — shared queued polar XY update

## Status and boundary

Opcode 618 is restored as natural C++ in
`src/EnemyStateSharedQueuedParametersOpcode.cpp`, routed through the existing
partial `EnemyState::execute_opcode` dispatcher and executed by the maintained
ASan/UBSan root host. It is an inline case inside the original **41,967-byte**
parent at `0x0048C010`, not a standalone native function. No separate match
unit or parent-byte credit is claimed; the parent remains **NONEXACT**.

## Locked native case

Target: Japanese TH20 1.00a Steamless `resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- Opcode: `618`; compressed selector index `136`.
- Case interval: `0x00492BC6..0x00492CB9` (end-exclusive).
- Size: **243 bytes / 55 x86 instructions / 10 direct E8 calls**.
- Native case SHA-256:
  `fd1d55043482bdee505c3d580e71a297af675abd061e4347e573a145e0c61a15`.

| Call site | Target | Recovered role |
|---|---:|---|
| `0x00492BCE` | `0x004AB080` | `integer_argument(0)` |
| `0x00492BE1` | `0x004AAFB0` | `float_argument(1)` — direction |
| `0x00492BF4` | `0x004AAFB0` | `float_argument(2)` — length |
| `0x00492C13` | `0x00498D10` | ensure-only `shared_shot` selector |
| `0x00492C1F` | `0x0040B280` | `std::move(pair)` |
| `0x00492C28` | `0x0048B180` | `std::get<0>(pair&&)` |
| `0x00492C3D` | `0x0040B280` | `std::move(pair)` |
| `0x00492C46` | `0x0048B160` | `std::get<1>(pair&&)` |
| `0x00492C5A` | `0x00422E10` | temporary `Vector3` default constructor |
| `0x00492C82` | `0x00439330` | `polar(Vector3&, direction, length)` |

The final native stores at `0x00492C9A` and `0x00492CAF` write the computed
X/Y values to queued-record offsets `+0x34` and `+0x38` respectively.

## Recovered behavior and ordering

1. Read integer argument 0 as the queued-record selector.
2. Read float argument 1 as the polar direction.
3. Read float argument 2 as the polar length.
4. Only after both float reads succeed, call the real ensure-only
   `EnemyState::shared_shot(selector)` and extract both pointers from its pair
   using the native `std::move` / `std::get<0/1>` path.
5. Construct a real temporary `Vector3`, initially zeroed by its native
   constructor, then call the existing `polar(offset, direction, length)`.
6. Copy only `offset.x` and `offset.y` into `record->vector_34.x/y`.

This is not a writable-shot COW operation. The metadata pointer is extracted
but not modified; the shared metadata owner and reference count remain stable.
The record's `vector_34.z` is preserved, as is the entire `vector_40` lane.
The existing natural-C++ `polar` and `Vector3` implementations are reused; no
handwritten trigonometric approximation or duplicate math leaf is introduced.

The integer selector in the root test is an immediate packet operand, while
float operands 1/2 are external VM references (`-101` / `-102`). The observed
read trace is therefore exactly two float reads in order. When the second
float read throws, `shared_shot` has not yet run: the queue remains empty and
no metadata owner is allocated. This is a meaningful exception boundary, not
just a test of the final numeric result.

## Focused verification

The dedicated `scripts/verify-enemy-shared-queued-polar-opcode-source.py`
checks the locked PE fingerprint, selector, 243-byte branch hash, 55 decoded
instructions, all ten ordered E8 sites/targets, the final `+0x34/+0x38` stores,
and the natural source operation order.

The maintained
`scripts/verify-enemy-state-dispatch-frontier.py` also checks the production
helper's locked-profile COFF relocation order:

`integer_argument → float_argument → float_argument → shared_shot → get<0> → get<1> → Vector3() → polar`

The actual production helper is linked into the existing ASan/UBSan root
host. Tests cover a pi/2 direction with length 2, preservation of Z and
`vector_40`, stable shared metadata ownership, and a second-float exception
before queue growth. The maintained root verifier passes with **36 locked-
profile i386 COFF source units** and the full focused root-host case set.

No full cold replay was run. The existing `polar` and `Vector3` leaves are
reused; no new leaf function or whole-parent exactness claim is created.
