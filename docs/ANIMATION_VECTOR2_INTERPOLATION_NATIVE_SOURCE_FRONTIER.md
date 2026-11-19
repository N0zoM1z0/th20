# Vector2 interpolation template instance: five whole-native exact methods

The original Animation interpolation subsystem contains a complete `Interpolation<Vector2>`
instantiation in the locked Japanese TH20 Steamless v1.00a target. The existing
natural C++ implementation is the explicit template instantiation in
`src/Interpolation.cpp`; no duplicate class, hand-written bytes or alternate
implementation is introduced.

| Native head | Source method | Bytes | Original role |
| --- | --- | ---: | --- |
| `0x00438E90` | `set_duration` | 22 | Stores duration at `Interpolation<Vector2>+0x38` |
| `0x00439510` | `set_mode` | 25 | Stores mode at `+0x3C` and returns it |
| `0x00439420` | `set_start` | 29 | Copies the two-float start value to `+0x00` |
| `0x00438AC0` | `set_end` | 30 | Copies the two-float end value to `+0x08` |
| `0x00439640` | `begin` | 92 | Calls the four setters, copies start to current `+0x20`, resets Timer `+0x28` |

The complete original extents are 198 bytes / 81 i386 instructions. All four
setter bodies have zero relocations and strict ordinary-byte identity. The
92-byte `begin` has five genuine E8 calls at `+0x0E,+0x1A,+0x26,+0x32,+0x50`,
whose targets are the four setters above and the already exact `Timer::operator=(int)`
at `0x00423520`. The candidate COFF object has all five REL32 fields at the
same offsets with the same destinations; all 72 non-relocated bytes match.
No PE HIGHLOW fields are present in any of the five original bodies.

The focused `scripts/verify-animation-vector2-interpolation-native.py` attests
the immutable whole-function SHA-256 values, complete decoded boundaries,
return stack cleanup, physical E8 destinations and absence of PE HIGHLOW fields.
`replay-exact-units.py --source src/Interpolation.cpp` rebuilds the one existing
translation unit and checks these five new unit boundaries together with the
previously admitted Interpolation descendants.

**Exact codegen is established; authorship is not.** The original uses the
same natural template specialization and real Animation VM/group callers, but
the generic `Interpolation<T>` bodies may be authored game templates or
compiler/library instantiations. The five functions are therefore source-mapped
and strict whole-native units but deliberately have no `matches.csv` authored
credit until origin review is resolved. The larger Animation VM remains open.
