# Whole Enemy creation, initialization and script selection

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

## Preserved nonexact work

The complete 00496FB0 opcode spawn entry is 653 bytes. Its natural probe has
that complete size, but fourteen non-relocation bytes differ because two float
loads and stack reservations exchange order. Byte/reference/const operand
forms and precise/fast/except profiles do not resolve it. The probe stays
private and pending; no partial opcode or dispatcher credit is assigned.

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

Cleanup retired 43 obsolete object/receipt artifacts / 1,153,194 bytes, with all
186 canonical hashes unchanged and 500 post-cleanup strict replays passing.
Cumulative retirement is 2,089 files / 70,300,517 bytes. Private
core066-cleanup.json records every removed path and byte count. Native exports,
rejected source/diagnostics and all supplied/reference/tool inputs are preserved.
