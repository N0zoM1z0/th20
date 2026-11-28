# UCRT secure multibyte-to-wide ownership and direction identities

Three pending library origins are reviewed and one compiler EH handler is
recovered through complete Windows SDK 10.0.26100.0 x86 `libucrt.lib`
`mbstowcs.obj` contributions. All 763 instruction bytes, five original INT3
bytes and the complete 36B FuncInfo agree with the locked Japanese TH20
v1.00a Steamless target. Real internal call roles distinguish the conversion
direction from same-shaped wrappers.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0055D43C` | 221 | `_mbstowcs_internal` secure policy owner |
| `0x0055D519` | 452 | `_mbstowcs_l_helper` conversion core |
| `0x0055D6E2` | 61 | `mbstowcs_s` public wrapper |
| `0x005682E0` | 29 | recovered cookie/EH handler |

The first three bodies and the five INT3 bytes at `0x0055D6DD..0x0055D6E1`
fill `0x0055D43C..0x0055D71E`. The helper's full SDK section is 457B; its
existing 452B instruction extent remains correct. No parent is shortened or
overlapping fragment invented. The source's throw() helper has the separate
29B handler, including both leading NOPs, and full 36B FuncInfo at
`0x005A91B8`. Cookie checking and the actual FrameHandler3 tail remain intact.

## Secure output validation, count and truncation

The secure policy first requires either null destination with zero capacity,
or nonnull destination with positive capacity. An invalid pair reports cached
EINVAL/22 through the reviewed returning invalid-parameter dispatcher before
clearing the optional converted-count output. A valid destination has its
first UTF-16 unit cleared, and a supplied converted-count pointer is then
cleared with a DWORD store.

The conversion bound is the unsigned minimum of requested count and capacity.
A value above INT_MAX reports EINVAL. The helper returns a size_t count
excluding the terminator or `SIZE_MAX` on failure. Failure resets a present
destination and returns the cached errno's original `value_or(0)` result.

Success adds one for the terminator. If the result exceeds a present buffer's
capacity, an ordinary count clears the first UTF-16 unit and reports
ERANGE/34. `_TRUNCATE` instead caps the result to capacity, returns
STRUNCATE/80 and writes the terminator over the last available element.
Otherwise the terminator is written immediately after the converted payload.
The optional count receives the final number of UTF-16 elements including
that terminator, not a byte count.

The 61B cdecl public wrapper accepts five arguments and constructs the
reviewed 40B cached PTD host with a null supplied locale. It invokes the
six-argument secure owner with that host, destroys it and returns the full
errno_t. Cached errno and locale restoration retain the
[host's existing lifetime contract](CRT_SECURE_STRING_INVALID_PARAMETER_ORIGIN_REVIEW.md).

## Core early exits, C locale and UTF-8 delegation

For a nonnull destination with zero conversion bound, the helper returns zero
before checking the source. A present destination with positive bound has its
first UTF-16 unit cleared before source validation. Null source then reports
EINVAL and returns `SIZE_MAX`; the two branches are not merged into a generic
validation-first rule.

The helper lazily obtains cached locale data. UTF-8/65001 initializes a fresh
eight-byte mbstate_t and delegates to the UTF-8 provider at
`0x005596DE`, passing the source pointer by address and the original bound.
The provider and its scalar/state dependencies are now covered by the
[complete UTF-8 review](CRT_UTF8_STATE_ORIGIN_REVIEW.md).

For other code pages, a null LC_CTYPE locale-name pointer selects the C path:
copy unsigned source bytes into UTF-16 elements until null or the bound.
The result excludes the terminator; reaching the bound does not add one.
Without a destination, that path scans the complete null-terminated byte string
for its length rather than applying the output bound.

## Win32 attempt, DBCS retry and error widths

The non-C output path first converts the full null-terminated input with flags
9 through the [reviewed conversion wrapper](CRT_LOCALE_REFRESH_CONVERSION_ORIGIN_REVIEW.md).
A successful result subtracts one for the converted null. A zero result checks
the independently named GetLastError import at `0x0056C130`.

Only ERROR_INSUFFICIENT_BUFFER/122 retries. The bounded source walk counts
characters and advances an additional byte for a lead byte, using the locale's
ctype WORD sign bit. A lead byte followed by the terminator fails. The retry
passes the measured **byte** extent and flags 1 to conversion, returning its
count without subtracting a terminator. Other initial errors, a dangling lead
byte and retry failure cache EILSEQ/42, clear the first UTF-16 unit and return
`SIZE_MAX`. These paths do not call the invalid-parameter dispatcher.

The non-C length-query path uses full null-terminated input, flags 9 and null
output; it returns the resulting count minus one or caches EILSEQ on failure.
All flags still pass through the original code-page-specific filter.

## Rejected names and unresolved shared-helper variant

The adjacent bodies are not CompareStringA: that SDK member's 671B/70B
candidates fail whole-body location. The successful mbstowcs contributions
retain their actual wide stores, UTF-8 delegation and secure-copy policy.

Ordinary bytes also suggest `_mbstowcs_s_l` at `0x0055DA96`, but its native
internal call is `0x0055D71F`, not the proved multibyte-to-wide owner at
`0x0055D43C`. The opposite-direction SDK member supplies the corresponding
wcstombs internal candidate. Likewise, ordinary public-wrapper bytes alone
cannot choose between mbstowcs_s and wcstombs_s. The actual `0x0055D6E2`
call to `0x0055D43C` resolves the reviewed wrapper. The opposite-direction
policy/core and locale-specific wrapper are now covered by the
[complete wcstombs review](CRT_WCSTOMBS_SECURE_ORIGIN_REVIEW.md).

The shared cached-locale updater at `0x0054A360` remains pending. Its ordinary
prefix and call roles agree with the SDK's 89B helper, but the target has a
91B body ending `MOV ESP,EBP; POP EBP; RET` rather than `LEAVE; RET`.
The full source and both epilogues are retained for a later compiler question;
the current review grants no shared-helper body credit from that near match.

## Evidence and affected scope

Private `.analysis/origin-boundary/mbstowcs/` retains the SDK member,
opposite-direction context, complete handler/cache/wrapper listings,
`review.py` and `reviewed.json`. The unchanged bounded primary listing is in
`compare-a/native.txt`, preserving the failed initial hypothesis. The audit
compares four whole code contributions, all five INT3 bytes, all 36B metadata,
complete control flow/HIGHLOW/callee/import roles and the wrong-direction
wrapper negative case. Installed source is `ucrt/convert/mbstowcs.cpp`, with
cached host behavior in `corecrt_internal_ptd_propagation.h`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
