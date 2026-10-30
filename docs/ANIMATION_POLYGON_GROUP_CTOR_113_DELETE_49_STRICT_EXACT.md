# CORE/RECON-907 — original 113B polygon Motion group constructor and 49B scalar-deleting wrapper strict exact

This checkpoint is grounded in the immutable Japanese TH20 Steamless 1.00a target, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`. The **entire original 113-byte, 30-instruction game-authored polygon Motion group constructor `0x0045F340`** and the separate **49-byte, 18-instruction compiler-generated scalar deleting destructor `0x0045F5A0`** pass fresh pinned MSVC x86 **complete canonical relocation replay**. They are distinct original executable addresses; the latter is **excluded** from authored-game credit.

## Original-only executable and virtual table observations

[`scripts/verify-animation-polygon-group-ctor113-native.py`](../scripts/verify-animation-polygon-group-ctor113-native.py) checks the *locked original PE only*, independently of reconstructed source and COFF. It attests the complete original 113B, 49B and separate 20B function boundaries; all native E8 site/actual absolute callee pairs, all original PE HIGHLOW fields and the six native vtable pointer values at `0x0056EE50`.

The 113B original game constructor has four genuine E8 calls and one PE HIGHLOW:

| Native field offset | Kind | Physical original target | Purpose |
| --- | --- | --- | --- |
| `+0x0F` | REL32 | `0x00446B60` | `AnimationCallback(Animation*)` base constructor |
| `+0x18` | DIR32 | `0x0056EE50` | Actual derived vtable, not an invented private table |
| `+0x23` | REL32 | `0x0045F2B0` | Complete exact 78B `std::array<Segment,3>` constructor |
| `+0x3F` | REL32 | `0x00422D90` | Original Timer default constructor |
| `+0x5A` | REL32 | `0x00422E10` | Original Vector3 default constructor |

It then returns the real `this` pointer by `ret 4`. Its original 0xBAC-byte layout consists of the 8B polymorphic `AnimationCallback` base, `3 × 0x3D4B` segment array at `+0x08`, a float-initialized four-byte control at `+0xB84`, Timer at `+0xB88`, an **opaque four-byte field** at `+0xB98`, Vector3 at `+0xB9C`, and a byte at `+0xBA8` initialized to one. Only its physical 32-bit storage/use is proven for the opaque field; the current pointer view is still a type hypothesis, **not** independent proof of object ownership.

The actual original vtable `0x0056EE50` contains the physical slots:

| Slot | Original pointer | Native identity |
| --- | --- | --- |
| `+0x00` | `0x0045F5A0` | 49B scalar deleting destructor wrapper |
| `+0x04` | `0x0045F5E0` | Already whole exact 140B virtual `update()` |
| `+0x08` | `0x0045F9B0` | Already whole exact 233B virtual `draw()` |
| `+0x0C` | `0x00412540` | inherited/folded base slot |
| `+0x10`, `+0x14` | `0x00414B50` | inherited/folded base slots |

**Remaining vtable-linking frontier:** the original PE has six virtual slots, while the current source-emitted derived vtable has five directly defined slots. The additional sixth folded/inherited original slot remains unresolved; whole ctor exactness does not imply complete runtime vtable parity.

This proves the C++ owner uses a genuine `AnimationCallback` base rather than an unrelated flat record with a guessed vptr. The original 156B C++17 diagnostic allocation factory **E8-calls this 113B constructor** at its physical `+0x6A` site.

The 49B original scalar-deleting wrapper has E8 `+0x0A → 0x0045C2A0` (the original **20B ordinary destructor**, independently verified but **still NONEXACT**) and `+0x20 → 0x0054278D` (real native sized delete). It has no PE HIGHLOW data fields. Generating that MSVC wrapper naturally from the real virtual destructor declaration emits its **complete 49/49B** original bytes. This exact wrapper **does not accept its separate 20B destructor child**, nor imply original object construction or game linkage is fully complete.

## Full natural C++ reconstruction and exact unit preservation

One shared [`src/NativePolygonMotionGroup.hpp`](../src/NativePolygonMotionGroup.hpp) now declares `NativePolygonMotionGroup : AnimationCallback`, the correct inherited virtual `update()` and `draw()` overrides, and actual 3-segment C++20 array. Its constructor is maintained in [`src/AnimationPolygonGroupCtor113.cpp`](../src/AnimationPolygonGroupCtor113.cpp). The original `0x0045F340` genuinely **does not pre-clear** the whole `0xB7C` array before array construction: explicitly adding `segments_08()` to the member initializer list emitted a nonnative whole-array memset and increased the candidate to 135B. Leaving that aggregate member to its natural *default initialization* while explicitly initializing the true float control, Timer, opaque value, Vector3 and flag yields the entire original **113B/30 x86**, exactly **93/93 nonrelocation bytes** with all five original relocation positions/kinds/targets. No artificial NOP, dead compiler-shaping local or target-byte patch was used.

This 113B constructor uses the real original **C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl` without `/EHsc`**, avoiding an otherwise extraneous 169B exception prologue. The separate [`src/AnimationPolygonMotionGroupFactory156.cpp`](../src/AnimationPolygonMotionGroupFactory156.cpp) retains its authentic **C++17 `/EHsc /sdl`** profile, and now instantiates `DiagnosticAllocator::allocate_object<NativePolygonMotionGroup,Animation*>`, matching the actual inherited `Animation*` receiver. Its old nominal `uint32_t` handle signature was a proxy; the original **156B/46-x86 and all six physical relocation roles are unchanged**. The 47B caller source simply reinterprets its 32-bit handle as the observed native Animation pointer, preserving that original cdecl body.

