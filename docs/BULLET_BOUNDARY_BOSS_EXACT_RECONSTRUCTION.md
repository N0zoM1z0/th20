# CORE/EXACT-220 — complete 832-byte original Bullet four-direction boundary boss

This checkpoint admits the **entire original** `0x00482A60..0x00482D9F`
(832 bytes, 235 native x86 instructions; native interval SHA-256
`9fd61fb2d55a5d75237917f70f0e0b3b4081d0ccc1b4eedf0703f6cb9d4da743`)
from the immutable TH20 Japanese v1.00a Steamless PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
The maintained natural C++20 `Bullet::handle_boundary()` in
`src/BulletBoundary.cpp` is a **single whole function**, not an isolated
switch arm or a prefix. Original method spelling remains inferred.

## Independently checked real gameplay ownership

The Bullet's live Context at +0x520 yields the genuine BulletController
`vector_4c_ref()` at +0x4C. When that controller's X limit is
nonpositive, the original caller uses its own `BulletExtendedCommands::at(4)`
width/height (real 64-byte stride and `ExtendedCommand` vectors) for the
full original four-edge rectangle test. Otherwise it reads the current
Controller X and Y. The real rectangle function at `0x00485420` has also
been independently reconstructed in `src/BulletRectangle.cpp`:
**176/176 exact native bytes, all seven original relocations**; it is called
at the original sites `0x00482AF6` and `0x00482B98`. The actual game field
uses 224.0f center on Y; neither the caller nor the callee invents a
single-axis clamp or a different collision predicate.

An important native `/Od` compiler distinction: expressing the two rectangle
paths as one short-circuit logical `||` causes a **direct forward conditional
jump** from the first test to the shared hit logic, followed by the original
Controller branch. A superficially equivalent explicit `goto`/nested `if`
compiled to **846, 848 or 865 bytes** instead of 832 and was rejected.
The accepted source matches all **708/708 non-relocation bytes** and all
original branch instructions, not merely the high-level Ghidra pseudocode.

On hit, the whole boss queries flag bits 0, 1, 3 and 2 in that original
order from `ExtendedCommand[4].word_3c` and calls four **separately fully
exact** game-specific Bullet reflections at the actual addresses:
upper Y `0x00483150` (277 bytes), lower Y `0x00482DA0` (281 bytes),
right X `0x00483010` (319 bytes), left X `0x00482EC0` (329 bytes).
The short-circuiting only skips a particular handler when its bit is off;
it does not skip later directions after a prior bounce.

After any successful reflection, the real command speed override is copied
when above the native **-990.0f** float stored at `0x0056FD74` (verified
from original PE bits `0xC4778000`). The actual `polar` method at
`0x00439330` updates Bullet velocity from its live Angle and resulting
speed. The command's +0x30 counter is incremented, and if the Bullet's
signed sound ID at +0x40 is nonnegative, real `process_sound` requests
that effect ID with pan zero through native `0x00426D70`.
The original signed count comparison uses command +0x30/+0x34; on
completion, **only low 32-bit word bit 6** of the native 64-bit
`BulletCommandFlags` at +0x90 is cleared. The maintained 8-byte flags
structure now exposes `words.low/high` and its existing complete `bits`
view as a native typed union, without changing owner layout.

## Full exact code, relocation and affected-only replay

The locked compiler (MSVC 19.44 x86, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`) emitted the entire original **832/832 bytes**
with **all 31 original native relocation offsets, types and destinations**.
Among these are four bounce calls, two actual independently exact rectangle
calls, real Context/Controller/command accessors, the unchanged native
floating -990/zero objects, Angle getter, `polar`, real process SoundInf
and positional request. They were independently obtained from the original
locked PE and caller/callee ownership, not inferred from successful target
fields. Full canonical replay:
`.analysis/core219-bullet-linked-boundary-rectangle-replay.log`.

Adding the `handle_boundary` declaration and typed low/high flags view to
shared `Bullet.hpp` affects **nine previously exact source providers and
45 complete old strict units** (including earlier BulletFire, lifecycle
and four-way reflection units). All nine objects were freshly recompiled
and every **45/45 prior strict unit passed**. MSVC's local diagnostic string
labels shifted from `$SG79823` to `$SG79850` in BulletController and
from `$SG117759..117762` to `$SG117786..117789` in Dialogue, but the
original data relocation destinations and strict compared native bytes
were unchanged. No relaxed byte comparison or exception is introduced.
Full scope: **47/47 distinct strict units across eleven freshly built objects**
(45 old + 832B boss + 176B rectangle), no all-repository cold replay.
Existing closure log: `.analysis/core219-bullet-header-full-closure-replay.log`.

The complete 3,735-byte single-shot `BulletController::emit`
(`0x004818E0`) and 41,967-byte Enemy ECL opcode dispatcher
(`0x0048C010`) **remain nonexact**. This boss's full code/body proof
only establishes the four-edge Bullet update path, not the rest of the game
or a full runnable link. Its individual reflection and rectangle subroutines
are separate original complete functions with disjoint byte credit.
