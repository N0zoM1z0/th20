# CORE/EXACT-206 — complete EnemyQueuedRecord native copy assignment

The locked TH20 Japanese v1.00a Steamless target (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains a **119-byte** copy assignment member at `0x0048BC00` for the
actual **76-byte** `EnemyQueuedRecord`. Natural maintained source in
`src/EnemyQueuedRecordAssignment.cpp` defines
`EnemyQueuedRecord::operator=(const EnemyQueuedRecord&) = default` on the
existing genuine type. The original C++ spelling and whether `=default`
was explicitly written or implicitly generated remain unknown; it is a
game-owned member rather than a generic imported STL/CRT function.

The complete original 119-byte body has **46 x86 instructions** and one
original native REL32 relocation, offset **`+0x11`** to the actual
`std::shared_ptr<EtamaArgInf>` copy-assignment helper at `0x0048BA20`.
The original instructions then copy the complete `ShotParameters` at
record `+0x8`, the field at `+0x30`, and both `Vector3` fields at `+0x34`
and `+0x40`, rather than treating this record as a flat `memcpy` and
losing the correct shared-owner assignment. The native code SHA-256 is
`b4bef593018a6c20cb566137218b9be394bb33f8f59addbfe000a2619d551669`.
The original opcode 614 large queue branch at `0x004925C7..0x00492802`
uses the complete member at its `0x004927F8` call; **614 itself is not
accepted as machine-code exact** by this method's separate acceptance.

The fixed MSVC 19.44.35211 x86 source profile emits **119/119 original
bytes**, including the independently decoded original relocation; canonical
unit `enemy_queued_record_copy_assignment` and the complete real native
COFF object/receipt are at `build/core206-canonical/EnemyQueuedRecordAssignment.obj`
and its sibling `.receipt.json`.

The declaration change in the real `src/EnemyState.hpp` affects exactly
**20 existing canonical source providers / 112 prior native exact units**;
adding the new member makes **21 provider cold compiles and 113 whole
strict units**. All **113/113 complete units** passed original native
code/relocation-aware strict replay, covering **21,355 comparison bytes**.
Six compiler-private `$SG` string labels changed due to the header update.
Every renamed label was separately checked against the unchanged original
PE `.rdata` literal at its original relocation address and the original
offset/type. Only current COFF internal symbol identities were updated,
not native targets, function ranges or code. See private hashes and evidence
in `.analysis/core206-whole-record-exact-proof.json`,
`.analysis/core206-string-symbol-drift.json` and
`.analysis/core206-113-strict-attested.json`.

This checkpoint adds **one fully native-exact game-owned function / 119
code bytes**. Confirmed authored/game-owned coverage is now **226 full
functions / 58,837 code bytes**, **1,021 source-present mappings** and
**1,012 canonical units / 169 physical comparison objects**. There was
**no full native cold replay**. The current *single complete* 41,967-byte
Enemy opcode root (last CORE205 host: **43,922/43,922** semantic scenarios)
remains native **nonexact**. Next integrate the **whole 572-byte opcode
614** using this real copy assignment and the actual PMR queue vector,
including index extension, operand order, real shared ownership and
exception-sensitive mutation, rather than shortcutting to a fake root.
