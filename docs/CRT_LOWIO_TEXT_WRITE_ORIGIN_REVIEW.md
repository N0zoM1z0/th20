# UCRT text-write translation, short writes and input-byte accounting

Three complete SDK 10.0.26100.0 x86 write.obj contributions identify library
origins in the locked Japanese TH20 Steamless target. All 758B/266 instructions,
seven REL32/twelve DIR32 fields and complete local control flow agree. Existing
extents remain unchanged and fill `0x00564B17..0x00564E0C` continuously. There
is no owned static data, EH record, embedded table or alignment to omit.

| Entry | Bytes | Instructions | Role | Probed stack bytes |
| --- | ---: | ---: | --- | ---: |
| `0x00564B17` | 219 | 80 | ANSI text | 5,132 |
| `0x00564BF2` | 233 | 82 | UTF16LE text | 5,136 |
| `0x00564CDB` | 306 | 104 | UTF8 text | 5,144 |

All three are cdecl aggregate-return functions with descriptor int32, const
byte pointer and uint32 input-byte count. CodeView and the reviewed caller
establish the hidden result pointer and full 12B write_result: unsigned DWORD
error_code, char_count and lf_count at offsets 0/4/8. Each owner zeros all
three fields, retains its real page probe and cookie check, and returns the
same result address in EAX. The shared cookie/checker bindings are reused;
this review grants no separate checker-body credit.

## ANSI and UTF16LE stop after a successful short write

ANSI uses a 5,120-byte local translation buffer. Each input LF inserts one
CR and increments lf_count by one while preparing the chunk. UTF16LE uses
2,560 WCHARs in the same byte capacity, copies two-byte code units and adds
two to lf_count for each inserted CR word. Both reserve the last element
before the inner iteration so a CR/LF pair fits. The translation is counted
by explicit input length, including embedded NULs; it does not normalize an
existing CR or append a string terminator.

Both call the original WriteFile import with the prepared byte count. Success
adds its reported DWORD to char_count. A successful short write, including
zero, returns immediately without retrying the remainder. Failure records
GetLastError and returns without adding that failed call's reported count.
Prepared lf_count is retained in either case: it is not rolled back to match
the written prefix. Previous chunks' progress also remains. The reviewed
parent applies its original char_count-minus-lf_count rule to this record.

## UTF8 drains converted output before counting consumed input

UTF8 mode takes UTF16 input, as required by the reviewed parent. It first
expands LF into CR/LF in an 853-WCHAR intermediate buffer, reserving one WCHAR.
It then calls the reviewed cdecl CRT WideCharToMultiByte wrapper with CP_UTF8
65001, flags zero, the prepared WCHAR count, a 3,413-byte output buffer and
both default-character pointers null. A zero conversion result records
GetLastError and returns the existing result.

For converted output, successful short WriteFile calls advance the output
pointer/count and repeat until the whole converted chunk is written. There
is no successful-zero-progress escape in that loop. API failure records
GetLastError and returns immediately. Only after the entire chunk is drained
does char_count become the consumed input-byte offset from the original
buffer. A failed partial chunk is not added to that input count. lf_count
stays zero, since inserted CRs are already excluded by input-byte accounting.
These rules differ from ANSI/UTF16LE's prepared-LF and reported-output counts.

## Evidence and affected scope

Private `.analysis/origin-boundary/lowio-write-text/` retains the full attested
listing, all fields/CFG comparisons, buffer/frame constants and original rows.
It reuses write.obj and unique whole locations in `lowio-write/`, CodeView
signatures/layout in `lowio-write-nolock/`, and established lowio state, page
probe, cookie and conversion-wrapper providers. Original PE WriteFile and
GetLastError identities are reused from the same locked-target proof.
Installed source is `ucrt/lowio/write.cpp`. The exact native frame sizes and
buffer boundaries agree with its constants; no compiler-shaping storage is
added to maintained source.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
