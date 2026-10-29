# CORE/ORIGIN-529 / CORE/EXACT-529 — ten complete original Enemy/Motion game functions, 7,204 bytes

Immutable reference: Japanese TH20 v1.00a Steamless,
`resources/th20.exe` SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Ten complete distinct Enemy/EnemyState/Motion gameplay functions,
7,204 original native game-body bytes and 1,930 original i386
instructions, are now independently confirmed strict exact and accepted
as authored TH20 game code.** Several are substantially larger than
simple leaf methods, including the native **967-byte enemy animation
opcode dispatcher**, **844-byte movement combiner**, **818-byte float
variable resolver**, **809-byte motion position controller**, and
**780-byte enemy spawn initializer**.

This checkpoint is a **source-origin admission** of complete natural C++
that was already maintained with pre-existing canonical strict units,
**not a claim that ten new C++ functions were typed here**. Their
original game ownership was previously `unknown/review`, which
properly withheld original authored exact credit. The immutable
physical native code, all relocation and compiler-contribution bytes,
and each original caller were reexamined rather than trusting those
prior status documents.

## Whole native game method inventory

| Native original | Game body | Instruction heads | Real maintained function and game role |
| --- | ---: | ---: | --- |
| `0x00496B90` | **967B** | 306 | `EnemyState::change_animation`: original ECL animation opcodes 319–337 and typed Animation state |
| `0x004A7DA0` | **844B** | 219 | `EnemyState::combine_movements`: true multi-record velocity and interpolation composition |
| `0x00498210` | **818B** | 216 | `Enemy::float_destination`: original negative ECL variable IDs, enemy/player/controller float lvalues |
| `0x00453AC0` | **809B** | 247 | `Motion::update_position`: real four-mode polar and rotated spatial motion |
| `0x004A89C0` | **780B** | 204 | `Enemy::apply_spawn`: initial health/flags/position/stone/bullet rank and native Enemy tick |
| `0x004A3060` | **765B** | 160 | `EnemyState::EnemyState`: actual original Enemy variable, interpolation, Timer and phase lifetime owner |
| `0x00453E40` | **694B** | 185 | `Motion::update_velocity`: actual clock and five-mode velocity/angular rate update |
| `0x00498600` | **663B** | 177 | `Enemy::integer_destination`: original negative ECL integer IDs, four persistent script globals, controller fields |
| `0x004A8760` | **448B** | 123 | `Enemy::tick`: real slowdown clock, loop over active Animation handles, restores clock and updates game flags |
| `0x004A7170` | **416B** | 93 | `EnemyState::initialize`: actual movement/animation arrays, original health and timer reset, bounds and state |

The natural implementations are maintained in **six actual source
providers**: `src/EnemyAnimation.cpp`, `src/EnemyState.cpp`,
`src/EnemyVariables.cpp`, `src/EnemySpawnApplication.cpp`,
`src/EnemyTick.cpp`, and `src/MotionUpdates.cpp`. Each whole original
method has a distinct original entry and no physical overlap with any
previously credited authored native function. This does not establish
the historical C++ filename or original method spelling.

## Real original caller and author-origin evidence

Rather than inferring origin from function labels, every candidate's
immutable native address was checked against **actual original direct
E8 call instructions** decoded throughout the complete function
inventory. Most decisive relationships include:

- The original **41,967-byte Enemy ECL dispatcher** at `0x0048C010`
  directly calls `EnemyState::change_animation` at native `0x0048C391`
  and calls the 844-byte `combine_movements` **seven times**. Its giant
  *parent* is not native exact; these are native xrefs into its real
  gameplay opcode control flow, not guessed C++ includes.
- The separately already **whole exact 1,675-byte**
  `EnemyState::update_movements` at `0x004A7710` independently calls
  `combine_movements`, `Motion::update_position` and
  `Motion::update_velocity`. Other original `Motion::update` wrappers
  independently call both actual motion heads.
- The complete original `EnemyController::create` at `0x004A8920`
  calls the real 780B `Enemy::apply_spawn` at `0x004A897E`. Original
  `Enemy::Enemy` calls the 765B EnemyState constructor; actual
  `Enemy::initialize` calls its 416B `state.initialize`.
- `Enemy::tick` is reached by `Enemy::apply_spawn` (the original E8
  at `0x004A8BA0`) and another genuine Enemy update function.
  The actual emitted source uses the real 0x5E4 Animation slowdown
  method and original `ClockScalar` state, not generic STL cleanup.

