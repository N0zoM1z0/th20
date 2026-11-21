# CORE/RECON-1149 — natural-C++ source for Enemy ECL opcode 614 queue copy

The maintained source now contains `execute_enemy_queue_copy_opcode(EnemyState&, opcode)` in `src/EnemyStateQueueCopyOpcode.cpp` for original opcode 614. This is one inline case region in the **41,967-byte** `EnemyState::execute_opcode()` Boss, not a standalone original native function.

## Original native case evidence

The locked TH20 1.00a Steamless PE audit `.analysis/core207-native-op614-audit.json` confirms the exact case interval `0x004925C7..0x00492803`: **572 bytes / 129 x86 instructions / 19 direct E8 calls**, SHA-256 `86502facaafd3ae67358babf1d91fb44682ce14248911264714d48ccf29ebfa9`.

The 19 original call destinations form this multiset: two integer-argument reads; two end/begin iterator pairs; two `std::distance` calls; two PMR forward-list resizes; two iterator default constructions; two `std::advance` calls; two iterator destructors; and one `EnemyQueuedRecord::operator=` call at `0x0048BC00`.

## Restored algorithm and state semantics

1. Read destination index with `integer_argument(0)` and source index with `integer_argument(1)` **before any list mutation**.
2. Query end then begin, compute the original unsigned size comparison, and resize to `destination+1` only if necessary.
3. Repeat the end/begin/distance/resize sequence for `source+1`, preserving destination-before-source growth order.
4. Construct independent destination and source iterators, advance them by their respective indices, then execute `*destination = *source`.

This is a full record copy, not a swap, raw `memcpy`, ShotParameters-only copy, or metadata COW clone. The destination's previous shared owner may be released, and the destination receives a copy of the source's real `shared_ptr<EtamaArgInf>`; the source record and its metadata remain unchanged. Same-index copy uses the real copy-assignment self-assignment behavior.

The final call is the already accepted whole-exact **119B `EnemyQueuedRecord::operator=`** (CORE/EXACT-206). It copies the complete 76B record: shared_ptr owner, 40B ShotParameters, `field_30`, and both 12B position vectors. The helper's 119B body is reused as a real typed method, not reimplemented.

## Scoped verification and exactness boundary

`src/EnemyStateQueueCopyOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-queue-copy-opcode-source.py` checks the immutable original branch hash, 572B/129-instruction/19-E8 counts, original target multiset, both operand reads before mutation, destination-before-source growth, two independent advances and final typed copy assignment.

This is a source fragment, not a standalone original function. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.
