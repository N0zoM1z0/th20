# CORE/RECON-947 — complete 172B native 200-particle group ctor and 49B deleting wrapper

Immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045C1F0` is a genuine game-owned **172B/46-i386**
polymorphic constructor for a **0x1940-byte** `AnimationCallback`
group. Its physical vptr is `0x0056EC14`, whose six original entries
include the **49B/18-i386** scalar-deleting wrapper at `0x0045C320`.

## Complete original PE body and class evidence

[`scripts/verify-animation-particle-grid-group-ctor172-native.py`](../scripts/verify-animation-particle-grid-group-ctor172-native.py)
reads the locked executable directly and verifies the complete original
172B/46 and 49B/18 disassemblies, actual returns, **nine native ctor
E8 fields and targets**, one genuine ctor HIGHLOW to the vtable, two
real deleting-wrapper E8, zero deleting-wrapper HIGHLOW, authentic
`sized delete(0x1940)` and all six physical PE-relocated vtable slots.
The original 156B allocation factory contains a genuine E8 at
`0x0045C0FA` to this constructor.

The source-owned layout is established by actual original call offsets:

| Owner offset | Real original subobject or action |
| --- | --- |
| `+0x08` | 200 four-byte `AnimationHandle` color cells; constructor E8 `+0x22 -> 0x0045C190` |
| `+0x328` and `+0xC88` | Two independently real 200-element `Vector3` arrays, 2,400 bytes each; ctor E8 `+0x30/+0x3E -> 0x0045C130` |
| `+0x15E8` | 200 floats cleared through genuine 800B `memset` E8 `+0x54 -> 0x00544760` |
| `+0x1908`, `+0x1914`, `+0x1920` | Three 12-byte Vector3 default constructors E8 `+0x65/+0x73/+0x81 -> 0x00422E10` |
| `+0x192C` | One naturally zero-initialized float |
| `+0x1930` | Native 16B Timer ctor E8 `+0x9D -> 0x00422D90`; total group size `0x1940` |

The first base constructor E8 `+0x0E -> 0x00446B60` and vptr HIGHLOW
`+0x18 -> 0x0056EC14` are also independently checked. The generated
49B deleting wrapper uses E8 `+0x0A -> 0x0045C2A0` to the *already
accepted* original folded 20B ordinary destructor, and E8 `+0x20 ->
0x0054278D` to real sized delete. That 20B head is never double-credited.

## Natural source and full original-byte match

[`src/NativeParticleGridGroup.hpp`](../src/NativeParticleGridGroup.hpp)
holds one layout-asserted polymorphic class with real arrays and Timer.
The natural [`src/AnimationParticleGridGroupCtor172.cpp`](../src/AnimationParticleGridGroupCtor172.cpp)
expresses ordinary base and member initialization, with the float array
value-initialized to zero. There is no manual memset, fake vptr, C++
assembly or artificial byte padding. Both distinct array constructors
were [separately accepted 83/83 each](ANIMATION_PARTICLE_GRID_ARRAYS200_78_STRICT_EXACT.md)
before this parent was admitted.

Pinned x86 MSVC 19.44 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally emits exactly the original native
bodies, with the genuine original one-byte `NOP` after Timer creation.
The canonical original target relocated replay verifies:

```text
animation_particle_grid_group_ctor_172: exact (172/172 bytes)
animation_particle_grid_scalar_delete_49: exact (49/49 bytes)
Existing 200-color and 200-Vector3 array ctor units: exact (83/83 each)
Exact replay: 4/4 units, 2 cold objects
```

Only the original 172B custom group constructor receives **one
newly credited game-authored function /172 `.text` bytes**. The generated
49B and prior two compiler array constructors remain origin-unknown and
zero-credit. The separate original 156B factory, update and other vtable
methods are not inferred exact until independently reconstructed.
No unfiltered full cold replay occurred.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-group-ctor172-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridGroupCtor172.cpp --source src/AnimationParticleGridArrays200.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
