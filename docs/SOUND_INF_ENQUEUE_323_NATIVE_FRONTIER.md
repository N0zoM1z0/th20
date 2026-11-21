# SoundInf command enqueue — 328B native C++ source frontier

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
- Preserve the native trailing `_Adl_verify_range` diagnostic-helper call.

The maintained implementation is `src/SoundInfEnqueue323.cpp`. It uses the
actual `SoundInf::commands` member and a narrow
`NativeSoundCommandArrayView` to preserve the original repeated subscript
calls. The view's `operator[]` at `0x004260D0` is a separate 23-byte strict
exact helper with the native `0x10c` `SoundCommand` stride.

## Parent remains NONEXACT

The original `SoundInf::enqueue` extent is 328 bytes. The current pinned MSVC
C++ candidate contributes 330 bytes; the remaining two-byte control-flow
shape difference is intentionally left visible. There is no strict parent
match unit or exact-byte credit. The implementation is ordinary C++ and uses
no assembly, padding, or post-return bytes.

`scripts/verify-sound-inf-enqueue.py` runs an ASan/UBSan host test covering
first-free insertion, the 31-entry limit, queue-full behavior, slot reuse,
field publication order and the trailing range-check call. The indexed-view
leaf is replayed independently; the parent function remains a source frontier.
