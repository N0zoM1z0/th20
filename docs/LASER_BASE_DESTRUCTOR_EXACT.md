# `Laser::~Laser()` — exact native base retirement

The complete 108-byte native base destructor at `0x004C8AF0` restores the
base Laser vtable, checks the owned pointer at `+0x6D8`, releases its storage
through the process allocator, and clears the pointer. The pointer is now
modeled as `LaserRuntimeState*`, not the earlier speculative
`IntrusiveLink<EclRuntime>*`.

The native type is independently bounded by the shared allocator factory at
`0x004C7FD0`: it allocates exactly `0x3C` bytes, clears the block, and calls
the constructor at `0x004C8240`. The constructor establishes two `Vector3`
subobjects, one `Vector2`, four float lanes, and three 32-bit words. The
state's destructor is trivial, so `DiagnosticAllocator::release_object`
correctly skips `destroy_at` for this type and retains the original allocator
release call.

## Strict replay

The destructor remains **108/108 exact**, with all five native relocations
matching, including the allocator specialization for `LaserRuntimeState`.
The scalar-deleting destructor remains a separate 49-byte exact boundary.
