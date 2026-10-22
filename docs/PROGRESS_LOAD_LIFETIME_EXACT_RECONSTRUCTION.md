# Complete progress loading and SaveManager destruction

CORE/EXACT-128 accepts two complete authored roots from fresh locked MSVC x86
production objects:

| Native entry | Maintained owner | Body bytes | Compared bytes | Relocations |
| --- | --- | ---: | ---: | ---: |
| `0050F3B0` | ProgressSaveManager::load | 562 | 562 | 33 |
| `0050E990` | ProgressSaveManager::~ProgressSaveManager | 299 | 304 | 13 |

The complete control flow has 161 and 81 instruction heads respectively. All
direct branch destinations remain inside the reviewed bodies, and the final
returns agree with the attested Ghidra listing and locked PE. The load object's
contribution ends at its return; the following fourteen linker-fill bytes are
outside its unit. The destructor retains all five trailing compiler-emitted
`CC` bytes through `0050EABF`, before the next entry at `0050EAC0`.

## Source and compiler observations

The maintained load body removes two one-use Profile pointer locals. It calls
initialize directly through the same complete Snapshot byte view. This preserves
both two-by-ten physical visits: row 0's tenth visit reaches row 1's first value,
and row 1's tenth visit reaches fallback. No out-of-array Profile subscript,
new field, alternate source body or inert local is introduced.

Under the existing C++20 profile this natural expression emits 562 bytes, with
54 differences outside relocation fields. Adding `/sdl` to this source's profile
produces the native local-variable placement and zero differences. The native
guard is at EBP-0x14, path at -0x2C, narrow string at -0x44, saved receiver at
-0x48, loop counters at -0x4C/-0x50/-0x54/-0x58, input path at -0x5C and
temporary string at -0x78.
Both EH cookie checks and the ordinary return cookie check agree. The per-source
profile records this reproducible compiler result; it does not establish the
whole game's original compiler flags. Worker still uses actual std::jthread and
requires C++20; the ECL buffer's earlier C++17 result is not generalized here.

The destructor's production source is unchanged. Its earlier 304/native299
size-only rejection was incorrect: the complete contribution contains the
299-byte body and five alignment bytes, all present in the target. The canonical
unit uses size 299 and compare_size 304. No compared extent is shortened, and no
source padding is added. Constructor 198/native199 and commit 68/native70 remain
whole nonexact because of unresolved post-call NOP differences. `/sdl`, `/Z7`,
`/fp:strict` and `/Ob1` trials do not close those roots. Exactness of the
destructor does not transfer to its commit dependency.

## Independent relocation and exception evidence

Existing canonical owners establish Worker shutdown/destruction, resource reads,
record defaults, parser/merge, allocator/free, locks and diagnostics. The real
WindowState base remains `005B6758`; the load object's two directory references
retain their original COFF +89 addends. Whole NUL-terminated backup/current
filenames and the load-completion diagnostic independently identify their native
constants. No destination is obtained by solving the root field being compared.

Ten full SDK callee bodies, their actual argument/result flow, installed pinned
SDK definitions and earlier independent consumers establish lock_guard lifetime,
path construction/assignment/append/string conversion, narrow c_str/move
assignment/destruction and path destruction. Their library origins are recorded
separately. Structural agreement of these helpers is support evidence; this batch
adds no standalone SDK exact units or authored credit for them.

The complete 68-byte load EH code section has one independent native shape
match at `0056A940`. It contains all three cleanup functions, natural alignment
and the handler at `0056A95D`. Once cleanup identities are established, the full
60-byte state/FuncInfo section uniquely matches at `005AB680`; its FuncInfo is at
`005AB698`. All code and data relocations strictly replay. Ghidra's existing
listing omits the cleanup instructions preceding the handler; the full PE/COFF
section comparison retains those bytes without changing the database.

The destructor's complete 36-byte no-unwind-state FuncInfo uniquely matches at
`005A91B8`. Replaying independently anchored security-cookie/runtime/FuncInfo
references selects the shared complete 29-byte handler at `00567600` from nine
shape candidates. This discovery does not use either root handler field. EH
support receives no additional physical coverage.

The custom destructor explicitly commits, joins and releases/resets four actual
current/backup C-heap buffers before Worker destruction. This application-owned
orchestration establishes authored origin independently of byte identity. It
does not use array delete. Load's authored classification retains the previously
established score.cpp, custom record and game-lock evidence.
Original class and function spellings remain inferred.

## Validation and remaining boundaries

Only ProgressFileLoad and ProgressSaveManager receive fresh production objects;
the latter's existing copy/merge units are replayed with the new destructor.
All four affected canonical units pass complete relocation replay. No shared
header, layout, ABI or existing profile changes, so 160 other objects are reused.
The graph contains 846 disjoint units and 163,715 compared bytes; authored exact
coverage is separately 99 functions and 32,231 body bytes.

All 80 public tests pass in 290.447 seconds. Protected retirement removes twenty
replaced object/probe products totaling 1,251,382 bytes after archiving their
original SHA-bound inputs and immutable receipts. All 324 current object/receipt
hashes remain unchanged. Post-cleanup strict replay passes all 846 complete units
using existing objects, with zero compiler invocations.

Existing O2/UBSan integration fixtures exercise the real load/save/parse/defaults,
Worker, allocator and destructor bodies. Their domain includes backup-before-
current ordering, all physical defaults, complete synthetic encrypted packets,
reload/fallback, thread join and ordered four-buffer release. Startup storage,
native filesystem execution and actual game runtime remain independent open
boundaries. See the [file protocol](PROGRESS_FILE_IO_RECONSTRUCTION.md).

Private proof is retained in `.analysis/core128-independent-bindings.json`,
`core128-boundaries.json`, `core128-affected-exact-results.json` and bounded
attested exports. Historical trial sources and original SHA-bound inputs remain
private. Use the [handoff](RE_HANDOFF.md) and live ledgers for present acceptance.
