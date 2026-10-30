# CORE/RECON-879 — original 72B/77B Vector2 compound value-return operators, whole-native strict exact

**LATER ACCEPTANCE NOTE (CORE/MAINT-896).** The 72B and 77B leaves
remain whole strict exact. The original **1,204B polygon outline caller
has since become whole strict exact**, too; its old SOURCE-ABSENT state
in this dated evidence is superseded. [Entire 1,204B original-native
proof](ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md).

The locked original Japanese TH20 v1.00a Steamless executable SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two original **game-authored value operations** are now restored using real
C++ member operators. They are directly used by the still source-absent
**1,204B polygon outline TRIANGLESTRIP renderer at `0x0043D370`**.
The original 1,204B parent is neither copied into the new leaf source
nor credited as strict exact.

| Immutable original physical fact | Compound scale | Compound add |
| --- | --- | --- |
| Native game code head | `0x00439910` | `0x00439960` |
| Entire original byte extent | **72B** | **77B** |
| Complete native x86 heads | **24** | **26** |
| Original actual operation | `Vector2::operator*=(float)` | `Vector2::operator+=(const Vector2&)` |
| Native mutating result | X,Y multiplied in place | X,Y added in place |
| Return convention | **Vector2 by value**, `ret 8` | **Vector2 by value**, `ret 8` |
| Original native real E8/PE HIGHLOW | **0/0** | **0/0** |
| Complete pinned MSVC strict native replay | **72/72 exact** | **77/77 exact** |

## Why a conventional reference-returning operator is wrong

[`scripts/verify-animation-vector2-compound-native.py`](../scripts/verify-animation-vector2-compound-native.py)
independently disassembles the **entire original PE** 72B/24-i386 and
77B/26-i386 bodies. Both take the current `Vector2` receiver in ECX,
mutate the two float lanes with the actual SSE `mulss`/`addss` opcodes,
then **write both modified 32-bit float lanes into a separate hidden
return-object pointer at `[ebp+8]`** and return that pointer through
EAX, cleaning two physical stack arguments with `ret 8`.

The original C++ therefore looks like:

```cpp
Vector2 Vector2::operator*=(float factor) {
    x *= factor;
    y *= factor;
    return *this;
}
Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}
```

A normal `Vector2&` return would omit the hidden result pointer and
change the stack ABI and native body. This is an actual value-category
fact relevant to C++ callers, not a guessed function name. The
source lives in [`src/Vector2CompoundValue.cpp`](../src/Vector2CompoundValue.cpp)
with the two real additional method declarations in
[`src/Vector2.hpp`](../src/Vector2.hpp), using the same genuine
8B two-float `Vector2` layout already maintained in the repository.

## Real 1,204B polygon Boss callers from the original executable

The original unmodified polygon renderer at `0x0043D370` has **real
native E8** to the 77B compound add at its three physical offsets
`+0x120`, `+0x1E0` and `+0x258`, and one genuine direct E8 to the
72B compound scale at `+0x2A9`. The independent verifier checks all
four original call-site target identities by disassembling the complete
1,204B original game method. These are helper operations in the actual
polygon join/width geometry: they should be used with the correct
value-return semantics when reconstructing the parent. This does
**not** establish that the original polygon renderer is strict exact;
that remains a separate 1,204B source/CFG/relocation task.

## Actual whole-native strict compiler acceptance

Two source units in [`config/match-units.toml`](../config/match-units.toml)
share exactly **one pinned compiler object and fresh receipt**
`build/core879-canonical/Vector2CompoundValue.obj`. Under pinned i386
MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
both C++ function extents **match the original 72B/77B bytes directly
without any relocations**. The locked original PE shows no E8 children
and no PE HIGHLOW data fields in either body. Full cold acceptance is
strictly source scoped:

```text
animation_vector2_compound_scale_72: exact (72/72 bytes)
animation_vector2_compound_add_77: exact (77/77 bytes)
Exact replay: 2/2 units, 1 cold objects
```

The header addition can affect other translation units that use
`Vector2`. Existing directly affected exact source providers are
checked in bounded, source-scoped replays; no unrelated whole-graph
cold replay is run. These two methods add **two unique game-authored
whole-native original function heads and 149 disjoint `.text` bytes**,
not compiler/STL code nor the unaccepted 1,204B parent. The current
accepted coverage becomes **630 authored whole-native exact game
functions /231,686 original native bytes**, **1,277 source-present
mappings /1,277 strict canonical units /294 accepted native compiler
object/receipt providers**.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-vector2-compound-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/Vector2CompoundValue.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
