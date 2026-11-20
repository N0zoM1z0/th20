# `WeaponStoneInfo::update_progress_mesh()` reconstruction

## Current result

`src/WeaponStoneProgressMesh.cpp` now contains a natural C++ reconstruction of
the large progress-mesh update routine at `0x00533970`. It is indexed as
`th20::WeaponStoneInfo::update_progress_mesh` and remains `reconstructed`, not
`matching`. No original-byte, canonical-replay, or authored-origin credit is
claimed.

The native function spans 1,780 bytes (`0x00533970..0x00534063`) and has 22
distinct direct callees. The callback chain is `0x00532720` -> `0x00532A90` ->
`0x00533970`; the last function updates the `RenderMesh*` at WeaponStoneInfo
`+0x40` and Timer at `+0x44`.

## Reconstructed behavior

1. Return when the mesh pointer is null. At Timer frame 80 or later, destroy the
   owned `RenderMesh`, clear the pointer, and return without another tick.
2. Select the geometry anchor from the real PlayerRecord mode field: mode 7
   uses `Weapon::phase_position()` through the `Weapon*` at `+0x28`; other
   modes use `Player::position_ref()`.
3. Reinitialize the 12x12 grid at `(anchor.x - 120, anchor.y - 120)` with a
   240x240 extent. Add the selected view's X/Y offsets to the center used by
   the vertex calculations.
4. For each base position and corresponding 28-byte
   `SpriteTexturedVertex`, compute the XY distance from the anchor. The
   viewport cull rectangle is `[view_x - 208, view_x + 208]` by
   `[view_y - 32, view_y + 480]`. Vertices outside it have alpha cleared.
5. Vertices farther than radius 120 also have alpha cleared. Otherwise set
   diffuse color to opaque white. Alpha stays 255 through normalized radius
   0.8, then falls linearly to zero at radius 1.0. After frame 60, multiply
   alpha by `(80 - frame) / 20` using integer arithmetic.
6. Apply a radial sine displacement. Its phase is
   `2*pi*normalized_distance - frame*pi/120`; displacement magnitude is
   `sin(phase) * normalized_distance * 0.5`. Clamp the displaced vertex to
   the same viewport bounds and zero both vertex Z and base-position Z.
7. Publish the changed columns through `RenderMesh::update_strips()` and tick
   the Timer once.

The diffuse word at vertex `+0x10` is set to `0xffffffff`; the alpha byte is
its high byte at `+0x13`. This is the observed native vertex layout, not an
untyped color/UV alias. The distance helper is the existing XY-only
`bullet_velocity_magnitude`, and the selected mode-7 anchor is the actual
virtual `Weapon::phase_position` slot at vtable offset `+0x60`.

## Native boundary details

The native lifetime predicate is `Timer::at_least(0x50)` (80), the fade
predicate is `Timer::greater_than(0x3c)` (strictly greater than 60), and the
final call is the real Timer increment wrapper. The native body also constructs
and assigns a second Angle local to `frame*pi/10` but never reads it again;
that dead local is intentionally not reproduced as inert source code.

The `/Od` local COFF contribution is 1,223 bytes versus the 1,780-byte native
function. This is a semantic reconstruction, not a byte match. It is not
admitted to `match-units.toml`; no full cold replay is run for this nonexact
candidate.

## Targeted validation

- `scripts/compile-probe.sh src/WeaponStoneProgressMesh.cpp ... /Od /Ob0 /GS`
  succeeds and emits i386 COFF.
- `scripts/validate-tracking.py --skip-target-bytes` passes after the
  provisional source mapping is added.
- No canonical replay or original-byte match is claimed.

## Adjacent callback and remaining boundaries

The 20-byte callback wrapper at `0x00532720` and its 32-byte callback-object
method at `0x00532A90` are now independently exact and admitted in
`CORE/EXACT-1203`; see `docs/WEAPON_STONE_PROGRESS_CALLBACK_EXACT.md`. Their
exactness does not transfer to this 1,780-byte updater. The 467-byte
progress-effect initializer at `0x005348D0` and the separate 581-byte sibling
progress routine at `0x00534AB0` remain open boundaries. Continue from their
actual native callers and owner/vtable evidence; do not fold them into this
method or claim them from its implementation.
