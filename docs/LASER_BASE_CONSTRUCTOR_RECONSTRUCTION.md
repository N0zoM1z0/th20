# `Laser::Laser()` — native common-prefix construction

The base constructor at `0x004C85B0` owns the complete 522-byte native body.
It initializes the common `Laser` object prefix of exactly `0x6F8` bytes. The
natural C++ implementation is `src/LaserBase.cpp`; the object remains abstract
and concrete family constructors install their own vtable immediately after
this base constructor returns.

## Recovered object boundaries

- The vptr is at `+0x00`; the native base vtable is `0x005710BC`.
- The intrusive list link starts at `+0x08`.
- The three base timers start at `+0x28`, `+0x38`, and `+0x48`.
- Position and velocity are real three-float `Vector3` subobjects at `+0x58`
  and `+0x64`.
- The scalar motion lanes span `+0x70` through `+0x80`; handle words occupy
  `+0x84`, `+0x88`, and `+0x8C`.
- Twenty-four real `ExtendedCommand` objects occupy `+0x90..+0x68F`, each with
  a `0x40` stride. `command_index` is at `+0x690`, the 64-bit active-command
  mask at `+0x698`, and the trailing timers at `+0x6AC` and `+0x6BC`.
- The controller/context tail begins at `+0x6CC`; the owned
  `IntrusiveLink<EclRuntime>*` is at `+0x6D8`, followed by two neutral words.
  The signed family/type discriminator is at `+0x6E4`, the sentinel word at
  `+0x6E8`, and `Context*` at `+0x6F0`. The last word at `+0x6F4` is also
  covered by the final clear.

The native body first installs its temporary base vtable, constructs the link,
timers, vectors and 24 command records, and writes the observed scalar
initializers. It then calls `memset(this, 0, 0x6F8)` and finally performs the
integer `Timer::operator=(0)` on the age timer at `+0x28`. Thus the pre-clear
`+0x6E8 = -1` write is intentionally overwritten; the final object state has
that word zero. The otherwise-uninitialized `+0x04` and `+0x6F4` words are
also zeroed by the full-prefix clear. This ordering is retained in C++ rather
than replacing the object with opaque padding or a fabricated initializer.

## Targeted validation — deliberately NONEXACT

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
probe compiles `src/LaserBase.cpp` independently. Its natural COFF body is
514 bytes versus the 522-byte native body. The remaining code-generation
difference is not credited as a match: the original uses its own EH/security
prologue and a separate 24-element constructor wrapper, while the current
compiler emits its native array-construction helper. No assembly, dead jumps,
NOPs or padding are added to imitate those eight bytes.

The 32-bit compile statically verifies the complete `Laser` size and all
recovered member offsets. Targeted probes also compile `LaserParameters.cpp`,
`LaserFactory.cpp`, `LaserRegistration.cpp`, and the Line, Beam and Infinite
circle-cancellation implementations against the new base constructor. The
Type0 parameter constructor is now explicitly `noexcept`, preserving its
native no-extra-EH call boundary in the concrete Line constructor. The
independent Beam and Infinite structural audits remain green, and the separate
Curve path-state constructor remains a strict exact replay. This constructor is
tracked as `reconstructed`, not `matching`; the class name and game-authored
object lifecycle are supported by the family vtables/factories and native
member construction, while original source spelling remains inferred.
