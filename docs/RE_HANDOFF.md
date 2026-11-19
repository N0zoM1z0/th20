# TH20 reconstruction — handoff to the next agent

**Reconciled 2026-11-11.** Start with [AGENTS.md](../AGENTS.md) for the
repository rules and exact target. This is the current work queue; the large
[evidence index](EVIDENCE_INDEX.md) contains dated investigations, **not** a
current-status ledger. Read the [open Boss backlog](RE_OPEN_BOSS_BACKLOG.md)
for more candidates. Git history preserves earlier checkpoints.

## Current target and authoritative status

| Property | Current state |
| --- | --- |
| Executable | `resources/th20.exe`, Japanese Steamless v1.00a, 1,858,560 bytes |
| Locked SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Version label caveat | Embedded title/replay strings say **1.00c** inside this *same* selected file; see [provenance](TARGET_PROVENANCE.md) |
| Provisional inventory | 6,929 function candidates, including one original-only recovered 2,884B head |
| Functions with provisional source mapping | **1,646** rows; includes unaccepted and excluded mappings |
| Source-present / implemented | **1,632** functions |
| Canonical exact units / compiler objects | **1,629** units / **471** protected MSVC objects and receipts |
| Credited game-authored whole exact | **815** distinct original heads / **274,659** `.text` bytes |
| Full playable game | **Not yet built, linked or runtime-validated** |

These figures are a checkpoint, not counters to update by hand. The
[original game exact ledger](../config/matches.csv),
[complete unit manifest](../config/match-units.toml), and
[function/source ledger](../config/functions.csv) are authoritative. Recheck
live progress with `scripts/repo-python scripts/report-reconstruction-status.py
--summary`. Authored game credit excludes compiler/STL helpers, duplicated
folded implementations, and post-`ret` switch/padding data.

## Recently closed whole-native work — do not reopen

- **Renderer D3D9 reset hooks** original 0x0041DB40/60/80/A0/C0 are [five whole-exact distinct native functions /108B](RENDERER_DEVICE_RESET_HOOKS108_STRICT_EXACT.md): four 21B byte setters and one 24B DWORD setter at native AnimationPoolOwner+0x6000E08...+0x6000E10, each nine exact x86 instructions. One cold source object, 5/5 exact local replay; these five hooks now have actual implementations in the NONEXACT 1,954B Window state reset Boss. No parent byte credit.

- **Window device reset state Boss** 0x0041A2C0 has [complete 1,911B compiled C++ source frontier vs original 1,954B/507 instructions](WINDOW_DEVICE_RESET_STATES_BOSS1954_FULL_SOURCE_FRONTIER.md): genuine 24 D3D9 RenderState, eight TextureStageState, six SamplerState calls, plus five Renderer recovery hooks. All 43/43 real game E8 and 47/47 PE data destination roles are preserved in original order; original MSVC security cookie/stack differ, so **NONEXACT and zero parent-byte credit**. This Boss is called by the now exact 884B Window scheduler; no full cold replay.

- **Graphics D3D9 resource release** 0x004DD840 [136/136B strict whole exact](GRAPHICS_D3D_RESOURCE_RELEASE136_STRICT_EXACT.md), 35 native i386, 13 original HIGHLOW data fields, 84 ordinary bytes and three actual COM Release virtual calls. Real process Graphics base +0x19C/+0x1A0/+0x1A4 member COFF addends; 1/1 source-scoped replay. Used by now exact 884B scheduler and separate exact 164B/385B Window Presenters.

- **Window frame scheduler Boss** 0x004193E0 is now [whole 884/884B strict exact](WINDOW_FRAME_SCHEDULER_BOSS884_STRICT_EXACT.md), **239 i386, all 32 original E8 +21 PE HIGHLOW physical positions and targets and 672/672 ordinary bytes**. Authentic scanline snapshot/time sample and scoped D3D9 Reset device restore original compiler NOP; 1/1 source-only canonical cold replay. Former 866B/NONEXACT notes below are historical frontiers; the separately accepted 31B RepeatCounter, 346B clock, 574B screenshot and 32B dispatch are not double-counted.

- **Graphics camera sqrt adapter** 0x00439850 is [source-native 35/35B strict exact, authorship review](GRAPHICS_CAMERA_SQRT_ADAPTER35_SOURCE_EXACT_ORIGIN_REVIEW.md): authentic float-to-double sqrt-to-float return, one original E8 to 0x00550000, 31 ordinary bytes; one-source 1/1 replay. Possible generated CRT/math wrapper, origin UNKNOWN, **no new game-authored head/byte credit**; the 846B camera Boss remains separately whole exact.

- **Graphics D3DX9 camera matrix Boss** 0x004DA1F0 [846/846B full strict exact](GRAPHICS_CAMERA_MATRIX_BOSS846_STRICT_EXACT.md): 194 i386, native 7 E8/20 HIGHLOW physical positions and targets, 738 ordinary bytes; true unsigned viewport 0/2^32 compiler conversion table, three Vector3 constructors, native sqrt and D3DX LookAt/Perspective. First full MSVC source compiled native exact, 1/1 source-scoped replay, +846 distinct authored game bytes. Exact 194B transform and 284B viewport callers preserved.

- **Graphics device matrix stage** 0x004DA120 is [whole 194/194B strict exact](GRAPHICS_PREPARE_DEVICE194_STRICT_EXACT.md): native 55 i386, original three E8/seven HIGHLOW physical targets, 154/154 ordinary bytes; real global Graphics D3D9 View/Projection transforms and Animation Renderer first point. One-source 1/1 cold replay. The connected 846B camera/matrix Boss 0x004DA1F0 remains a separate open function.

