# CORE/LIB-254 — actual shot-command STL vector ABI and whole 3,735-byte emitter audit

All native evidence below comes independently from the locked Japanese
TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original compiler attribution must remain separate from game-authored code:
**two complete native C++ standard-library instantiations** were recovered
from the 3,735-byte Bullet emitter's actual command vector call sites,
but **neither should be counted in authored exact function/byte totals**.

## Two real complete MSVC STL instantiations

The original `EtamaArgInf` / `ShotMetadata` contains an actual
`std::pmr::vector<th20::BulletCommand>` at +`0x04`, matching the existing
native owner declarations in `src/ShotMetadata.hpp`. The true element
`BulletCommand` is **44 bytes** (`0x2C`) in the existing
`src/BulletValues.hpp` and the actual native allocator is
`std::pmr::polymorphic_allocator<th20::BulletCommand>`.

| Entire original STL body | Native address | Bytes | Original relocations | Scoped strict replay |
| --- | --- | ---: | ---: | ---: |
| `std::pmr::vector<BulletCommand>::operator[](size_t)` | `0x0047C6C0` | **33** | 0 | **33/33** |
| `std::pmr::vector<BulletCommand>::size() const` | `0x00486600` | **41** | 0 | **41/41** |

Both are emitted by **direct explicit instantiation of the existing
standard-library template** using the locked MSVC 19.44 x86 toolchain,
without any game-specific fake container type, target-byte data, manual
assembly, injected padding or altered compiler flags. `operator[]`
fetches the native `std::vector` data pointer and adds the signed x86
index multiplied by **`0x2C`**, while `size()` computes the pointer
end-minus-begin difference in 44-byte elements. This independently
corroborates both the existing 0x4C-byte ShotMetadata owner and the
embedded BulletCommand `opcode` at +0x20 and `script` at +0x28.

Original full-body SHA-256 values are
`0be16ac2c29ebaeb13b8b7cb2ae3ee14b8bb22062c785d4007382a3a785e15aa`
and `4973a1674bd95c81a3a092a450506c5ccd795770c88327e9aa7060fc07beba86`.
The two COFF bodies have **no relocation fields whatsoever**, so the
structural diagnostic already compares all 33 and all 41 actual bytes;
the canonical strict replay also freshly recompiles both and accepts
**2/2 complete native library units in one cold object**. Source:
`src/ShotMetadataVectorInstantiation.cpp`. The manifest explicitly
retains these as library-origin canonical providers. Their function
inventory and origin ledgers say **`origin=library`, `disposition=exclude`,
`owner=library`**, rather than erroneously claiming game-authored 100%
exact coverage in `config/matches.csv`. They are additionally mapped as
library-source-present for accurate maintenance and analysis. The actual
game-authored exact ledger remains at its previous **272 functions /
71,108 bytes**; **74 real compiler/library bytes** have been reconciled
separately.

## Independent whole-function and native switch-table reconciliation

The **complete original game-authored** single-shot
`BulletController::emit` boss is `0x004818E0..0x00482776`, **3,735B**
and **935 x86 instructions**, 60 direct calls to 43 distinct immediate
addresses, with two indirect jump-through-table locations. The native
whole-body SHA-256 is
`54c8c60dc8ca5aaf6a97e094db9447150152849e904741f1f110455b002e051d`.
The emitter really consumes the above `vector::operator[]` three times
and its `vector::size()` once; no prior notes were assumed to identify
their owner. Complete native disassembly independently establishes:

- Indirect branch at **`0x00481A7C`** uses the first native table
  **`0x00482778`**, **13 entries / 52 bytes**. Original entries 0..12
  target, in order, `0x00481A83`, `0x00481A83`, `0x00481B34`,
  `0x00481B43`, `0x00481B99`, `0x00481BA8`, `0x00481C1F`,
  `0x00481C51`, `0x00481CD4`, `0x00481D33`, `0x00481D33`,
  `0x00481EA8`, `0x00481F88`. This first table's independent SHA-256
  is `4e48be290d3aaa49d4861fac2de14664ac556bf956b5d01fa71d6105d2a80a55`.
- Indirect branch at **`0x004823B5`** uses the second native table
  **`0x004827AC`**, **11 entries / 44 bytes**, not an inferred
  13-entry array. Entries 0..10 target `0x004823BC`, `0x004823D1`,
  `0x004823E9`, `0x00482407`, `0x00482416`, `0x00482501`,
  `0x00482425`, `0x00482497`, `0x004824B2`, `0x004824CD`,
  `0x004824E8`. The table's native SHA-256 is
  `62eaa2431569f56870b2f3a04ea1ef55d54de507fc84811a0c60231058664866`.
- An original **one-byte NOP** at `0x00482777` follows the entire
  3,735B game method. The two contiguous tables end at `0x004827D7`;
  the following **eight CC alignment bytes** at
  `0x004827D8..0x004827DF` precede the independent 637B command-8
  method at `0x004827E0`. Thus the whole emitter code, its two real
  compiler jump tables and alignment occupy **3,840 bytes**, from
  `0x004818E0` up to (but not including) `0x004827E0`. Future whole
  exact admission must compare its full table-containing contribution,
  **not merely the first 3,735 function bytes** or a padded table guess.

The original 3,735B body still contains real Bullet slot allocation,
real free-list prepend, 0x4C-byte ShotMetadata move, typed Timer float
assignment, horizontal/vertical shot pattern arithmetic, object setup,
original Animation creation/file binding and native teardown on failure.
Its game-owned **3,735-byte** body and both 13-/11-way switch dispatches
remain **nonexact**. In particular the real native AnimationPoolOwner
allocation `0x0044C9B0` and file script setup `0x004383A0` remain
separately unresolved; correctly recognizing the STL methods does **not**
complete the whole shot emitter.

## Separate complete 1,846-byte physics boss (still nonexact)

The native `Bullet::update_physics` at `0x00485B60..0x00486295` contains
**1,846B / 517 x86 instructions**, **57 direct calls / 30 distinct
callees**, and a native state switch at `0x00485CC0` through a **four-way
active table** at `0x00486298` (entries `0x00485D67`, `0x00485CC7`,
`0x00486041`, `0x004860E4`). Its original whole-body SHA-256 is
`52127c18b3eb70751ce6c9ca21a35fb8e78b1b4281bea758fbd1f2c533220018`.
It calls nine separately exact command/trajectory handlers, the full
832B Bullet bounds boss, now exact 781B Bullet wrap and complete Bullet
retirement; none of those accepted children makes this entire 1,846B
parent exact. This physical source remains a major active reconstruction
target alongside the complete **2,018B** Bullet collision boss,
**12,140B** Bullet update and **41,967B** Enemy ECL opcode dispatcher.

**Validation scope:** this checkpoint adds just one new source containing
standard-library template instantiations and changes no existing source,
shared header, compiler profile or previously accepted relocation. Its
actual native replay scope is precisely **one cold MSVC object and two
new 33B/41B library units**, as recorded in
`.analysis/core254-shot-vector-stl-exact-replay.log`. **Zero old strict
units require replay**; no unfiltered full-graph cold replay was run.
