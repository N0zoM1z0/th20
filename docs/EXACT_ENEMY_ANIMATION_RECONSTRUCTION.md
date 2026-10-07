# Whole Enemy animation dispatch and parameter protocol

EXACT-065 reconstructs twenty complete functions with 2,218 instruction bytes
and 77 associated alignment/table bytes. The largest is the actual
`EnemyState::change_animation` at `00496B90`: 967 instruction bytes, one compiler
NOP, and all nineteen four-byte switch pointers, for a complete 1,044-byte
comparison. This is a direct dependency of the still-pending 41 KB `0048C010`
Enemy dispatcher; it does not establish partial or whole exactness of that root.

## Target observations and independent bindings

Attested Ghidra exports cover every instruction through the final return of each
accepted body. `00496B90` reads the current instruction through Enemy `00499310`,
reads animation index zero, grows the real PMR vector if necessary, uses its
unchecked subscript, and resolves the selected handle. Failed resolution returns
before reading any mutation parameters. The vector size (`0049CB30`), resize
(`0049C2A0`) and subscript (`0048BCE0`) have independent whole native exports.
Existing ownership/resize/subscript bindings and the actual 20-byte link stride
corroborate their ABI; no new library or vector coverage is counted here.

The signed instruction opcode is reduced by 319 and bounded by 18. The native
indexed JMP explicitly names table `00496F58`. Its nineteen entries reach the
thirteen implemented operations and the shared no-op exit. Default entries,
out-of-range exit, failed lookup and all table pointers remain in the complete
comparison. The native next function begins at `00496FB0`; twelve intervening
INT3 bytes are outside the actual cold COFF contribution and receive no credit.

| Owner / behavior | Entry | Instruction bytes |
| --- | --- | ---: |
| Enemy animation dispatcher | 00496B90 | 967 |
| Enemy current instruction | 00499310 | 22 |
| Three-channel color construction | 0048B720 | 34 |
| Color-to-integer-triple construction | 00429180 | 82 |
| Rotation wrapper / Z rotation | 00450590 / 004505C0 | 33 / 47 |
| Primary / secondary scale | 00470E50 / 004864F0 | 60 / 60 |
| Scale interpolation | 0049C680 | 104 |
| Scale / final-position references | 0044CCA0 / 0044CB20 | 17 / 19 |
| Position interpolation | 004614A0 | 51 |
| RGB channels / interpolation | 0049C860 / 0049C5E0 | 50 / 155 |
| Primary / secondary alpha | 00470B60 / 0049C8A0 | 25 / 25 |
| Primary / secondary alpha interpolation | 00464580 / 0049C520 | 91 / 134 |
| Second flag byte | 0045DD40 | 25 |
| Signed layer selection | 00450350 | 217 |

The native producers write separate B/G/R/A bytes and read packed color words.
The shared declaration therefore exposes these actual representations through
unions, preserving both original word fields and constructor/reset behavior.
`Color3` has three real B/G/R bytes without padding. Its conversion initializes
all three signed components to zero, then assigns R, G and B into third, second
and first. The original type names and original union spelling remain unknown.

Separate native byte consumers establish the three-bit secondary color mode and
two-bit layer mode. Layer ranges 3..19 and 20..23 select modes one and two;
other signed layers select zero. The 20..36 and 45..53 ranges set byte `+4A4` to
one unless flag 23 vetoes it. Other paths retain that byte. The full-width
bitfield declaration explains the native read/AND-zero/OR-one write, while
constructor/reset replay guards the existing aggregate layout and initialization.
The layer update hook folds to the existing empty `0040E5E0` body; it receives
no duplicate function credit or new authorship classification.

Complete native interpolation children independently establish actual reference
parameters, start/end/current transfer and timer reset. Float/integer `begin`
fold at `00439550`; Vector3/IntegerTriple at `004395D0`; Vector2 uses `00439640`.
These aliases retain their actual template types and receive no duplicate credit.
Local switch labels are bound using COFF section values, the native indexed-JMP
operand and the reviewed opcode paths, independently of the fields compared.
Eight complete container/interpolation/empty support contributions
independently replay without coverage credit. Canonical replay includes every
DIR32 and REL32 relocation.

## Compiler observations and rejected alternatives

The natural whole dispatcher uses the real EnemyState, Enemy, Animation,
AnimationHandle, Color3, PMR vector and interpolation owners. Maintained source
has no profile branches or assembly. EnemyScript and IntegerTriple retain their
existing recipes; new translation units use the explicit GS/SDL/EHsc C++20
recipe recorded in the canonical manifest. This is a per-unit result, not a
claim about all game compiler flags or complete linkage.

A named Vector3 local hoists storage under GS and changes the stack layout. An
explicit `Vector3{...}` expression introduces a constructor-result reference
spill; C++17 retains that discrepancy. Direct list initialization of the existing
reference parameter preserves left-to-right X/Y reads and eliminates the extra
spill naturally. This reproduces the whole 1,044-byte contribution. No inert
locals, pointer ABI substitution or padding were introduced.

Private byte-pointer experiments add address temporaries to channel access and
are rejected. The real packed-word/channel representations reproduce the native
whole parameter functions. Every accepted extent ends at its complete return;
none is shortened to hide mismatches.

## Semantic checks and scope

Owned host tests execute the maintained dispatcher, actual EnemyScript argument
forwarding, every maintained animation parameter body and real value/container
lifetimes. They exercise all thirteen operations, every default table index,
out-of-range opcodes, parameter-read ordering, invalid-handle clearing, PMR vector
growth before resolution, modulo byte narrowing, BGR interpolation order,
start/end/current transfers, flag preservation, secondary-mode retention and
signed layer boundaries with flag-23 veto. The runner uses C++20/O2/UBSan.

Startup, ECL argument reading, surrounding unresolved polymorphic lifetimes and
renderer lookup are explicit bounded fixtures. These tests do not execute the
original Windows game or prove production renderer/resource startup. Valid
mutation indices remain nonnegative; this work does not invent malformed-index
recovery for the native unchecked vector access.

The reference `change_enemy_animation` (REF-040) and `set_animation_layer`
(REF-042) remain credited as behavioral leads. Their service/raw-offset wrappers
are replaced by canonical owners and complete native member functions. Other
reference bodies receive no invented exact association. New source origins remain
pending; 64 authored functions / 16,948 authored bytes are unchanged.

Next integrate these real interfaces into the complete `0048C010` root. Laser
virtual ownership, callback tables, copying allocation/queue emission and other
whole direct dependencies remain open. The normal root CFG/table audit and the
five actual temporary cleanup owners are preserved for that work.
