# CORE/EXACT-190: complete native EnemyController animation resource selector

The genuine game-owned `EnemyController::animation_file(int)` at
`0x004AAE10` is now **151/151 bytes native-exact**, with all **7/7** original
relocations independently anchored. This is a *whole function* and a concrete
dependency of the **still nonexact 41,967-byte**
`EnemyState::execute_opcode()` boss. It is not a fake shortened case fragment.

The source is `src/EnemyResourceSelection.cpp`, compiled with locked MSVC
19.44.35211, x86, `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`. The canonical object and all receipt hashes are preserved at
`build/core190-canonical/EnemyResourceSelection.obj` and its sibling receipt.
The strict canonical unit is `enemy_controller_animation_file` in
`config/match-units.toml`; full relocation-aware comparison returns `exact`
for **all 151 native bytes**, not just a structural match.

## Original four-route protocol

The complete locked PE instruction sequence distinguishes four cases before
returning the selected `AnimationFile*`:

- **Index 7:** load original process pointer at `0x005C069C`, then call the
  independent 20-byte getter `0x004AADF0`. Its original class name and full
  Stage/Background storage are unresolved. The maintained `StageResourceOwner`
  is an explicit *inferred interface*, not a claimed recovered type; neither
  its global definition nor its method body is fabricated.
- **Index 0:** load the real `EnemyController+0x130` Context, call the Context
  BulletController getter (physical alias at `0x0040C300`), then the separately
  accepted byte-exact Bullet file view at `0x004859B0`.
- **Index 1:** load the same Context and call `Context::effect_info` at
  `0x0041CAD0`, then `EffectInfo::animation_file(0)` at `0x0045D100`.
- **All other indices:** call the actual checked **eight-element**
  `std::array<AnimationFile*,8>::at` at `0x004AA130`, using the native unsigned
  index comparison. Invalid negative indices are *not* silently repaired;
  the original checked-array exception path remains active.

The source's nested `if`/`else` mirrors these separate native control-flow
boundaries and branch-local resource selection; these are meaningful source
values and not an assembly trick or injected fake return. Three earlier
private source experiments of the same visible semantics compiled to 124,
145 and finally **151** bytes. Only the final natural nested version matched
the native target's complete code and original relocation roles. This
independently challenges the earlier documentation's convenience shortcut
which treated the owner as a uniform eight-pointer array.

## Seven independently established original anchors

| Original COFF field | Native target | Evidence |
| --- | --- | --- |
| `+0x11` DIR32 | `0x005C069C` | Stage/Background global and other native xrefs |
| `+0x16` REL32 | `0x004AADF0` | Stage getter: independently decoded full 20B load |
| `+0x2F` REL32 | `0x0040C300` | Genuine Context Bullet accessor shared physical alias |
| `+0x36` REL32 | `0x004859B0` | Previously strict-exact 20B Bullet getter |
| `+0x4F` REL32 | `0x0041CAD0` | Independent Context EffectInfo getter |
| `+0x5C` REL32 | `0x0045D100` | Complete EffectInfo resource getter |
| `+0x79` REL32 | `0x004AA130` | Native 34B eight-array checked index and other caller |

All seven were checked from **original x86 instructions and separate
producer/consumer evidence**, not reverse-solved from candidate mismatch
fields. The private evidence `.analysis/core190-native-selector-audit.json`
records original function digest, each original relocation target, actual
original direct calls, source/object SHA-256 and compiler receipts. Native
callers include original Enemy opcode 555 and other animation/effect paths.

## Affected-only native replay

The production `EnemyController.hpp` field is now a real
`std::array<AnimationFile*,8>` rather than a raw array, preserving the native
8-pointer layout and `EnemyController` size/offset assertions. The actual
previous compiler include closures select **11 existing production providers
plus the new selection TU**, **12 cold objects / 68 affected strict units**.
Every one of the **68/68** complete native units passed fresh locked-MSVC
compilation and strict original relocation-aware replay; other canonical
providers were not cold-built.

The header change renumbered six compiler-private `$SG` source string labels:
one Enemy allocation hint, one Controller construction diagnostic and four
Dialogue `text` literals. The original string contents, independently proven
native targets, relocation roles, function extents and machine-code results
remain unchanged. Only the corresponding actual fresh COFF **symbol names**
were refreshed in the canonical manifest; no target address was chosen from a
candidate mismatch and no comparison size was shortened. The current native
replay log is `.analysis/core190-affected-replay.log`.

## Acceptance boundary and further boss work

This checkpoint admits **151** additional confirmed authored exact bytes from
one genuine large-enough owner method, bringing the graph to **220 confirmed
authored exact functions / 57,442 bytes**, **1,006** canonical units and
**1,015** source-present mappings. The original Stage resource factory,
startup publication of `0x005C069C`, renderer/VM lifetime, remaining whole
Enemy opcode branches, compiler EH and jump tables are **still open**.
No whole-game executable has been reconstructed or linked, and no full cold
replay was run. Resume the **single complete-root private Enemy draft** and
exercise this real four-way method there instead of substituting the old
uniform-array host boundary. Keep old native/host proofs intact.
