# CORE/RECON-624 — native x87 RNG and trigonometric return lifetimes in the full 3,735-byte Bullet emitter

Original executable: Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The full original game-owned `BulletController::emit()` at
`0x004818E0` remains NONEXACT.** The entire immutable original contains
**3,735 machine-code bytes / 935 native x86 instructions**, 60 original
E8 direct calls and 69 actual PE HIGHLOW relocations in its complete
3,832-byte compiler contribution. After recovering natural C++
x87-to-float lifetime in three RNG pattern branches and two game
trigonometric operands, the maintained `src/BulletEmitter.cpp`
compiles to **3,736 bytes / 936 x86 instructions, 934/935 native
mnemonic heads aligned in order** (up from 928/935). The whole C++
contribution remains **3,832 bytes**, all **60/60 original physical
callee identities** still agree in original ordinal order, and the
69 candidate DIR32 relocations agree with original PE by **count**.
None of these partial equivalences implies strict native byte equality.

## Six immutable original x87 return / parameter-read / SSE reload chains

Independently decoding every instruction of the original complete
3,735B PE body exposes **six** consecutive three-instruction chains:

| Original method-relative x87 `fstp` | Original shot pointer `mov` | Original float `movss` |
| --- | --- | --- |
| `+0x357` | `+0x35A` | `+0x35D` |
| `+0x389` | `+0x38C` | `+0x38F` |
| `+0x40C` | `+0x40F` | `+0x412` |
| `+0x439` | `+0x43C` | `+0x43F` |
| `+0x612` | `+0x615` | `+0x618` |
| `+0x63A` | `+0x63D` | `+0x640` |

At each chain, the original native x87 float return is first stored
to a 32-bit EBP stack local, then the game `ShotParameters*` is
reloaded from `[ebp+8]`, and **only then** the saved scalar is loaded
into SSE XMM0 before multiplying or adding a separate game field.
These are genuine original float dataflow/lifetime facts, not
compiler-size guesses. The native RNG E8s themselves were already
correct; the old maintained code fused RNG calls and `shot` member
arithmetic in one expression, reversing the independent post-call
source operand evaluation.

For native RNG modes **6, 7, and 8**, the source now uses typed
per-branch float locals: one signed-angle sample in mode 6; one
speed sample in mode 7; separate signed-angle and speed samples in
mode 8. The C++ blocks have genuine per-case local lifetimes and
capture real RNG return values before the original ShotParameters
member reads. Two complete original-game trigonometric returns in
mode **11**, `scalar_math::cosine(circle_angle)` and
`scalar_math::sine(circle_angle)`, likewise use one typed sampled
float each before multiplying real `shot.speed` and
`shot.speed_step` fields. Original custom geometry/math E8 targets,
IEEE scalar operations and Bullet owner types are preserved.

## Whole method compiler evidence, including rejected hypotheses

| Candidate full Bullet emitter source | Code bytes | x86 heads | Original aligned mnemonic heads |
| --- | ---: | ---: | ---: |
| Previously committed original mask/direct Player ABI | 3,736 | 936 | 928/935 |
| RNG branch 6 sampled locally | 3,736 | 936 | 929/935 |
| RNG branch 7 sampled locally | 3,736 | 936 | 929/935 |
| RNG branch 8 both samples local | 3,736 | 936 | 930/935 |
| All three real RNG branch cases | 3,736 | 936 | 932/935 |
| Also mode 11 cosine and sine sampled independently | **3,736** | **936** | **934/935** |

Original entire source compiler profile remains pinned MSVC
19.44.35211 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` for the noncanonical emitter.
There are **60 real CXX REL32 calls** and **69 CXX DIR32
fields**. After the newly maintained-source compile, a fresh
independent immutable PE audit confirms **60/60 actual original
callee identities in original order** with zero wrong and zero
unknown symbols, and the real eight-entry writable cancel-script
data array remains byte-for-byte **32/32 native bytes**.

The remaining mode 12 `scalar_math::absolute(scalar_math::sine(...))`
return is a distinct frontier. The immutable native game has the
`fstp [ebp-0x7c]` at method `+0x722`, then **`movss xmm0,[ebp-0x7c]`**
at `+0x725`, and *then* loads the `ShotParameters` pointer at
`+0x72A`. Current maintained ordinary C++ generates an opposite
member-load order for this final expression: a pointer `mov` before
the `movss`, giving a seventh compiled instance of the
`fstp -> parameter pointer mov -> SSE movss` sequence. It is **not
identical to the original sixth chain's ordering**. This is the
last residual mnemonic-order divergence; all 935 original mnemonic
heads can be made to align by adding a `const volatile float` local,
but immutable native code has **not** established the source variable
was actually volatile. Merely forcing compiler behavior with a
possibly invented volatile qualifier was rejected, as were
unnecessary extra stack locals that increase the method by 16–36
bytes. A correct original source/lifetime explanation remains to be
recovered before changing mode 12.

The **one current extra machine-code instruction** is a compiler
`nop` at `+0x112` after the second Timer setter. Under ordinary
pinned compiler settings the resulting native emitter candidate
is **3,736B/936 instructions**, one byte and one net instruction
more than original. Earlier private tests varied `/fp`, `/sdl`,
`/GS`, exception processing, local declaration locations, Timer
assignment syntax, and original row conditional forms. None gave
the original entire 3,735B/935 opcode and call/relocation pattern
without introducing other real differences. The physical E8
sites remain **11 identical offsets + 49 positions shifted by +1B**;
whole jump tables, EH and some native stack offsets remain nonexact.
No compiler-emitted `nop` was patched or suppressed artificially.

## Scoped verification and remaining work

Independent immutable PE vs fresh real maintained C++ evidence:

- `.analysis/core619-emitter-rng-x87-case-lifetime-results.json` — complete full-function per-case RNG source trials.
- `.analysis/core620-emitter-trig-stack-lifetime-results.json` — whole mode-11/12 cosine/sine/absolute source lifetime and branch cases.
- `.analysis/core621-emitter-abs-sine-expression-results.json` — rejection of artificial volatile and excess original-absent locals.
- `.analysis/core622-emitter-maintained-X87-score.json` — fresh entire maintained 3,736B/936 and 934/935 compiler result.
- `.analysis/core623-emitter-x87-60-native-call-proof.json` — real physical E8 callee identity census, 60/60 native original targets.
- `.analysis/core623-emitter-x87-color-pe-proof.json` — independent original `.data` and HIGHLOW/native target proof.
- `.analysis/core624-emitter-original-X87-lifetime-proof.json` — independent native six return/mov/movss groups and current seven compiled groups.

**Only `src/BulletEmitter.cpp` was modified**, preserving all
prior genuine game state and original mask fixes. No header, other
accepted C++ source, pinned canonical unit or original target was
changed. This nonexact source owns **zero accepted strict native
units**; only its complete C++ compiler object and immutable PE
reference/call evidence were checked. No full cold replay.

Authored game exact coverage remains **498 complete functions /
175,709 disjoint original native bytes**. Canonical native units
remain **1,184**, source-present mappings **1,183**, unique MSVC
providers **243**. The full 3,735B emitter, 12,140B Bullet
controller dispatcher, 3,111B Player main frame, 555B Player
movement, 41,967B Enemy ECL dispatcher and 39,470B Animation VM
remain independent unfinished whole original game bosses.
