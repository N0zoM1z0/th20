# UCRT multibyte synchronization and corrected thread-update ownership

Eleven pending origins are reviewed and two compiler fragments are recovered.
The overlapping 159B primary at `0x0055ED36` becomes a 124B primary partition
of its complete 160B owner. Eight Windows SDK 10.0.26100.0 x86 `libucrt.lib`
`mbctype.obj` contributions agree with the locked Japanese TH20 v1.00a
Steamless target: 1,041 instruction bytes, one INT3 and 1,130B of owned
state, default tables and SEH metadata. Reference ordering, original error
branches and the initializer's unconditional true result are retained.

## Complete contributions and disjoint partitions

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0054FC8E` | 129 | local inline `memcpy_s` contribution |
| `0x0055E85A` | 65 | guarded global-publication primary |
| `0x0055E89B` | 12 | publication finally/unlock funclet |
| `0x0055E8A7` | 131 | global-publication lambda |
| `0x0055E968` | 113 | `getSystemCP` |
| `0x0055EBE1` | 341 | `setmbcp_internal` |
| `0x0055ED36` | 124 | thread-update primary, corrected from 159B |
| `0x0055EDB2` | 3 | recovered finally prefix |
| `0x0055EDB5` | 9 | shared lock-5 unlock funclet |
| `0x0055EDBE` | 18 | shared return continuation |
| `0x0055EDD0` | 5 | recovered abort tail |
| `0x0055EDD6` | 72 | `__acrt_initialize_multibyte` |
| `0x0055EE1E` | 19 | `__acrt_update_thread_multibyte_data` |

The updater's five code partitions total 159B. Its original INT3 at
`0x0055EDD5` completes the 160B SDK contribution. The former 159B ledger
span overlapped the existing unlock and return entries; the corrected primary
retains all instructions through the separately recorded fragments.

The guarded publication is one complete 77B contribution split into the
existing 65B primary and 12B finally entry. Ordinary bytes locate this generic
guard at three native heads. Its actual action at `0x0055E8A7` and scope
metadata distinguish this owner from the other two candidates. The thiscall
entry pops its three explicit pointer arguments. Its finally fragment reads
the cleanup capture from the parent frame, rather than exposing an independent
public C interface.

## Synchronization and reference order

The 19B cdecl wrapper obtains required PTD and passes the address of the current
multibyte pointer at `0x005E596C` to the internal updater. PTD multibyte and
locale pointers are at +0x48 and +0x4C, with own-locale flags at +0x350.
A zero intersection with the mask at `0x005B29F8` permits synchronization.
A missing **locale** pointer also forces synchronization, even when the flags
would ordinarily prevent it.

Under lock 5, unequal old/current multibyte pointers cause an atomic decrement
of the old reference. A zero result frees old data unless it is the static
initial object at `0x005B2A00`. The updater then publishes the current pointer
into PTD and increments its reference. Equal pointers skip these changes.
The no-sync path retains existing PTD multibyte data. After unlocking, a null
final result reaches the original abort tail; a nonnull pointer reaches the
shared return continuation.

This release-before-publication sequence differs from the
[locale replacement helper's add-before-release order](CRT_LOCALE_REFCOUNT_BOUNDARY_REVIEW.md).
Their contracts must remain distinct. This completes the updater body used by
the [refresh helpers](CRT_LOCALE_REFRESH_CONVERSION_ORIGIN_REVIEW.md).

## Code-page selection, allocation and global publication

`getSystemCP` constructs the reviewed legacy locale guard with null supplied
locale and resets `fSystemSet` at `0x005E5970`. Requests -2, -3 and -4 set the
flag and select GetOEMCP, GetACP or the guarded locale's code page respectively.
Other integer requests pass through unchanged. The guard's own-locale bit is
restored on every exit. PE imports at `0x0056C09C` and `0x0056C0A0` independently
identify GetOEMCP and GetACP.

`setmbcp_internal` first synchronizes thread data, resolves the request and
returns zero immediately if the code page already agrees. Otherwise it
allocates 544B and copies the complete existing structure through an original
544B stack temporary, retaining both REP MOVSD transfers. It resets the new
reference count to zero before calling `_setmbcp_nolock` at `0x0055EE31`.
Allocation failure returns -1 and retains the emitted free of null. A
population result of -1 sets errno to EINVAL/22, frees the candidate and
returns -1.

On success, a non-initialization call marks the locale changed. The setter
decrements and conditionally frees old thread data, gives the new object
reference count one and installs it in PTD. If synchronization is disabled,
it returns the population status without global publication. Otherwise the
guarded action under lock 5 copies all 257 ctype bytes and 256 casemap bytes
from PTD into the global arrays through `memcpy_s`. Both copy results are
ignored. It then decrements and conditionally frees old global data, publishes
the PTD pointer globally and increments its reference. Initialization updates
the initial-locale multibyte pointer only after this global-sync path.
The detached candidate's final free-of-null remains in the original body.

The 72B initializer installs the static initial/current data and default table
pointers, obtains PTD head and calls the setter with request -3 and the
initialization flag true. It ignores that return value, writes its initialized
byte at `0x005E5974` and returns true in AL, including when the setter failed.
Later calls also return true. The native body selects one global state; the
source's conditional two-state mode is not introduced here.

## Secure copy, complete tables and SEH

The complete 129B inline `memcpy_s` returns zero for zero source count before
checking pointers. For nonzero count, a null destination reports EINVAL.
A null source or insufficient destination size first clears the entire supplied
destination size, then reports EINVAL for null source before considering
ERANGE/34 for insufficient size. Successful copying delegates to memcpy.
The original fallback EINVAL return remains, and there is no overlap check.
The reviewed returning invalid-parameter dispatcher is retained as a callee.

The owned data closure is complete:

| Address | Bytes | Contribution |
| --- | ---: | --- |
| `0x005B2A00` | 544 | initial multibyte data, including ctype/casemap fields |
| `0x005B2C20` | 257 | default global ctype array |
| `0x005B2D28` | 256 | default global casemap array |
| `0x005E5964` | 16 | three global pointers and `fSystemSet`, loader-zero state |
| `0x005E5974` | 1 | initialized flag, loader-zero state |
| `0x005AC600` | 28 | updater SEH table, finally target `0x0055EDB2` |
| `0x005AC620` | 28 | publication SEH table, finally target `0x0055E89B` |

The initial object's ctype/casemap fields equal the complete standalone default
arrays. All 1,130B, both full relocation sets and eleven intervening linker
zero-alignment bytes agree. The updater table has frame offset -44; publication
has -40. Ghidra omits the three-byte `MOV ESI,[EBP-0x1C]` finally prefix;
pinned decoding and the full SDK comparison cover it without mutating the
database. Neither scope table is truncated to its handler pointer.

## Evidence and affected scope

Private `.analysis/origin-boundary/multibyte-update/` retains `mbctype.obj`,
the locator, bounded attested native/helper/copy listings, `review.py` and
`reviewed.json`. The audit covers all eight whole code sections, thirteen
disjoint entries, complete branches/HIGHLOW/callee/import roles, all seven
owned data sections and the same-shaped guard negative cases. Source context
is `ucrt/mbstring/mbctype.cpp`, `corecrt_internal.h`, `corecrt_memcpy_s.h` and
the compiler's `crt/src/vcruntime/internal_shared.h`.

The [complete population review](CRT_MULTIBYTE_POPULATION_ORIGIN_REVIEW.md)
now covers `_setmbcp_nolock`, its code-page tables and population helpers,
including the original six-byte UTF-8 ctype reset. Memcpy/memset and the
locale-changed setter remain separate pending bodies. Named call roles give
those bodies no review credit here. Only classification, focused evidence,
handoff and generated progress change. All 2,151 protected native input/product
hashes remain unchanged. Exact replay scope is **zero units**, with no new
authored or maintained-source exact credit.
