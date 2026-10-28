# CORE/EXACT-232 — complete 419-byte Bullet item-drop boss and 136-byte screen test

This checkpoint independently reconstructs two **entire original game functions**
from the immutable Japanese TH20 Steamless v1.00a PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Names are inferred; every complete code interval, native target address and
calling convention was separately inspected. Reconstructed source is maintained
in `src/BulletDrops.cpp` and `src/BulletScreenBounds.cpp`, with the typed screen
ABI exposed through `src/BulletScreenBounds.hpp`.

| Entire native function | Original entry | Whole size | Original relocations | Fresh strict replay |
| --- | --- | ---: | ---: | ---: |
| `Bullet::cancel_drops` | `0x0047D3D0` | 419 B | 20 | 419/419 B |
| `bullet_position_outside_screen` | `0x00485390` | 136 B | 5 | 136/136 B |

The original 419B Bullet boss contains **121 native x86 instructions** and
an independent call at `0x0047CABA` from the original complete 662B
`Bullet::cancel` (still nonexact). Its native interval SHA-256 is
`53ab4a62abea6a1d576eeba27a5d288829a351a5e4514e15996408d60da7cfa5`.
It rejects cancellation mode 0 and out-of-screen positions, then increments
the **real BulletController item counter at +0x286D80** obtained from the
Bullet's live Context. With mode 1, the actual `Context::item_controller()`
provides the original `ItemInf::spawn_many(position,1,13)` at `0x004C45B0`.
Mode 4 consults the owner's actual **signed** counter remainder modulo 5,
with original short-circuit decisions for remainder 0, remainder 2 + the
native `script_random.next() % 2 == 0`, and remainder 4 + the same process
RNG `% 3 == 0`. The owner lookup is repeated where the original native
instructions repeat it. The random stream is the real global at
`0x005BA4A8` and RNG method `0x00423EE0`, not an invented local engine.
On the rare branch, it calls the original entire `ItemInf::spawn` at
`0x004C3C90` with game type 2, color `0xffffffff`, original
`-3.1415927410125732f / 2.0f` angle, **2.2f** speed, zero delay/extra
and sound -1. On the fallback it calls the actual `spawn_many` with type 13.

The complete native screen predicate at `0x00485390` has interval SHA-256
`8371f851e86a5a024d502f1a393410c74d7f2346910f5b2a166316fe034d8b83`.
It evaluates **four ordered SSE boundary comparisons** of the true Vector3
position: `x + width <= -384.0f/2`, `x - width >= 384.0f/2`,
`y + height <= 0`, and `y - height >= 448.0f`. Inputs are the caller's
actual 32.0f extents from `0x0056CD94`. The threshold literals at
`0x0056FD6C`, `0x0056CDA4`, `0x0056C8D0` and `0x0056D7C0`
were checked independently from original native PE bits. Retaining the
original **SSE operand order** for the second comparison matters: an
apparently equivalent expression comparing the constant on the left compiled
to an incorrect sequence. Native floating unordered/NaN conditions and the
full-EAX integer return semantics are preserved.

For the 419B boss the first natural source attempt compiled to 444B with
wrong long-jump shapes, **unsigned** rather than native signed modulo 5, and
floating temporary spills before `ItemInf::spawn`. Moving to natural nested
conditional branches, converting the counter to signed before `% 5`, and
materializing the real `ItemInf*` receiver produces all **339/339
non-relocation bytes**. Separately, the screen function reproduces its full
**116/116 non-relocation bytes**. Locked MSVC 19.44 x86 `/Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` freshly builds both complete
objects and replays all **25 original relocation offsets, types and targets**,
producing **555/555 exact original bytes** without copied instructions,
artificial padding or relaxed comparison. The original complete larger
662B Bullet cancel is not given partial credit by its exact 419B callee.

Adding the one real declaration to shared `Bullet.hpp` affects **15
previously exact source objects/52 existing exact units** by the captured
compiler include closure. They were all recompiled, and all **52/52 prior
units remained exact**, including the 832B Bullet collision boss, 339B
Bullet firing boss, 401B capped cancellation and 388B filtered cancellation.
The new 419B and 136B functions add two cold objects. Total **54/54
complete strict affected units across 17 freshly built objects**; no
unfiltered cold replay. The compiler renumbered only private diagnostic
`$SG85490` to `$SG85493` for BulletController and Dialogue strings
`$SG117835..117838` to `$SG117838..117841`; native data addresses and
relocation fields remained unchanged. Focused replay logs:
`.analysis/core232-bullet-drops-screen-replay.log` and
`.analysis/core232-affected-bullet-scope-replay.log`.

Remaining major original game-owned sources still nonexact include the
**662-byte Bullet::cancel** at `0x0047C8F0`, the **3,735-byte**
`BulletController::emit` at `0x004818E0` and the **41,967-byte**
Enemy opcode dispatcher at `0x0048C010`. Whole-function exactness does not
prove full-game linker or runtime completeness.
