**CORE/RECON-1073 STATUS CORRECTION:** Original **118B native queue-node guard destructor** `0x00414350` is now [WHOLE 118/118 STRICT EXACT, including five native INT3 tail bytes in 123/123 full comparison](GLYPH_QUEUE_NODE_GUARD118_STRICT_EXACT.md). The prior 123B-vs-118B compiler-lowering hypothesis below misclassified genuine native alignment as executable function code. The 151B `_Emplace` and 158B node constructor remain NONEXACT.

# CORE/RECON-1061 — original 151B glyph queue list Emplace frontier and five whole-exact PMR list helpers

Immutable target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native `0x004131E0` is a **complete 151B/51-i386**
`std::pmr::list<std::function<void()>>` queue node-insertion body
(original SHA-256
`a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75`).
It is physically invoked by the now whole-exact 56B game-owned
`NativeGlyphQueueView::submit_4162f0` wrapper via original E8
`+0x2C`. The 151B native function is a standard-library template
implementation, not independently game-authored. It receives the
real list position/node pointer and a forwarded existing
`std::function<void()>` owner, reads native node count at `this+8`,
checks the genuine maximum-size bound, acquires the list allocator,
constructs a list-node emplacement guard, increments size, links the
new node before the original requested position and destroys the guard.

Its entire original code has exactly **eight E8/2 PE HIGHLOW**:

| Native E8 | Actual native destination |
| --- | --- |
| `+0x1F` | `0x00416270` genuine list `max_size` |
| `+0x30` | `0x00540ED5` genuine CRT `_Xlength_error` |
| `+0x39` | `0x0040F160` native PMR allocator getter |
| `+0x45` | `0x0040B280` original folded `std::_Unfancy` pointer |
| `+0x5B` | `0x00413000` complete 158B list-node emplacement constructor |
| `+0x74` | `0x00414EB0` original 124B `_Transfer_before` |
| `+0x7F` | `0x00414350` complete 118B emplacement guard destructor |
| `+0x8C` | `0x005429EE` original cookie check |

Original data fields: `+0x07 -> 0x005B25C0` security cookie and
`+0x2C -> 0x0056C8BC` list-too-long error text. It ends in the
actual native `ret 8`. These original physical values are read from
the immutable PE, **not solved by comparison with the candidate**.

## Five distinct original generic methods now whole strict exact

Using the actual C++ type `std::pmr::list<std::function<void()>>`, the
maintained [`src/GlyphTextQueueList151.cpp`](../src/GlyphTextQueueList151.cpp)
performs a meaningful `emplace(position, std::move(*std::_Unfancy(&task)))`
and exposes the equivalent append-at-end operation. The pinned MSVC
19.44 i386 C++20 compiler naturally generates five complete
standard-library methods that have **independently verified original
native heads** and original calling edges:

| Exact physical head | Whole native extent | Genuine independent original caller |
| --- | ---: | --- |
| `0x00416270` PMR list `max_size` | **59B/22 i386** | original 151B list Emplace E8 `+0x1F`; native four nested E8 to allocator/limits |
| `0x00414EB0` `_List_node_emplace_op2::_Transfer_before` | **124B/43 i386** | original 151B Emplace E8 `+0x74`; three genuine E8/two actual Win32 list-node linking calls, original cookie HIGHLOW |
| `0x00413F50` `_Alloc_construct_ptr` constructor | **34B/13 i386** | native 158B node construction E8 `+0x2F`; zero relocations |
| `0x00416240` `_Normal_allocator_traits::max_size` | **19B/8 i386** | original 59B list `max_size` E8 `+0x12`; one nested original E8 |
| `0x004142E0` `_Alloc_construct_ptr` destructor | **48B/20 i386** | original 118B node-emplace destructor E8 `+0x61`; one real PMR deallocation E8 |

The read-only
[`verify-glyph-queue-list-native.py`](../scripts/verify-glyph-queue-list-native.py)
independently pins all five whole original SHA-256 function bodies,
actual instruction bounds, native `ret` widths, all E8 targets,
physical HIGHLOW fields, and the genuine original parent E8 for each
helper. It also verifies the entire 151B original and the exact
56B game queue wrapper that calls it. The five original code extents
are all unique and had no earlier canonical match-unit owners.
One newly compiled canonical source object passes:

```text
glyph_queue_list_max_size_59: exact (59/59 bytes)
glyph_queue_list_transfer_124: exact (124/124 bytes)
glyph_queue_allocator_construct_34: exact (34/34 bytes)
glyph_queue_allocator_max_size_19: exact (19/19 bytes)
glyph_queue_allocator_destroy_48: exact (48/48 bytes)
Exact replay: 5/5 units, 1 cold objects
```

This adds **five complete generic STL native heads /284 distinct `.text`
bytes**, but none is credited as game-authored (`origin=unknown/review`).
No re-credit is given for the original 56B game bridge, folded 8B
`std::_Unfancy` or other already accepted PMR helpers.

## Original 151B native template remains NONEXACT

The real C++20 list insertion source naturally instantiates a complete
**130B/44-i386** `_Emplace` template with **seven E8/two DIR32**, not
the original 151B/51-i386 with **eight E8/two HIGHLOW**. The original
has one additional live `std::_Unfancy` pointer forwarding call inside
the original `_Emplace` flow and different intermediate stack/size
ownership. That is a real compiler-lowering frontier, not removable
padding. The original **151B** is therefore `SOURCE-PRESENT, NONEXACT`
in the ledger and has **zero whole-parent exact credit**. The original
158B node construct, 118B guard destructor and 2,227B game text core
are separate further source targets. No artificially shortened
comparison, invented native callback, opcode patch, or project-wide
cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-queue-list-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueList151.cpp
```

## CORE/RECON-1072 — five deeper native PMR list child methods exact

The original 151B `_Emplace` invokes physical 158B/118B node ctor/guard
dtor methods that themselves call
[five now WHOLE EXACT generic allocation/destruction functions](GLYPH_QUEUE_PMR_DESCENDANTS_47_58_59_17_16_STRICT_EXACT.md):
47B node allocation, 58B PMR allocator, 59B memory-resource allocation,
17B allocator-traits destroy and 16B std::destroy_at. All are genuine
independently original native heads, generated from this existing
source's real PMR list insertion; 10/10 scoped units are exact in one
canonical object, no code is re-credited, and the full 151B `_Emplace`
remains SOURCE-PRESENT/NONEXACT. The 158B/118B parent boundaries are
independently SHA-pinned, but are themselves not whole exact yet.
