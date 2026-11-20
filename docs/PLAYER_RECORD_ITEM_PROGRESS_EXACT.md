# PlayerRecord item-progress state machine — five native functions

The PlayerRecord progress state is split across two independent marker groups.
The +0xB8/+0xC0/+0xC4 triplet drives the FrontInf seven-marker array at +0x50;
the +0xCC/+0xD0 pair drives the second marker array at +0x6C.

Five original PlayerRecord methods are restored as ordinary C++:

- 0x004E10E0 — PlayerRecord::advance_progress_cc(int), 187 bytes
- 0x004E11A0 — PlayerRecord::tick_progress_d0(int), 172 bytes
- 0x004E1250 — PlayerRecord::advance_progress_b8(int), 188 bytes
- 0x004E1310 — PlayerRecord::tick_progress_c0(int), 246 bytes
- 0x004E1510 — PlayerRecord::advance_progress_c4(), 86 bytes

advance_progress_cc increments the +0xCC counter, resets its sub-frame
counter at the configured cap, clamps overflow, emits sound 0x2E only while
below the cap, and updates the +0x6C HUD marker group. tick_progress_d0
accumulates the sub-frame value and advances the progress counter every three
frames while the cap is not reached.

advance_progress_b8 maintains the +0xB8 counter, clamps to the configured
maximum, clears the +0xC0 remainder when the cap is reached, and refreshes the
+0x50 marker group. tick_progress_c0 accumulates frames, chooses its threshold
table according to Session mode 4 versus the standard mode, consumes as many
thresholds as necessary, and advances the +0xC4 table cursor. advance_progress_c4
performs the actual one-step increment, emits sound 0x11, and reports result
mode 4 to the native card HUD.

The two original threshold tables are real signed C++ data, not inline byte
sequences or placeholder padding:

- 0x005AFED8 — 31 standard-mode entries: thirty 3 values, then 99999999
- 0x005AFF54 — 10 mode-4 entries: nine 3 values, then 99999999

All five complete function bodies match their original lengths and every
non-relocation byte. All 46 native relocation sites resolve to their original
callee/global addresses. The five functions total 879 bytes, with 695
non-relocation bytes independently matched.

The progress methods call the existing PlayerRecord clamp accessors, the
FrontInf progress-animation routines, the Session mode accessor, the shared
sound owner, and the existing native card-HUD result boundary. No assembly,
padding, hand-authored instruction bytes, or byte-copying is used.
