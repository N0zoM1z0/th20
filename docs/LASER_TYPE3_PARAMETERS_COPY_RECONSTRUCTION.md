# Type3 Laser parameter copy assignment — natural C++ reconstruction

The 216-byte native copy helper at `0x004C8C90` copies the two `Vector3`
values, scalar parameter lanes, the real PMR `BulletCommand` vector, and the
view index. The source models the observed `+0x38` flag word through two
neutral union aliases and copies both aliases, preserving the native duplicate
store instead of deleting it as redundant.

The natural MSVC x86 candidate is also 216 bytes. It resolves the original
`std::pmr::vector<BulletCommand>::operator=` target at `0x0047C570`, and 206
of 212 non-relocation bytes match. The first of the two native writes to
`+0x38` uses a different register schedule, accounting for six byte
differences. This helper remains reconstructed, not exact; no assembly,
manual bytes or padding are used.
