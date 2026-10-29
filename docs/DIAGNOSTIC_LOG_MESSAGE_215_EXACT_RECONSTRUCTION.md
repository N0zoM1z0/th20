# CORE/EXACT-496 — original 215B append-only logger vs. 221B error logger

Immutable TH20 Japanese v1.00a Steamless target SHA256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The entire original `0x00454150` is **215/215 bytes,
57 original instructions** strictly exact, native SHA256
`6e98263ac26c5c19ed5be59da3b0befebafe4c8b6949caba8ebffa057d772c3a`.
The new maintained `th20::report_log_message` source name is
descriptive, not a claim that the original C++ spelling is known.

This is **not** the already exact 221-byte
`th20::report_log_error` at `0x00454230`, original SHA256
`18ddaad24b3f7c16f3b147761b560110f33899113af9a38ea25d72196a7a7f9c`.
Both use the real recursive-mutex slot 3, a 1,024-byte stack
buffer, CRT secure variadic formatting, and append through a genuine
`std::pmr::string`. Only the 221B error entry writes
`DiagnosticLog::error = 1` at receiver offset +0x1C.
The 215B original has no such write; it preserves the independent
error state and naturally emits the original NOP at that location.

The complete 215B body has **seven E8/REL32 and three original
PE HIGHLOW/DIR32** reference fields: original EH descriptor
`0x005687D0`; cookie `0x005B25C0`; lock registry
`0x005C0240`; lock selector `0x0040C310`;
lock guard constructor/destructor `0x0040B730/0x0040B900`;
`memset` `0x00544760`; native `vsprintf_s`
helper `0x00452D60`; PMR append `0x004530A0`;
and cookie check `0x005429EE`. All ten original
PE field offsets, types, targets, actual COFF symbols
and addends were attested independently:
`.analysis/core496-diagnostic-message-original-pe-proof.json`.
Whole strict comparison accepts **175/175 original nonrelocated
bytes and 40/40 relocation bytes**.

The original whole 726B `InputInf::discover_directinput_devices`
contains **five** E8 calls to this 215B physical address;
the original 218B `InputDevice::initialize_directinput`
contains **one** more. Their original six physical destinations are
`0x00454150`, NOT the 221B error-flagging entry
`0x00454230`. The maintained source and canonical compiler
symbol fields now point to the correct normal-log function,
with all original bytes of both 726B/218B callers preserved.
Their previous type-level misidentification was corrected.

Original pre-edit `DiagnosticLog.hpp` compiler receipts
selected exactly **four source providers / five previous strict units**:
`src/DiagnosticLog.cpp`, the two DirectInput owners, and
`src/ProgressFileWrite.cpp`. New and existing logging methods
and their callers passed **6/6 strict original units in four
source-filtered cold objects**, low priority:
`.analysis/core496-diagnostic-message-scoped-replay.log`.
No global replay was performed.

**New distinct original game credit: one 215-byte native
game-authored function.** Neither the prior 221B error logger
nor the 726B/218B whole-exact callers receive extra byte credit.
