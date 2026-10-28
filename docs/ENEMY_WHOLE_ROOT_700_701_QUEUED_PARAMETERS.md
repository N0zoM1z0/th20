# CORE198: native Enemy opcodes 700/701 inside the entire boss root

CORE198 continues the **same 41,967-byte original `EnemyState::execute_opcode`**
at `0x0048C010`, against the user-selected Japanese Steamless TH20 v1.00a
locked SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The new *private whole-root source draft* integrates two genuinely separate
original primary heads, rather than just leaf setters or shortened fake
root functions. The original 41,967-byte machine code, jump tables and EH
remain **nonexact**; no additional authored exact bytes are claimed here.

## Original native evidence and field ownership

The original target and independent native case-path catalog agree on both
complete local primary-head intervals, including instruction membership,
direct-call targets and the final full-root jump:

| Opcode | Original interval (exclusive end) | Bytes | x86 instructions | Direct calls |
| --- | --- | ---: | ---: | ---: |
| 700 | `0x0049392D..0x00493A3A` | 269 | 59 | 10 |
| 701 | `0x00493A3A..0x00493B5B` | 289 | 67 | 11 |

Both cases call the actual `EnemyState::integer_argument(0)` receiver then
the writable **396-byte** original queued record/metadata selector at
`0x00498B80`, which returns the *pair of raw pointers* independently
identified in CORE188: `EnemyQueuedRecord*` and `ShotMetadata*`. The
selector itself remains compiler-byte nonexact; its source-draft test
candidate executes real `std::pmr::forward_list`, `std::shared_ptr`,
`DebugAllocator` and deep copy-on-write where necessary, without inventing a
by-value `shared_ptr` return. The original 700 branch invokes
`EnemyState::float_argument` separately, in strict operand order **1, 2,
3, 4**, storing the first three raw float words into the selected record's
`ShotParameters::position.x/y/z` at record offsets `+0x10`, `+0x14`,
`+0x18`, and the last to the selected `EtamaArgInf::field_14`. The 701
branch invokes `EnemyState::integer_argument` separately for operands
**1 through 5**, storing their exact original unsigned word representations
into `EtamaArgInf` offsets `+0x24`, `+0x28`, `+0x2C`, `+0x30`, `+0x34`.
There is no final cursor write for 700/701; do not conflate them with
609–612 even though the same real metadata object is used. The original
opcode selector request always comes **before** later operands and their
side effects.

The original complete instructions, original PE branch bytes, SHA-256 and
every original direct call are recorded at
`.analysis/core198-native-op700.asm`,
`.analysis/core198-native-op701.asm`, and
`.analysis/core198-native-700-701-audit.json`. These were independently
redecoded from the locked PE and checked against the existing native
case-path catalog, not accepted from older reconstruction notes without
verification.

## Same-root implementation and two sanitizer runs

The new opcodes live in the *single continuing* entire Enemy root candidate
`.analysis/core198-enemy-dispatch-candidate.cpp`, preserving every earlier
opcode and its test coverage. The new
`.analysis/core198-queued-parameters-host-cases.inc` runs a matrix of **337
additional scenarios**: 152 successful four-float writes and 152 successful
five-integer writes, with two actual native parameter owner structures,
80 real deep COW copies, 144 first-time metadata owners, 64 real queue-list
growth situations, and **33 staged selector/operand exceptions**. It
checks every source/destination value, including positive/negative signed
zero, infinities, and distinct NaN payloads by bitwise comparison; complete
nonqueue Enemy state preservation; exact ECL operand read order; isolation of
the original shared owner after COW; and partial writes that persist when a
later VM operand throws. A genuine list extension may replace the queue
head, so the state-image assertion excludes **only that real container's
own bytes**, not an arbitrary surrounding state region.

The same whole-root host has been rebuilt with **84 translation units**,
including the unchanged, separately native-exact 474-byte Laser creator and
75-byte registration methods. All previous **42,087** scenarios still pass.
Both complete-host variants pass **42,424/42,424**: GCC 13 `-O2 -Wall
-Wextra -Werror` with UBSan and the same with ASan+UBSan. Only vptr checks
were excluded due to unrelated unavailable `WeaponStoneInfo` fixture RTTI;
ASan leak detection remained enabled. All active source/recipe hashes, both
complete-host binaries and both logs are in
`.analysis/core198-enemy-whole-root-proof.json`. Logs are
`.analysis/core198-dispatch-host.log` and
`.analysis/core198-dispatch-host-asan.log`. The original CORE196 and all
older protected sources, logs, binaries and proofs remain preserved.

## Exactness boundary and next work

The entire Enemy draft currently covers **132 effective opcode values
and 100 original primary heads** of 174 native primary heads. These are
semantic behavior fixtures, **not** an authored exact percentage or a
complete executable. This CORE198 integration changed **zero production
compiler inputs/headers**, so the affected canonical native cold-build
scope is **zero units**; there was no full cold replay. Conservative native
acceptance remains **222 authored exact functions / 57,991 code bytes /
1,008 canonical units**, including the separately exact 474-byte Laser
factory already covered by CORE195's 223 affected-only strict native units.

High-value continuation: investigate the complete larger native Laser
script branches 711 (619 original bytes) and 713 (611 original bytes),
which consume `LaserType2/3Parameters`, real PMR command copies and the
already exact 474-byte creator. Separately complete the four derived
concrete Laser classes and native 92-byte factory wrappers, without dummy
padding or invented constructor semantics. The 396-byte queued selector,
original 41,967-byte root compiler EH/switch and missing native primary
heads remain open.