**Eight** of these exact whole roots have identifiable independent
original game callers and are assigned **high-confidence authored**
classification. **Two** (`Enemy::float_destination` and
`Enemy::integer_destination`) have **no original incoming direct E8
calls discovered in the provisional complete-function inventory**.
These two are still clearly bespoke TH20 Enemy/ECL variable resolvers:
the entire native x86 code handles game-specific negative variable IDs
and game controller/script globals rather than any CRT or STL
algorithm, and the maintained types are actual Enemy/EnemyState game
owners. However their exact original invocation pathway (possible
indirect use or unreviewed caller boundary) is **not proved**, so
both deliberately retain **medium rather than high confidence**.
Their lack of discovered *incoming* E8 is separate from the many
normal E8 calls *inside* both resolver bodies.

All actual original callers, sites, native sizes, old tracking states
and possible unknown owner roots are retained independently in
`.analysis/core528-enemy-motion-independent-original-callers.json`
and the readable
`.analysis/core528-enemy-motion-native-callers.log`.

## Entire immutable PE byte and reference proof

All ten original body regions were read directly from the immutable
original executable, decoded through their full last instruction,
and checked for physical disjointness against every previously accepted
authored native range. The *real* physical bodies total
**7,204B / 1,930 i386 instruction heads**. The original compiler's
complete native code and attached tables/alignments cover **7,826B**;
**622 additional genuine compiler bytes** (switch tables, code-label
pointers and alignment) follow the respective body extents. Those
622 bytes were **fully compared** against the existing canonical
objects, but are **not** counted again as authored game-body bytes.

Independently decoding original native `E8` instruction operands
recovers **247 direct call fields** across the ten whole bodies.
Independently parsing the immutable original executable's actual PE
`.reloc` directory yields **128 HIGHLOW absolute fields** over their
full code-plus-table comparison spans, including real switch-table
label destinations. The original PE field position, kind and native
absolute target of **all 375/375** references agree with the already
maintained canonical MSVC COFF symbol identity/base and its actual
compiler addend. Every remaining nonrelocated original code/table byte
also agrees with the original, with no byte masking outside genuine
relocations, skipped instructions, fabricated original globals,
reordered branches, manual assembly or changed compiler flags.

The per-function original bytes and comparison extents are:

| Original source role | Game bytes | Strict whole comparable bytes | Original E8 / HIGHLOW |
| --- | ---: | ---: | ---: |
| Enemy animation opcode | 967 | 1,044 | 54 / 21 |
| Enemy combine movements | 844 | 844 | 25 / 9 |
| Enemy float destination | 818 | 1,001 | 32 / 27 |
| Motion position update | 809 | 832 | 32 / 10 |
| Enemy spawn | 780 | 922 | 15 / 12 |
| EnemyState constructor | 765 | 765 | 22 / 0 |
| Motion velocity update | 694 | 716 | 20 / 13 |
| Enemy integer destination | 663 | 838 | 23 / 26 |
| Enemy tick | 448 | 448 | 13 / 5 |
| EnemyState initialization | 416 | 416 | 11 / 5 |

Each original full function SHA-256, all native E8 and PE HIGHLOW
fields/targets, compiler comparison scope, attached data hash and
outside-relocation source-byte equality are preserved in
`.analysis/core529-enemy-motion-full-original-10anchor-proof.json`,
with human-readable proof in
`.analysis/core529-enemy-motion-original-native-audit.log`.
This proof reads targets from the original independently; it never
solves an original relocation destination from a C++ candidate field.

## Fresh focused native strict replay

Only the **six actual source/object providers** above were freshly
cold compiled with their original already registered per-source
MSVC 19.44.35211 x86 profiles. Since **no C++ source or public
header changed**, no other compiler input or include-closure unit
needed rebuilding. Full existing-object original native scoped
replay over these six sources passed **24/24 whole original canonical
units** from **six fresh native MSVC objects**, including the ten
newly origin-admitted game functions, other genuine Enemy and Motion
helpers and the previously accepted **1,371B `Enemy::defeat`**.
The newly accepted Enemy routines in this checkpoint were already
strict exact code: the new step was independently proving their
**game-authored origin**, not inventing new native bytes or changing
their compiler profile.

Reproducible private logs:
`.analysis/core528-enemy-motion-scoped-build.log`,
`.analysis/core528-enemy-motion-sixprovider-scoped-replay.log`,
`.analysis/core528-enemy-motion-six-provider-audit.json`.
No unfiltered full cold replay was performed.

**Authored exact totals grow from 455 whole original game functions /
154,558 disjoint original body bytes to 465 / 161,762 bytes.** The
1,181 existing canonical native units, 1,181 source-present mapping
rows and **241** distinct MSVC object providers do not increase:
these ten game bodies were already represented by canonical native
source and had pending *origin* classification. They are now explicitly
credited only once by their distinct whole original physical bodies.

The 41,967B enclosing Enemy ECL dispatcher, 39,470B Animation VM,
3,735B Bullet emitter, 555B Player movement and 3,111B Player main
frame remain independent **NONEXACT** roots. Original incoming E8
relationships and native whole-function equivalence do not prove the
parents exact, a full game link or playable runtime.