The original 140B and 233B game-owned methods' physically exact original addresses are unchanged; their **correct compiler symbols** are now `?update@NativePolygonMotionGroup@th20@@UAEHXZ` and `?draw@NativePolygonMotionGroup@th20@@UAEHXZ`, rather than provisional nonvirtual descriptive names. All previously accepted exact game/group/helper units retain the identical physical original `.text` bytes and original relocation destinations. Compiler-generated vtable `.rdata` labels do not receive new `.text` credit.

The actual affected-only bounded native replay for **four source providers** (including the triple-array constructor source, which includes the changed group header) is:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
animation_polygon_registry_wrapper_47: exact (47/47 bytes)
animation_polygon_group_tick_140: exact (140/140 bytes)
animation_polygon_group_factory_156: exact (156/156 bytes)
animation_polygon_color_array_ctor_75: exact (75/75 coverage bytes; 80/80 compared bytes)
animation_polygon_segment_array_ctor_78: exact (78/78 coverage bytes; 83/83 compared bytes)
animation_polygon_group_ctor_113: exact (113/113 bytes)
animation_polygon_group_scalar_delete_49: exact (49/49 bytes)
Exact replay: 11/11 units, 4 cold objects
```

The new **113B authored original game code** is credited once in `config/matches.csv`. The **49B compiler-generated virtual wrapper** is `origin=compiler, disposition=exclude`, is still separately strict exact, and contributes zero to authored-game total. Neither previous 156B allocation factory nor previous exact group methods are double counted.

Live after this checkpoint: **1,334 source-present mappings, 1,333 strict canonical units, 304 pinned compiler object/receipt providers; 640 distinct game-authored whole exact functions /234,802 native `.text` bytes**. This is not evidence that TH20 as a whole links or plays.

### Narrow reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-group-ctor113-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonMotionGroupFactory156.cpp --source src/AnimationPolygonGroupCtor113.cpp --source src/AnimationPolygonSegmentArrayCtor78.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_ctor_113
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_scalar_delete_49
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Only the actual four affected native C++ source providers are cold-rebuilt: **no unfiltered whole-repository replay**. The separately original-only verified 20B ordinary destructor, 75B Vector2 array constructor, 104B outline caller and 5,993B Animation Draw dispatcher remain open as independent nonexact heads.
