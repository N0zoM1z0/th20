# CORE/RECON-910/911 — complete 19B native ribbon array-end pointer

> **CORE/RECON-911 semantic correction:** The original `0x0045ECA0` is
> the one-past-end accessor of the **three genuine 0x3C0-byte ribbon
> segments**, not a free-standing four-byte field at offset +0xB40. Its
> actual C++ declaration/source and accepted symbol now live at
> [`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp) and
> [`AnimationRibbonSegmentArrayEnd19.cpp`](../src/AnimationRibbonSegmentArrayEnd19.cpp).
> The canonical 19/19-byte exact result remains unchanged, but the historical
> nominal `NativePolygonSlotB40` source-owner hypothesis is superseded.
> See [the whole exact 140B enclosing update](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md)
> and the separate still-open 156B draw at 0x0045EA20 for independent
> native loop evidence.


The locked target is the original Japanese TH20 1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The previously unsourced original `0x0045ECA0` has now been independently
reconstructed from natural C++ and verified over its **complete 19B/9-i386
function body**. Its two actual native parents remain unfinished; exactness
of this leaf cannot imply exactness of either parent.

## Original physical ownership and callers

[`scripts/verify-polygon-b40-accessor-native.py`](../scripts/verify-polygon-b40-accessor-native.py)
checks the full original PE function boundary and `ret`, all nine native
instructions, genuine `add eax,0xB40`, no in-body E8 or HIGHLOW, and two
independent original call instructions:

| Physical caller E8 | Complete target | Native context |
| --- | --- | --- |
| `0x0045E7A2` | `0x0045ECA0` | Parent `0x0045E770` (140B, NONEXACT) |
| `0x0045EA7A` | `0x0045ECA0` | Parent `0x0045EA20` (156B, NONEXACT) |

Original ECX receiver is returned as `receiver + 0xB40` via EAX. The
precise original owner class, member type beyond four-byte alignment, and
higher-order semantics remain provisional. These physical offsets are **not**
evidence that the receiver is the separately reconstructed polymorphic
polygon Motion group, nor proof that this body is game authored.

## Natural source, complete native replay and scope

[`src/AnimationRibbonSegmentArrayEnd19.cpp`](../src/AnimationRibbonSegmentArrayEnd19.cpp) declares
a real three-element `std::array` of 0x3C0-byte ribbon records and
returns the one-past-end segment pointer. This is ordinary C++ field-address arithmetic, not an
instruction stub or pointer-byte patch. The shared native group now declares its verified inherited vtable/update;
no new constructor or independent object allocation is introduced.

Pinned MSVC x86 C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl`
reproduces **all 19/19 original bytes** with zero relocations in the
canonical `animation_ribbon_segment_array_end_19` unit:

```text
PASS original caller E8 0x0045e7a2 -> 0x0045eca0
PASS original caller E8 0x0045ea7a -> 0x0045eca0
PASS original 0x0045ECA0: 19B/9 i386, add eax,0xB40, RET, no relocations
animation_ribbon_segment_array_end_19: exact (19/19 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The newly added object is the **only affected compiler provider**; existing
canonical sources and receipts are unchanged. Original authored-vs-compiler
origin remains `unknown/review`; this unit adds **no authored-game function
or text-byte credit**, and no parent-body credit.

```bash
scripts/repo-python scripts/verify-polygon-b40-accessor-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentArrayEnd19.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
