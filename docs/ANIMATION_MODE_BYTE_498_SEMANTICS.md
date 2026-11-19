# Animation mode and secondary flag bytes at +0x498

`AnimationBase::flags` begins at `Animation+0x498`. Its first 16-bit view
contains two distinct bytes:

- `bytes_00.animation_mode` (`Animation+0x498`): selects the Animation mode
  consumed by the complete Draw Boss and `Animation::update_geometry`
  dispatchers. Observed values include geometry modes 9, 13, 14, 24, 25, 47,
  and 48, renderer modes 0–48, and mesh mode 12.
- `bytes_00.flag_byte_01` (`Animation+0x499`): a separate secondary byte
  written by `Animation::set_flag_byte_01`, initialized by render-mesh strip
  setup, and compared/published by the quad texture-state cache. It is not a
  second mode identifier.

The typed `AnimationFlagBytes` remains exactly two bytes, preserving the
original 16-bit `AnimationFlags::field_00` overlay and all following offsets.
The source now names the low byte by its dispatch role and the high byte by
its independent flag/cache role; no storage or padding was added.

## Exact dependent-unit preservation

The renamed `AnimationFlagBytes` members changed the four compiler-generated
local literal labels in `RenderMeshLifecycle.obj` to `$SG176316..319`.
Their DIR32 relocation offsets and targets (`0x0057002c`, `0x00570068`,
`0x005700a8`, `0x005700ec`) and the literal contents are unchanged. The
canonical relocation manifest was refreshed only for these local symbol
names; the focused `RenderMeshLifecycle.cpp` replay passed both exact units.
