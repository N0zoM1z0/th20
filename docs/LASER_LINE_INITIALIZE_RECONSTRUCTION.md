# `LaserLineInf::initialize_laser()` — native type-0 initialization

The native Line initializer at `0x004D4150` spans 1,284 bytes. Its object has
three separately constructed Animation subobjects at `+0x74C`, `+0xD30`, and
`+0x1314`, plus a Type0 parameter block at `+0x6F8`.

The C++ reconstruction copies the Type0 block, selects the context and
style-remapped cancel color, initializes the first Animation callback/script
and its flags, binds the second Animation at `color + 0x3A`, and selects the
third Animation script using the native type boundary (`type < 0x12` or
`type == 0x26` selects `color + 0x5D`; otherwise `color + 0x55`). It then
requests the optional sound, resets the two short timers, copies the base
position and applies the radial offset, initializes angle/width/speed and the
length threshold, builds velocity, copies the command index and handle,
initializes the two trailing scalar lanes, allocates the shared `0x3C`
`LaserRuntimeState`, and sets `field_6DC`.

The current natural C++ body compiles to 1,260 bytes under the locked MSVC x86
`/Od` profile. It is tracked as reconstructed, not exact; the native body is
1,284 bytes and strict byte comparison does not establish a full match. The
Type0 copy assignment is independently reconstructed at 236 bytes with its
PMR vector relocation grounded to `0x0047C570`.
