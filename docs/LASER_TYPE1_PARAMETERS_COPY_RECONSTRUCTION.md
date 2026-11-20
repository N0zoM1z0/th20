# Type-1 Laser parameter copy assignment — natural C++ reconstruction

The 324-byte native assignment helper at `0x004C8E90` copies the complete
`LaserType1Parameters` value, including both Vector3 values, the scalar lanes,
the PMR `BulletCommand` vector at `+0x60`, and the view index at `+0x70`. The
source preserves the native duplicate store to the aliased flag word at
`+0x5C` through two union member names.

The current candidate is also 324 bytes. Its PMR vector assignment relocation
resolves to the original `0x0047C570` destination, and 314/320 ordinary bytes
match. The first duplicate flag store uses a different six-byte register
schedule; the second store and the remaining function body match. This helper
remains reconstructed, not exact.
