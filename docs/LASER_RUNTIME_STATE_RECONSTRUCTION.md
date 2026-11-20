# Laser-owned 0x3C runtime state — constructor and allocation boundary

Both native `LaserLineInf` and `LaserInfiniteInf` initializers call the same
allocator factory at `0x004C7FD0` and store its result at `Laser+0x6D8`. The
factory requests exactly `0x3C` bytes, calls the shared 31-byte
`__autoclassinit2` preclear helper at `0x0040C080`, then calls the constructor
at `0x004C8240`. The owning Laser base destructor releases this allocation.

The maintained `LaserRuntimeState` layout is grounded by the constructor's
three subobject calls and its scalar stores:

| Offset | Native value owner |
|---|---|
| `+0x00` | `Vector3` |
| `+0x0C` | `Vector3` |
| `+0x18` | `Vector2` |
| `+0x20..+0x2C` | four zeroed float lanes |
| `+0x30..+0x38` | three zeroed 32-bit words |

The natural C++ constructor produces the full 118-byte body and reaches all
three original vector constructors. Its first 96 of 106 ordinary bytes match;
the final `+0x38` store uses a different compiler register schedule. The
current allocator template instantiation is ordinary
`DiagnosticAllocator::allocate_object<LaserRuntimeState>` and produces 55
bytes. It omits the native pre-constructor zero-span helper call, so the native
67-byte factory remains nonexact. Neither boundary is credited as exact.

`LaserRuntimeState` is trivially destructible.
`DiagnosticAllocator::release_object` skips the no-op destructor for trivial
types while retaining normal destruction for nontrivial owners. The updated
`Laser::~Laser()` still strictly replays all 108 function bytes and five
original alignment bytes, with the runtime-state release specialization
relocated to the original `0x00413B70` body.
