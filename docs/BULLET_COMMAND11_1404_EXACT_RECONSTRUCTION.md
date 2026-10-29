# CORE/EXACT-512 — complete original 1,404-byte Bullet command-11 boss, strict native exact

Immutable original target: Japanese TH20 v1.00a Steamless
`resources/th20.exe`, original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The entire original `Bullet::advance_command11()` at
`0x00481200..0x0048177B` is now strictly original-byte exact:
1,404/1,404 original bytes, 357/357 actual x86 instructions,
33/33 original native E8 direct calls and 35/35 original PE HIGHLOW
absolute fields independently reconciled.** The native whole body
SHA-256 is
`48a4da455a231997829ed66a57a9604d32988b2d8eb604749a935da80f94f546`.
This adds one whole game-authored native function and 1,404 disjoint
original-body bytes. There is no cropped-prefix, subfunction, assembler,
byte-patch, partial-match or parent/child double-credit acceptance.

## Actual gameplay and whole-function ownership

`src/BulletCommand11.cpp` maintains a genuine typed
`std::int32_t Bullet::advance_command11()` implementation. The original
1,846-byte whole-exact game `Bullet::update_physics` at `0x00485B60`
independently calls this original Bullet command-11 at `0x00481200`.
Its actual `ExtendedCommand[11]` Timer decrements before the mode gate.
When enabled and outside the true sprite-adjusted screen rectangle,
`Animation::sprite_data()` supplies the real width/height. The function
constructs two genuine eight-byte `Vector2` values, calculates unit
polar XY direction, normalizes all four corner vectors, and stores four
original cross products and four original projections in separate
float[4] arrays. It scans the nonpositive crossing then nonnegative
crossing half-planes, with original projected-distance eligibility and
running maximum state initially -999.0f. If no eligible candidate
survives the exact native -998.0f cutoff, it clears only Bullet command
flag `0x100` and returns 1. Otherwise the original Timer expiration
check determines whether that same bit is cleared; nonterminal frames
return 0. The actual polar/normalization/cross/dot, Timer and native
Animation sprite dependency calls all retain their original physical
callee addresses and ABI. Earlier complete gameplay analysis remains
in [CORE/RECON-302](BULLET_COMMAND11_FULL_SOURCE_FRONTIER.md), now
explicitly a historical nonexact codegen checkpoint.

## Recovery of the four original MSVC `/Od` local instructions

The original exact x86 at `+0x105..+0x11E`, immediately after the real
`polar2` call, independently reads two unchanged global native floats
**384.0f** at `0x0056CDA4` and **448.0f** at `0x0056D7C0`, then writes
them to **distinct stack slots** `[EBP-0x78]` at `0x0048130D` and
`[EBP-0x7C]` at `0x0048131A`. A fresh disassembly of the **entire
1,404-byte original** verifies these are the only accesses to those
two particular stack slots: the locals are initialized but no later
instructions read the saved copies. The original source spelling and
reason for retaining these scalars are unproven, but the compiled
assignments themselves are incontrovertibly part of the game binary.
They are **not fabricated compiler-shaping NOPs**, nor replacements
for actual gameplay expressions.

The prior maintained source had omitted these two legitimate original
local initializations on the assumption that source-level unused locals
should never be reconstructed. It produced a whole 1,378-byte /
353-instruction candidate with 66 relocations. That conservative earlier
choice is now superseded by independently verified native machine-code
evidence. Typed natural C++ source now preserves them as distinct
`const float screen_half_width = native_384;` and
`const float screen_half_height = native_448;` immediately after the
real polar call. Under the actual pinned `/Od` compiler profile,
those **four real original SSE instructions** and their two real
original stack-storage writes are re-emitted at exactly the original
positions. Independent source-local probes checked plain scalar,
const scalar, scoped scalar, reversed-local and array forms. Separate
scalars reproduce the whole original 1,404B, 357 instruction heads
and 68 relocations; a float array/struct gives different original
byte ordering and was rejected. Nothing in this source introduces a
new observable gameplay side effect or artificially patches a byte;
it models local initialization code that the original actually has.

## Corrected physically folded typed polar helper