- **Graphics Worker close leaf** 0x004D9E30 [53/53B whole strict exact](GRAPHICS_WORKER_CLOSE53_STRICT_EXACT.md): real Graphics+0xD90 Worker stop/detach+join with the native SyncCloseSubThread diagnostic. Three E8 and one PE HIGHLOW original physical target, 37 ordinary bytes and original NOP all exact. Only new 53B source 1/1 cold replay; 370B/433B/583B Window frame callers remain exact.

- **Graphics viewport/clip switch** 0x0041DCE0 is [whole 284/284B strict exact](GRAPHICS_VIEWPORT_CLIP284_STRICT_EXACT.md), called by 15 original sites including newly exact 433B/583B/370B Window controllers. Uses true Graphics 0x16C ViewportState array, raw viewport +0xE0, adjusted D3D9 viewport +0x104, third point and Graphics +0xB04 reset. 2 E8 +4 HIGHLOW physical sites and 260/260 ordinary bytes exact, 1/1 new source cold replay; independent already exact 280B sibling not re-credited.

- **Window paced frame controller Boss** 0x0041A030 [370/370B strict whole-native exact](WINDOW_FRAME_PACED_BOSS370_STRICT_EXACT.md): original 97 i386, all 15 E8 and 15 HIGHLOW original positions and targets, 250/250 ordinary bytes. Real FunctionChain render path and already exact 385B paced Presenter; original true guard generates the natural 13B branch. New source 1/1 scoped cold replay, all six header-affected Window exact units individually 1/1. The 884B Window scheduler remains NONEXACT.

- **Window paced frame controller Boss** 0x0041A030 is [whole 370/370B strict exact](WINDOW_FRAME_PACED_BOSS370_STRICT_EXACT.md), 97 native i386. The real constant-true frame enable guard restores native +13B; 15/15 E8, 15/15 PE data locations/targets and all 250 ordinary bytes match. Calls the separately exact 385B paced Presenter and genuine D3D9 scene/FunctionChain draw; new 1/1 and six header-affected local 1/1 strict replays all passed. Original 884B scheduler remains NONEXACT.

- **Window synchronized no-wait frame controller Boss** 0x00419DE0 is [whole 583/583B strict exact](WINDOW_FRAME_NO_WAIT_BOSS583_STRICT_EXACT.md), 138 original i386, real WindowState clock sync, deadline and Sleep(1), FunctionChain update/draw, D3D9 scene and existing exact 164B Presenter. All 16 E8 +20 HIGHLOW physical fields/targets and 439/439 ordinary bytes exact. One new 583B 1/1 source cold replay, plus five Window-header-affected older exact units each 1/1. 884B scheduler stays NONEXACT.

- **Window frame controller Boss** 0x00419C20 [whole 433/433B strict exact](WINDOW_FRAME_CONTROLLER_BOSS433_STRICT_EXACT.md): 110 original i386, 15 E8 and 18 HIGHLOW original physical fields and targets plus all 301 ordinary bytes. Real FunctionChain 611B update/587B draw, D3D9 BeginScene/SetTexture/EndScene, actual 32-bit render-alpha reset and Window 1/60 frame deadline; 1/1 scoped replay. Its 884B scheduler callee remains independently NONEXACT.

- **Window screenshot scene Boss** 0x00419760 is now [whole 574/574B strict exact](WINDOW_SNAPSHOT_SCENE574_STRICT_EXACT.md): native 132 i386, all original 20 E8 +12 HIGHLOW physical fields, 446/446 ordinary bytes; genuine short-circuit input guard, two real c_str pointer lifetimes and original WindowState base+0x89 addends. 1/1 scoped replay; 884B scheduler still NONEXACT.

- **Window paced D3D9 Present Boss** 0x00419A50 is [385/385B whole strict exact](WINDOW_PACED_PRESENT385_STRICT_EXACT.md), 94 original i386, original 1/60 frame budget and Sleep, real D3D9 Present/Reset with authentic 12 E8 and 17 PE HIGHLOW physical fields/targets, 269/269 ordinary bytes. 1/1 local cold replay; shared-header exact 31B getter and 164B no-wait presenter each 1/1 preserved. The 574B screenshot is now exact; only the 884B frame scheduler remains NONEXACT.

- **Window D3D9 Present/Reset** 0x004199A0 is [164B/49-i386 whole strict exact](WINDOW_PRESENT_NO_WAIT164_STRICT_EXACT.md), all nine native E8 and eight HIGHLOW physical fields/targets plus 96/96 ordinary bytes. Authentic distinct Present and Reset device lifetimes and a real scoped NOP after the 574B screenshot update make MSVC naturally produce exact stack and length; 1/1 new and 1/1 shared-header-affected 31B replay. The 574B scene child is now exact; the 884B scheduler remains NONEXACT; 32B clock dispatch already exact.

- **Window snapshot pending Renderer leaf** 0x0041BFC0 [88B/28-i386 whole strict exact](WINDOW_CAPTURE_PENDING88_STRICT_EXACT.md), four real 40B Renderer surface copy records at +0x18; submits each active entry through already exact 439B D3D9 blit at 0x0044BB10 then retires file_index to -1. Single real E8 and 84/84 ordinary bytes exact; 1/1 local cold replay. 574B screenshot is now exact; only the 884B Window scheduler remains NONEXACT.

- **Window frame scheduler Boss** 0x004193E0 now has [complete compiled source frontier](WINDOW_FRAME_SCHEDULER884_FULL_SOURCE_FRONTIER.md): 884B/239 native vs 866B/236 real-D3D9 candidate, with all 32 E8 and 21 PE data target roles in original order (13/32 E8 and 7/21 data sites aligned, 367 ordinary positional bytes). True GetRasterStatus(InVBlank/ScanLine), D3D9 Present/Reset and 574B screenshot child. Parent NONEXACT, zero byte credit; 31B repeat, 346B clock, 32B dispatch and 574B screenshot children are independently exact. Only source-local compiler probe, no full cold replay.

