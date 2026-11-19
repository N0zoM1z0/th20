# Animation viewport-placement mode at +0x4A3

The two low bits of `AnimationBase::flags` byte `+0x0b` (absolute
`Animation+0x4A3`) select the viewport-placement path. The source field is now
named `viewport_placement_mode`; it remains a two-bit field in the same byte.

Observed modes and behavior:

- `0`: ordinary/mesh-relative placement. Mesh drawing adds mesh viewport
  offsets when no parent is present; position transformation does not add a
  screen-space origin pair.
- `1`: first viewport placement. `Animation::transform_position` adds the
  WindowState `+0x58/+0x5c` coordinate pair when there is no parent. Mode 6/7
  and related draw paths treat nonzero placement as screen/viewport-relative.
- `2`: second viewport placement. Position transformation instead adds the
  WindowState `+0x60/+0x64` pair; other renderer paths use the same nonzero
  screen-space behavior.

Independent producers corroborate these values: `Animation::set_layer` sets
mode 1 for layers 3–19, mode 2 for layers 20–23, and 0 otherwise;
`AnimationFile::spawn` initializes mode 1 for layers through 23; Bullet and
Player drawing publish mode 1; mesh lifecycle setup explicitly clears it.
Geometry, mode-6/mode-7, mesh, and draw consumers establish a placement role
rather than merely a layer identifier.

The field remains two bits; `AnimationFlags` remains 0x20 bytes and the
adjacent scale-mode byte remains at offset +0x0c. No storage or padding was
added. The generic `layer_mode` spelling was replaced at source level because
all observed consumers use this placement role.

## Exact dependent-unit preservation

The header's typed field name changed the compiler-generated local string
symbol labels in `RenderMeshLifecycle.obj` from `$SG176245..248` to
`$SG176313..316`. The four DIR32 relocation sites, target addresses, literal
contents, and function bytes are unchanged. The canonical relocation manifest
was updated only for those four compiler-local symbol names; focused replay
then passed both units in `RenderMeshLifecycle.cpp` (`878/878` constructor and
`266/266` retirement destructor). The other affected exact sources also
passed their scoped replays.
