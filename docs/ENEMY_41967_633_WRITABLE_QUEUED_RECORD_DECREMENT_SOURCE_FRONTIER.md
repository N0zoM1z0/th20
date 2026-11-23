# Enemy ECL opcode 633 — writable queued-record decrement

## Status and boundary

Opcode 633 is represented by natural C++ in src/EnemyStateQueuedParametersOpcode.cpp,
linked through the maintained EnemyState::execute_opcode root host, and covered
by native PE, locked-profile i386 COFF and ASan/UBSan checks. It is an inline
case fragment in the original 41,967-byte EnemyState::execute_opcode body at
0x0048C010, not a standalone native function or independently replayable unit.
The parent remains **NONEXACT** and receives no whole-parent byte credit.

Checkpoint: 8714ad591dcbec8d8e698e72cef9e317e140737e
(gpt-web: restore Enemy opcode 633 queued counter decrement).

## Locked native case

Target: resources/th20.exe, Japanese TH20 1.00a Steamless image,
SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

| Property | Native value |
| --- | --- |
| Selector index | 151 |
| Start | 0x0049378E |
| End (exclusive) | 0x00493831 |
| Extent | 163 bytes |
| Decoded instructions | 41 |
| Direct E8 calls | 6 |
| Case SHA-256 | 90eb5f86bcdf5af4629fcfbdf5f647f5befec2e77ba0794f048b91fd4b4ac536 |

The ordered native call targets are:

1. 0x004AB080 — EnemyState::integer_argument(0)
2. 0x00498B80 — EnemyState::writable_shot
3. 0x0040B280 — pair move
4. 0x0048B180 — std::get<0>
5. 0x0040B280 — pair move
6. 0x0048B160 — std::get<1>

## Recovered behavior and integer semantics

The native branch reads selector operand 0, calls writable_shot, extracts
both pair members in order, and then decrements the selected
EnemyQueuedRecord::field_30. The second pair member is intentionally
extracted even though this branch only mutates the record word; that call is
part of the original observable call sequence.

On the 32-bit target, field_30 is at record offset 0x30. The operation is
not a signed C++ decrement: x86 performs a wrapping 32-bit subtraction, stores
the result, tests the sign bit, and stores zero if the result is negative.
The source expresses that without signed-overflow undefined behavior:

~~~cpp
record->field_30 -= 1u;
if ((record->field_30 & 0x80000000u) != 0) {
    record->field_30 = 0;
}
~~~

The source has an x86-only offsetof(EnemyQueuedRecord, field_30) == 0x30
assertion. It is guarded for _M_IX86/__i386__: the 64-bit host's wider
shared_ptr changes the host struct offset, while the locked i386 COFF build
checks the actual target layout.

The COW call is also retained even though this case does not write through the
metadata pointer. If the owner is shared, writable_shot clones it before
the counter update. That clone is a visible side effect and is tested.

## Production integration and verification

The production queued-parameter helper handles 633 beside 619 and 700/701.
The root test uses the real queue selector and shared-owner COW path. It checks
2 -> 1, 0 -> 0, 0x80000000 -> 0x7fffffff, and 0x80000001 -> 0, plus selector-read
exception behavior: if operand 0 throws, neither COW nor the counter write
occurs.

The maintained verifier checks selector index 151, the original 163-byte
case hash, all 41 instruction boundaries, six ordered native call targets,
the COFF pair-extraction sequence and the high-bit clamp. The focused
ASan/UBSan root host passes.

This is source recovery for one inline case only. It does not establish an
independent function unit, strict exact-byte receipt, or whole-parent
completion. The 41,967-byte dispatcher remains **NONEXACT**; no full cold
replay was run.
