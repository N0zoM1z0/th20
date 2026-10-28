# CORE/EXACT-381 — ten game-owned whole native roots, 28,350 bytes

Comparison target: immutable Japanese TH20 v1.00a Steamless original
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Scope and provenance:** This checkpoint is a new *independent original
PE and game-authored-origin audit*, not newly typed source. The
maintained C++ implementations and canonical matching compiler objects
already existed. Ten full original game-owned functions had been left
as `origin=unknown / disposition=review / reconstructed` in inventory.
Reexamining complete native instruction boundaries, original PE E8 and
HIGHLOW references **including real symbol addends**, real TH20 class
owners, and independently original callers now resolves their actual
game-owned origin and promotes them to live authored-exact credit.
No already credited original native address is counted twice.

## Five genuinely large original game-owned functions

| Whole function | Original native entry | Complete original body | Native instructions | Original E8 / HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `ProgressProfile::ProgressProfile` | `0x0050AF20` | **13,684B** | **3,549** | **127 / 4** |
| `Animation::update_geometry` | `0x00435C80` | **5,388B** | **1,239** | **43 / 64** |
| `easing` | `0x00454EF0` | **4,154B** | **717** | **6 / 336** |
| `EnemyMotionInterpolation::sample` | `0x004A8D70` | **2,433B** | **635** | **43 / 18** |
| `EnemyState::update_movements` | `0x004A7710` | **1,675B** | **450** | **52 / 13** |

These five original bodies total **27,334 unique original native code
bytes**. Their source owners are `src/ProgressProfile.cpp`,
`src/AnimationGeometry.cpp`, `src/Easing.cpp`,
`src/EnemyMovement.cpp` and `src/EnemyMovementUpdate.cpp`, each retained
with its original locked MSVC compiler profile.

**ProgressProfile constructor:** Its real TH20-specific
`ProgressProfile` is 0x7AE8 bytes, initializing 70 Scores, 123
physical 224-byte Spell records, 72-byte Statistics and 63 Practice
records. The independently original `ProgressSnapshot` constructor
at `0x0050E540` invokes it through the native iterator for
**18 Profile records** and directly for a distinct fallback.
Actual profile parsing/saving code consumes this exact game record
shape; this is project-specific game data ownership, even though the
maintained constructor source uses a genuine C++ defaulted constructor.

**Animation geometry boss:** The real `Animation` update at
`0x0042B5D0` calls `0x00435C80`. Its seven original geometry selectors
write actual 24-byte and 28-byte vertex records for screen/world
rings, arcs, XZ strips and triangles, with live parent/window
transforms. The original code extent is 5,388 bytes and the canonical
contribution is **5,452 bytes**: the extra **24-byte pointer table
and 40-byte selector table** are retained and strictly compared,
not omitted after the last return.

**Easing dispatcher:** The game-owned 4,154-byte easing switch is
called by Animation/interpolation/Enemy/ECL routines. Its actual
contribution is **4,284 bytes** because of **two alignment bytes and
a 128-byte native jump table**. The original code and table, including
all native table relocation fields, remain covered by the strict
canonical original oracle.

**Enemy interpolation and movement:** The complete 2,433-byte
`EnemyMotionInterpolation::sample` implements the original timer,
duration, axis-specific modes, vector/tangent and Hermite/easing
math. Its independently original caller is the separately exact
1,675-byte `EnemyState::update_movements` at `0x004A7710`.
That complete game boss handles actual Enemy movement samples,
parent motion, animation transitions and original off-screen flags.
Its original script-state caller is `0x004AB4C0`; neither method
is a generic compiler/STL routine.

## Five separate smaller, complete real TH20 functions

