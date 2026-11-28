# UCRT x86 ASCII comparison returns a normalized sign

The full 97B/48-instruction `__ascii_strnicmp` at `0x005669C0` matches SDK
10.0.26100.0 x86 libucrt.lib's `_strnicm.obj` byte for byte in the locked
Japanese TH20 Steamless target. This is the x86 implementation, not the
non-x86 C++ body in strnicmp.cpp. It returns exactly -1, zero or +1 rather
than the folded character difference. The existing extent remains unchanged.

The complete source section has no relocations, PE HIGHLOW fields, owned
data, EH or switch table. Its original three-byte `LEA ECX,[ECX]` at
`0x005669D9` aligns the loop within the 97B instruction extent. Fifteen INT3
after the return precede the next aligned contribution and do not extend this
section. No tail is omitted or replaced with a target-sized prefix.

Count is uint32 in ECX. Zero returns zero before loading either source pointer
or reading string bytes. The helper itself does not validate null pointers
or reject counts above INT_MAX; those checks belong to separate public
wrappers when present. With nonzero count, each iteration reads the left
byte and then the right byte before taking the left-NUL branch. Preserve that
right-side read even if the left byte is already zero.

For nonzero bytes, unsigned comparisons fold only A..Z by adding 0x20;
high bytes and punctuation remain unchanged. A folded mismatch selects -1
or +1 using the unsigned comparison carry. Equal nonzero bytes decrement
count and continue only while it remains nonzero. A terminator compares the
already loaded bytes and returns the same normalized sign. Reaching the
count bound with equal bytes returns zero without another input read.

The installed corecrt_internal.h declares cdecl int with two const char*
arguments and size_t count. The member's MASM procedure debug record describes
three cdecl arguments but records a void return type. The native return
sequence explicitly moves the normalized int into EAX; the assembly debug
void type is not an accurate C return declaration. The generic C++ body is
excluded for ordinary x86 and supplies no proof of this implementation's
return magnitude.

Private `.analysis/origin-boundary/ascii-strnicmp/` retains original member
provenance, the unique full location, complete attested listing, CodeView,
all-byte/CFG comparison and boundary checks. Its separate strnicmp.obj has
no whole ordinary-byte locations for the 49B validator, 89B public wrapper or
343B locale implementation. Those candidates receive no entries. Ghidra
reports no references to this head; a bounded search for that one target also
finds no direct E8/E9 or absolute DWORD encoding candidates. This supplies no
new caller or runtime-use claim.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
