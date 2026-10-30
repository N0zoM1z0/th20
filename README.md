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

At the October 30, 2026 checkpoint the maintained graph has **1,389
source-present mappings**, **1,389 strict canonical native units** and
**350 canonical MSVC object/receipt providers**. Independently verified
game-authored whole-function exactness is **670 complete functions /
241,394 original native bytes**. These are dated values, not a
whole-game buildability or playable-game claim: always run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`
for the live inventory and consult the
[current concise handoff](docs/RE_HANDOFF.md) for the unfinished bosses.

| Area | Verified live state and detailed evidence |
| --- | --- |
| **Large exact game functions** | Original [11,110B ECL runtime tick](docs/EXACT_ECL_TICK_RECONSTRUCTION.md), [3,735B Bullet emitter](docs/BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md), [3,490B InputDevice polling](docs/INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md), and other accepted whole bodies; the complete physical credit is in [`config/matches.csv`](config/matches.csv). |
| **Animation quad-submit Boss** | Original **3,159B body /3,180B complete relocated contribution** [strict exact](docs/ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md). Its separate [20B standard `round(float)` header wrapper](docs/ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md) is strict exact but **library**, not authored game code. |
| **Animation rendering backends** | Original **4,347B Mode8**, **2,769B Mode6**, **1,378B Mode6 setup**, **1,996B Mode7 setup**, **753B Mode7**, and **2,136B mesh24/25** each independently whole strict exact. [Mode8](docs/ANIMATION_DRAW_MODE8_4347_STRICT_EXACT.md), [Mode6](docs/ANIMATION_DRAW_MODE6_2769_STRICT_EXACT.md), [Mode6 setup](docs/ANIMATION_DRAW_MODE6_SETUP_1378_STRICT_EXACT.md), [Mode7 setup](docs/ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md), [mesh](docs/ANIMATION_DRAW_MESH2425_2136_STRICT_EXACT.md). Their enclosing **5,993B Draw dispatcher remains NONEXACT**. |
| **Animation geometry Bosses** | Independently exact **2,169B closed line, 1,980B rectangle, 1,601B triangle, 1,468B ring**, and many 375B–1,174B fan/ellipse/strip renderers. [Source-native proof index](docs/EVIDENCE_INDEX.md) supplies the individual original heads and relocation roles; exact children do **not** complete the 5,993B Draw dispatcher. |
| **Separate ribbon Motion-group pipeline** | Separate native **538B segment dynamics Boss**, **140B group update**, **156B draw**, **76B LINESTRIP wrapper**, **89B polymorphic ctor**, **60B segment ctor** and **47B allocation/config wrapper** are independently whole strict exact game-authored functions. Their **78B triple-array ctor**, **156B diagnostic allocation factory**, **20B/49B destructor pair**, **two 19B radius/point ends** and **19B group array-end** are whole native exact with unresolved compiler/template or source ownership, hence not duplicate authored credit. Three 0x3C0-byte segments and the pointer-bearing +0xB5C member preserve real native vtable/auto-zero ABI. The separate **252B ribbon configuration Boss**, its **23B segment-array index**, and the **88B palette with two 31B forwarding helpers**, plus the **75B ribbon 60-color array constructor**, are independently whole strict exact; the whole game does not link or play. [538B dynamics](docs/ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md), [89B/20B/49B ctor and deletion](docs/ANIMATION_RIBBON_GROUP_CTOR_89_STRICT_EXACT.md), [78B array](docs/ANIMATION_RIBBON_SEGMENT_ARRAY_CTOR_78_STRICT_EXACT.md), [156B factory](docs/ANIMATION_RIBBON_GROUP_FACTORY_156_STRICT_EXACT.md), [47B wrapper](docs/ANIMATION_RIBBON_CONFIG_WRAPPER_47_STRICT_EXACT.md), [252B configuration](docs/ANIMATION_RIBBON_GROUP_CONFIG_252_STRICT_EXACT.md), [88B palette and 31B forwarding](docs/ANIMATION_RIBBON_PALETTE_88_31_STRICT_EXACT.md), [75B color array](docs/ANIMATION_RIBBON_COLOR_ARRAY_75_STRICT_EXACT.md), [23B index](docs/ANIMATION_RIBBON_SEGMENT_AT23_STRICT_EXACT.md), [140B update](docs/ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md), [156B draw](docs/ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md), [76B renderer](docs/ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md). |
| **64-point ribbon trail object** | Original **103B polymorphic ctor and 49B scalar deletion** independently whole strict exact under one 0x320-byte native class at original vtable 0x56ED1C. The **520B update Boss is now whole strict exact**, and **165B draw Boss is also whole strict exact**, and **340B gray configuration now also whole strict exact**; **382B magenta alternate configuration is now also whole strict exact**. [103B ctor/49B delete](docs/ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md), [520B update Boss](docs/ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md), [165B draw](docs/ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md), [156B factory](docs/ANIMATION_RIBBON_TRAIL_FACTORY156_STRICT_EXACT.md), [340B gray config](docs/ANIMATION_RIBBON_TRAIL_GRAY340_STRICT_EXACT.md), [382B magenta config](docs/ANIMATION_RIBBON_TRAIL_PINK382_STRICT_EXACT.md), [47B/49B entry wrappers](docs/ANIMATION_RIBBON_TRAIL_WRAPPERS_47_49_STRICT_EXACT.md), [75B color-array ctor](docs/ANIMATION_RIBBON_TRAIL_COLOR_ARRAY75_STRICT_EXACT.md). |
| **Separate one-segment ribbon pipeline** | Original **140B virtual update, 156B virtual draw** and **19B one-past-end pointer** all whole strict exact at separate 0x56ECA4 polymorphic vtable; original 697B segment dynamics and 76B renderer are now independently whole exact. Separately, original **123B packed-color and 202B float `std::fill_n`** C++20 bodies are whole strict exact with real unsigned `jbe` branching, **not authored game credit**. [140B/19B proof](docs/ANIMATION_RIBBON_SOLO_UPDATE_140_END19_STRICT_EXACT.md), [89B ctor and 49B delete](docs/ANIMATION_RIBBON_SOLO_GROUP_CTOR_89_DELETE_49_STRICT_EXACT.md), [156B solo factory](docs/ANIMATION_RIBBON_SOLO_FACTORY_156_STRICT_EXACT.md), [47B solo wrapper](docs/ANIMATION_RIBBON_SOLO_WRAPPER_47_STRICT_EXACT.md), [182B solo configuration](docs/ANIMATION_RIBBON_SOLO_CONFIG_182_STRICT_EXACT.md), [123B solo palette](docs/ANIMATION_RIBBON_SOLO_PALETTE_123_STRICT_EXACT.md), [156B draw proof](docs/ANIMATION_RIBBON_SOLO_DRAW_156_STRICT_EXACT.md), [76B fan](docs/ANIMATION_RIBBON_SOLO_FAN_76_STRICT_EXACT.md), [697B dynamics Boss](docs/ANIMATION_RIBBON_SOLO_DYNAMICS_697_STRICT_EXACT.md), [123B/202B library proof](docs/ANIMATION_RIBBON_FILL_N_123_202_STRICT_EXACT.md). |
| **Polygon stroke and group pipeline** | Whole strict exact **1,204B polygon outline**, **827B dynamics Boss**, **60B segment ctor**, **296B configuration**, **233B group draw**, **140B timer tick**, **120B palette**, **76B fan wrapper**, and **47B configuration wrapper**. [Outline](docs/ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md), [group](docs/ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md), [tick/827B frontier](docs/ANIMATION_POLYGON_DYNAMICS_827_TICK140_ITERATORS_STRICT_FRONTIER.md), [palette](docs/ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md). The **827B segment updater is now whole strict exact**, including both `std::views::drop(1)` loops and original 62/61 array sizes. [Whole native proof](docs/ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md). The original **60B segment ctor** and its 75B 4-byte-cell array ctor are now strict exact; [construction and genuine padding evidence](docs/ANIMATION_POLYGON_SEGMENT_CONSTRUCTION_60_75_NATIVE_EXACT.md). The enclosing **113B group constructor** and its **78B three-segment array constructor are now whole strict exact**. [Array native proof](docs/ANIMATION_POLYGON_SEGMENT_ARRAY_78_STRICT_EXACT.md). [Inheritance/ABI frontier](docs/ANIMATION_POLYGON_GROUP_CTOR_113_ARRAY_78_FRONTIER.md). The generated **49B group scalar-deleting wrapper is also strict exact** (compiler code, not authored credit); its ordinary 20B physical destructor was later matched by the genuine ribbon-group folded destructor chain (original polygon-specific source owner still unresolved). [Complete 113B/49B proof](docs/ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md). The separate **104B outline wrapper remains NONEXACT**. The previously missing **156B C++17 group allocation factory is now whole strict exact** but counted as an origin-unverified template, not authored game bytes. [Factory proof](docs/ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md). |
| **Compiler/STL-like exact helpers** | Seven polygon counted-range leaves, four strict 16B/93B C++20 drop-view helpers, **27 more entire 17B–48B C++20 polygon-range helpers**, two 31B palette tag wrappers and two 23B/19B array access helpers are **whole native strict exact**, but their original authorship is unproven and they are **excluded from authored game totals**. [27-function range-closure proof](docs/ANIMATION_POLYGON_DROP_CLOSURE_27_STRICT_EXACT.md). |
| **202B original Vector3 normalized geometry** | Whole **202B/58-i386** three-component vector normalization/copy exact, two native E8 and real 0.01f epsilon HIGHLOW; **+202 authored game bytes**. [Original full proof](docs/ANIMATION_PARTICLE_NORMALIZE202_STRICT_EXACT.md). |
| **200-particle polymorphic native group constructor** | Whole **172B/46-i386** original game ctor and **49B/18-i386** generated deleting wrapper now strict exact under one real **0x1940-byte** class with two 200-element Vector3 arrays. Original `0x56EC14` vtable and all 9 ctor E8/1 HIGHLOW independently audited. **+172 authored-game bytes**; generated wrappers uncredited. [Whole original proof](docs/ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md), [156B C++17 factory](docs/ANIMATION_PARTICLE_GRID_FACTORY156_STRICT_EXACT.md), [47B create/31B configuration](docs/ANIMATION_PARTICLE_GRID_CREATE47_CONFIG31_STRICT_EXACT.md), [92B virtual stop](docs/ANIMATION_PARTICLE_GRID_STOP92_STRICT_EXACT.md). |
| **1,486B rotated sprite corner Boss now whole exact** | **1,486/1,486 original x86 exact** with all 13 E8, nine native HIGHLOW and an authentic compiler-emitted `+0x41` NOP from the post-Angle lexical scope. The separately exact 985B corner sibling remains unchanged. [Complete strict proof](docs/ANIMATION_CORNER_ROTATED_1486_STRICT_EXACT.md). |
| **Source-present, NONEXACT parents** | Original [5,993B Animation Draw](docs/ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md), [104B polygon wrapper](docs/ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md), [3,111B Player main](docs/PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), and [555B Player movement](docs/PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **Source-absent large parents** | Original [12,140B Bullet extended command](docs/BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md), [41,967B Enemy ECL opcode dispatcher](docs/ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md), and **39,470B Animation VM update**. Their exact callees are not parent-body credit. |
| **Exact original `.rdata`** | The **96B 2×3×4 quad corner table**, **8B polygon widths (16.0f/32.0f)** and **72B Player direction table** each have attested original data bytes; **none** increases game `.text` coverage. [Corner table](docs/ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md), [polygon scalars](docs/ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md), [Player data](docs/PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |
| **Whole-program result** | **Not linked or playable yet.** Source mapping, canonical strict acceptance, original authorship credit, static data and runtime integration are different claims. |

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
