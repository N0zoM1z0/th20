# Enemy opcode 554: genuine BulletController two-axis setter (CORE/EXACT-174)

The sole source-comparison target remains the Japanese TH20 v1.00a Steamless
PE32, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **41,967-byte** Enemy opcode dispatcher at `0x0048C010` is still
**unimplemented and not machine-code exact**. This batch restores its **complete
39-byte** real BulletController callee, not a sliced portion of the dispatcher.

## Independent original native path

The native opcode 554 primary head starts at `0x004961D5`. It first reads the
`EnemyState::context` pointer at State+`0x2EC`, then calls the 16-byte
shared getter at `0x0040C300`. This getter reads its receiver's **first
pointer word**; actual Context ownership independently establishes
`Context::bullet_controller()` at offset zero, so the returned pointer is the
real BulletController, **not** an EnemyState or Renderer service adapter.
The root caches that pointer **before** reading any float operands.

It then evaluates `EnemyState::float_argument(1)` (Y) followed by
`float_argument(0)` (X), and forwards the saved values to x86 thiscall
`0x00486480` as `(X, Y)`. The callee writes two single-precision words to
the receiver at `+0x4C` and `+0x50` and returns with `RET 8`. Actual native
BulletInf storage independently has `BulletController::vector_4c` at exactly
`+0x4C`; its X and Y words occupy these locations. No `Context` relookup,
parameter reorder, float scaling, extra state change, or global is inferred.
The existing `BulletController` is a very large real owner, containing a
2001-slot bullet pool; preserving its complete storage is essential.

The natural maintained method is
`void BulletController::set_vector_4c(float x,float y)` assigning the real
`vector_4c.x` and `.y` members in order. Pinned MSVC 19.44.35211 x86
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
emits **39/39 exact original bytes**, with **zero relocation fields**.
A native x86-only static assertion establishes the `vector_4c` member offset.
The method and storage declaration reuse existing real `src/BulletController.cpp`
and `src/Bullet.hpp`; no additional invented owner or source-matching facade
is introduced. The field's original source spelling remains inferred.

## Scoped whole-source recompilation and semantics

Authentic compiler include receipts select **5** affected translation units
containing **31** previously accepted complete strict functions, including
Dialogue, Bullet construction, Item spawning and AnimationCallback.
All five are cold rebuilt into a separate `build/core174-canonical/` directory
while retaining the original object/receipt products unchanged. The original
31 plus the new 39-byte method replay **32/32 complete exact strict units**,
covering **6,539 comparison bytes**. Five renamed COFF-local string symbols
are reconciled by byte-for-byte identical original COFF, final cold COFF and
complete original PE constant extents, not by solving comparison relocations.
All **10** old object/receipt SHA-256 hashes survive, and the other **159**
canonical object receipts remain valid. Private proof files are
`.analysis/core174-bullet-affected.json`, `core174-literal-reconciliation.json`,
`core174-strict-replay.json` and `core174-bullet-final-exact-proof.json`.

The actual production BulletController host passes **64** independent
X/Y float-bit-pattern combinations. It checks the **entire owner byte image**
after each setter call, allowing only the two target float words to change.
Samples include ±0, ±1, a normal magnitude, maximum finite, +infinity and a
quiet NaN payload, compared by bytes rather than NaN equality. Native x86
layout is separately proved; host x64 member offsets are never assumed to be
native. Existing full bullet pool construction, 2001 handle slots, metadata
retirement, and Context routing tests also remain passing. This is host-side
O2/UBSan corroboration, not full native-game runtime execution.

## Open complete-root integration

The original opcode 554 subpath is part of the single, unaccepted Enemy root.
Its private full-root host case integration must still exercise Y-before-X
argument reads, the original cached BulletController identity when the Context
changes during operand evaluation, and the actual whole-owner float writes.
Renderer, Bullet VM, whole root compiler tables and callback/resource paths
remain open. This new 39-byte full callee does not grant any partial 41KB root
byte credit.
