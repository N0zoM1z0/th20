# Game loading, player state and frame review

## REF-041 — 2026-10-07

All **169 remaining Gameplay implementations** were individually read across
**18 indexed files**, including their nested lambdas, inline members, fixtures
and extraction scripts. Original CRLF body and whole-file hashes are bound to
the clean pinned reference. The relevant Session definitions and stage header
were also read. These files have no parser gaps.

Decisions are **3 absorbed / 25 nonexact / 141 support**. The earlier Player
constructor review is upgraded separately, retaining its body hash and review
count. Global coverage reaches **6,100 terminal / 844 pending** of 6,944 bodies;
all **1,019 Gameplay bodies** now have individual decisions. Parser-gap coverage
remains **91 complete / 22 pending**. Sprite has540 pending, StageBackground121,
and other categories183. The exhaustive review goal remains active.

## Natural PlayerRecord batch

The original table constructor at `422F20` passes stride240, count2 and the real
`423050` constructor to the array-construction helper. The complete constructor
initializes actual integer and byte fields through `EC`, with a paired64-bit
zero store at0. Score consumers read both words through `44C090`; the starting
power getter clamps the actual word at38 and writes it back.

An independently written **240-byte PlayerRecord** uses a64-bit score, explicit
integer/byte fields and the compiler's natural alignment. Original names and
some field roles are unknown, so provisional offset labels are retained. The
original gaps `A6/A7` and `B1..B3` arise naturally from member alignment and are
preserved; there is no explicit padding or raw whole-owner facade. Eight-byte
alignment is the maintained value inference, consistent with the table stride
and surrounding aligned storage, rather than proof of the original declaration.

| Complete contribution | Address | Bytes |
| --- | --- | ---: |
| PlayerRecord constructor | `0x00423050` | 712 |
| 43 distinct integer/byte setter heads | Manifest lists every address | 2,859 |
| 64-bit score query | `0x0044C090` | 19 |
| Mutating starting-power query | `0x004B81D0` | 64 |

These **46 new canonical units add3,654 disjoint complete bytes**. All45 setter
semantics have natural member implementations, but `41DF50` and `412D10`
already have canonical Interpolation and FunctionChain owners. Their identical
code does not establish a unique original type; they receive no second unit or
byte credit. The reference's descriptor-based free helper is still a different
contribution; it is absorbed through the individual independently restored
members, rather than counted as45 exact source functions.

Every native range fully PE-decodes and agrees with attested Ghidra output.
The45 setters independently confirm their actual destination width/offset,
signed clamp constants, original `RET4`, and reference-returning clamp calls
to `471170`. Native call evidence precedes the bulk probes; relocation fields
are replayed using that anchor, without solving target comparison fields.
The installed MSVC profile remains a candidate, not a global original-build
claim. Original spellings and authored/compiler/library origins remain pending.

The final source freeze passes a **221/221-unit cold canonical replay from51
objects**, covering **15,890 disjoint bytes**. Source presence221, pending
origins160 and library4 are separate from authored57 /4,074 bytes. Portable
C++20 with UBSan passes **24,080 independent checks**: dirty guarded
construction/defaults, setter boundary and random full-byte preservation,
mutating power and full64-bit score. No original Windows oracle was rerun.

## Whole owners and complete reference diagnostics

Eight actual, unmodified reference production translation units were freshly
compiled serially after the maintained source freeze. They define **486
functions /127 static functions**. **71 complete diagnostic comparisons across
27 bodies** yield69 size differences and2 structural matches: Game restart
`488830/20` and clear-bit6 `4BD920/32`. The full Game class still adds a Services
pointer at110 and has unresolved original base/vptr/Configuration/EH/lifetime;
those structural matches receive no canonical or exact credit. Contributions
were never shortened to target-sized prefixes. Older unrelated reference
object receipts are stale until rebuilt after this new source freeze.

The Game constructor owns a real callback base, two Timers, Configuration,
double fields and a debug-string dependency. Loading owns recursive-lock6
guards, old-worker detachment and a new thread whose closure observes the
current global Game when it runs. Teardown repeatedly queries shared scene
state after dependent calls; it preserves progress/clock/surface, retained/full
owner cleanup, callback removal, music gates and final-color ordering. Source
recorded Services tests do not establish original destructor or thread graphs.

The complete load flow preserves repeated profile queries, current-player
selection, fresh/restart/Spell/Extra branches, two Player resets, save score and
availability offsets, meter/lives/bombs, twelve ordered factory failure prefixes,
callbacks/config/background variants, retained Replay/HUD/Enemy owners,
progress/music/stats/audio/effect waits, display completion and double Session
clock updates. Real save, resource, allocator, HUD observer, worker and factory
lifetimes remain dependencies. Natural value setters do not close the original
bomb update or reset protocol; the historical Player fixture always nulls HUD.

The frame flow preserves counter wrapping/clamping, pause/loading/exit/demo
gates, HUD score, four ANM calls, input/slowdown/Timer updates and real Screen
allocation. Its prepared fixture excludes age0/30 activation, a nonnull secondary
Background and the final Replay branch. Scheduler snapshots replace every word
equal to an identified pointer/vptr/callback, potentially normalizing a scalar
that coincidentally has the same value. Draw checks cover Sprite prefixE0,
rather than the complete owner. These limits remain explicit.

## Static data and retained evidence

All eight308-byte stage rows were independently checked against the locked PE:
**448 scalar words,168 nullable ASCII pointer slots**, and **18 difficulty
constants**. Selection's added bounds exception differs from native out-of-range
behavior. The Stage4 character-pair background selector is extracted from
`4BAD40`, not an independently bounded original function. Both extraction
scripts were fully read; their source/evidence writers were never executed and
their generated code was not imported into maintained source.

| Historical report | Checks/assertions | Current source hashes | Limits |
| --- | ---: | ---: | --- |
| Game CPU | 107,522 | 2/2 | Zeroed constructor with normalized vptr; flags/getters and paused wrapper only |
| Player CPU | 58,025 | 12/13 | Entry adapter stale; HUD forced null; prepared raw records and valid stage indexes |
| Loading | 40,345 | 12/13 | Entry adapter stale; source-only recorded external owners |
| Frame | 225,280 | 389/389 | Prepared domains, pointer normalization and Sprite prefix noted above |

The frame report's shared Sprite CPU report digest and2,915,831 total were
also independently verified. These numbers include several checks per scenario;
they do not represent complete whole-game executions. No Windows fixture,
report writer, original target patch or analysis-database mutation was run.
Executed test binary/compiler/startup identity remains unbound for the retained
reports. The newly maintained PlayerRecord has its own fresh canonical and
portable evidence, distinct from those historical fixture results.
