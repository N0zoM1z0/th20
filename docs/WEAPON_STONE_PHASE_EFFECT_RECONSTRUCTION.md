# `WeaponStoneInfo::initialize_phase_effect()` reconstruction

## Native boundary

The native x86 function at `0x00534AB0` is 581 bytes (`0x00534AB0..0x00534CF4`),
called from the WeaponStone frame/update method at `0x00532B20`. The receiver
is the actual `WeaponStoneInfo*` in ECX: it accesses the owner fields at
`+0x28`, `+0x40`, `+0x44`, and `+0x7c`. It is not a parameterless global.

## Reconstructed behavior

1. Read the player's mode. Mode 7 snapshots `weapon_28->phase_position()`;
   other modes snapshot `player(0)->position_ref()`. Preserve the selected
   pointer in a second local before copying its three floats; the original
   stack layout contains this pointer alias. The snapshot happens before the
   old mesh is retired and before a replacement is allocated.
2. Retire the previous RenderMesh, clear `mesh`, and allocate a new 12x12
   RenderMesh with surface selector zero, this object's view index, and the
   original diagnostic source label `weaponstone.cpp:652 RenderMeshInf`.
3. Reset `timer_44` to zero and install the exact root callback setter. The
   installed callback wrapper and its callback-object method are separately
   exact (`CORE/EXACT-1203`); the RenderMesh callback publication wrapper is
   separately exact (`CORE/EXACT-1204`).
4. Construct `EffectParameters` and a zero Angle, copy the position snapshot
   into `vector_00`, and set `enabled` to `player mode != 7`. Set the first
   ring speed to `PI/20` and packed color to `0xffffc080`.
5. Spawn 24 type-6 effects while increasing the angle by `(PI*2)/24`.
6. Set the second ring speed to `-PI/20` and spawn another 24 type-6 effects
   while decreasing the angle by `(PI*2)/24`.

The `enabled` byte is the actual `EffectParameters+0x28` lane, not an invented
flag. The native function queries the player mode again after copying the
position, and the C++ reconstruction preserves that second query. Both rings
use the actual session-0 `EffectInfo` and the existing type-6 spawn path.

## Exactness status

The natural `/Od /Ob0 /GS /sdl` i386 COFF function contribution is 580 bytes;
the native body is 581 bytes. After the callback publication call, the native
compiler emits a one-byte NOP at `0x00534B81`; the natural candidate proceeds
directly to the next local construction. The candidate is tracked as
`reconstructed`, not `matching`. No assembly, inert statement, NOP, padding,
byte credit, or original-origin claim is added to close the difference. The
source is compiled as i386 COFF and the function remains outside
`match-units.toml`.

## Adjacent open work

The caller at `0x00532B20` is a separate 1,018-byte WeaponStone frame/update
function, now represented by a natural but nonexact reconstruction in
`src/WeaponStoneUpdateMain.cpp`. Its phase-state, timing, cancellation, and
four-weapon virtual-dispatch behavior are tracked independently; this
initializer claims none of the caller's bytes.
