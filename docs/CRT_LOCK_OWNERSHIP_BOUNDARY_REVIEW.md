# CRT lock ownership and the false 66,925-byte destructor span

`0x005419AC` owns the complete 31-byte STL `_Lockit` destructor. Its conditional
branch transfers to the separate nine-byte UCRT `_unlock_locales` function at
`0x00551F10`. The initial Ghidra inventory merged those two ranges into a
66,925-byte convex span. The corrected ledger retains both full bodies as
independent entries and preserves the cross-function tail edge.

The review classifies eighteen lock/lifetime entries totaling 474 code bytes:
eleven existing candidates and seven previously omitted entries. Thirteen
missing entries are added to the inventory in total; six adjacent startup/exit
callbacks were retained pending and are now [resolved by the retirement review](CRT_GLOBAL_RETIREMENT_ORIGIN_REVIEW.md). The target remains the locked Japanese TH20
v1.00a Steamless file, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Independent function boundaries

The installed MSVC 14.44.35207 `libcpmt.lib` member `xlock.obj` defines a complete
31-byte `std::_Lockit::~_Lockit` contribution. Its conditional branch has a
REL32 relocation naming `_unlock_locales`. The same member names the separate
STL mutex table and `_Mtxunlock` call. UCRT `libucrt.lib` member `locks.obj`
defines the complete nine-byte `_unlock_locales` function and names its
`__acrt_unlock` call. Both complete contributions agree with the original
ordinary bytes; the decoded native destinations agree with these independent
roles. No branch path or far-end code is discarded.

Ghidra's read-only database still reports forty body addresses spanning the two
routines. That observation is preserved in the private queries; the reviewed
ledger follows the independently evidenced original object partition. The
66,885 intervening bytes were never owned by this destructor. Neither the
thirty-one-byte main body alone nor an artificial forty-byte contiguous extent
would represent the original complete protocol without the separate callee.

| Entry | Bytes | Operation | Origin |
| --- | ---: | --- | --- |
| 0x0040AEBA | 22 | `Lock lifetime initializer` | compiler |
| 0x0040AEF4 | 22 | `Lock lifetime initializer` | compiler |
| 0x00541927 | 45 | `??0_Init_locks@std@@QAE@XZ` | library |
| 0x00541954 | 49 | `??0_Lockit@std@@QAE@H@Z` | library |
| 0x00541985 | 39 | `??1_Init_locks@std@@QAE@XZ` | library |
| 0x005419AC | 31 | `??1_Lockit@std@@QAE@XZ` | library |
| 0x00542480 | 14 | `__Mtxdst` | library |
| 0x0054248E | 21 | `__Mtxinit` | library |
| 0x005424A3 | 14 | `__Mtxlock` | library |
| 0x005424B1 | 14 | `__Mtxunlock` | library |
| 0x00551E62 | 65 | `___acrt_initialize_locks` | library |
| 0x00551EA3 | 23 | `___acrt_lock` | library |
| 0x00551EBA | 49 | `___acrt_uninitialize_locks` | library |
| 0x00551EEB | 23 | `___acrt_unlock` | library |
| 0x00551F02 | 14 | `__lock_locales` | library |
| 0x00551F10 | 9 | `__unlock_locales` | library |
| 0x0056B449 | 10 | `Lock lifetime exit invoker` | compiler |
| 0x0056B471 | 10 | `Lock lifetime exit invoker` | compiler |

## Two lock pools and their lifecycle

The STL pool occupies `0x005E4D40..0x005E4DFF`: eight 24-byte critical sections.
The reference counter at `0x005B257C` starts at -1. `_Init_locks` construction
uses an interlocked increment and initializes the pool only when the new count
is zero. Destruction decrements the same counter and destroys the eight locks
only when the result is negative. Both loops advance by 24 bytes to
`0x005E4E00`. The direct mutex wrappers independently identify the imported
Initialize/Delete/Enter/LeaveCriticalSection APIs. Initialization passes spin
count 4000 and flags zero; the STL void wrapper does not test the API result.

