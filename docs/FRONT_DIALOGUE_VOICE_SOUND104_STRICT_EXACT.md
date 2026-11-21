# Front dialogue voice helper — 104B and two 19B strict-exact views

The native `0x004D9B50` helper is now reconstructed in
`src/FrontDialogueVoiceSound104.cpp` as the caller-proven
`Graphics::play_front_dialogue_voice_4d9b50` member. Its complete 104-byte
body strictly replays, including all eleven relocation anchors and
all five native calls:

1. `Graphics::uses_preloaded_music` at `0x00428FA0`;
2. `SoundInf::enqueue` at `0x00428C90` for optional stop and voice start;
3. the card-record stage-flag base view at `0x004640E0`;
4. the indexed stage-flag address view at `0x00411C10`.

The two borrowed accessors are independently strict exact at 19/19 bytes.
`NativeCardRecordArchive` is based at the original global pointer `0x005C6108`;
its stage-voice flag array begins at `+0x91F48+0x36`. The voice command name
uses the original `dummy` string at `0x00571B14`.

The implementation preserves the original queue types (4 for optional stop,
2 for voice start), selector and voice ID, and final byte store of one. The
native caller loads `process_graphics` into ECX immediately before the call,
proving the `Graphics` receiver. The original authored spelling/provenance
remain unknown. The 328-byte SoundInf enqueue parent remains NONEXACT at its
separate source frontier.
