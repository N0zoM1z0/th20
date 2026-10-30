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
2. Resolve both **source-present large Animation bosses**: the **5,993B
   49-mode draw dispatcher** has all 123 original E8 roles but a different
   compiled switch layout, and the **3,159B quad submission** has all 41 E8
   and 96 original HIGHLOW source-target roles but a longer x86 body.
   Their **2,725B texture/sampler** and **1,163B blend state** children are
   independently whole strict exact. [Draw source gap](ANIMATION_DRAW_BOSS_5993_TYPED_49_MODE_PARENT_FRONTIER.md),
   [quad current gap](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md).
3. Continue the **3,111B Player main** register/stack-lifetime gap,
   **555B Player movement** SSE spill and **273B Bullet draw group**
   SSE-temporary gap using only natural C++ source experiments. The
   **3,735B Bullet emitter, 1,404B Bullet command 11 and original
   73B Animation factory are already whole-native strict exact**;
   do not repeat their old unclosed-compiler hypotheses as live work.
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
