# CORE/RECON-932 — whole original 156B solo-ribbon C++17 factory strict exact

Locked Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045D2C0` is a **156B/46-i386** solo ribbon diagnostic
allocation factory for the independently exact 89B polymorphic group
constructor and its real **0x3E0-byte** object. It is physically called
by the still-independent 47B wrapper at `0x0045DC83`.

## Independent immutable-original PE role proof

[`scripts/verify-animation-ribbon-solo-factory156-native.py`](../scripts/verify-animation-ribbon-solo-factory156-native.py)
verifies the whole native body, `ret 8`, two original `push 0x3E0`,
**four complete original E8 instruction destinations**, **two original
PE HIGHLOW locations/targets**, and the actual native 47B parent E8:

| Physical original field | Destination | Role |
| --- | --- | --- |
| E8 `+0x2D` | `0x0054275D` | Real C++ scalar `operator new(0x3E0)` |
| E8 `+0x4D` | `0x0040C080` | Native class auto-initialize `0x3E0` bytes |
| E8 `+0x56` | `0x0040B280` | Real C++17 forwarding helper (original folded head) |
| E8 `+0x6A` | `0x0045D5B0` | Whole-exact native solo ribbon group 89B constructor |
| DIR32 `+0x06` | `0x005688D7` | Native exception handler |
| DIR32 `+0x15` | `0x005B25C0` | Original stack cookie |

The C++ type has one genuine 0x3C0 segment at `+8`, an original float
at `+0x3C8`, Timer at `+0x3CC`, and the original four-byte
pointer-like resource token at `+0x3DC`. Initial `struct` spelling of
the otherwise layout-identical polymorphic source built only **143B**,
omitting the original MSVC `/sdl` auto-clear. Declaring the same
polymorphic group as `class ... : public AnimationCallback` and keeping
identical public fields naturally generates **156B/46 i386**, including
the real `__autoclassinit2` call, without manual memset, hidden no-op,
artificial vptr, target byte patch, or a second constructed object.
This is direct evidence of the compiler's classification/ABI lowering,
not independent proof of the historical source's exact keyword spelling.

[`src/AnimationRibbonSoloGroupFactory156.cpp`](../src/AnimationRibbonSoloGroupFactory156.cpp)
instantiates the existing ordinary C++17 `DiagnosticAllocator::allocate_object`
template for the one shared native class. Pinned MSVC 19.44 x86 C++17
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` and the
relocation-aware native oracle verify:

```text
animation_ribbon_solo_group_factory_156: exact (156/156 bytes)
Exact replay: 1/1 new unit, 1 cold object
Affected solo closure: 9/9 strict units, 8 cold objects
```

These local replays include the exact 89B ctor, 49B deleting wrapper,
78B array ctor, 140B update, 156B draw, 697B dynamics, 76B fan and
19B array end. None regressed, and no unfiltered whole-graph replay ran.
The 156B body is likely instantiated compiler/allocator code with
`origin=unknown/review`, **zero authored-game byte credit**. The separate
47B registration wrapper and 182B solo configuration remain open.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloGroupFactory156.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
