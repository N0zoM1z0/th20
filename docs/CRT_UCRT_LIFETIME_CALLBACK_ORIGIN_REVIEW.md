# UCRT lifetime roots, static callbacks and encoded-null initialization

Ten library entries are reviewed through complete Windows SDK 10.0.26100.0
x86 `libucrt.lib` member `initialization.obj` contributions: 317 code bytes and
the existing full 128B initializer table. Six heads were missing from the
provisional function ledger. The target is the locked Japanese TH20 v1.00a
Steamless executable; the native source graph and exact unit graph are unchanged.

| Entry | Bytes | SDK operation | Ledger head |
| --- | ---: | --- | --- |
| `0x005538BF` | 13 | `initialize_global_variables` | recovered |
| `0x005538CC` | 26 | `initialize_c` | recovered |
| `0x005538E6` | 8 | `uninitialize_environment` | recovered |
| `0x005538EE` | 46 | `initialize_pointers` | recovered |
| `0x0055391C` | 9 | `uninitialize_vcruntime` | recovered |
| `0x00553925` | 23 | `uninitialize_allocated_memory` | existing |
| `0x0055393C` | 80 | `uninitialize_allocated_io_buffers` | recovered |
| `0x0055398C` | 46 | multibyte retirement lambda | existing |
| `0x005539BA` | 18 | `__acrt_initialize` | existing |
| `0x005539CC` | 48 | `__acrt_uninitialize` | existing |

The ten contributions fill `0x005538BF..0x005539FB` contiguously, 317B
without gaps or alignment. Each complete archive contribution ends at its
original return. Full ordinary bytes, HIGHLOW sets and local branch targets
agree. The earlier eleven-byte thread-attach assignment at `0x00558390` was
incorrect and is superseded by the
[complete API cache identity proof](CRT_WINAPI_THUNK_CACHE_ORIGIN_REVIEW.md).

## Paired table and static-CRT callbacks

The [already reviewed initializer table and executors](CRT_HEAP_LIFECYCLE_EXPAND_ORIGIN_REVIEW.md)
give independent roles to the short callbacks. The root initializer passes
`0x00599410` and `0x00599490`, the full sixteen-record range, to the forward
executor at `0x0055F686`. Its original E8 is at `0x005539C4`. Normal retirement
passes those same bounds to the reverse executor at `0x0055F6EE`, with E8 at
`0x005539F3`. The complete table still has 25 pointer fields and seven null
fields; this review reuses its retained proof rather than changing that record.

`initialize_global_variables` publishes `__acrt_initial_locale_data` through
the current-locale slot and returns true in AL. `initialize_c` initializes the
normal and quick-exit onexit tables and returns true; this contribution matches
the source's non-CRTDLL branch, with no `_initterm`/`_initterm_e` calls. This
identifies the selected owner variant, not a compiler profile for the whole game.

Five source callback roles share the already reviewed three-byte true return
at `0x00543D2F`: environment initialization, C uninitialization, global-state
isolation initialization/uninitialization, and the release-build leak-report
stub. Their original table fields establish those aliases. No extra physical
heads or duplicate byte credit are added. Other three-byte true returns inside
the dense callback region are not assigned standalone ownership without an
original entry reference.

## The missing matherr caller and encoded null

The complete `initialize_pointers` body loads the security cookie at
`0x005B25C0` into ESI, then supplies that same value to the invalid-parameter,
new-handler, signal-handler, user-matherr and thread-local-exit initializers.
The SDK pointer codec reduces encoded null to the cookie value. Preserve the
actual operand; a literal null would initialize these encoded slots incorrectly.

The original E8 at **`0x0055390A` calls `0x00555930`**, the previously reviewed
matherr initializer. Ghidra did not list this source callback's instructions,
so its empty reference result omitted a real native call. Full archive symbols,
the table's `initialize_pointers` record and pinned original-byte decoding now
establish the caller. This resolves the caller-location limit in the
[math exception review](CRT_MATH_EXCEPTION_ORIGIN_BOUNDARY_REVIEW.md).

The eight-byte `uninitialize_environment` has the same ordinary shape as an
SDK thread-detach wrapper, but its table role and call to
`__dcrt_uninitialize_environments_nolock` distinguish it. Similarly, the nine-byte
VCRuntime callback is not an unlock helper merely because the opcodes agree:
its table field and relocation identify `__vcrt_uninitialize(false)`. Short
masked matches are candidates until their external roles are reconciled.

## Retirement order and return contracts

`__acrt_uninitialize` tests its terminating argument. On true, it calls
`_flushall` only when the stdio table pointer is nonnull, then returns true in
AL. On false, it uses the complete reverse executor. The stdio predicate is
inline here; no address is assigned to an unmatched standalone helper.

The 80B buffer-retirement callback frees stdout storage, stderr storage, narrow
argv and wide argv in the original order, clearing each pointer slot along the
way. All four calls target the separately reviewed `_free_base` at
`0x00557BA0`. The 23B allocated-memory callback passes the current multibyte
pointer slot to its original release lambda.

The complete 46B lambda uses LOCK XADD with `-1`, branches on the resulting
count, and only on zero compares against the immortal initial multibyte block.
A different block is freed and its slot restored to that initial block. The
initial-block and nonzero-count paths remain intact, including `RET 4`; no
invented null handling or simplified unconditional free is introduced. This
is the release callback's contract, separate from the outer cdecl initializer.

## Evidence and affected scope

Private `.analysis/origin-boundary/ucrt-lifetime/` contains bounded native and
caller queries, `review.py`, `reviewed.json` and diagnostic member locations.
It reuses the extracted `heap-control/initialization.obj`. Pinned decoding
supplements 126 original bytes absent from Ghidra's instruction listing: the
46B pointer initializer and 80B buffer cleanup. All ten accepted complete bodies and
the table retain their original extents; the new ledger heads do not mutate
Ghidra or target bytes. The retained original report includes the rejected
eleventh role as failed-hypothesis evidence; the linked cache review supplies
its corrected identity.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
