**CORE/RECON-1073 CURRENT STATUS:** The original 118B queue-node guard destructor `0x00414350` is now [WHOLE STRICT EXACT](GLYPH_QUEUE_NODE_GUARD118_STRICT_EXACT.md). The previously suspected 5B surplus in its 123B generated COFF object is exactly five original native `INT3` alignment bytes after the genuine 118B return, not an incomplete source method. The original 151B list `_Emplace` and 158B node constructor remain NONEXACT; earlier 118B-NONEXACT statements below are historical.

# CORE/RECON-1072 — five whole-exact original PMR glyph queue allocation and destruction descendants

Locked Japanese TH20 Steamless v1.00a target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The genuine original **151B/51-instruction**
`std::pmr::list<std::function<void()>>::_Emplace` at `0x004131E0`
remains **SOURCE-PRESENT, NONEXACT** (modern MSVC source 130B/44). Its
original physical E8 `+0x5B` calls the **158B/51-i386** node-emplace
constructor `0x00413000`, and original E8 `+0x7F` calls the
**118B/41-i386** emplacement-guard destructor `0x00414350`. Those
larger two STL template functions also remain individually NONEXACT.

Following actual original native E8 edges below these larger original
functions, five further *distinct complete original code heads* are
naturally generated from the **same** meaningful
[`src/GlyphTextQueueList151.cpp`](../src/GlyphTextQueueList151.cpp)
source, which genuinely inserts an existing queued
`std::function<void()>` into a PMR-allocated `std::list`.

| Original physical head | Whole original native function | Native physical parent and true E8 |
| --- | ---: | --- |
| `0x004148D0` node `_Alloc_construct_ptr::_Allocate` | **47B/17 i386** | native 158B node ctor `0x00413000` E8 `+0x3E`; sole child E8 `+0x20 -> 0x00414FF0` |
| `0x00414FF0` `polymorphic_allocator<ListNode>::allocate` | **58B/22 i386** | 47B `_Allocate` E8 `+0x20`; native E8 `+0x15 -> 0x00413730` size conversion, `+0x29 -> 0x00415070` memory resource |
| `0x00415070` `std::pmr::memory_resource::allocate` | **59B/24 i386** | 58B PMR node allocator E8 `+0x29`; sole native E8 `+0x2D -> 0x0040E700` aligned allocation path |
| `0x00413CA0` `_Normal_allocator_traits<ListNode>::destroy` | **17B/8 i386** | native 118B guard dtor `0x00414350` E8 `+0x56`; sole E8 `+0x07 -> 0x00413CC0` |
| `0x00413CC0` `std::destroy_at<std::function<void()>>` | **16B/8 i386** | native 17B allocator-traits destroy E8 `+0x07`; native E8 `+0x08 -> 0x004147B0` function scalar-deleting destructor |

All five original bodies have **zero genuine PE HIGHLOW fields**.
The exact native complete SHA-256, every instruction boundary and
native E8 destination are independently pinned by
[`verify-glyph-queue-pmr-descendants-native.py`](../scripts/verify-glyph-queue-pmr-descendants-native.py).
The proof also SHA-pins the full original 158B node constructor
`5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b`,
118B guard destructor
`2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52`,
and 151B `_Emplace`
`a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75`.
The original child chain is established from the locked PE, not
post-hoc from a generated COFF relocation.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
rebuilds just the existing queue-list source owner:

```text
glyph_queue_list_max_size_59: exact (59/59 bytes)
glyph_queue_list_transfer_124: exact (124/124 bytes)
glyph_queue_allocator_construct_34: exact (34/34 bytes)
glyph_queue_allocator_max_size_19: exact (19/19 bytes)
glyph_queue_allocator_destroy_48: exact (48/48 bytes)
glyph_queue_node_allocator_allocate_47: exact (47/47 bytes)
glyph_queue_pmr_node_allocate_58: exact (58/58 bytes)
glyph_queue_memory_resource_allocate_59: exact (59/59 bytes)
glyph_queue_allocator_destroy_17: exact (17/17 bytes)
glyph_queue_function_destroy_at_16: exact (16/16 bytes)
Exact replay: 10/10 units, 1 cold object
```

The five newly admitted original heads cover **197 distinct original
`.text` bytes**. All are generic STL/PMR methods with
`origin=unknown, disposition=review`; **zero new game-authored
head/byte credit**. The previously accepted five list helpers, folded
26B callable and all other game-authored functions are not counted
again. The genuine 151B/158B/118B parents remain NONEXACT and
receive **no** transitive exact credit. No full-project cold replay
was used, and no target bytes, guessed machine-code padding or
hand-written fake library wrappers were introduced.

```sh
scripts/repo-python scripts/verify-glyph-queue-pmr-descendants-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueList151.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
