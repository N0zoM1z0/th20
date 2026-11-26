# Player state frame: complete extent and private matching candidate

The native function at `0x004F7430` is the Player state-frame owner. It
selects seven states and then updates common timers, presentation, shots and
feedback. A complete private C++ candidate now reproduces all 3,256 ordinary
bytes of its 4,072B contribution, excluding 204 relocation fields. It is
**not accepted as exact**: independent bindings and member-interface review
remain open, and the candidate has not entered the public source graph.

The locked target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
All Ghidra queries used `scripts/ghidra.py`; their logs attest the target,
database bytes and complete text hash. The proposed name
`Player::update_state_frame` describes the recovered role.

## Native ownership and complete range

The ECX receiver uses Player's state at +0x10, Animation at +0x28, position
at +0x614, timers at +0x644/+0x654/+0x2050/+0x2060, options/history,
shot controller at +0x22B4 and Context at +0x14858. It calls the independently
exact [3,111B main frame](PLAYER_MAIN3111_STRICT_EXACT.md) and
[555B movement](PLAYER_MOVEMENT555_STRICT_EXACT.md). Its caller is the
separate 13B cdecl callback at `0x004FEDA0`. These Player-specific state,
input, damage and item protocols establish authored origin independently
of Ghidra's initial function classification.

| Owned region | Native extent |
| --- | --- |
| Complete code, 1,028 instructions | `0x004F7430..0x004F83FA`, 4,043B |
| One emitted NOP | `0x004F83FB`, 1B |
| Seven absolute switch pointers | `0x004F83FC..0x004F8417`, 28B |
| Complete contribution | **4,072B** |

The body contains 151 direct calls, 73 internal direct branches and 46
HIGHLOW fields. The table adds seven HIGHLOW fields. Every branch and table
entry reaches an instruction head inside the body. Eight following INT3
bytes separate it from the distinct function at `0x004F8420`.

Body SHA-256:
`8e85390503c6bfadf650d6c45cfbf00bd857ccd6c07186ae52332a09286c3df9`.
Complete contribution SHA-256:
`dd0c05c0cff466d2ab0656f35b8a75ebd38f6a650b5c0ed917f390f62e1b0a26`.

The table's cases 0..6 enter at `0x004F7523`, `0x004F7824`, `0x004F79F5`,
`0x004F7F24`, `0x004F7920`, `0x004F7FB1` and `0x004F7492` respectively.

## Recovered state behavior

- State 6 resets the age and assigns the initial float and fixed positions.
- State 0 slides the Player into the playfield, refreshes history, cancels
  nearby bullets/lasers and creates a damage circle. At frame 60 it enters
  normal operation during the same update.
- State 1 checks the game flag, BombController and replay-pressed mask 4,
  then calls the normal main frame. Controller lookups remain separate.
- State 4 provides the timed bomb opportunity before entering state 2;
  a successful bomb resets the Player to state 1 with age 60.
- State 2 applies the option-dependent power loss, creates seven item drops,
  rebuilds options and performs the frame-30 life/respawn transition.
- State 3 preserves the otherwise unused comparisons at frames 4 and 30
  around the frame-15 laser cancellation.
- State 5 applies direction-based movement with a decreasing scale and
  returns to state 1 at frame 40.

The common tail decrements protection timers, selects the Animation +0x4A1
color mode, clears extra motion, updates animation/expansion interpolation,
advances two timers, updates shots and feedback, and returns one. The color
field is `flags.bits_09.color_mode`; the earlier private raw-byte hypothesis
used the wrong +0x499 field and was corrected before the matching candidate.

## Compiler findings

The private candidate uses locked MSVC 19.44.35211 x86 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The useful progression was:

| Private source/control | Code / instructions | Complete contribution |
| --- | ---: | ---: |
| Initial complete state implementation | 4,163B / 1,038 | 4,192B |
| Corrected branches and real color bitfield | 4,148B / 1,041 | 4,176B |
| Literal float call arguments | 4,036B / 1,027 | 4,064B |
| `/sdl`, direct world assignment and explicit state transitions | 4,026B / 1,028 | 4,056B |
| Braced position assignments and corrected case-4 break scope | **4,043B / 1,028** | **4,072B** |

External float variables introduced argument spills across nested getter
calls. Using the genuine literals 640, 120, 80, 32, 16, 4 and 3 removes those
spills. `/sdl` restores the native receiver home at `[ebp-0x20]` and the
0x188 frame. Braced Vector3/IntPoint assignments recover the original
constructor temporary locations and direct field copies. Explicit transitions
preserve the state-0/state-4 jumps; placing the case-4 `break` outside its
`else` also recovers the native unreachable jump target.

The final audit matches all 1,028 mnemonic ordinals, 73 branch destinations,
344 frame operands, 202 ordinary immediates and every ordinary register
operand. All 151 calls remain; 121 use existing canonical anchors and 30 use
newly inferred member interfaces. C++17 did not change the earlier spill
candidate. Forcing C++17 library features into C++14 failed to compile and
was rejected. Reuse the retained controls.

## Independent binding frontier and next work

Nine private header copies hold the new interfaces. Their exact diff is
retained; public headers remain unchanged. In particular, the feedback update
returns void, while the shot-controller update returns an integer. The
Identifier32 damage operation and other new methods still need interface
review before integration.

Existing canonical bindings cover many constants through aliases. Bounded
attested cross-reference queries provide other consumers for the 512, 64,
80 and 120 floats and the screen-transition global. The zero Vector3 at
`0x00572664` has only one known reference, in this same root. Its twelve zero
bytes corroborate the value but do not independently resolve its address for
this comparison. Do not populate a canonical destination from that field.
This anchor is the next evidence question.

**Public canonical replay scope is zero.** No maintained executable input or
acceptance unit changed. Promoting all nine current interface hypotheses would
expand the captured include closure to 1,146 units from 313 source providers;
rederive the affected scope after settling the interfaces. Mapping and authored
origin are recorded now; source presence and exact credit remain unchanged.

Private evidence is in `.analysis/player-state4043-session/`: attested
`decompile.txt`, `callees.txt`, `owner-callbacks.txt` and query logs;
`native-extent-proof.txt`; `boundary-audit.py/json/txt`; `data-xrefs.txt`;
`header-hypotheses.diff`; and the complete maintained-style candidate in
`private/PlayerStateFrame4043.cpp`. Current objects/receipts are under
`build/gpt61-player-state-probe/`; `case4-boundary.obj` is the final candidate.
Preserve earlier exact Player products and these useful private controls.
