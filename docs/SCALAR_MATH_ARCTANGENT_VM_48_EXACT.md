# ScalarMath VM atan2 adapter — exact 48B leaf

The original `0x004397F0` function is a 48-byte x86 cdecl wrapper taking two
float arguments. It widens both to `double`, calls the original atan2 math
entry at `0x0054FFA0`, narrows the result to `float`, and returns with the
caller-cleaned stack. The original `Animation::update` Boss calls it twice.

`th20::scalar_math::arctangent_vm(float y, float x)` in `src/ScalarMath.cpp`
uses the natural `std::atan2(static_cast<double>(y), static_cast<double>(x))`
expression. Its pinned MSVC x86 C++20 contribution reproduces the complete
**48/48-byte** body, including the single `REL32` relocation at `+0x1F` to
`_atan2` / original target `0x0054FFA0`. The two Boss call sites now invoke
this typed cdecl ScalarMath owner directly; no numeric `FUN_004397F0` adapter
remains.

A separate existing `ScalarMath::arctangent` wrapper at `0x00459280` calls a
different original math dispatcher. This VM-specific wrapper is retained as a
distinct natural source method because its original relocation target differs.
The semantic name is inferred; original CRT/compiler/library authorship is
unknown and receives no game-authored byte credit.
