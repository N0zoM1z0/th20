# Two Animation color interpolation methods: 274 original bytes exact

The locked Japanese TH20 Steamless v1.00a target contains two distinct game
Animation methods called from the still-open 39,470-byte Animation VM:

| Original | Real behavior | Native calls/data |
| --- | --- | --- |
| `0x00438BD0` (132B) | Convert two byte endpoint values to signed integer interpolation inputs at `Animation+0x2F4`; set nonzero color mode | One 86B integer interpolation begin, one cookie check, cookie data |
| `0x00438CC0` (142B) | Construct two `IntegerTriple` values from separate `Color3` inputs; interpolate at `Animation+0x2A0`; set nonzero color mode | Two `IntegerTriple(Color3)` calls, one triple interpolation begin, cookie check, cookie data |

Both methods use the actual `AnimationBase` interpolation members and existing
`AnimationFlags::color_mode` three-bit field at `Animation+0x4A1`. The
native check activates that mode only when its current value is zero;
setting the mode unconditionally would change the game. Both algorithms are
normal C++20 in `src/AnimationColorConfig274.cpp`, borrowing an existing
Animation without allocating or constructing a duplicate runtime owner.

Under pinned x86 MSVC `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` the whole 132B and 142B bodies match the original through the native
returns and security cookie verification. The 132B method has all **120/120
ordinary bytes** and three exact relocation fields; the 142B method has all
**122/122 ordinary bytes** and five exact fields, including the two original
Color3-to-triple constructors. They have independent physical original heads:
SHA-256 `4ae1afd405670ec7f64ecece8faa0efee394d7efca63729a7f374672b962ba72`
and `9b21e541fa2a49fabb113df8414da35476b8d8d8f55ac6046229f23f5b7789d1`.

A focused `replay-exact-units.py --source src/AnimationColorConfig274.cpp`
performs the strict whole-object comparison, including original relocation
destinations. The two original methods add 274 disjoint game `.text` bytes;
their already exact interpolation and constructor callees are not counted a
second time. The 39,470B Animation VM caller remains a separate large Boss.
