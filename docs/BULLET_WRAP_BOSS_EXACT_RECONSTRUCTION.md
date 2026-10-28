# CORE/EXACT-248 — full 781-byte Bullet screen-wrap boss and real SpriteData chain

Original target is the immutable Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original source names are inferred; all complete function extents, x86
instruction streams, ABI/data identities and relocation destinations below
were independently checked against original PE disassembly and Ghidra.
No partial native prefix, copied machine-code array, fake SpriteData prefix,
compiler padding or assembly is admitted.

| Complete original native function | Entry | Native bytes | Native relocations | Canonical strict result |
| --- | --- | ---: | ---: | ---: |
| `Bullet::wrap_screen` | `0x00483270` | **781** | **25** | **781/781** |
| `Animation::animation_file` | `0x00437500` | 29 | 2 | 29/29 |
| `AnimationFile::sprite` | `0x00437C80` | 23 | 0 | 23/23 |
| `Animation::sprite_data` | `0x00437CD0` | 45 | 2 | 45/45 |

**Four whole source functions, 878 new original native bytes, 29 independently
verified relocation sites across two fresh MSVC x86 objects.**
Original interval SHA-256 respectively:
`55aad8459ac15ab485f06119d89dabe73e093c0c7ebc334ba7a45c548ed90f96`,
`78de66b8b0432047fe07f8fd0be4c7aa62781fb359791c8e2efbbffc9ff2dd18`,
`ea69924af1a8a838f4ceb6d8a51e62e1e7d8b2ce00d44b5161071fa2168a18d7`,
`6b7c865cf9d9a19fb5d2420e9798b243047bf4f85f552748e8806bc689145e16`.

## 781-byte original full screen-wrap/teleport gameplay boss

The complete original `0x00483270..0x0048357C` contains **202 x86
instructions** and four independent directional branches. The game-owned
`Bullet` first obtains real `SpriteData::extent_48` and `extent_4c` from
its actual `Animation*`, then calls previously exact
`bullet_wrap_outside(position, width, height)` at `0x004854D0`.
On a positive out-of-bounds result, the original
`BulletExtendedCommands::at(6)` command flags select the first eligible
wrap direction. The native flag bits in `word_38` are 1 (Y below zero),
2 (Y above 448), 4 (X below -384/2), and 8 (X above +384/2), in exactly
that priority order. Y is mirrored by adding/subtracting the original
**448 + SpriteData height**; X by adding/subtracting the original
**384 + SpriteData width**. The negative left boundary uses original
-384.0f at `0x0056FD6C`, divisor 2.0f at `0x0056C8D0`, positive right
extent 384.0f at `0x0056CDA4` and 448.0f at `0x0056D7C0`.
The first Y test uses native double-precision zero comparison, not a
silently changed float NaN behavior.

On a wrap, the original increments `commands.at(6).word_30` and, when the
signed sound ID at Bullet+0x40 is nonnegative, requests the real native
`SoundInf` effect via `0x00426D70`. On reaching the signed count threshold
`word_30 >= word_34`, it clears exactly low-word bit `0x1000` of the native
64-bit `BulletCommandFlags` and returns integer one. Otherwise it returns
zero. Original animation SpriteData lookup is intentionally repeated on
every branch, not cached across the control flow; the result is a normal
natural C++20 `Bullet::wrap_screen()` in `src/BulletWrap.cpp`.

Earlier private complete-body attempts produced **759 bytes / 197 of 202
instruction mnemonics** and were rightly refused exact credit. A further
private probe at `.analysis/core245-wrap-label-inside-if.cpp` already
contained the missing solution but had not been admitted or cross-checked
against production types. Independent replay established that the true
original `/Od` codegen has **two consecutive MSVC branch jumps** at the
end of the four direction arms, and a shared action label **inside the
natural `if (hit)` block**. Keeping that real shared-hit control flow
reproduces **202/202 instruction mnemonics**, **681/681 non-relocation
bytes**, and, after all **25** original relocation fields are anchored,
**781/781 full native bytes**. Changing control flow only to remove one
of those jumps makes this method nonexact; no arbitrary padding is used.

## Actual typed Animation / SpriteData lookup chain

Three separately complete native game methods independently establish all
SpriteData-owner offsets and the call chain used by the 781B boss:

- `Animation::animation_file` (`0x00437500`, 29B) passes the authentic
  `AnimationBase::field_1c` file ID to the external game animation manager
  (`current_animation_pool` at original global `0x005C0028`) via actual
  `0x00437970`. Both relocation sites and all bytes are exact.
- `AnimationFile::sprite` (`0x00437C80`, 23B) uses the existing real
  `AnimationFile::sprites` pointer at owner+`0x50` and native 0x58-byte
  `SpriteData` stride. The 0x58-byte type and its real `extent_48` /
  `extent_4c` members already exist in `src/AnimationFile.hpp` with native
  layout assertions; no artificial manager or member prefix was created.
- `Animation::sprite_data` (`0x00437CD0`, 45B) calls the authentic 29B
  animation-file getter, then `AnimationFile::sprite` with original
  `AnimationBase::field_20` Sprite index. Both original relocations are
  independently identified and exact.

These three methods are normally maintained in `src/AnimationSpriteAccess.cpp`.
`AnimationRuntimeOwner.hpp` only gains an **external nonvirtual method ABI**
for `file_by_index(int)` at `0x00437970`. The owning Renderer array at
+`0x6000730` and its complete initialization/layout remain unresolved;
no fake giant owner definition or full-game linker proof is claimed.

## Scoped strict regression, not full cold replay

Declaring the real Bullet/Animation/AnimationFile/Renderer methods changes
four shared headers. Their **actual historical MSVC receipt include-closure
union** comprises **61 existing source providers / 315 previously accepted
complete exact units**. All 61 objects were freshly compiled and all
**315/315** prior native units strictly replayed without a regression.
The compiler renumbered some internal diagnostic `$SG` string symbols in
BulletController, Dialogue, Enemy, Item, Player, rendering and other
providers. Every accepted update was checked automatically to be **only
an `$SG` symbol name** with exactly the same relocation offset, COFF type
and independently fixed original target address; non-private relocation,
byte or ownership mismatches terminate immediately. Source-specific replay
was then rerun and required to pass with the strict canonical comparator.

The four new entire functions also compile and strict replay together:
**319/319 total affected exact units across 63 freshly built source
objects**, with **no unfiltered whole-repository cold replay**. The source
and canonical logs are `.analysis/core248-sprite-wrap-canonical-replay.log`,
`.analysis/core248-sprite-wrap-affected-replay-part-{0..5}.log`, and the
private relocation-review `.analysis/core248-sprite-wrap-sg-corrections.jsonl`.
Original source spelling and whole-game runtime are explicitly separate
from machine-code matching.

This new admission supersedes only the **historical 781B parent nonexact
status** in `BULLET_WRAP_BOUNDARY_EXACT_RECONSTRUCTION.md`; that document's
original 176B/181B strict boundary checks remain exact and unchanged.
Remaining major whole-function targets include original **662B**
`Bullet::cancel`, **273B** `BulletController::draw_group`, **3,735B**
`BulletController::emit`, **12,140B** Bullet update, and **41,967B**
Enemy ECL opcode root. None receives partial credit here.
