# CORE/RECON-907 — whole 113B polygon group Boss constructor and 49B scalar-deleting wrapper native exact

Immutable original target: Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete game-owned **`0x0045F340` 113B/30-i386 polygon Motion group constructor** is now **113/113 whole canonical relocated bytes exact**, a genuine parent of the already exact 78B three-segment array constructor and called directly from the exact 156B C++17 allocation factory. The separately generated **`0x0045F5A0` 49B/18-i386 scalar-deleting destructor wrapper** is **49/49 whole native exact**, but compiler-owned rather than authored-game code. The ordinary 20B destructor at `0x0045C2A0` remains **NONEXACT**; wrapper exactness is not evidence of its callee's exactness.

## Independent original PE ABI and vtable evidence

The [original-only verifier](../scripts/verify-animation-polygon-group-ctor113-native.py) reads the locked `.text` and PE `.reloc` directly, not any candidate object. It checks all complete 113B/49B/20B original instruction extents and **all physical native call/destination pairs and HIGHLOW roles**. The original 113B constructor has four genuine E8 and one PE HIGHLOW field:

| Native relocation field | Original physical destination | Meaning |
| --- | --- | --- |
| `+0x0F` REL32 | `0x00446B60` | Real `AnimationCallback(Animation*)` base constructor |
| `+0x18` DIR32 | `0x0056EE50` | Native derived polygon group vtable |
| `+0x23` REL32 | `0x0045F2B0` | Complete 78B C++20 triple-segment `std::array` constructor |
| `+0x3F` REL32 | `0x00422D90` | Timer default constructor |
| `+0x5A` REL32 | `0x00422E10` | Vector3 default constructor |

Its authentic member order is native 8B polymorphic base with `Animation*` at `+4`, three `0x3D4` segments at `+8`, a float-zero lane at `+0xB84`, Timer at `+0xB88`, a four-byte opaque token at `+0xB98`, Vector3 at `+0xB9C`, and a true byte `+0xBA8 = 1`; whole allocation size **0xBAC**. It returns the original object pointer with `ret 4`.

The independently file-backed native vtable at `0x0056EE50` has original first entries `0x0045F5A0` scalar delete, `0x0045F5E0` whole-exact 140B update, `0x0045F9B0` whole-exact 233B draw. The source now declares a real `NativePolygonMotionGroup : AnimationCallback` (not a parallel flat class) and correctly exports **`update()` and `draw()` as virtual overrides**, using those same original 140B/233B method bodies. They preserve 140/140 and 233/233 entire original bytes under their updated linker symbols. The fifth and sixth virtual table slots represent inherited/folded original source identities; the present MSVC source table exposes five entries, and the additional native sixth entry is still to be reconciled for whole-program linkage. **Constructor exactness alone does not prove a complete exact vtable or a playable game.**

## Why source expression order and field type matter

An initial candidate with real derived `std::array` member **value initialization `segments_08()`** caused MSVC C++20 to emit a redundant `memset(0xB7C)` before constructing the array, producing **135B/37 instructions** and a wrong third E8. The original PE has no pre-clear in the derived constructor: the actual segment-array object is **default-initialized**. Omitting that explicit value initializer produces exactly **113B/30 x86**, and the original `std::array` ctor call at `+0x22`. The class/member initializer order naturally emits the native float-zero store, Timer, zero word, Vector3 and terminal Boolean. No manual byte padding or assembly was introduced.

The 156B original C++17 `/sdl` allocation template also genuinely needs a pointer-bearing class to generate the native auto-initializer. The base class provides the original verified `Animation*` at `+4`; a separate **existing four-byte token at `+0xB98`** is retained as a direct `void*` *codegen/ABI view* with no pointer dereference or invented extra storage. The original only writes zero and assigns an opaque four-byte configuration argument to this slot; its precise semantic meaning (pointer or integer token) **remains unproven**. The `void*` spelling therefore denotes a provisional 32-bit source interpretation, not a claim of confirmed pointer behavior. It does reproduce both the original `/sdl` 156B factory's class auto-init and the original 296B configuration's raw four-byte assignment. The factory forwards **`Animation*`**, rather than the former provisional `uint32_t` handle, to the original 8B base constructor. The factory's six native relocations, the 47B caller's four original roles and all original machine bytes remain exact.

The 49B compiler scalar-deleting wrapper calls original physical `0x0045C2A0` at E8 `+0x0A` and the native sized delete `0x0054278D` at E8 `+0x20`, with no PE HIGHLOW. Ordinary C++ `virtual ~NativePolygonMotionGroup()` produces precisely the 49B complete wrapper without source padding, and the compiler's separate ordinary destructor body is **29B**, not the actual **20B**. Thus this 49B unit is accepted as a whole original compiler wrapper, but **the 20B destructor is explicitly not accepted**, and native runtime destruction still needs its source/ABI repair.

## Canonical strict proof and conservative accounting

One pinned `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl` (no `/EHsc`) source provider `src/AnimationPolygonGroupCtor113.cpp` emits both new complete exact functions with **5/5** ctor relocations and **2/2** scalar deleting wrapper relocations, independently matched to the original PE. In `config/match-units.toml` the exact units are `animation_polygon_group_ctor_113` and `animation_polygon_group_scalar_delete_49`. The two already exact group methods and C++17 factory preserve the original physical targets but now have correctly typed C++ mangled symbols.

The affected-only cold replay gives:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
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

This adds **one whole game-authored original 113B function**, credited exactly once to `config/matches.csv`: live authored coverage becomes **640 distinct functions /234,802 disjoint original bytes**. The separate 49B compiler scalar-deleting wrapper stays `origin=compiler/exclude`; the already accepted 156B factory and 78B/75B array constructors remain non-authored-origin credited. Source mappings become **1,334**, strict canonical units **1,333**, pinned compiler object/receipt providers **304**. The game is still not globally linked or playable.

### Reproduce only the affected source closure

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-group-ctor113-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonMotionGroupFactory156.cpp --source src/AnimationPolygonGroupCtor113.cpp --source src/AnimationPolygonSegmentArrayCtor78.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_ctor_113
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_scalar_delete_49
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

No unfiltered whole-graph cold replay, artificial target/object byte patching, compiler-only dead local or invented executable body was used.
