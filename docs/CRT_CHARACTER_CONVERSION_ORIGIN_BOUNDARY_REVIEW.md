# CRT character conversion and case-mapping origins

Nine pending candidates, totaling 1,834 bytes, have reviewed library origins.
Their complete contributions correspond to independently named members of the
installed x86 `libcpmt.lib`; all ordinary bytes agree. The target remains Japanese
TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Bytes | Archive symbol | Member |
| --- | ---: | --- | --- |
| 0x00541D3B | 115 | `__Getcvt` | `xwctomb.obj` |
| 0x00541DAE | 306 | `__Mbrtowc` | `xmbtowc.obj` |
| 0x00541EE0 | 87 | `__Utf8_trailing_byte_count` | `xmbtowc.obj` |
| 0x00541F37 | 255 | `___std_get_cvt@8` | `format.obj` |
| 0x0054203B | 110 | `__Getctype` | `_tolower.obj` |
| 0x005420A9 | 236 | `__Tolower` | `_tolower.obj` |
| 0x00542195 | 236 | `__Toupper` | `_toupper.obj` |
| 0x00542556 | 25 | `??1?$__crt_scoped_stack_ptr@_W@@QAE@XZ` | `StlLCMapStringA.obj` |
| 0x0054256F | 464 | `___crtLCMapStringA` | `StlLCMapStringA.obj` |

## Conversion layout, results and state

The pinned `__msvc_xlocinfo_types.hpp` defines the 44-byte `_Cvtvec`: code page
at +0, maximum multibyte width at +4, C-locale flag at +8 and a 32-byte lead-byte
bitmap at +12. `_Getcvt` clears the record, obtains the current CRT values and
builds the bitmap by scanning 256 classification entries for bit `0x8000`.
It returns the aggregate through its hidden result pointer, also returned in EAX.

`_Mbrtowc` ignores its supplied `mbstate_t*`; incomplete input returns -2 without
saving partial state. Zero input length returns zero without writing output;
a first NUL writes a zero `wchar_t` and returns zero. C-locale input passes
through as an unsigned byte. The single-byte and DBCS paths call
`MultiByteToWideChar` with flags 9. The bitmap selects one or two DBCS bytes;
a lead byte with only one available byte returns -2. Conversion failure writes
EILSEQ (42) and returns -1.

The UTF-8 branch uses the separately emitted 87-byte prefix helper. It accepts
at most two trailing bytes for the single 16-bit output, checks continuation
prefixes and rejects decoded surrogate values. It contains no shortest-form
check. The continuation decoder is inlined in the parent; its archive symbol
does not identify another reviewed physical entry.

`0x00541F37` is the explicit-code-page `__std_get_cvt`, with a Win32 error result
and `RET 8`. It clears the output and a 0x220-byte `CPINFOEXW`, calls
`GetCPInfoExW` and returns `GetLastError` on failure. It fills the page, maximum
width and lead-byte bitmap. The native loop and `format.cpp` both stop before
each range's upper endpoint; preserve that observed behavior. The C-locale flag
stays zero. This entry is distinct from the hidden-result `_Getcvt` ABI.
The archive's 92-byte `_Wcrtomb` body did not match this entry.

## Classification ownership and packed-byte mapping

`_Getctype` returns a 16-byte `_Ctypevec`: page, table pointer, ownership flag
and locale-name pointer. Successful `calloc(256, 2)` yields an owned copy of the
classification table; allocation failure borrows the CRT table with ownership
zero. Its optional duplicated locale name comes from `LC_COLLATE` (index one).
The null-context paths of `_Tolower` and `_Toupper` instead use `LC_CTYPE`
(index two), as the original instructions and SDK sources both show.

The two case methods operate on an integer containing one or two packed bytes.
Their C-locale paths apply ASCII case conversion. Other paths use the current
or supplied classification table, preserve a lead-byte pair and call the shared
mapping wrapper with lower/upper flags `0x100`/`0x200`, output capacity three
and the invalid-input flag enabled. A zero mapping result returns the original
integer; success reconstructs an unsigned byte or a packed pair.

## Mapping buffers and complete boundaries

The 464-byte mapping wrapper caps bounded input at the first NUL, including it
when encountered before the bound. It queries and performs multibyte-to-wide
conversion, queries `LCMapStringEx`, then handles sort keys or maps through a
second wide buffer before `WideCharToMultiByte`. Several later failure paths
retain the queried mapping length: they must not be replaced with a blanket
zero result based on the source's generic failure comment.

Both buffers use the SDK stack/heap allocation protocol, including the size
overflow check, 1,024-byte threshold, eight-byte header, `0xCCCC` stack marker
and `0xDDDD` heap marker. Both cleanup calls target `0x00542556`. That complete
25-byte thiscall destructor reads the pointer from the receiver, skips null or
stack storage and frees only a heap-marked allocation through the previously
reviewed `_free` at `0x0054A540`. The distinct ordinary `_freea_crt` contribution
is 30 bytes and does not match this entry.

Every reviewed ledger span ends exactly at its full archive contribution.
Attested original listings cover every instruction, including alternate returns,
both allocation paths and the GS checks. These contributions have no owned EH
records, trailing tables or additional alignment inside the compared extents.
The existing five-byte exception-count shim at `0x00542036` stays separate.

## Evidence and validation

Private evidence is retained under `.analysis/origin-boundary/conversion/`:
`native.txt` and `mapping-native.txt` are bounded attested Ghidra listings;
the six archive members, `root-comparisons.json` and `reviewed.json` preserve
complete sizes, object hashes, observed relocation destinations and PE import
identities. `audit.py` checks archive extraction, full instruction coverage,
ordinary-byte equality, consistent shared destinations and the complete HIGHLOW
sets. The archive and corresponding sources are from the installed
`VC/Tools/MSVC/14.44.35207` package, under `lib/x86` and `crt/src/stl`.

These are origin/boundary comparisons using observed native relocation roles;
they add no canonical source mapping or exact credit. Tracking and generated
progress pass. All 2,089 protected native inputs and canonical products retain
their hashes. No native input changed, no compiler run was needed, and the
canonical exact replay scope is **zero units**.