- **Window frame scheduler repeat leaf** 0x0041CA50 is [31/31B strict exact](WINDOW_ACTIVE_REPEAT31_STRICT_EXACT.md), 11 i386/no relocs; genuine WindowState+0x2100 index into four 12B RepeatCounters at +0x2104. Original 884B Window scheduler calls this 14 times. Only new 31B credited; 1/1 scoped cold replay; parent stays NONEXACT.

- **Window frame time wrappers** 0x004AC170 **46B**, 0x004AC200 **42B** and 0x004AC270 **21B** are [full native source-exact](WINDOW_FRAME_TIME_LEAVES109_NATIVE_EXACT.md). Genuine 8B time temporary creates original compiler NOP, three real CRT/chrono adapter calls, and 6/6 affected exact units /4 cold objects preserve the 113B pipeline, 437B Boss and 32B dispatch. These three helpers are **origin review**, not credited as new authored game bytes.

- **Window device frame pipeline** 0x004AC0E0 is [113/113B whole strict exact](WINDOW_FRAME_PIPELINE113_STRICT_EXACT.md). The real three original date/time helper E8 sites and 101/101 ordinary bytes match. No native GS cookie; one source compiled /GS- without /sdl. Its real 437B parent and 32B dispatch remain exact in scoped **3/3** cold replay; only the new 113B is credited.

- **Window device frame-timing Boss** 0x004ABD50 is [437/437B whole strict exact](WINDOW_FRAME_DEVICE_CLOCK437_STRICT_EXACT.md): 105 i386, original 2 E8/14 HIGHLOW sites and targets, 373/373 ordinary bytes. Real FPS 65/57 limits, 1.0/60.0 intervals, actual 0/2^32 unsigned time table and GameController flag roles; scoped **2/2** replay also preserves 32B Window frame dispatch. Adds 437 distinct authored game bytes; 113B downstream pipeline is still open.

- **Window/Frame clock dispatch** 0x004193C0 is [32/32B whole strict exact](WINDOW_FRAME_CLOCK_DISPATCH32_STRICT_EXACT.md), with two genuine E8 and two process-pointer HIGHLOW original sites/targets (16/16 ordinary bytes). Calls separate 437B device frame owner conditionally, then already exact 37B Card clock callback. Scoped **1/1** source cold replay; +32 new authored game bytes. The 437B callee was subsequently [reconstructed whole strict exact](WINDOW_FRAME_DEVICE_CLOCK437_STRICT_EXACT.md).

- **WindowState seconds clock** 0x0041CB10 is [346/346B whole strict exact](WINDOW_SECONDS_CLOCK346_STRICT_EXACT.md): 79 i386, original 8 E8/19 PE HIGHLOW physical sites and base/addend-correct roles, 238/238 ordinary bytes. Authentic 64-bit QPC/WinMM clock, true 0 and 2^32 DWORD correction table and one shared arithmetic double local. Scope: **1/1** cold object; 346 new authored original bytes. Its two caller sites in the 645B Card clock were separately verified.

- **Card time archive selectors** at 0x00488740 **38B** and 0x00488770 **41B** are [whole strict exact](CARD_TIME_ARCHIVE_ACCESSORS_38_41_NATIVE_EXACT.md); the genuine 20B/44-byte-index generic helper is also compiled exact but held authorship review and excluded from original game credit. Existing folded 22B indexer retained exact; all **3/3** changed units in one object, **79** new authored bytes.

- **Card time-settlement Boss** 0x004872D0 is [645/645B whole strict exact](CARD_CLOCK_BOSS645_CALLBACK37_STRICT_EXACT.md), together with its native independent 37B callback 0x00487560. All **14 E8 / 12 PE HIGHLOW** native sites/targets, **541/541** ordinary bytes and native FWAIT plus exception-aware integer conversion match. **2/2** source-only cold replay, 682 additional original bytes. The original 346B WindowState clock helper remains open; the two 38/41B record selectors were subsequently [closed whole exact](CARD_TIME_ARCHIVE_ACCESSORS_38_41_NATIVE_EXACT.md).

- **Card Draw Boss** `0x00487590` is [797/797B whole strict exact](CARD_DRAW_BOSS797_AND_ASCII_SETTERS75_STRICT_EXACT.md), with **30/30 E8, 28/28 HIGHLOW** exact sites and targets, plus all **565 original ordinary bytes**. Three real AsciiInf setters (font, layer, packed alpha) at `0x00488B00`, `0x00488A00`, `0x00488940` are **25/25B** each; **4/4** scoped strict units /2 objects. This closes Card register → draw callback → draw Boss, not Card Start or 6,073B battle control.

- **Card registration + C callback bridges** `0x00487B10` **121B** and
  `0x004885D0` / `0x00488680` **13B each** are [three new whole strict exact](CARD_REGISTRATION121_CALLBACK_BRIDGES13_STRICT_EXACT.md).
  Actual `Session::context`, Card publication, two original
  FunctionChain priorities **40/12** and their original function-pointer
  PE HIGHLOW fields; the tick callback enters our exact 875B Card Boss.
  The draw callback now enters the [independently completed 797B draw Boss](CARD_DRAW_BOSS797_AND_ASCII_SETTERS75_STRICT_EXACT.md).
  A focused 6/6 unit replay also preserved the existing 875B/32B/23B Card units.