The UCRT pool instead occupies `0x005E5320..0x005E5487`: fifteen critical
sections. Its initialization loop records each successful lock in the counter
at `0x005E5488`. A failed initialization invokes cleanup and returns false.
Cleanup destroys only the initialized prefix, in reverse order, decrementing
the counter after each deletion. The original wrapper takes the existing
terminating argument even though this body ignores it.

`_Lockit` kind zero routes through `_lock_locales` / `_unlock_locales`, which
use **UCRT lock index 4**. Other kinds use the STL pool when the original signed
comparison is less than eight. The native branch has no separate nonnegative
check. The locale lock first eagerly loads locale APIs before acquiring the
lock; unlock has no corresponding load step. These distinctions must survive
later reconstruction.

## Startup registration and omitted entries

Original table slots `0x0056C38C` and `0x0056C390` reference the two 22-byte
initializers. They construct receivers at `0x005E4D38` and `0x005E4EA0`, both
through `0x00541927`, then register exit invokers at `0x0056B449` and
`0x0056B471` through the original `atexit`. Each invoker restores its matching
receiver in ECX and tail-transfers to `0x00541985`.

The complete compiler-generated startup/exit contributions in `xlock.obj` and
its `.CRT$XCC` registration corroborate this shape. Both native pairs preserve
receiver identity. Their original translation-unit spelling remains unresolved;
the ledger uses descriptive lifetime names. The shared cleanup bytes also agree
with the library's alternate static `_Init_locks_dtor` helper, so the native
roles do not identify every folded contributor.

Six further omitted entries were retained pending at this checkpoint:

| Registration entry | Exit invoker | Receiver | Cleanup destination |
| --- | --- | --- | --- |
| `0x0040AED0` | `0x0056B453` | `0x005E4E28` | `0x00541A42` |
| `0x0040AEDC` | `0x0056B45D` | `0x005E4E1C` | `0x004F5600` |
| `0x0040AEE8` | `0x0056B467` | `0x005E4EA1` | `0x005424BF` |

Each registration body is twelve bytes and each exit invoker is ten. Actual CRT
initialization-table references and `atexit` arguments establish these heads;
complete listings preserve their terminal RET or external JMP. Their original object
owners are now identified as facet cleanup, classic locale and the STL exit
controller; the [retirement review](CRT_GLOBAL_RETIREMENT_ORIGIN_REVIEW.md)
supplies their complete source and object evidence.

## Evidence, useful negative controls and validation

Private evidence remains under `.analysis/origin-boundary/locks*`. The complete
listings are `locks-native.txt`, `locks-context.txt`, `locks-init-and-tail.txt`,
`locks-static-init.txt` and `locks-static-dtors.txt`. The two xref exports bind
startup-table slots, `atexit` arguments and the far conditional branch.
`locks/reviewed.json` records full member sizes, hashes and relocation roles.
The installed `xlock.cpp`, `xmtx.cpp` and UCRT `internal/locks.cpp` corroborate
the branches, counts and lifetimes.

A masked opcode search alone is insufficient here. The three fourteen-byte
Delete/Enter/Leave wrappers have identical ordinary bytes and differ in their
import operands. A nine-byte suffix inside `_lock_locales` resembles
`_unlock_locales` but calls `__acrt_lock` instead of `__acrt_unlock`. Short
startup fragments also resemble an unrelated `_Lockit_ctor` helper after
relocation masking. The review admits full object contributions only after
checking imports, shared symbol roles, native references and receiver pairing.
The bounded locator and whole-contribution audit are retained privately.

All eighteen admitted bodies have complete attested instruction coverage and
whole-object ordinary-byte agreement. Original DIR32 fields have PE HIGHLOW
entries, and the original import descriptors identify every direct SDK wrapper.
Tracking and generated progress pass. Protected source, headers, canonical
objects/receipts and manifests retain their captured hashes. The corrected and
new entries own no canonical units, and existing native callee addresses are
unchanged: the exact replay scope is **zero units**. Source presence and exact
credit remain unchanged.
