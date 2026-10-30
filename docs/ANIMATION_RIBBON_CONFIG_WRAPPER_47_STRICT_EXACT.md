# CORE/RECON-920 — original 47B ribbon allocation/configuration wrapper exact

> **CORE/RECON-922 follow-up:** The original separate 252B configuration
> function is now independently [whole 252/252 native strict exact](ANIMATION_RIBBON_GROUP_CONFIG_252_STRICT_EXACT.md).
> The previously accepted 47B wrapper receipt is unchanged.

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-specific **47B/18-i386** CDECL function at
`0x0045EC70` registers a ribbon group by constructing its native
`0xB60` polymorphic object through the independently accepted
[156B allocator factory](ANIMATION_RIBBON_GROUP_FACTORY_156_STRICT_EXACT.md)
and invoking the separate original **252B configuration method**.

Independent original-PE verifier
[`scripts/verify-animation-ribbon-config-wrapper47-native.py`](../scripts/verify-animation-ribbon-config-wrapper47-native.py)
checks its whole 47B body/return and the exact native physical
relocation sites and destinations:

| Original field | True target | Native meaning |
| --- | --- | --- |
| DIR32 `+0x09` | `0x0056EDF8` | Genuine ribbon allocation type marker |
| DIR32 `+0x0F` | `0x005B8894` | Existing diagnostic allocator global |
| E8 `+0x13` | `0x0045E5D0` | Whole-exact C++17 156B ribbon factory |
| E8 `+0x26` | `0x0045EB10` | Separate 252B ribbon-group configuration Boss |

[`src/AnimationRibbonConfigWrapper47.cpp`](../src/AnimationRibbonConfigWrapper47.cpp)
uses the real `DiagnosticAllocator::allocate_object<NativeRibbonGroup,
Animation*>` and a C++20 `extern template` declaration so the 156B
factory retains its single C++17 source owner. It forwards the
actual options and token to the original 252B group method;
neither compiler-shaping no-op code nor fake return/padding is used.

The pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` produces the full canonical
relocation-aware match:

```text
animation_ribbon_config_wrapper_47: exact (47/47 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared ribbon group header was extended only with the authentic
252B method interface. The new source alone is **1/1 exact**; its actual
affected-header closure also preserves all **11 prior exact units** in
nine existing objects. The combined scoped replay confirms **12/12 units
from 10 cold objects** without any whole-graph cold replay.
The 47B body is original game registration/configuration logic,
adding **one authored original game head /47 distinct `.text` bytes**.
Its 252B configuration child remains independent and does not
become exact merely because the 47B parent is exact.

```bash
scripts/repo-python scripts/verify-animation-ribbon-config-wrapper47-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonConfigWrapper47.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
