# REF-001: reference review and verified absorption

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

This is the historical first-pass audit. The user's exhaustive implementation
review continues in [REF-002](REFERENCE_FUNCTION_REVIEW.md); module dispositions
below are not function-level completion. Current exact totals come from the
canonical ledgers and progress report.

## Scope and provenance

Reference: [Oracatt/Touhou20](https://github.com/Oracatt/Touhou20/tree/011aa029d1dac51578107bc98a0006bd750e453c),
commit `011aa029d1dac51578107bc98a0006bd750e453c`, tree
`dc2441727a7591a7c9560a5396fcf0744d17a865`. The clean checkout lives under
ignored `_reference/Touhou20`. No reference implementation, generated
decompilation or game resource was copied into our public tree.

The review scans every tracked file, examines build entry points and module
contracts, checks disassembly identity and report freshness, and independently
reconstructs selected components. It does **not** certify every reference C++
function, rerun every Windows oracle or establish whole-game equivalence.
Per-file hashes and raw findings are private; the module decision index is
`config/reference-review.csv`. Deferred implementations receive no credit.

The reference executable hash matches our locked target. Its v1.00c label is
supported by embedded title/replay strings. The independent hash registry and
supplied package identify that same file as v1.00a Steamless. Both labels are
recorded; no distinct updated v1.00c build is established. The early inference
that the reference label lacked target support was corrected before publication.
Locally supplied `custom.exe`, `th20.dat`, `thbgm.dat`, `readme.txt` and
`omake.txt` also match its source manifest. Its empty loose `st01.ecl` is absent
locally; this does not establish a missing shipped archive resource. Its
acquisition directory does not establish publisher provenance.

## Repository-wide evidence

`scripts/review-reference.py` refuses a different commit, dirty checkout or
comparison target. The sorted path/NUL/SHA256 inventory digest is
`a74d79ea16b0fa34f80f208784b05f5351ebe1e0730ef506f05753f219f9aca2`.

| Observation | Count |
| --- | ---: |
| Tracked files read and hashed | 10,822 |
| Content bytes | 114,038,724 |
| Generated Ghidra pseudocode files | 6,928 |
| C++ implementation/test files | 529 |
| C++ headers | 254 |
| Disassembly evidence files | 1,629 |
| Byte-bearing disassembly files checked | 1,627 |
| Matching instruction rows | 648,476 |
| Mismatching byte-bearing rows | 0 |
| JSON path-key/SHA256 bindings checked | 8,434 |
| Stale bindings | 401, involving 50 distinct files |

The 2,156,872 compared disassembly bytes include overlapping/repeated exports;
they are not unique code coverage. One evidence file is empty
(`platform_window/evidence/040ba8b0.asm`); Replay `00508f70.asm` has instruction
text without bytes. Neither is silently treated as byte-verified. Replay
0x00508F70 is also absent from our current function inventory and requires a
separate control-flow/boundary investigation.

The `.asm` files are documentary disassembly, with zero `.asm` mentions in
CMake inputs. The recovery has substantial production C++, rather than an
assembly-backed game. Inline assembly and executable-memory facilities occur
in isolated CPU tests and historical image-mapping code. Those facilities are
not production imports under our policy. Lexical counts include comments and
do not establish linkage or behavior.

Stale bindings appear in the recovery registries, build snapshots and selected
module reports, including item, pause, special-state, small-score, stone-menu,
text, startup, progress, window, title and effect records. Private
`bindings.json` retains each report, source, expected hash and observed hash.
401 counts references, not 401 failed runtime tests. A current hash alone does
not prove correct report/binary/scenario binding.

Older coverage/README records describe incomplete linkage; the newer root README
describes a playable source build. Their scopes and dates differ and neither
status transfers to ours. Root CMake builds inspection tools/native components;
the game uses the separate `source_reconstruction` closure and explicit targets.
Do not mistake the root build for the game.

## Build and behavioral-oracle assessment

The reference's VS2019/14.29, SDK 10.0.19041 and C++17/20 environment differs
from our locked 19.44.35211 candidate. Its `/fp:strict`, static CRT and SSE2
profiles are behavioral choices, not proof of target-wide options. It has no
canonical COFF/relocation exact replay comparable to ours.

Several CPU fixtures execute unmodified selected original bodies; others
redirect external functions or share native services between both sides.
Reports normalize known object/vtable/allocation addresses, restrict input
domains, or omit failing CRT/uninitialized-runtime cases. Rendering evidence
ranges from COM traces to actual D3D pixel comparisons. Resource byte round
trips, source-only assertions and runtime screenshots are distinct classes.
Shared oracle counts overlap and cannot be summed into completion.

Many production owners append service pointers, replace allocators/locks or
change malformed-input behavior. These designs inform semantics but cannot
be transplanted as exact target layouts. Padding, callback ABI, unique global
ownership and initialization need their own evidence and compiler probes.

The reference's portable root tools build successfully with GCC 13 and their
binary-parser CTest passes. The archive library and its CTest also pass. Its
verifier fails to link on Linux because it supplies Windows `wmain`; this
platform limit is not an archive-algorithm failure. Neither test validates the
Win32 game closure. Logs remain under `.analysis/reference-review/`.

## Accepted routing evidence

`config/source-diagnostics.csv` records 153 independently checked sites in 124
candidate functions. Every accepted row requires a matching retained CP932
string, a fresh attested Ghidra string-reference pair, a containing inventoried
function and independently decoded Capstone immediate at the claimed instruction.

Two reference rows without containing functions are rejected and retained in
private `rejected-diagnostics.json`. These are routing evidence only. They do
not rename functions, classify all owners, import source or earn exact credit.

## Maintained components

| Target | Our implementation | Full comparator result | Authored credit |
| --- | --- | --- | --- |
| 0x00422CB0, 133 bytes | `th20::random_step` | Exact, including helper relocation | Excluded: MSVC STL |
| 0x004235F0, 35 bytes | `th20::RandomState::next` | Exact, including transition relocation | Excluded: MSVC STL |
| 0x00423F50, 41 bytes | `th20::Timer::reset` | Exact, every byte | 41 bytes |
| 0x00423F80, 90 bytes | `th20::Timer::set` | Exact, both call relocations | 90 bytes |
| 0x00423FE0, 38 bytes | `th20::Timer::set_mode` | Three register-encoding differences | None |

These are independently maintained bodies derived from our attested target,
using the reference as a lead. They contain no assembly, copied decompiler,
byte array, profile-selected body, inert local or artificial return.

RNG constants/folding and state-update patterns match the installed MSVC
`<random>` minstd_rand implementation: `_Next_linear_congruential_value` and
`linear_congruential_engine::operator()`. This corroborates **library** origin;
the reference's game-component label does not become authored credit. Our
four-byte RandomState is the engine subobject, not the 28-byte enclosing game
RNG. Seed normalization, distribution and locking remain separate.

Reset writes current=0, previous=-999999 and positive float zero, preserving
flags. Mode replaces only bits 1..2. Set initializes iff bit 0 is clear, then
writes integer/float values and wrapping previous. Natural void declarations
reproduce reset/set bytes; incidental EAX=self does not justify fluent return
semantics. Delta/tick and global clock protocols remain open.

Relocation anchors come from separately reviewed target bodies, Ghidra
callers/callees and semantic identities. The complete 31-byte helper at
0x00542E90 implements EDX:EAX unsigned shift by CL and is excluded as CRT.
Reset/mode are reviewed separately from Set's relocation fields. No
comparator-solved destination was promoted as independent anchor evidence.

Cold replay uses one profile per source: MSVC x86 C++20 with
`/Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise`. Four units compare complete COFF
contributions. Authored progress counts only two Timer matches, 131 bytes.
Portable tests use a division-based RNG oracle, known sequence values and Timer
state invariants with undefined-behavior sanitization. They cover full-word RNG
samples, integer extremes, flag preservation and float conversion boundaries.

## Decisions and next families

Every reference module has a disposition in `reference-review.csv`. Generated
pseudocode/disassembly remain local evidence. Historical patched-game launchers,
service-suffixed layouts, build topology and completion percentages are rejected
as production imports. Script/resource tools are investigation candidates;
assets and decompiled resource scripts are not distributed.

Next families: close Timer clock/rounding and enclosing RNG ownership, then
FunctionChain observer/dispatch contracts, archive dictionary ownership, Input
transitions and ECL/ANM contracts. Renderer, entities, menus, audio, save/replay
and global constructors need bounded owner/ABI and runtime reviews. Deferred
modules have no source-present or exact credit in our project.

## Reproduction

```bash
git clone https://github.com/Oracatt/Touhou20 _reference/Touhou20
git -C _reference/Touhou20 checkout 011aa029d1dac51578107bc98a0006bd750e453c
scripts/repo-python scripts/review-reference.py
scripts/repo-python scripts/ghidra.py architecture
scripts/repo-python scripts/import-reference-leads.py --check
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

LeanToken supported initial indexed discovery. After moving the checkout under
`.gitignore`, it was not indexed; remaining reference contracts used bounded
native reads. This retrieval limitation does not change target attestation.
