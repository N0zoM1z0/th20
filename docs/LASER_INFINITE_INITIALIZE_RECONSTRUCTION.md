# `LaserInfiniteInf::initialize_laser()` — native type-1 initialization

The native type-1 initializer at `0x004D3D70` spans 986 bytes and initializes
the `0x1338`-byte `LaserInfiniteInf` object. The source is maintained in
`src/LaserInfiniteInitialize.cpp`. Its parameter block is the native
`LaserType1Parameters` value at `+0x6F8`; the two Animation subobjects begin
at `+0x770` and `+0xD54`.

The recovered sequence copies the parameter block, sets Laser state and
family/color selectors, binds the view's `LaserController` context, selects
the default or style-remapped cancel color, configures the first Animation's
script callback and user-data owner, loads its script, interrupts and updates
it, and publishes its native flag words. It then binds the second Animation
using `color + 0x3A`, interrupts/updates it, and publishes its flags.

The remaining initialization queues the optional sound effect, copies the
base position and applies the radial offset, installs length/speed/growth and
angle, computes the length threshold, builds the velocity vector, copies the
handle and command index, resets the native timer at `+0x38`, clears
`field_76C`, allocates the shared `LaserRuntimeState`, sets `field_6DC`, and
preserves the `type == 0x26` transition in the Laser `state` word. The two
`+0x6AC`/`+0x6BC` timer assignments belong to the Line initializer, not this
Infinite path.

The current natural C++ body compiles to 1,086 bytes under the locked MSVC x86
`/Od` profile, versus 986 native bytes. It is tracked as reconstructed, not
exact. The 105-byte script callback and the 17-byte BulletStyle accessor
used by this initializer are independent exact native boundaries.
