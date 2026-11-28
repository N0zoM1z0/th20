# UCRT allocating locale-info queries, guard and secure copies

Six pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions. All 1,385 body bytes, two owned
INT3 bytes and two linker INT3 bytes agree with the locked Japanese TH20
v1.00a Steamless target. The original output widths and temporary-buffer
protocol are retained. A different 32B freea definition in the query member is
rejected; the caller uses the independently reviewed shared 30B implementation.

## Complete bodies and alignment

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0054C44C` | 130 | `_LocaleUpdate` constructor |
| `0x0055CE76` | 224 | `InternalGetLocaleInfoA` |
| `0x0055CF58` | 431 | `__acrt_GetLocaleInfoA` |
| `0x00555DEF` | 95 | `__acrt_copy_locale_name` |
| `0x005651E0` | 242 | `strncpy_s` |
| `0x0055F860` | 263 | `wcsncpy_s` |

The public query and name-copy contributions each include one trailing INT3,
at `0x0055D107` and `0x00555E4E`. Both linker INT3 bytes between the internal
and public query bodies are checked. The wide copy retains its full nine-byte
NOP at `0x0055F8E7`, absent from Ghidra's listing but covered by pinned decoding
and the complete SDK comparison. Every selected ledger extent stays unchanged.

## Output widths and distinct allocation paths

The public dispatcher clears four bytes at the caller's output address before
checking its mode. This includes the integer mode and unsupported selectors.
Integer mode passes a temporary DWORD to the reviewed GetLocaleInfoEx wrapper
with `LOCALE_RETURN_NUMBER` (`0x20000000`) and a two-wide-unit capacity. Success
writes only the low byte to the caller and returns zero; query failure returns
`-1`. Both the initial DWORD store and final byte store belong to the original.

Narrow mode first converts into a 128B local buffer. A nonzero length allocates
an exact zeroed byte buffer, publishes its pointer and uses strncpy_s with
`length - 1`; unexpected copy failure enters the original Watson path. The
temporary detached owner still calls free_base(null). An initial zero result
retries dynamically only when GetLastError is 122. It then queries the required
length, allocates, converts and transfers ownership only on success.

Wide mode queries the required wide-unit length, allocates that count times
two bytes, fills the buffer and transfers ownership on success. Both dynamic
paths retain private ownership and cleanup on failure, including free(null)
after a successful detach. Unsupported modes return `-1` after the initial
clear. These paths are the actual providers used by the
[component initializers](CRT_LOCALE_COMPONENT_LIFETIME_ORIGIN_REVIEW.md).

## Temporary UTF-16 buffer and locale guard

The 224B internal converter creates the 16B legacy locale guard, reads the
locale's code page and queries the wide result length. It preserves the
original 32-bit size arithmetic and header-addition overflow branch. Temporary
storage has an eight-byte header; total size at most 1024B uses the aligned
stack probe and marker `0xCCCC`, while larger storage uses malloc and marker
`0xDDDD`. The data pointer advances by eight bytes in either case.

After filling the UTF-16 buffer, conversion calls the CRT wide-to-multibyte
wrapper with flags zero, input length `-1` and null default-character outputs.
A zero destination size passes a null destination to obtain the required size.
The temporary release, locale guard restoration and GS cookie check remain on
the original exits. The conversion provider is now covered by the
[complete refresh/conversion review](CRT_LOCALE_REFRESH_CONVERSION_ORIGIN_REVIEW.md);
the stack-probe body remains outside these reviewed owners.

The thiscall guard constructor accepts a supplied locale, otherwise initial
pointers when the locale has not changed, otherwise required PTD plus locale/
multibyte refresh. It sets PTD sync-disable bit 2 only when previously clear
and records whether it changed it. The internal converter's inline destructor
clears that bit only when this guard set it. Its 16B layout differs from the
[40B cached PTD host](CRT_SECURE_STRING_INVALID_PARAMETER_ORIGIN_REVIEW.md).

## Rejected member freea variant and retained shared implementation

The internal converter calls the already reviewed 30B `_freea_crt` at
`0x0054273F`. The independent `StlLCMapStringA.obj` evidence and object hash in
the [allocation review](CRT_ALLOCATION_ORIGIN_BOUNDARY_REVIEW.md) remain valid.
That body subtracts the same eight-byte header and calls `_free` at
`0x0054A540` only for the heap marker; null and stack storage are skipped.

`getlocaleinfoa.obj` also contains a 32B definition. It adds the two-byte
`MOV EDI,EDI` prefix and calls free_base directly. After accounting for the
prefix and relocation field, its remaining bytes agree with the shared body,
but its complete contribution does not. The new audit preserves this rejected
variant and reuses the prior full 30B proof for the real callee. It does not
replace the existing owner, shorten the candidate or modify historical evidence.
This is a local definition/context difference, not a newly proven global build
profile.

## Name-copy bounds and complete secure-copy behavior

The name helper rejects null or a wcsnlen result at least 85. Otherwise it
allocates `(length + 1) * 2`, then copies with both capacity and count equal to
`length + 1`. Successful output owns the allocation. Allocation failure returns
null. A nonzero secure-copy result calls Watson with the five original zero
arguments; no replacement return or extra cleanup is inserted.

The narrow/wide bounded copies retain their zero-count special cases. A null
destination with zero capacity/count returns success; a valid destination and
zero count is cleared without reading the source. Other validation failures
use EINVAL (22) and the original invalid-parameter path. Finite counts preserve
their count/capacity ordering, explicit terminator and ERANGE (34) reset path.
`_TRUNCATE` (`0xFFFFFFFF`) preserves a terminated prefix and returns STRUNCATE
(80) when capacity is exhausted, without adding the ordinary range-error path.
All original byte/word loads, stores, pointer steps and internal NOPs agree.

## Evidence and affected scope

Private `.analysis/origin-boundary/locale-info/` retains the four SDK members,
bounded attested listings, member locations, `review.py` and `reviewed.json`.
The audit compares all six whole contributions, complete local branches,
HIGHLOW sets and call roles; listing union plus pinned NOP decoding covers
every body byte. It verifies the prior freea object hash and keeps the 32B
negative case. All referenced local code sections are selected bodies or that
explicitly reused shared provider; no owned data/EH section is omitted.

Installed source is `ucrt/locale/GetLocaleInfoA.cpp`, the focused name helper in
`wsetlocale.cpp`, `ucrt/string/{strncpy_s,wcsncpy_s}.cpp`, and the relevant
internal guard/string-template headers. Only classification, focused evidence,
handoff and generated progress change. All 2,151 protected native input/product
hashes remain unchanged. Exact replay scope is **zero units**, with no new
authored or maintained-source exact credit.
