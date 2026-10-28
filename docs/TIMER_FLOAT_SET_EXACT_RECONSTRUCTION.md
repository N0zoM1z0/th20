# CORE/EXACT-238 — complete native Timer float assignment and initialization

The immutable target is Japanese TH20 v1.00a Steamless, PE SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original function intervals, native C++20 compiler ABIs and
full-length original relocation targets were independently audited, not taken
from old source names or Ghidra's guessed return conventions.

| Complete native method | Entry | Bytes | Relocations | Locked full strict replay |
| --- | --- | ---: | ---: | ---: |
| `Timer::set(float)` | `0x004841F0` | 103 | 3 | 103/103 |
| `Timer::operator=(float)` | `0x0047C5F0` | 33 | 1 | 33/33 |

The actual original 16-byte `Timer` object has `previous` at +0, `current`
at +4, `current_fraction` at +8 and flags at +12. The native 103B setter
checks `flags & 1`, and only if uninitialized invokes genuine `reset()` at
`0x00423F50`, native `set_mode(0)` at `0x00423FE0`, and sets initialized
bit 0. Unlike the separately accepted **integer** setter, the float setter
then writes **truncated-toward-zero** integer `current = (int)value`, stores
the **untruncated** input to `current_fraction`, and writes
`previous = (int)(value - 1.0f)` via native SSE `cvttss2si`. Original float
1.0f at `0x0056C8CC` and both original member call addresses were
independently anchored. The emitted x86 behavior also preserves the native
SSE out-of-range conversion instruction; no separate blanket C++ domain
assumption was used to claim broader semantics.

The native 33B wrapper receives a floating argument by the actual MSVC x86
`__thiscall`, puts its original scalar bit pattern on the stack, invokes the
full 103B method and returns with `ret 4`. Its unique native `REL32` call
relocation is `0x004841F0`. This true `Timer::operator=(float)` is called
**twice** by the separately open native **662B** `Bullet::cancel` function
at `0x0047CB34` and `0x0047CB50`, and is also used in the original 3,735B
Bullet emitter path. Neither whole boss is credited by this checkpoint.

The maintained code is a natural single source `src/TimerFloat.cpp` with
actual declarations inside the existing `Timer` in `src/Timer.hpp`.
Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` emitted **all 120/120 original non-relocation bytes** and
**all four** independently anchored original relocation fields. The two
canonical complete original bodies strictly replayed **136/136 bytes**
from `build/core238-canonical/TimerFloat.obj`. There is no artificial
padding, duplicate object layout, compiler-specific alternative source or
unaccepted hidden function fragment.

## Actual affected-only include closure (not an unfiltered cold replay)

Changing the real shared `Timer.hpp` affects **95 existing source providers,
595 existing strict native units**, as established by the original locked
compiler include receipts. They include the entire Bullet, Enemy, Animation,
ECL, Item, Laser, HitCtrl, Player, Interpolation, and Renderer source graphs,
as well as the original `probes/EnemyShotAllocation.cpp` owner. Every one
of these **595/595** old strict units was cold recompiled and fully replayed
in eight source-filtered groups, each with real `--source` constraints.
The **two new exact units** add one new cold object. Total verified scope:
**597/597 exact units across 96 freshly compiled objects**. The unaffected
repository units were not recompiled, and no full/unfiltered cold replay ran.

Twenty-one old functions required **32 changes to compiler-private diagnostic
literal `$SG` symbol identifiers** after the new overloads changed MSVC
internal numbering. For each change, the offset and relocation type were
required to be identical, both old/new names had to be local `$SG` labels,
and the previously independently anchored original PE data target address
was preserved. The individual affected source was then immediately recompiled
and run through the **unchanged strict canonical comparator**. No other
symbol, target address or code-body mismatch was waived or rewritten.
The audit of every symbol/offset and its immutable original target is in
`.analysis/core238-timer-sg-corrections.jsonl`.

Scoped proof logs:
`.analysis/core238-timer-float-canonical-replay.log`,
`.analysis/core238-timer-affected-replay-part-0.log` through
`.analysis/core238-timer-affected-replay-part-7.log`; source closure
inventory `.analysis/core238-timer-affected-sources.txt`.

The original 662B Bullet cancellation function at `0x0047C8F0`, the 273B
single-draw-group function at `0x0047DB70`, the 3,735B Bullet single-shot
emitter at `0x004818E0`, and the 41,967B Enemy ECL dispatcher at
`0x0048C010` remain **full source/COFF nonexact**. Exactness here is
function-local with complete relocation ownership and does not imply the
full game now links or runs.
