# Entity opcode, adapter and fixture review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## REF-040 — 2026-10-07

All **243** scoped reference implementations were individually read across
**22 indexed files**. This includes animation and creation cases, state,
queued shots, lasers, miscellaneous instructions, the entity dispatcher, all
five adapter families, their interface headers and six CPU-case files. Nested
lambdas, same-line definitions and annotation-recovered endpoints have their
own original CRLF body hashes and decisions. The common reader, opcode data
header and retained entity-opcode narrative were also read.

Decisions are **26 nonexact / 217 support**. No new canonical implementation
is accepted: the small introduced transports and combined case helpers do not
have independently established native function boundaries, and genuine native
members still need their real enclosing owners and call protocols. Existing
value implementations are reused without inventing another exact unit.

Global coverage is **5,931 terminal / 1,013 pending** of 6,944 implementations.
Gameplay has **169 pending**. Five grammar files are manually reconciled,
bringing parser-gap coverage to **91 complete / 22 pending**. The exhaustive
review goal remains active; this batch closes individual review of these files,
not their game behavior or original dispatcher equivalence.

## Native dispatcher and complete diagnostics

The locked PE independently establishes the original `48C010` member entry,
its State receiver, EH/aligned-frame setup, signed opcode load and default
epilogue at `4963DF`, which clears the full EAX result. The dispatcher uses:

| Native data | Address | Entries |
| --- | --- | ---: |
| Primary jump table | `0x00496400` | 174 |
| Opcode-to-slot byte table | `0x004966B8` | 704 |

All table bytes and destinations were independently checked. Exactly **224**
opcodes select a nondefault entry: 300–344, 400–448, 500–575 except 569,
600–633, 700–714, 800–802 and 1001–1003. All other values within the indexed
range select the default; the entry's bounds check covers values outside it.
Table destinations remain inside the original provisional code range. This
does not close each case's shared control flow, EH, globals and lifetime.

The reference splits that large member into optional-int free handlers,
convenience wrappers and a routing function. It adds explicit Services,
checked arrays, helpers and error paths. None is a standalone original handler
with the same complete extent. Diagnostic comparison against the provisional
41,967-byte dispatcher never truncates a contribution or accepts a case prefix.

Eleven actual reference production translation units freshly compile from the
unchanged maintained source freeze. Their full COFF inventory has **1,134
defined functions / 196 static functions**. **27 complete comparisons across
26 mapped bodies** all differ in length. Those include both queue accessors
represented by one combined reference helper. There are no structural matches.
Older unrelated reference receipts remain historical until rebuilt.

The existing **175 canonical units / 50 objects / 12,236 disjoint complete
bytes** retain fresh source/profile/object receipts and all replay exact.
Maintained `src/`, probes, compiler profiles and anchors did not change in this
batch, so the prior cold objects remain valid. Source presence 175, pending
origins 114, library 4 and authored 57 / 4,074 bytes are unchanged.

## Individual implementation findings

Animation creation preserves capacity and selected-boss gates, variable-size
names with logical argument masks, mirrored/relative position variants, parent
selection, the 84-byte spawn payload, named ANM calls and script/handle changes.
Native `496FB0` returns full integer zero; the reference void Reader/Services
function has a different ABI. `496B90` handles fourteen ANM mutation cases,
including BGR starting color order, byte masks, interpolation/Timer setup and
layer/flag operations. Original Animation, vector and member ownership remain
unclosed despite prepared scalar comparisons.

State operations preserve fifteen-kind/sixteen-count distinctions, health and
phase updates, boss slots, waits, clocks, rewards, encrypted spell names,
difficulty variants, Card/HUD writes, cleanup, fog and death/defeat boundaries.
Native phase methods `4AB650/4AB780` use the enclosing **Enemy receiver** and
its vector at `+340`, returning with `RET16/RET8`. Their three-argument copy
calls pass capacity 64 to `548610`. Reference State/free functions introduce
checked growth and length exceptions. Bounded-name PMR fixtures do not establish
the original copy routine's invalid-input behavior, complete owner or allocator.
The Player reward at `497CC0` similarly uses the genuine Player receiver and
reference-return clamp helper rather than the free raw transport.

Shot operations preserve initially null metadata, shared aliases, copy-on-write,
ETEX words and script-pointer slot, cursor wrap/clamp, retained offset.z and
metadata padding, absolute-position comparison direction and local output
order. Queue access combines native `498B80` and `498D10` into one helper.
Real control blocks, PMR list/vector growth, EH and member receiver protocols
are still unresolved. The existing typed ShotParameters/BulletCommand values
do not establish a complete queued-owner implementation.

