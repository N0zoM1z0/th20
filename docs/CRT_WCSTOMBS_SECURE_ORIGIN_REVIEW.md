# UCRT wide-to-multibyte conversion and final-byte truncation

Three pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` `wcstombs.obj` contributions. All 949 code bytes
and complete branch/HIGHLOW/callee/import roles agree with the locked Japanese
TH20 v1.00a Steamless target. The core avoids copying part of a multibyte
character during fallback, but the secure policy subsequently writes its
terminator at a byte boundary and can overwrite a final trail byte.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0055D71F` | 214 | `_wcstombs_internal` secure policy |
| `0x0055D7F5` | 673 | `_wcstombs_l_helper` conversion core |
| `0x0055DA96` | 62 | `_wcstombs_s_l` locale-specific public wrapper |

These three whole contributions fill `0x0055D71F..0x0055DAD3`, with unchanged
ledger boundaries and no omitted owned alignment, data or EH section. The
673B core retains its GS check. Unlike the adjacent mbstowcs throw() helper,
this core has no separate C++ EH contribution.

## Secure policy counts bytes

The policy validates destination/capacity before clearing its optional DWORD
converted-count output. A valid destination first has its initial byte cleared.
The unsigned minimum of requested count and capacity must fit INT_MAX, then
becomes the core's byte bound. Core failure clears a present destination and
returns the cached errno's original `value_or(0)` result.

Success adds one for the terminator. An oversized result with an ordinary
request clears the first byte and reports ERANGE/34 through the existing
invalid-parameter dispatcher. `_TRUNCATE` instead caps the count to capacity,
sets STRUNCATE/80 and writes zero at `destination[count - 1]`. The final count
includes the terminating byte. Validation and locale/error caching reuse the
[reviewed cached PTD host](CRT_SECURE_STRING_INVALID_PARAMETER_ORIGIN_REVIEW.md).

The final store does not backtrack over a lead byte. A bounded byte-store model
assumes a complete two-byte core result `82 A0` in a two-byte buffer. This
policy returns 80, reports count two and changes the buffer to `82 00`.
With capacity three, it instead returns zero and produces `82 A0 00`.
This conditional model follows the native post-conversion branch and does not
invoke Win32 or assert an observed game input. Preserve the actual final-byte
write rather than adding reserved terminator space or character-aware trimming.

## Early exit, C locale and UTF-8

A nonnull destination and zero bound return zero before source validation.
Otherwise null source caches EINVAL/22 and invokes the returning invalid-
parameter dispatcher. Locale access uses the same pending cached updater at
`0x0054A360` as the
[multibyte-to-wide owner](CRT_MBSTOWCS_SECURE_ORIGIN_REVIEW.md).
The core itself does not add the policy's destination clearing on every error.

UTF-8/65001 creates a fresh eight-byte mbstate_t and delegates to the separate
provider at `0x005652D2`. Other code pages with a null LC_CTYPE locale name
use the C path: each UTF-16 value must fit 0..255 before narrowing. Invalid
values cache EILSEQ/42 and return `SIZE_MAX`. Both output and length-query
paths enforce that range. A null output scans the whole terminated source,
while output mode stops at the byte bound and excludes the null from its count.

## SBCS, default substitution and whole-character fallback

For a non-C locale with `mb_cur_max == 1`, the inlined bounded wide counter
includes an early null. The adjusted count supplies both input elements and
output bytes to the reviewed WideCharToMultiByte adapter. Success requires
nonzero API result and a zero used-default BOOL. A trailing output null is
excluded from the returned count. The counter is part of this complete body;
its unused out-of-line 43B SDK definition receives no separate entry.

For other character widths, a bulk null-terminated conversion is attempted
first. Nonzero result with no default substitution returns count minus one.
Default substitution fails with EILSEQ before querying LastError. A zero
result only enters fallback for ERROR_INSUFFICIENT_BUFFER/122 from the named
GetLastError import at `0x0056C130`; other errors fail with EILSEQ.

Fallback converts one UTF-16 element into the original five-byte temporary,
passing signed `min(5, mb_cur_max)` capacity. A zero result, used-default flag,
negative result or result above five fails with EILSEQ. If the whole converted
sequence would exceed remaining capacity, the core returns its accumulated
count without copying it. Otherwise it copies every returned byte, stops on a
copied null without counting it and advances the wide source after each
nonterminating character. The secure policy's later terminator overwrite is
separate from this whole-character decision.

The non-C length query also rejects default substitution and subtracts the
terminator from a successful API result. All wide-to-narrow API calls use
flags zero, null default-character input and the original DWORD used-default
output. Code-page-specific filtering and UTF pointer rewriting remain in the
[complete conversion adapter](CRT_LOCALE_REFRESH_CONVERSION_ORIGIN_REVIEW.md).

## Wrapper direction and evidence

The 62B cdecl wrapper accepts six arguments, passes the explicit locale to the
40B cached host constructor, calls the actual secure owner at `0x0055D71F`,
destroys the host and returns errno_t. Its ordinary bytes also fit the losing
`_mbstowcs_s_l` candidate; the internal callee establishes the direction.
Conversely, the SDK's ordinary wcstombs_s wrapper bytes fit `0x0055D6E2`, but
that reviewed head actually calls mbstowcs internal at `0x0055D43C`. It remains
the one mbstowcs_s owner and receives no second name or credit.

Private `.analysis/origin-boundary/wcstombs/` retains the bounded complete
365-instruction listing, member details, `review.py` and `reviewed.json`.
The unchanged SDK member and locations remain at
`mbstowcs/wcstombs-context.obj`. The audit compares all three whole code
sections, every branch/relocation and import/callee role, the wrong-direction
wrapper and final-byte store model. Installed source is
`ucrt/convert/wcstombs.cpp`. The UTF-8 provider and cached updater remain
separate pending bodies.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
