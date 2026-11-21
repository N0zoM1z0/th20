# FrontInf dialogue command — 626B native boss source frontier

The original `FrontInf::set_dialogue_command` at `0x004B9740` is the 626-byte
boss reached by Enemy ECL opcode 518. Its maintained implementation is
`src/FrontInfDialogueCommand626.cpp` and is ordinary C++ against the real
`FrontInf`, `Dialogue`, `Card`, `Graphics`, and `SoundInf` owners.

## Recovered branches

- `-1` / `-3`: select one of the two native voice-table entries, preserve the
  `Session::field_70_is_two` and `GameController::restart` duplicate-track gate,
  append `.wav`, compare the actual `SoundInf+0x2444` queued name, then enqueue
  the voice, set its stage flag and spawn the corresponding FrontInf message
  animation.
- `-2`: call `card(0)`, test the native card end flag and route to the original
  screen-transition or GameController transition path.
- Other commands: release the existing Dialogue through the native
  ECX-receiver/stack-argument ABI, clear the FrontInf pointer, read the script
  offset from `message_bytes + command*8 + 4`, allocate the new Dialogue and
  publish the command into its first state field.

The current pinned-MSVC candidate is **622/626 bytes**. The 4-byte difference
remains explicit; there is no parent strict match unit and no exact-byte credit.
The ordinary C++ implementation preserves the native duplicate pointer clear
and message-table offset lookup. It uses no assembly, padding or post-return
bytes. The 156-byte allocator callee now uses a class-specific
`Dialogue::operator new` to preserve the native raw-storage clear before the
real constructor. A direct `new Dialogue(std::move(script))` lets the compiler
generate the matching sized-delete unwind path when construction throws. The
pinned candidate is 168 bytes against the 156-byte native contribution and
remains NONEXACT; no bytes are credited until the complete contribution and
relocation set match.

## Exact voice dependency

The 104-byte `0x004D9B50` voice helper is now a separate strict-exact
`Graphics::play_front_dialogue_voice_4d9b50` member. Its original caller at
`0x004B9890` explicitly loads `process_graphics` into ECX before the call,
proving the Graphics receiver. It preserves the five native calls:
preloaded-music check, two SoundInf queue writes, card-record stage-flag base
(`0x004640E0`) and indexed flag address (`0x00411C10`). Both 19-byte offset
helpers are strict exact as well. The original authored spelling/provenance
remains unproven; no parent completion is inferred from these leaves.

The opcode-518 dispatcher fragment is wired through
`src/EnemyStateDialogueOpcode.cpp`, then performs the original Bullet, Laser
and Enemy controller cleanup. The 41,967-byte `EnemyState::execute_opcode`
root remains NONEXACT.
