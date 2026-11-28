# UCRT narrow classification masks, DBCS input and locale restoration

Three complete SDK 10.0.26100.0 x86 libucrt.lib contributions establish library
origins in the locked Japanese TH20 Steamless target. All 467B/192 instructions,
nine REL32/five DIR32 roles and 33 adjacent INT3 bytes are reviewed. Existing
extents remain unchanged, with no owned static data, EH or embedded jump table.

| Entry | Bytes | Instructions | Symbol | Member section |
| --- | ---: | ---: | --- | --- |
| `0x005521D0` | 132 | 57 | `_islower` | _ctype.obj 61 |
| `0x00552260` | 132 | 57 | `_isupper` | _ctype.obj 69 |
| `0x0055A0F2` | 203 | 78 | `__isctype_l` | isctype.obj 21 |

CodeView establishes cdecl int32 results and int32 character arguments.
The locale-specific helper additionally takes an int32 mask and a 32-bit
pointer to `__crt_locale_pointers`. The masks and return widths remain native:
lowercase returns classification bit 2, uppercase bit 1; these are not bool
interfaces normalized to one.

## Current-locale fast paths retain their exact conditions

Both public functions test the independently identified locale-changed word
at `0x005E55DC`. When zero, an unsigned `(c + 1) <= 256` test accepts exactly
-1 through 255. The function reads the initial locale's pctype pointer at
`0x005B2788`, loads the full WORD at index c, and applies its fixed mask.
Other inputs return zero on this path, without obtaining PTD.

When the locale-changed word is nonzero, each function calls the reviewed
required PTD getter, copies PTD+0x4C into a local slot, and passes that slot
to the actual locale refresh helper at `0x00558511`. In-range inputs use the
refreshed pctype pointer. For an out-of-range int, mb_cur_max at locinfo+4
must be greater than one to call isctype_l; otherwise the result is zero.
That call passes the original int, the fixed mask and a null locale pointer,
so the callee obtains the current locale again. No new locale guard or
multibyte synchronization is inserted into these fast functions.

## Isctype_l owns the packed-byte and guard paths

The 203B helper constructs the already reviewed 16B legacy `_LocaleUpdate`.
For signed c in [-1,255], it directly loads the locale's WORD and applies the
caller-supplied 32-bit mask. Other ints enter the Microsoft packed-byte path:
the high byte of the low sixteen bits indexes pctype, and its signed WORD
sign tests the 0x8000 lead-byte flag. A lead byte produces two payload bytes;
otherwise only the low byte is used. Both forms have a following NUL and an
explicit payload length of two or one. This path does not add a public range
validation or require mb_cur_max greater than one.

The original three-WORD output buffer is fully zeroed by a DWORD and WORD
store before calling the reviewed GetStringTypeA adapter at `0x0055D108`.
Arguments retain CT_CTYPE1, the guard's locale pointers, explicit payload
length, locale code page and TRUE. Adapter failure returns zero; success
returns the first WORD AND mask. On both paths, the inlined guard destructor
clears PTD+0x350 bit 1 only when this guard recorded that it disabled sync.
Both exits share the real cookie check; no EH record or separate destructor
entry belongs to this contribution.

## Complete boundaries and retained evidence

Private `.analysis/origin-boundary/narrow-classification/` retains the full
members, independent locations, CodeView pointer/primitive records, attested
listing, complete comparison/CFG/relocation checks and original ledger rows.
Installed sources are `ucrt/convert/_ctype.cpp`, `isctype.cpp` and the public
ctype mask declarations. Existing locale-info, PTD, locale-refresh and narrow
adapter reviews establish every external code/state role. The already reviewed
130B LocaleUpdate constructor and 34B array helper receive no duplicate credit.

There are six INT3 bytes before islower, twelve after each public function,
and three after isctype_l. Treating the latter gap as nineteen INT3 up to the
next inventory entry failed: `0x0055A1C0..0x0055A1CF` contains sixteen real code
bytes omitted from that inventory. Its independent member/initializer review
is the next bounded task; it is not part of isctype_l or accepted alignment.
Other unlocated member shapes remain private negative search evidence.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
