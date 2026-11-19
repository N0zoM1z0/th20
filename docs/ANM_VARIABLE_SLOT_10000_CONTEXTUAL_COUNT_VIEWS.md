# ANM variable slot 10000 — contextual count views

`AnmVariables` is the 64-byte per-animation script variable bank at
`AnimationBase+0x444`. Slot 10000 remains one signed 32-bit storage word at
offset `0x00`; it is not a new fixed field of every Animation.

The native consumers establish several path-specific count roles:

- `Animation::update_geometry` reads the word as a vertex count in the
  polygon/strip geometry paths. Those paths iterate through `count - 1`
  segments and write the terminal vertices separately.
- `AnimationPoolOwner::draw` passes the word to native shape renderers as
  their count argument. The native `0x0043C780` renderer uses its integer
  parameter as the loop bound and emits the associated vertex records;
  `0x0043AB20` likewise uses its integer parameter to size the shape loop.
- `NativeParticleGridGroup::update` uses the word to bound particle-grid
  generation and passes it into the child creation paths.

The source now exposes these as `geometry_vertex_count`, `draw_shape_count`,
and `particle_grid_count` union views. The original `field_00` name remains
available for generic script-operand access (`Animation::integer_argument`,
`integer_value`, and `float_value`), where the slot has no single global
meaning. All aliases share offset zero; `sizeof(AnmVariables)` remains 64 and
no bytes, padding, initialization, or runtime state were added.

This is semantic naming progress only. It does not claim new native-byte
exactness for the three large consumers.