Laser operations build all four parameter kinds and command vectors, handle
nullable targets, write concrete offsets even for a different type, and erase
all matching nonzero identifiers with `(0,0)`. Actual Laser vtables, concrete
owners and creation/cancellation lifetimes remain unclosed. Misc operations
preserve selected-target names, X/Y stack aliases, stone attachment ordering
and repeated argument reads, but real script and Special attachment bodies
remain dependencies.

The heavy shot adapters also contain rectangle slowdown/reset callbacks,
callback tables, cancellation, mesh replacement, background event seek and
score composition. Their source code was fully read. Callback table bytes at
`56FE8C/56FE98/56FE9C` independently corroborate null/`488B80`/`488E80` and
two null-only tables; source pointers and virtual Hosts do not establish native
identity. Native `479080` is a Player member setter at `+20EC`; a global raw
setter cannot restore it by introducing a padded Player facade. Full-int zero
callback returns, observers and actual Player/ANM/Bullet owners remain open.
Ten focused native helper ranges fully PE-decode with closed direct branches;
these rejected diagnostic ranges receive no exact or origin credit.

## Grammar reconciliation

| Entire file individually read | Indexed gap sites | Reconciliation |
| --- | ---: | --- |
| `enemy_opcode_animation.cpp` | 8 | Unsigned casts, shifts and color-member expressions on lines 30, 32, 36 |
| `enemy_opcode_state.cpp` | 9 | Unsigned bit expressions, member accesses and nested conditional/throw expression on lines 39, 48, 110, 111, 121 |
| `enemy_opcode_creation_cpu_cases.inc` | 12 | Six fastcall annotations and ternary expressions on lines 10–15 |
| `enemy_opcode_laser_cpu_cases.inc` | 6 | Six fastcall endpoint annotations on lines 6, 11–15 |
| `enemy_opcode_misc_cpu_cases.inc` | 4 | Four fastcall endpoint annotations on lines 5–8 |

All complete surrounding implementations were already indexed and their
original bytes were individually read. Two additional unnamed missing-semicolon
artifacts in the creation parse are contained in those same fully read bodies;
the established index traverses named nodes and counts twelve sites. No source
was edited, no function was omitted and no grammar label counts as reconstruction.

## Retained evidence and prepared domains

The historical CPU report has **1,254,134 cases / zero mismatches**, with all
105 current source hashes. Its six selected entity-opcode fixture families sum
to **381,824 comparison checks**, including multiple checks per scenario.
The prose entity report still says 1,254,114, predating twenty additional
iterator hazard cases; it does not override the current JSON. The frame report
has 7,682 assertions and all 105 current hashes. Executed binary/compiler/startup
identity remains unbound, and no Windows oracle or report writer was run here.

- Animation scalar cases use 20 opcodes × 800 scenarios and share original
  resolve/layer dependencies. Creation uses 25 × 512 and patches six ANM,
  Effect and Enemy endpoints. Full surrounding bytes/arguments are compared;
  actual allocation, interruption and ANM VM internals are recorded boundaries.
- State uses 53 × 1,024 finite prepared scenarios. Raw HUD/Card/Bullet/Player/
  Game buffers and the bounded pool are compared; heavy endpoints throw and
  HUD collecting is always null. Active waiting, spell/card, resource and
  whole-owner lifetimes do not follow from those cases.
- Shot parameters use 24 × 512 scenarios with actual PMR metadata allocation,
  queue growth, null owners and COW/alias checks. State pointers at08/16C are
  normalized; metadata padding4A/B is excluded. Ten heavy shot-composition
  instructions remain outside this fixture's direct CPU coverage.
- Lasers use 15 × 512 scenarios. Creation, lookup and rectangle calls are
  patched, and a synthetic native vtable supplies three recorded methods at
  slots0/3/17. Vptr bytes are normalized; parameter bytes, command payloads,
  target changes and call order are checked, without actual Laser execution.
- Misc uses six × 1,024 scenarios, bounded names and prepared targets. Four
  clear/reset/select/attach endpoints are patched; script execution and Special
  allocation remain recorded boundaries. Patch fixtures restore mapped bytes
  and cache, but not page protection. They were only read during this review.

The resource report has 3,304 assertions and only 100/105 current hashes; the
same five implementation/test files remain stale. Its recorded GPU boundary
and excluded simulation/rendering scope remain unchanged. No target file or
analysis database was modified. Continue the remaining Gameplay, Sprite,
StageBackground and support batches with individual decisions and natural exact
restoration where the native owner and complete protocol can be established.
