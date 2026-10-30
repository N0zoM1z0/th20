# CORE/RECON-919 — complete 156B ribbon-group allocation factory strictly exact

Target: the immutable Japanese TH20 1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045E5D0` is **156B/46-i386** and directly invokes the
independently strict-exact **89B polymorphic group constructor** at
`0x0045E6D0`. The genuine `std::array<NativeRibbonSegment,3>`/Timer
hierarchy and original vtable remain shared with the already accepted
140B update, 156B draw, 538B dynamics, 76B line wrapper and constructors.
This factory is whole native exact but its original **authored versus
C++ compiler-template ownership remains unproven** and is not counted as
a new authored game `.text` function.

## Full original PE physical audit

[`scripts/verify-animation-ribbon-group-factory156-native.py`](../scripts/verify-animation-ribbon-group-factory156-native.py)
reads the locked original PE `.text` and actual PE `.reloc`, checking every
instruction through the original `ret 8`, all **four original E8** call
instructions and both original in-body HIGHLOW fields:

| Physical field | Destination | Verified original role |
| --- | --- | --- |
| DIR32 `+0x06` | `0x00568957` | Original EH handler pointer |
| DIR32 `+0x15` | `0x005B25C0` | Original security-cookie global |
| E8 `+0x2D` | `0x0054275D` | True scalar allocation |
| E8 `+0x4D` | `0x0040C080` | Genuine compiler `__autoclassinit2` folded helper |
| E8 `+0x56` | `0x0040B280` | Native folded `std::forward<Animation*>` helper |
| E8 `+0x6A` | `0x0045E6D0` | Real complete 89B ribbon-group constructor |

Two separate original native instructions push **0xB60** (allocation and
class auto-initialization). Original allocation-failure/control flow,
EH/cookie prologue and return path are all preserved; neither a truncated
prefix nor an in-memory structural alignment is credited as exact.

## Actual class type and natural C++17 compiler lowering

Initial source with `NativeRibbonGroup::zero_initialized_b5c` represented
as `uint32_t` generated a **143B candidate**, omitting original
`__autoclassinit2`; it was **rejected** even though the separate 89B group
constructor was exact. The original 89B constructor separately authenticates
a genuine zeroed four-byte member at `+0xB5C`, while the class size and
virtual table are original PE-attested. Representing that member as
`void* resource_token_b5c` makes pinned MSVC x86 `/sdl` naturally emit
its real **0xB60-byte** class auto-initialization and restores the
complete **156B/46-instruction** original, without modifying the 89B
constructor code or any accepted children. This is a compiler-corroborated
**pointer-semantic hypothesis**, not independent evidence of the unique
historical original C++ field name or lifetime.

The single maintained [`factory source`](../src/AnimationRibbonGroupFactory156.cpp)
uses ordinary C++17 `DiagnosticAllocator::allocate_object<NativeRibbonGroup,
Animation*>`, the same real typed class as the
[`group constructor`](../src/AnimationRibbonGroupCtor89.cpp). No hand-written
vptr assignment, byte array, fake no-op, target patch, assembly or
compiler-conditional duplicate implementation is introduced.

Pinned MSVC 19.44 x86 C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and full canonical relocation-aware replay:

```text
animation_ribbon_group_factory_156: exact (156/156 bytes)
Exact replay: 11/11 units, 9 cold objects
```

The nine explicitly selected compiler providers are **only the new factory
and the actual eight-source header/include closure**. All accepted
19B/140B/156B/76B/538B/60B/78B/89B/20B/49B dependent contributions
remain strict exact; **no whole-graph cold replay** ran. The new template
factory remains `origin=unknown/review` and contributes **zero authored
game function or `.text` bytes**. Original 5,993B Animation Draw and the
remaining source-absent large opcode interpreters are independent open work;
no complete executable is linked or playable yet.

```bash
scripts/repo-python scripts/verify-animation-ribbon-group-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupFactory156.cpp --source src/AnimationRibbonGroupCtor89.cpp --source src/AnimationRibbonSegmentArrayCtor78.cpp --source src/AnimationRibbonSegmentCtor60.cpp --source src/AnimationRibbonSegmentDynamics538.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonSegmentDraw76.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
