# CORE/RECON-961 — complete original 187B RendererPool generation/AnimationHandle registration strict exact

The immutable original is Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0044C8F0` is a **187B/56-i386** game-owned registration
method: it assigns one composite generation/index `AnimationHandle` to a
new Animation and returns that Handle by value using MSVC's genuine
hidden-result-pointer ABI. It is the true last callee of all four
[separately strict-exact original 72B/75B Renderer spawn modes](ANIMATION_SPAWN_RENDERER_FOUR_MODES_STRICT_EXACT.md).

## Immutable original PE evidence and actual generation algorithm

[`scripts/verify-animation-renderer-handle-register187-native.py`](../scripts/verify-animation-renderer-handle-register187-native.py)
decodes every original 187B, 56 x86 instructions and `ret 8`, checks the
original `0x1C` stack frame, all **six genuine original E8 physical
locations AND target addresses**, confirms **zero PE HIGHLOW** fields,
and checks the four real 72B/75B parent E8 instructions:

| Original physical E8 | Native destination | Role independently established from native bytes |
| --- | --- | --- |
| `+0x19` and `+0x5F` | `0x00449570` | Postfix increment of four-byte generation counter (callee returns old word) |
| `+0x2C` | `0x00449690` | Bitwise **AND assignment** of counter with actual literal `0xFFFF` |
| `+0x43` | `0x00449430` | Compare generation counter to zero, native boolean return |
| `+0x76` | `0x004493E0` | Return current generation shifted by 16, native `push 16` |
| `+0x9F` | `0x004117A0` | Assign composed `uint32_t` into actual `AnimationHandle` at `Animation+0x4C0` (folded Identifier32 assignment physical code) |

The four parent E8 sites are `0x0044B82A`, `0x0044B87A`,
`0x0044B91D`, and `0x0044B8CD`. All physically target `0x0044C8F0`.
The original receiver's counter is at **pool offset `+0x07D40E88`**;
the original Animation's low-order index resides at `+0x4C4`.
The native writes `((generation << 16) | (index & 0xFFFF))` to the
real Handle at `+0x4C0`, then returns its actual 32-bit value. It
increments generation, AND-masks it with `0xFFFF`, checks zero and
increments again on zero, so the produced generation is kept nonzero
for wraparound. These are original instruction/protocol facts, not
invented API names.

## Source reconstruction and the essential actual C++ operator

[`src/NativeRendererPoolRegister.hpp`](../src/NativeRendererPoolRegister.hpp)
is a single non-owning view shared with all four Renderer spawn sources.
It records the independently observed 0x07D40E88 counter offset with
an explicitly **unclassified prefix** of bytes and a four-byte counter
object, but does **not** instantiate or allocate that enormous owner;
complete RendererPool storage/layout remains unknown. The counter view
exposes native postfix `operator++(int)`, bitwise `operator&=`, a
zero-comparison and generation-bit read. These are supported by the
original callee instructions, rather than mistaken Ghidra labels.

The natural whole
[`src/AnimationRendererHandleRegister187.cpp`](../src/AnimationRendererHandleRegister187.cpp)
uses ordinary object/member operations and existing `AnimationHandle`
assignment. The first direct `counter.intersect_mask(0xFFFF)` source
compiled to **195B/58 i386**, introducing a surplus pointer temporary;
it was rejected. A real C++ `counter &= 0xFFFFu` directly corresponds
to native `0x00449690` and naturally emits the original argument-first
calling order and **187B/56-i386** instruction stream. An explicit
postfix counter operation similarly matches original `0x00449570`.
No raw opcode, fake NOP or manual relocation adjustment was inserted.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits all original 187 bytes, 163/163
nonrelocated byte matches and all six native-anchored relocation roles.
The shared Renderer class header is also used by the already exact
72B+72B+75B+75B spawn modes. Their entire code was independently
recompiled and remained strict exact:

```text
animation_renderer_handle_register_187: exact (187/187 bytes)
animation_spawn_renderer_normal_72: exact (72/72 bytes)
animation_spawn_renderer_flag2_72: exact (72/72 bytes)
animation_spawn_renderer_flag4_75: exact (75/75 bytes)
animation_spawn_renderer_flag6_75: exact (75/75 bytes)
Exact replay: 5/5 affected units, 2 cold objects
```

This contributes **one new original game-authored whole-exact
function /187 native `.text` bytes**. The existing folded 21B
Handle-assignment and other separately accepted child/helper sources
are **not double-credited**. The complete RendererPool owner allocation
and startup, 39,470B Animation VM and whole-game linking/playability
remain unfinished. No global cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-renderer-handle-register187-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererHandleRegister187.cpp --source src/AnimationSpawnRendererFourModes.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
