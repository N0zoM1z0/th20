# UCRT string counters and wide adapter count rules

Three pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions in `strncnt.obj`,
`lcmapstringw.obj` and `comparestringw.obj`. All 194 code bytes, complete
branches and relocation roles agree with the locked Japanese TH20 v1.00a
Steamless target. The byte counter reads before testing its limit, while
wide mapping and comparison apply different null-termination rules.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00552590` | 30 | `__strncnt` |
| `0x0056665E` | 62 | `__acrt_LCMapStringW` |
| `0x0056669C` | 102 | `__acrt_CompareStringW` |

All three are complete cdecl bodies with unchanged ledger extents. Their SDK
sections own no trailing alignment, data or EH tables. Existing wcsnlen and
wide API thunks retain their separately reviewed owners and bindings.

## Byte counter reads before the limit check

The counter returns a 32-bit size_t length without including the null. It
reads `string[0]` even when count is zero. For a nonempty input, the loop tests
the limit, increments the length and reads the next byte before returning to
that limit test. An input with no earlier null therefore also reads
`string[count]` before returning count. Early termination returns the smaller
length. No pointer validation or errno path is added.

This differs from the reviewed
[bounded strnlen/wcsnlen kernels](CRT_SECURE_STRING_INVALID_PARAMETER_ORIGIN_REVIEW.md),
whose zero-count paths read no input. A bounded branch model records reads
0 for count zero, reads 0/1 for count one, and reads 0/1/2/3 for count three
over `abc\0`. It models the complete decoded scalar loop without executing
the game. The [narrow mapping adapter](CRT_NARROW_LOCALE_ADAPTER_ORIGIN_REVIEW.md)
uses this actual counter only when its source count is positive.

## Wide mapping includes an early terminator

The mapping adapter scans only for a positive source count, calling the
complete reviewed wcsnlen at `0x00548430`. If the bounded length is smaller
than the supplied count, it passes length plus one to include the terminator.
Otherwise it passes the bounded length. Zero and negative counts pass through
without a scan.

It forwards locale name, map flags, source, adjusted count and both destination
arguments to the nine-argument LCMapStringEx adapter at `0x0055822C`, adding
three zero reserved arguments. Destination width and sort-key interpretation
remain with that API protocol. The wrapper does not allocate or re-encode.

## Wide comparison excludes the terminator and retains raw zero paths

Comparison independently caps each positive count with wcsnlen, without
adding one for a terminator. Negative and zero counts are left unchanged.
If both adjusted counts are nonzero, the original six arguments plus three
zeros reach CompareStringEx at `0x00558040`. Both real thunk identities are
already established in the
[complete WinAPI wrapper review](CRT_LOCALE_WINAPI_WRAPPER_ORIGIN_REVIEW.md).

If either adjusted count is zero, no comparison API is called. The native
SUB/SAR/CMOV sequence returns 2 for zero difference, 1 for a negative 32-bit
difference and 3 otherwise. For example, zero versus -1 returns 3 and -1
versus zero returns 1. It does not first resolve the -1 side into a string
length. The private model also retains the machine-width edge case zero
versus INT_MIN, whose wrapped subtraction selects 1; this is a native
observation rather than a promise about overflowing signed C++ arithmetic.
The result remains an integer comparison code, not a bool or -1/0/1 order.

## Evidence and affected scope

Private `.analysis/origin-boundary/locale-adapter-next/` retains the three SDK
members, complete attested `native.txt`, locations, `review.py` and
`reviewed.json`. The audit covers every instruction, branch, REL32 and complete
empty HIGHLOW sets, with bounded read/count models for the observed edge
branches. Installed sources are `ucrt/string/strncnt.cpp` and
`ucrt/locale/{LCMapStringW,CompareStringW}.cpp`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
