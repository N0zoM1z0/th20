# CORE/RECON-931 — original 89B solo ribbon group ctor /49B scalar deletion strict exact

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native single-segment ribbon group is a true **0x3E0-byte**
polymorphic AnimationCallback-derived object with original six-slot
vtable `0x0056ECA4`. Both its complete **89B/25-i386** authored
constructor (`0x0045D5B0`) and **49B/18-i386** compiler-generated
scalar-deleting wrapper (`0x0045D6B0`) now pass full original-target
strict canonical matching. The preexisting original physical 20B
ordinary destructor at `0x0045C2A0` is a shared/folded body and was
already separately accepted. It is not double-counted.

## Independently original PE-verified ABI and call graph

[`scripts/verify-animation-ribbon-solo-group-ctor89-native.py`](../scripts/verify-animation-ribbon-solo-group-ctor89-native.py)
independently checks original function boundaries, all original E8 and
HIGHLOW site/destination pairs, exact returns, real class size and all
six native vtable fields with their physical PE relocations:

| Original head | Original fields | Meaning |
| --- | --- | --- |
| `0x0045D5B0`, **89B** | E8 `+0x0E -> 0x00446B60` | Real AnimationCallback base construction |
| | DIR32 `+0x18 -> 0x0056ECA4` | Genuine derived class vptr |
| | E8 `+0x22 -> 0x0045D550` | Independently whole-exact 78B single-segment array ctor |
| | E8 `+0x3E -> 0x00422D90` | Original Timer constructor |
| `0x0045D6B0`, **49B** | E8 `+0x0A -> 0x0045C2A0` | Folded 20B base/derived ordinary destructor |
| | E8 `+0x20 -> 0x0054278D` | Genuine sized delete, pushing the real `0x3E0` object size |

The original constructor additionally initializes the true float
control at `+0x3C8`, `Timer` at `+0x3CC`, and four-byte pointer-like
storage at `+0x3DC`. Those fields are declared with real offsets and
full `sizeof(NativeRibbonSoloGroup)==0x3E0` assertions in
[`src/NativeRibbonSoloGroup.hpp`](../src/NativeRibbonSoloGroup.hpp).

## One natural C++ owner and full native replay

The maintained [`src/AnimationRibbonSoloGroupCtor89.cpp`](../src/AnimationRibbonSoloGroupCtor89.cpp)
uses ordinary base/member construction, including real
`std::array<NativeRibbonSegment,1>` at `+0x08`. Pinned MSVC x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl` emits both the
constructor and deleting wrapper; its implicit derived destructor
also emits a complete 20B native body identical to the already
accepted shared physical original, without `novtable` or manual vptr
modification. Full relocation-aware canonical original oracle:

```text
animation_ribbon_solo_group_ctor_89: exact (89/89 bytes)
animation_ribbon_solo_scalar_delete_49: exact (49/49 bytes)
Exact replay: 2/2 new units, one cold object
```

The previously exact 78B array ctor, 140B update, 156B draw and
697B dynamics were also locally recompiled with no regressions.
**Only the authored 89B constructor adds one game function /89 unique
original `.text` bytes.** The generated 49B destructor remains
`origin=unknown/review` and carries zero additional authored-game
byte credit. Original 20B physical code is not claimed twice.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-group-ctor89-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloGroupCtor89.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
