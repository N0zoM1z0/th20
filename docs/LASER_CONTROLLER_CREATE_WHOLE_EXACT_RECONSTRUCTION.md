# CORE/EXACT-195: complete 474-byte LaserController creation and switch table

The original TH20 Japanese Steamless v1.00a executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains the genuine `LaserController::create_laser` at **`0x004D47F0`**.
This checkpoint reconstructs the **entire 474-byte game-authored function**
in natural maintained C++20, with the exact original MSVC 19.44 x86 machine
code, **21 independently decoded relocation anchors** and its complete
compiler-owned **2-byte alignment + 16-byte four-entry jump table**. This is
one complete root of the LaserController creation subsystem, not a truncated
Enemy opcode case or an optimistic native body prefix. The larger **41,967-byte
`EnemyState::execute_opcode` root remains nonexact**.

## Original whole-function and jump-table evidence

The full native interval `0x004D47F0..0x004D49CA` has **474 bytes / 149 x86
instructions**, SHA-256
`9c4e941d4749b25ca6d2866023ea2082549aa358d6d88bab8d7e3f3aa9235ce7`.
The compiler adds the original x86 `66 90` alignment at `0x004D49CA..CB`
then a **16-byte absolute-address table** at `0x004D49CC..DB`. Original
machine code has a `ja`-guarded indexed jump through this table. Its four
original table entries are `0x004D484B`, `0x004D48AC`, `0x004D4968` and
`0x004D490D` (types 0/1/2/3, not simply textual branch order). All
21 relocation destinations, including all four table entries, were decoded
independently from the locked PE, before registering the canonical manifest.
The complete original byte, branch and relocation proof is protected at
`.analysis/core195-native-laser-creator-audit.json`.

The concrete game protocol is more than a little setter. It checks the **signed
active count** `LaserController+0x28` against 512; when at or above the cap,
returns 0 without allocating or changing the handle. Otherwise it increments
`next_handle` at `+0x2C` first and applies a **signed floor of 0x10000**
before choosing a concrete Laser type. Even unsupported type indices preserve
that handle increment and return the current full integer handle. Each of
the four valid branches calls the original process `DiagnosticAllocator*`
`0x005B8894`, passes its genuine game-owned source label, and invokes a
distinct original 92-byte factory:

| Native type | Original concrete owner label | Original factory entry |
| --- | --- | --- |
| 0 | `LaserLineInf` | `0x004C8190` |
| 1 | `LaserInfiniteInf` | `0x004C8130` |
| 2 | `LaserBeamInf` | `0x004C8080` |
| 3 | `LaserCurveInf` | `0x004C8020` |

The debug labels have independent complete strings from the PE's `.rdata` at
`0x00571478`, `0x005714C0`, `0x00571508` and `0x00571550`. The source
labels and type-to-factory mapping are native observations; the inferred
method spellings `allocate_laser_line/infinite/beam/curve` do *not* claim
original symbol recovery. Their four actual concrete allocation/construction
bodies and lifetimes are still **undefined interfaces**, not fake implemented
factories. They are declared on the genuine `DiagnosticAllocator` owner in
`src/DiagnosticAllocator.hpp`, and their original addresses anchor the exact
creator's four call relocations.

A non-null concrete Laser has its `Laser+0x8C` handle assigned **before** its
actual virtual initializer is invoked via vtable offset `+0x14`. The native
call pushes the original typed parameter pointer and tests the **signed
32-bit** result; a negative initializer result returns 0 without registering
it. This independently corrected the previous unresolved `Laser::slot_14`
`void()` placeholder to
`std::int32_t Laser::initialize_laser(const void*)` in the maintained virtual
interface; the original spelling and exact concrete derived types remain
inferred. A successful initializer calls the previously accepted complete
**75-byte** `LaserController::register_laser` at `0x004C9300`, now real
maintained source, with **four independent actual native caller sites**.
That method initializes the actual intrusive link, prepends it to the
controller's active list and increments count after list insertion. A null
factory or failed initializer preserves the already advanced handle and
returns 0. The original code shows no invented cleanup in those early returns;
concrete allocation error and ownership policies require separate work.

