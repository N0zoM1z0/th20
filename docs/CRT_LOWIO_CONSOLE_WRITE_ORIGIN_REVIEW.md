# UCRT console conversion, buffered input, LFCR order and full EH ownership

The complete console pair and ANSI EH handler match SDK 10.0.26100.0 x86
write.obj in the locked Japanese TH20 Steamless target. All 1,109B/394
instructions, thirteen REL32/seventeen DIR32 roles, 292B of full table/metadata
and twenty original INT3 bytes are reviewed. The existing 966B ANSI and 104B
Unicode extents remain unchanged. A missing 39B compiler handler is recovered.

| Entry | Code bytes | Instructions | Role |
| --- | ---: | ---: | --- |
| `0x00564667` | 966 | 333 | ANSI console double translation |
| `0x00564A32` | 104 | 49 | Unicode console output |
| `0x0056B32A` | 39 | 12 | recovered ANSI cookie/EH handler |

The full ANSI source section is 971B: its 966B body plus five original INT3
at `0x00564A2D`. No tail was missing from that candidate. Fifteen INT3 follow
the handler before the next inventory entry. Both helpers retain cdecl hidden
aggregate return and the full 12B write_result. ANSI takes descriptor, source,
uint32 byte count and cached-host reference; Unicode takes only source/count.

## ANSI keeps incomplete input in the real descriptor record

ANSI obtains the raw handle and GetConsoleOutputCP result, then lazily obtains
the cached locale. It snapshots the locale code page; UTF8 is selected by
65001. The shared 256B lookup table at `0x005B2F20` uniquely matches the full
read.obj definition: C0..DF map to one trail byte, E0..EF to two, F0..F7 to
three, and all other indices to zero. It estimates sequence length; the
reviewed UTF8 decoder still performs validation.

UTF8 pending input occupies the five-byte mbBuffer at lowio record+0x2E.
The code scans it to the first zero or five bytes. If enough new input can
complete the pending sequence, it combines the bytes in the original local
buffer and clears the previously buffered bytes before decoding. Four-byte
UTF8 selects two output WCHARs; other lengths select one. The temporary
mbstate is zeroed. Decode failure returns the current result without restoring
the cleared pending bytes or assigning an OS error field.

If input is still incomplete, it appends the available bytes to the descriptor
buffer, adds their count to char_count and returns without console output.
A new incomplete sequence follows the same store-and-credit rule. Previously
credited pending bytes are not counted again when a later call completes them.

For non-UTF8 locales, record+0x2D flag 0x04 denotes a buffered DBCS lead byte.
That path combines the saved lead and current byte, clears the bit before
calling mbtowc_internal, and retains the cleared state on conversion failure.
Otherwise the locale's signed pctype WORD tests the lead-byte flag. A complete
pair consumes two input bytes; a lone final lead is saved at +0x2E, sets flag 0x04,
credits one byte and returns. Single-byte input uses the original one-byte
conversion. Neither the local byte buffers nor the whole host are newly zeroed.

## Converted output and newline order remain distinct from file text output

The decoded one/two WCHARs go through the reviewed CRT WideCharToMultiByte
wrapper using the captured console code page, flags zero, a five-byte output
buffer and null default-character pointers. A zero conversion result simply
returns the existing write_result. Decoder and conversion failures do not
copy GetLastError into error_code in this owner.

WriteFile failure does copy GetLastError. On API success, ANSI first sets
char_count to lf_count plus consumed new input bytes, then tests for a short
write. Thus a successful short write retains that consumed-input credit even
when less converted output was written. It does not retry the remainder.

Only after a full converted write does a captured original input byte of LF
select a second WriteFile call: one byte from a WCHAR CR temporary. Successful
one-byte output increments both count fields once. This is LF then CR, not
the file text helpers' inserted-CR-before-LF sequence. Short or failed CR
output preserves the earlier character credit; only API failure fills the
OS error field. The original five-byte temporaries, wc[2] initialization and
shared copying provider are retained.

Unicode console output reads one WCHAR at a time and compares the WORD result
of putwch_nolock with that character. Equality adds two input bytes. For LF,
it next outputs CR; success increments char_count and lf_count by one each,
so the parent's subtraction still credits two input bytes. A failed comparison
records GetLastError and returns the partial result. No byte-order change,
extra WEOF filter or CRLF normalization replaces these original WORD tests.

## Complete handler, FuncInfo and evidence

The 39B handler retains two leading NOPs, both original cookie checks and its
CxxFrameHandler3 tail. It reconstructs the parent base from registration+0x0C
and validates saved cookies at registration-0x80/-4 before loading FuncInfo.
Ghidra has no function at this address; full object/native comparison and
bounded pinned decoding cover all 39 bytes without modifying the database.

The unique full 36B FuncInfo is at `0x005A91B8`: magic 0x19930522, maxState zero,
no unwind/catch map, and flags 5. Installed ehdata_values.h/ehdata4.h identify
those bits as EHS and NoExcept. The empty maps do not remove the original
cookie/exception registration. Metadata and the lead-byte table were located
by their complete independent contents before comparing code pointer fields.

Private `.analysis/origin-boundary/lowio-write-console/` retains full locations,
attested listing/no-function observation, complete comparisons/CFG/fields,
handler decode, tables and provider identities. It reuses write.obj and its
CodeView/layout from the preceding write reviews. read.obj owns the lookup
definition. Existing memmove/canonical memcpy bindings, 91B cached-locale
updater, UTF8 decoder, conversion wrapper and FrameHandler3 retain their roles.
The new mbtowc.obj/putwch.obj uniquely identify the 304B/50B providers and their
CodeView signatures; their own protocols remain pending. Source is
`ucrt/lowio/write.cpp`, `read.cpp` and the lowio header.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
