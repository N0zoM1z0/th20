# CORE/RECON-892 — whole original 47B registry-to-polygon configuration wrapper strict exact

> **CORE/RECON-903 correction:** The original `0x0045F0A0` 156B function is now [whole strict exact as the C++17 diagnostic allocator factory](ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md), **not** a registry resolver. The original global `0x005B8894` is `process_allocator` and the old `NativePolygonRegistryOwner` name was provisional. The 47B wrapper retains all original byte/relocation roles after correction. Historical labels below document the earlier hypothesis only.

The immutable Japanese TH20 v1.00a Steamless original executable has
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original cdecl wrapper at **`0x0045FD10`** now has a natural C++
source in [`src/AnimationPolygonMotionGroup233.cpp`](../src/AnimationPolygonMotionGroup233.cpp)
that reproduces **all 47B/18 original x86 instructions**, plus all
**two direct E8 and two PE HIGHLOW** physical relocation site/target
identities in one pinned whole-native strict canonical match unit.

## Immutable PE-only source/ABI and callee proof

[`scripts/verify-animation-polygon-registry-wrapper47-native.py`](../scripts/verify-animation-polygon-registry-wrapper47-native.py)
reads the entire 47B immutable original PE and its actual PE `.reloc`
fields. It independently validates its one local `push ecx`/`mov
[ebp-4],eax`, cdecl `ret` without callee stack cleanup, and these
four original physical site/target references:

| Native original source field | Real original site and target |
| --- | --- |
| Registry type marker address | PE HIGHLOW `+0x09` → `0x0056EE68` |
| Global registry owner pointer | PE HIGHLOW `+0x0F` → `0x005B8894` |
| Registry resolution | E8 `+0x13` → `0x0045F0A0` (original 156B function) |
| Actual polygon configuration | E8 `+0x26` → `0x0045FB60` (earlier strict 296B Boss) |

The wrapper accepts three cdecl stack arguments: a registry handle,
a `NativePolygonGroupOptions*` and a native integer value. It calls
the registry resolver with the handle and the actual original marker
address, retains the returned group pointer in its real local, then
passes the options and integer to the complete
[296B polygon group initialization Boss](ANIMATION_POLYGON_GROUP_CONFIG_296_STRICT_EXACT.md).
The resolver `0x0045F0A0` is a separate original 156B native function
and is **not** promoted to exact by this caller's reconstruction.
No invented marker data, global allocation or replacement registry
class is added; only observed external ABI/targets are declared.

## Why the original has no post-call NOP

A first plausible C++ source declared the wrapper as `void __cdecl`
and discarded the 296B callee's integer result. MSVC `/Od` compiled
**48B/19 i386**, adding a `NOP` immediately after the final call.
The original PE has **no NOP** there; its last call leaves the
296B callee's return EAX intact all the way through the cdecl return.
Expressing the actual operation as an integer-returning C++ function

```cpp
std::int32_t __cdecl configure_polygon_group_45fd10(
    std::uint32_t handle, const NativePolygonGroupOptions* options,
    std::int32_t value) {
    NativePolygonMotionGroup* group = native_polygon_registry_5b8894->resolve_45f0a0(
        native_polygon_type_marker_56ee68, handle);
    return group->configure_group_45fb60(*options, value);
}
```

naturally compiles **47B/18 i386**, with **31/31 original
nonrelocation bytes** identical. The original game runtime can use
that return value or ignore it; the exact source ABI preserves it
rather than artificially adjusting machine-code bytes. No inline
assembly, object patch, padding or fake `NOP` is involved.

## Strict acceptance and conservative game-original code credit

One new unit `animation_polygon_registry_wrapper_47` in
[`config/match-units.toml`](../config/match-units.toml) uses the
existing pinned i386 MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` source object/receipt
`build/core884-canonical/AnimationPolygonMotionGroup233.obj`.
All original E8/PE HIGHLOW symbols, physical offsets, relocation
types and true absolute destination addresses are attested
independently by the original-only native verifier.

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
animation_polygon_registry_wrapper_47: exact (47/47 bytes)
Exact replay: 5/5 units, 1 cold objects
```

The 23B/19B array helpers remain origin-uncertain and are not
credited as hand-authored game code. The 120B palette and two 31B
tag-forwarding functions remain separately whole strict exact in
their own earlier source unit; the original 104B outline caller
and original 156B registry resolver are still NONEXACT. No global
cold replay is run. The new wrapper counts as **one unique authored
game function /47 native `.text` bytes**. Live accepted game coverage
becomes **636 exact whole original authored functions /233,662 native
code bytes**, **1,288 source mappings /1,287 canonical strict units /
298 pinned compiler source-object providers**.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-registry-wrapper47-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_registry_wrapper_47
scripts/repo-python scripts/validate-tracking.py --require-target
```
