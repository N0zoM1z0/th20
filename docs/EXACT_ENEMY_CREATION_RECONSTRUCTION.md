# Whole Enemy creation, initialization and script selection

**Later [CORE/ORIGIN-706](ENEMY_ECL_LIFECYCLE_762_ORIGINAL_GAME_EXACT_ORIGIN.md):** the entire original 155B EnemyController::create and 222B Enemy::initialize methods are independently game-authored strict native exact, with original direct Enemy creation to initialization E8 and original large-dispatch call witnesses. Other historical review status below predates this game ownership admission.

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-066 adds nineteen whole functions / 1,279 instruction and comparison
bytes. The frozen source graph has 500 units / 93 objects / 90,121 disjoint
comparison bytes. New origins stay pending: 427 pending / 9 library / 64
independently authored contributions, with 16,948 authored bytes unchanged.
Complete canonical relocation replay is required for every credited body.

## Native observations and actual owners

The 155-byte 004A8920 controller member uses the process allocator's named
scalar factory, initializes the actual Enemy, appends its real parent link when
requested, applies the original 84-byte EnemySpawn, prepends the controller link
and increments its count. There is no capacity gate in this function; the
unclosed opcode entry owns that separate gate. The allocation label is the
original native diagnostic string at 00570420, including its source path and
line, rather than an invented pool name. Production scalar factory emission,
allocation failure handling and compiler pre-construction clear remain pending.

The 222-byte 004A73F0 Enemy initializer resets its inherited EclManager, selects
context through the native unresolved interface, sets State's entity, runs the
already reconstructed State initialization, resets both detached intrusive
owners and clears the real std::function callback. It takes the controller's
generation, advances the process generation and selects a script through the
controller's EclLoader. The whole 147-byte 004972C0 inherited script reset uses
the actual runtime, stack, interpolation vector and intrusive runtime link.

Two generation words are independently observed at 005C49F0 and 005C49EC.
The complete 98-byte advance saves the old word, increments and masks the low
16 bits, skips zero and ORs the controller's player index into the upper half.
The maintained shift converts to unsigned before shifting. Global production
initialization remains unresolved. Actual count and capacity getters preserve
the signed interpretation used by the opcode entry.

ScriptStack's full 61-byte reset clears pointer/frame base and the PMR words,
then **reserves 256 words**. It keeps size zero and retains an existing larger
capacity. The independent whole 0049C220 callee proves reserve; a resize
hypothesis produces the same caller shape but has a different symbol/behavior
and is rejected. Clear at 00497F40 is shared by the actual trivial element
vectors. Dependency emission/ownership is not extra exact credit.

EclLoader's complete 144-byte binary lookup uses its count and actual eight-byte
records, a signed midpoint and bytewise case-sensitive strcmp at 0054FD10.
The whole native comparison routine corroborates unsigned byte ordering and
zero termination. The original lookup returns an encountered matching midpoint
or -1; sorting/count/lifetime are caller preconditions. The natural else-if
chain reproduces the compiler's unreachable two-byte jump as part of the full
contribution. No boundary shortening removes it. Complete 66-byte selection
binds the loader, resolves the subroutine, sets offset/time zero and returns
zero even for a missing name. The distinct earlier activate protocol is retained.

Enemy's complete 30-byte identifier getter returns the actual Identifier32
value through the native hidden result pointer, rather than a fabricated
uint32 return. Four complete Enemy/State value forwarding methods preserve
logical operand indexes and the supplied raw values. Their runtime callees
are the **non-consuming** 0053EA90 / 0053EE30 protocols, distinct from the
consuming helpers used by ECL calls. Fresh complete native callee exports
prevent an incorrect shared anchor/name despite equal wrapper byte shapes.

The controller's script_loader getter emits a complete 20-byte contribution
identical to the already credited 00415800 Graphics getter. Both real owners
have a four-byte member at +0x104. Its whole independently bound folded alias
replays, but receives no duplicate byte/unit or unrelated reference credit.

## Maintained implementation and validation

EnemySpawning.cpp, EnemyInitialization.cpp and EclSelection.cpp supply the
actual member bodies. EnemyScript and ScriptStack extend their existing
profiles and canonical owners. Header declarations retain pending production
interfaces; no placeholder Session layout, fake callback/vtable, assembly,
byte blob, inert local or compiler-header patch is introduced.

Owned C++20/O2/UBSan tests exercise complete creation/initialization, parent and
controller links, ordering, identity, generation wrap/zero avoidance/player
encoding, signed getters, binary lookup endpoints/misses, missing selection,
script reset and retained flags/rank/capacity. Fixtures cover only unresolved
pool/startup/controller/context lifetimes and the complete spawn application
boundary. The animation test additionally exercises actual supplied-value
forwarding and Identifier32 copy isolation. These tests are not a claim of a
linked/playable whole game or real pool/Session runtime behavior.

Frozen-source cold compilation covers all 93 unique objects serially at reduced
priority. Existing 90 objects are rebuilt once; the three newly configured
objects are then cold-built once and all 500 units strictly replay. This staged
receipt set is one complete frozen-source batch, not a reused old-source result.
All 40 public tests, tracking/progress and source checks pass locally. The exact
pushed GitHub head is checked separately.

