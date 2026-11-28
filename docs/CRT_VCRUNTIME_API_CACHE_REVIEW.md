# VCRuntime API caches and downlevel fallbacks

Nine whole archive contributions identify nine pending library origins in the
locked Japanese TH20 Steamless target. The complete comparison covers 623B of
instructions, five INT3 bytes, 305B of data and seven zero alignment bytes.
All existing ledger extents remain unchanged.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005478A7` | 160 | VCRT cached function resolver |
| `0x00547947` | 75 | system-directory library loader |
| `0x00547992` | 59 | FlsAlloc shim |
| `0x005479CD` | 59 | FlsFree shim |
| `0x00547A08` | 59 | FlsGetValue shim |
| `0x00547A43` | 62 | FlsSetValue shim |
| `0x00547A81` | 71 | InitializeCriticalSectionEx shim |
| `0x00551400` | 11 | public calloc forwarder |
| `0x00557290` | 67 | wcsncmp |

The first seven contributions are from MSVC 14.44.35207
`libvcruntime.lib(winapi_downlevel.obj)`. The last two are whole SDK
10.0.26100.0 x86 `libucrt.lib` members `calloc.obj` and `wcsncmp.obj`.
The API interval `0x005478A7..0x00547AC7` is contiguous. The calloc body is
followed by five INT3 bytes before the next head at `0x00551410`; wcsncmp
ends immediately before the previously reviewed signal guard at `0x005572D3`.
The resolver's two single-byte NOPs and the comparator's four-byte NOP remain
instructions in their full contributions. These sections own no EH tables.

## Raw caches and atomic publication

The complete 32B loader-zero section at `0x005E52EC` holds three module
handles, followed at `0x005E52F8` by five function pointers. Both tables
store raw values: zero means unattempted and -1 means a failed attempt.
Function IDs 0 through 4 select FlsAlloc, FlsFree, FlsGetValue, FlsSetValue
and InitializeCriticalSectionEx. Module IDs 0 through 2 select the fibers
API set, synchronization API set and kernel32.

Publication uses unconditional XCHG, including failure sentinels. It does
not use a compare-exchange against null. After publishing a loaded module,
any nonzero previous cache value causes one FreeLibrary call on the newly
loaded handle to balance the duplicate reference; the resolver still uses
that newly loaded handle. Debug assertions in the installed source add no
release branches. The source intentionally retains module references;
there is no shutdown cache cleanup in these bodies.

The resolver advances through candidate modules only while loading a module
fails. Once a module is available, it calls GetProcAddress once. A missing
export caches function failure and returns null without trying another module.
The native branch at `0x0054793C` goes to the failure publication at
`0x00547915`, retaining this distinction.

## Complete names and candidate arrays

| Address | Bytes | Data |
| --- | ---: | --- |
| `0x00597B44` | 12 | three relocated module-name pointers |
| `0x00597B50` | 60 | UTF-16 api-ms-win-core-fibers-l1-1-1 |
| `0x00597B8C` | 58 | UTF-16 api-ms-win-core-synch-l1-2-0 |
| `0x00597BC8` | 18 | UTF-16 kernel32 |
| `0x00597BDC` | 16 | UTF-16 api-ms- prefix |
| `0x00597BEC` / `0x00597BF4` | 8 / 9 | FlsAlloc module IDs / ASCII name |
| `0x00597C00` / `0x00597C08` | 8 / 8 | FlsFree module IDs / ASCII name |
| `0x00597C10` / `0x00597C18` | 8 / 12 | FlsGetValue module IDs / ASCII name |
| `0x00597C24` / `0x00597C2C` | 8 / 12 | FlsSetValue module IDs / ASCII name |
| `0x00597C38` / `0x00597C40` | 8 / 28 | CriticalSectionEx module IDs / full ASCII name |

All strings include their terminators. The four FLS arrays each contain
`[0,2]`; the critical-section array contains `[1,2]`. Each whole array is
retained separately, including one-past-end pointer addends that numerically
equal a following name address. Zero alignment occupies two bytes at
`0x00597BC6`, two at `0x00597BDA` and three at `0x00597BFD`. Together with
the BSS cache, these sections and gaps form the complete 312B data closure.

## Loader policy, TLS fallback and ABI

The loader first calls LoadLibraryExW with flags 0x800. A failure is retried
with flags zero only when GetLastError is 87 and the case-sensitive first
seven wide characters differ from `api-ms-`. API-set-prefixed names receive
no such retry. The complete wcsncmp body returns zero for count zero without
reading either string. Otherwise it stops at the count, first null in the
left string or mismatch, returning the difference of two zero-extended
16-bit characters. It does not normalize a nonzero result to -1 or 1.

The five public VCRT shims use cdecl; resolved WinAPI pointers use stdcall
and pass the existing guard check before an indirect call. FlsAlloc forwards
its callback only to a resolved FlsAlloc. Its fallback tail-jumps to TlsAlloc
with no callback argument, so that path does not register a destructor.
Free/GetValue/SetValue pass their original arguments and return values to
the respective TLS imports. These shims add no LastError restoration; the
outer PTD getter's normal-return preservation is documented in the
[state review](CRT_VCRUNTIME_STATE_ORIGIN_REVIEW.md).

The resolved InitializeCriticalSectionEx receives section, spin count and
flags. Its fallback calls InitializeCriticalSectionAndSpinCount with section
and spin count, dropping flags. The public calloc forwarder preserves its
arguments and tail-jumps to the independently reviewed calloc base at
`0x00557B40`. This is the public entry used by the reviewed VCRT PTD owner.

## Rejected candidates and evidence

The 11B calloc ordinary-byte shape has twelve target candidates. Only
`0x00551400` calls the established calloc base; the other eleven resolve to
different callees and receive no calloc identity. Likewise, the VCRT weak
FlsFree and FlsGetValue accessor shapes match at `0x00557CB6` and
`0x00557CE1`, inside reviewed UCRT owners. Their actual names are
CompareStringEx and EnumSystemLocalesEx, with UCRT resolver `0x00557E53`.
They are not VCRT entries or aliases. The separately extracted
winapi_thunks.obj is another provider and supplies no credit in this review.

Private `.analysis/origin-boundary/vcrt-api/` retains the complete members,
bounded attested listings, locator results, original ledger rows,
`review.py` and `reviewed.json`. The comparison checks every ordinary byte,
branch, full REL32/DIR32 role and HIGHLOW relocation, and the complete
initialized/BSS data closure. All nine Windows imports are independently
named through the PE import directory. Installed source
`vcruntime/winapi_downlevel.cpp` and UCRT `string/wcsncmp.cpp` corroborate
the observed control flow and argument roles.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**. These library origins establish neither a
global game compiler profile nor new authored or maintained-source exact credit.