The original command-11 direct E8 field at `0x004812FE` targets the
real physical **89-byte polar function** at `0x00439330`. Previously,
this source only declared `polar2(Vector2&,float,float)` without any
maintained definition. The original 89B body is already separately
strict canonical as `th20::polar(Vector3&,float,float)` and writes **only
XY**; it leaves Vector3's Z lane unchanged. The original Bullet caller
passes an actual **8-byte `Vector2`** destination, not a 12-byte
Vector3. Casting this destination to Vector3 would be undefined
behavior and historically false type attribution.

`src/MotionMath.cpp` now defines a **real typed
`polar2(Vector2&,float,float)`** with genuine float cosine/sine and
XY result writes. Under the original `MotionMath.cpp` `/fp:strict`
compiler profile, both complete typed polar contributions are
**89-byte / 89-byte original structural matches**, including the two
actual calls to the original native 24B float sine/cosine heads at
`0x00439530`/`0x004371D0`. The independently original physical
`0x00439330` body and its incoming original command-11 E8 are
unchanged. These two semantic source roles share **one original
physical game function**, so **zero** extra original bytes are
credited for adding the typed `polar2` linker alias. The precise
future whole-program linker ICF settings remain unproved; a complete
linked executable/runtime is not claimed.

## Independent immutable PE relocation and entire-byte proof

Fresh independent Capstone decoding of all original 357 x86
instructions found exactly **33 E8 calls**. Each original field's
relative displacement was read from the *original executable* and
resolved to its original absolute native callee. Separately parsing
the executable's **real `.reloc` blocks** found exactly **35 original
HIGHLOW fields** inside the complete 1,404-byte function, including
the two formerly omitted `native_384` and `native_448` fields. This
is a complete original field census: no original native E8 or PE
absolute site is omitted or filled from candidate field content.

The fresh new MSVC i386 C++ object exposes exactly **68 matching COFF
relocation offsets, types, symbol identities and ordinary addends**.
Every original native target agrees with its genuine callee/global
address, with original constant payloads for 384, 448, -384, -448,
-998, -999, zero, one and two independently read from native PE
`.rdata`. **All 1,132 remaining nonrelocated original bytes match
at their original positions**. Original `0x00439330` polar folding
is separately verified with two complete 89-byte compiled bodies.
The original 1,404-byte interval is disjoint from all previously
credited exact game bodies.

The new complete canonical unit is `bullet_command11_whole` using
`src/BulletCommand11.cpp`, fresh real
`build/core512-canonical/BulletCommand11.obj`, and pinned MSVC
19.44.35211 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compilation. Formal
`compare-coff-function.py --unit bullet_command11_whole --json`
reports **`exact`, 1,404/1,404**, not just diagnostic
`structural-exact`. The independent complete immutable-native proof,
original E8+HIGHLOW field table and original source scalar reads are
retained privately in
`.analysis/core512-command11-native-original-68anchor-proof.json`,
`.analysis/core512-command11-original-68anchor-proof.log` and
`.analysis/core512-command11-canonical-strict-result.json`.

## Affected-only native replay and remaining gameplay frontier

The changed source files are **only** `src/BulletCommand11.cpp` and
`src/MotionMath.cpp`, with no public-header changes. The command-11
whole boss previously had **zero canonical units** in its own source.
The actual `MotionMath.cpp` provider had **11 complete canonical units**
including the original physical polar body. That single previously
canonical provider was cold rebuilt and **all 11/11 prior units remain
strict exact**; the command-11 source was cold built into **one new
canonical unit**, and both source files were jointly replayed with
**12/12 strict whole native units, two source objects**. Logs:
`.analysis/core512-motionmath-recompile.log`,
`.analysis/core512-motionmath-11unit-scoped-replay.log`,
`.analysis/core512-command11-native-cold-build.log`,
`.analysis/core512-command11-polar-scoped-strict-replay.log`.
No full-graph cold replay was used.

**The game-authored exact inventory rises from 451 / 152,497B to
452 / 153,901 distinct original-body bytes. Canonical native units
rise from 1,177 to 1,178 and distinct canonical compiler object
providers from 237 to 238.** Source-present function mappings remain
1,177 because the original complete command-11 source was already
tracked before this exact admission. The separate original 12,140B
Bullet dispatcher, 3,735B Bullet emitter, Player 555B movement,
3,111B Player main frame and Animation/Enemy giant dispatchers all
remain unfinished. Byte-exact whole command-11 does not establish
full original game linkage, game runtime or a playable binary.
