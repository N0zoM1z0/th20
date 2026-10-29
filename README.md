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

At the October 29, 2026 checkpoint the maintained graph has **1,181
source-present mappings**, **1,181 strict canonical native units** and
**241 canonical MSVC object/receipt providers**. Independently verified
game-authored whole-function exactness is **455 complete functions /
154,558 original native bytes**. These are dated values, not a
whole-game buildability or playable-game claim: always run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`
for the live inventory and consult the
[current concise handoff](docs/RE_HANDOFF.md) for the unfinished bosses.

| Area | Current position |
| --- | --- |
| Target and analysis | Locked Japanese Steamless target and attested Ghidra 12.1.3 |
| Reference review | All 6,945 indexed implementations and 113 parser-gap files reviewed |
| ECL Runtime | Whole tick, call/frame/argument and lifetime protocols; [evidence](docs/EXACT_ECL_TICK_RECONSTRUCTION.md) |
| Animation | Lifetime, child links, script/frame geometry and operands; 17 newly [origin-reviewed native-exact gameplay methods](docs/ANIMATION_FRAME_5527_EXACT_ORIGIN_AUDIT.md) add 5,527B, while the 39,470B VM parent is open; [source map](docs/SOURCE_MAP.md) |
| Enemy | Actual owners and [whole defeat](docs/ENEMY_DEFEAT_RECONSTRUCTION.md); private whole opcode draft remains machine-code nonexact; [layout](docs/CORE_ENEMY_DISPATCH_LAYOUT.md) |
| Gameplay cores | Scheduler, hit ownership, Player/SHT, Bomb and Item protocols; the complete 3,111B [Player main-frame C++ frontier](docs/PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md) is source-present but NONEXACT; four directly called 120B [original game leafs are now strict exact](docs/PLAYER_FRAME_LEAF_120_EXACT_RECONSTRUCTION.md) |
| Archive and Progress | Actual codec/resource/file pipelines and serialization; remaining whole nonexact functions recorded in ledgers |
| Collision geometry | **19 complete original whole-function** geometry predicates, including 1,452B rectangle/rectangle and 1,439B line/rectangle bosses, now independently [origin-reviewed and strictly exact](docs/GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md); **13,360B disjoint authored credit** |
| Input devices | Complete 3,490B [keyboard/DirectInput/XInput poll](docs/INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md) strict exact; [corrected signed InputInf selector ABI](docs/INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md) from three original callers; game link/runtime remain open |
| Interpolation gameplay | Ten complete [interpolation bosses and evaluators](docs/INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md) add 8,571 native exact bytes, including 1,489B IntegerTriple, 1,129B Vector3, 1,074B Fog and independent ECL/Animation/Enemy/Bullet whole callers |
| Direct animation script and VM forward | Original 338B [AnimationFile script loader and 21B Renderer VM forwarding wrapper](docs/ANIMATION_DIRECT_SCRIPT_359_EXACT_RECONSTRUCTION.md) both whole **strict exact**; fixes the real Bullet emitter original call target; 39,470B VM remains open, 61 original source providers/266 old units preserved |
| Animation pool allocation boss | Complete native **298B/78-instruction** [Renderer Animation pool allocation and reuse](docs/ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) now **298/298 strict exact**, original 14 E8 and 2 HIGHLOW fields; genuine 0x600 PooledAnimation slots and physically folded typed front/detach/initialize helpers, no duplicate bytes |
| Bullet emitter boss | The original **3,735B/935-instruction** Bullet emitter now has [complete maintained C++20 source](docs/BULLET_EMITTER_3735_MAINTAINED_SOURCE_FRONTIER.md), 13+11 native switch cases and correct shared_ptr metadata ownership; native source remains NONEXACT (3,516B emitted body), all 91 shared-header exact units protected |
| Bullet command-11 | The entire **1,404B** original Bullet edge-ray state machine is now [whole canonical native exact](docs/BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md), with 33 original E8/35 PE HIGHLOW positions and a real typed 89B Vector2 polar linker-folded alias (no duplicate credit); 12,140B controller dispatcher and 3,735B emitter remain open |
| Graphics and sound | Maintained mesh/lifecycle and sound loading; Renderer and full runtime ownership remain open |
| HUD and text | Complete FrontInf, AsciiInf and [Dialogue construction/destruction/follow-box protocol](docs/DIALOGUE_OWNER_RECONSTRUCTION.md); native resource lifetime and frame execution remain open |
| Whole-program build and runtime | Not yet available |

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
- [Guarded artifact retirement and storage audit](docs/ARTIFACT_RETIREMENT_2026_10_29.md)
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
