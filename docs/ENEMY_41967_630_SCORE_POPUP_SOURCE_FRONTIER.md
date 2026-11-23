# Enemy ECL opcode 630 — score award and item-reward popup

## Native branch

Opcode **630** is the original **109-byte / 24-instruction / 5-E8** inline
case at `0x0048C24A..0x0048C2B7`, selector index **148**. The native call
sequence is pinned by `scripts/verify-enemy-score-popup-opcode-source.py`:

1. integer operand 0;
2. `Session::add_score`;
3. the Context +0x1C `ItemRewardPopupQueue` accessor;
4. live `EnemyState::position_ref`;
5. the original **255-byte** `ItemRewardPopupQueue::enqueue` Boss.

The native branch also pushes `-1` as the popup type/identifier argument.
Its selector pointer, exact byte extent/hash, all five E8 site/target pairs
and the negative marker are checked against the locked PE.

## Natural C++ and owner semantics

`execute_enemy_score_popup_opcode` reads integer operand 0, awards the amount
through the real `Session::add_score`, resolves the queue from the live
Context's `object_1c` field, takes the current EnemyState position and calls
the real `ItemRewardPopupQueue::enqueue(&position, -1, uint32_t(amount))`.
The Session/PlayerRecord score update is kept in `src/SessionScore.cpp`,
separate from the other query methods in `DamageQueryProtocol.cpp`.
The queue accessor is a typed Context member; the queue itself remains the
existing PMR-backed `ItemRewardPopupQueue`, not a copied test popup or string.

The root host executes opcode 630 through the actual Enemy dispatcher. It
checks score growth, popup digits/color/position and queue publication,
Context retargeting between the operand read and queue selection, and an
integer-operand exception before score or popup side effects. The original
255-byte enqueue Boss is separately strict-exact and is reused without
claiming duplicate bytes.

The maintained root verifier currently runs **129 focused host source units**
under ASan/UBSan and compiles **62 locked-profile i386 COFF units**. The
41,967-byte `EnemyState::execute_opcode` parent remains **NONEXACT**; opcode
630 is an inline fragment and receives no whole-parent byte credit. No full
cold replay was run.
