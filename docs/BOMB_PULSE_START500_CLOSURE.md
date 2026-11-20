# Bomb pulse start — 500B original Boss and exact boundary leaves

The original Japanese Steamless TH20 `0x00478C00..0x00478DF3` is a
complete 500B / 153-instruction virtual `Bomb::start(int)` implementation.
The original derived vtable contains its function pointer at `0x0056FB10`.
The start routine sets a +0xB8 `Vector3`, +0xC4 angle and two animation
handles, issues two `"pl01"` spawns (scripts 0x33 and 0x41), binds their
original entry callback at `0x00478380`, refreshes Card capture state,
sets Player +0x2050 invulnerability, advances an EnemyController counter,
creates a 0x44B scheduled helper, and marks Player flag bit 2.

The natural `src/BombPulseStart500.cpp` candidate compiles with pinned
MSVC 19.44 C++20 to 498B/151 instructions versus the original 500B/153.
It has 25 real E8 roles and eight DIR32 roles, matching the original PE's
25 E8 and eight HIGHLOW roles in order, including both callback data
addresses, the two `"pl01"` string literals, and the negative-π/2 angle.
The original has NOPs after the Sound request and first callback; they
are absent from the current C++ codegen. **The parent remains NONEXACT**
and receives no whole-original-byte credit. Do not add inert instructions,
assembly, or padding to make up the two bytes. The full source and the
independent native target remain available for continued convergence.

## Four whole native exact leaves now closed

| Address | Original | Source owner | Independent native result |
| --- | ---: | --- | --- |
| `0x00450850` | 30B | AnimationHandle owner forwarder | 30/30, one E8 to `0x0044CF10` |
| `0x00479060` | 32B | Player invulnerability Timer | 32/32, one E8 to `0x00423520` |
| `0x004790A0` | 26B | Player bomb-used bit 2 | 26/26, no relocs |
| `0x00477F40` | 28B | EnemyController counter | 28/28, no relocs |

The 30B accessor must use the result of `resolve_or_resident_44cf10()`
directly: introducing a `Animation*` temporary adds a non-original
stack slot. The 32B Player wrapper must use `Timer::operator=(int)`,
not `Timer::set(int)`, to preserve the original native `0x00423520`
E8 role and compiler register lifetime. Both observations come from
comparing complete original i386 bodies and compiled COFF relocations.
The two flag/counter leaves use true Player and EnemyData fields and do
not construct duplicate storage. All four independent exact units are
scoped for cold MSVC and strict full relocation replay; the 500B parent
is not included in an exact unit.

The `0x00425090` helper was initially named CRT aligned realloc by
auto-analysis, but its 7-argument constructor at `0x004250F0` allocates
and initializes a scheduled game-side object; this is a source-role
hypothesis pending its own independent reconstruction, not an exact leaf.
