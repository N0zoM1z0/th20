# CORE/RECON-903 — complete original 156B polygon class allocation factory strict exact

> **CORE/RECON-907 correction:** The 113B called constructor now [whole native exact](ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md), and the C++17 factory forwards a real `Animation*` (not the earlier guessed `uint32_t` handle) into an 8B polymorphic `AnimationCallback` base. Its own 156B original code and all six native fields remain exact; a separate +0xB98 four-byte token has provisional pointer semantics. The older template spelling and nonexact-parent claim below are historical.

The immutable Japanese TH20 v1.00a Steamless target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original **156B /46 i386 function at `0x0045F0A0`** is now complete
**canonical relocation strict exact, 156/156 bytes**, including its real
exception-handler pointer and compiler stack cookie. This is a previously
source-absent class allocation factory **called by the already exact
47B polygon group configuration wrapper**, rather than a registry lookup.
The actual source is the C++17 diagnostic allocator template instantiation:

```cpp
// The real pointer-bearing class has sizeof 0xBAC.
template NativePolygonMotionGroup* DiagnosticAllocator::allocate_object<
    NativePolygonMotionGroup, std::uint32_t>(const char*, std::uint32_t);
```

## Independently verified native body and original caller

[`scripts/verify-animation-polygon-factory156-native.py`](../scripts/verify-animation-polygon-factory156-native.py)
reads **only the original locked PE `.text` and `.reloc`**, before any COFF
comparison. The true body ends in `ret 8`, has an EH state region, allocates
`0xBAC` bytes, performs the native class auto-clear and constructs the
real polygon group from the forwarded handle. All **four physical E8**
site/absolute callee identities are original-PE authenticated:

| E8 instruction offset | Original physical callee | Native role |
| --- | --- | --- |
| `+0x2D` | `0x0054275D` | `operator new(0xBAC)` |
| `+0x4D` | `0x0040C080` | MSVC class auto-initialization, clears all 0xBAC bytes |
| `+0x56` | `0x0040B280` | Real C++17 `std::forward<uint32_t>` folded helper |
| `+0x6A` | `0x0045F340` | Original 113B polygon group constructor (separate body) |

Both genuine PE HIGHLOW fields are `+0x06 → 0x00568997` (original
compiler EH handler) and `+0x15 → 0x005B25C0` (security cookie).
The *already strict exact* `0x0045FD10` wrapper calls this allocation
factory at original E8 `+0x13`, then calls the 296B polygon group
configuration Boss at `+0x26`. Its real absolute `0x005B8894`
owner is `process_allocator`, and original `0x0056EE68` is the
allocation diagnostic marker, not an independent invented registry.

## Original C++17 and native class identity, not an artificial memset

The ordinary C++20 `new T(std::move(handle))` and C++20 allocator template
hypotheses generate only **126B**, missing the original template forwarding
and auto-clear. C++17 of an incomplete, pointer-free byte-record type
generates **143B** with `std::forward`, but lacks the real class
initialization. A complete **`class NativePolygonMotionGroup` with an
existing, native-observed `Animation*` pointer member at `+0x04`**, compiled
using **C++17 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc**,
naturally generates the original **156B/46 i386** code, all four original
E8 positions and both native absolute data fields. It does so via the
existing untouched `DiagnosticAllocator::allocate_object<T, Args...>`
template, not manual memset, fake `std::forward` wrapper, inline assembly,
bytes copied from the PE or compiler-shaping locals.

One canonical owner declaration is now
[`src/NativePolygonMotionGroup.hpp`](../src/NativePolygonMotionGroup.hpp),
shared by the original group methods and the new
[`src/AnimationPolygonMotionGroupFactory156.cpp`](../src/AnimationPolygonMotionGroupFactory156.cpp).
It includes the genuine three `0x3D4`-byte segment objects and actual
`Timer`, `Animation*` and `Vector3` fields, with original layout asserts
at `+0x04`, `+0x08`, `+0xB84`, `+0xB88`, `+0xB98`, `+0xB9C`, `+0xBA8`
and full `sizeof == 0xBAC`. No second incompatible class is invented.

The original 47B wrapper in
[`src/AnimationPolygonMotionGroup233.cpp`](../src/AnimationPolygonMotionGroup233.cpp)
now calls the real `process_allocator->allocate_object<...>()`; its
`extern template` prevents a conflicting C++20 instantiation, leaving
one legitimate C++17 factory definition. Only the source relocation
symbol identity for the original `0x005B8894` global and `0x0045F0A0`
E8 call changed. The target addresses, relocation offsets and emitted
**47B/47B original code** did **not** change. Earlier incorrect
`NativePolygonRegistryOwner::resolve_45f0a0` was a semantic guess and
has been removed; this is not a new physical game function.

## Whole strict receipt and conservative credit

`animation_polygon_group_factory_156` is configured in
`config/match-units.toml` with **all six** original physical relocation
site/type/symbol/target roles. A freshly pinned MSVC x86 compiler object
`build/core903-canonical/AnimationPolygonMotionGroupFactory156.obj`
provides the entire strict native byte contribution:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
animation_polygon_registry_wrapper_47: exact (47/47 bytes)
animation_polygon_group_tick_140: exact (140/140 bytes)
animation_polygon_group_factory_156: exact (156/156 bytes)
Exact replay: 7/7 units, 2 cold objects
```

This proves **156 unique native `.text` bytes from source**. The body
is an instantiated compiler/allocator template and independent original
authorship is unproven, so it remains `origin=unknown/review` and is
**excluded from the authored-game byte ledger**. Its separate 113B
constructor is not promoted by the factory's exactness. Authored game
whole-exact coverage remains **638 functions /234,629B**. Live source
mappings become **1,329**, strict units **1,328** and pinned object
providers **301**. The game is not yet globally linked or playable.

### Reproduce only affected native providers

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonMotionGroupFactory156.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_group_factory_156
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Only **two** source providers are affected by the new header, typed
factory and corrected 47B call. No unfiltered whole-project cold replay.
