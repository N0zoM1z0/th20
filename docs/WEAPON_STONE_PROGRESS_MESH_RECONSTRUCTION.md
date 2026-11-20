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

The `/Od` local COFF contribution is now 1,675 bytes versus the 1,780-byte
native function. The source uses independently address-anchored original
`.rdata` values for the 120px radius (`0x00570AD0`), alpha maximum
(`0x0056CD9C`), fade thresholds (`0x00573160`, `0x0056FBF8`), wave
amplitude/period (`0x0056E0EC`, `0x0056E048`), PI (`0x0056E0F0`), and viewport
margins (`0x0056CD94`, `0x00576360`). The cull is expressed as short-circuit
comparisons so the per-vertex WindowState getters execute in native order.
The radial Vector3 returned by subtraction is then mutated in place for the
wave displacement and passed to the native `Vector3::operator+=`, avoiding a
second synthetic Vector3 construction. The top cull uses the native integer
`view_y - 32` ordering; the displaced lower clamp uses the original -32.0f
data constant.

The native body also contains an unused second Angle local, assigned from
`Timer * PI / 10`, and an unused stack copy of the 120px radius. Those dead
operations are intentionally not recreated as inert source statements. The
remaining 105-byte difference is visible; this is a semantic reconstruction,
not a byte match. It is not admitted to `match-units.toml`; no full cold replay
is run for this nonexact candidate.

## Targeted validation

- `scripts/compile-probe.sh src/WeaponStoneProgressMesh.cpp ... /Od /Ob0 /GS`
  succeeds and emits i386 COFF.
- `scripts/validate-tracking.py --skip-target-bytes` passes after the
  provisional source mapping is added.
- No canonical replay or original-byte match is claimed.

## Adjacent callback and remaining boundaries

The 20-byte callback wrapper at `0x00532720` and its 32-byte callback-object
method at `0x00532A90` are now independently exact and admitted in
`CORE/EXACT-1203`; see `docs/WEAPON_STONE_PROGRESS_CALLBACK_EXACT.md`. The
37-byte RenderMesh callback setter at `0x0052CD50` is also exact in
`CORE/EXACT-1204`; see `docs/RENDER_MESH_CALLBACK_EXACT.md`. Their exactness
does not transfer to this 1,780-byte updater. The 467-byte progress-effect
initializer at `0x005348D0` now has a natural 466-byte semantic candidate; all
non-relocation bytes align after removing its single native NOP, but it remains
NONEXACT. See `docs/WEAPON_STONE_PROGRESS_EFFECT_INITIALIZER_RECONSTRUCTION.md`.
The separate 581-byte sibling progress routine at `0x00534AB0` remains the next
large boundary. Continue from its actual native callers and owner/vtable
evidence; do not fold it into this method or claim it from its sibling.
