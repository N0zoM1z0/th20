# CORE/EXACT-296 — exact complete 863-byte active Bullet update and six-group draw-list boss

The original Japanese TH20 v1.00a Steamless PE SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original complete game-owned `BulletController` active-bullet frame
method at **`0x0047D600..0x0047D95E`** is now natural typed C++20 in
`src/BulletActiveLoop.cpp`, inferred spelling
`BulletController::rebuild_active_bullets()`.

**Entire native code: 863/863 bytes strict exact; all 237 original x86
instructions; all 35 original relocation sites independently matched,
including EH handler, security-cookie, process globals, all intrusive
iterator/Timer methods, and both game-owned Bullet child functions.**
Original full native interval SHA-256:
`53aed6755f58a249053439bba8cffb00aae26a62e4706079489a142efbd3fe06`.
The genuine x86 source frame is `0x34` bytes and has the original managed
C++ exception handler and `IntrusiveIterator<Bullet>` destructor.
No standalone loop arm, raw opcode array, fake class prefix, assembler
insert, dummy local or ABI-incorrect helper earns exact credit.

## Original complete active-Bullet frame protocol

The native Controller first selects its current animation view through
the real `AnimationPoolOwner` at original global `0x005C0028` and
native `0x004776A0`. It resets the actual `BulletController::bullet_count`
at `+0x44`. It then clears **each of six `draw_heads` and all six
`draw_tails` pointers** in original MSVC order, covering real native
Controller offsets `+0x14..+0x43`. The normal chained C++ assignments
compile to the original explicit 5-to-0 array write sequence; a generic
`memset` here would be false codegen, even if semantically similar.

The Controller iterates its actual `active` intrusive list at
`+0x286D64`. The source constructs a real **two-pointer** managed
`IntrusiveIterator<Bullet>` using native `begin` at `0x00412280`,
computes the native `end()` sentinel at `0x00412540`, uses genuine
`differs()` at `0x00411BB0`, `get()` at `0x0040C300`, and advances
through native `0x00411C30`. Its original 8-byte default initialization
at `0x0040C080` and complete destructor `0x00411B00` are preserved as
the existing typed iterator protocol, **not** byte-level code generation.

The original global `current_game_controller` at `0x005BA828` points to
the **existing real** 0x110-byte `GameController`. Native
`GameController::game_flags` is at `+0xE8`. If the controller exists and
its bit 11 is set, the function intentionally **skips physics/collision
but still processes drawing-group publication**. This is a real, natural
common branch in maintained C++; the compiler emits the original short
conditional jump followed by the original unconditional jump, rather
than a different long conditional encoding.

Otherwise, for each live Bullet, original flag bit 8 selects collision
special handling. If Bullet state equals 2 and the exact native Timer
at `+0x4F8` has reached eight frames, or if state equals 1, the method
calls the **already entire strict-exact 2,018B**
`Bullet::process_collision(1)` at `0x00484A20`. For other cases, it
calls the **already exact complete 211B** `Bullet::step_update()` at
`0x0047D960`. A nonzero step-update result means the Bullet is no
longer eligible for publication; its managed iterator advances exactly
once before the next test. The original bit-9 suppression check on the
Bullet flags then governs the rendering-group path. All other eligible
bullets append to one of the genuine six singly linked draw groups:
first `draw_heads[group]`, then the previous `draw_tails[group]` chain's
`Bullet::draw_next` at `+0x60`, then update the new tail and clear the
new `draw_next`. Finally, for each active Bullet (including those with
drawing suppressed), the Controller increments its original live count
and postfix-increments real `Timer+0x4F8` at `0x00423540`.

## Two independent native ABI and source-control corrections

The previous intact source attempt `.analysis/core295-BulletActiveLoop.cpp`
was a **whole function**, but the source incorrectly used `while` with
multiple manually repeated iterator `advance()` operations. It emitted
**987 bytes/265 instructions**, with about 203/237 native mnemonic
positions aligned. Rewriting the actual lifetime as a normal `for`
loop, with its one shared iterator advancement and the original
short-circuit collision-or-step condition, reduced it to **835B/221
instructions** with **212/237** original mnemonic kinds aligned.

