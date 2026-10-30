# CORE/RECON-919 — original 156B ribbon allocation factory whole strict exact

The target is Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045E5D0` is a **156B/46-i386** C++17 diagnostic
allocation template for the same native **0xB60** polymorphic ribbon
group whose [89B ctor and destructor chain](ANIMATION_RIBBON_GROUP_CTOR_89_STRICT_EXACT.md)
are independently strict exact. The factory has a separate original
47B caller at physical E8 `0x0045EC83`.

## Independent original native roles

[`scripts/verify-animation-ribbon-group-factory156-native.py`](../scripts/verify-animation-ribbon-group-factory156-native.py)
checks the complete original code extent and `ret 8`, four real E8
site/destination pairs, two native PE HIGHLOW sites and the parent call:

| Original field | Actual target | Native role |
| --- | --- | --- |
| E8 `+0x2D` | `0x0054275D` | Allocate `0xB60` bytes with `operator new` |
| E8 `+0x4D` | `0x0040C080` | Native MSVC automatic class zero initialization |
| E8 `+0x56` | `0x0040B280` | C++17 forwarding helper, physically folded original |
| E8 `+0x6A` | `0x0045E6D0` | Whole-exact native 89B group constructor |
| DIR32 `+0x06` | `0x00568957` | Native C++ EH handler |
| DIR32 `+0x15` | `0x005B25C0` | Actual security cookie |

The final four-byte member at group offset `+0xB5C` is genuinely
zeroed by the original constructor. Initial nominal `uint32_t` C++
source generated only a **143B** C++17 factory, omitting the authentic
native `/sdl` class initialization. Representing the member as a
**pointer-bearing resource token** naturally produces the original
156B, including its complete autozero and all original call positions.
This is compiler-ABI-backed evidence for pointer-like storage, but
the resource lifecycle and historical field name remain provisional.
The already whole-exact 89B group constructor, 20B implicit folded
destructor and 49B deleting wrapper are unchanged by this type revision.

## Complete canonical replay and scope

[`src/AnimationRibbonGroupFactory156.cpp`](../src/AnimationRibbonGroupFactory156.cpp)
instantiates the ordinary `DiagnosticAllocator::allocate_object<
NativeRibbonGroup,Animation*>` C++17 template with the same typed group
class in [`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp).
No manually inserted memset, invented vptr or copied native bytes is
present. Pinned x86 MSVC 19.44 C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` generates the entire relocated original:

```text
animation_ribbon_group_factory_156: exact (156/156 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared-header change required only eight previously accepted
ribbon providers; all **10/10 existing strict units** remain exact
after fresh local cold compilation. No unfiltered whole-graph replay
was used. A duplicate manifest draft was retained privately in ignored
`.analysis/gptweb-ribbon-factory156/duplicate-factory-unit.toml` before
consolidation. The separate 47B factory caller is not inferred exact.

This 156B allocation function is `origin=unknown/review`, likely an
instantiated allocator/compiler template; it adds **zero authored-game
code credit** until authorship is independently proven.

```bash
scripts/repo-python scripts/verify-animation-ribbon-group-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupFactory156.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupCtor89.cpp --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonSegmentDraw76.cpp --source src/AnimationRibbonSegmentDynamics538.cpp --source src/AnimationRibbonSegmentCtor60.cpp --source src/AnimationRibbonSegmentArrayCtor78.cpp
```
