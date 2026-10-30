# CORE/RECON-933 — complete 47B solo-ribbon creation wrapper whole strict exact

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045DC70` is a **47B/18-i386** game-authored cdecl
function that constructs the actual polymorphic one-segment ribbon
group through the genuine C++17 factory before invoking an independent
**182B** configuration method. It is not the separate 47B
three-segment ribbon wrapper or a registry lookup.

[`scripts/verify-animation-ribbon-solo-wrapper47-native.py`](../scripts/verify-animation-ribbon-solo-wrapper47-native.py)
authenticates all original bytes through the actual `ret` boundary,
**two physical E8 instructions/targets** and both original PE HIGHLOW
fields:

| Original field | Destination | Native role |
| --- | --- | --- |
| DIR32 `+0x09` | `0x0056ECC0` | Real solo-ribbon allocation diagnostic marker |
| DIR32 `+0x0F` | `0x005B8894` | Actual process allocator pointer |
| E8 `+0x13` | `0x0045D2C0` | [Independently exact 156B solo-ribbon C++17 factory](ANIMATION_RIBBON_SOLO_FACTORY_156_STRICT_EXACT.md) |
| E8 `+0x26` | `0x0045DB30` | Separate **182B** original group configuration Boss, still independently open at this checkpoint |

[`src/AnimationRibbonSoloConfigWrapper47.cpp`](../src/AnimationRibbonSoloConfigWrapper47.cpp)
uses the actual `DiagnosticAllocator::allocate_object<NativeRibbonSoloGroup,
Animation*>` template instantiation with an `extern template` declaration,
preventing an incompatible second C++20 factory. The same canonical
class and original options/token ABI are used; it makes no raw memory
patch, fake extra caller, manually inserted NOP or inline x86 statement.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and full relocation-aware original-bound replay:

```text
animation_ribbon_solo_config_wrapper_47: exact (47/47 bytes)
Exact replay: 1/1 new strict units, 1 cold object
Affected local closure: 7/7 strict units, 6 cold objects
```

This credits **one new whole exact authored-game function /47 original
`.text` bytes**. Exactness of its 156B callee does not implicitly prove
the different 182B configuration method. No whole-graph cold replay ran.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-wrapper47-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloConfigWrapper47.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
