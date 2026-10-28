# CORE/EXACT-200: complete native Enemy queued metadata selectors

The genuine TH20 `EnemyState` writable COW selector at **`0x00498B80`**
(**396 bytes**) and ensure-only selector at **`0x00498D10`**
(**305 bytes**) are now **both fully byte-exact native functions** under the
locked MSVC 19.44.35211 x86 compiler. Their maintained production
source is `src/EnemyQueuedSelection.cpp`, using the existing actual
`EnemyState` layout, the real `std::pmr::forward_list<EnemyQueuedRecord>`,
`std::shared_ptr<EtamaArgInf>`, `DebugAllocator<EtamaArgInf>` and the
native eight-byte **pair of raw record and metadata pointers**.
The original source method spellings `writable_shot` and `shared_shot`
remain inferred; the native x86 member ABI, behavior, typed records and
full function bytes are independently established. **This is not a claim
that the complete 41,967-byte Enemy opcode dispatcher is byte-exact.**

## Native bodies and original relocation anchors

The target is the locked Japanese v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two original complete native functions were independently decoded with
Capstone, with no branch truncation:

| Function | Original entry | Original bytes | x86 instructions | Original relocations |
| --- | --- | ---: | ---: | ---: |
| Writable, copy-on-write | `0x00498B80` | **396/396** | 137 | **22/22** |
| Shared, ensure-only | `0x00498D10` | **305/305** | 105 | **16/16** |

All **38** native relocation target addresses were computed from the
**original PE instructions**, independently of any proposed COFF
mismatch fields. They comprise direct native `call rel32` destinations and
the actual `__security_cookie` process global. The full original native
call sites, instruction bytes, original SHA-256 and each target are in
`.analysis/core200-selector-native-independent-audit.json`. Original
callers that consume the returned aggregate further corroborate the actual
`std::pair<EnemyQueuedRecord*, ShotMetadata*>` interface; the value is **not**
a by-value `shared_ptr`.

The COW selector reads the actual indexed queue, extends its real PMR
forward-list when its unsigned count is smaller than `index + 1`, and finds
the selected `EnemyQueuedRecord`. A missing shared metadata owner is
allocated using its game-native `DebugAllocator`, while an owner with
reference count greater than one is **deep-copied**, including its PMR
command vector, before being replaced. A nonnull unique owner is reused.
The 305-byte ensure-only selector performs the same lookup and missing-owner
allocation, but **never clones** an already shared metadata owner. Both
return `{&record, record.owner.get()}` after those transitions.
Unsupported negative/overflowed script indexes or allocator exhaustion are
not silently repaired; those paths are not claimed as fully recovered runtime
behavior solely from semantic fixtures.

## Natural-source compiler reconstruction

An earlier private attempt was nearly exact for ensure-only, but moved its
compiler local `DebugAllocator` into a conditional temporary, changing
17 stack-frame operand bytes. Moving the naturally required allocator to
function scope—**without fake padding, volatile shaping, assembly or
special compiler flags**—produced all 241 comparable original bytes in
that 305-byte function. Applying the same genuine allocator lifetime and
native null/reference-count branch structure to COW then produced **all
308 comparable original bytes** of its 396-byte function. Both received
strict **whole-function** codegen credit only after all 16+22 original
relocations were independently checked and fully replayed.

The canonical physical MSVC object is
`build/core200-canonical/EnemyQueuedSelection.obj`, with its real pinned
compiler receipt; the two canonical unit names are
`enemy_state_shared_shot` and `enemy_state_writable_shot` in
`config/match-units.toml`. The canonical strict verifier reports exact
**305/305** and **396/396**, respectively, *including every original
relocation field*. No native target address, original instruction or
comparison span was altered to conceal a difference.

## Affected-only cold replays and historical proof preservation

The shared `src/EnemyState.hpp` declaration is a genuine production graph
change. Actual prior compiler receipts select precisely **19 existing
translation units / 110 existing strict native units**, plus the one new
source object containing both new methods. Only these **20 source objects**
were cold compiled; all **112/112 affected whole units** passed the
complete native relocation-aware replay using fresh source/object receipts.
The aggregate strict replay inspected **21,236** native comparison bytes.
Of the old units, **zero non-relocation machine-code bytes differed**.
Six compiler-private `$SG` debug-string symbol numbers moved when the real
header changed; each original literal's bytes, native target address,
relocation type and offset was independently checked against the original
PE. Only those six fresh source symbol names were updated, never a target
address or comparison extent.

Evidence is protected in `.analysis/core200-selectors-full-proof.json`,
`.analysis/core200-112-strict-attested.json`,
`.analysis/core200-all-112-relocation-audit.json`, and the 20 individual
`core200-replay-*.log` source traces. **No full graph cold replay occurred**.

During audit, a copied local verification script mistakenly wrote a new
112-unit JSON result to the **historical ignored CORE195** proof file path.
The new result was moved to the correct CORE200 path. We reconstructed the
former CORE195 compiler-input inventory and independently reverified its
**223/223** original strict native units. However, the old historical
JSON **byte identity cannot be recreated** from new COFF builds because
MSVC encodes a variable object timestamp: the original historical SHA-256
`397f52b3176dace8286016674e811360a6db07c97020aed771062bdbefe39c73`
was preserved explicitly while the re-attested JSON has a different digest.
The correction is disclosed—not misrepresented as the original bytes—in
`.analysis/core200-historical-proof-recovery.json` and as a
`CORE200_historical_proof_recovery` amendment to the private CORE195 audit.
All original PE machine-byte matching claims were independently rechecked;
this historical proof-identity difference is separate from exactness.

## Acceptance and remaining Boss work

This checkpoint adds **two complete authored functions, 701 native code
bytes**, bringing TH20 to **224 authored exact functions / 58,692 bytes**,
**1,019 source-present mappings, 1,010 canonical units and 168 canonical
objects**. The separate *single complete-root* Enemy source draft last
passed **42,743/42,743** GCC UBSan and ASan+UBSan scenarios in CORE199,
but that older host still contains its prior *private* queued-owner COW
candidate. The next high-value task is to link these two newly accepted
production selectors into the **same** whole-root host while preserving
old injected-failure tests, then continue missing large Enemy branches.
The original Enemy dispatcher, Stage and renderer/VM lifetime, other
concrete Laser derived owners and switch/EH codegen remain nonexact.
