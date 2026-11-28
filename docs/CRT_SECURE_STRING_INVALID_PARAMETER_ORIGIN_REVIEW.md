# UCRT secure strings, cached PTD and invalid-parameter dispatch

Fifteen pending library origins form the complete interval
`0x00547DB0..0x00548604`: 2,106 instruction bytes and all 27 original INT3 bytes.
Complete Windows SDK 10.0.26100.0 x86 `libucrt.lib` contributions in
`invalid_parameter.obj`, `wcscpy_s.obj` and `strnlen.obj` agree with the locked
Japanese TH20 v1.00a Steamless target. The full failure chain and SIMD branches
are retained, including a physical RET in the SDK's noreturn Watson routine.

## Complete entries and alignment

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00547DB0` | 72 | cached PTD host constructor |
| `0x00547DF8` | 60 | cached PTD host destructor |
| `0x00547E34` | 41 | cached global-state index synchronization |
| `0x00547E5D` | 70 | forced PTD synchronization |
| `0x00547EA3` | 28 | required PTD reader |
| `0x00547EC0` | 313 | `__acrt_call_reportfault` |
| `0x00547FF9` | 15 | `__acrt_initialize_invalid_parameter_handler` |
| `0x00548008` | 55 | `_invalid_parameter` |
| `0x0054803F` | 124 | `_invalid_parameter_internal` |
| `0x005480BC` | 16 | `_invalid_parameter_noinfo` |
| `0x005480CC` | 52 | `_invoke_watson` |
| `0x00548100` | 149 | `wcscpy_s` |
| `0x005481A0` | 352 | `strnlen` |
| `0x00548300` | 290 | `wcslen` |
| `0x00548430` | 469 | `wcsnlen` |

The PTD reader and internal dispatcher each own one trailing INT3 in their full
SDK contributions. The other 25 INT3 bytes occupy the eleven-byte copy/length
alignment gap and fourteen-byte gap after wcslen. The audit covers the entire
2,133B interval without a shortened extent or omitted branch. The SDK's
`check_synchronize_per_thread_data` and `get_raw_ptd` sections are identical,
including relocations, and share the one physical reader head; no duplicate
head or credit is added. Existing ledger sizes remain unchanged.

## Copy validation and complete length kernels

wcscpy_s rejects a null destination or zero capacity with EINVAL (22). With valid
output and capacity, a null source first clears the initial UTF-16 unit, then
reports EINVAL. Exhausting capacity before copying the NUL also clears the first
unit and reports ERANGE (34). Both errors set errno and call the no-info invalid
parameter wrapper; a returning custom handler permits the error-code return.
The successful loop copies the NUL and returns zero. It retains the original
scalar stores and does not add whole-buffer filling or overlap handling.

All three length owners read the established `__isa_available` at `0x005E5288`:
level 5 selects AVX2, level 1 selects SSE2, otherwise they use scalar scanning.
Bounded strnlen counts bytes and bounded wcsnlen counts UTF-16 units. Their
zero-count paths read no input. wcslen is unbounded and takes only a pointer.
Both wide owners keep their odd-address scalar paths, since a two-byte step
cannot repair odd alignment.

The vector paths retain scalar prefixes, aligned 16B/32B comparisons and scalar
terminator refinement/suffixes. Wide bounded loops preserve the original
element-count rounding masks and two-byte stepping. VZEROUPPER placements also
differ: bounded AVX2 loops execute cleanup inside the scan cycle, while the
unbounded wide loop cleans up after detecting a terminating vector. These are
complete original owners, rather than interchangeable generic length stubs.

## Cached PTD layout and deferred state

The public dispatcher allocates a 40B cached PTD host. Its constructor clears
the PTD pointer and validity bytes, then uses an explicit locale or the initial
locale pointers when the locale-changed flag permits. It does not zero all
payload fields. The destructor clears PTD locale-sync bit 2 only for a locale
acquired through PTD, then writes cached errno/doserrno only when valid.

The global-index helper caches index zero in this build. Both it and forced PTD
synchronization preserve Win32 LastError through GetLastError/SetLastError.
Forced synchronization calls `__acrt_getptd_noexit_explicit` at `0x00557A9F`,
caches the nullable result, and returns it. The required reader calls abort if
lazy synchronization fails. The invalid-parameter path uses the nullable result
so that missing PTD can still fall through to the global handler. The explicit
provider is now covered by the [full PTD/FLS protocol review](CRT_PTD_FLS_ERRNO_ORIGIN_REVIEW.md).

## Handler precedence, encoded null and normal returns

The internal dispatcher first uses a nonnull thread-local handler at PTD+0x35C.
Otherwise it selects the global slot using the cached state index and decodes
it as `ROR(encoded XOR cookie, cookie & 31)`. The cookie is at `0x005B25C0` and
the complete single-slot global contribution is at `0x005E530C`. Both nonnull
handler paths CFG-check their target and forward the five original arguments.
If neither handler is present, dispatch calls Watson.

The 15B initializer stores the caller-supplied encoded null. Its generic store
shape has five original candidates, but the actual global slot and the already
reviewed [UCRT pointer-initializer call](CRT_UCRT_LIFETIME_CALLBACK_ORIGIN_REVIEW.md)
bind this one to `0x00547FF9`. The prior caller supplies cookie-valued encoded
null, which this decoder maps to zero. Image-zeroed BSS is not substituted for
that runtime initialization.

The public wrapper constructs the host, dispatches the five inputs plus the
host reference, and destroys the host on normal return. The 16B no-info entry
passes five zeros and cleans those arguments. Neither receives the distinct
noreturn wrapper's contract merely because default handling normally terminates.

## Watson, reportfault and the retained RET

Watson queries processor feature 23. If available, it executes INT 0x29 with
fast-fail code 5. Otherwise it calls reportfault with debugger hook 2, status
`0xC0000417` and flag 1, then calls TerminateProcess on GetCurrentProcess with
that same status. PE import names independently establish every API target.

The SDK declares Watson noreturn, and its callers use that contract. The
complete object and original target nevertheless contain `POP ESI; RET` at
`0x005480FE..0x005480FF` after TerminateProcess. Keep those bytes and the call;
do not replace them with a fabricated return value or omit the physical RET.
The [downlevel conversion](CRT_DOWNLEVEL_LOCALE_TABLE_ORIGIN_REVIEW.md) still
uses the fatal-call contract when its secure copy unexpectedly fails.

The full 313B reportfault helper captures x86 registers/segments/flags in its
stack context, initializes both complete records, runs the initial debugger
hook when requested, clears the unhandled-exception filter, and invokes
UnhandledExceptionFilter. A zero handler result, no previously attached
debugger and a requested hook cause the second debugger notification. Its
cookie check and normal return remain intact. The installed SDK uses inline
assembly for context capture; no maintained assembly is introduced here.

## Evidence and affected scope

Private `.analysis/origin-boundary/secure-wide-string/` retains the three SDK
members, locations, bounded attested listings, `review.py` and `reviewed.json`.
The two capped length queries are completed by the tail/final queries; the audit
requires full instruction coverage across their union. It checks all fifteen
whole contributions plus the folded PTD alias, every local branch, call role,
HIGHLOW set, all 27 INT3 bytes, the full 4B handler state and PE import names.
The report records object hashes and the Watson RET. External PTD, errno,
memset, debugger-hook and cookie-check bodies receive no credit from their
named dependency roles.

Installed source is `ucrt/misc/invalid_parameter.cpp`,
`ucrt/string/{wcscpy_s,strnlen}.cpp` and
`ucrt/inc/{corecrt_internal_string_templates,corecrt_internal_ptd_propagation}.h`.
Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
