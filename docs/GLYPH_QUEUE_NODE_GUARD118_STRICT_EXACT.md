# CORE/RECON-1073 — whole original 118B PMR glyph queue node guard destructor, strict exact including native 5B INT3 tail

Immutable target Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original complete `0x00414350` **118B/41-i386**
`std::_List_node_emplace_op2<polymorphic_allocator<ListNode>>` guard
destructor has native physical SHA-256
`2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52`.
Its actual original caller is the separate **151B/51-i386** native
list `_Emplace` at `0x004131E0`, physical E8 `+0x7F`. That
151B parent also calls the independent **158B node constructor**
at E8 `+0x5B`. These are authentic original node-lifetime edges,
not conclusions derived from compiler labels.

## Native cleanup and whole-body exactness

The destructor checks the real PMR node's allocated state, resolves
the function payload through the folded pointer helper, invokes the
genuine allocator-traits `destroy`, releases the allocation
construction guard, and preserves MSVC's native exception-handler
and cookie checks. The entire native original has **three real E8**
and **two real PE HIGHLOW**:

| Original site | Physical target and source role |
| --- | --- |
| HIGHLOW `+0x06` | original function EH registration `0x00567750` |
| HIGHLOW `+0x15` | original security cookie `0x005B25C0` |
| E8 `+0x3B`, COFF field `+0x3C` | `0x0040B280` existing folded `std::_Unfancy` |
| E8 `+0x56`, field `+0x57` | newly independently strict-exact **17B** `_Normal_allocator_traits::destroy` `0x00413CA0` |
| E8 `+0x61`, field `+0x62` | previously exact **48B** `_Alloc_construct_ptr` destructor `0x004142E0` |

The original native destructor ends in an actual `ret` after **118B**.
Immediately following it are **five genuine `0xCC` (INT3) alignment
bytes** in the original executable, and the pinned MSVC C++20 source
generates precisely those **same five bytes** as part of this
function's complete **123B COFF contribution**. The prior claim
that the generated 123B was a *five-byte code length mismatch* was
therefore incorrect. The correct strict canonical unit now has
`size=118, compare_size=123` and checks **all original 118B code
bytes and all five original trailing INT3 bytes**. The distinct
function-code credit is only **118B**, not 123B, and no source
instruction or padding is hand-inserted.

The source is generated naturally from meaningful
[`std::pmr::list<std::function<void()>>` insertion](../src/GlyphTextQueueList151.cpp).
It is a real STL node-construction guard destructor, not an
independent invented function that happens to have the same bytes.
Read-only [`verify-glyph-queue-node-guard118-native.py`](../scripts/verify-glyph-queue-node-guard118-native.py)
SHA-attests the complete original 118B/41 instructions and their
native `ret`, independently proves every original native E8 and
HIGHLOW, checks the real five INT3 alignment bytes and the whole
151B/51 parent E8, and validates the separately whole-exact
17B/16B/48B nested PMR/function destructors.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiles the entire 123B contribution into the existing one
canonical source object without changing accepted code. Independent
COFF/native comparison gives **103/103 ordinary nonrelocated bytes
in the complete 123B contribution**, five matching relocation
fields and the full five native INT3 bytes:

```text
glyph_queue_node_guard_dtor_118: exact (118/118 coverage bytes;
                                       123/123 compared bytes)
Existing real glyph queue allocator, transfer, destruct and PMR descendants:
  10/10 units exact, unchanged
Exact replay: 11/11 units, 1 cold object
```

This adds **one distinct whole-exact standard-library physical head /
118 native `.text` function bytes**. Its original provenance is
generic compiler/STL-owned (`origin=unknown`, `disposition=review`),
so **zero new game-authored head/byte credit**. Previously accepted
17B/16B/48B destructors, 47B/58B/59B allocation descendants, and
the exact 56B game-owned queue wrapper are not credited twice. The
original **151B list `_Emplace` and 158B node constructor remain
SOURCE-PRESENT, NONEXACT** (modern MSVC natural 130B and 143B
respectively). Their unaccepted bytes are not inferred exact from
the new 118B source. No original PE modification, fake NOP/INT3,
shortened native function extent, or full cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-queue-node-guard118-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueList151.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1074 — full 158B native node constructor source frontier

The larger original node constructor `0x00413000`, invoked by 151B
`_Emplace` E8 `+0x5B`, is now separately
[documented as SOURCE-PRESENT, NONEXACT](GLYPH_QUEUE_NODE_CTOR158_NATIVE_FRONTIER.md).
Its original complete 158B/51-instruction body has five genuine E8 and
two HIGHLOW; current real PMR-list C++20 naturally emits 143B/46,
missing one original folded pointer forwarding call. The original
118B guard destructor and all accepted PMR allocation/destruction
children stay WHOLE STRICT EXACT; none grants exact credit for 158B.
