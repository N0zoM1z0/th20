# UCRT integer parsing and string-source position ownership

Six complete Windows SDK 10.0.26100.0 x86 `libucrt.lib(output.obj)`
contributions identify pending library origins in the locked Japanese TH20
Steamless target:

| Entry | Complete bytes | Operation |
| --- | ---: | --- |
| `0x005489E6` | 52 | unsigned-long overflow predicate |
| `0x00548A4B` | 27 | C-string source factory |
| `0x00548A66` | 531 | unsigned-long char parser, TrimWhitespace=false |
| `0x0054A302` | 41 | char source unget |
| `0x0054A32B` | 46 | wchar_t source unget |
| `0x0054A3BB` | 27 | source validation |

All 724B/293 instructions agree with the complete contributions and bounded
attested listings. The eleven REL32 fields bind to the complete selected
helpers and the previously reviewed errno/invalid-parameter providers.
HIGHLOW sets are empty. These sections own no static data, padding or local
EH metadata; every instruction is reachable and all existing extents remain
unchanged.

## An eight-byte source owns the cursor and optional end publication

The source has a cursor at offset zero and an optional pointer-to-end at
offset four. Its factory returns this 8B object through the original hidden
result buffer, returns that buffer in EAX and immediately writes the original
string pointer through a nonnull end argument. Source destruction publishes
the final cursor through that same optional end pointer.

The parser receives the source by value, alongside the supplied cached PTD
host, 32-bit base and low-byte signed-result flag. It returns a full unsigned
32-bit result in EAX with cdecl cleanup. Its inlined destruction paths publish
the cursor on ordinary, invalid-base and range-error returns. The no-digit
path publishes the saved original start, including after a consumed sign or
prefix. No source-position tail is omitted from the complete 531B owner.

Complete char/wchar factory and validate members are compatible with the
same two physical heads, including all relocation roles. Each head receives
one canonical origin row. The width-dependent unget implementations retain
their separate complete entries; this establishes no wider parser location.

## Validation and putback retain their actual errno paths

Validate tests the source cursor for null. Failure calls the real errno
getter at `0x005516C1`, stores EINVAL (22), calls the complete no-info invalid
parameter provider at `0x005480BC`, and returns false if that handler returns.
Its nonnull branch returns true in AL.

Unget first decrements the stored cursor: one byte for char, two bytes for
wchar_t. A zero supplied character bypasses the memory comparison; otherwise
the previous byte/word must equal the supplied character. A mismatch stores
actual errno 22 and calls the same no-info provider, retaining the already
decremented cursor if execution returns. Both thiscall bodies use their
original byte/word argument widths and RET 4; validate uses thiscall with no
stack argument.

## Base selection and scan progress are kept together

The parser validates its source first. A nonzero base outside 2–36 writes
cached EINVAL at host `+0x18`, sets its valid byte at `+0x1C` and calls the
complete internal invalid-parameter provider at `0x0054803F` with that host
and five null/zero arguments. These cached writes remain distinct from the
source helpers' actual errno writes.

This instantiation skips no whitespace. It handles one optional sign, then
base-zero decimal/octal selection and the original 0x/0X prefix for base
zero or sixteen. A peeked non-x character is put back through the real
unget helper. Digits are ASCII 0–9, a–z and A–Z; values outside the selected
base terminate the scan. The terminator, including zero, is put back before
the digit-read test and final end publication.

The accumulator remains 32-bit. Its maximum pre-multiply value is
UINT32_MAX/base. Each accepted digit sets READ_DIGIT and ORs a sticky
OVERFLOW bit for multiplication range or addition wrap. Scanning continues
after that flag is set, preserving the complete final cursor.

## Range handling preserves signed and unsigned outcomes

The separate overflow predicate first checks the sticky arithmetic flag.
In signed mode, negative magnitudes may reach 0x80000000, while positive
magnitudes may reach 0x7FFFFFFF. Unsigned mode adds no signed-magnitude limit.
The predicate takes two 32-bit cdecl arguments and returns its boolean in AL.

On overflow the parser caches ERANGE (34). Unsigned results saturate at
0xFFFFFFFF; signed negative/positive results return 0x80000000/0x7FFFFFFF.
Only a nonoverflowing negative input applies the final unsigned negation.
All range exits retain end-pointer publication and the common register/frame
epilogue. A scan with no digit returns zero and restores the original end
position without applying those range rules.

## Evidence and affected scope

Private `.analysis/origin-boundary/format-parse-integer/` retains scoped
root/helper locations, three attested listings, full comparisons, compatible
alias sections, cursor/error/flag observations, provider references and
original rows. It reuses the complete member/provenance in `format-buffer/`.
Installed `corecrt_internal_strtox.h` defines the complete source, parser
and overflow protocol, including the no-whitespace instantiation.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
