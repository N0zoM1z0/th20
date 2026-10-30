# 東方錦上京 ～ Fossilized Wonders.

<p align="center">
  <img
    src="resources/title-screen.png"
    width="640"
    alt="Original Japanese TH20 title screen">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="TH20 exact source reconstruction progress">
</p>

Source reconstruction of the original Japanese TH20 v1.00a **Steamless**
executable. Function-level exactness requires reproducible comparison against
one hash-attested target. The workflow follows [TH095](https://github.com/N0zoM1z0/th095),
with Ghidra and a separate modern MSVC environment for TH20.

> [!IMPORTANT]
> Reconstruction is in progress. Verified source components and exact function
> comparisons are available; the repository does not yet build a playable game.
> Origin review, source presence, exactness, linkage and runtime behavior are
> separate statuses.

## Exact target

Supply your own executable as `resources/th20.exe`:

| Property | Required value |
| --- | --- |
| Version | Japanese 1.00a, user-selected Steamless variant |
| Embedded title/replay label | 1.00c; recorded separately from registry/package identification |
| Size | `1,858,560` bytes |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| MD5 | `e7ccdbd2f319ba868ce386e484fff1d3` |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |

```bash
scripts/import-target.sh /path/to/th20.exe
scripts/repo-python scripts/verify-target.py
```

The Steam-original backup is retained locally as provenance evidence. Its
code differs from the comparison target. See [target provenance](docs/TARGET_PROVENANCE.md)
for official Japanese release and independent executable identification.
Game executables, assets, private databases, toolchains and reference checkouts
are excluded from Git.

## Repository status

At the October 30, 2026 checkpoint the maintained graph has **1,239
source-present mappings**, **1,240 strict canonical native units** and
**260 canonical MSVC object/receipt providers**. Independently verified
game-authored whole-function exactness is **590 complete functions /
196,671 original native bytes**. These are dated values, not a
whole-game buildability or playable-game claim: always run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`
for the live inventory and consult the
[current concise handoff](docs/RE_HANDOFF.md) for the unfinished bosses.

| Area | Verified current state |
| --- | --- |
| Large game-original exact bodies | [11,110B ECL Runtime tick](docs/EXACT_ECL_TICK_RECONSTRUCTION.md), [3,735B Bullet emitter /3,832B complete compiler extent](docs/BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md), [3,490B InputDevice poll](docs/INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md), [456B Animation handle resolver](docs/ANIMATION_POOL_RESOLVER_456_STRICT_EXACT_RECONSTRUCTION.md), [1,404B Bullet command-11](docs/BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md), [1,036B LZSS compressor](docs/ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md) and [73B Animation factory](docs/ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md) are **whole native strict exact**. |
| Source-present, **NONEXACT** | [3,111B Player main](docs/PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [555B Player movement](docs/PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md), [273B Bullet draw group](docs/BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md), and [1,649B Enemy mesh](docs/ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). Compiler, stack and ABI/codegen differences remain. |
| Other giant original bosses, **NONEXACT** (Animation draw source-present; Bullet command, Enemy ECL and Animation VM source-absent; quad submission is separately whole exact) | [12,140B Bullet command processor](docs/ANIMATION_RETIRE_SUBTREE_362_EXACT_RECONSTRUCTION.md), [5,993B Animation Draw Boss with original 49+31 pointer tables and recovered native backend ABI, still NONEXACT](docs/ANIMATION_DRAW_BOSS_5993_NATIVE_80_TABLE_ABI_FRONTIER.md), [41,967B Enemy ECL dispatcher](docs/ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md) and **39,470B Animation VM**. Exact children do not close these parent bodies. |
| Bullet command call graph | Entire original 12,140B has **210 original native E8 calls, 208 with fully strict-canonical source targets and two compiler-runtime-only outstanding**. Seven new Animation methods in two batches add 447 whole native original bytes, but the parent remains NONEXACT. The [three original switch tables](docs/BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md) contain **53 genuine PE HIGHLOW code pointers**. |
| Renderer/Animation draw (whole strict bosses vs nonexact dispatcher) | **Whole-native strict exact:** [3,159B quad submission with its 3,180B code/table extent](docs/ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md); [2,725B ten-mode D3D9 texture/sampler boss](docs/ANIMATION_QUAD_TEXTURE_STATES_2725_STRICT_EXACT.md) including its ten-case PE table; [1,163B four-mode blend-state boss](docs/ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md) including its four-way PE table; [352B batch append +26B forwarding wrapper](docs/ANIMATION_QUAD_BATCH_APPEND_352_AND_TEXTURE_PREPARE_26_EXACT.md); [60B game texture lookup and 34B+16B checked STL helpers](docs/ANIMATION_TEXTURE_LOOKUP_60_STL_ARRAY_34_16_EXACT.md), with library bytes excluded from game credit; [192B D3D9 batch flush](docs/ANIMATION_DRAW_QUEUE_FLUSH_192_STRICT_EXACT_RECONSTRUCTION.md); [five quad drawing mode wrappers](docs/ANIMATION_DRAW_MODE4_48_MODE5_142_STRICT_EXACT.md) and [three 92B Graphics state-cache transitions](docs/GRAPHICS_DRAW_RENDERSTATES_276_STRICT_EXACT_RECONSTRUCTION.md). **Still NONEXACT:** [5,993B draw dispatcher with original 80 case pointers and all 123 ordered E8 targets, still NONEXACT](docs/ANIMATION_DRAW_BOSS_5993_NATIVE_80_TABLE_ABI_FRONTIER.md). Original source-role counts do not establish machine-code exactness. |
| Renderer rounding library leaf | [20B standard C++ `round(float)` overload at `0x00445B80`](docs/ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md) now whole **20/20B strict exact**, naturally emitted with the 3,159B quad Boss from a shared `/fp:strict` source provider. The wrapper forwards to native CRT `_roundf` and is **excluded** from authored game byte/function credit. |
| Typed gameplay and native library source | [199B Bullet interpolation game methods](docs/BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md), [Animation/Player/ECL game methods](docs/GAME_PLAYER_ANIMATION_ECL_SEVEN_ORIGINAL_1283_EXACT_ORIGIN.md), [Laser lifetimes](docs/LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md), [geometry and value methods](docs/GAME_FOG_GEOMETRY_PLAYER_PBG_SESSION_1686_ORIGIN.md). Separate [PMR vector STL](docs/BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md) and [shared_ptr STL](docs/BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md) code is **library-excluded**, not additional game-authored exact credit. |
| Original game data | [72B signed 9x2 Player movement direction table](docs/PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md) is exact original .rdata and real maintained C++; **not** counted as authored .text. |
| Whole-program link or playability | **Not yet available.** Strict mapping, provenance, game-origin credit and executable runtime are distinct. |

[Generated progress](docs/PROGRESS.md) and the status reporter provide live
authored totals. [The current handoff](docs/RE_HANDOFF.md) records remaining work
and local verification; [the evidence index](docs/EVIDENCE_INDEX.md) routes dated
investigations without mixing historical counts into current status.

The pinned toolchain candidate is MSVC 19.44.35211 x86, Windows SDK 10.0.26100.0
and D3DX 9.29.952.8. Accepted units use explicit per-source profiles. These results
do not establish executable-wide compiler flags, SDK or CRT identity.

## Build and verify

Documentation and artifact-cleanup handoffs use diff/link checks and protected
product hashes. An unchanged native compiler-input graph needs no replay,
compiler, Ghidra or full CI run. Shared-header text edits can invalidate
pinned compiler receipt hashes: replay only the actual pre-edit receipt include
closure in that case. Use the `gpt-web:` commit prefix.

When code or infrastructure changes warrant broader checks, public CI needs
Python 3.11+, with no original game or C++ compiler:

```bash
scripts/repo-python scripts/ci.py
```

Default CI checks the exact oracle and repository metadata. The historical
portable C++ semantic suite has been retired; [retained tests](tests/README.md)
cover exact comparison and repository tools. Exact checkpoints require affected
native builds and complete strict replay. A specific unresolved behavior or ABI
question can use a temporary probe under `.analysis/`.

Private preflight for reconstruction changes is:

```bash
scripts/bootstrap-tools.sh
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

On a fresh private workspace, provision tools as described in
[Tools](docs/TOOLS.md), then run `scripts/repo-python scripts/ghidra.py import` once.
Every query re-attests the executable and complete mapped code section;
inventory refreshes never overwrite reviewed ledgers.
For source changes, derive the actual affected providers from captured include
closures and manifest dependencies. Build and replay only those units, with
individual unit commands or explicit `--source` filters. New exact acceptance
requires affected cold builds; see [build and matching](docs/BUILD_MATCHING.md).

## Reference review

[Oracatt/Touhou20](https://github.com/Oracatt/Touhou20) is pinned locally under
ignored `_reference/Touhou20`. Its target hash matches ours. Its v1.00c label
comes from embedded strings; our v1.00a identification follows the independent
hash registry and supplied package. Both observations are preserved in provenance.

The [review](docs/REFERENCE_REVIEW.md) records the repository-wide evidence audit,
module dispositions, stale reports and independently verified absorption.
Validated source diagnostics route further analysis; reference source, build
layout and completion claims are not imported wholesale.

The [function-by-function review](docs/REFERENCE_FUNCTION_REVIEW.md) is complete
for all 6,945 indexed implementations, including one parser omission recovered
during manual review. All 113 parser-gap files are manually reconciled. The
[final audit](docs/REFERENCE_SUPPORT_REVIEW.md) records coverage and evidence
limits; nonexact implementations remain documented for further reconstruction.

## Documentation

- [Current handoff](docs/RE_HANDOFF.md)
- [Focused evidence index](docs/EVIDENCE_INDEX.md)
- [Architecture and target inventory](docs/ARCHITECTURE.md)
- [Reconstruction workflow](docs/RE_WORKFLOW.md)
- [Latest source/document cleanup and protected storage audit](docs/MAINTENANCE_STORAGE_2026_10_30.md)
- [Historical CORE628 artifact-retirement checkpoint](docs/ARTIFACT_RETIREMENT_CORE628.md)
- [Independent oracles](docs/ORACLES.md)
- [Build and strict matching](docs/BUILD_MATCHING.md)
- [Ghidra setup and attestation](docs/GHIDRA.md)
- [Tool routing](docs/TOOLS.md)
- [Source ownership](docs/SOURCE_MAP.md)
- [Semantic reconstruction policy](docs/SEMANTIC_RECONSTRUCTION.md)
- [Reference review](docs/REFERENCE_REVIEW.md)
- [Function-by-function reference review](docs/REFERENCE_FUNCTION_REVIEW.md)
- [Complete reference review and final tooling batch](docs/REFERENCE_SUPPORT_REVIEW.md)
- [Enemy movement, spawn and variable review](docs/REFERENCE_ENEMY_MOVEMENT_REVIEW.md)
- [Runtime invincibility launcher](docs/RUNTIME_PATCH.md)
- [Verified knowledge base](docs/KNOWLEDGE_BASE.md)
- [Roadmap](docs/ROADMAP.md)
- [Generated progress](docs/PROGRESS.md)
- [Agent rules](AGENTS.md)

## Credits

- [Oracatt/Touhou20](https://github.com/Oracatt/Touhou20): reference
  reconstruction, source diagnostics and behavioral investigations that guide
  our independent, function-by-function review.
- [N0zoM1z0/th095](https://github.com/N0zoM1z0/th095): reconstruction workflow,
  exact-oracle control plane, tracking conventions and README/progress layout.

## License

[MIT](LICENSE) for this repository's original code and TH095-derived control
plane. It grants no rights to the original game, downloaded tools or external
reference material. Maintained prose and commit messages are in English;
official names and original target evidence retain their original language.
