# CORE/RECON-1074 — complete native 158B glyph task-list node constructor: meaningful C++ source, NONEXACT compiler frontier

Locked original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x00413000` is a **whole 158B/51-instruction i386**
`std::_List_node_emplace_op2<polymorphic_allocator<ListNode>>`
constructor for the genuine native
`std::pmr::list<std::function<void()>>` glyph-render task queue.
Its native full-body SHA-256 is
`5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b`.
The original **151B/51-i386** `_Emplace` at `0x004131E0` physically
calls this entire function at E8 `+0x5B`. That original `_Emplace`
also calls the **now whole-exact 118B node guard destructor**
`0x00414350` at E8 `+0x7F`.

## Real native constructor, backed by exact child code

Original native i386 `_List_node_emplace_op2` owns an allocator pointer
and a node allocation state pointer, registers MSVC SEH/unwind for the
partial node lifetime, constructs a real `_Alloc_construct_ptr`
guard, allocates a polymorphic list node and constructs the captured
`std::function` value in its node payload. It does not perform a
fake fixed-size memcpy of the 40B function or move a disjoint game
task out of the real list. Its complete original **five E8/two PE
HIGHLOW** are:

| Original native site | Physical original destination | Real role |
| --- | --- | --- |
| HIGHLOW `+0x06` | `0x00567CBD` | actual constructor SEH handler |
| HIGHLOW `+0x15` | `0x005B25C0` | genuine security cookie |
| E8 `+0x2F` | `0x00413F50` | **already whole-exact 34B** `_Alloc_construct_ptr` constructor |
| E8 `+0x3E` | `0x004148D0` | **now whole-exact 47B** `_Alloc_construct_ptr::_Allocate` |
| E8 `+0x47` | `0x0040B280` | genuine folded function-argument pointer forwarding |
| E8 `+0x5C` | `0x0040B280` | second genuine folded node-value pointer forwarding |
| E8 `+0x7B` | `0x00413B00` | separate original 31B function-value node constructor |

The whole original ends in a real **`ret 8`**. The independent locked
PE verification
[`verify-glyph-queue-node-ctor158-native.py`](../scripts/verify-glyph-queue-node-ctor158-native.py)
SHA-attests the entire physical 158B/51 code, **all** original E8 and
HIGHLOW roles, and its genuine complete 151B parent E8. The checked
source below is not compared against a shortened native extent and no
parent exact credit is claimed.

## Correct typed natural C++ source, unaccepted 158B body

[`src/GlyphTextQueueList151.cpp`](../src/GlyphTextQueueList151.cpp)
maintains the actual `std::pmr::list<std::function<void()>>` queue and
truly inserts queued callable tasks. This is not an arbitrary
`NativeNodeView` with a manually imitated constructor: it naturally
instantiates the C++20 standard-library
`std::_List_node_emplace_op2` constructor as a genuine separate COFF
symbol on the same original-related translation unit.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiles that method as **143B/46 instructions**, with **four
REL32/two DIR32** fields. The original native method has **158B/51
instructions, five E8/two HIGHLOW**. Exact original Ghidra
read-only decompilation confirms two distinct live pointer-forwarding
calls, first for the function input and then for the node storage.
Modern installed MSVC STL emits one pointer forwarding/`addressof`
path directly instead, omitting the extra native E8 and shifting
allocation and exception-lifetime locals. The original-size gap is
**15B/five instructions** and a real call-graph difference, not
padding. Controlled source probes with lvalue, const lvalue,
`std::_Unfancy`, `std::move`, `std::forward`, insertion and direct
`emplace` all kept `_Emplace` at 130B and its nested node ctor
at 143B; no such source variant restored the original internal
STL forwarding operation.

The node ctor is therefore now **SOURCE-PRESENT, NONEXACT** in the
per-function ledger, with its full original signature, genuine parent
source file, physical target extent and independently pinned
compiler frontier. **No canonical exact unit is registered for the
158B**. The enclosing 151B `_Emplace` also remains SOURCE-PRESENT,
NONEXACT (130B/44 C++20 vs 151B/51 native, seven vs eight E8).
Their genuine original **118B guard destructor** and its actual
five 0xCC alignment bytes are separately
[whole strict exact](GLYPH_QUEUE_NODE_GUARD118_STRICT_EXACT.md), as
are the 34B/47B allocation children and other native PMR allocator
methods. No child exact bytes are incorrectly attributed to the
158B/151B original parent.

## Verification scope

This new source-presence checkpoint changes **no accepted native
function code**. Only the real queue source's documented function
ownership and notes change. The one affected original PMR list
provider is **locally** cold replayed, with all **11/11 complete
native exact child/guard units** unchanged. The
[`verify-glyph-queue-node-ctor158-native.py`](../scripts/verify-glyph-queue-node-ctor158-native.py)
script independently verifies the 158B original and the generated
143B candidate's E8 and DIR32 counts, without marking the shorter
candidate exact. No project-wide cold replay, fake no-op or emitted
assembly is used.

```sh
scripts/repo-python scripts/verify-glyph-queue-node-ctor158-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueList151.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
