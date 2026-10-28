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
  the selected direction, layer **`3`**, and null output. Its temporary handle is
  not published by this opcode.

The layer `3` is independently verified by the original instruction
`push 3` at `0x0048C540` (part of the ten native direct calls and 81 native
instructions in the **388-byte** 555 branch at `0x0048C3F4..0x0048C577`).
This corrects an earlier mistaken analogy with `Enemy::defeat`, which uses
layer `-1`. The native branch SHA-256 is
`5ab9c44d05b183785798d82102af4643c853bca652d0766f463c2548686016cd`.
The input/root provenance and original call targets are independently checked
in `.analysis/core185-native-555-audit.json`.

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

## CORE186: same whole-root opcode 555 integration

The 555 case is now inside **one entire existing** 41,967-byte Enemy root
source draft: `.analysis/core185-enemy-dispatch-candidate.cpp`. Neither a
standalone partial-root function nor a separate replacement dispatcher was
introduced. The real maintained `geometry::squared_distance_xy` and
`geometry::direction_xy` are linked alongside the already exact original
SoundInf coordinate-to-pan method, EnemyState position owner, native
`BulletController::animation_file` and the actual four-argument AnimationFile
wrapper. The final renderer/VM seven-argument producer remains captured at its
original interface. The index-0 file lookup actually uses the newly exact
Bullet getter; other routes are honest private boundaries until their
resource owners are independently reconstructed.

`.analysis/core185-dispatch-host-recipe.json` selects 81 TUs (the previous
80, plus real `src/GeometryMetrics.cpp`) and builds with GCC 13 `-O2`,
`-Wall -Wextra -Werror -fsanitize=undefined`. Its
`.analysis/core185-dispatch-host.log` passes **38,973 / 38,973** full-root
host cases: **all 38,433 predecessors plus 540 new 555 cases**. The new
matrix covers signed independent `field_250`/`field_254` gates,
negative/zero/positive ids, nine XY displacements including both sides of
0.2, two live Contexts, five distinct indices, real pan conversion and
fresh position references. Of the new primary matrix, **252** run the real
SoundInf path and **252** invoke the real File wrapper. Further cases capture
**18 expected exceptions** at the sound queue, file selection and VM
boundary, asserting call order, short circuit, zero VM operand reads and
unchanged complete Enemy/Context/controller owner images. The original layer
3 is asserted in every effect call, not copied from the defeat routine.

The host executable `build/core185-dispatch-host`, the new private candidate,
recipe, audit and proof are **protected live evidence**. The SHA-bound private
proof `.analysis/core185-enemy-whole-root-proof.json` refers to four exact
source inputs. CORE183 and all older root evidence remain intact.
This batch changed no further production input/headers beyond CORE/EXACT-185,
so its new **cold-build/replay affected-unit count is zero**; it reuses the
33/33 complete already-verified canonical receipt outcome. No unfiltered
native replay, whole-image replay or full cold build was run.

## Remaining work

The complete native 41,967-byte root **is not codegen/byte exact**; its draft
now covers **124 effective opcode values / 95 native primary heads** of
174 total native primary heads. Original jump tables, exception scopes,
compiler partition, missing case heads and VM/resource lifecycle remain open.
The 151-byte genuine `EnemyController::animation_file` at `0x004AAE10` is
still nonexact; it differentiates indices 0/1/7 from ordinary array indices.
Its Stage/Background global owner `0x005C069C`, along with the downstream
renderer and animation loader, must be resolved from native producers and
consumers before integrating their actual production bodies. Do not claim
that semantic host cases confer exact native credit on those large routines.
