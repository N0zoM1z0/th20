# Enemy opcode 555: native resource chain and exact Bullet file getter

CORE/EXACT-185 recovers one actual dependency of the **entire** native
`EnemyState::execute_opcode` root at `0x0048C010` (41,967 bytes). It does not
accept any bytes of that root. The 555 case is independently decoded from the
locked Japanese Steamless target, not assumed from a reference source. The
following observations are bounded to original opcode 555 and its concrete
call chain; owner names without separate evidence remain provisional.

## Native evidence

The primary jump-table entry for opcode 555 resolves to `0x0048C3F4`.
The branch through `0x0048C573` has two independent signed nonnegative gates:

- `EnemyState+0x250` selects `SoundInf::request_effect_at` at `0x00426EB0`.
  The x-coordinate comes from `Motion` at state `+0x110`, accessed through
  the genuine 16-byte float view `0x004292E0`. The call receives the original
  `field_250` and coordinate, with no VM operand reads.
- `EnemyState+0x254` enables a visual effect. Only inside that gate does the
  caller calculate squared XY distance between `state.vector_6c` and the
  independently accepted `EnemyState::position_ref` (`0x00499350`).
  It uses squared `0.2f` as a strict comparison; near points use `-pi/2`,
  otherwise it asks `geometry::direction_xy` at `0x0047A2E0`.
  The actual `Context::enemy_controller` getter is `0x00412730`, followed by
  `EnemyController::animation_file` at `0x004AAE10`, with the complete
  `state.field_258` index. `AnimationFile::spawn` at `0x004790E0` is then
  called with a null stem, `field_254` script, a **fresh** position reference,
  the selected direction, layer `-1`, and null output. Its temporary handle is
  not published by this opcode.

The selected 151-byte controller file dispatcher (`0x004AAE10`) is a separate
nonexact owner. Its native control flow distinguishes indices 7 (unresolved
Stage/Background global `0x005C069C` and getter `0x004AADF0`), 0 (actual
Context BulletController and the getter below), 1 (actual Context EffectInfo
and its array0 getter), and other indices (the checked eight-pointer array
at `EnemyController+0xE4`, via `0x004AA130`). The array helper tests the
**unsigned** index against 8. This is *not* a uniform array-only lookup.
The native 555 caller observes the result but does not repair null files.

## Complete exact dependency: BulletController file view

The index-zero path of `0x004AAE10` invokes `0x004859B0` (20 bytes).
The exact native instructions are a normal x86 `thiscall` prologue, a read
of the receiver and `mov eax, [eax+0x286D8C]`, followed by frame teardown and
`ret`. The native 20-byte SHA-256 is
`3d13427bac7c6680c840bb2d875b8e6ba70e093933dbdd7696c040e58e4b3d55`.
The actual `BulletController` layout places its `AnimationFile* file` at
`0x286D8C`, independently supported by the large pool, handles, linked lists,
and following controller fields. The maintained production method is
`BulletController::animation_file() const` in `src/BulletController.cpp`.
The original source spelling and `const` annotation are inferred, not claimed
as recovered symbols. The genuine game-specific caller/owner establish this
as an authored accessor rather than a generic compiler or STL routine.

Pinned MSVC 19.44.35211 x86, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, emitted **20/20 byte-identical** native bytes,
with zero relocations. Canonical unit `bullet_controller_animation_file`
now resides in `config/match-units.toml`, alongside the other ten methods from
the same genuine BulletController TU. This is full native codegen credit for
one function, **not** byte-exactness for `0x004AAE10` or `0x0048C010`.

The `Bullet.hpp` declaration changed the actual compiler include closure of
**five providers**: DialogueText, Bullet, BulletController, ItemSpawn and
AnimationCallback. Only these five objects were cold-built (priority 15),
with **33/33 whole canonical units** passing strict relocation replay.
The MSVC private `$SG` symbols for one Bullet constructor literal and four
Dialogue literals moved by one in the new objects. Their independently
established original relocation targets and complete comparison extents remain
unchanged; the manifest reflects the newly observed source-symbol names.
No other provider was cold-built, and **no unfiltered replay** was performed.
The local receipt log is `.analysis/core185-affected-replay.log`.

## Remaining work

The full 555 branch is not yet integrated into the current private whole-root
host candidate. It must be added to the *same* 41,967-byte Enemy dispatcher
exercise, preserving real position/geometry/sound/File wrapper calls and the
four resource selection routes. Independently test the exact threshold,
signed sentinel gates, nonread VM operands, recipient pointer retargeting,
exception paths, and no effect-publication side effect. The 151-byte
`EnemyController::animation_file` and Stage owner at `0x005C069C` must be
reconstructed without inventing an array-only shortcut or claiming that the
full Enemy switch is machine-code exact. The target's 174 heads, EH and jump
partition remain open.
