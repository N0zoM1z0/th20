# Reconstruction roadmap

Bootstrap, locked-target/Ghidra setup and the exhaustive pinned-reference review
are complete. Current reconstruction counts and open boundaries are recorded in
[the handoff](RE_HANDOFF.md), [progress](PROGRESS.md) and the source/match ledgers.

1. Reconstruct the **12,140B original Bullet extended-command Boss parent**
   directly, not just its exact leaves. All **210 original native E8** calls
   are decoded; **208/210** have whole-native-exact game-callee source and
   the remaining two are **compiler runtime helpers**, not absent game
   source. The original **34+8+11** switch architecture, **53 PE HIGHLOW
   switch pointers** and 38 function-body HIGHLOW are independently known;
   the parent is still **SOURCE-ABSENT / NONEXACT**. [Current original CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md),
   [original PE call verifier](../scripts/verify-bullet-command-call-coverage.py).
2. Recover the **5,993B 49-mode Animation Draw dispatcher**, which is
   **SOURCE-PRESENT, NONEXACT** despite a native-length 5,993B/1,501-x86
   candidate and 49+31 original switch pointers. All 123 E8 callee
   targets are known but only 86 physical E8 sites currently align;
   the mode35/36 x87 spill and late SSE/stack layout remain open.
   The separate **3,159B quad-submit Boss is already whole strict
   exact** (3,180B with genuine NOP and table), as are its 2,725B
   texture/sampler and 1,163B blend-state children. The historical
   3,212B quad candidate is superseded. [Current Draw frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md),
   [accepted quad-submit proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md).
3. Attack the **827B polygon dynamics Boss** next to its already
   whole-exact **140B group tick** and seven original-native-exact
   counted-range iterator helpers: reconstruct the two real range
   factory, sentinel, comparison and loop-bound sequences rather than
   claiming the current 513B/137-x86 high-level candidate exact.
   Then resolve the **104B polygon-outline wrapper** ESI lifetime and
   **1,486B rotated-corner projection** native constructor NOP.
   Continue the **3,111B Player main**, **555B Player movement**, and
   **273B Bullet draw group** native codegen gaps. [Polygon frontier](ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md),
   [104B wrapper](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md),
   [Player operand frontier](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md).
   The **3,735B Bullet emitter, 1,404B command-11 and 73B Animation
   factory** are already whole strict exact; do not reopen old hypotheses.
4. Reconstruct full source and control flow of the **39,470B Animation
   VM update** and separate **41,967B Enemy ECL opcode dispatcher**;
   exact child parsers and typed Laser lifetimes do not close either
   parent. Keep review of actual Renderer/callback/packet ownership
   and original 704-byte Enemy opcode index grounded in PE evidence.
5. Resolve remaining whole nonexact native game functions and compiler/
   STL codegen frontiers (including the original 470B Bullet vector
   counted-range helper); keep library methods **excluded** from
   authored-game credit. Complete original process-global initialization
   and resource lifetime contracts.
6. Assemble the actual full production native build/link graph, and
   only then validate gameplay/resources/runtime separately. A playable
   reconstruction is **not** currently available.

Keep periodic protected artifact retirement and bounded serial tool usage. A
portable product is a separate future scope; original game assets remain private.
