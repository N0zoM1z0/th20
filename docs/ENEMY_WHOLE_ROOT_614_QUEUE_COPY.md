# CORE207: complete original Enemy opcode 614 record-copy branch in the whole root

This checkpoint continues the **same full 41,967-byte**
`EnemyState::execute_opcode` source-draft at `0x0048C010`, against the
locked Japanese TH20 v1.00a Steamless target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
It does **not** claim that original native Enemy root is machine-code exact.
The independently decoded complete original opcode **614** primary branch
covers `0x004925C7..0x00492802`, **572 bytes / 129 x86 instructions /
19 direct native calls**. A separate native case-path catalog agrees on
all 129 original instruction addresses, original call destinations and the
final `jmp 0x004963DF` back into the full dispatcher. Original complete 572-byte SHA-256 is
`86502facaafd3ae67358babf1d91fb44682ce14248911264714d48ccf29ebfa9`. Original instruction
and address/hash audit is protected at
`.analysis/core205-native-op614.asm` and
`.analysis/core207-native-op614-audit.json`.

## Actual native semantics — copy, not swap

The original branch reads ECL **integer_argument(0)** (destination index),
then **integer_argument(1)** (source index), *both before any queue mutation*.
It takes native `std::pmr::forward_list<EnemyQueuedRecord>::end()` and
`begin()` iterators, computes the current distance with native
`std::distance`, and grows the list to `destination+1` if necessary.
**Only then** does it repeat the distance/resize for `source+1`, preserving
that order and the original unsigned bound comparisons. It constructs two
independent iterators, advances them respectively by destination and source,
and finally invokes the real **119-byte `EnemyQueuedRecord::operator=`**
at `0x0048BC00` (original direct call `0x004927F8`). This is literally
`queued[destination] = queued[source]`; it is **not** a swap of records, a
raw struct `memcpy`, a write into only `ShotParameters`, or a COW clone.

The member-copy callee is an independently accepted complete native-exact
production function from [CORE/EXACT-206](ENEMY_QUEUED_RECORD_ASSIGNMENT_EXACT_RECONSTRUCTION.md):
**119/119 original x86 bytes** and its original native `shared_ptr`
assignment relocation at `0x0048BA20` match under locked MSVC 19.44 x86,
with **113/113 actual header-affected native units** already strictly
replayed. The assignment copies the genuine 76-byte record's ownership
`shared_ptr<EtamaArgInf>` at offset zero, its 40-byte shot parameters,
`field_30`, and both position vectors. Thus a successful record copy
**shares** metadata ownership with the source; the destination's former
owner may be released, and the source record remains intact. A same-index
copy keeps its own value and owner. Neither native case 614 nor the 119-byte
callee has evidence for a blanket zeroing or temporary clone.

## Same complete-root integration and tests

The active private candidate is
`.analysis/core207-enemy-dispatch-candidate.cpp`. The one complete original
Enemy draft now includes case 614 while retaining all previous 539/555,
600–604, 609–612, 700–703, 711/713 and earlier opcode families. Its
**86-TU** GCC host links the unmodified production
`src/EnemyQueuedRecordAssignment.cpp` for real shared pointer copy/release,
not a test-only reimplementation. Current fixture
`.analysis/core207-op614-queue-copy-host-cases.inc` adds **308** cases:

- **288** real typed record assignments across different valid queue
  lengths, indexes, initial shared-owner configurations and raw parameter
  values, including **56** self-copy cases, **48** first-index queue growths,
  **20** second-index growths, **32** preserved externally shared aliases,
  and **64** releases of overwritten destination owners.
- **12** ECL operand failures at argument 0 or 1, proving no premature
  allocation or assignment and complete record/state preservation.
- **8** genuine cross-opcode **614 → 602 → 700** chains: copying first
  makes two records share the same metadata, 602 changes the target's raw
  type/color without cloning, and 700 then uses the independently exact
  396-byte COW selector to deep-copy *only* target metadata. The source's
  metadata and PMR command storage remain unchanged.

Both complete-host profiles pass **44,230/44,230** scenarios: the prior
43,922 retained tests plus 308 new. Profiles are GCC 13 `-O2 -Wall
-Wextra -Werror` with UBSan and separately with ASan+UBSan. In the second,
only unrelated `WeaponStoneInfo` fixture `vptr` instrumentation is
disabled, with ASan leak detection enabled. Full logs are
`.analysis/core207-dispatch-host.log` and
`.analysis/core207-dispatch-host-asan.log`. SHA-bound source/recipe inputs,
both binaries, and both successful logs are preserved at
`.analysis/core207-enemy-whole-root-proof.json`. All earlier CORE206/205
and historical original/native proofs remain intact.

## Exactness limits and next work

The full Enemy source draft now semantically covers **140 effective opcode
values / 108 original primary heads** out of 174. The original native
41,967-byte Enemy boss is **still machine-code nonexact**; in particular
its compiler EH, missing primary heads and entire switch partition remain
unaccepted. CORE207 made **no maintained native compiler source/header
changes**, so its affected native cold-build/replay scope is **zero**; no
full cold replay was run. Previously accepted authored/game-owned native
exact totals remain **226 functions / 58,837 bytes / 1,012 canonical units**.
A substantial further dependency is the 339-byte native Bullet firing
routine at `0x00481780` used by opcode 601; the original full queue
allocator/clear paths and missing opcode heads also merit independent
reconstruction. Do not infer native exactness from a GCC semantic host alone.
