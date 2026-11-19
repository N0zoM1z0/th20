# ScalarMath VM floating-remainder adapter — exact 48B leaf

The original `0x004397F0` function is a 48-byte x86 cdecl wrapper taking two
float arguments. It widens both to `double`, calls the CRT math dispatcher at
`0x0054FFA0`, narrows the result to `float`, and returns with the
caller-cleaned stack. The dispatch descriptor at `0x0059A740` begins with the
name `fmod`; the separate `0x005500E0` descriptor at `0x0059A980` is named
`atan2`. This distinguishes the two nearby math wrappers unambiguously.

`th20::scalar_math::floating_remainder(float value, float divisor)` in
`src/ScalarMath.cpp` uses the natural
`std::fmod(static_cast<double>(value), static_cast<double>(divisor))`
expression. Its pinned MSVC x86 C++20 contribution reproduces the complete
**48/48-byte** body, including the single `REL32` relocation at `+0x1F` to
`_fmod` / original target `0x0054FFA0`. The two Boss call sites now invoke
this typed cdecl ScalarMath owner directly; no numeric `FUN_004397F0` adapter
remains.

The separate existing `ScalarMath::arctangent` wrapper at `0x00459280` calls
the distinct `atan2` CRT dispatcher at `0x005500E0`. The semantic name is
inferred; original CRT/compiler/library authorship is unknown and receives no
game-authored byte credit.