- **Card periodic Update Boss** `0x00486F60` **875/875B whole strict exact** and its distinct
  `0x00487B90` **32/32B HUD leaf** are [strict original complete](CARD_TICK_BOSS875_AND_UI32_STRICT_EXACT.md). All 28 E8 + 8 PE HIGHLOW positions/targets
  and 731 original ordinary bytes matched pinned MSVC; genuine Card/Timer,
  Player/Enemy, bit8 gating, real 0.05f native vector interpolation and HUD
  bit0 side effect. The preexisting [23B Card flag bit8 getter](CARD_FLAG8_GETTER23_STRICT_EXACT.md)
  remains exact in the same scoped 3/3 replay, not double credited. The
  6,073B battle controller and 1,896B Card Start remain NONEXACT.

- **Two native Animation field leaves** `0x0044C650` **21B alpha** and `0x0044CB00` **19B Vector3** are [whole strict exact](ANIMATION_FIELD_READ_LEAVES_21_19_STRICT_EXACT.md). Original 4KB/9KB callers and true `+0x493`/`+0x484` offsets are attested; two distinct heads add 40 original bytes. One new source/object, scoped 2/2 strict replay; no existing canonical headers or units changed.
- **Animation pool staging reset** `0x00445A40` is [111/111B whole exact](ANIMATION_POOL_STAGING_RESET111_STRICT_EXACT.md). Three original recovery callers pass the existing pool; its queue and stream cursors are shared with exact 192B Draw Flush. One new canonical unit and object were cold-replayed in isolation.
- **Both Renderer list-update Bosses** `0x00449870` **508B** and
  `0x00449B20` **511B** are [whole strict exact](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md).
  An Animation-only `class IntrusiveList<Animation>` specialization reproduces
  the authentic `/sdl` preclear. All **82 affected existing units /22 objects**
  passed scoped strict replay. The separate **40B list ctor /42B reset** are
  still open, however: [current leaf proof](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md).
- **Game file exists** `0x004107A0` is [157/157B strict exact](GAME_FILE_EXISTS157_NATIVE_FRONTIER.md).
  Its real input is **`const char*`**, not `const filesystem::path&`; it calls
  the existing 44B path-from-narrow-string constructor. Seven E8/three
  HIGHLOW roles are exact. The previous 155B path-copy theory is superseded.
- **Renderer formatted-text caller** `0x0044AC20` **417B** is
  [whole exact](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md);
  its adjacent 586B centered-text sibling remains open.
- **D3D9 alpha-fringe finalizer** `0x00451910` is
  [2,745B whole exact](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md),
  including a 2,798B complete comparison containing 53B of uncredited
  after-`ret` table data. Related 562B uploader, 439B copy, and 581B effect
  are independently exact.
- **InputDevice poll** `0x00421B00` **3,490B** is
  [whole exact](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md). The
  1,022B AnimationFile loader, 269B preloader, and multiple 2–4KB draw
  backends are also exact. Do not trust old docs calling them source-absent.
- **Particle-grid children** (26B EffectInfo lookup, 83B spawn, 51B Event,
  92B Stop) are independently exact; this does **not** make their 2,884B
  parent exact. See [current parent source](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md).

## Work queue — attack large Bosses and related leaves together

1. **5,993B Animation Draw** `0x00443880` — source
   [`AnimationDrawBoss.cpp`](../src/AnimationDrawBoss.cpp), still **NONEXACT**.
   Whole code 5,993B/1,501 instructions, original 49+31 switch pointers,
   all 123 native E8 target roles. Current source aligns **113/123 E8 sites**,
   **26/32 body HIGHLOW sites**, and **4,801/5,376 nonrelocation bytes**.
   Investigate mode35/36 first-scale x87 spill and mode45 SSE/temp lifetimes;
   preserve the current used-width and color/count improvements.
   [Latest proof](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md).
