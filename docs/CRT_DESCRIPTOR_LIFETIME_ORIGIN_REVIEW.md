# UCRT descriptor arrays, handle associations and error protocols

Eleven pending origins are reviewed and a three-byte finally entry is
recovered through ten complete Windows SDK 10.0.26100.0 x86 `libucrt.lib`
contributions. All 841 instruction bytes and the full 28B SEH table agree
with the locked Japanese TH20 v1.00a Steamless target. Descriptor-array
lifetime, OS-handle association, per-handle locks and global index locking
retain their distinct original responsibilities.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00555A57` | 61 | `_set_fmode` |
| `0x005597F1` | 39 | `_fileno` |
| `0x0055F967` | 123 | create lowio handle array |
| `0x0055F9E2` | 53 | destroy lowio handle array |
| `0x0055FA17` | 146 | ensure-fh primary |
| `0x0055FAA9` | 3 | recovered finally entry |
| `0x0055FAAC` | 9 | global index-lock unlock funclet |
| `0x0055FAB5` | 35 | per-handle lock |
| `0x0055FAD8` | 35 | per-handle unlock |
| `0x0055FAFB` | 145 | `_free_osfhnd` |
| `0x0055FB8C` | 106 | `_get_osfhandle` |
| `0x00563DCF` | 86 | `_isatty` |

The array/lock/association contributions fill `0x0055F967..0x0055FBF5`.
All existing instruction extents remain unchanged. The 146B ensure-fh primary,
3B prefix and existing 9B unlock form its complete 158B SDK section. The
original NOP inside fileno at `0x00559815` remains an instruction in its 39B
body. There is no owned trailing alignment.

## Array geometry, initialization and retirement

Creation calloc-allocates 64 records of 56B each, a full 0xE00B block. Each
record starts with its critical section; osfhnd is at +0x18, the 64-bit
start position at +0x20, attributes at +0x28 and text mode at +0x29.
The three lookahead bytes follow, with bit flags at +0x2D and the five-byte
multibyte buffer at +0x2E. The allocation also retains the structure's original
zeroed padding.

Every record initializes its critical section with spin count 4000 and flags
zero through the already reviewed InitializeCriticalSectionEx adapter. Its
return value is ignored. The owner assigns invalid OS handle -1, zero start
position/attributes, ANSI mode, three LF lookahead bytes, cleared conversion
bits and five zero buffer bytes. The original final free-of-null from detached
heap ownership remains on both allocation-failure and success paths.

Retirement returns for null; otherwise it deletes all 64 critical sections and
frees the block. It does not close the associated OS handles. Constructor and
destructor preserve the same 56B stride and complete allocation extent.

## Expansion, recovered finally prefix and lock identities

Ensure-fh rejects unsigned handles at least 8192, including negative inputs,
with EBADF/9 and the returning invalid-parameter handler. Valid input enters
global lowio index lock 7. Starting at array index zero, it skips existing
array pointers until the handle is covered by `_nhandle`. Each newly created
array is published into `__pioinfo` and adds 64 to `_nhandle`. Allocation
failure returns ENOMEM/12 while retaining prior successfully published arrays.
The routine does not roll back partial expansion or reserve one descriptor.

The full SEH table at `0x005AC640` has the original header `-2,0,-48,0` and
record `-2,0,0x0055FAA9`. That target reloads ESI from the parent frame before
falling into the existing 9B global-lock unlock. Normal completion calls the
9B entry directly. Ghidra omits the three-byte prefix; pinned decoding and the
whole SDK comparison cover it without changing the database.

The two 35B per-handle helpers calculate array index `fh >> 6` and record offset
`(fh & 63) * 56`, then call EnterCriticalSection or LeaveCriticalSection on
that record. They add no validation. Their ordinary bytes are identical after
relocations are masked; real PE import names distinguish lock from unlock and
reject swapping them. They are separate from the global lock-7 finally owner.

## Handle lookup, reset and sentinel-specific errors

The observed external pointer array is at `0x005E5690`, with `_nhandle` at
`0x005E5890`. These are named dependencies in the compared SDK members, not
locally owned state sections or new canonical bindings in this review.

`_get_osfhandle` checks the -2 no-console sentinel first, then range and FOPEN.
A valid entry returns its raw 32-bit handle at +0x18, including -1 if that
value remains in an otherwise open entry. No further OS validation or lock
is added. `_isatty` tests only range and attributes & FDEV/0x40; it has no
FOPEN test and returns the raw flag bit rather than normalized true.

`_free_osfhnd` requires valid range, FOPEN and an association other than -1.
For console app type, descriptors 0/1/2 call SetStdHandle with the matching
standard-stream ID and null handle. The API result is ignored. The routine
then writes -1 to the association and returns zero. It neither invokes
CloseHandle nor clears FOPEN. Its source comment's general description of
freeing a descriptor must not replace these actual stores.

| Failure input/path | Return | errno | Explicit doserrno write | Invalid-parameter call |
| --- | ---: | ---: | --- | --- |
| fileno null stream | -1 | 22 | none | yes |
| isatty sentinel -2 | 0 | 9 | none | no |
| isatty other invalid range | 0 | 9 | none | yes |
| get_osfhandle sentinel -2 | -1 | 9 | zero | no |
| get_osfhandle bad range/closed | -1 | 9 | zero | yes |
| free_osfhnd bad association | -1 | 9 | zero | no |

Fileno otherwise returns the FILE object's raw integer descriptor at +0x10,
without additional stream-state checks. The reviewed errno/doserrno getters
and returning no-info dispatcher preserve the original paths in this table.

## Global default translation mode

Set_fmode accepts only TEXT/0x4000, BINARY/0x8000 and WTEXT/0x10000. Success
atomically exchanges the four-byte `_fmode` slot at `0x005E5994` and returns
zero, discarding the old mode. Other values set EINVAL/22, call the no-info
handler and return 22. The initializer and default global value are outside
this body; a loader-zero slot is not treated as a configured runtime mode.

## Evidence and affected scope

Private `.analysis/origin-boundary/wide-stdio/` retains `fileno.obj`,
`isatty.obj`, `osfinfo.obj` and `setmode.obj`, bounded attested listings,
`review.py` and `reviewed.json`. The audit compares ten whole code sections,
twelve disjoint entries, the complete scope table, every branch/relocation,
all four PE import identities and the same-shaped lock negative case.
Source is `ucrt/stdio/fileno.cpp`, `ucrt/lowio/{isatty,osfinfo,setmode}.cpp`
and `corecrt_internal{,_lowio}.h`; compiled lock-helper definitions are retained
in the complete SDK member. Query-app-type and unreviewed allocation/stdio
wrappers receive no body credit from their named call roles.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
