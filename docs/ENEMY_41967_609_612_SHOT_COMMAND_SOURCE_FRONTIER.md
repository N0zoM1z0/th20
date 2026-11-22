# CORE/RECON-1145 — natural-C++ source for the shared Enemy ECL opcodes 609–612

The maintained source now contains `execute_enemy_shot_command_opcode(EnemyState&, opcode)` in `src/EnemyStateShotCommandOpcode.cpp` for the four original opcodes 609, 610, 611 and 612. All four map to the same original primary case head `0x004931DD`; this is one inline case family inside the **41,967-byte** `EnemyState::execute_opcode()` Boss, not four separate functions or a complete parent definition.

## Immutable original case evidence

The locked Japanese TH20 1.00a Steamless PE has a single shared 609–612 case body of **1,457 bytes / 314 x86 instructions**, ending at the common native tail before `0x0049378E`. The branch SHA-256 is `f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b`. It contains **29 direct E8 calls**:

| Original target | Calls | Native role |
| --- | ---: | --- |
| `0x004AB080` | 8 | `EnemyState::integer_argument` |
| `0x004Aafb0` | 4 | `EnemyState::float_argument` |
| `0x00498B80` | 1 | Writable queued metadata pair selector |
| `0x0040B280` | 2 | Pair element address helpers |
| `0x0048B180` / `0x0048B160` | 1 each | First/second raw pointer pair elements |
| `0x00486600` | 1 | PMR command vector size |
| `0x004862F0` | 1 | PMR command vector resize |
| `0x0047C6C0` | 10 | `std::pmr::vector<BulletCommand>::operator[]` |

The independent CORE187 audit records all 29 original site/target pairs and the whole 1,457B instruction stream in `.analysis/core187-native-609-612-audit.json`. The independent CORE188/EXACT-200 ABI work subsequently established that `0x00498B80` returns an eight-byte pair of raw `EnemyQueuedRecord*` and `ShotMetadata*`, and the 396B writable selector is now accepted native-exact. This source calls that real `EnemyState::writable_shot()` implementation directly.

## Four opcode modes and exact mutation order

| Opcode | Command index | Integer fields | Float fields |
| ---: | --- | ---: | ---: |
| 609 | `integer_argument(1)` | 4 | 2 |
| 610 | `integer_argument(1)` | 6 | 4 |
| 611 | Current `ShotMetadata::field_30` cursor | 4 | 2 |
| 612 | Current `ShotMetadata::field_30` cursor | 6 | 4 |

The handler first evaluates integer operand 0 and selects the writable queued metadata pair. It then chooses the explicit command index or the current metadata cursor, checks the actual PMR vector size against unsigned `index + 1`, and resizes only when required. It writes the command in the original order: flags `+0x24`, opcode `+0x20`, integer payloads `+0x10/+0x14` and optionally `+0x18/+0x1C`, then float payloads `+0/+4` and optionally `+8/+0xC`.

The source deliberately does **not** cache a `BulletCommand&`. It spells out ten possible `metadata.commands[command_index]` stores individually, so each VM argument is evaluated before its corresponding element access/store. This retains the native per-field partial-write behavior: if a later VM argument throws, earlier field writes and any successful vector resize remain visible. The metadata cursor is committed last: explicit-index mode stores `index+1`; cursor mode increments the prior cursor by one. The original unsigned arithmetic and unbounded script index behavior are not replaced with invented validation.

## Scoped verification and exactness boundary

`src/EnemyStateShotCommandOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. The focused verifier `scripts/verify-enemy-shot-command-opcode-source.py` checks the immutable audit's branch hash, 1,457B/314-instruction/29-E8 counts, original call-target multiset, all four source cases, ten individual command-field accesses, and final cursor commit. The compiler currently inlines the vector element accessor in this source object; the source preserves the original per-field C++ access order, but this does **not** claim exact 33B accessor call emission or exact parent codegen.

This helper receives no `config/functions.csv` native-function mapping because the original 609–612 bodies are one inline region inside `EnemyState::execute_opcode()`. The 41,967B parent now has a partial C++ root entry (CORE/RECON-1196), but remains incomplete/NONEXACT, with no canonical whole-parent unit and zero parent byte credit. No full cold replay was performed.

Next work: continue closing the other large Enemy ECL opcode families and integrate the source fragments into the full natural-C++ dispatcher only after preserving the original compact opcode table, common epilogue, exception behavior and all parent ABI boundaries.

## Maintained root-host execution closure — CORE/RECON-1246

The maintained tests/enemy_state_dispatch_root.cpp previously supplied a
false-returning execute_enemy_shot_command_opcode stub. Although production
EnemyState::execute_opcode() already routed the four cases to the helper,
the maintained ASan/UBSan root host therefore never executed those production
branches. CORE/RECON-1246 removes that stub and links the actual helper together
with the real EnemyState::writable_shot() and EtamaArgInf implementations.

The root host now executes all four variants through the production dispatcher:

- 609: explicit command index, base six-field payload and real vector growth
- 610: explicit command index, extended ten-field payload and shared-owner COW
- 611: metadata cursor, base payload and real vector growth
- 612: metadata cursor, extended payload without unnecessary growth

The tests check the real forward-list selector, unique/shared owner behavior,
44-byte BulletCommand fields, untouched neighboring commands, PMR vector
resize, exact integer-before-float operand read sequence, explicit-index versus
cursor commit, and both base and extended layouts. A second-float exception in
610 verifies that the resize and prior field writes survive while the final
cursor write does not occur.

The focused root verifier now re-decodes the original locked PE branch on every
run: all four opcodes share selector index **130** and head 0x004931DD;
the branch is **1,457 bytes / 314 instructions / 29 ordered E8 calls**, with
the independently audited SHA-256 and exact call targets. It invokes the
dedicated immutable source audit and checks the compiled natural-C++ helper's
**26 ordered DISP32 relocations** (25 semantic calls plus the security-cookie
epilogue), including all ten separately emitted PMR vector element accesses.

Affected-only dependency replays passed EnemyQueuedSelection.cpp **2/2**
(writable_shot **396/396**) and ShotMetadata.cpp **3/3** (constructor,
destructor and move assignment). The root verifier compiles **30** locked
i386 COFF source units and its ASan/UBSan host now links the real shot-command
helper, COW selector and metadata constructor. The four branches remain inline
regions of the **41,967-byte** dispatcher: no standalone native function,
whole-parent exactness or parent byte credit is claimed. No full cold replay
was run; no assembly or padding is used.