| Whole original method | Native entry | Original bytes | Original E8 / HIGHLOW |
| --- | --- | ---: | ---: |
| `Animation::position(Vector3&)` | `0x004376E0` | **103** | **3 / 0** |
| `Animation::transform_position(Vector3&)` | `0x004379E0` | **660** | **16 / 8** |
| `ProgressScore::ProgressScore` | `0x0050E4A0` | **81** | **0 / 0** |
| `EnemyMotionInterpolation::factor(int)` | `0x004AAB10` | **89** | **2 / 0** |
| `EnemyMotionInterpolation::factor()` | `0x004AAB70` | **83** | **2 / 0** |

These five different physical original addresses add **1,016
unique native bytes**. The real Animation position/reference
ownership, Score object initialization and two Enemy easing-factor
overloads were checked against original callers and the class
source. No identical folded alias or other credited native interval
is repeated.

## Independently recomputed native PE and symbol-addend proof

The fresh private audit at
`.analysis/core380-big-native-audit.py`:
1. Reads the **unmodified original PE** and independently decodes
   every full native x86 instruction head for the selected functions.
2. Obtains all direct E8 call targets from **native original** x86
   instruction operands and absolute HIGHLOW fields from the original
   `.reloc` table, including post-body original dispatch tables.
3. Compares every original reference location/type with the actual
   locked COFF function relocation.
4. Independently verifies the true original destination via
   **original native target = canonical source symbol base +
   actual compiler COFF addend**. The addend is essential for
   WindowState subobjects and native jump-table/internal labels;
   comparing raw symbol bases would produce false mismatches.
5. Checks the entire original physical compare extent, including
   13,689 bytes for the Profile ctor (five trailing INT3 bytes),
   5,452 bytes for Animation geometry, and 4,284 for easing.

All original E8/HIGHLOW field offsets/types, symbol targets and
addends agree **100%**, including:

| Root | Actual PE E8 | Actual PE HIGHLOW | Exact original references |
| --- | ---: | ---: | ---: |
| Profile 13,684B | 127 | 4 | **131/131** |
| Animation geometry 5,388B + table | 43 | 64 | **107/107** |
| Easing 4,154B + table | 6 | 336 | **342/342** |
| Enemy interpolation 2,433B | 43 | 18 | **61/61** |
| Enemy movement 1,675B | 52 | 13 | **65/65** |
| Animation position 103B | 3 | 0 | **3/3** |
| Animation transform 660B | 16 | 8 | **24/24** |
| ProgressScore ctor 81B | 0 | 0 | **0/0** |
| Enemy per-axis factor 89B | 2 | 0 | **2/2** |
| Enemy general factor 83B | 2 | 0 | **2/2** |

Original target SHA, full function SHA, x86 head count, complete
reference locations/targets and native addend comparisons are saved
in ten private
`.analysis/core380-native-big-audit-*.json` files and
`.analysis/core380-native-big-audit-summary.json`.

## Strict actual-source replay — five owners, not a global cold build

Some existing objects had **stale compiler receipts**; before
attribution, the real Profile, EnemyMotionInterpolation and easing
owners were individually cold rebuilt and strictly re-compared.
Then a single affected-only, reduced-priority strict replay rebuilt
**exactly these five existing source providers**, with **16/16
strict native units across five cold objects**:

`scripts/repo-python scripts/replay-exact-units.py
  --source src/ProgressProfile.cpp
  --source src/AnimationGeometry.cpp
  --source src/Easing.cpp
  --source src/EnemyMovement.cpp
  --source src/EnemyMovementUpdate.cpp`

The full exact replay and receipts are retained in
`.analysis/core380-five-big-owner-replay.log`. No source
implementation, public header, compiler profile, canonical object
identity or original PE bytes were changed by this checkpoint.

**Accounting conclusion:** Ten previously undercredited game-owned
complete native functions totaling **28,350 unique original code
bytes** are now recognized as authored-exact, but **no new canonical
units or source-present mappings** were introduced. This is an
explicitly documented provenance/status correction of **existing
fully reconstructed source**, not an assertion that 28,350B of C++
was newly authored in this one turn. Remaining large Animation/Enemy
dispatchers, startup lifetime and whole-executable linkage are
separate unfinished tasks.
