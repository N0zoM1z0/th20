# Item main-function evidence

## CORE-105: complete primary-spawn candidate

The current target remains the locked Japanese v1.00a Steamless executable.
The maintained checkpoint remains CORE/EXACT-104: 747 canonical units in 143
objects, 140,553 disjoint compared bytes and 253 source files. This investigation
adds no production source, mapping, canonical unit, authored or reference credit.

The complete 1,576-byte primary spawn at 004C3C90 and 815-byte draw at 004C38D0
are present through their final returns in the retained CORE104 native export.
Fresh bounded Ghidra decompilation and callee queries independently re-attest
the target/database. Decompiled types and reference source remain hypotheses.

The private spawn uses complete maintained Item, ItemInf, Session, PlayerRecord,
BulletController, Animation and AnimationFile storage. A complete 0x38 Weapon
receiver candidate has two real Timers and its thirty-slot virtual interface;
the uncalled reference virtual signatures remain hypotheses. Its byte setter
is independently observed to write +0x35, not +0x34. No empty receiver facade or
raw prefix allocation substitutes for the owner. The actual passive Weapon
pointer is Overlay+0x34, not a byte at that offset.

The two Record getters (21/18 bytes), actual Overlay pointer getter (17 bytes),
Weapon byte setter (22 bytes) and Animation packed-color setter (25 bytes)
have whole private zero-difference replay against independently observed native
bodies. This does not admit their owner semantics or any canonical unit.
The complete 128-byte script table at 005AFD50 and three float payloads are
independently checked; relocation destinations are not solved from root fields.

Natural full spawn trials are 1,570, 1,582, 1,574 and 1,577 bytes under the locked x86
/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:strict /sdl /EHsc profile. Branch-local
returns and forwarding the caller's type explain real storage/control-flow
differences. The third trial's instructions agree after diagnostically omitting
two native NOPs and normalizing branch destinations by instruction index; that
normalization is not exact byte comparison. Narrowing the genuinely used Weapon
and Animation borrow scopes produces the two NOPs but also an extra scope-entry
NOP. The current fourth trial is still whole nonexact against 1,576;
no padding, inert local, fake return or shortened comparison hides the mismatch.
The public pointer interface versus private const-reference interface has the
same machine argument width, but source spelling and consistent caller migration
remain separate gates. No portable semantic or original-runtime acceptance is
claimed for these private trials.

## Native protocol observations

- Type-one bonus spawning consumes the process RNG for y before x, sets the
  passive Weapon byte and recursively forwards the request with delay+16.
  Counter arithmetic preserves the original 32-bit modulo behavior.
- The special branch tests five equalities for types 9 through 13. It records
  generation before detaching the node and uses descending delay thresholds
  1024, 512 and 256. The first-member link belongs to a standard-layout Item.
- Ordinary spawning calls the first node's value getter without first testing
  whether the list head is null. The reference's safe empty-list return is
  different behavior. An available ordinary head is a native precondition.
- Type fifteen accumulates mode+1 before threshold conversion to type two.
  Type fourteen converts to six. The original does not throw for a negative
  table index; valid ordinary indices are a separate execution precondition.
- The x clamp skips both assignments for unordered comparisons, preserving
  NaN. The reference's `if (x > -192) ... else ...` changes that behavior.
- Both ANM bindings obtain the actual BulletController file through Context.
  Effect creation at zero delay remains a genuine unresolved gameplay call.

These are observed ordering and argument contracts. The meaning of unnamed
fields, live owner publication, bonus recursion under observers, complete ANM
binding/effect execution and gameplay runtime remain open.

## Draw dependency boundary

The update callback tests GameController's bits zero/two suppression, then bit
eleven. Both draw callbacks instead call 00485AE0, a getter of bit two only;
substituting the update predicate would change behavior. Animation activity at
00445AB0 returns a full integer register, not merely a boolean byte. The native
draw repeatedly obtains node values and copies real Item positions into both
Animations before choosing the primary/secondary draw path.

The renderer factory allocates 0x7D40E94 bytes. Bounded constructor evidence
establishes the real Worker, two Animations, three lists, 65,536 pooled slots,
42 file pointers, a matrix, four corners, 1,048,576 textured vertices and
65,536 colored vertices. Some intervening storage types and its ownership
protocol are still unresolved. The reference's byte storage and explicit gap
at +0x6000DFC are not sufficient production type evidence. No fabricated renderer
prefix or arbitrary padding is introduced to make Item draw compile.

Next work is the full spawn emission discrepancy and actual dependency
semantics, followed by renderer storage/ownership and the complete draw/update
protocol. Original source syntax, RTTI, full linkage and game startup/runtime
remain separate from private byte comparison.

## Private evidence and retirement

Use the ignored CORE105 main/callee/renderer/ABI Ghidra exports and attestations,
the current private header closure and `core105-primary-v4-report.json`.
Original v1/v2/v3 trial inputs and receipts are archived before their object
pairs are retired. `core105-retired-primary-inputs.json.gz` retains their exact
source/receipt envelopes and the hashes needed to reproduce every legacy archive
byte for byte. Redundant SDK text is recovered from the protected installed
headers, with original-file and normalized-text hashes both checked. Original
tool bytes, rather than normalized text copies, establish receipt freshness.
Periodic cleanup preserves current canonical pairs, native exports, archived
inputs, active candidates, original game/reference and installed tools.
Cleanup replays existing objects at reduced priority; it does not cold-build
an unchanged source graph. No completed proof writer is overwritten.

All 68 public tests pass in 213.961 seconds. The periodic retirement removes
nine files/208,194 bytes and preserves all 747 existing-object results. Final
retirement compacts the trial archives, removes the replaced third object pair
and regenerated caches, and preserves all 747 strict existing-object results.
Together both passes retire 85 files/1,490,179 gross bytes and save 1,313,723
bytes after the 176,456-byte compact archive. All 286 canonical object/receipt
hashes, 253 source hashes and 6,017 retained evidence/product hashes are unchanged.
Private
Ghidra evidence, current fourth trial, canonical pairs, game/reference and tools
stay protected; source and coverage remain unchanged.
