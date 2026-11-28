# UCRT stricmp difference results and locale synchronization

Three complete SDK 10.0.26100.0 x86 stricmp.obj contributions match the locked
Japanese TH20 Steamless target: 448B/170 instructions and eleven REL32/four
DIR32 roles. The existing 40B validator at `0x00555720`, 120B `_stricmp` at
`0x00555750` and 288B `_stricmp_l` at `0x005557D0` retain their extents. All
five internal NOP bytes and both eight-byte INT3 gaps are checked. No owned
data, EH or switch table belongs to these sections.

CodeView establishes cdecl int32 returns, with two const char* arguments
and an additional locale pointer for `_stricmp_l`. These functions preserve
actual folded-character differences. For example, the public initial-locale
path returns -2 for `A` versus `c`, unlike the normalized -1 from the
[separate x86 bounded helper](CRT_ASCII_STRNICMP_ORIGIN_REVIEW.md).

The 40B validator checks left then right. A null stores EINVAL/22 through the
reviewed global errno getter, calls the returning no-info invalid-parameter
handler and returns `_NLSCMPERROR`/0x7FFFFFFF. With both arguments nonnull,
it still returns that sentinel but does not assign errno or call the handler.
This private entry's result is not a bool.

Public `_stricmp` first tests the reviewed locale-changed DWORD. Zero selects
its own null checks and then the inline ASCII loop; failure calls the validator.
The loop reads both bytes as unsigned values, folds A..Z only when their raw
values differ, subtracts the resulting ints and stops on difference or left
NUL. It has no count limit. A changed locale calls `_stricmp_l` with the same
strings and a null locale argument. It does not call the separately emitted
72B ascii_stricmp contribution, whose whole signature has no target location.

The locale API validates left and then right before acquiring locale state.
Either failure assigns global EINVAL, calls the same handler and returns the
full sentinel if execution resumes. Explicit locale copies its two pointers
without obtaining PTD or changing synchronization. Null locale with an
unchanged global locale uses the reviewed initial pointer pair. Otherwise it
obtains required PTD, snapshots locale/multibyte pointers at +0x4C/+0x48 and
calls both actual refresh helpers.

In the PTD path, `_own_locale` at +0x350 is tested for bit 2. Only if initially
clear does this owner set it and record its own restoration obligation.
The comparison snapshots the lowercase-byte map at locinfo+0x94, maps each
unsigned input byte through it and returns the int difference. It does not
decode multibyte characters or use a signed char as the table index. Both
unequal and NUL-equal exits clear sync-disable bit 2 only if this call set it;
a previously set bit, explicit locale and initial-pointer path are retained.
The inlined `_LocaleUpdate` protocol agrees with its
[reviewed standalone owner](CRT_LOCALE_INFO_COPY_ORIGIN_REVIEW.md).

Private `.analysis/origin-boundary/ascii-stricmp/` retains the original member
and provenance, three unique full locations, CodeView, complete attested
listing and all-byte/relocation/CFG comparison. Existing errno/handler/PTD,
locale refresh and initial-global identities are reused. The 72B standalone
ASCII body receives no entry. Source is `ucrt/string/stricmp.cpp` and the
locale guard/lowercase helpers in corecrt_internal.h.

The neighboring memory-comparison check in private `ascii-memicmp/` found
no whole ordinary-byte locations for the 89B x86 ASCII, 336B public or 307B
locale contributions. Both original members and the negative locations are
retained; no memory-comparator entry receives credit from these string owners.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
