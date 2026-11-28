# UCRT UTF-8 state, counts and surrogate boundaries

Ten pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions. All 1,554 code bytes and 17B of
owned state/literal data agree with the locked Japanese TH20 v1.00a Steamless
target, including complete branches, HIGHLOW fields and callee roles. The
single-character replacement, string surrogate output, resumed-byte count and
state changes before short-buffer exits are distinct original contracts.

## Complete entries and state layout

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x005593CA` | 65 | leading-byte `__mblen_utf8` |
| `0x0055940B` | 441 | scalar decoder `__mbrtoc32_utf8` |
| `0x005595C4` | 171 | surrogate encoder `__c16rtomb_utf8` |
| `0x0055966F` | 44 | string decoder's available-byte lambda |
| `0x0055969B` | 67 | single-wide-character `__mbrtowc_utf8` |
| `0x005596DE` | 275 | string decoder `__mbsrtowcs_utf8` |
| `0x00563CEB` | 174 | scalar encoder `__c32rtomb_utf8` |
| `0x00563D99` | 20 | `reset_and_return` |
| `0x00563DAD` | 34 | `return_illegal_sequence` |
| `0x005652D2` | 263 | string encoder `__wcsrtombs_utf8` |

The complete intervals are `0x005593CA..0x005597F0`,
`0x00563CEB..0x00563DCE` and `0x005652D2..0x005653D8`. Existing ledger sizes
remain unchanged. There is no owned alignment or EH contribution. The
decoder and string encoder retain their GS checks.

mbstate_t is eight bytes: DWORD `_Wchar` at +0, WORD `_Byte` at +4 and WORD
`_State` at +6. Decoder initialization tests the full state WORD, then resumed
length/remaining counts use the low bytes at +4/+6. Saved counts are written
back as WORDs. Null state selects the complete loader-zero eight-byte decoder
state at `0x005E5670` or separate c16 encoder state at `0x005E5678`. These are
shared static objects, not added thread-local storage. The owned empty input
literal is one byte at `0x00570AFC`.

## Scalar decoding and single-character replacement

The leading-byte helper only classifies length: ASCII/null returns 1/0,
C0..DF returns 2, E0..EF returns 3, F0..F7 returns 4, and other high bytes
return -1. Complete validity is checked by the scalar decoder afterward.

The decoder substitutes empty input with length one and null output for null
input. Otherwise zero available bytes return INCOMPLETE/`0xFFFFFFFE` without
reading input or resetting state. Initial ASCII/null returns directly. Longer
input accumulates continuation bytes, retaining partial scalar, original
length and remaining-byte count when incomplete. A resumed state requires
length 2..4 and remaining count 1..length-1.

Completed decoding rejects malformed continuations, surrogates, values above
0x10FFFF and overlong values below 0x80/0x800/0x10000 for lengths 2/3/4.
Completed multibyte success writes the optional DWORD scalar and clears all
eight state bytes. The initial ASCII/null fast path returns without that reset.
Its nonzero result is the bytes needed **in this call**, including when
completing a previously partial sequence; it is not always the original
sequence length.

The 67B mbrtowc adapter writes a WORD only for unsigned results 0..4. A scalar
above 0xFFFF becomes U+FFFD; it does not return a surrogate pair. INVALID and
INCOMPLETE leave that optional output untouched. It returns the original
primitive result. By contrast, the string decoder emits both UTF-16 units
when a supplementary scalar fits.

## String decoding and resumed-count consequence

The 44B lambda inspects at most the first three source bytes, returning 1/2/3
when it encounters a null there and 4 otherwise. Its real member-call ABI pops
one explicit pointer argument. It supplies a bounded available count to the
scalar decoder without blindly requesting four bytes past a terminator.

Output mode stops before decoding when its UTF-16 capacity is zero. INVALID
stores the offending source position and caches EILSEQ. A null writes a UTF-16
terminator, sets the caller's source pointer to null and excludes the terminator
from the result. BMP values use one unit; supplementary values use two. If
only one unit remains for a supplementary value, no source/output advance is
committed, but the primitive has already decoded and reset its state. No state
rollback is added.

Null-output counting ignores the output limit and leaves `*src` unchanged,
while still operating on the supplied state. It counts two UTF-16 units only
when the primitive's return is 4. A bounded model starts with partial state
after `F0 9F`, then supplies `98 80 00`: the scalar is U+1F600, but the resumed
primitive returns two remaining bytes and this query counts one unit. Output
would require two units. With one output unit it instead returns zero with
unchanged source and cleared state. This source/native consequence is retained
rather than correcting the count or restoring the state.

## Scalar/surrogate encoding and short-buffer state

The c32 encoder emits one through four UTF-8 bytes, rejecting surrogate scalars
and values above 0x10FFFF. Multi-byte output is filled backward from trail
bytes before its lead byte. Null output or a null character clears state and
returns one; the null character also writes zero. Nonzero ASCII writes one
byte and returns without clearing state. The primitive does not supply an
extra fallback state for null ps.

The c16 encoder uses `_Wchar` alone to remember a shifted high surrogate.
A high surrogate initially returns zero without output; a lone low surrogate
fails. With a saved high half, only a low half is accepted. It combines them,
encodes with a fresh temporary state and resets the caller's full state.
Ordinary units delegate directly to c32. Output-pointer handling remains in
the delegated primitive rather than a new validation-first branch.

The string encoder writes directly only with at least four output bytes;
otherwise it calls c16 into a five-byte temporary, then checks whether the
result fits. Thus a zero-byte limit still invokes the encoder and can read or
consume surrogate state. Failure reports the start of the current code point;
a non-fitting result rewinds the source to that same position. Neither path
rolls back primitive state changes. With an already saved high half and only
the low half as input, an insufficient three-byte output returns zero and
leaves the source unchanged, but clears the saved high-half state.

A copied null sets `*src` to null and excludes its byte from the result. Other
committed characters advance the source, byte count and remaining limit.
Counting mode always encodes into the temporary, ignores the output limit and
leaves `*src` unchanged, while retaining normal state/error effects.

The common reset helper clears all eight bytes and returns its supplied
size_t unchanged. Illegal-sequence handling does the same reset, writes cached
EILSEQ/42 and its validity byte in the PTD host, then returns INVALID/
`0xFFFFFFFF`. It does not immediately call the global errno getter.

## Evidence and affected scope

Private `.analysis/origin-boundary/utf8-conversions/` retains SDK members
`mbrtowc.obj`, `wcrtomb.obj`, `mbrtoc32.obj`, `c16rtomb.obj`, `c32rtomb.obj`
and `common_utf8.obj`, complete attested listings, `review.py`, `reviewed.json`
and the bounded `edge-model.py/.json`. The audit compares ten whole code
sections and all three owned data sections, every instruction/branch/relocation,
shared scalar/state roles and exact field widths. The edge model covers the
specific resumed supplementary scalar and short-output decisions above; it
does not execute Win32 or the game. Installed implementation is in the six
corresponding `ucrt/convert/*.cpp` files plus `corecrt.h` and
`corecrt_internal_mbstring.h` for layout/sentinels.

This completes the UTF-8 providers called by the reviewed
[mbstowcs](CRT_MBSTOWCS_SECURE_ORIGIN_REVIEW.md) and
[wcstombs](CRT_WCSTOMBS_SECURE_ORIGIN_REVIEW.md) owners. Memcpy remains a
separate pending body; its named call role gives no body credit here. Only
classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
