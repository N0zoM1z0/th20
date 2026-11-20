# `Laser::~Laser()` and its scalar deleting destructor

The native base destructor at `0x004C8AF0` owns a 108-byte body. The source
`src/LaserBase.cpp` reproduces the complete native cleanup: the compiler
restores the base `Laser` vtable, the destructor checks the owned
`IntrusiveLink<EclRuntime>*` at `+0x6D8`, releases it through the original
`DiagnosticAllocator::release_object<IntrusiveLink<EclRuntime>>` specialization,
and then clears the member. This type is independently established by the
native relocation to `0x00413B70`, the exact release-object template
instantiation, and the EclManager async-runtime link allocation/retirement
paths. It replaces the earlier neutral `void*` field.

The base constructor initializes this pointer to null. The destructor's release
uses the allocator's process lock slot 1 and the original scalar storage family;
it does not call the unrelated C-heap `DiagnosticAllocator::release_bytes`.

## Strict replay receipts

- **Destructor:** 108 function bytes, plus five original `INT3` alignment bytes.
  Canonical replay compares all 113 bytes; all 93 non-relocation bytes and all
  five original relocation destinations match. The release call targets the
  already established 97-byte `release_object<IntrusiveLink<EclRuntime>>`
  specialization at `0x00413B70`.
- **Scalar deleting destructor:** 49/49 bytes match. The compiler-generated
  wrapper calls the complete destructor and conditionally performs sized scalar
  delete using the native `0x6F8` base allocation size. Its origin is compiler,
  not authored gameplay code, so it receives no separate authored-byte credit.

The scalar deleting wrapper is emitted by the virtual destructor declaration;
there is no handwritten machine-code or padding substitute. The complete Laser
base constructor remains a separate natural-C++ NONEXACT reconstruction.
