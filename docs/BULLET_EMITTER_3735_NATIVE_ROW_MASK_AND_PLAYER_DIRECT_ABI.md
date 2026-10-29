# CORE/RECON-615 — original 16-bit row masking and direct Player-position reference ABI, entire 3,735B Bullet emitter

**Later CORE/RECON-624 current whole-boss x87 checkpoint:**
[Original RNG/cosine/sine returned-float lifetimes](BULLET_EMITTER_3735_X87_RETURNS_934_FRONTIER.md)
are restored in the full 3,735B Bullet emitter game C++ source.
The maintained whole code generates **3,736B/936 instructions with
934/935 original mnemonic heads aligned**, and **all 60 original
physical E8 callees correct in ordinal order**. The remaining mode12
x87 float/parameter reload order and one extra compiler NOP are
not yet natively exact. Historical older scores below remain as
evidence, not the current whole-source status. No original parent
exact-byte credit or full graph cold replay.


Immutable game target: Japanese TH20 v1.00a Steamless,
`resources/th20.exe` SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The original game-authored `BulletController::emit()` remains NONEXACT.**
Its entire original code is **3,735 bytes / 935 i386 instructions**
with a genuine compiler contribution (code, alignment, 13+11 switch
labels) of **3,832 bytes**. Fresh locked MSVC i386 C++20 compilation
of the maintained complete `src/BulletEmitter.cpp` now emits
**3,736 bytes / 936 instructions, with 928/935 original ordered
mnemonic heads aligned and all 60 original E8 callee identities
correct in native ordinal order**. The full compiler COFF contribution
is also **3,832 bytes**, and the 69 absolute references agree with
original PE by *count* but not physical site. This is a stronger
whole-source reconstruction of real game behavior than the previous
3,742B / 938-instruction candidate; it is **not** a 3,735/3,735-byte
strict proof, not a final original executable and adds no game-authored
exact byte credit.

## Two genuine original AND masks, not `& ~1`

Modes 9/10 use row-derived even indices for stepped bullet speeds.
The prior C++ source wrote `((row+1)&~1)` and `(row&~1)`.
That is not just a compiler instruction-length choice: `&~1`
means `& 0xFFFFFFFE` in a signed 32-bit value and **preserves the
upper 16 bits**, while the actual original machine code applies
**`& 0x0000FFFE`**, clearing those high bits.

The two original immutable PE method-relative x86 instructions are:

| Original native instruction | Exact original bytes | Semantics |
| --- | --- | --- |
| `+0x4BF` | `81 E1 FE FF 00 00` | `and ecx, 0x0000FFFE` for odd rows `row+1` |
| `+0x53F` | `81 E2 FE FF 00 00` | `and edx, 0x0000FFFE` for even rows `row` |

The earlier source compiled each one as a **3-byte** sign-extended
`and reg,0xFFFFFFFE`. The maintained real C++ now uses the correct
`&0xfffe` mask. Under pinned `/Od` the compiler emits the real two
**6-byte `and imm32` instructions**. In the current candidate their
physical offsets are `+0x4C0` and `+0x540`, exactly one byte later
than original because of a separately unresolved earlier NOP.
Their *complete six instruction bytes* agree with the two original
native instructions; no byte copying, manual instruction or invented
source memory is involved.

Replacing the two wrong masks adds **six bytes of genuine compiled
original-game behavior** without adding any new E8 or HIGHLOW
references. The error could change actual values for negative or
out-of-range row indices; the source fix preserves the original
unsigned-mask truncation, not just matching assembly size.

## Original Player-position reference is passed directly

At the end of the emitter the original PE performs the real
`Context::player()` E8, then the real
`Player::position_ref()` E8, and **immediately pushes the returned
EAX reference address** for the existing native
`geometry::squared_distance_xy` call. The old C++:

```cpp
const auto& player_position = context->player()->position_ref();
if (geometry::squared_distance_xy(bullet->position, player_position) < field_48)
    // ...
```

introduces a source-local `const&` temporary. The pinned `/Od`
compiler generates an original-absent pair:
`mov [ebp-0xbc],eax; mov eax,[ebp-0xbc]` between the two
actual native E8 calls. Their separate function identities and
arguments were previously correct; the **lifetime / stack protocol**
was not.

The maintained source now uses the actual direct C++ reference
argument:

```cpp
if (geometry::squared_distance_xy(
        bullet->position, context->player()->position_ref()) < field_48)
    // ...
```

