# CORE/EXACT-225 — original complete six-group Bullet draw orchestrator

This checkpoint reconstructs the entire **81-byte** original gameplay draw
method `0x0047DC90..0x0047DCE0` from the immutable Japanese TH20 v1.00a
Steamless PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
The whole original interval SHA-256 is
`6937bd381b5dbccd3f08bde9e117ef96c2efa1623883c33271e9f17de267b5a4`.
The native body was read independently with Capstone and Ghidra and compared
against real typed BulletController ownership; original C++ spelling remains
inferred.

`src/BulletDrawGroups.cpp` contains the complete game-specific
`BulletController::draw_groups()` method. It resolves the process animation
manager pointer at original global `0x005C0028`, invokes the actual Renderer
presentation/layer selector at **`0x0044F3D0`** with constant **12** and
the Controller's real `view_index` at +`0x286D9C`, then calls the genuine
original `BulletController::draw_group(int)` at **`0x0047DB70`** for each
index **0 through 5**, in increasing order, and returns integer one.
This is the whole drawing orchestration, including all iteration and return
instructions, not a prefix or one unrolled draw-group arm.

The natural C++ `for` loop with the locked MSVC 19.44 x86 profile
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` compiles to
**81/81 exactly identical original bytes** and the three independently
verified relocation fields:

- `+0x17` `DIR32` -> original animation pool global `0x005C0028`.
- `+0x1C` `REL32` -> native `AnimationPoolOwner` layer-selection call `0x0044F3D0`.
- `+0x41` `REL32` -> native `BulletController` single-group draw `0x0047DB70`.

The last two native function bodies are **still nonexact** (original
806-byte Renderer presentation selector and 273-byte single-group draw).
This full exact 81B caller proves their ABI and call ordering, but does
**not** imply its two callee bodies are reconstructed or the original
complete Renderer allocation/global initialization is known.

The earlier exact `Bullet::deactivate()` used a narrow `AnimationPoolOwner`
ABI declaration inside its own translation unit. To prevent inconsistent
class definitions across rendering and retirement, the maintained
`src/AnimationRuntimeOwner.hpp` now declares their **one shared external
method ABI** (`release_animation`, `select_draw_layer`, `draw`) and the
pointer `current_animation_pool`. This header does **not** invent the unknown
original manager storage members, promise a real linker/global definition,
or claim full game startup/runtime behavior. The original 291-byte
Bullet retirement remained **291/291 exact** after this change.

The addition of two real BulletController member declarations to shared
`Bullet.hpp` requires revalidating the complete existing include closure:
**nine existing source providers, 45 old strict units** including the
339-byte Bullet firing method, 291-byte retirement and all four previously
accepted vertical/horizontal reflection functions. All **45/45** previously
exact functions were freshly cold-compiled and compared with zero byte or
original relocation regressions. Only MSVC-private diagnostic string labels
shifted (`$SG79850` -> `$SG79853` in BulletController and
`$SG117786..117789` -> `$SG117789..117792` in Dialogue); all four
original data addresses and all relocation sites remained unchanged.
**Total: 46/46 strict units across ten fresh MSVC objects** (45 previous +
new 81B). No all-graph cold replay was performed.

Focused proof logs:
`.analysis/core225-draw-groups-and-lifecycle-replay.log` and
`.analysis/core225-bullet-header-other-affected-replay.log`.
The native **3,735-byte** Bullet single-shot emitter at `0x004818E0`
and **41,967-byte** Enemy ECL opcode dispatcher at `0x0048C010` remain
nonexact. A natural full-body probe of the 211-byte Bullet movement step
at `0x0047D960` emits **212B** (one extra compiler NOP), while a 273-byte
single-group draw probe still differs in original floating/x87 argument
ordering and real Animation flag field semantics; neither incomplete body
is admitted as exact. Their original boundaries and attempted source are
retained privately under `.analysis/core221-*` and `.analysis/core223-*`.