## Independent compiler experiment and complete exactness

A first private diagnostic correctly matched native control flow but reported
**492 bytes versus a 474-byte function inventory**, because the compiler
emitted its two alignment bytes and four table entries in the *same complete
COFF contribution*. We **did not truncate** the COFF comparison to force a
474-byte prefix. Comparing the entire **492-byte** source contribution
achieved **408/408 non-relocation bytes**. The actual production source
`src/LaserFactory.cpp` then compiled using the genuine `LaserController`,
`Laser`, `DiagnosticAllocator`, existing full
`LaserController::register_laser` and explicit native virtual interface.
Its canonical `laser_controller_create_laser` unit is declared in
`config/match-units.toml` with `size=474`, `compare_size=492` and all **21
original relocation offsets/types/symbols/targets**. Locked MSVC 19.44.35211
x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` strictly
replays **474/474 native function bytes and all 492/492 compared bytes**,
including the complete jump table and all relocation replay fields.
The canonical product and receipt are
`build/core195-canonical/LaserFactory.obj` and its sibling `.receipt.json`.
No fake assembly, target PE patch, ignored mismatch, changed function boundary
or replacement original `.rdata` address was used.

## Scoped native regression across the actual include closure

Because the corrected virtual slot and concrete factory declarations modify
`LaserParameters.hpp` and `DiagnosticAllocator.hpp`, the source closure is
larger than the registration leaf. Original complete compiler receipts
select exactly **33 existing/new provider objects and 223 canonical native
units**. Each of those 33 providers was **cold-built independently at reduced
priority** using its original pinned compiler profile. All **223/223** units
subsequently passed strict full original relocation-aware replay from fresh
source/header/object receipts, covering 35,632 cumulative code bytes and
35,832 comparison bytes across those affected units. This outcome includes
all old native units in the affected closure, not merely the new 474B method.
None of the unrelated canonical providers was cold-built.

The new declarations changed MSVC compiler-internal `$SG` names in several
TUs. Rather than accepting the first failing unit, we audited **all 223
affected native COFF objects/functions** against the original PE and found
**zero non-relocation code mismatches**. The full manifest diff contains
exactly **42** compiler-private `$SG` symbol renumberings in 23 functions
across 13 sources, plus the new canonical unit. For each changed `$SG`, the
original target address, relocation kind/offset and the matching native
literal remained identical. Only fresh COFF symbol names changed; no old
relocation destination, exact range, type or target bytes were altered.
See `.analysis/core195-all-42-sg-renames.json` and
`.analysis/core195-223-strict-attested.json`, plus the per-provider
`core195-replay-*.log` receipts. No full cold replay was run.

## Acceptance scope and next Boss work

CORE/EXACT-195 admits **474 game-authored native instruction bytes** from
this complete function (plus **18 separately compared** compiler alignment
and jump-table bytes). The conservative live ledger advances to **222
authored exact functions / 57,991 authored bytes**, **1,017 source-present
mappings**, **1,008 physical strict units** and **167 canonical comparison
objects**. The four concrete allocator bodies, derived virtual Laser
initializers and runtime construction/destruction are still unknown.
The whole Enemy opcode dispatcher at `0x0048C010` remains **41,967 bytes
nonexact**. Its latest CORE192 same-root private host has **40,941/40,941**
GCC O2/UBSan and ASan+UBSan semantic scenarios. That historical host
captured the 474B creation boundary; it **does not yet execute the newly
admitted real factory**. A useful next step is to integrate the real source
into that same whole-root fixture while keeping the four allocation/virtual
initializers as explicitly captured dependencies, then attack the native
92-byte allocators and full beam constructions. Do not claim full executable
or game startup/runtime reconstruction from this local codegen acceptance.
