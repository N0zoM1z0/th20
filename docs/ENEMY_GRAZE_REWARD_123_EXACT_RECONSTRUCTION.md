# CORE/EXACT-355 — whole original 123-byte EnemyController graze reward predicate

Immutable comparison original: user-approved Japanese TH20 v1.00a
Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned original `EnemyController::graze_reward_active`
occupies the complete native `0x0049BE20..0x0049BE9A`: **123 bytes,
47 original x86 instructions**. The native interval SHA-256 is
`a3d9dd1ba1dc1ec93d160362d561a3d1de911405240fd6367396bb02a850dd85`.
Its independently source-present and strictly exact original caller is
`Player::record_bullet_graze` at `0x004F8B90`, now accepted as the
entire separately exact 332-byte original gameplay function.

## Source behavior, native boundaries, and bool ABI

The original method takes the real 16-slot `std::array<EnemyHandle,16>`
at `EnemyController+0x54` (`EnemyData.handles`) and passes its native
`end()` and `begin()` iterator values to the real MSVC `std::any_of`
instance. Its *captureless predicate takes a four-byte `EnemyHandle`
value* and tests whether the underlying `value != 0` rather than resolving
an enemy entity or testing unrelated health/flags. The return value is
normalized to an actual one-byte `bool` with two genuine branches:

```cpp
if (std::any_of(data.handles.begin(), data.handles.end(),
                [](EnemyHandle handle) { return handle.value != 0; }))
    return true;
return false;
```

A private baseline directly returning the `std::any_of` result generated
only **111 bytes / 41 instructions**. The natural explicit success and
fallback branches restore the original `movzx`, `test`, `je`, true `mov`,
jump and false `xor` tail. Its resulting **123 bytes / 47 instructions**
match the original entire native body with all three native calls and
strict C++20 `/Od` evaluation order. The original 1-byte empty-lambda
value is passed to `std::any_of` naturally; no fabricated capture, dummy
local, padding, inline assembly or false caller return is used.

The independently decoded original **three `E8 / REL32` call fields**
are:

| Original displacement offset | Original callee | Actual role |
| --- | --- | --- |
| `+0x26` | `0x004981A0` | 16-slot `std::array<EnemyHandle,16>::end()` |
| `+0x46` | `0x0045FD60` | 16-slot `std::array<EnemyHandle,16>::begin()` |
| `+0x63` | `0x0048A990` | native compiler-generated `std::any_of` instance |

All original locations/types/targets were extracted from the unmodified
PE and agree with the three actual COFF relocations emitted by the natural
whole method. The canonical object `build/core355-canonical/EnemyGrazeReward.obj`
and its fresh receipt pass **123/123 strict whole-function byte comparison**.
The original name is inferred from its actual Player graze caller; the
receiver, 16-value scan, lambda and `bool` ABI are directly grounded.

## Separate library helper boundaries and affected-only replay

The compiler also generates two 30-byte standard-array begin/end helper
bodies and the 41-byte lambda predicate, structurally consistent with
the independent original entries, but they are **separate original
boundaries** and are **not newly credited game-authored roots** in this
checkpoint. Its 107-byte native `std::any_of` callee at `0x0048A990`
currently emits a 104-byte candidate: the library template itself is
**still not exact**. Accepting the original 123-byte caller does not
assert exactness for this unaccepted callee or double count folded
standard-library helpers.

Only the new maintained `src/EnemyGrazeReward.cpp` provider and its
native evidence ledger changed. The real member was already declared in
`src/EnemyController.hpp` and validated by the previous complete 332-byte
Player graze-feedback checkpoint. There is **no shared header or previous
exact source change**. Exactly **1/1 strict units across one freshly
built source object** passed, via an explicitly filtered replay, with no
unfiltered repository cold replay. Private confirmation is in
`.analysis/core355-enemy-graze-replay.log` and the independently
original-referenced `.analysis/core355-enemy-graze-original-refs.json`.

The 41,967-byte Enemy ECL dispatch root and broader renderer/Enemy data
lifetime remain independent open work. This is complete original method
exactness, not whole-game binary linkage or runtime equivalence.
