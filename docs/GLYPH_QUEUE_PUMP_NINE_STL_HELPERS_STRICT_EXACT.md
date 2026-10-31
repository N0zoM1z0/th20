# CORE/RECON-1076 — nine complete original std::function/PMR glyph queue helpers, 434B whole strict exact

Locked Japanese TH20 v1.00a Steamless target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned original **254B/74-i386 glyph queue dispatcher**
`0x00416140` is already independently WHOLE STRICT EXACT. It actually
checks a 12B PMR list's count, copies its front `std::function`,
erases the begin node, and invokes the callback under two game-owned
recursive locks. The resulting meaningful
[`GlyphTextQueuePump254.cpp`](../src/GlyphTextQueuePump254.cpp)
C++20 source naturally instantiates **nine further distinct whole
original STL/PMR physical function heads**. The original parent and
all its originally nested native E8 destinations are independently
SHA-pinned; none is inferred from a guessed compiler function name.

| Physical original head | Whole exact native code | Actual original native parent E8 | Native subtree |
| --- | ---: | --- | --- |
| `0x00414150` default `std::function<void()>` construction | **23B/11 i386** | game 254B pump `+0x72` | E8 to independently exact 25B `_Func_class` ctor `0x00413F80` |
| `0x00415600` `std::pmr::list<GlyphTask>::front` | **22B/11 i386** | pump `+0x80` | read true sentinel's first node and return task member at +8; no E8 |
| `0x00414540` `std::function<void()>::operator=(const&)` | **60B/22 i386** | pump `+0x89` | genuine 93B function copy, 26B swap below, existing 20B destructor |
| `0x004150B0` PMR task-list `begin()` | **63B/24 i386** | pump `+0x98` | folded pointer helper and distinct 33B iterator ctor below |
| `0x00415550` PMR task-list `erase` | **93B/34 i386** | pump `+0xAF` | 70B `_Unlinknode`, allocator getter, 93B node disposal frontier, 44B `_Make_iter` |
| `0x00413FD0` native `_List_iterator` constructor | **33B/15 i386** | 63B `begin` `+0x31` | native E8 `+0x12` to already exact folded iterator owner `0x00413FA0` |
| `0x00414F90` `_List_val::_Unlinknode` | **70B/27 i386** | 93B `erase` `+0x21` | native E8 `+0x0E` to already exact folded native 13B iterator orphan `0x0040EC90` |
| `0x00414B20` `list::_Make_iter` | **44B/18 i386** | 93B `erase` `+0x4F` | folded pointer helper and distinct 33B iterator ctor |
| `0x00417A90` `std::function<void()>::swap` | **26B/12 i386** | 60B function assignment `+0x25` | E8 `+0x0E` to separate original **188B** complex `_Func_class` swap Boss `0x00414C80`, not yet exact |

All **nine complete original physical extents have zero PE HIGHLOW**;
their authentic native E8 counts and destinations range from zero to
four and exactly match the naturally emitted compiler functions.
The read-only
[`verify-glyph-queue-pump-stl-nine-native.py`](../scripts/verify-glyph-queue-pump-stl-nine-native.py)
independently hashes all nine complete original bodies, checks every
original decoded native instruction and original E8 target, and
re-attests each genuine complete original parent (254B, 93B, 63B and
60B as appropriate) at its native physical call site. Distinct
physical code heads are counted only once, even when two different
C++ iterator instantiations naturally emit equal folded code.

All functions naturally compile from the same real game task-queue
source using pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The exactness is not a copy of original code bytes into nine fake
standalone functions, nor a hand-crafted `_List_node` layout:

```text
glyph_text_queue_pump_254: exact (254/254 bytes)
glyph_queue_func_default_ctor_23: exact (23/23 bytes)
glyph_queue_list_front_22: exact (22/22 bytes)
glyph_queue_func_copy_assign_60: exact (60/60 bytes)
glyph_queue_list_begin_63: exact (63/63 bytes)
glyph_queue_list_erase_93: exact (93/93 bytes)
glyph_queue_list_iterator_ctor_33: exact (33/33 bytes)
glyph_queue_list_unlinknode_70: exact (70/70 bytes)
glyph_queue_list_make_iter_44: exact (44/44 bytes)
glyph_queue_func_swap_26: exact (26/26 bytes)
Exact replay: 10/10 units, one affected cold object
```

These **nine newly accepted distinct STL methods cover 434 original
`.text` function bytes**, but `origin=unknown/disposition=review` is
retained throughout. Therefore this checkpoint contributes **zero
new game-authored heads/bytes**; the parent 254B pump's
already credited game-authored code, folded `std::function` helpers,
previous generic callback invocation, and all 151B insertion subtree
functions are not counted again. The original 93B `_List_node`
deallocation and original 188B complex function swap remain open
higher-value independent compiler frontiers; child exactness does
**not** make them exact. No global cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-queue-pump-stl-nine-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueuePump254.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1078 — separate original 188B callback swap frontier now sourced

The native 26B `std::function<void()>::swap` accepted here really calls a
[complete original 188B `std::_Func_class<void>::_Swap` body](GLYPH_FUNCTION_SWAP188_NATIVE_FRONTIER.md)
at native E8 `+0x0E`. The full original 188B/63 uses three extra
live folded `_Unfancy` E8 groups absent from the installed C++20 STL
161B/54 compiler source. The larger native 188B method is now
SOURCE-PRESENT, NONEXACT with its physical original SHA and complete
15-E8/one-HIGHLOW graph independently recorded. It receives no
original exact credit; the 26B wrapper, 60B assignment and native
254B TH20 queue pump stay separately whole exact.
