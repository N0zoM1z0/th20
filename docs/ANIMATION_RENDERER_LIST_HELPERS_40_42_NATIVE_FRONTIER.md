## CORE/RECON-1113 — maintained 40B double-tail constructor and 42B reset frontier

The original `0x00418A50` has **40 genuine code bytes and 16 x86
instructions**. The original SHA-pinned machine code and target-bound
disassembly show two writes to the same physical `tail` field at `this+0x14`.
The maintained Animation-specific specialization now expresses the natural
member-initializer plus constructor-body invariant directly in
[`src/IntrusiveListAnimation.hpp`](../src/IntrusiveListAnimation.hpp):

```cpp
inline IntrusiveList<Animation>::IntrusiveList()
    : IntrusiveLink<Animation>(), tail(this) {
    tail = this;
}
```

Pinned MSVC 19.44 i386 C++20 emits the **full original 40B/16-instruction
extent**, including both tail stores and the one E8
`+0x0A -> 0x00418A10`. The full comparison reaches **34/36 ordinary
(nonrelocation) bytes**. The only differences are two ModRM register-direction
bytes: native `+0x16 = 0x41` versus candidate `0x48`, and native `+0x1F = 0x50`
versus candidate `0x42`. This is a real C++ source hypothesis now present in
the maintained header, but it remains **NONEXACT** and receives no head/byte
credit.

The bounded regression script
[`scripts/probe-animation-list-ctor40-double-tail.py`](../scripts/probe-animation-list-ctor40-double-tail.py)
compiles the maintained `probes/AnimationRendererLinkFrontier.cpp` against
the real header. It SHA-attests the original constructor and the existing
63B/61B link helpers, requires the two specific ModRM differences, and
rejects a false exactness claim. It no longer clones or rewrites a private
header hypothesis.

The physically separate 42B reset remains **37/38 ordinary bytes**, with
one register-selection byte unresolved at `+0x22` (`0x42` emitted versus
native `0x50`). A further 21 compilable natural C++ forms were tested for
that reset: distinct owner/base/value pointers, reference aliases,
pointer-to-member access, address-of-field stores, qualified base calls, and
scoped pointer lifetimes around `initialize(input)`. None produced an exact
42B candidate. No assembly, padding, or fabricated code is used, and neither
leaf receives strict exact credit.

Fast focused reproduction:

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-list-ctor40-double-tail.py
```

---

**Historical 2026-11-11 baseline (superseded by the current CORE/RECON-1113 update above):** The *parent* 508B/511B Renderer updates are
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
