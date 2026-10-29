# CORE/RECON-710 — original 12,140-byte Bullet command sequencer: complete 34-way switch and independent game-owner ABI

**The full 12,140-byte original Bullet::run_extended_commands() game Boss is NOT YET source-present or byte-exact.** This native-source frontier establishes its exact game-class ownership, original 2,490-instruction body, 34-element relocated switch table, 210 original physical E8 and independently strict 3,735B/1,846B callers. It does not invent a partial C++ implementation or claim any of the original 12,140 code bytes as new exact credit.

Original original target: Japanese TH20 v1.00a Steamless PE, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Entire immutable native function, guards and correct C++ owner

The actual original body is **0x0047DCF0..0x00480C5B inclusive**, i.e. **12,140 original bytes**. Fully decoding its immutable PE image yields exactly **2,490 original x86 instruction heads** and an authentic RET at 0x00480C5B; the next byte after that RET is not body code. Inside the whole function the original contains **210 direct E8 call sites** and **38 physical original PE HIGHLOW relocation fields** (read from the actual original .reloc directory).

At entry, the genuine ECX thiscall receiver reads Bullet+0x38 and checks it against 0x18 (maximum 24 commands in this processing loop), reads the actual Bullet+0x98 shared_ptr metadata command vector and compares the index with its real vector size. It retrieves a command object, reads its actual opcode at command+0x20, and uses Bullet+0x90/+0x94 to update the real 64-bit command flag mask. These are actual native field offsets, not invented names or a guessed BulletController layout. The original dispatcher checks opcode against 0x21 and then executes a native indirect jmp through the table at 0x00480C5C.

**Independent original game ownership is confirmed by TWO entirely native-exact large callers and their rebuilt COFF symbols:**

- Complete original **3,735B BulletController::emit** at 0x004818E0 E8-calls this 12,140B original head at **0x004826B5 → 0x0047DCF0**. The complete actual canonical emitter object uses relocation field +0xDD6 with the legitimate MSVC class method symbol **?run_extended_commands@Bullet@th20@@QAEXXZ**. The separately accepted 3,832-byte compiler/NOP/switch-table contribution is still **3,832/3,832 exact**.
- Complete original **1,846B Bullet::update_physics** at 0x00485B60 also E8-calls it at **0x00485D7B → 0x0047DCF0**. Its actual pinned canonical C++ object uses the *same* legitimate Bullet member symbol at original immediate field +0x21C, with **1,846/1,846 original bytes and 1,864/1,864 complete compiler contribution strict exact**.

Thus the original parent is a **Bullet instance command sequencer**, not a BulletController dispatch root or an STL/library helper. The real shared Bullet.hpp already declares the exact void Bullet::run_extended_commands() method; however there is **NO maintained complete C++ definition**. The original 12,140B function must remain unclassified/unmapped for reconstruction strict acceptance even though its original project/game authorship and C++ entry role are now high-confidence.

## Actual original post-body switch table

The immutable original bounds check uses opcode indices **0..33 inclusive**, followed by a real jmp through the table **0x00480C5C..0x00480CE3**, exactly **34 little-endian original absolute code pointers, 136 bytes**.

Every one of these **34 original table fields is independently present as IMAGE_REL_BASED_HIGHLOW in the actual original PE relocation directory**. All 34 point to real x86 instruction boundaries inside the 12,140B body, with **32 distinct physical case entries**. Original command IDs **5, 14 and 28** point to the **same no-op/advance tail at 0x00480C25**. These are three entries for one code location, not three complete separately credited functions.

The following original case table is generated verbatim from independent original PE data words rather than from a source guess:

