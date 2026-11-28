# UCRT code-page tables and the six-byte UTF-8 reset

Four pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` `mbctype.obj` contributions. All 1,099 code bytes
and 308B of classification/range/name data agree with the locked Japanese TH20
v1.00a Steamless target, including complete branch and HIGHLOW sets. The UTF-8
path clears only the first six ctype bytes. The source comment describing a
whole-table clear does not match either its loop bound or the target stores.

## Complete entries and owned tables

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0055E92A` | 62 | `CPtoLocaleName` |
| `0x0055E9D9` | 99 | `setSBCS` |
| `0x0055EA3C` | 421 | `setSBUpLow` |
| `0x0055EE31` | 517 | `_setmbcp_nolock` |

All four sections are complete and have unchanged ledger boundaries. There
is no owned code alignment or EH table. Data includes the four flag bytes at
`0x005B2E28`, all five 48B code-page records at `0x005B2E30`, the full four-pointer
locale-name array at `0x0059A9F0`, and four complete 12B UTF-16 strings at
`0x0059AA00`, `0x0059AA0C`, `0x0059AA18` and `0x0059AA24`. The four linker
zero-alignment bytes at `0x005B2E2C` are also retained.

The record IDs are 932, 936, 949, 950 and 1361. Each includes six full-width
mapping words and four eight-byte range arrays. Flags 1, 2, 4 and 8 mean
single-byte symbol, punctuation, lead byte and trail byte respectively. Range pairs stop
on a zero endpoint, use inclusive bounds and set ctype at byte index plus one
to preserve the EOF slot. The locale-name helper maps only 932 to `ja-JP`,
936 to `zh-CN`, 949 to `ko-KR` and 950 to `zh-TW`. Other values return null;
1361 has a built-in classification record but no locale-name mapping.

## Population branches and original failure behavior

The cdecl population function first calls the
[reviewed code-page resolver](CRT_MULTIBYTE_UPDATE_BOUNDARY_REVIEW.md).
Code page zero delegates to SBCS reset and returns zero. A built-in record
clears all 257 ctype bytes, applies its four range groups, sets the code page
and multibyte flag, assigns the mapped locale name, copies all six full-width
words and generates the case map.

For other pages, UTF-7/65000 is rejected before the validity query.
`MOVZX EAX,BX` at `0x0055EE8E` supplies only the low 16 bits to IsValidCodePage
at `0x0056C13C`. The later GetCPInfo call at `0x0056C190` receives the full
32-bit code page. These widths cannot be merged into a single validation rule.
Invalid pages return integer -1 without adding an errno write here.

A successful OS query clears all 257 ctype bytes and sets the code page.
Only `MaxCharSize == 2` receives lead-byte flags from the API ranges and trail
flags for byte values 1 through 254. Values 0 and 255 are excluded from that
trail loop. This branch sets the mapped locale name and multibyte flag; other
character widths keep both null/zero. Both paths zero all six full-width words
and generate case mappings. Failed GetCPInfo falls back to SBCS only when
`fSystemSet` is nonzero; otherwise it returns -1.

The resolver resets `fSystemSet` on each call. In the reviewed 341B setter,
the request is resolved before this function is called. Resolving that already
positive code page again clears the earlier system-request flag. Preserve this
double resolution rather than carrying the first call's flag into the fallback.

## UTF-8 preserves old classification bits

After validity succeeds for 65001, the setup writes code page 65001 and clears
the locale-name pointer and multibyte flag. It clears ctype with exactly these
stores:

| Native store | Structure offsets | Ctype indices |
| --- | --- | --- |
| DWORD at `0x0055EEB2` | +0x18..+0x1B | 0..3 |
| WORD at `0x0055EEB5` | +0x1C..+0x1D | 4..5 |

The source uses `NUM_ULINFO` (six) for this ctype loop. Three STOSD instructions
then clear the separate six-word full-width mapping array. The branch reaches
the ASCII fallback in `setSBUpLow`, which ORs upper/lower flags into ctype and
rewrites every casemap byte. It does not clear the other ctype bytes, so prior
flags at indices 6..256 survive.

A bounded byte-footprint model uses the decoded store widths, complete ASCII
fallback and original CP932 range record. It retains lead/trail bits 0x0C for
byte 0x82 across this UTF-8 path. This records a source/native consequence;
the model invokes neither Win32 conversion nor the game. Do not replace the
six-byte reset with a 257B clear during later reconstruction.

## SBCS defaults and case generation

The 99B SBCS helper resets code page, multibyte flag, locale name and six
full-width words. It clears ctype and then copies all 257 default ctype bytes
and all 256 default casemap bytes from the initial object. The original
clear-before-copy remains. The refcount is untouched. Initial data and global
state are reused from the complete prior synchronization review.

The 421B case helper retains its full GS-protected 0x720B stack frame. For
non-UTF-8 pages with successful GetCPInfo, it builds the 0..255 byte vector,
substitutes space for zero and lead bytes, then calls GetStringTypeA and both
lower/upper LCMapStringA adapters. All three return values are ignored before
their stack outputs are consumed. Upper classification takes priority over
lower; corresponding flags are ORed into ctype while opposite-case values are
stored in casemap. Nonletters receive zero casemap values.

UTF-8 or failed GetCPInfo selects ASCII A..Z/a..z classification and opposite
case, with zero casemap elsewhere. Both paths preserve pre-existing ctype bits.
The separate adapter providers at `0x0055D108` and `0x0055D3F3` remain pending;
their named call roles give no body credit in this review.

## Evidence and affected scope

Private `.analysis/origin-boundary/multibyte-population/` retains bounded
attested case/population listings, `review.py` and `reviewed.json`. It reuses
the unchanged SDK member and locale-name-helper listing in `multibyte-update/`.
The audit checks all four whole code sections, seven whole data sections,
every branch/callee/import/HIGHLOW field, complete sparse range records and
UTF-8 store widths. Installed source is `ucrt/mbstring/mbctype.cpp`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