The value, member receiver and original game behavior remain
correct, but two non-original stack instructions and **12 native
bytes** vanish. Other private variants (a local pointer, `auto&`,
const local reference and named distance result) were compiled as
whole 3,735B candidates; only direct reference passing or evaluating
distance into a scalar local reproduced the original receiver-passing
instruction count.

## Whole native exactness is still a separate requirement

| Entire native method metric | Before these source fixes | Current maintained C++ | Original PE |
| --- | ---: | ---: | ---: |
| Original/candidate method code | 3,742B | **3,736B** | 3,735B |
| x86 instruction heads | 938 | **936** | 935 |
| Original mnemonic heads aligned in order | 928 | **928** | 935 |
| Direct E8 call-reference fields | 60 | **60** | 60 |
| Whole compiler/code/table contribution | 3,840B | **3,832B** | 3,832B |
| Whole source/PE absolute fields | 69 | **69** | 69 |

The independently decoded original PE has **45 actual HIGHLOW fields
in code and 24 in its native two switch-label tables**. The maintained
COFF has 69 DIR32 fields and the same total 3,832-byte compiler
extent, including an actual 32/32 original-byte-exact writable
cancel-script table at `0x005AEFF8` already documented in
[CORE/RECON-605](BULLET_EMITTER_3735_CANCEL_TABLE_AND_METADATA_928_FRONTIER.md).
All 60 current E8 fields still resolve to the **correct original
physical callee address in ordinal order**, including the exact
legacy 63B shared_ptr move operator and folded 8B move helper.
But the physical E8 field *positions* are not yet exact: independent
site-by-site original PE versus COFF comparison gives **11 original
E8 sites identical by offset and 49 candidates shifted +1 byte**.
This drift begins after the source's extra **1-byte `nop` at
method-relative `+0x112`**, immediately following its second Timer
float assignment. The original has no such NOP at that position.
Current source has one extra x86 instruction overall, and several
original SSE stack-slot and operand-lifetime differences remain.
The candidate's table offsets and compiled-source EH selection
must still be reconciled with the actual original; matching counts
and section size do **not** authorize an exact-body claim.

## Negative experiments and bounded source verification

The entire original 3,735B method was compiled repeatedly with
real C++ variations to challenge the assumption that the extra NOP
comes from merely where `float base_speed;` is declared. Moving its
declaration to ten legitimate positions left the native `+0x112`
NOP unchanged. Grouping the two Timer assignments using comma
expressions, explicit member calls, parentheses, or local blocks,
and expressing `shot.rows > 1` as equivalent signed comparisons,
also failed to eliminate the NOP without introducing new original
mismatches. The private diagnostics never patch `.obj` bytes or
insert hand-written `nop` directives into source.

The new whole-source compiler score and independently PE-backed
original reference proofs are reproducible under:

- `.analysis/core614-emitter-fresh-whole-native-score.json` — 3,736B/936 current candidate and two genuine 6-byte AND instructions.
- `.analysis/core615-emitter-native-mask-60-E8-proof.json` — all 60 whole original E8 physical targets in native order.
- `.analysis/core615-emitter-native-mask-original-color-proof.json` — original 32B writable table and 45+24 PE HIGHLOW to COFF comparison.
- `.analysis/core615-emitter-physical-offset-drift.json` — exact E8 original/candidate site-drift count (11 equal, 49 plus one).
- `.analysis/core606-emitter-player-position-ABI-results.json` — six whole-function typed Player position lifetime probes.
- `.analysis/core612-base-speed-nop-lifetime-results.json` — eleven whole-function local-declaration placement experiments.
- `.analysis/core613-timer-native-NOP-and-row-conditional-results.json` — fifteen whole-function Timer and signed-row source/flag experiments.

**Only `src/BulletEmitter.cpp` was changed** in production. There are
**zero previously accepted native canonical exact units** configured
in this source, so a fresh whole-file native locked MSVC compile and
original PE verification are the entire *affected source scope*.
No shared header, existing canonical object recipe or original
game-authored match row changed. An unfiltered 1,184-unit whole-graph
cold replay would not prove the still-NONEXACT parent and was not run.

Current accepted TH20 **game-authored exact coverage remains
498 whole original functions / 175,709 disjoint native bytes**;
canonical native units **1,184**, source-present function mappings
**1,183**, distinct compiler providers **243**. The original
3,735B Bullet emitter, 12,140B Bullet command dispatcher, 3,111B
Player frame, 555B Player movement, 41,967B Enemy ECL dispatcher
and 39,470B Animation VM remain independently unfinished game bosses.
