# `LaserInfiniteInf::cancel_circle()` — exact native Infinite cancellation

The Infinite vtable at `0x005712E8` dispatches circle cancellation through
slot `+0x30` to the 1,123-byte native method at `0x004CABF0`. The original
type-1 `create_laser` diagnostic identifies the concrete class as
`LaserInfiniteInf`; the native factory allocates `0x1338` bytes. The natural
C++ implementation is in `src/LaserInfiniteCancelCircle.cpp`.

## Recovered behavior and layout

The method preserves the native early guard on the fourth argument and
`Laser::field_6CC`, initializes a 512-byte segment mask, constructs its two
real `Vector3` locals and base-position snapshot, and samples along the base
angle. It starts at an 8-unit half-step and advances by 16 units while the
next half-step remains within `field_74`. Each sample uses the XY squared
distance against the squared radius. A hit increments the owning
BulletController cancellation counter, then applies the native 32px screen
boundary test before spawning effects. The signed `field_6E4` value selects
one of three native script families, using the `LaserType1Parameters::color`
value. After the loop it publishes the mask through the native virtual slot
`+0x38` and returns the hit count.

## Strict native replay

The natural C++ forward miss goto makes the locked MSVC x86 `/Od` compiler emit
the native `JBE` hit edge and both `JMP` edges, preserving unordered `COMISS`
semantics without inline assembly or synthetic instructions. The complete
**1,123/1,123 bytes** now strictly replay, with **991/991 ordinary bytes** and
**33/33 original relocation destinations** matching. The relocations cover
the security cookie, both `Vector3` constructors and operators, screen-size
constants, `_memset`, polar sampling, squared-distance testing, BulletController
accessors, screen-boundary culling, all three `bullet` literal/effect spawn
paths, and the security-cookie check. No NOPs, assembly, or padding are added.
