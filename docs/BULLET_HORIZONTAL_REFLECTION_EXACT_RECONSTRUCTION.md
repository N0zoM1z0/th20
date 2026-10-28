# CORE/EXACT-216 — whole 319-byte and 329-byte horizontal Bullet reflection

Two substantial entire original Bullet methods are reconstructed in the same
maintained `src/BulletReflection.cpp` owner as the previously exact vertical
reflection and its two typed command/vector dependencies. No alternative
compiler-only body, copied native assembly, artificial padding or duplicated
compiler-shaping local variables were introduced. The original target is
Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original names are inferred and full typed control flow was checked against
both immutable native disassembly and the existing underlying Bullet objects.

| Whole original method | Entry | Whole size | Original relocations | Canonical replay |
| --- | --- | ---: | ---: | ---: |
| `Bullet::reflect_at_right_x` | `0x00483010` | 319 B | 14 | 319/319 |
| `Bullet::reflect_at_left_x` | `0x00482EC0` | 329 B | 16 | 329/329 |

Both methods use the actual Bullet+0x520 Context, live BulletController
`vector_4c_ref()` at `0x00485990`, and `BulletExtendedCommands::at(4)` at
`0x0047C680`. The current controller X component is chosen when strictly
positive; otherwise the fallback is the real command slot's `vector_18.x`.
The right-side bound is **+half the selected horizontal extent**, while the
left-side bound is **negative half the same extent**. Their full original
SSE comparisons retain the native unordered/NaN behavior, not a generic
clamp approximation. Each returns zero when no boundary hit occurs and one
on a hit, including command flag `0x10` which suppresses physical reflection
without suppressing hit detection.

The successful physical reflection negates the actual Angle, subtracts the
original pi constant at `0x0056E0F0`, calls the actual `Angle::operator=(float)`
and then normalizes the resulting value using the original
`add_angles(angle, 0.0f)` at `0x00438600` followed by a **second** Angle
assignment. The real `position.x` is mirrored about the selected horizontal
extent. The negative sign is represented by the native 128-bit SSE sign mask
at `0x0056D7D0` and the divisor is the original 2.0f object at
`0x0056C8D0`. This source is the same natural C++ expression tested against
the complete original bodies, not a handwritten opcode/byte sequence.

For the 319-byte right reflection, all **14** native relocations replay,
including both original Controller/command lookups, the two real Angle
assignments and the normalization call. The 329-byte left reflection
has all **16** original relocations replayed, with its additional negative
sign masks. Both full functions independently match **263/263** and
**265/265** non-relocation bytes before relocation replay; afterward the
complete **648/648** native bytes are exact. Original interval SHA-256:
right `720276fef402bf1a724ea887a458bd245f62a44d67eefbf6ecff69013020b4aa`;
left `7a15b8aae68b0d213d14d94142303437064ab72e516d4923793836bcd9580d7e`.

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` object containing the old three and new two functions was
recompiled; **5/5 same-source strict exact units** passed. The real
`src/Bullet.hpp` include closure covers six existing objects and **35**
prior strict exact units: all 35 were cold recompiled and full replayed
without a native byte regression. The compiler assigned new private local
Bullet constructor diagnostic symbol `$SG79822` (formerly `$SG79820`),
and Dialogue strings `$SG117758..117761` (formerly `$SG117756..117759`),
with native independently verified relocation targets unchanged. Only those
private COFF symbol labels changed in `config/match-units.toml`.

**This checkpoint's affected-only strict replay: 37/37 functions across
seven cold objects**, consisting of two new + 35 unchanged old. The other
three functions in the same new object also remain exact. No unfiltered
cold replay was executed. Focused proof logs are
`.analysis/core216-bullet-reflections-replay.log` and
`.analysis/core216-bullet-header-affected-replay.log`; native complete
function disassembly is privately recorded as
`.analysis/core216-native-00483010.asm` and
`.analysis/core216-native-00482ec0.asm`.

The complete original **832-byte** Bullet boundary dispatcher at
`0x00482A60` is not exact. Its own source/emission still require restoring
call order, boundary tests, signed counters, command flags, sound policy and
all original relocation/EH contributions, including separate reflection
cases. The much larger 3,735B Bullet single-shot emitter and the
41,967B Enemy dispatch root are also open. Exact individual callees cannot
be mistaken for byte identity of their enclosing boss function.
