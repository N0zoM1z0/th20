# Enemy whole-root opcode 548: true FrontInf stage-title chain (CORE181)

The fixed native target remains Japanese TH20 v1.00a Steamless PE32,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The full `EnemyState::execute_opcode()` at `0x0048C010` is a **single
41,967-byte root**, still **not byte-exact**. This private checkpoint adds
one complete real caller path to the previous private natural-source root;
no Enemy branch fragment is registered as an independent exact function.

## Complete original native 548 case and real owner chain

The original opcode 548 interval is **`0x0048C5C1`–`0x0048C5D2`
(end exclusive), 17 bytes / 4 instructions**, with the only direct call at
**`0x0048C5C7` → `0x004B96F0`**. The root loads the genuine published
`FrontInf*` at `0x005C06A4`, calls `FrontInf::show_stage_title` on it and
jumps directly to the common root exit. There are **zero ECL operand reads**.
The independently decoded original bytes, complete case hash and call target
are preserved in `.analysis/core181-enemy-548-native-audit.json`.

[CORE/EXACT-180](ENEMY_OPCODE_548_STAGE_TITLE_EXACT_RECONSTRUCTION.md)
accepted the **complete 75-byte** FrontInf stage-title function with its five
authentic relocations, and the complete **20-byte Graphics field_b0c getter**
and **23-byte Session bit5 getter**. The original typed, source-compiled method
reads process Graphics at `0x005C4D40`; if mode is exactly 8, it returns
without touching Session or the AnimationFile. Otherwise, if Session
`flags.bits` bit5 is set, it also returns without a spawn. Only for the
remaining conditions does the real `FrontInf::message_file` at owner+`0x170`
call the *production* native four-argument `AnimationFile::spawn` wrapper
with `(nullptr, 0, -1, nullptr)`.

## One complete-root host, no substitute service

The current single root uses `case 548: current_front->show_stage_title()`.
The genuine FrontInf, Graphics, Session and four-argument AnimationFile
implementation are executed, as are all the earlier 37,985 complete-root
cases from CORE179. The unresolved **seven-argument Renderer/Animation VM**
producer alone is a captured test boundary; that capture checks every native
argument, preserves the returning four-byte AnimationHandle semantics, and
can throw to exercise cleanup/error propagation. No new Stage services,
fictitious globals or stub production owners are introduced.

A newly compiled **80-translation-unit** O2/UBSan whole-root host passes
**38,241/38,241** scenarios. This adds **256** full opcode548 caller tests
covering eight Graphics modes, eight Session flag patterns, two active
FrontInf pointers and two spawn-failure choices. **112** enabled conditions
forward to the actual four-argument AnimationFile wrapper; disabled conditions
must not call the downstream renderer. All tests verify **complete byte
images** of both FrontInf owners, genuine process Graphics, genuine process
Session and the EnemyState, plus the original zero-operand behavior. An
underlying renderer exception may propagate only when the original native
guards permit a call; the selected FrontInf remains the same cached receiver.

`.analysis/core181-enemy-whole-root-proof.json` contains **97** source and
fixture input SHA-256 identities, the newly compiled host executable and
run-log hashes, original whole-case opcode byte hash, and proof that every
CORE179 native draft/host/fixture/log input remains unchanged. All **164**
currently accepted pinned MSVC object and receipt identities validate; no
maintained exactness unit changed in CORE181. The original executable is
unmodified.

## Scope and remaining big-function work

CORE181 takes the private complete-root semantic draft to **122 effective
opcode values / 93 original primary heads**. The source-accepted exact graph
remains **217 full authored functions / 57,008 native bytes / 1,003 strict
units**; the **17-byte** 548 case contributes **zero** partial native root
credit. Original 539, 555 and other missing long case paths, full 174-head
primary index, four nested rank tables, shared case exits, original compiler
EH/data, and native Renderer/Background/Stage startup and resource lifecycle
are still open. This portable host is not a playable Windows game.
