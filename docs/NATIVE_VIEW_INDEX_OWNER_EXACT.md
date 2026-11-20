# Opaque native view-index owner — exact setter boundary

The helper at `0x004776A0` is a 25-byte thiscall setter used by 16 native callers, including the 4,757-byte ItemInf update. It writes the supplied view index to the owner at `+0x6C4` and has no relocations.

`src/NativeViewIndexOwner.hpp` models only the known field at `+0x6C4`; all preceding storage remains explicitly unknown. The original global pointer slot is `0x005C0028`. The C++ setter replays **25/25 bytes** exactly. No class name or semantics are asserted for the unobserved fields.
