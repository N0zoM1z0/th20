# AnimationHandle recursive flag-0 setter — 50B strict exact

The native helper at `0x0044FA30` is a 50-byte handle-first wrapper used by
Enemy ECL opcode 503 and by the Card HUD's borrowed animation-handle view. Its
body resolves the 32-bit handle through `current_animation_pool->resolve_handle`
and, when resolution succeeds, invokes `Animation::set_flag0_recursively()`.
A null resolved animation returns without mutating the handle.

## Natural C++ source

- `src/AnimationHandleSetFlag0Recursive.hpp`
- `src/AnimationHandleSetFlag0Recursive.cpp`
- Semantic entry: `th20::set_animation_handle_flag0_recursively(AnimationHandle*)`
- ABI: one handle pointer in ECX (`TH20_FASTCALL` on MSVC i386)

The generic handle-view name describes the observed receiver layout without
claiming that the original source owner was literally `AnimationHandle`. The
native call graph also contains a Card-HUD caller-local alias, and the original
class/source ownership remains **unknown**. No new authored-byte credit is
claimed from this source-level name.

## Strict native comparison

- Native extent: `0x0044FA30..0x0044FA61` (50 bytes)
- Canonical source object: `build/gpt-web-enemy-canonical/AnimationHandleSetFlag0Recursive.obj`
- Match unit: `animation_handle_set_flag0_recursive`
- Result: **50/50 bytes**, all three original relocation records and destinations

| Relocation offset | Kind | Native target | Meaning |
| ---: | --- | ---: | --- |
| `0x11` | DIR32 | `0x005C0028` | `current_animation_pool` |
| `0x16` | REL32 | `0x0044CD00` | `AnimationPoolOwner::resolve_handle` |
| `0x29` | REL32 | `0x0044FA70` | `Animation::set_flag0_recursively` |

The implementation uses ordinary C++ control flow and the original i386
calling convention. It contains no inline assembly, synthetic padding, or
post-return data. The target was re-attested against the locked Japanese
Steamless v1.00a executable before the Ghidra decompilation and focused replay.

## Caller evidence

The 41,967-byte `EnemyState::execute_opcode` decompilation uses this helper in
native switch case 53 / opcode 503 at callsite `0x0049197C`. The Card HUD also
has a caller-local `NativeCardGlyphView::show_digit_44fa30` alias targeting the
same physical entry. These callsites support the shared handle-view semantics,
not a definitive original class name.
