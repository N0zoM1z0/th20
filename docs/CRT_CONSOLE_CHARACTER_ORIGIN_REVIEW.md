# UCRT mbtowc state and console handle lifetime

Six complete SDK 10.0.26100.0 x86 contributions match the locked Japanese
TH20 Steamless target: 524B/189 instructions, nine REL32/fifteen DIR32 roles
and 32B of owned state, literal and termination registration. All existing
extents remain unchanged. The console character provider and its complete
handle protocol are now reviewed alongside the internal multibyte converter.

| Entry | Bytes | Instructions | Role |
| --- | ---: | ---: | --- |
| `0x0055929A` | 304 | 110 | `_mbtowc_internal` |
| `0x0056662C` | 50 | 22 | `_putwch_nolock` |
| `0x00566913` | 31 | 11 | initialize console output handle |
| `0x00566932` | 31 | 9 | ensure console output initialized |
| `0x00566951` | 23 | 8 | terminate console output |
| `0x00566968` | 85 | 29 | write console with one invalid-handle retry |

These are full source sections, without owned padding, EH or switch tables.
The 170B console lifetime interval is contiguous. The three INT3 after it
precede the separate aligned ascii_strnicmp entry; they do not extend the
85B writer. CodeView confirms cdecl throughout: mbtowc and the console BOOL
helpers return int32, initialization/termination return void, and putwch
returns unsigned WORD from a WCHAR argument. Its upper EAX bits are not part
of the result contract.

## mbtowc resets and resumes its shared state selectively

The converter takes optional WCHAR output, source, uint32 size and a reference
to the caller's cached PTD host. Null source or zero size clears its complete
eight-byte static mbstate and returns zero before accessing the host/output.
A nonnull empty string optionally writes a zero WCHAR and returns zero,
without clearing that state. Nonempty input refreshes the cached locale only
when its initialization byte at +0x14 is zero.

UTF8 calls the already reviewed 67B mbrtowc adapter with that shared state.
CMOVS collapses every signed-negative primitive result to -1, including
INCOMPLETE. That collapse does not erase the decoder's retained partial state;
a later call can resume it. The adapter's non-BMP replacement and error/output
rules remain those of the [full UTF8 review](CRT_UTF8_STATE_ORIGIN_REVIEW.md).
The state is a shared static object, not a new per-call or thread-local value.

For a non-UTF8 C locale, optional output receives the zero-extended unsigned
input byte and the result is one. Other locales test the signed pctype WORD
for a lead byte. The lead path first checks mb_cur_max > 1 and signed
`(int)n >= mb_cur_max`, then calls the reviewed MultiByteToWideChar wrapper
with flags 9, that byte count and output capacity one or zero.

The original fallback is narrower than a general conversion-error test.
If either prerequisite fails or the API returns zero, it sets cached EILSEQ/42
only when unsigned n < mb_cur_max or the second source byte is zero. Otherwise
it still returns mb_cur_max. Thus an API failure with enough bytes and a
nonzero second byte can return the positive length without caching EILSEQ.
Keep the signed prerequisite and unsigned fallback distinct. The single-byte
path instead caches EILSEQ on a zero API result and otherwise returns one.
The cache writes its validity byte at host+0x1C before the DWORD at +0x18;
this owner neither commits global errno immediately nor sets doserrno.

## Console output keeps the cached handle and retries once

The complete four-byte handle initializer is -2. Ensure opens only that
uninitialized value, then returns false only for -1. CreateFileW uses the full
UTF16 `CONOUT$` literal, GENERIC_WRITE, read/write sharing, OPEN_EXISTING,
zero attributes and null security/template arguments. An initial open failure
leaves -1, so later ensure calls do not automatically reopen it.

Termination skips -1/-2, otherwise calls CloseHandle and ignores its result.
It does not reset the cached value. The write helper directly calls
WriteConsoleW with the current handle and the caller's buffer/count/result
pointer, with null reserved argument. Success returns its original BOOL.
Failure checks GetLastError; only ERROR_INVALID_HANDLE/6 selects termination,
reinitialization and exactly one further WriteConsoleW. It neither loops nor
checks the new handle with ensure before that second attempt. Other failures
return directly. No new locking or errno mapping is present in these owners.

putwch first ensures initialization, then passes the address of its stack
WCHAR, count one and a local DWORD output count to the write helper. Either
false result returns WEOF/0xFFFF. Otherwise it returns the original WCHAR
through AX without inspecting the reported count. A successful zero-character
write therefore still returns that WCHAR; this is the WORD result compared
by the [console write caller](CRT_LOWIO_CONSOLE_WRITE_ORIGIN_REVIEW.md).

## Complete data and retained evidence

The full 16B literal has a unique independent content match at `0x005A2FD0`.
The static mbstate at `0x005E5668` occupies eight loader-zero virtual bytes;
its pass/reset references name the same local COFF symbol. All six native
handle references agree on the complete -2 cell at `0x005B3020`. These private
state locations are observed linked identities: zeros and the four-byte -2
initializer alone cannot independently select unique canonical addresses.

The separate console_output_initializer.obj owns a complete four-byte
`.CRT$XPX` terminator at `0x0056C448`. Its sole relocation points to the
independently located 23B termination body; the resulting DWORD has a unique
image location. The full 20B XP context retains zero sentinels and the existing
neighboring terminators, with exactly three HIGHLOW entries.

Private `.analysis/origin-boundary/console-character-providers/` retains
initcon/initializer members, provenance, complete section locations, CodeView,
three attested listings, state/termination references and `review.py`/`reviewed.json`.
It reuses mbtowc.obj/putwch.obj and their ABI from `lowio-write-console/`.
All ordinary bytes, relocation roles, CFG paths, full owned data and imports
agree. The separate 88B retry template, 34B lambda constructor and 23B lambda
call operator have no whole ordinary-byte locations and receive no entries.
The actual 91B cached-locale provider remains in use; the member's different
SelectAny implementation does not replace it. Source is `convert/mbtowc.cpp`,
`conio/{putwch,initcon}.cpp` and `initializers/console_output_initializer.cpp`.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
