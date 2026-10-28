# CORE208 — entire original Enemy opcode 632: borrowed ECL script pointer

The original Japanese TH20 v1.00a Steamless binary is pinned at SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
CORE208 extends the **same complete 41,967-byte**
`EnemyState::execute_opcode` source-draft root at `0x0048C010`, with the
complete native opcode **632** interval `0x00493831..0x0049392C`
(**252 bytes / 62 x86 instructions / 10 direct calls**). Its native SHA-256
is `45cdbd018eea322e53dcffa4af1834acceeb26b2f9ba2aa72d6a17d41535f277`.
The locked-PE independent Capstone instruction set, case-path catalog,
complete direct calls and final `jmp 0x004963DF` agree. The opcode is part
of the whole original root—not a stand-alone 252-byte function credit.

## Original behavior and a critical borrowed-pointer distinction

The branch calls the original ECL `integer_argument(0)` for a queued record
index, then `integer_argument(1)` for a BulletCommand vector index. **Both
reads occur before** `EnemyState::writable_shot` at `0x00498B80`, the
independently accepted **396-byte full native byte-exact** COW selector. The
selector returns the real record/metadata pointer pair; the branch uses
the metadata pointer to access the native `std::pmr::vector<BulletCommand>`
at offset `+0x4`. Its original native command-array size function at
`0x00486600` and resize at `0x004862F0` ensure unsigned `index + 1`
elements when necessary. The checked 44-byte command element accessor at
`0x0047C6C0` returns a genuine `BulletCommand`.

The branch then stores a raw pointer to **`EclInstruction + 0x1C`** in
`BulletCommand::script` at offset **`+0x28`**, without copying or allocating
a string. The native operations at `0x00493901`, `0x00493906` and
`0x00493909` compute `4 * 3` then add the packet pointer and `0x10`:
this is the **fourth** word of the trailing instruction payload. The
original store at `0x00493925` preserves all other command fields and
metadata cursor, with no separate ECL operand read for the script text.
The script's lifetime belongs to the ECL packet owner. Treating it as a
freshly allocated `std::string`, dereferencing it after the packet expires,
or reading `float_argument(3)` would change the original semantics.

## Single whole-root integration, with real owners

Active private whole-root source:
`.analysis/core208-enemy-dispatch-candidate.cpp`. The complete **86-TU**
GCC host in `.analysis/core208-dispatch-host.cpp` calls the actual
`src/EnemyQueuedSelection.cpp` 396-byte accepted native COW method and uses
real PMR vector storage and 44-byte `BulletCommand` values. Its new
`.analysis/core208-op632-script-pointer-host-cases.inc` runs **324** cases:
**304 normal paths**, including 80 independent shared-owner COW clones,
144 first-time metadata owners, **112 actual PMR vector growths**, and
bitwise preservation of the other command fields. Each valid test packet
contains real trailing bytes and asserts both that the stored pointer is
*exactly* the address `&instruction + 0x1C` and that the pointed-to text is
unchanged. Twelve early ECL argument exceptions prove zero premature COW,
allocation or script publication. Eight chained scenarios execute
**632 → 609 → 632**, verifying that subsequent integer/float command
modification preserves the borrowed script pointer and the second 632
retargets only that pointer.

Both complete-host configurations pass **44,554/44,554** scenarios, keeping
all previous **44,230**: GCC 13 `-O2 -Wall -Wextra -Werror` with UBSan,
and independently with ASan+UBSan and leak detection. Only unrelated fixture
`WeaponStoneInfo` vptr instrumentation is excluded due unlinked native RTTI.
Passing logs, original 252-byte native calls, SHA hashes of four current
source/recipe inputs and two entire-root binaries are protected in
`.analysis/core208-enemy-whole-root-proof.json` and
`.analysis/core208-native-632-audit.json`. Previous CORE207/206 and earlier
source, compiler and native evidence remains intact.

## Exactness scope and continuation

CORE208 changes **zero maintained production compiler inputs**, so its
canonical native cold-build/replay scope is **zero**. No unfiltered/full
cold replay or unrelated CI was invoked. The whole Enemy source draft now
covers **141 effective opcode values / 109 original primary heads** of
174. The original **41,967-byte Enemy boss remains machine-code nonexact**.
Confirmed accepted native totals stay at **226 complete authored functions /
58,837 native bytes / 1,012 canonical units**. Future high-value work
includes the 346-byte native opcode 621, the 339-byte Bullet firing owner
from opcode 601, missing original heads and full root EH/jump partition.
