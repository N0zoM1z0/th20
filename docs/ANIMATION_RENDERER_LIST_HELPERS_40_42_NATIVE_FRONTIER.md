# CORE/RECON-995 — independent 40B/42B Renderer list-helper investigation

This follow-up to the [508B/511B complete Renderer update sources](ANIMATION_RENDERER_LIST_UPDATE_508_511_NATIVE_FRONTIER.md)
checks the *physical* original list primitive heads, without relying on the
prior docs' inferred template spelling, member order, or original authorship.
The target is the unchanged Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Complete original bodies and real call-site graph

| Original physical address | Complete body | Independent original observation | Natural C++20 probe |
| --- | --- | --- | --- |
| `0x00418A10` | 63B /18 x86 | Link default constructor, five null fields | **63/63 exact**; already canonical `link_default_ctor` under `DamageRegion` |
| `0x0044A670` | 61B /18 x86 | Link initializer with incoming pointer and four zeroed fields | **61/61 exact**; already canonical `link_initialize` under `DamageRegion` |
| `0x00418A50` | 40B /16 x86 | List constructor E8 `+0x0A -> 0x00418A10`, *two* tail publications | **31B, NONEXACT**; current generic constructor publishes tail once |
| `0x0044A640` | 42B /16 x86 | List reset E8 `+0x16 -> 0x0044A670`, one `ret 4` | **42B, 37/38 nonrelocated bytes**; instruction byte `+0x22` is `0x42` candidate vs `0x50` original |

The verifier [`verify-animation-renderer-link-frontier-native.py`](../scripts/verify-animation-renderer-link-frontier-native.py)
SHA-pins all four entire original function bodies independently, disassembles
to the true ending `ret`, checks each original E8 target, and checks absence
of PE HIGHLOW fields. It then compares the **real compiled** probe
[`probes/AnimationRendererLinkFrontier.cpp`](../probes/AnimationRendererLinkFrontier.cpp)
under pinned MSVC 19.44 x86. The 42B mismatch is specifically the register
chosen as the destination-base in the final `tail` store: the original does
`mov [eax+0x14],edx`, while the current source emits `mov [edx+0x14],eax`.
It is **not** a missing algorithm branch or a pointer-layout mismatch.

The 40B mismatch is **not** repaired by inserting a deliberate redundant
store. Such code would be compiler-shaping rather than recovered source
semantics. The compiler's physical original second tail write may reflect
different real source/member initialization roles; those remain unproven.
The actual public `IntrusiveLink.hpp` is unmodified. The Animation-specific
instantiation is an isolated **probe, not a second canonical template owner**.

## Canonical credit and bounded verification

Both the 63B default constructor and 61B initialize primitive were already
admitted by the earlier **EXACT-051** `src/IntrusiveLink.cpp`/`DamageRegion`
canonical owner, under unit IDs `link_default_ctor` and `link_initialize`.
The independent Animation probe reproduces their **same physical bodies**.
There are **zero new strictly accepted heads/bytes** from these two leaves.
The different 40B and 42B physical heads **remain NONEXACT**.

The existing owner object was rebuilt **once**, scoped to its `link_default_ctor`
unit. Both old original canonical units then still passed strict comparison:
`link_default_ctor: exact (63/63 bytes)` and
`link_initialize: exact (61/61 bytes)`. No project-wide cold replay occurred.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  probes/AnimationRendererLinkFrontier.cpp build/core995-probes/AnimationRendererLinkFrontier.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-renderer-link-frontier-native.py \
  --candidate-object build/core995-probes/AnimationRendererLinkFrontier.obj
nice -n 15 scripts/repo-python scripts/build.py --unit link_default_ctor
scripts/repo-python scripts/compare-coff-function.py --unit link_default_ctor
scripts/repo-python scripts/compare-coff-function.py --unit link_initialize
```

Next experiments should examine naturally expressed initialization order and
MSVC template symbol ownership for the list constructor/reset, while separately
assessing the far-reaching `struct`/`class` ABI migration required to close
both **508B/511B** update parents. No physical head may be counted twice.
