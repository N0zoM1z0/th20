# Three native Animation Vector2 interpolation methods: 153 bytes exact

The original TH20 v1.00a Animation VM `0x0042B5D0` calls three different
51-byte Animation methods that delegate to a single `Vector2Interpolation::begin`
head at `0x00439640`, using three actual AnimationBase state members:

| Original method | C++ source role | Interpolation member |
| --- | --- | --- |
| `0x00438DB0` | Secondary scale | `Animation+0x220` |
| `0x00438DF0` | Primary scale | `Animation+0x1E0` |
| `0x00438E30` | Texture/UV scale | `Animation+0x260` |

Each method is 51 bytes/21 i386 instructions with exactly one original E8
at `+0x27 -> 0x00439640` (REL32 field `+0x28`), and no PE HIGHLOW fields.
All 47 nonrelocated bytes match in each independent function, including the
compiler-emitted NOP after the call and `ret 0x10`. All three are implemented
as normal, non-inlined C++ member functions on one borrowed Animation view in
`src/AnimationVector2ConfigLeaves153.cpp`. The state is the real existing
`Vector2Interpolation` member; no duplicated object layout or synthetic bytes.

The pinned MSVC x86 compilation and `replay-exact-units.py --source
src/AnimationVector2ConfigLeaves153.cpp` validate each complete native function,
including its E8 destination. This adds three distinct physical game heads /
153 new original `.text` bytes; the common interpolation callee is not counted
a second time. The 39,470B Animation VM itself remains a separate, open Boss.
