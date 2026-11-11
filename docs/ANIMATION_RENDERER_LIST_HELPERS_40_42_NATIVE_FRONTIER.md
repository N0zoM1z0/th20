## CORE/RECON-1113 — native constructor double-tail store and exact-size C++ hypothesis

The original `0x00418A50` has **40 genuine code bytes and 16 x86
instructions**. The target-bound Ghidra analysis and the independently
SHA-pinned original machine code both show its actual executed operations:

```cpp
IntrusiveLink<Animation>::IntrusiveLink();
this->tail = this;  // original store 1 at +0x15
this->tail = this;  // original store 2 at +0x1E
```

Both stores affect the *same physical field* at `this+0x14`; their
source-level reason (for example a member-initializer phase plus a
constructor-body invariant) remains **unproven**. An explicitly
**evidence-only** private class-key probe hypothesizes a member
initializer and a constructor-body invariant assignment:

```cpp
IntrusiveList<Animation>::IntrusiveList()
    : IntrusiveLink<Animation>(), tail(this) {
    tail = this;
}
```

Pinned MSVC 19.44 i386 C++20 emits **the entire original 40B/16
instructions**, including two 0x14 tail stores and exactly one E8
`+0x0A -> 0x00418A10`. The full original comparison now reaches
**34/36 nonrelocation bytes**, rather than the historical 31B/13
instruction one-store candidate. The only remaining differences are
two **ModRM register-direction bytes**: native `+0x16 = 0x41` versus
candidate `0x48`, and native `+0x1F = 0x50` versus candidate `0x42`.
All other original constructor bytes and call roles match.

A reproducible single-object, original-only bounded experiment is
[`scripts/probe-animation-list-ctor40-double-tail.py`](../scripts/probe-animation-list-ctor40-double-tail.py).
It clones the *real maintained* `src/IntrusiveListAnimation.hpp` into
a disposable `.analysis/` translation unit, changes only the private
constructor hypothesis and **requires** the above two original ModRM
differences rather than pretending they are exact. The script also
SHA-attests the native constructor and the existing 63B/61B original
link helpers; no public header, canonical unit or receipt is changed.
The source interpretation of the duplicate tail publication needs more
evidence before mainline acceptance, and the current full comparison is
still **NONEXACT**. The real 42B reset remains **37/38 ordinary bytes**
(one original register-selection byte unresolved), despite 15 private
natural C++ alias/lvalue tests. **No new original head/byte credit.**

Fast focused reproduction:

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-list-ctor40-double-tail.py
```

---

**2026-11-11 status:** The *parent* 508B/511B Renderer updates are
[now complete strict exact](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md).
The physically separate **40B list constructor and 42B reset** remain
NONEXACT and have no new duplicate credit; the historical investigation
below is still valid for those two leaves.

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
The generic `IntrusiveLink.hpp` remains unchanged. At this historical
checkpoint, the Animation-only class specialization was a probe; it was
subsequently introduced in [the exact Renderer migration](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md)
with 82/82 existing exact consumers preserved. The new two-store ctor
*itself* is still only a private hypothesis, not canonical source.

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

Next experiments should resolve the two genuine ctor ModRM bytes and the
reset register-selection byte without unproven duplicate assignment or dead
locals. The **508B/511B update parents are already whole exact**; no physical
head may be credited twice.
