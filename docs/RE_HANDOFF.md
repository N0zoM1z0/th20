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
| Functions with provisional source mapping | **1,627** rows; includes unaccepted and excluded mappings |
| Source-present / implemented | **1,613** functions |
| Canonical exact units / compiler objects | **1,610** units / **456** protected MSVC objects and receipts |
| Credited game-authored whole exact | **797** distinct original heads / **269,557** `.text` bytes |
| Full playable game | **Not yet built, linked or runtime-validated** |

These figures are a checkpoint, not counters to update by hand. The
[original game exact ledger](../config/matches.csv),
[complete unit manifest](../config/match-units.toml), and
[function/source ledger](../config/functions.csv) are authoritative. Recheck
live progress with `scripts/repo-python scripts/report-reconstruction-status.py
--summary`. Authored game credit excludes compiler/STL helpers, duplicated
folded implementations, and post-`ret` switch/padding data.

## Recently closed whole-native work — do not reopen

- **Window frame scheduler Boss** 0x004193E0 now has [complete compiled source frontier](WINDOW_FRAME_SCHEDULER884_FULL_SOURCE_FRONTIER.md): 884B/239 native vs 890B/240 candidate, with all 32 E8 target roles and 21 PE data roles in native order (12/32 E8 and 6/21 data physical offsets aligned). Parent NONEXACT, zero byte credit; distinct 31B RepeatCounter, 346B clock and 32B frame dispatch children stay exact. Only source-local compiler probe, no full cold replay.

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
