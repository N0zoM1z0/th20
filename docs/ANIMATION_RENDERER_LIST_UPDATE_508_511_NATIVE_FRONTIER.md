# CORE/RECON-993 — Renderer list-update Boss: original 508B primary source and compiler-tag frontier

Target: immutable Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Original native, independent of source hypotheses

`0x00449870..0x00449A6B` is the complete original **508B/152-i386**
primary Renderer update. The original locked 150B wrapper calls it directly.
The native contains **30 E8 / five PE HIGHLOW fields**; a whole-body SHA-256,
real termination at `ret`, exact physical call destinations, and all five
image relocation targets are checked by
[`verify-animation-renderer-list-update-native.py`](../scripts/verify-animation-renderer-list-update-native.py).
The original secondary Renderer update `0x00449B20..0x00449D1E` is a distinct
**511B/153-i386** function with an additional `+0x18` list-selection
instruction. No inference about exactness of one body is made from the other.

## Complete reconstructed algorithm

[`src/AnimationRendererListUpdate508.cpp`](../src/AnimationRendererListUpdate508.cpp)
retains the complete original two-pass traversal. A local 24-byte deferred
list is initialized/reset. The active list is iterated with actual
`IntrusiveIterator<Animation>` observer lifetime; each animation's
`+0x554` and `+0x550` pending words are cleared. State `+0x570 == 1`
queues the object and descendants for retirement via the separately exact
411B recursive method; state zero calls the **still nonexact 39,470B**
Animation VM and queues retirement only for its nonzero result. Other states
are skipped. A second iterator drains the deferred list, calling the
independently exact 308B AnimationPool release. No original branch,
retirement pass, allocator action or exception-safe iterator lifetime is
silently removed; no decompiler dump was copied into maintained source.

## Reproduced MSVC compiler mismatch: NONEXACT

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` builds the primary source as a complete **498B**
body, 10B shorter than the original. Both 498B and original 508B were
compared after independently masking relocation fields and excluding
**only** the original compiler-generated `0x2B..0x34` ten-byte sequence:
`push 0x18; lea ecx,[ebp-0x38]; call 0x0040C080`. All **498/498
remaining bytes** agree. This normalization is *diagnostic only*, not a
canonical relocated match.

An *ignored/private, fully restored* compiler experiment changing the shared
`IntrusiveList<T>` **struct** tag to **class** causes the **complete 508B**
primary candidate, **368/368 nonrelocated bytes** and original field sites,
including that real `/sdl` zero-initializer. This identifies a real
compiler-tag/ABI problem, not missing business logic. A global class-tag
change also changes decorated names and would invalidate many previously
exact providers; it is **not** adopted here without dependent source,
relocation and include-closure migration. The public header and all previously
accepted strict units remain unchanged. No new strict unit, original
`.text` exactness, whole-linkage or gameplay claim is made.

Reproduce the bounded investigation:

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationRendererListUpdate508.cpp build/core993-probes/AnimationRendererListUpdate508.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-renderer-list-update-native.py \
  --variant 508 --candidate-object build/core993-probes/AnimationRendererListUpdate508.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

The next step is a **scoped class-tag/ODR and real decoration dependency audit**.
Native constructor `0x00418A50` and reset `0x0044A640` also need separate
source-owner review. **Do not** claim an exact parent by normalizing out
missing source instructions or changing the canonical 508B function extent.

## CORE/RECON-994 — complete 511B secondary update source

The secondary wrapper at `0x00449A70` has an original physical E8 to
`0x00449B20`. The separate source
[`src/AnimationRendererListUpdate511.cpp`](../src/AnimationRendererListUpdate511.cpp)
uses the same active-update/recursive-queue/deferred-release protocol, with
one additional **`+0x18`** second-list selection. Its original entire native
body is **511B/153 x86 instructions** (SHA-256
`82610fc6e8e74938e509de8a188f053c31e2e9e08ff4039f498b7046861258d8`).
The verifier checks the 30 actual E8 targets, all five HIGHLOW original PE
relocations, original branch-to-VM/recursive-queue calls, the genuine additional
three-byte list displacement and one-byte post-function alignment. This
independently proves the body and distinguishes it from the 508B primary one.

Pinned MSVC with unchanged actual headers emits a complete 501B candidate.
The original 10B `/sdl` initialization at `0x2B` is the **only** missing
sequence: after independently masking the 35 native field sites (30 E8, five
HIGHLOW) and 34 candidate relocations, the other **501/501 bytes match**.
This is a byte-for-byte normalized *diagnostic*, not exactness. The original
511B extent must remain 511B. Neither this secondary Boss nor the primary
Boss is admitted to the strict-unit manifest, and no game-authored exact code
credit is added; all previously exact direct callers remain protected.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationRendererListUpdate511.cpp build/core993-probes/AnimationRendererListUpdate511.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-renderer-list-update-native.py \
  --variant 511 --candidate-object build/core993-probes/AnimationRendererListUpdate511.obj
```
