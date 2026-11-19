# ANM variable slot 10010 — particle-grid angle offset

`AnmVariables` is the per-animation script variable bank. Slot 10010 is the
32-bit float at offset `+0x28`; it remains generic storage for other ANM
consumers, so the original `field_28` name is retained.

In `NativeParticleGridGroup::update`, the value is added directly to the
owner's `rotation_z_value()` to form the second polar heading before the
150-unit tangent is generated. This establishes the contextual name
`particle_grid_angle_offset` for this particle-grid path. The name is not a
claim that every use of ANM variable 10010 has the same role.

The alias shares the original float storage at `+0x28`. Static assertions pin
both names to that offset; no storage, initialization, or padding changed.
