# CORE192: real Laser parameter owners inside the entire Enemy boss root

This work extends the *same* natural-source candidate for the native
**41,967-byte** `EnemyState::execute_opcode()` at `0x0048C010`. It integrates
two previously uncovered, individually large original primary opcode heads:
702 and 703. The entire function, original jump partitions, EH and native
compiler codegen are **still not byte-exact**. No part of either case has
been promoted to an independent fake function or counted as authored exact
code. The original target is Japanese Steamless v1.00a, locked SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Complete native branch investigation

The original PE's dispatch table and an independent case-path catalog
locate the following *complete local primary* case intervals. Capstone
instruction heads, direct-call targets, final tail jump and original bytes
agree independently across the whole interval; there are no truncated
instruction prefixes:

| Opcode | Original interval (exclusive end) | Native bytes | x86 instructions | Calls |
| --- | --- | ---: | ---: | ---: |
| 702 | `0x004944C7..0x00494771` | 682 | 153 | 15 |
| 703 | `0x00494771..0x00494A84` | 787 | 176 | 16 |

Both cases invoke the genuine, already recognized
`LaserType0Parameters` or `LaserType1Parameters` constructor, then read
`integer_argument(0)`, perform the writable **396-byte queued metadata
selection at `0x00498B80`**, retrieve its two-pointer record/metadata
aggregate, and copy the real `std::pmr::vector<BulletCommand>` into the
concrete laser parameter's own vector via original copy helper `0x0047C570`.
The original record is a 76-byte `EnemyQueuedRecord`, not just a `ShotMetadata`
value. Its `vector_40.z` at record offset `0x48` is compared against the
native float at `0x0056FC00`, whose independently read original bits are
`0x3F666666` (**0.9f**). The gate uses `comiss` followed by `jbe`, making
unordered/NaN use the non-relative path as well. For **strictly greater**
values, the copied `vector_40 + vector_34` is used and output Z is forced
to zero. Otherwise the caller computes `EnemyState::position_ref() +
record.vector_34`, retaining the computed Z. Both vector additions call the
real `Vector3::operator+` owner at `0x00429570`.

Each branch then populates its *different actual parameter layout* from the
record's `ShotParameters` fields and from the selected `EtamaArgInf` metadata.
Both normalize the original shot angle with `normalize_angle` at `0x00438540`,
copy type/color, speed/length/width-related scalar lanes, preserve original
metadata flags and force a different low flag bit (702 OR `1`; 703 OR `2`).
702 writes type-0 sound/alternate-sound fields and the borrowed current
view index. The larger 703 additionally copies four duration words, a
handle word from a *late* `integer_argument(1)` read, and the same view index
from the possibly retargeted state. Therefore 702 has only VM operand 0;
703 has VM operands 0 then 1, with operand 1 **after** command cloning and
most parameter writes. The native owner selection then invokes the real
`Context::laser_controller` getter at `0x0041CA90` and calls the 474-byte
`LaserController` create/factory routine at `0x004D47F0` with selector 0
or 1, respectively. The actual `LaserType0/1Parameters` destructors are
called on normal exit and unwind.

The raw complete instructions, SHA-256 and the native call-site audit are
protected at `.analysis/core192-native-op702.asm`,
`.analysis/core192-native-op703.asm` and
`.analysis/core192-native-702-703-audit.json`. No original target bytes,
Ghidra database bytes or compiler artifacts were patched to generate them.

## Whole-root semantic integration

The active source remains *one* complete-root private draft:
`.analysis/core192-enemy-dispatch-candidate.cpp`. The host uses genuine
`LaserType0Parameters` / `LaserType1Parameters` constructors/destructors,
real PMR command-vector copying, actual `EnemyState` queued forward-list,
the CORE188 tested COW selector candidate with correctly returned record and
metadata pointers, real vector/angle methods, and the genuine Context Laser
owner getter. The **474-byte** original Laser factory remains a clearly
captured private boundary and is **not** labeled byte-exact or implemented as
a fake production creator. The general `LaserController` lifecycle and
concrete beam resource allocation remain independently open.

The new test fixture `.analysis/core192-enemy-laser-spawn-host-cases.inc`
adds **303** cases, including:

- 144 type-0 and 144 type-1 successful factory-boundary calls, with every
  actual parameter field compared to independent source-record expectations.
- 108 threshold-triggered relative-position/Z-zero and 180 normal/NaN
  absolute-position cases, including values immediately either side of 0.9.
- 96 shared-owner copy-on-write cases, 96 first-time metadata creations,
  and **288 real PMR command vector deep copies** checked element by element.
- 48 retargeted late Context/view-index cases after opcode 703's
  `integer_argument(1)` hook; 15 staged exceptions at VM reads or the
  captured downstream Laser factory, verifying read order, retained owner
  state and absence of double destruction.

Both full 82-translation-unit host configurations pass **40,941/40,941**
scenarios (all 40,638 earlier cases plus 303 new ones): GCC13 `-O2
-Wall -Wextra -Werror` with UBSan; and GCC13 `-O2 -Wall -Wextra -Werror`
with ASan+UBSan. **Only vptr instrumentation** was disabled in the latter
because unrelated `WeaponStoneInfo` key-function RTTI is not linked into the
fixture. ASan leak detection was enabled. Detailed stdout/receipt and
SHA-bound inputs/binaries are in `.analysis/core192-dispatch-host.log`,
`.analysis/core192-dispatch-host-asan.log`,
`.analysis/core192-dispatch-host-recipe.json` and
`.analysis/core192-enemy-whole-root-proof.json`. Prior CORE191/188 and all
historical proof-bound binaries and source inputs remain intact.

## Exactness and next targets

The draft now covers **130 effective opcode values / 98 original primary
heads** out of 174 heads. This is semantic progress, *not* machine-code
completion or a new native byte-identity claim. CORE192 did not change
maintained production source/header/compiler profiles or acceptance ledgers,
so its affected native cold-build/replay scope is **zero**. No full cold
replay was performed. Confirmed authored native-exact coverage remains
**220 functions / 57,442 bytes / 1,006 configured canonical units**.

The most valuable next dependent Boss function is the original **474-byte
`0x004D47F0` LaserController create method**. Its 4-way dispatch, allocation
and virtual init are not yet source-admitted, so the private host captures
that boundary. Other large original Enemy heads 700/701/711/713, queued
selector codegen, and full root EH/jump-table reconstruction remain open.
