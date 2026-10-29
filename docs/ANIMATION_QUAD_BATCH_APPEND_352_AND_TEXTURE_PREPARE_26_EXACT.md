# CORE/RECON-806/807 — complete 352-byte renderer batch append and 26-byte texture-state wrapper, both strict exact

Original immutable Japanese TH20 v1.00a Steamless executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original **3,159-byte /763-x86** quad submit Boss at `0x0043F6A0`
calls two original custom game renderer methods: the entire **352B**
`0x0043E9B0` six-vertex buffer append and entire **26B** `0x00445BA0`
texture-state forwarding wrapper. Both are now natural maintained C++
strict-whole-native exact and physically distinct game code, totaling
**378 original .text bytes**. The enclosing original 3,159B parent remains
SOURCE-PRESENT but **NONEXACT**; original compiler/library and
backend code is never silently recredited.

## Entire 352B /98 native x86 append: actual six vertices and capacity guard

The original `0x0043E9B0..0x0043EB0F` checks actual live stream
`SpriteTexturedVertex*` at native renderer owner offset **`+0x07C00E74`**
against the genuine bounded backing vertex array at owner
**`+0x06000E74`**, indexed by **`0xFFFFA`** entries of 28-byte
`SpriteTexturedVertex` source layout. If the next six vertices cannot
fit, it returns integer 1 without changing the stream pointer or count.
If room remains, it performs exactly **six native `rep movsd` 7-dword
copies** in this real original order:

| Destination slot | Source slot | Purpose |
| ---: | --- | --- |
| 0 | incoming 0 | First triangle vertex |
| 3 | incoming 1 | Shared vertex for second triangle |
| 1 | newly written slot 3 | First triangle shared vertex |
| 4 | incoming 2 | Shared vertex for second triangle |
| 2 | newly written slot 4 | First triangle shared vertex |
| 5 | incoming 3 | Second triangle final vertex |

It then increases the actual stream cursor by **six 28B vertices
(168B/`0xA8`)** and increments the native queued primitive count at
owner **`+0x06000E70`**, returning integer 0. Every copy is naturally
represented as a typed `SpriteTexturedVertex` struct assignment; the
original x86 `rep movsd` from six whole POD records is not handwritten
or patched. There are **zero original PE HIGHLOW/data references and zero
original direct E8 call operands in this complete 352B body**.

An initial natural C++ version cached the stream pointer and folded the
queue-capacity test to a single constant, generating **274 bytes**. A
non-cached pointer-lvalue version generated **329 bytes**, differing only
in the original bound calculation. Independent native disassembly
established that the original x86 compiles two **array-index address
expressions**, `&live_stream[0]` and `&backing[0xFFFFA]` with an actual
28-byte `SpriteTexturedVertex` type. Under the exact pinned MSVC x86
compiler, expressing the genuine typed array indexing naturally emits
the two missing `imul` calculations and the original compare. The
result is **352/352 original executable bytes, 98/98 x86 heads**, all
six `rep movsd` copies, complete original `ret 4`, **zero differences**
without compiler knobs, assembler, NOPs, inert variables or a fictitious
130-MB padded renderer class.

Maintained source is `src/AnimationQuadBatchAppend.cpp`, receiver
`AnimationQuadSubmitOwner::append_quad(SpriteTexturedVertex*)` from shared
`src/AnimationQuadSubmitOwner.hpp`. The original provisional owner
spelling is not historical C++ name proof; method's actual ECX receiver,
`Animation*` caller, code and structure are native confirmed. A second
private, individually byte-identical source hypothesis was reviewed and
kept in ignored `.analysis/core807-append-reviewed-duplicate.cpp`;
**only one** canonical C++ source/symbol and original 352B address is
mapped. No duplicate authored physical byte credit is taken.

## Entire original 26B /12 native x86 texture state forwarding wrapper

The source `src/AnimationTexturePrepare.cpp` uses that *same* local
`AnimationQuadSubmitOwner` receiver, rather than a second fictitious
renderer type, and simply forwards actual `Animation*` to the separate
2,725-byte original texture-state backend at **`0x00445BC0`**. The
original wrapper at **`0x00445BA0`** is exactly 26 native bytes/12
instruction heads; its only native relocation is the original signed
`E8` displacement at **`+0x0F`** (instruction at `0x00445BAE`),
independently resolving to **`0x00445BC0`**. The call's subsequent
native `NOP`, true `ret 4`, and entire 26B extent are reproduced by
ordinary MSVC C++ method codegen. There are **zero original PE HIGHLOW
fields** inside this wrapper. Its 2,725-byte called backend remains
separately unsourced/NONEXACT and receives no new source or byte credit.

## Narrow strict-native acceptance and counts

Both source methods compile with pinned MSVC **19.44.35211 x86**,
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, into two
new independent canonical COFF object/receipt providers:

- `animation_quad_append_six_vertices_352`,
  `build/core806-canonical/AnimationQuadBatchAppend.obj` — **352/352B strict**.
- `animation_quad_texture_prepare_26`,
  `build/core807-canonical/AnimationTexturePrepare.obj` — **26/26B strict**,
  one real target-matched native E8.

The actual receipt-validated changed-only replay is:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadBatchAppend.cpp --source src/AnimationTexturePrepare.cpp
    scripts/repo-python scripts/verify-animation-quad-submit-native.py

**2/2 whole strict functions exact across exactly two new cold objects**.
The shared receiver header previously existed only as uncommitted new
source for the 3,159B NONEXACT candidate; its declarations were
reconciled across both accepted leaf C++ methods and the still-unaccepted
parent before replay. No previously accepted shared header, old exact
translation unit or protected object/profile changed; replay scope is
**two new units, zero older accepted units**. There was no unfiltered
full cold replay. The source-present parent method `render_quad` was
recompiled only as a disposable one-object probe, not given exact credit.

Previously accepted game authored whole-native strict coverage was
**584 distinct functions /189,186 original bytes**. The new two distinct
game-authored methods add **378B**, producing **586 /189,564 original
game bytes**. Source-present mapping **1,231 →1,233**, configured
canonical units **1,231 →1,233**, distinct accepted object providers
**254 →256**. The original 3,159B quad submission and 5,993B Animation
draw Boss remain SOURCE-PRESENT/NONEXACT; the 12,140B Bullet command,
41,967B Enemy ECL and 39,470B VM remain separate NONEXACT giants.
Neither unit-level byte equality nor call mapping establishes
whole-game linkage or a runnable replacement executable.
