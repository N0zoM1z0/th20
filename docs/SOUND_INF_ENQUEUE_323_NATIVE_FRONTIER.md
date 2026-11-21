# SoundInf command enqueue — 328B strict-exact C++ reconstruction

The original `SoundInf::enqueue` at `0x00428C90` is the shared command-queue
writer used by the music/voice path in the 626-byte FrontInf dialogue-command
Boss at `0x004B9740`.

## Recovered queue protocol

- Acquire `process_locks.slot(11)` with a recursive-mutex lock guard.
- Search command entries `0..30` in order; entry 31 is reserved and is not
  considered by this writer.
- Stop at the first entry whose `type` is zero.
- Publish `type`, then `argument`, copy the 256-byte name with `strcpy_s`,
  and finally set `stage` to zero.
- If all 31 usable entries are occupied, leave the queue unchanged.
- Preserve the native trailing 5-byte no-op diagnostic hook at `0x0040C6B0`; the source reuses the existing `ecl_diagnostic_hint` symbol, without duplicating or crediting the folded helper.

The maintained implementation is `src/SoundInfEnqueue323.cpp`. It uses the
actual `SoundInf::commands` member and a narrow
`NativeSoundCommandArrayView` to preserve the original repeated subscript
calls. The view's `operator[]` at `0x004260D0` is a separate 23-byte strict
exact helper with the native `0x10c` `SoundCommand` stride.

## Complete parent strict replay

The original `SoundInf::enqueue` extent is 328 bytes. The maintained natural
C++ `for` loop, with each native indexed-view access kept at its original
source site, now contributes the complete 328-byte function. All 15 relocation
anchors replay to their original targets: the EH handler and security cookie,
slot-11 lock acquisition, five command-array indexed accesses, secure name
copy, exact diagnostic literal and hook, lock-guard destruction, and final
security-cookie check. The whole body is admitted as a strict match.

The implementation remains ordinary C++ with no assembly, padding, or
post-return bytes. The source-level owner attribution is still conservative:
the native `SoundInf` receiver is proven, while original file/class spelling
and authored provenance remain unclaimed.

`scripts/verify-sound-inf-enqueue.py` runs an ASan/UBSan host test covering
first-free insertion, the 31-entry limit, queue-full behavior, slot reuse,
field publication order, slot-11 unlock and the trailing diagnostic hook. The indexed-view
leaf is replayed independently; the parent function remains a source frontier.
