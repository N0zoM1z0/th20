# TH20 reconstruction — current handoff

## Start here

The next reconstruction task is origin/boundary review, before further native
matching. This handoff and cleanup change no native source, compiler input,
ledger, profile or exact acceptance. Exact replay scope is **zero units**.

Read [AGENTS.md](../AGENTS.md), the selected owner's focused note in the
[evidence index](EVIDENCE_INDEX.md), and the complete live Git status. Use
**`gpt-6.1-sol:`** for checkpoints and `scripts/repo-python` for repository
Python. Keep heavy jobs serial at reduced priority. Ghidra work goes through
`scripts/ghidra.py`; do not use REA or IDA. Documentation/cleanup needs diff,
link and protected-hash checks, with no compiler, Ghidra or cold replay.

## Target and live status

Preserve the Japanese TH20 v1.00a Steamless target, `resources/th20.exe`,
1,858,560B, SHA-256:

`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`

Its embedded title/replay label is 1.00c; both observations describe this same
locked file. Keep the supplied Steam-original backup as provenance. See
[target provenance](TARGET_PROVENANCE.md). A playable reconstruction has not
been built, linked or runtime-validated.

Read current counts from the canonical ledgers, without copying old totals:

```bash
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The README SVG measures exact coverage of the confirmed authored-byte set.
Library/compiler exclusions, source presence and exactness remain separate.
Keep `config/claims.csv` header-only. Do not edit old receipts to manufacture
freshness or replay an unchanged native graph for documentation.

## Current origin/boundary investigation

The last completed review is
[cookie checking and failure reporting](CRT_SECURITY_COOKIE_FAILURE_ORIGIN_REVIEW.md):
five complete contributions, 526B/124 instructions, four REL32/fifty-eight DIR32
roles and 872B cookie/report data. The original fastcall/cdecl distinctions,
tail attribution, partial context writes and emitted epilogues remain intact.
The external PDB type server is unavailable; installed declarations and native
sequences supply ABI evidence. Private proof is in
`.analysis/origin-boundary/security-cookie-check/`. Reuse secchk.obj in
`catch-transfer/` and gs_cookie.obj in `seh4-dispatch/` rather than extracting
copies. Cookie initialization was already reviewed at `0x00543CD2`.

The next **unaccepted** candidate is `0x00542A0F`, 35B. The newly retained
attested listing in `.analysis/origin-boundary/runtime-542a0f/native.txt`
shows a deleting-destructor pattern: ECX is this, the vptr becomes `0x00597124`,
`flags & 1` selects `0x0054278D(this, 12)`, and EAX returns this with RET 4.
No class/member identity or origin has been accepted. Resolve the vtable,
size-deallocation callee and adjacent nine-byte candidate at `0x00542A01`
using independent runtime evidence before assigning names or ownership.
This investigation has no public source/ledger changes to recover.

Completed comparison, lowio, exception and math reviews are indexed in their
focused notes. Reuse original member paths, complete comparisons and retained
negative signatures. In particular, `tail-566ed0/` retains full powhlp/fpclass
proof; its pooled constants remain observed instances rather than new
canonical anchors. The standalone inttype, other ieeemisc bodies and separate
report_securityfailureEx have no whole signatures. Revisit such misses only
with new caller/compiler evidence.

## Native frontiers after origin review

- **Player state:** `src/PlayerStateFrame4043.cpp` covers the 4,043B owner at
  `0x004F7430`, its NOP and seven switch pointers: a 4,072B contribution.
  All ordinary bytes agree, but independent relocation bindings remain open.
  The zero Vector3 at `0x00572664` has only this root's known reference.
  Thirteen physical accessors are exact; the 68B Angle origin remains under
  review. The separate 663B death-entry owner at `0x004F8420` is another
  frontier. See [state frame](PLAYER_STATE4043_NATIVE_FRONTIER.md) and
  [accessor ABI proof](PLAYER_STATE_NATIVE_ACCESSORS_STRICT_EXACT.md).
- **Animation Draw:** native is 5,993B/1,501 instructions. Current retained
  source build is **5,977B/1,497**, with the correct **0x204 frame**, 84/123
  physical E8 sites and 23/32 HIGHLOW site/target pairs. The first-result
  stores and frame discrepancy are closed. Four register-source scalar
  reloads account for the remaining 16B deficit. It remains NONEXACT.
  Use [the current scorecard](ANIMATION_DRAW_BOSS_C2_DEBUG_TRACE.md#2026-11-27-current-parent-scorecard-after-first-result-local-recovery).
- **Particle Update:** native is 2,884B/768; current retained source build is
  **2,888B/770**, with the native **0x19C frame**, 99/99 signature-checked E8
  destinations and 25 data roles. Four-byte local-slot displacement and
  x87/SSE materialization remain open. The old 2,875B prefix-Timer candidate
  matched only 98/99 actual destinations. Preserve the corrected postfix
  `Timer::operator++(int)` ABI. See [current source](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md)
  and [Timer/lifetime findings](ANIMATION_PARTICLE_GRID_UPDATE_2884_ESI_POLAR_LIFETIME_CONVERGENCE.md).

Player main/movement, Glyph compositor/text core, Card start/finish, polygon
updater and rotated projection already have whole exact proofs. Historical
NONEXACT notes do not reopen them. Other large parents remain in
[the backlog](RE_OPEN_BOSS_BACKLOG.md). Source navigation, architecture and
workflow each retain their own documentation role.

## Protected products and useful compiler contexts

Preserve the target, `../game_exe/`, pinned `.tools/`, game-specific Wine state,
`ghidra-project/` and Factory runtime configuration/cache. Current canonical
objects/receipts come from `config/match-units.toml`; this cleanup also retains
all existing canonical directories and the 2,151-file protected baseline.
Do not infer current acceptance merely from an old directory's name.

Keep the private Player sessions and corrected-ABI parent in
`build/gpt61-player-state-abi/`, plus the Player canonical products. Keep math
binding correction products in `build/gpt61-origin-tangent-canonical/` and
`build/gpt61-origin-tangent-{before,after}/`; the corrected native bindings
and affected replay are in [the focused proof](CRT_X87_CONTROL_TANGENT_ORIGIN_REVIEW.md).

For Draw/C2, retain `.analysis/draw-boss-session/`,
`.analysis/gptweb-particle2884-owner-lifetime/` (the historical directory name
also contains Draw controls), `build/gptweb-drawboss-session/`,
`build/gptweb-particle2884-owner-lifetime/`, the C2 trace/VCTIP/debug products
and `build/gptweb-probe/`. The first-result object and its receipt retain the
current source fingerprint. Particle's current object/receipt are
`build/gptweb-particle2884-probe/ParticleUpdate2884Research.*`.
Retain `build/core835-probe/` for its source verifier, and useful origin
compiler probes in `build/gpt61-origin-{locale,allocation,exception-copy}/`.

Private source, focused attested exports, failed ABI inputs and useful debug
metadata remain available. Rebuildable compiled matrices, obsolete invocation
exports and old runtime logs have been retired. Git objects were packed with
pruning and reflog expiration disabled; history and references are retained.
No historical receipt or native acceptance was rewritten.
