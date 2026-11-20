# `LaserController::cancel_near()` reconstruction

The native method at `0x004CAAD0` is a 288-byte thiscall controller operation.
Its receiver is the actual `LaserController` (`active` intrusive list at
`+0x10`, cancellation center at `+0x30`). It copies the supplied center into
`cancel_position`, then walks the live list using the native iterator lifetime.

Each list element is an actual polymorphic `Laser`. State 1 is excluded; every
other state dispatches the real virtual slot `+0x30`,
`Laser::cancel_circle(center, radius, mode, argument)`. The method sums the
returned cancellation counts and returns the aggregate. This is the exact
path used by WeaponStone's 24/128-radius phase cancellation.

The natural `/Od /Ob0 /GS /sdl` i386 COFF contribution is 281 bytes versus the
288-byte native body. It is tracked as `reconstructed`, not `matching`. No
assembly, synthetic padding, no-op statements, or original-origin claim is
used to close the seven-byte difference.
