# `WeaponStoneInfo::initialize_progress_effect()` reconstruction

## Current result

`src/WeaponStoneProgressEffect.cpp` reconstructs the native initializer at
`0x005348D0` as natural C++. The native body is 467 bytes through RET at
`0x00534AA2`; the local `/Od /Ob0 /GS /sdl` candidate contributes 466 bytes.
It is therefore tracked as `reconstructed`, not `matching`, and no original
byte or authored-origin credit is claimed.

## Behavior

- Release the existing `RenderMesh` through the real process allocator and
  clear the owning pointer.
- Allocate a new 12x12 RenderMesh with the original diagnostic label, surface
  selector zero, and WeaponStoneInfo view index.
- Reset `timer_44` to zero.
- Install the root-animation entry callback through the exact
  `RenderMesh::set_update_callback` wrapper at `0x0052CD50`. The installed
  20-byte entry wrapper at `0x00532720` and its 32-byte callback-object method
  at `0x00532A90` are separately exact in `CORE/EXACT-1203`.
- Construct `EffectParameters` and a zero Angle, copy the current player's
  position into `vector_00`, set the first ring's scalar to `PI/20`, and set
  color to `0xffffc080`.
- Spawn 24 type-5 particle effects while increasing Angle by `(PI*2)/24`.
- Set the second ring's scalar to `-PI/20` and spawn another 24 type-5
  particle effects while decreasing Angle by `(PI*2)/24`.

The 48 particle requests are independent of the RenderMesh vertex update.
The 12x12 mesh geometry is initialized by the separately reconstructed
`WeaponStoneInfo::update_progress_mesh()` routine on the animation callback.

## One-byte native boundary difference

The native code contains a single `NOP` at `0x00534945`, immediately after the
callback publication call. Removing that one byte from the native body makes
its 466-byte sequence align with the candidate: all 334 non-relocation bytes
match, and the candidate has 33 relocation fields. The source intentionally
does not add an empty statement, inline assembly, or padding to manufacture
that byte. The candidate remains NONEXACT until the native instruction can be
explained by a genuine source-level construct.

## Targeted validation

- The source compiles to i386 COFF with the original x86 MSVC `/Od` and `/GS`
  profile.
- The callback setter and callback chain it installs have separate strict
  exact replays; this initializer itself is not admitted to
  `match-units.toml` and is not cold-replayed.
- `scripts/validate-tracking.py --skip-target-bytes` validates the provisional
  function/source mapping.
