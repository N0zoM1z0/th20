# CORE/EXACT-214 — complete Bullet vertical reflection and typed command access

The immutable original for this checkpoint is Japanese TH20 Steamless v1.00a,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
All three whole original native functions are authored as natural C++20 in
`src/BulletReflection.cpp`. Their original spellings remain inferred; types,
fields, callee addresses and complete native extents come from independently
reviewed original control flow and existing typed Bulletin owners.

| Complete native function | Entry | Length | Strict result |
| --- | --- | ---: | --- |
| `Bullet::reflect_at_y_limit` | `0x00482DA0` | 281 bytes | 281/281 |
| `BulletExtendedCommands::at` | `0x0047C680` | 22 bytes | 22/22 |
| `BulletController::vector_4c_ref` | `0x00485990` | 17 bytes | 17/17 |

The original full 281-byte method is called from the **entire 832-byte**
`0x00482A60` Bullet update handler. It follows the real Bullet+0x520 Context
pointer, queries the current BulletController, and examines the existing
`vector_4c` at Controller+0x4C. If its Y component compares less than or
equal to floating zero, it uses `commands.at(4).vector_18.y` instead; otherwise
it fetches the live controller vector Y a second time. The complete method
compares Bullet+0x68 `position.y` against `(448.0f / 2.0f) +
(upper / 2.0f)` using the original IEEE-754 SSE instruction and branch
behavior, including unordered/NaN inputs. The native float objects are
`448.0f` at `0x0056D7C0` and `2.0f` at `0x0056C8D0`.

On reaching the threshold, unless `commands.at(4).word_3c & 0x10` is set,
it negates the actual Bullet Angle through its real float conversion and
normalizing assignment and mirrors position Y to `(448.0f + upper) - old_y`.
The sign inversion uses the original 128-bit SSE sign-mask object at
`0x0056D7D0`, not an invented scalar constant. The whole function returns
one if the threshold is reached and zero otherwise. All **13** original
relocation offsets, types and destinations are independently anchored to
these native callee/data identities, including two controller getters,
two command-slot accesses, two `vector_4c_ref` calls and the Angle members.

The natural ternary expression for choosing `upper` reproduces the original
locked MSVC x86 SSE and complete branch shape, unlike a tempting inverse
comparison or redundant local-variable shaping. The 22-byte command access
has the true `ExtendedCommand` **64-byte** stride, and the 17-byte vector
accessor returns the real Controller subobject. Caller xrefs establish their
actual use in the original game rather than only semantic resemblance.

The new methods are compiled in one fresh `build/core214-canonical/BulletReflection.obj`
using the locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` profile. Strict canonical replay returned **320/320
original function bytes**, and all 13 relocation fields match the original
whole function. Private focused log:
`.analysis/core214-bullet-reflection-replay.log`.

Adding three method declarations to `src/Bullet.hpp` affected six existing
source-object providers and **35** previously accepted native units. All six
objects were freshly rebuilt, and **35/35 old units remained exactly matched**.
The compiler only changed a native Bullet constructor debug literal local
symbol `$SG79816` to `$SG79820` and four Dialogue debug literal local
symbols `$SG117752..117755` to `$SG117756..117759`. The original native
data addresses, relocation offset/type and compared bytes were invariant;
only the COFF-private symbol names in the canonical manifest were corrected.
Total affected verification: **38/38 strict units, seven cold objects**,
with no unfiltered cold replay. Existing-unit log:
`.analysis/core214-bullet-header-affected-replay.log`.

This does **not** accept the full original **832-byte Bullet handler** at
`0x00482A60`, the **3,735-byte Bullet single-shot emitter** at `0x004818E0`,
or the **41,967-byte Enemy opcode dispatcher** at `0x0048C010`. Those complete
bosses and the still-unrecovered Animation/Renderer global owners remain
open, and no full-game link/runtime proof is implied by the scoped exact replay.
