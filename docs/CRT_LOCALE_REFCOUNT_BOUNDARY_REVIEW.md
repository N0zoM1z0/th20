# UCRT locale reference counts and complete update-thread ownership

Ten pending origins are reviewed and two compiler fragments are recovered.
The false 128B primary at `0x00560B88` is now a 93B primary partition of a
complete 129B owner. All eight Windows SDK 10.0.26100.0 x86 `libucrt.lib`
`locale_refcounting.obj` contributions agree with the locked Japanese TH20
v1.00a Steamless target: 921 instruction bytes, one INT3 and the full 28B SEH
table. The comparison retains the complete interval `0x005608BF..0x00560C58`.

## Complete entries and corrected partitions

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005608BF` | 125 | `__acrt_add_locale_ref` |
| `0x0056093C` | 328 | `__acrt_free_locale` |
| `0x00560A84` | 41 | LC_TIME add-reference |
| `0x00560AAD` | 49 | LC_TIME conditional retirement |
| `0x00560ADE` | 41 | LC_TIME release-reference |
| `0x00560B07` | 129 | `__acrt_release_locale_ref` |
| `0x00560B88` | 93 | update-thread primary, corrected from 128B |
| `0x00560BE5` | 3 | recovered finally entry |
| `0x00560BE8` | 9 | shared unlock funclet |
| `0x00560BF1` | 18 | shared return continuation |
| `0x00560C03` | 5 | recovered abort tail |
| `0x00560C09` | 80 | `_updatetlocinfoEx_nolock` |

The five update-thread code partitions total 128B; the INT3 at `0x00560C08`
completes its 129B SDK contribution. The old 128B ledger span overlapped the
existing unlock and return entries. All fragments now have disjoint extents,
without dropping any instruction, call, branch or alignment from the owner.
The 3B prefix and 5B abort tail are compiler partitions, not separate ordinary
C functions. No whole-owner exact credit is inferred from the split.

## Reference increments, decrements and static objects

The add owner requires nonnull locale data, while release explicitly returns
for null. Both update the main counter at +0x0C, each present lconv/ctype
counter, then all six narrow/wide category records and the LC_TIME reference.
Category-wide reference updates exclude the shared wide C string at
`0x005B2848`; narrow updates require both the string and counter pointers.
Neither reference owner frees the locale allocation itself.

The LC_TIME add/release helpers exclude null and the static C object at
`0x00599ED8`, returning `LONG_MAX` for both cases. Other objects use atomic XADD
on the counter at +0xB0 and return the new signed LONG count. These are not
boolean APIs. Conditional retirement reads the counter and only at zero calls
the time-data destructor followed by free_base, preserving both calls.

## Full destruction and allocation-base arithmetic

The 328B free owner preserves the compound lconv condition: the lconv pointer
must be nonnull, differ from static `__acrt_lconv_c` at `0x005B2660`, and have
a nonnull zero-valued international counter. Monetary and numeric cleanup
then each require their own nonnull zero-valued counters. The corresponding
subobjects, international counter and lconv allocation are released in the
original order.

Ctype cleanup requires its counter to be present and zero. It frees the ctype
allocation 254 bytes before `ctype1`, then the lower/upper map allocations at
their respective pointers minus 128 bytes, then the counter. The different
adjustments follow the original word/byte pointer widths and must be retained.

After conditional LC_TIME cleanup, all six categories preserve their individual
wide C-string and reference-count checks. Wide cleanup frees the counter and
the corresponding locale-name allocation; narrow cleanup frees its zero-ref
counter allocation rather than adding a separate free of the string pointer.
The locale-data structure itself is freed last. Monetary, numeric and time
destructor bodies remain separate pending providers.

## Pointer replacement and thread synchronization

The 80B `_updatetlocinfoEx_nolock` rejects null new-data or destination pointers
and returns immediately when the old and new pointers agree. Otherwise it
publishes the new pointer and adds its references before releasing the old
references. This ordering protects shared counters/resources. It frees old
data only if nonnull, now zero-ref and different from initial locale data at
`0x005B2788`, then returns the new pointer.

This differs from the 75B void helper in the
[PTD lifetime owner](CRT_PTD_FLS_ERRNO_ORIGIN_REVIEW.md), which performs the
construction/retirement replacement under its own caller protocol. Their
names, return conventions and order cannot be interchanged from a generic
locale-replacement interpretation.

The thread updater obtains required PTD and tests its own-locale flags against
the global mask at `0x005B29F8`. A zero intersection, or a missing locale
pointer, enters synchronization under lock 4. It passes the PTD locale slot
and current global locale at `0x005E5664` to the 80B replacement helper. A
nonnull result reaches the shared return; null reaches the complete abort
tail. A no-sync path with nonnull existing locale reaches that same return.

## Finally entry and complete scope table

The complete table at `0x005AC660` has the original `-2,0,-44,0` header and
`-2,0,0x00560BE5` record. Its pointer targets the missing three-byte
`MOV ESI,[EBP-0x1C]` prefix, which falls through to the existing 9B lock-4
unlock. Normal completion calls the unlock directly. The return continuation
restores the exception chain and parent frame; the cold call to abort remains
inside the original owner.

Ghidra omits the three prefix bytes from its instruction listing. Pinned
decoding and the full SDK/target comparison cover that gap, including the
scope pointer and full HIGHLOW sets. The retained old convex-span description
in the private report records why the primary extent changes; the complete
129B comparison and source contribution remain intact.

## Evidence and affected scope

Private `.analysis/origin-boundary/locale-refcount/` retains the SDK member,
bounded `native.txt` and `replacement-native.txt`, member locations, `review.py`
and `reviewed.json`. The audit compares eight whole code sections, complete
branch/callee/HIGHLOW roles, the original INT3, all twelve disjoint entry
partitions and the complete scope table. Static C objects, the current locale
slot and global mask are named external dependencies rather than locally
owned data contributions. Installed source is
`ucrt/locale/locale_refcounting.cpp`, with the synchronization predicate in
`ucrt/inc/corecrt_internal.h`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