2. **2,884B particle-grid Update** `0x0045C360` — source
   [`AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp),
   **NONEXACT**: candidate 2,924B/760 i386 versus original 2,884B/768.
   All 99 E8 and 25 HIGHLOW *roles* remain correct; native ESI/age lifetime
   was recovered, with six E8 physical sites aligned. Next: polar/x87
   argument spills, 0x19C native frame and loop register lifetime.
   [Current experiment](ANIMATION_PARTICLE_GRID_UPDATE_2884_ESI_POLAR_LIFETIME_CONVERGENCE.md).
3. **Near-exact leaves:** 336B ANM group parser `0x0044EBF0` is
   278/280 ordinary bytes (two stack slot operands), while its 1,022B
   loader parent is exact. The 40B Animation list ctor is 34/36
   ordinary bytes in an **evidence-only** double-tail hypothesis; 42B reset
   is 37/38. The 294B ASCII text submit is 292B (two native NOPs missing).
   Do not insert unused locals, redundant writes or manufactured NOPs.
   [ANM proof](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md),
   [list helper proof](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md),
   [text submit](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md).
4. **Other source-present Bosses:** The 586B centered Unicode text now
   compiles as **586B/140 instructions**, with 10/11 physical E8 sites
   and 399/506 ordinary bytes aligned, but only four of nine body data
   positions; the reordered SSE/font-width lifetime remains **NONEXACT**.
   The 578B ASCII renderer, 2,245B glyph compositor, 2,227B Unicode
   glyph core, 1,896B Card spell-start and 3,111B Player main also remain
   open. The glyph **compositor** now has a complete 2,141B/565-i386
   natural candidate with **37/37 original E8 target roles**, all nine
   real stride getters and the four 22B indexed offset calls. Its 2,245B
   parent remains NONEXACT, and 24/24 linked exact descendants still pass.
   [Compositor current roles](GLYPH_MASK_BOSS2245_RGBA4444_SOURCE_STRIDE_37_CALLS.md).
   The **Glyph Text Core** now types its completion-byte pointer, uses a
   named task alive through queue submission and matches **17/25 E8 sites**;
   its 2,296B source remains NONEXACT against the original 2,316B full
   code+table contribution.
   [Current queue-task ABI](GLYPH_TEXT_CORE2227_QUEUE_TASK_ABI_FRONTIER.md);
   [Current glyph core proof](GLYPH_TEXT_CORE2227_COLOR_AND_CANVAS_ABI_FRONTIER.md);
   [queued task/EH frontier](GLYPH_TEXT_CORE2227_QUEUE_TASK_ABI_FRONTIER.md);
   [Current centered frontier](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md);
   [other Bosses](RE_OPEN_BOSS_BACKLOG.md).
   The 1,896B **Card Start Boss** now recovers its real two 20B renderer
   getters, separate 16B text getter, seven independent script-table
   global reads, and the PMR name lifetime ending after all spell work.
   Source candidate **1,848B/490 i386** has **62/62 E8 callee roles**
   and **26/26 data roles** in native order, but still **NONEXACT**
   (original 1,896B/512); affected 128B+7B source units and existing
   1,522B HUD/20B getter remained exact under bounded validation.
   [Current Card Boss proof](CARD_START1896_FULL_CALL_DATA_ROLES_FRONTIER.md).
5. **Huge source-absent dispatchers:** 12,140B Bullet command,
   41,967B Enemy ECL opcode, 39,470B Animation VM update. Exact children
   do not establish whole-parent exactness. Keep their full original
   code/table boundaries in view; see [backlog](RE_OPEN_BOSS_BACKLOG.md).

## Fast reproduction and safety boundaries

Use the selected original target only; source presence, semantic behavior,
compiler output, whole byte exactness, linkage and playability are distinct.
Original SHA, function boundaries, E8 destinations and physical PE HIGHLOW
fields must be independently grounded. The compiler is pinned MSVC 19.44
x86 (`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`).
Ghidra and tool access are described in [shared tools](SHARED_TOOLS.md).

```sh
# Read current state; no cold compilation
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target

# Whole source-present NONEXACT Bosses, each one isolated build/role check
scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/probe-animation-particle-grid-update2884.py
scripts/repo-python scripts/verify-animation-file-group336-native.py

# For changed exact source, ONLY its affected unit(s)/include consumers
scripts/repo-python scripts/build.py --unit UNIT_ID
scripts/repo-python scripts/compare-coff-function.py --unit UNIT_ID
# Or: scripts/repo-python scripts/replay-exact-units.py --source src/FILE.cpp
```

**Never run unfiltered full cold replay for a routine handoff.** Inspect
and handle all dirty/untracked files before changing code; preserve original
user data and useful unresolved experiments. Commit meaningful progress with
**`gpt-web: xxx`**; all maintained code comments/docs/commits are English.
For documentation-only edits or removal of regenerated ignored objects, there
are **zero native units to rebuild**: check links, tracking and Git diff.

## Local storage and next-agent startup

The locked executable, `_reference`, `ghidra-project`, pinned MSVC/SDK in
`.tools/msvc`, the TH20-specific Wine prefix in `.tools/wine`, `.venv`,
current source and all **438 canonical** object/receipt providers are
**protected**. Storage maintenance on this checkpoint removed 37
recreatable `build/gptweb-*` experiment-output directories and superseded
private source clones; keep current `.analysis/` research sources for open
Bosses. Re-run the relevant probe script when a removed temporary object is
needed, rather than restoring old binary caches. Large historical
entries in the [evidence index](EVIDENCE_INDEX.md) are dated and sometimes
superseded; use the **current ledger and this handoff** for status.

## 2026-11-19 session — contextual ANM count views

- Added same-storage `AnmVariables` aliases for the context-specific uses of
  slot 10000: `geometry_vertex_count`, `draw_shape_count`, and
  `particle_grid_count`. `field_00` remains the generic script-variable name.
- Updated `AnimationGeometry`, the 5,993B Draw Boss, and the 2,884B Particle
  Grid Update to use their evidenced contextual names. The union remains 64B
  with every alias statically asserted at offset zero; no new storage or
  padding was introduced.
- Focused verification passed for the Draw Boss source/ABI/native census and
  Particle Grid role audit. Their machine-code statuses remain unchanged:
  Draw Boss NONEXACT (5,993B/1,501 instructions; 123 call roles), Particle
  Grid NONEXACT (2,924B/760 instructions vs native 2,884B/768; 99 call roles,
  25 data roles). The contextual naming pass reduced Draw Boss lexical
  anonymous-identifier findings from 48 to 24; this heuristic count is not an
  exactness metric.
- The next semantic frontier remains the mode 35/36 x87 spill/lifetime and
  mode 45/46 SSE ordering in Draw Boss, plus the Particle Grid local-frame and
  loop-lifetime differences. Do not add dead compiler-shaping locals to mimic
  native stores that are not subsequently read.
- See `docs/ANM_VARIABLE_SLOT_10000_CONTEXTUAL_COUNT_VIEWS.md` for the
  evidence and the distinction between contextual views and fixed field
  semantics.

## 2026-11-19 session — Animation retirement lifecycle view

- Resolved `Animation+0x570` as a retirement lifecycle state from independent
  producers and consumers: file detach and recursive tree marking write 1;
  active-list updates distinguish 0 (update) from 1 (queue); pending
  retirement appends the +`0x53c` link once and writes 2; draw rejects
  nonzero; pool/reset paths restore 0.
- Added the same-storage `retirement_state` alias for renderer/retirement
  consumers while preserving the original `field_570` spelling and exact
  `Animation::clear_field_570` mangled symbol in CORE/EXACT-119. Both names
  are statically asserted at +`0x570`. See
  `docs/ANIMATION_RETIREMENT_STATE_570_SEMANTICS.md`.
- Targeted exact replay passed for all 54 configured units across the eight
  affected source objects (Animation 38/38, Binding 7/7, Retire 3/3, Queue
  1/1, Classification 2/2, File Detach 1/1, List Update 508 1/1, List Update
  511 1/1). The Draw Boss source/ABI and Particle Grid role audits also pass;
  both large parents remain NONEXACT.

## 2026-11-19 session — Animation scale-mode view

- Resolved `AnimationBase::flags+0x0c` (`Animation+0x4A4`) as a scale-mode
  byte from the parameter producer and geometry/draw consumers. Modes 1/3
  select full scale and 2/4 half scale in position transformation; draw and
  corner paths use 1/5 and 2/6 for the corresponding full/half behavior.
- Added `scale_mode` as a same-byte, same-width bitfield union alias while
  retaining `field_0c`; `AnimationFlags` remains 0x20 bytes and the following
  byte is statically pinned at offset 0x0d. Updated the observed
  producers/consumers to use the semantic name. See
  `docs/ANIMATION_SCALE_MODE_4A4_SEMANTICS.md`.
- Targeted exact replay passed for the 29 affected configured units:
  Animation Parameters 20/20, Corner Projection 1/1, Geometry 6/6, Draw Mode
  8 1/1, and Corner Rotated 1/1. Draw Boss source/ABI/native and Particle Grid
  role audits also pass; their parents remain NONEXACT.

## 2026-11-19 session — particle-grid angle variable

- Resolved the Particle Grid Update's remaining `AnmVariables.field_28` use:
  it is added to `rotation_z_value()` to form the second polar heading.
  Added the same-storage `particle_grid_angle_offset` view at slot 10010
  (`+0x28`) and used it in the 2,884B parent. The generic `field_28` name
  remains available to other script-variable consumers. The Particle Grid
  lexical debt report is now 0 under the repository's layout-heuristic scan;
  this is not an exactness metric. Its focused role audit still confirms
  99/99 call targets and 25/25 data roles, with the source remaining
  NONEXACT at 2,924B/760 instructions versus native 2,884B/768. The shared
  `Animation.cpp` object also passed targeted exact replay 38/38 after the
  ANM layout alias. See
  `docs/ANM_VARIABLE_SLOT_10010_PARTICLE_GRID_ANGLE_OFFSET.md`.

## 2026-11-19 session — Animation viewport-placement mode

- Resolved the two low bits at `Animation+0x4A3` as a viewport-placement
  selector. Mode 1 selects WindowState coordinate pair `+0x58/+0x5c`, mode 2
  selects `+0x60/+0x64`, and mode 0 leaves ordinary mesh-relative placement.
  `set_layer`, file spawn, Bullet/Player draw setup, mesh lifecycle, geometry,
  and mode-6/mode-7 renderers independently corroborate the values.
- Renamed the bitfield to `viewport_placement_mode` without changing its
  two-bit width or the `AnimationFlags` 0x20-byte layout. Focused strict
  replays passed Animation Geometry 6/6, Animation Parameters 20/20, mesh
  draw 1/1, mode 6 1/1, mode 7 setup 1/1, AnimationFile spawn 1/1, Bullet
  emitter 1/1, Player Draw 1/1, and RenderMesh lifecycle 2/2.
- RenderMesh's four compiler-local `$SG` literal labels changed under the
  typed header name; their relocation sites, targets, and literal contents
  stayed identical. Only those local names were refreshed in the canonical
  relocation manifest. See
  `docs/ANIMATION_VIEWPORT_PLACEMENT_MODE_4A3_SEMANTICS.md`.

## 2026-11-19 session — Animation mode byte semantics

- Named the low byte of `AnimationFlags::bytes_00` as `animation_mode`; it
  selects the renderer/geometry dispatch mode (including mode 12 mesh and
  geometry modes 9/13/14/24/25/47/48). Named the separate high byte
  `flag_byte_01`, used by the setter, render-mesh strip setup, and quad
  texture-state cache.
- Kept the two-byte overlay and 16-bit raw `field_00` alias unchanged. The
  four RenderMesh compiler-local literal labels were refreshed in the exact
  relocation manifest; both RenderMesh units still replay exact. See
  `docs/ANIMATION_MODE_BYTE_498_SEMANTICS.md`.

## 2026-11-19 — Animation 86B interpolation callee closed

- Entire original `0x00438C60` Animation integer interpolation from two byte
  endpoints is now strict exact, `86/86` native bytes and three relocations;
  `src/AnimationFadeConfig86.cpp`, unit `animation_fade_config_86`.
- Consolidated four exact Polygon/Ribbon/Trail caller sources onto the one
  canonical callable borrowed view. Scoped strict replay: 6/6, 1/1, 1/1,
  1/1; original caller instruction and E8 target roles unchanged.
- See `docs/ANIMATION_FADE_CONFIG86_STRICT_EXACT.md`. The much larger
  Animation Draw, Particle Grid and GDI Text cores remain NONEXACT.

## 2026-11-19 — Glyph Text 2,227B Boss queue lifetime convergence

- A named **used** rvalue reference keeps the real glyph render job alive
  during its move into the queued `std::function`; destructors remain after
  queue submission in original order. The complete 2,308B/468-i386 C++
  candidate now has the native `0x310` frame, all 25 genuine E8 roles and
  43 data roles, 17/25 aligned E8 sites, **52** absolute site offset sum
  (down from 148), 41/43 aligned data sites, 1,629/1,948 ordinary bytes.
- The original 2,227B/470-i386 code +NOP+22-pointer contribution totals
  2,316B; the parent remains NONEXACT, no new game authored bytes. Its
  separate 132B constructor and 23B destructor still pass 2/2 scoped replay.
- See `docs/GLYPH_TEXT_CORE2227_RVALUE_QUEUE_LIFETIME_FRONTIER.md`.

## 2026-11-19 — Vector2 interpolation template source frontier

- The existing natural `Interpolation<Vector2>` instantiation in
  `src/Interpolation.cpp` now maps five complete original functions at
  `0x00438E90`, `0x00439510`, `0x00439420`, `0x00438AC0`, and `0x00439640`.
  Scoped replay rebuilt one Interpolation object and passed **55/55** units.
- The new five functions cover 198 original bytes and all five original E8
  targets from Vector2 `begin`. The native SHA/extent/ret/E8 proof is
  `scripts/verify-animation-vector2-interpolation-native.py`.
- Authorship remains under review because these are generic template bodies;
  they are source-present and exact but receive no new authored `matches.csv`
  credit yet. See `docs/ANIMATION_VECTOR2_INTERPOLATION_NATIVE_SOURCE_FRONTIER.md`.

## 2026-11-19 — Animation VM opcode 0x5A corner-projection chain

- The 95B `0x00438EB0` Vector2 screen-coordinate normalizer is now whole-native
  exact in `src/AnimationVector2CoordinateNormalize95.cpp` (commit `888f36b`).
- Recovered the original `0x00445770` 244B mode dispatcher and added natural
  C++ source. Modes 0/2/3 route to the 985B corner projector; mode 1 routes to
  the 1486B rotated projector. Its real unused ECX receiver is the renderer
  owner global `current_animation_pool` at `0x005C0028`.
- The focused probe confirms the original 244B SHA/79 instructions, three E8
  destinations and four HIGHLOW fields, and the candidate's three projector
  calls plus three renderer-owner relocations. Candidate is **192B**, so it
  remains SOURCE-PRESENT NONEXACT with no match-unit or byte credit.
- The `0x0042B5D0` 39,470B VM's opcode `0x5A` and final flag-bit-11 path both
  use this dispatcher, then normalize four Vector3 corners and store width/height
  at `+0x398/+0x39C`. The VM parent remains open. See
  `docs/ANIMATION_CORNER_PROJECTION_DISPATCH244_SOURCE_FRONTIER.md`.

## 2026-11-19 — 716B AnimationFile::apply_sprite whole-native exact

- Replaced the temporary zero-data derived ABI view with the actual
  `AnimationFile::apply_sprite` member declaration and implementation in
  `src/AnimationFile.hpp` / `src/AnimationFileSpriteApply.cpp`; no storage or
  object layout was added. The x86 owner asserts `bytes+0x3C` and
  `sprites+0x50`.
- Recovered the exact four-corner UV order, UV width/height, source extents,
  both identity-based scale matrices, copied transform matrix, and signed
  integer source rectangle.
- The complete original `0x00438620` body is 716B/179 i386 instructions.
  Canonical member source emits 716/716 exact: 696 ordinary bytes and all
  20 relocation bytes; the original SpriteData accessor E8 and four HIGHLOW
  destinations are independently pinned. The only unit is
  `animation_file_apply_sprite`; the obsolete derived-view unit was removed.
- Original VM `0x0042B5D0`, wrapper `0x0044BD50`, and setup/apply path
  `0x004708E0` are direct consumers. The 39,470B VM parent remains NONEXACT.
- See `docs/ANIMATION_FILE_SPRITE_APPLY716_STRICT_EXACT.md`.

## 2026-11-19 — AnimationFile 604B VM child-spawn method restored

- Added the natural `AnimationFile::spawn_child(int, Animation*, uint32)`
  return-by-value member in `src/AnimationFileSpawnChild604.cpp`. The
  hidden `AnimationHandle` return-object ABI is preserved.
- It locks recursive registry slot 9, increments AnimationFile+0x68,
  allocates from the real Animation Pool, inherits the parent's renderer
  and layer, binds the child script, dispatches the four Renderer modes,
  and links the child into the parent's intrusive Animation tree.
- Original VM opcodes 0x72-0x75, 0x77 and 0x7C call this 604B helper.
  Opcode 0x76 is a separate 619B helper at 0x004512B0.
- Whole 604/604 strict exact: 528 ordinary bytes + 76 relocation bytes,
  all 19 relocation destinations exact, 15 original E8 calls and four
  original PE HIGHLOW fields independently verified.
- See `docs/ANIMATION_FILE_SPAWN_CHILD604_STRICT_EXACT.md`.

## 2026-11-19 — 236B recursive world position bound to Animation

- Replaced the temporary `NativeAnimationRawPositionView` ABI with the
  actual `Animation::world_position_for_spawn(Vector3&)` member. The method
  remains whole-function strict exact at `0x0044CB80`, 236/236 bytes.
- Original recursive parent semantics are unchanged: compose the three
  local vectors, honor parent-inheritance bit 12, optionally rotate XY
  under bit 5, recurse and add the parent's position.
- All 77 original instructions, eight E8 calls, the recursive self-call,
  one PE HIGHLOW cookie and all nine relocation destinations are verified;
  200 ordinary bytes + 36 relocation bytes exact. Removed the derived-view
  source and duplicate experimental unit.
- This real Animation member is the position dependency for the next
  619B opcode-0x76 recursive child-spawn helper.

## 2026-11-19 — AnimationFile 619B recursive child-spawn helper restored

- Added natural `AnimationFile::spawn_child_and_update(int, Animation*, uint)`
  source. It applies the file template, inherits parent renderer/layer/flags,
  copies the parent's recursive raw world position and transform vectors,
  then executes the new Animation VM before Renderer registration.
- Original VM opcodes 0x76 and 0x78 call this 619B helper. The existing
  236B raw-world-position helper and four Renderer modes are reused exactly.
- Whole 619/619 strict exact: 551 ordinary bytes + 68 relocation bytes,
  all 17 relocation destinations exact, 13 original E8 calls and four
  original PE HIGHLOW fields independently verified. The 39,470B VM callee
  remains NONEXACT and is not credited.
- See `docs/ANIMATION_FILE_SPAWN_CHILD_UPDATE619_STRICT_EXACT.md`.

## 2026-11-19 — eight original Animation VM opcode leaves restored

- Recovered the 43B `Color3(red,green,blue)` BGR-storing constructor used
  by opcode 0x55; the 29B `Timer::set_from_current` helper used by VM
  jump/reset paths; all four 23/24B `Interpolation<Angle>` start/end and
  tangent setters used by opcode 0x53; and the 76B/62B Animation angular-
  rate and scale-rate setters called by opcodes 0x57/0x58.
- Every leaf has its own physical match unit and whole original PE proof.
  All eight complete C++ candidates replay strict exact (305/305 bytes,
  including the Timer helper's one real E8 relocation to `Timer::set`).
- The 39,470B `Animation::update` Boss remains explicitly NONEXACT; these
  are verified leaves and opcode semantics, not a claim that the dispatcher
  has been reconstructed.

## 2026-11-19 — full Animation::update VM dispatcher translated to C++

- Added a compiling `std::int32_t Animation::update()` source translation
  for the complete original 39,470B Boss at 0x0042B5D0. All 161 original
  opcode case labels are represented, and known helper calls now route
  through maintained Animation, AnimationFile, Timer, Interpolation,
  Motion, AnimationHandle and geometry C++ interfaces.
- The immutable original is independently bounded at 39,470B / 8,559
  instruction heads / 505 E8 / 55 PE HIGHLOW. The current C++ contribution
  is 40,808B: 40,164B code plus a compiler-emitted 644B/161-entry switch
  table; the code portion decodes to 8,382 instruction heads and 505 E8.
  The generic `NativeAnimationVmCallView` numeric adapter has been removed;
  120 Animation/AnimationFile/Motion/AnimationHandle/Timer/Clock/Random/
  Controller/Vector3/Interpolation/config operations now use direct typed C++
  member expressions; all corresponding numeric `FUN_` wrappers are gone.
  308 operand/value lookups are direct Animation member calls
  (`integer_argument`, `float_argument`, `integer_value`, `float_value`).
  All numeric `FUN_` wrappers are gone. The 0x4397F0 helper is correctly
  identified as CRT `fmod` (not atan2) and is bound to the exact 48B
  `scalar_math::floating_remainder` owner with the original `_fmod` relocation.
  Both call sites are typed; the 14 previous-file lookups and both corner
  projection dispatch calls also use direct typed C++ owners.
  All 505 candidate E8 destinations match the original call-target multiset,
  including postfix Timer increment, child-spawn return ABI, corner projection,
  the whole-exact +0x18 file lookup, the original 0x0040BC20 array helper,
  the newly exact 59B Timer unscaled-fractional advance at opcode 4, the
  existing whole-exact 20B CardRenderer current-file getter at all three
  negative-index fallback paths, typed Timer postfix decrement, three
  interpolation-duration members (including the 22/22 Angle specialization),
  the exact CRT square-root adapter, and all four scalar trig wrappers as
  natural cdecl ScalarMath calls. The newly added asin/acos wrappers each
  replay 35/35 bytes with their original CRT import relocations. Opcode 0x24
  now calls the exact 88B cdecl `polar_components` helper; both independent
  output pointers and the original float-cosine/float-sine relocations match. The stack frame is now `0x85c`
  versus the original `0x804`, down from the previous `0x874`.
- The eight exact color/fade/vector leaves and all eight coordinate-normalizer
  calls are bound through typed owners; the normalizer independently replays
  95/95 bytes. The 59B Timer unscaled fractional-advance leaf is now
  59/59 exact and called as `timer_4c8.add_unscaled`. The Angle interpolation
  duration specialization is independently 22/22 exact; both Timer postfix
  decrement call sites and the three duration writes now use real C++ members,
  and opcode 0x20 uses the existing exact 35B CRT sqrt adapter. This latest
  Timer/interpolation pass removed 136B/17 instructions from the 41,048B
  checkpoint and shrank the frame from 0x874 to 0x85c. The follow-up math
  owner pass removes another 100B/17 instructions from the 40,912B candidate.
  The follow-up polar helper removes another 4B/1 instruction from 40,812B. Opcode scratch values
  now use real Color3, Vector2, Vector3 and Angle objects. Both corner paths use natural Vector3[4] arrays, and
  their compiler-generated 56B array helper is byte-identical to original
  0x0040BC20. This corner-array recovery grew the candidate by 220B from the
  preceding 40,836B checkpoint; it restores real source-level lifetimes,
  not an optimization or an exactness claim.
- The candidate still has 210 DIR32 relocations versus 55 original PE
  HIGHLOW fields and a larger stack frame (`0x85c` versus `0x804`). Its total
  contribution is +1,338B (+694B code plus the switch table); it has 177 fewer
  code instruction heads than the original. It is explicitly NONEXACT, has
  no exact match unit, and is not counted as a new exact function. No
  assembly, NOP padding, dummy accesses or byte fillers. Next work is strict
  frame/data relocation and ordinary-byte reconciliation.