A particularly important independent ABI correction is the native
`IntrusiveLink<Bullet>::node_access()` at `0x0040F160`, returning a
**`Bullet*&`** (a pointer to the stored Bullet pointer) rather than
`Bullet*`. The original caller must load the pointer by dereferencing
its returned address. Most of the previous source used
`node_value()` with a different return type, spuriously omitting
**one native 2-byte `mov` after each access**. Changing to the genuine
existing `node_access()` reference contract, while keeping the one
actual `node_value()` use needed for draw-tail publication, restored
all of these original instructions. That second getter uses native
`0x0040C300`, a physically shared/folded original 16-byte getter
already represented in historical tracking. **No new exact credit is
assigned to either child getter.**

Second, MSVC must run the genuine iterator destructor before loading
the final return value one. Placing its natural iterator and `for`
loop in a nested lexical scope gives an actual C++ RAII lifetime and
makes the original `0x34` stack frame and last `call destructor; nop;
mov eax,1` sequence, instead of a synthetic compiler-shaping return
local and the prior incorrect `0x38` frame. The complete whole function
was then **862B/236 instructions with 235/237 native kinds aligned**.
The final single substantive control-flow correction is a normal
`goto publish_draw` when the live GameController freeze bit is set:
this implements the real common draw-list path, not an inert label or
machine-code padding. It emits the native **2-byte `je` plus native
5-byte `jmp`** instead of a merged 6-byte `jne`. The final code is
**863B/237 instructions and 723/723 original non-relocation bytes**.

## Independently attested native relocations and strict replay

For all **35** original COFF relocation positions, the immutable PE was
independently disassembled and the original operand identified before
canonical registration. The 30 relative relocated calls correspond
to true original intrusive iterators, native `Timer`, full Bullet
collision/step methods and genuine stack-cookie cleanup. The five
absolute native data references are original x86 EH handler
`0x005683CD`, native cookie at `0x005B25C0`, global AnimationPoolOwner
at `0x005C0028`, and the twice-used true GameController global at
`0x005BA828`. No relocation address is merely copied from a comparator
solution or inferred solely from earlier prose. See the private
`.analysis/core296-bullet-active-native-35-relocations.json` and
`.analysis/core296-bullet-active-native-attestation.log`.

The locked MSVC 19.44 x86 C++20 compilation profile is `/nologo /c
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
run at reduced scheduling priority. Complete canonical strict result:
`bullet_controller_rebuild_active: exact (863/863 bytes)` in
`.analysis/core296-bullet-active-canonical-replay.log`, with all
35 original native relocation targets in the maintained
`config/match-units.toml` unit.

## Exact changed-header closure and remaining large roots

The maintained C++20 method adds only one actual external member ABI
to existing `src/Bullet.hpp`, and its single natural new source owner.
According to the compiler's historical *real include receipts*,
`Bullet.hpp` has **29 existing source providers / 67 previously
accepted complete exact native units**. All **29 old source objects**
were freshly recompiled and **all 67/67 prior exact units strictly
replayed**, including the complete 2,018B collision, 1,846B physics,
662B cancellation, 781B wrap, all accepted Bullet commands and original
Controller constructor. The only renumbered symbols were MSVC-private
`$SG` literal names in Bullet cancellation, BulletController and
Dialogue; every relocated offset, COFF type and original data target
remained independently fixed, and each source was rerun under the
strict comparator. Total local regression scope is **68/68 exact
old+new native units across 30 cold objects**, with no unfiltered
whole-repository cold replay.

The whole **1,404B** command-11, **273B** single-group draw,
**3,735B** shot emitter, **12,140B** Bullet command sequencer and
**41,967B** Enemy opcode dispatcher remain separate nonexact roots;
acceptance of this native update boss does not grant partial credit
to any of those parents or prove complete game linkage.