## CORE/RECON-1263 — whole 653-byte opcode-spawn Boss strict exact

The complete `0x00496FB0` `EnemyState::spawn_from_opcode()` function now
strictly replays all 653 bytes from natural C++, including all 19 original
relocation destinations and all 577 ordinary bytes. The explicit identity
float casts in `SPAWN_FLOAT` reproduce the original outgoing stack-slot
reservation before both X/Y operand loads; they do not add instructions or
change the value. The complete native body has 192 x86 instructions and 17
ordered direct calls. See the [full native and canonical COFF proof](ENEMY_SPAWN_FROM_OPCODE_653_STRICT_EXACT.md).

The 41,967-byte dispatcher routes native case-zero opcodes 300/301/304/305/321
to this Boss. It performs the EnemyController capacity guard, parses the
padded script-name payload and per-operand defaults, applies relative/mirrored
position and spawn-flag rules, copies EnemyCounters and source Enemy identity,
then calls the existing `EnemyController::create` path. Native case six covers
309/310/311/312 through the exact `EnemyController::selected(0)` leaf; only an
empty slot branches to this same spawn Boss. The whole dispatcher remains
NONEXACT and receives no parent byte credit. Original source origin remains
unknown, so no authored-origin byte credit is claimed for this exact function.

## CORE/RECON-1197 — exact opcode-303 animation creation

The adjacent native case-2 opcode 303 operation at `0x00496A00` is now
implemented as `EnemyState::spawn_animation()` in
`src/EnemyStateAnimationCreateOpcode.cpp`. Its complete 398-byte body and all
18 original relocation destinations strictly replay. It grows the PMR
`EnemyAnimationLink` vector, retires the selected prior handle, resolves the
controller AnimationFile using `field_1c`, and calls `spawn_flag2` with the
second integer operand and `field_34 + 7`. The script operand is read again
for the spawn call and, for index zero, once more for `field_24`; these are
three distinct native evaluations. The primary animation then supplies height
and width for `vector_170`.

The same dispatcher table also has two related inline animation-create
operations, now restored in `src/EnemyStateAnimationCreateOpcode.cpp`: opcode
306 takes its script from integer operand 1 and, for link zero, publishes the
secondary animation identity/flag fields; opcode 313 takes its script from
`field_28 + 5`. Both replace a PMR `EnemyAnimationLink`, create via
`AnimationFile::spawn_flag2`, refresh the primary dimensions for link zero and
conditionally clear recursive flag 0. The 306/313 paths do not share opcode
303 negative-script guard. These are inline regions of the large dispatcher,
not separately bounded native functions, so they receive semantic progress
only and no independent strict-byte credit.

The 50-byte native `0x00450120` helper is also strict exact in
`src/EnemyAnimationLinkClearFlag.cpp`: it resolves the link leading handle
through `current_animation_pool` and clears Animation flag bit zero recursively
only when a live animation is found. The maintained method is attached to
`EnemyAnimationLink`, whose first member is the handle; the original source
class name is not asserted. Both new functions are strict whole-function
matches; their original source-origin records remain unknown, so they are not
entered as authored byte credit.

The focused `/Od /Ob0` strict one-function comparison reproduces the 653-byte
extent and all 19 relocation fields resolve to their original native
destinations. It reports 639/653 bytes matched after relocation replay; the
non-relocation view is 563/577 bytes. The remaining 14 bytes are exactly the two
7-byte argument-setup sequences at offsets `0x86–0x8C` and `0xA5–0xAB`, where
the native reserves the float argument slot before its `movss` load and the
natural probe performs the load before the slot reservation. Direct, const,
reference and volatile operand forms did not resolve this compiler scheduling
difference. No assembly or padding is used. This is maintained semantic source
progress only: the function is still NONEXACT and receives no strict exact or
accepted-fact credit until a natural-source exact comparison passes.

Scalar factory 004A2910 calls a compiler pre-construction clear before the
actual Enemy constructor. Clean scalar-new probes currently omit that clear.
The whole 780-byte 004A89C0 spawn application depends on unclosed Session /
difficulty / stage interfaces and update ownership. No fake Session facade is
added. Whole list prepend also retains a pointer-comparison emission difference;
its natural semantic body is tested, but no helper exact credit is assigned.

Fresh runtime supplied-value probes have the correct literal/local/stack/virtual
protocol but omit nine bytes of the native virtual target materialization.
The consuming helpers cannot replace them. A guard experiment requires missing
guardcfw.h and is rejected without changing compiler headers. These private
probes remain pending; their bodies are not imported into maintained source.
The whole 41 KB 0048C010 dispatcher, laser/callback ownership and whole-game
link/runtime remain open. Native exports and rejected source/diagnostics stay
in ignored .analysis; obsolete object/receipt artifacts are retired separately.

At this checkpoint all 500 units strictly replayed. Native exports, rejected
source/diagnostics and supplied/reference/tool inputs remain available for
further reconstruction.
