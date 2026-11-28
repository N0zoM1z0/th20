# UCRT write_nolock mode dispatch, console selection and result precedence

Two complete SDK 10.0.26100.0 x86 write.obj contributions identify library
origins in the locked Japanese TH20 Steamless target. All 665B/241 instructions,
eleven REL32/ten DIR32 roles, local branches and import identities agree.
The existing 125B/540B extents remain unchanged. Neither contribution owns
static data, EH, padding or an embedded jump table.

| Entry | Bytes | Instructions | Symbol |
| --- | ---: | ---: | --- |
| `0x00564A9A` | 125 | 45 | write_requires_double_translation_nolock |
| `0x00564F1E` | 540 | 196 | _write_nolock |

CodeView establishes cdecl bool/AL for the selector and cdecl int32 for
write_nolock. The latter retains the parent's four arguments: int32 descriptor,
const void pointer, uint32 byte count and cached PTD host reference. The whole
12B anonymous write_result has unsigned DWORD fields error_code at +0,
char_count at +4 and lf_count at +8. CodeView's forward/full records agree;
the five translation helpers return this aggregate. Native calls retain the
caller-provided hidden result pointer, EAX result address and full three-DWORD
copy, rather than a scalar return or truncated result record.

## Validation and append precede mode dispatch

Write_nolock returns zero for a zero count before testing the buffer or reading
descriptor state. A nonzero count with null buffer caches doserrno zero and
EINVAL/22, invokes the reviewed internal invalid-parameter dispatcher and
returns -1 if it resumes. Modes 1/UTF8 and 2/UTF16LE also require an even input
byte count, taking that same failure path for odd counts. UTF8 mode consumes
UTF16 input here; its output conversion does not make an odd input count valid.

Mode is the original byte at lowio record+0x29, with ANSI=0, UTF8=1 and
UTF16LE=2. The established array has 64-record blocks and 56B stride. FAPPEND
bit 0x20 selects lseeki64_nolock_internal with signed 64-bit offset zero,
FILE_END/2 and the original host reference. Its result is ignored, and its
cached-error side effects are not cleared before a later successful write.
This owner obtains no descriptor lock or FOPEN validation of its own; those
belong to the reviewed write_internal caller.

## Console selection preserves its cached locale conditions

The 125B predicate first requires the reviewed isatty result and FTEXT/0x80.
It then uses the existing cached-locale updater only when host+0x14 is zero.
The established 91B provider is retained, including its SelectAny distinction.
A null LC_CTYPE locale-name pointer (locinfo+0xA8) combined with ANSI mode
returns false without querying console mode. Otherwise the original raw OS
handle and a DWORD output address go to KERNEL32.dll!GetConsoleMode at IAT
`0x0056C06C`; its nonzero BOOL becomes true in AL. The mode DWORD itself is
not inspected. This is a console query, not a code-page or capability substitute.

True selects ANSI double translation for mode zero and Unicode double
translation for either mode 1 or 2. False with FTEXT selects separate ANSI,
UTF8 or UTF16LE text helpers. False without FTEXT executes the complete
inlined binary WriteFile path. Both mode switches retain their default
zero-result fallthrough instead of adding a new invalid-mode handler.
The out-of-line 79B binary helper has no complete ordinary-byte location;
its inlining does not create another native entry.

## Nonzero progress takes precedence over the OS error field

The binary path zeroes its full 12B temporary, calls WriteFile through IAT
`0x0056C138` with the original buffer/count and char_count address, and records
GetLastError through IAT `0x0056C130` only when the API returns false.
Translated paths copy their full result from the returned aggregate address.

A nonzero char_count immediately returns the original 32-bit
`char_count - lf_count` result. The error field is examined only when
char_count is zero; an accompanying nonzero error does not override nonzero
progress on this path. No clamp, retry or errno-based replacement changes
the subtraction.

With zero progress, ERROR_ACCESS_DENIED/5 explicitly caches EBADF/9 and
raw doserrno 5, overriding the normal access-denied errno mapping. Other
nonzero errors call the reviewed cached OS-error mapper. Both return -1.
With no OS error, FDEV/0x40 and a first input byte of Ctrl+Z/0x1A return zero;
otherwise the owner caches ENOSPC/28 and doserrno zero, then returns -1.
The original byte test and cached payload/validity widths remain intact.

## Evidence and remaining translation owners

Private `.analysis/origin-boundary/lowio-write-nolock/` retains both attested
listings, CodeView/aggregate layout, full comparisons/CFG/fields and named PE
imports. It reuses write.obj and its complete locations from `lowio-write/`,
plus reviewed lowio state, cached locale, isatty and error/handler providers.
The new lseek.obj independently locates the 30B append wrapper and 131B shared
64-bit seek owner; their own protocols remain pending. Installed source is
`ucrt/lowio/write.cpp` and the lowio/PTD propagation headers.

The three text translators now have their [full short-write/accounting review](CRT_LOWIO_TEXT_WRITE_ORIGIN_REVIEW.md).
The console pair remains pending, especially the 971B ANSI double translator
and its 39B EH handler at `0x0056B32A`. The old 966B primary candidate must be
reconciled with that full contribution before acceptance. Their whole-member
identities alone confer no separate reviewed credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
