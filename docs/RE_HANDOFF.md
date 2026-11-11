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
| Functions with provisional source mapping | **1,601** rows; includes unaccepted and excluded mappings |
| Source-present / implemented | **1,587** functions |
| Canonical exact units / compiler objects | **1,585** units / **439** protected MSVC objects and receipts |
| Credited game-authored whole exact | **776** distinct original heads / **265,848** `.text` bytes |
| Full playable game | **Not yet built, linked or runtime-validated** |

These figures are a checkpoint, not counters to update by hand. The
[original game exact ledger](../config/matches.csv),
[complete unit manifest](../config/match-units.toml), and
[function/source ledger](../config/functions.csv) are authoritative. Recheck
live progress with `scripts/repo-python scripts/report-reconstruction-status.py
--summary`. Authored game credit excludes compiler/STL helpers, duplicated
folded implementations, and post-`ret` switch/padding data.

## Recently closed whole-native work — do not reopen

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
   open. The 2,227B glyph text core now generates the full **2,316B**
   code+22-pointer contribution and correct font-switch alias groups, but
   remains NONEXACT (candidate RET one byte late). [Glyph core switch](GLYPH_TEXT_CORE2227_SWITCH22_NATIVE_CONVERGENCE.md);
   [Current centered frontier](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md);
   [other Bosses](RE_OPEN_BOSS_BACKLOG.md).
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
