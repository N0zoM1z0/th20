# Laser Type0 parameter copy

The native `LaserType0Parameters` copy assignment at `0x004C8FE0` copies the
position vector, scalar/type/color fields, a duplicated `+0x34` flags alias,
the PMR `BulletCommand` vector, and the three trailing words. The native body
is 236 bytes. The reconstructed natural C++ assignment also produces 236
bytes; the vector-assignment relocation resolves to the original
`0x0047C570` implementation. Strict comparison matches 226 of 232 ordinary
bytes. The first duplicated flags store differs by six compiler-scheduled
bytes, so the function remains reconstructed rather than exact.
