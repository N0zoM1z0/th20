# Recovered UCRT SSE2 math initializer and startup-table record

The missing 16B/5-instruction entry at `0x0055A1C0` is
`___acrt_initialize_sse2` from SDK 10.0.26100.0 x86 mathfcns.obj.
Its complete section has a unique ordinary-byte location in the locked
Japanese TH20 Steamless target. Both DIR32 roles are independently checked
against the PE import identity and the SSE2 math state already used by the
reviewed dispatchers. The original extent ends at `0x0055A1CF`, immediately
before CIacos; the preceding three bytes are INT3, outside isctype_l.

The entry pushes feature ID 10, `PF_XMMI64_INSTRUCTIONS_AVAILABLE` in the
installed winnt.h, and calls KERNEL32.dll!IsProcessorFeaturePresent through
IAT `0x0056C17C`. It stores the complete BOOL/EAX at `0x005E59AC`, then clears
EAX and returns. CodeView identifies cdecl int32 with no arguments. The return
is always zero, including when the feature query reports no SSE2 support;
it is not a boolean report of initializer failure.

The member defines `___use_sse2_mathfcns` as a four-byte common symbol. Its
previously identified linked instance at `0x005E59AC` lies entirely in the
PE's zero-filled virtual data tail. This initializer supplies the startup
write consumed by the reviewed math dispatchers. The member's separate 41B
set_SSE2_enable contribution has no complete ordinary-byte location and
receives no entry or reviewed credit here.

The independent sse2_initializer.obj supplies the complete four-byte
`.CRT$XIC` record named `___acrt_tran_sse2_initializer`. Its sole DIR32
selects the independently located function at original field `0x0056C42C`.
The reviewed startup owner delimits `__xi_a = 0x0056C418` and
`__xi_z = 0x0056C43C`; this record is inside that C-initializer range.
The full forty-byte context retains both zero delimiters and all eight
nonnull HIGHLOW fields. The original data reference selects the same entry.
The reviewed initterm_e therefore receives an int-returning C initializer,
whose zero result permits traversal to continue.

Private `.analysis/origin-boundary/sse2-initializer/` retains both complete
members, archive provenance, unique location, CodeView, attested instructions
and data reference, complete comparisons and the original table context.
The registration member's guard-FID symbol index also names this function;
there is no owned EH or embedded table in its code. Public source
`ucrt/initializers/i386/sse2_initializer.cpp` establishes the registration
and cdecl int declaration. The matching native math implementation source
is absent from the installed snapshot; its full object/native body supplies
the five-instruction implementation evidence.

One recovered library row is added; no old extent changes. Owned data is
the four-byte initializer record and four-byte common state. Tracking/progress
checks pass, all 2,151 protected hashes remain unchanged, and exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
