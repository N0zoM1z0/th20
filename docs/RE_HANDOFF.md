# TH20 reconstruction — current handoff

## Start here

Read [AGENTS.md](../AGENTS.md), then this page, then the focused note for the
owner you pick from the [evidence index](EVIDENCE_INDEX.md). Inspect the
complete live Git status first. Use the commit prefix the user gives for your
session and `scripts/repo-python` for all repository Python. Keep compiler,
Ghidra and replay jobs serial at reduced priority (`nice -n 15`). Ghidra work
goes through `scripts/ghidra.py`; do not use REA or IDA.

This handoff checkpoint changed documentation and pruned ignored artifacts
only. Its exact replay scope is **zero units**.

## Target and live status

Preserve the Japanese TH20 v1.00a Steamless target, `resources/th20.exe`,
1,858,560B, SHA-256:

`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`

Its embedded title/replay label is 1.00c; both observations describe this same
locked file. See [target provenance](TARGET_PROVENANCE.md). No playable build
has been linked or runtime-validated.

Read counts from the ledgers instead of copying them:

```bash
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

At this checkpoint the ledger reports 1,080 exact functions (332,504 bytes)
of 7,078 inventoried candidates; 5,041 candidates still await origin review.

## Recent work

The 2026-11-28 session added 108 exact functions (+22,217 bytes) in nine
batches, mostly from the Graphics owner's original TU, which the allocation
labels name as `game/mother.cpp`:

- WindowState [screen layout](WINDOW_LAYOUT_RECONSTRUCTION.md) and
  [window creation and window procedure](WINDOW_CREATION_PROCEDURE_RECONSTRUCTION.md).
- Graphics [viewport layout and configuration predicates](GRAPHICS_VIEWPORT_LAYOUT_RECONSTRUCTION.md),
  [frame-chain registration, start-up, clears and surface passes](GRAPHICS_FRAME_CHAIN_RECONSTRUCTION.md),
  and [scene transitions, update node, surface targets and shutdown](GRAPHICS_SCENE_TRANSITIONS_RECONSTRUCTION.md).
- [AnimationPoolOwner draw-chain callbacks](ANIMATION_POOL_DRAW_CALLBACKS_RECONSTRUCTION.md).
- [Laser command steppers and command array](LASER_COMMAND_STEPPERS_RECONSTRUCTION.md).

The code-shape rules that settled these matches are collected in
[the workflow guide](RE_WORKFLOW.md#observed-od-code-shape-rules).

## Next work

1. **Laser family.** About 35 virtuals in `0x004C9000..0x004D8000` are still
   unmatched. Their vtables are listed in the Laser note. The headers have
   include closures of 4 to 27 sources, so iteration is cheap. Start with the
   mid-size slots, then the 2.6–3.8KB update/draw bodies.
2. **Remaining `mother.cpp`.** The 836B configuration loader `0x004DC1C0`
   (EH frame, `std::string`/`std::function` locals) and the 2,537B WinMain
   body `0x0041E7D0` (goto into a loop; about 35 callees, most now declared).
   The window frame scheduler callers of `create_surface_targets_4dbd70` are
   in `0x00419xxx`.
3. **AnimationPoolOwner constructor** `0x00447E00` (2,794B, EH). It needs the
   full owner layout used by the overlay in `src/AnimationPoolDestructor138.cpp`.
4. **Open large parents** stay as recorded: Animation Draw 5,993B (candidate
   5,977B, four register-source reloads open), Particle Update 2,884B
   (candidate 2,888B), Player state frame 4,043B (relocation bindings open).
   See [the backlog](RE_OPEN_BOSS_BACKLOG.md).
5. **Origin review.** The 35B candidate at `0x00542A0F` (deleting-destructor
   pattern, vtable `0x00597124`) has a retained listing in
   `.analysis/origin-boundary/runtime-542a0f/`.

To find work with no new dependencies, list unmapped functions whose direct
callees are already mapped. Calls into still-unmatched inventoried functions
are also fine: bind each REL32 or function-pointer DIR32 to the native call
or immediate target, as 1,400+ existing relocations do.

## Protected products

Preserve the target, `../game_exe/`, pinned `.tools/`, the game-specific Wine
prefix, `ghidra-project/` and the Factory runtime configuration/cache. Every
canonical object and receipt named in `config/match-units.toml` is protected;
`scripts/prune-generated-artifacts.py` (dry run by default) enforces this.

Also keep these private products of open questions:

- Player state frame: `build/gpt61-player-state-abi/` and
  `.analysis/player-state4043-{session,abi}/`.
- Math bindings: `build/gpt61-origin-tangent-{canonical,before,after}/`.
- Origin compiler probes: `build/gpt61-origin-{locale,allocation,exception-copy}/`
  and the open candidate listing `.analysis/origin-boundary/runtime-542a0f/`.
- Draw/Particle: `.analysis/draw-boss-session/`,
  `.analysis/gptweb-particle2884-owner-lifetime/`, `build/gptweb-drawboss-session/`,
  `build/gptweb-particle2884-owner-lifetime/`, `build/gptweb-particle2884-probe/`,
  the C2 trace/VCTIP products, `build/gptweb-probe/` and `build/core835-probe/`.

Tooling reads `.analysis/{architecture,inventory,reference-functions,reference-review,progress,factory-runtime,bootstrap}`,
`ghidra.lock`, the enemy opcode audit JSONs and
`stage-resource-vm-cpu-compare.json`; keep them too.

At this checkpoint, build directories holding only superseded objects were
pruned (830 files, 51MB). Everything else under `.analysis/` was also
removed: historical probes, decompiler exports and the private proofs of
completed origin reviews (about 150MB in total). The CRT objects those reviews
used can be extracted again from the pinned toolchain libraries. Raw Ghidra
exports can be regenerated through `scripts/ghidra.py`.
