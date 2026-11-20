# Shared Laser virtual and context helpers — exact native boundaries

The four concrete Laser vtables share the original implementations at
`0x004D7D50` (slot `+0x00`) and `0x004D67E0` (slot `+0x04`). The first copies
the three position lanes into `Laser+0x58`. The second builds a polar offset
from the Laser angle at `+0x70` and the requested distance, then adds the
base position. Both are natural C++ implementations in `src/LaserBase.cpp`.

The nonvirtual `Laser::select_context` helper at `0x004D7DD0` stores the signed
view index at `+0x6EC` and resolves the matching 0x30-byte Context through the
original `Session::context` accessor, storing the pointer at `+0x6F0`.

## Strict replay receipts

- `Laser::set_position`: 38/38 bytes, no relocations.
- `Laser::point_at_distance`: 66/66 bytes, both original `polar` and
  `Vector3::operator+=` destinations match.
- `Laser::select_context`: 54/54 bytes, both original Session global and
  `Session::context` destinations match.

All three functions use the pinned MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` profile.
