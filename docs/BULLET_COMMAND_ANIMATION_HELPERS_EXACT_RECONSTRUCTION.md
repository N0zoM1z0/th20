# CORE/RECON-752 — four game-authored Animation helpers on the 12,140-byte Bullet command Boss

The selected TH20 Japanese v1.00a Steamless binary is fixed by its independently
verified SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original Boss at `0x0047DCF0` is **12,140 bytes / 2,490 decoded x86
instructions** and remains source-absent, NONEXACT. This checkpoint closes
**four of its seven previously unsourced original direct E8 targets** with
maintained typed C++ and strict whole-function canonical replay; these are
separate native functions, not credits for the parent body.

| Original call site | Original function head | Complete extent | Native action | Strict replay |
| --- | --- | ---: | --- | --- |
| `0x004807C1` | `0x0045E590` | 21 B | Write `Animation::base.flags.bytes_00.field_01 = 0` at `+0x499` | 21/21 |
| `0x004807B0` | `0x0045E5B0` | 21 B | Write same native byte = 1 | 21/21 |
| `0x00480793` | `0x004865D0` | 21 B | Write same native byte = 2 | 21/21 |
| `0x0047F671` | `0x00486330` | 22 B | Call `Animation::interrupt(2)` at real `0x004388F0` | 22/22 |

The three original machine-code bodies each have the same `push ebp; mov ebp,
esp; push ecx; mov [ebp-4],ecx` prologue and direct `mov byte ptr
[eax+0x499], immediate` write, then normal epilogue. Each original body ends
with its `ret` at the claimed original extent; there is no partial-prefix
comparison. The interrupt wrapper is the original `__fastcall` ECX-receiver
pattern used by the separately exact `interrupt_animation_mode3` at
`0x00486370`: `push 2`, call real `Animation::interrupt`, a native `nop`,
then the normal epilogue. The only new COFF relocation is the 4-byte `REL32`
field at offset `+0xD` to `0x004388F0`, independently decoded from original
native E8. There are no original PE HIGHLOW fields in these four bodies.

`src/BulletCommandAnimationHelpers.cpp` supplies one natural C++ body per
original function with the actual `AnimationBase` flag layout (compile-time
assertions already hold for `Animation+0x498`). As with existing proven Bullet
helpers, the member-versus-namespace spelling of these ECX-only native
functions is *not* established by binary evidence; typed one-argument
`__fastcall` is ABI-correct, and no duplicate animation-owner storage or
byte-offset arithmetic was added.

Pinned MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` built exactly **one** new canonical COFF object from this new
source. Focused `replay-exact-units.py --source
src/BulletCommandAnimationHelpers.cpp` compared all four **complete native
functions at zero byte difference (4/4)** with separately locked target
and exact relocation identity; no old source file or public header changed,
so **zero existing canonical objects** required recompilation. These four
functions add **85 physical authored-game bytes** and no library credit.

The 37-byte `AnimationHandle::retire` at `0x0044FCD0` remains the fifth open
game E8 target in this batch: original native ECX is a four-byte handle;
its implementation reads that value, invokes a separate pool-owner
`0x0044FCA0` method through global `0x005C0028`, then clears the same
handle word. The two remaining E8 targets are compiler helpers:
`__security_check_cookie` at `0x005429EE` and `__allshl` at `0x005432F0`.
Neither is authored gameplay and neither should be counted as such.

The independent original-PE verifier
`scripts/verify-bullet-command-call-coverage.py` now retains all seven
original E8 observations, reports which of them have canonical source
providers, and continues checking all **210 native E8**, three original
switch tables (**53 PE HIGHLOW**) and 38 in-body HIGHLOW relocations.
This exact-child checkpoint does **not** establish that any of the original
34-case/8-case/11-case Bullet command dispatch parent is exact or linked.
