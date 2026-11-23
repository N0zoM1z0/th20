# Enemy ECL opcode 629 — callback-table Bullet clear and Player movement scale

## Native branch and callback table

Opcode **629** is an inline **46-byte / 10-instruction** branch at
`0x00490B4D..0x00490B7B`, selector index **147**. It reads integer operand
0, indexes the original callback table at `0x0056FE8C`, and invokes the
selected `EnemyState` member-function pointer indirectly. The original table
is `(nullptr, 0x00488B80, 0x00488E80)`.

The two native callback Bosses are separately bounded and pinned:

| Callback | Original extent | Size / instructions / E8 | SHA-256 |
| --- | --- | --- | --- |
| Animation-rectangle Bullet clear | `0x00488B80..0x00488E76` | 758B body / 205 x86 / 34 E8 | `2f66245e6c05e12b15c2b32030a0d23be74dac207e5c6bf0724beffd0c8df3b1` |
| All-active-Bullet reset | `0x00488E80..0x00488FA3` | 291B body / 86 / 17 | `981d4d97b63177f87684ca7a6bb854b32bbe9213f01c5282869be60323d2024b` |

The first callback's 768-byte native region includes a separate ten-byte
`INT3` alignment tail at `0x00488E76..0x00488E7F`; it is not part of the
758-byte C++ function and is not credited as source. The second callback has
no tail bytes in its 291-byte body.

`scripts/verify-enemy-bullet-clear-opcode-source.py` pins the original
selector, 46-byte branch, indirect call, callback table words, complete
callback hashes, decoded instruction extents and every direct call site and
target. The two callback functions are restored as natural C++ members of
`EnemyState`, not as inline assembly or a synthetic dispatcher shim.

## Callback 1 — animation rectangle

`EnemyState::clear_bullets_in_animation_rectangle()` resolves animation
handle 0 and reads its X scale, Y scale and Z rotation. It obtains the live
Context BulletController and traverses the real active intrusive Bullet list.
For each Bullet it reads the Bullet position and the live EnemyState position
through their typed reference getters, then calls the existing strict-exact
`geometry::rectangle_circle` with the animation dimensions/rotation and the
original **6.0f** radius at `0x0056F00C`.

An intersecting Bullet receives, in native order:

1. `Bullet::set_timer_4d8(counters.field_10)`;
2. animation packed color `0xFFA05000` through the real Bullet animation
   getter and `Animation::set_packed_color`;
3. `Bullet::set_field_18_to_ten()`.

The active-list iterator is destroyed before the callback's separate Player
phase. The callback reads the current Context Player position, re-reads the
EnemyState position and tests the same rotated rectangle with the original
**10.0f** radius at `0x0056E734`. On overlap it resolves global Player zero
and writes `field_20ec` through the real Player setter using
`counters.field_10`.

## Callback 2 — all-active-Bullet reset

`EnemyState::clear_all_bullets_for_enemy_clear()` traverses every active
Bullet without a state or `field_18` filter. It assigns the original 1.0f
global to each Bullet's `timer_4d8`, restores packed animation color to
`0xFFFFFFFF`, and calls `Bullet::clear_field_18()`. After the iterator is
destroyed it resolves global Player zero and sets `field_20ec` to the same
original 1.0f global.

The two native iterator destructors occur before their respective Player
phases. The maintained COFF call-order checks preserve this lifetime boundary
as well as the AnimationHandle, Context, position, geometry, Bullet Timer,
animation, field setter and Player calls.

## Whole-function strict replay

Both callback Bosses now have independent canonical COFF units in
`config/match-units.toml`, built from the same natural C++ translation unit.
The 758-byte rectangle callback strictly replays all 38 original relocation
fields and all 606 ordinary bytes. The 291-byte all-Bullet reset strictly
replays all 21 original relocation fields and all 207 ordinary bytes. Fresh
pinned-compiler replay reports `exact (758/758 bytes)` and
`exact (291/291 bytes)` respectively. The 10-byte rectangle alignment tail
is verified as original `0xCC` data separately, never padded into the source.

The native iterator receiver lifetimes are reflected in ordinary source:
Context's BulletController result flows directly into `active_list()`, and
`iterator.get()` is retained as a typed intrusive-link local before
`node_value()`. The all-Bullet callback also retains global Player zero in an
explicit local before passing the original 1.0f global to its movement-scale
setter; this reproduces the native stack/argument order without assembly.

## Runtime and leaf verification

The ASan/UBSan root host executes both callback indexes through the actual
`EnemyState::execute_opcode` dispatcher. Tests cover rotated geometry,
inside/outside Bullets, deliberately nonmatching Bullet state/field values
(which are still processed), Timer/color/field writes, Player overlap and
non-overlap, the all-Bullet reset path, and an integer-operand exception
before callback selection or any side effect.

The callback's `Bullet::set_timer_4d8` dependency is independently restored
as a **39-byte strict-exact** C++ leaf at `0x0049CAE0`; its complete 35
non-relocation bytes and sole REL32 to `Timer::operator=(float)` are verified
by `scripts/verify-bullet-timer-4d8-source.py`.

The maintained root verifier currently runs **128 focused host source units**
under ASan/UBSan and compiles **62 locked-profile i386 COFF units**. The
41,967-byte `EnemyState::execute_opcode` parent remains **NONEXACT**; opcode
629 is an inline fragment and receives no whole-parent byte credit. No full
cold replay was run.
