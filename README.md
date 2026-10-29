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

At the October 29, 2026 checkpoint the maintained graph has **1,201
source-present mappings**, **1,203 strict canonical native units** and
**245 canonical MSVC object/receipt providers**. Independently verified
game-authored whole-function exactness is **556 complete functions /
186,645 original native bytes**. These are dated values, not a
whole-game buildability or playable-game claim: always run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`
for the live inventory and consult the
[current concise handoff](docs/RE_HANDOFF.md) for the unfinished bosses.

| Area | Current position |
| --- | --- |
| Target and analysis | Locked Japanese Steamless target and attested Ghidra 12.1.3 |
| Reference review | All 6,945 indexed implementations and 113 parser-gap files reviewed |
| ECL Runtime | Whole original 11,110B ECL tick plus **21 full game-owned [ECL, Bullet, Animation, constructors and Archive](docs/ECL_BULLET_ANIMATION_6836_EXACT_ORIGIN_AUDIT.md)** add 6,836 disjoint native exact bytes; 41,967B Enemy ECL dispatcher remains NONEXACT; **12 complete original ECL argument/tagged ScriptStack methods, 2,073 disjoint strict bytes** independently [game-origin reviewed](docs/ECL_ARGUMENT_TAGGED_STACK_2073_ORIGINAL_GAME_EXACT_ORIGIN.md), with the original exact 11,110B Runtime / 923B invocation call graph; [whole runtime tick](docs/EXACT_ECL_TICK_RECONSTRUCTION.md) |
| Animation | Lifetime, child links, script/frame geometry and operands; 17 newly [origin-reviewed native-exact gameplay methods](docs/ANIMATION_FRAME_5527_EXACT_ORIGIN_AUDIT.md) add 5,527B, while the 39,470B VM parent is open; [source map](docs/SOURCE_MAP.md) |
| Enemy | Whole defeat plus **ten complete 416–967B Enemy/Motion gameplay bosses** now [origin-reviewed and strict exact](docs/ENEMY_MOTION_7204_EXACT_ORIGIN_AUDIT.md), adding **7,204 disjoint native bytes**; four additional [original Enemy creation/ECL runtime lifecycle game methods](docs/ENEMY_ECL_LIFECYCLE_762_ORIGINAL_GAME_EXACT_ORIGIN.md) are separately verified at **762 original exact bytes** without overlap; the enclosing 41,967B original Enemy ECL dispatcher remains nonexact; [layout](docs/CORE_ENEMY_DISPATCH_LAYOUT.md) |
| Gameplay cores | Scheduler, hit ownership, Player/SHT, Bomb and Item protocols; the complete 3,111B [Player main-frame C++ frontier](docs/PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md) is source-present but NONEXACT, with [independently corrected native controller getter/scale ABI](docs/PLAYER_FRAME_3111_GAMEPLAY_ABI_CORRECTION.md) ([original Timer postfix ABI corrected](docs/PLAYER_MAIN_TIMER_POSTFIX_3111_NATIVE_ABI.md), [original input/signed-speed and typed handle equality recovery](docs/PLAYER_ANIMATION_HANDLE_TYPED_EQUALITY_NATIVE_FRONTIER.md) [9×2 original direction-table correction](docs/PLAYER_MAIN_FRAME_NATIVE_9X2_DIRECTION_TABLE.md) improves to [two focus DWORDs/history lifetimes](docs/PLAYER_MAIN_FOCUS_AND_HISTORY_NATIVE_LIFETIMES.md) and [original X-then-Y motion accumulator source order](docs/PLAYER_MAIN_3111_NATIVE_XY_ACCUMULATION_ORDER.md) improve to [correct script indices and option pointer lifetimes](docs/PLAYER_MAIN_NATIVE_SCRIPT_INDICES_AND_OPTION_LOOPS_3111.md) improve to **783/783 original ordered mnemonic kinds** (3,114B/783 candidate versus original 3,111B/783), with a native 45/45-byte compatible handle equality and [all 67 original callee roles independently mapped](docs/PLAYER_MAIN_FRAME_67_ORIGINAL_CALLEE_ROLES_FRONTIER.md) (folded aliases remain provisional); **no duplicate original byte credit** and still no exact parent bytes); four directly called 120B [original game leafs are now strict exact](docs/PLAYER_FRAME_LEAF_120_EXACT_RECONSTRUCTION.md) |
| Archive and Progress | Entire **1,036B [LZSS compressor boss now whole strict exact](docs/ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md)**, paired with independently authored-exact 706B decoder, 612B ProgressMetadata and 346B PBG File::open; remaining SaveManager file/runtime pipelines are separate nonexact roots |
| Collision geometry | **19 complete original whole-function** geometry predicates, including 1,452B rectangle/rectangle and 1,439B line/rectangle bosses, now independently [origin-reviewed and strictly exact](docs/GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md); **13,360B disjoint authored credit** |
| Input devices | Complete 3,490B [keyboard/DirectInput/XInput poll](docs/INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md) strict exact; [corrected signed InputInf selector ABI](docs/INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md) from three original callers; game link/runtime remain open |
| Interpolation gameplay | Ten complete [interpolation bosses and evaluators](docs/INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md) add 8,571 native exact bytes, including 1,489B IntegerTriple, 1,129B Vector3, 1,074B Fog and independent ECL/Animation/Enemy/Bullet whole callers |
| Direct animation script and VM forward | Original 338B [AnimationFile script loader and 21B Renderer VM forwarding wrapper](docs/ANIMATION_DIRECT_SCRIPT_359_EXACT_RECONSTRUCTION.md) both whole **strict exact**; fixes the real Bullet emitter original call target; 39,470B VM remains open, 61 original source providers/266 old units preserved |
| Animation allocation factory | Complete original **73B/22-instruction** [game-owned Animation diagnostic allocation](docs/ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md) is now **73/73B strict exact**. Seven coherent `class Animation` headers and `/sdl` emit the authentic automatic class clear, with all three original E8 destinations; `extern template` prevents a 60B duplicate from the non-SDL 298B pool. **492/492 existing affected strict units protected by 117 affected-only cold objects**; the 31B compiler helper is not duplicate authored credit. |
| Animation pool allocation boss | Complete native **298B/78-instruction** [Renderer Animation pool allocation and reuse](docs/ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) now **298/298 strict exact**, original 14 E8 and 2 HIGHLOW fields; genuine 0x600 PooledAnimation slots and physically folded typed front/detach/initialize helpers, no duplicate bytes |
| Fog, geometry, Player-shot queries, PBG, Session and Graphics whole original methods | [Nine game-owned full original methods, 1,686 disjoint native exact bytes](docs/GAME_FOG_GEOMETRY_PLAYER_PBG_SESSION_1686_ORIGIN.md): three authentic 55B->38B->246B Player shot query stages, 248B CP932 game-file name conversion, 229B Vector3 normalization, two 226B FogValue arithmetic bodies, 214B Session and 204B GraphicsFlags constructors. Original PE **31 E8/10 HIGHLOW**, with independently exact 1,074B Fog interpolation, 941B Graphics, 346B PBG File open and polygon/geometry callers. **Eight source-bounded native objects, 121/121 strict units** protected including two stale receipts properly rebuilt; 16B compiler-generated Session startup thunk is a caller witness but not authored-byte credit. |
| Original Player direction data now defined | The genuine original 9×2 signed [72-byte Player direction table at 0x00572C48](docs/PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md) is now real maintained C++ source in src/PlayerDirectionTable.cpp, with pinned MSVC **72/72 original .rdata bytes identical** and both whole-frame references using one extern symbol. The whole 3,111B Player main now has **37/37 original PE absolute-data roles authenticated** (34 old strict-canonical globals, two table fields, one exact effect literal). This is DATA, not newly credited original game-code bytes; the Player parent remains NONEXACT. |
| Game Animation, ECL, Player and Item shared method exactness | [Seven genuine whole original game methods — Animation child links, recursive lookup and layer, async ECL spawn, Item spawn-many, PlayerFeedback construction and ScriptStack locals](docs/GAME_PLAYER_ANIMATION_ECL_SEVEN_ORIGINAL_1283_EXACT_ORIGIN.md) add **1,283 nonoverlapping native strict bytes**. Independently verified original PE **30 E8 /13 HIGHLOW**, exact original parent calls including 11,110B ECL tick and 794B Player ctor. **Seven affected-only MSVC objects /66/66 previously strict units** protected. The 3,111B Player parent and other large nonexact roots stay open. |
| Laser parameter and controller lifetimes | [Ten complete original LaserType0/1/2/3 parameter constructors/destructors and LaserController context/lookup methods](docs/LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md) are **936 new disjoint native strict exact bytes**, independently tied by original PE E8s to both the 12,140B Bullet and 41,967B Enemy opcode Bosses (both still NONEXACT). One source-only LaserParameters.cpp cold replay **12/12** preserves two already credited 179B/263B controller siblings without double counting. |
| BulletCommand PMR vector native STL helpers | [Original 121B/20B PMR vector copy/destructor](docs/BULLET_COMMAND_PMR_VECTOR_121_20_LIBRARY_EXACT.md) plus newly [200B/196B/73B genuine C++17 PMR capacity/uninitialized/memmove helpers](docs/BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md) now total **610B of distinct whole original library code** (five physical methods, **no authored-game byte credit**). One coherent existing template owner, native C++17 MSVC **7/7 exact source units**. Original 470B counted-range parent remains NONEXACT, with a newly identified missing real std::is_constant_evaluated call at 0x0047A99F; full 12,140B game Boss remains nonexact. |
| Original Bullet interpolation tangents and Timer reset | Seven genuine [38B/38B Vector3 tangent, 24B/24B float tangent, 25B/25B Timer reset and 25B Vector3 mode methods](docs/BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md) are now **199 disjoint original game-native bytes strictly exact**, with actual typed Bullet+0x420/+0x474 original E8 callers. New natural class declarations/definitions in Interpolation.hpp/cpp compile **50/50 exact**. Because the shared header affects a real **114-object/542-old-unit** include closure, all 114 affected objects were individually cold rebuilt, old 542/542 whole exact preserved; 25 original-PE-validated compiler-private string symbols were updated rather than hiding changes. The original 12,140B game parent remains NONEXACT, with no global cold replay. |
| Bullet vector interpolation game child functions | [Three complete original VectorInterpolation::set_start/set_end/set_duration physical game methods, 35+38+22 = 95 distinct native exact bytes](docs/BULLET_VECTOR3_INTERPOLATION_95_EXACT_FOLDED_ALIAS.md). The original whole 12,140B Bullet command Boss directly invokes all three with genuine Bullet+0x420 Vector3 interpolation. **Only 2 new canonical units**, because set_start is byte-identical to already strict 35B Motion::set_position at one original physical head; no duplicate game credit. Existing Interpolation.cpp whole native replay **43/43 exact**, plus Motion 13/13 and Bullet Command 8 1/1 scoped parent checks. Giant original dispatcher remains NONEXACT. |
| Bullet emitter boss | Entire original **3,735B/935-x86 BulletController::emit strict original exact**, including **3,832/3,832** original compiler code/NOP/13+11 switch-table bytes and **129/129 independently anchored true E8/HIGHLOW relocations**. Corrected original velocity **4.0f**, not wrongly inferred 2.0f, and restored native float lifetimes and Timer EH boundary in [full whole-game-boss proof](docs/BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md). One new targeted source cold replay **1/1 exact**, no global replay and no extra alignment/compiler byte credit; larger Bullet dispatcher still separate and nonexact. |
| Legacy STL compatibility and genuine Bullet shared_ptr ownership | The independently original [63B shared_ptr<EtamaArgInf> move assignment](docs/SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md) now also has its genuine [46B move constructor and 54B _Ptr_base move helper](docs/BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md) as entire **46/46B and 54/54B native exact**. The whole original 12,140B Bullet command Boss calls the 46B ctor; the already exact 63B assignment calls the same ctor and the ctor calls the separate 54B helper. Existing typed STL source cold replays **3/3 original exact**, with 33B and 8B fold-compatible aliases not credited twice. These 100B are STL library-origin, not new authored game bytes; giant parent remains NONEXACT. |
| Bullet command-11 | The entire **1,404B** original Bullet edge-ray state machine is now [whole canonical native exact](docs/BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md), with 33 original E8/35 PE HIGHLOW positions and a real typed 89B Vector2 polar linker-folded alias (no duplicate credit); the original 12,140B [34+8+11 nested-switch Bullet::run_extended_commands game Boss](docs/BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md) now has all **53 real PE HIGHLOW case-table entries**, **204/210 original E8 case calls** independently native-CFG mapped and two strict large callers, but its full C++ body remains absent/NONEXACT; the 3,735B emitter is separately whole exact |
| Graphics and sound | Entire **941B Graphics constructor** and 319B native ViewportState construction now [game-owned whole strict exact](docs/GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md); full Graphics/Renderer runtime remains open |
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
- [Current concise handoff and guarded storage cleanup (CORE628)](docs/ARTIFACT_RETIREMENT_CORE628.md)
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