<!-- BEGIN ORIGINAL PE TABLE -->
| Command ID | Native PE table field | Original branch instruction head |\n| ---: | --- | --- |\n| 0 | 0x480c5c | 0x47dee2 |\n| 1 | 0x480c60 | 0x47de54 |\n| 2 | 0x480c64 | 0x47df50 |\n| 3 | 0x480c68 | 0x47e69c |\n| 4 | 0x480c6c | 0x47e7c4 |\n| 5 | 0x480c70 | 0x480c25 **shared no-op** |\n| 6 | 0x480c74 | 0x47ed51 |\n| 7 | 0x480c78 | 0x480036 |\n| 8 | 0x480c7c | 0x47f0ea |\n| 9 | 0x480c80 | 0x47f194 |\n| 10 | 0x480c84 | 0x47f691 |\n| 11 | 0x480c88 | 0x47f6bd |\n| 12 | 0x480c8c | 0x47ef27 |\n| 13 | 0x480c90 | 0x47f6fc |\n| 14 | 0x480c94 | 0x480c25 **shared no-op** |\n| 15 | 0x480c98 | 0x47ff6c |\n| 16 | 0x480c9c | 0x47ff98 |\n| 17 | 0x480ca0 | 0x480188 |\n| 18 | 0x480ca4 | 0x480477 |\n| 19 | 0x480ca8 | 0x4805e2 |\n| 20 | 0x480cac | 0x48077e |\n| 21 | 0x480cb0 | 0x47e427 |\n| 22 | 0x480cb4 | 0x4807e1 |\n| 23 | 0x480cb8 | 0x48093c |\n| 24 | 0x480cbc | 0x480a37 |\n| 25 | 0x480cc0 | 0x480b51 |\n| 26 | 0x480cc4 | 0x47f063 |\n| 27 | 0x480cc8 | 0x47f99f |\n| 28 | 0x480ccc | 0x480c25 **shared no-op** |\n| 29 | 0x480cd0 | 0x480b7d |\n| 30 | 0x480cd4 | 0x47efdb |\n| 31 | 0x480cd8 | 0x48004d |\n| 32 | 0x480cdc | 0x47e1a9 |\n| 33 | 0x480ce0 | 0x480bfa |\n
<!-- END ORIGINAL PE TABLE -->

## Exactly what the 210 original calls and native flags establish

The complete original body has **210 genuine E8 fields**, of which **188 physical call occurrences target an already configured canonical original whole-function provider**, and **127 target original heads already independently accepted as game-authored exact**. These are counts of actual E8 sites, not counts of unique helpers or exact bytes of this parent. The most frequently used real original physical helper is BulletExtendedCommands::at at 0x0047C680 (**81 separate E8 occurrences**), corresponding to original per-command slot access. Other physically established targets include Timer integer assignment (12 calls), the real ClockScalar float conversion (10), identifier_get (9), Bullet aim-selector (6), game polar geometry (5), queued sound (4), Bullet::cancel (4), original Player::direction_to (4), genuine x87 normal angle conversion and typed Animation script loaders. Cases include authentic game state, movement, sound, laser or Enemy creation and effect policy. No whole-parent exactness follows from any of those exact children.

A native per-case entry offset and the initial actual instructions at that address are retained privately for every one of the 34 entries. The disjoint original code regions between distinct jump-table targets are **physical binary spans, not automatically equivalent to semantic independent switch-case implementations**; some cases jump to shared tails or previously declared case labels. A future full source must preserve those transitions and the real exception/SEH cleanup, not concatenate decompiled snippets or count the shared tail multiple times.

## Work remaining before exact acceptance

The original C++ type receiver and exact symbol spelling are supported by the two original independently strict parent link sites. But **the game project does not yet have the entire 34-case C++ definition** under src. The current function-origins review may be marked independently game-authored high-confidence without changing the provisional reconstruction status or mapping this function as implemented. The original function inventory still has source_file EMPTY, status UNCLASSIFIED and 0.00 source match; there is no matching canonical 12,140B strict unit or accepted 12,140 original body.

Future reconstruction must implement the full original command engine naturally, reconcile all 210 original E8 source roles, **38 body HIGHLOW fields and 34 post-body table HIGHLOW fields**, preserve original return and EH/SEH mechanics and compare the entire original native function and its 136-byte support table. Support data after the original RET is not separately authored gameplay credit.

## Scoped reproducibility

- .analysis/core709-bullet-12140-original-switch-callgraph.py/json: original full 12,140B/2,490 x86 disassembly, 34 true PE pointer words, independent original .reloc HIGHLOW evidence, all 210 original E8 destinations and 34 command entry instruction samples.
- .analysis/core710-bullet-dispatcher-12140-game-owner-proof.py/json: independent original E8 call sites and exact MSVC COFF symbol/field positions for original strict 3,735B emitter and 1,846B physics parents, plus actual original Bullet member offsets and original source/prototype declaration audit.
- Unchanged canonical bullet_emitter_whole_3735: 3,735/3,735 original strict and 3,832/3,832 whole compiler contribution.
- Unchanged canonical bullet_update_physics: 1,846/1,846 original strict and 1,864/1,864 whole compiler contribution.

This checkpoint changes only original game-owner/working-definition metadata, source-navigation/evidence notes and this original-native proof document. There is **zero affected canonical source unit**, zero new exact original bytes, no global cold replay, and no claim of linked/playable game. The original full 12,140B Bullet parent remains NONEXACT, while the preexisting game-authored total stays **520 complete original functions / 182,446 disjoint native bytes**.
