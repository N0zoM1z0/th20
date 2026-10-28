# Current reconstruction handoff

CORE/EXACT-182 reconstructs the **entire 263-byte native
`LaserController::reset_all_lasers`** call of Enemy opcode **539**, with
independently decoded 34-slot beam vtables, original iterator EH and all
**14** original relocation targets. Pinned x86 MSVC strictly replays
**263/263** bytes; only the two affected canonical sources were cold built.
All **21/21** affected old/new units (4,148 bytes) replay exactly, and all
**162** unaffected object/source/include receipts remain hash-valid without
recompilation. A real typed LaserController + Laser iterator fixture passes
**601/601** scenarios on each GCC/Clang ASan+UBSan. The maintained graph now
has **1,013 source-present mappings, 1,004 physical strict units, 218 exact
authored functions and 57,271 exact authored bytes**; the 41,967-byte Enemy
boss root is **still not exact**. See
[opcode 539 whole-callee proof](ENEMY_OPCODE_539_LASER_RESET_EXACT_RECONSTRUCTION.md).

CORE181 advances the *same complete 41,967-byte Enemy root* with native
opcode **548** (original 17 bytes / four instructions) calling the now-exact
real `FrontInf::show_stage_title` method, guarded by genuine Graphics mode8
and Session flag5 helpers. The 80-translation-unit whole-root host passes
**38,241/38,241** cases (256 new with 112 captured lower-level Animation VM
spawn calls), including all 37,985 previously verified CORE179 scenarios.
The real 4-arg AnimationFile wrapper and all owner methods execute; only its
original 7-arg Renderer/VM producer is a captured boundary. Private SHA-256
proof records 97 actual input paths, protected CORE179 source/log identities
and 164 unchanged current canonical build receipts. The original Enemy boss
root is **still not machine-code exact**; 217 independently exact functions /
57,008 bytes / 1,003 physical strict units remain unchanged. See
[CORE181 whole-root opcode548 proof](ENEMY_WHOLE_ROOT_548_STAGE_TITLE_INTEGRATION.md)
and `.analysis/core181-enemy-whole-root-proof.json`.

CORE/EXACT-180 reconstructs **three complete real functions** in the
original Enemy opcode548 call chain: `Graphics::field_b0c_value` (20B),
`Session::flag5_value` (23B) and `FrontInf::show_stage_title` (75B), with
all 5 source-independent Graphics/Session/AnimationFile relocations exact.
The actual FrontInf `+0x170` message file spawns only when the original
Graphics mode is not 8 and Session flag5 is unset. **29** affected current
pinned-MSVC objects are freshly cold built and all **199/199** old/new strict
units replay (**33,658** comparison bytes). All 58 previous object/receipt
SHA hashes and 135 unaffected receipts remain valid. Actual Front, Graphics,
Session and AnimationFile host tests pass 112 gate/spawn/failure scenarios,
with 48 genuine animation spawn boundary calls, complete owner images and
full original parameter ordering. CORE181 subsequently integrated opcode548 into the single
private whole-root host with 256 additional real Front/Graphics/Session tests;
native 41,967-byte boss root remains nonexact. See [focused proof](ENEMY_OPCODE_548_STAGE_TITLE_EXACT_RECONSTRUCTION.md)
and `.analysis/core180-stage-title-final-proof.json`.

CORE179 integrates the **full 95-byte native Enemy opcode549 caller path** into
the same 41,967-byte private whole-root draft, executing real
`EnemyController::has_identifier` (244-byte exact) and real ECL destination
forwarding. The previous opcode551 host now uses the separately confirmed
`PackedColor` zero/returning assignment ABI, **not** the folded
AnimationHandle void setter. One new 80-translation-unit O2/UBSan host passes
**37,985/37,985** cases (336 new), checking early cached controller versus
late live destination, intrusive iterator cleanup, owner-image preservation
and operand/destination failures. Private input hashes cover **96** files;
all 164 authenticated canonical receipts and CORE176 original source/hash
identities remain valid. The exact graph is **unchanged**: 214 authored
functions / 56,890 bytes / 1,000 physical strict units. Native 41,967-byte
Enemy root remains **nonexact**. See
[full boss-root evidence](ENEMY_WHOLE_ROOT_549_AND_COLOR_CORRECTION.md).

CORE/EXACT-178 corrects a real type/ABI misconception discovered by
whole-provider replay: native 0x4117A0 is the **void-return AnimationHandle**
writer, while native 0x45D650 is the **24-byte PackedColor uint32-return**
writer. Original AnimationHandle is preserved. The genuine four-byte
PackedColor already exists in production; its default constructor shares
the **previously accepted 23-byte** zero head and has **zero new byte credit**.
The other complete new function is the **244-byte** native
`EnemyController::has_identifier` used by opcode 549, with full iterator
lifetime and **13 independently established relocations**. The combined 14
changed-include providers cold replay **87/87** original + new units over
16,836 compared bytes; 28 original product hashes and 150 unaffected
receipts remain valid. Both host suites pass. The whole Enemy dispatcher
remains nonexact, and its opcode 551 host needs the corrected PackedColor type.
See [corrected native type and query evidence](ENEMY_COLOR_CONTAINS_NATIVE_RECONSTRUCTION.md).

CORE176 extends the actual single **41,967-byte Enemy dispatcher** private
candidate with **opcode 551**, independently decoded as a whole **257-byte
native interval / 58 instructions**. It runs the real AnimationHandle and
FogValue construction/packing with true `integer 0/1/2, float 4/3` read order.
The original global at `0x005C069C` is deliberately an **opaque captured
boundary**: its full Stage/Background owner remains unproven. The entire
79-translation-unit host passes **37,649/37,649** scenarios, adding 170
new packed-color, late-global and exception checks. All 164 canonical
compiler receipts and previous CORE175 private hashes remain valid. The
full-root exactness graph remains **unchanged**: 212 whole authored exact
functions / 56,622 bytes / 998 strict units. See
[focused 551 full-root evidence](ENEMY_WHOLE_ROOT_551_FOG_INTEGRATION.md).

CORE175 now integrates native Enemy **opcode 554** into the single complete
whole-root host, using the real 39-byte exact BulletController vector setter
and complete original **106-byte caller interval**. One fresh 79-translation-
unit host passes **37,479/37,479** O2/UBSan scenarios (132 new), including
whole 2,001-bullet owner images, Y-before-X read order, early cached receiver,
and operand failures. The private candidate reaches **119 effective values /
90 primary heads**. Existing compiler-exactness statistics do not change;
all 164 receipts and the original CORE173 private sources are preserved.
See [new full-root verification](ENEMY_WHOLE_ROOT_554_BULLET_INTEGRATION.md).

CORE/EXACT-174 restores **all 39 native bytes** of the true
`BulletController::set_vector_4c(X,Y)` used by Enemy opcode **554**. The root
reads the cached Context BulletController before **float operand 1 then 0**.
The real typed BulletController contains the native vector at +0x4C.
All **32/32** full affected strict units replay after five pinned cold builds;
10 original product hashes and all 159 untouched canonical receipts survive.
The 64 full Bullet owner image tests pass. The whole Enemy opcode dispatcher
remains **nonexact**, with private opcode554 host integration still open.
See [native owner/callee proof](ENEMY_OPCODE_554_BULLET_VECTOR_RECONSTRUCTION.md).

CORE173 now integrates **Enemy opcode 524 and 553** as two complete
native paths within the existing private whole-root candidate, executing
the independently exact GameController, PlayerTable and EnemyController
setters. The single **37,347-case** host passes, adding 166 complete-owner,
receiver-retargeting and exception-order checks to CORE170's 37,181 cases.
All 164 canonical original-source compiler receipts remain valid, with no
change to the exact reconstruction graph. The **41,967-byte** Enemy root,
actual Game publication and many subsystem resources are still open.
See [new complete-root integration proof](ENEMY_WHOLE_ROOT_524_553_INTEGRATION.md).

CORE/EXACT-172 adds the two complete 78-byte PlayerTable / 36-byte
GameController dependencies of Enemy opcode 524, with 149/149 protected
strict replays. CORE/EXACT-171 previously added the complete 25-byte
EnemyController scalar dependency called by Enemy opcode 553.
CORE170 previously added opcode 517 ScreenInf factory and opcode 518
FrontInf→Bullet→Laser→Enemy cleanup paths to the private whole-root draft.
The 37,181-case host passes, including all 36,802 prior CORE169 scenarios;
the exact 41,967-byte Enemy root, native Screen allocation and full resource
implementations remain open. CORE169 previously closed the two 1,472-byte
502/503 visibility paths semantically, without granting partial exactness. Start with this
page, [generated progress](PROGRESS.md) and the [evidence index](EVIDENCE_INDEX.md).
Do not restart completed validation merely to review the handoff.

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Embedded title/replay strings say 1.00c in this same file. The Steam-original
backup is provenance evidence; see [target provenance](TARGET_PROVENANCE.md).

The graph contains 1,003 physical strict units, 164 canonical objects and 181,381
disjoint comparison bytes. All 1,012 mapped functions have source; nine whole
mapped functions remain nonexact. Authored exact coverage is separately
217 functions / 57,008 bytes, with 229 confirmed authored origins. The reference
retains 6,945 terminal implementation reviews and 113 reconciled parser-gap files.
Whole-game 95% byte exactness, complete compilation/linkage and a playable
reconstruction remain unproved.

CORE161 closes the complete 0x140-byte Dialogue storage and 1,738-byte constructor,
actual callbacks/ready getters, the genuine 0x58-byte Laser controller and its
179-byte constructor/context routing. Eleven new strict units add 2,230 comparison
bytes; full EH support separately passes 157 bytes. A 17-byte Context pointer
getter folds to an existing physical ScriptStack unit without duplicate credit.
See [Dialogue owner evidence](DIALOGUE_OWNER_RECONSTRUCTION.md). Earlier
[FrontInf](FRONT_OWNER_RECONSTRUCTION.md) and [AsciiInf](ASCII_OWNER_RECONSTRUCTION.md)
construction remain accepted; native resource retirement/frame execution stay open.

The private whole Enemy draft now covers **122 effective values / 93 native
primary heads**, including original opcode548 and its actual FrontInf title
owner, 549 genuine Enemy membership, 551 real PackedColor/FogValue packing,
554 BulletController, 524/553 Game/Session/Controller, 517/518 ScreenInf,
502/503 visibility and 516/575 real callees. Its **38,241-case O2/UBSan**
single-root host passes (37,985 CORE179 cases plus 256 native stage-title
owner/gate/failure scenarios). The original Enemy 41KB dispatch, compressed
index, nested rank tables, common exits and EH are still **not byte exact**;
no opcode fragment gets partial root credit. See
[whole-root 548 caller](ENEMY_WHOLE_ROOT_548_STAGE_TITLE_INTEGRATION.md),
[549/551 binding](ENEMY_WHOLE_ROOT_549_AND_COLOR_CORRECTION.md),
[502/503 paths](ENEMY_VISIBILITY_OPCODE_502_503_RECONSTRUCTION.md) and
[516/575 integration](ENEMY_WHOLE_ROOT_516_575_INTEGRATION.md).

CORE/EXACT-162 reconstructs the 228-byte Dialogue destructor and its complete
233-byte compiler contribution. It retires fifteen actual animation handles
in the native order and leaves handle +70 untouched. All 14 independent
relocations and seven existing same-provider units strictly pass from a new
cold-built DialogueText object; portable production-owner retirement order
and populated Cursor destruction pass 512 dirty constructions. The full resource/frame VM remains open; see [Dialogue evidence](DIALOGUE_OWNER_RECONSTRUCTION.md).

CORE/EXACT-163 closes the whole 387-byte Dialogue follow-box and 63-byte
AnimationHandle child-forwarding method, with 26 independently mapped relocations.
The native WindowState coordinate scale is proven at global +20C0, and the
Dialogue TU now uses exact `/fp:strict` for all nine previously accepted units
plus follow-box. The portable production-owner fixture exercises real intrusive
child traversal, missing/invalid handles, X/Y scaling, three placement modes,
retained Z and cross-FrontInf callback routing. These two functions add 450
physical comparison bytes. The affected include-closure providers, not the
whole graph, are the correct cold-build scope.

## Current verification and cleanup

CORE/EXACT-180 adds three full original source/ABI matches for Enemy opcode
548's genuine stage-title path. The natural 75-byte FrontInf call is gated by
20-byte Graphics `field_b0c` and 23-byte Session bit5 getters, with five
independent relocs including original `AnimationFile::spawn` at 0x450C70.
**29** authentic affected providers and **196** older units are cold replayed
as **199/199** total exact over 33,658 bytes. Thirty local MSVC literal
labels are reconciled against complete old/new COFF bytes and original native
NUL-terminated strings. All **58** original object/receipt hashes and **135**
unaffected current compiler receipts survive. The new real-owner Front title
host exercises **112** graphics/flags/exception combinations (48 successful
spawn boundary calls), with all prior Front, Graphics and Session suites
passing. Authored whole-function graph increases by three, not by an Enemy
root fragment; see [native 548 proof](ENEMY_OPCODE_548_STAGE_TITLE_EXACT_RECONSTRUCTION.md).


CORE179 advances the **same complete Enemy root** with the real opcode549
95-byte/20-instruction original caller and restores the genuine
`PackedColor` value type in opcode551, without new production code or
independently counted case fragments. The 80-translation-unit full host passes
**37,985/37,985** cases, with **336 new** real Enemy list/controller/VM
late-destination/exception tests. Previous 170 FogValue scenarios all pass
with the corrected PackedColor constructor and uint32 assignment. The private
proof binds 96 actual inputs and compiler executable/log hashes; all 164
current canonical receipts and protected CORE176 private evidence survive.
Exactness remains **214 whole authored functions / 56,890 bytes / 1,000
strict units**, and native 41,967-byte Enemy body tables and EH are open.
See [complete root proof](ENEMY_WHOLE_ROOT_549_AND_COLOR_CORRECTION.md)
and private `core179-enemy-whole-root-proof.json`.


CORE/EXACT-178 is an actual source/ABI correction and protected exact replay:
**24/24** bytes for the real `PackedColor::operator=(uint32_t)` at 0x45D650
and **244/244** bytes for genuine EnemyController boolean membership at
0x49BF00. The first is **not** the existing 21-byte void AnimationHandle
assignment at 0x4117A0; a 53-object rejected experiment proves why. Shared
PackedColor no-arg construction has the already-credited 23-byte physical
head at 0x425CC0 and is **not** added as a new strict unit. Native iterator
EH/cleanup and thirteen pre-established relocation targets support the
second method. Source/receipt include closures require **14** new cold MSVC
objects / 85 pre-existing exact units; all **87/87** including the two new
units pass with **16,836** complete compared bytes. Every one of the **28**
old object/receipt hashes and **150** unaffected canonical receipts is valid.
PackedColor and Enemy iterator/whole-owner public tests pass. The whole root
remains separate. See [focused correction and exact evidence](ENEMY_COLOR_CONTAINS_NATIVE_RECONSTRUCTION.md)
and `.analysis/core178-final-exact-proof.json`.


CORE176 is a **whole-root host-only** continuation. Its original opcode 551
is one 257-byte native case (58 instructions), with live AnimationHandle and
actual 28-byte FogValue constructors and all five operands evaluated in their
independently verified `i0,i1,i2,f4,f3` order. The current global pointer at
0x005C069C is chosen after the operands; it is captured as an unresolved
owner, **not** introduced as a maintained class. The complete 79-source host
passes **37,649/37,649**, including **170 new** full-color, signed distance,
late-owner and operand-failure tests. Private proof hashes **94** input paths,
protects original CORE175 candidate/log bytes, and verifies all 164 canonical
build receipts. The admitted graph is unchanged: **212 whole authored exact
functions / 56,622 bytes / 998 strict units**; no whole Enemy root byte claim.
See [native and whole-root proof](ENEMY_WHOLE_ROOT_551_FOG_INTEGRATION.md) and
`core176-enemy-whole-host-proof.json` in private analysis.


CORE175 is a **complete-root semantic** change with zero new production source
or pinned strict units. The actual original opcode554 interval is 106 bytes/
22 instructions and calls `Context::bullet_controller` before `float_argument(1)`
and `float_argument(0)`, then the fully exact 39-byte BulletController setter.
The protected 79-source whole Enemy host now passes **37,479/37,479** cases
(132 new), exercising live 2001-slot BulletInf owners, early receiver
selection, full object images and exceptions. Private evidence hashes cover
93 inputs; all 164 canonical build receipts and CORE173 original whole-root
candidate/log identities remain unchanged. Exact authored count remains
**212 functions / 56,622 bytes / 998 physical strict units**, without
partial Enemy root byte credit. See [complete caller evidence](ENEMY_WHOLE_ROOT_554_BULLET_INTEGRATION.md)
and private `core175-enemy-whole-host-proof.json`.


CORE/EXACT-174 is a real graph change: `BulletController::set_vector_4c`
restores the complete 39-byte, zero-relocation native setter at 0x486480,
called by the native Enemy opcode 554 path after capturing true Context
slot-zero BulletInf and reading float operands **1 then 0**. Original x86
member offsets are +0x4C and +0x50. Actual include closures select only
**5** providers and **31** prior full strict units, cold rebuilt into
`build/core174-canonical/`; all **32/32** old and new whole units are exact
(**6,539** compared bytes). Five changed compiler-local labels match full
old/new COFF and native PE literal bytes. All **10** original object/receipt
hashes and **159** unaffected authentic receipts are verified. The real
2,001-bullet controller host passes 64 full-owner float-bit image tests,
including signed zeros and NaN payloads. Focused proof:
[Bullet vector and native opcode554](ENEMY_OPCODE_554_BULLET_VECTOR_RECONSTRUCTION.md),
private `core174-bullet-final-exact-proof.json`. The big Enemy root still
has no partial exact credit.


CORE173 adds no maintained production source and **zero** canonical units:
private Enemy opcode **524/553** case paths from original independently
verified 76-byte and 66-byte intervals are exercised inside the same
79-translation-unit whole-root host. **37,347/37,347** tests pass (166 new),
checking late published Game pointer versus cached early Context controller,
actual full Game/Session/EnemyController methods, complete owner images and
operand-exception order. Private input hashes cover 92 source/fixture files;
all 164 existing authentic pinned-MSVC object receipts are verified and
previous CORE170 evidence remains unchanged. See
[focused host proof](ENEMY_WHOLE_ROOT_524_553_INTEGRATION.md) and private
`core173-whole-enemy-root-proof.json`. The graph stays **211 authored whole
exact functions / 56,583 bytes / 997 physical strict units**; nothing here
claims 41,967-byte Enemy exactness.


CORE/EXACT-172 establishes the genuine GameController and Session.table
chain for opcode 524: global GameController pointer `0x005BA828` points to
the real Game owner; `Session` at `0x005BA568` has PlayerTable at +0x88,
which matches the independent native global access at `0x005BA5F0`.
**`PlayerTable::set_field_1fc` (78/78)** stores then clamps the signed value
to 0..999. **`GameController::set_field_34` (36/36)** calls that real table
setter and preserves the original full input word in Game+0x34. Three
relocations are independently established and 19 truly affected providers
are cold-built into `build/core172-canonical/`: **149/149** complete strict
units, **18,875** compared bytes. Fourteen changed compiler string labels
match complete old/new COFF and original native constant bytes. All 38
original object/receipt hashes survive, and 145 unaffected receipts remain
valid. Both focused Game/Session O2/UBSan tests pass, including 40 paired
full-owner image scenarios. The Enemy root still gets **zero** partial exact
credit; opcode 524 whole-root host integration is separate next work. See
[focused native/owner proof](ENEMY_OPCODE_524_GAME_SESSION_RECONSTRUCTION.md)
and private `core172-final-exact-proof.json`.


CORE/EXACT-171 reconstructs **`EnemyController::set_field_88`**, the complete
25-byte game-specific write at 0x49C490, through the genuine Controller at
+0x98. The native opcode 553 obtains `Context::enemy_controller` before
integer operand 0 and calls the cached receiver; the whole Enemy dispatcher
remains unaccepted. Authentic includes require **11** protected fresh MSVC
objects and **65 previous** strict units. All **66/66** old and new units
replay exactly (**14,881 complete compared bytes**). Six renamed local string
labels are proved independently from old/new complete COFF and native PE
literals. All **22** old object and receipt hashes survive, with **153**
valid unaffected receipts. Host Enemy creation/clear regression passes, plus
30 complete `field_88` object-image scenarios; the genuine x86 layout is
asserted at +0x98 without pretending x64 host offsets are identical. See
[complete source/owner proof](ENEMY_OPCODE_553_CONTROLLER_FIELD_RECONSTRUCTION.md)
and private `core171-final-exact-proof.json`.


CORE170 independently decodes full opcode 517/518 case intervals (99/142
original bytes; 25/31 native instructions), fixes seven-argument ScreenInf
allocation ownership (`0x4250F0`, owner size 0x44 and 637-byte ten-mode
initializer) and confirms late Front/Context receivers through actual native
calls. The private host compiles 78 real source units and passes
**37,181/37,181** scenarios, adding 379 to CORE169. Front message, Bullet,
Laser and Screen resource bodies are bounded captures; the last
`EnemyController::clear` call is the actual accepted whole implementation.
The hash-attested `core170-whole-enemy-root-proof.json` preserves 90 input
hashes and all 164 unchanged canonical receipts. **Zero tracked production
or exact-unit changes**; the 41,967-byte whole root remains nonexact.


CORE169 audits the **full two 1,472-byte** native Enemy branches for opcodes
502/503 (592 original instructions), including all fourteen separate low-bit
writes, the post-update bit-five gate, and the original begin/end/vector loop.
Failed Renderer lookups must retain stale handle values; the private host
therefore captures just this boundary while executing real recursive Animation
flag operations on nested child storage. Full source candidate versions CORE168
and older are protected; the new host compiles 78 genuine sources and passes
**36,802/36,802** cases, adding 492 to CORE168. Hash-attested native ranges,
89 source/fixture input hashes and a valid unchanged 164-object receipt graph
are stored in `core169-whole-enemy-root-proof.json` and
`core169-enemy-502-503-native-audit.json`. **Zero production-source or exact
unit changes**; this is large-root semantic progress, not partial byte exactness.


CORE168 adds zero tracked production-source or canonical-unit changes. The
private whole Enemy draft is extended with real opcode 516 and 575 case order,
and its preserved 36,232 previous scenarios and 78 new real SoundInf/Player
scenarios pass (**36,310**). The private host uses 78 source providers and
keeps its original 76-provider/old candidate inputs SHA-protected rather than
overwriting them. All new code and input SHA-256 hashes, locked PE checks and
actual original case heads are in
`core168-whole-enemy-root-proof.json`. This is verified large-root semantic
progress only; total exact functions remain **208 / 56,444 bytes**. No
cold canonical build or strict-root comparison is asserted for these private
source changes.


CORE/EXACT-167 closes all 52 original bytes of the real
`SoundInf::request_effect_at(id,x)` at 0x426EB0, with three independently
established float/callee relocations. Enemy opcode 516 captures the state
position's X before reading its integer sound identifier, then calls this
member on process_sound at 0x5BA830. The one changed SoundEffects translation
unit is cold-built into `build/core167-canonical/`: **4/4** old and new
complete exact units, 163 unaffected canonical receipts retained, and both
original object/receipt SHA hashes preserved. The live SoundLoading host
fixture passes 52 pan conversion cases plus its 140 original resource cases.
See [sound/Enemy integration](SOUND_EFFECT_PAN_RECONSTRUCTION.md); native
request queue and whole 41KB Enemy dispatch remain separate open boundaries.


CORE/EXACT-166 recovers the native 42-byte `Player::set_entity_flag_10`
member at 0x49C390, called by the *whole* Enemy dispatcher's opcode 575 path.
The opcode reads `player(0)` before operand 0, then calls the bitfield setter.
The real Player+14 word is a typed 10/1/21 bitfield view; 42/42 function bytes
are exact with zero relocations. The 6 objects whose genuine include closures
contain Player/PlayerStorage headers are independently cold rebuilt; all 36
old functions and the new complete function replay **37/37** full comparisons
(6,521 compared bytes). The one compiler-local initialization string rename
was reconciled using the original complete COFF bytes and PE string. All 12
original object/receipt SHA-256 hashes survive and all 158 unaffected
canonical receipts remain valid. Portable Player/SHT tests pass 24 full-word
flag cases and prior resource/damage-cap behavior. See
[focused proof](ENEMY_OPCODE_575_PLAYER_FLAG_RECONSTRUCTION.md) and private
`core166-player-final-proof.json`. **No partial Enemy root credit** is taken.


CORE/EXACT-165 corrects `ProgressMetadata::calculate_integrity` at 0x463F20:
its return is a byte, not the previously declared uint32_t; the native signed
32-bit address comparison and actual array-first-element expression now emit the
whole 134-byte target. All six relocations are independently supported by prior
exact LockRegistry/Worker and compiler-security roles. The 161-byte Metadata
integrity update also remains exact with its corrected callee symbol. Actual
include closures select **8 providers and 22 old strict units**. All eight are
cold-built at reduced priority into `build/core164-canonical/`; all 22 old
units and the new complete unit strictly replay exactly (**23/23**). The
remaining 156 canonical providers reuse unchanged valid evidence. All five
focused progress test suites pass. The original eight object and eight receipt
hashes are protected in `core164-progress-scope.json`, while the new
`core165-progress-final-proof.json` records verification results. Source ABI,
exactness and portable fixture limitations are in
[focused evidence](PROGRESS_INTEGRITY_BYTE_EXACT.md). No whole-graph replay was run.

CORE/EXACT-164 touches only the Enemy mesh host semantics test and focused
evidence/handoff prose. Its complete native 1,649-byte code audit confirms
three writes (and zero direct reads/address formations) of stack byte -31,
with independently identified 32.0/64.0/255.0 constants. The real mesh
production fixture passes 1,536 whole-owner deformation cases spanning those
thresholds, growing/equal/shrinking radius targets, independent geometry,
color, UV and strip checks. This **does not** grant whole-root exact credit;
`EnemyState::update_mesh` remains 1,548-source/1,649-native nonexact. The
CORE164 reconstruction graph is unchanged; its affected cold-build/strict
replay scope is **zero units**. Private evidence is
`core164-mesh-unused-byte-audit.json`; unrelated diagnostic drop/compression
probes remain ignored and unaccepted.

CORE163 changed the two source files `DialogueText.cpp` and
`AnimationHandle.cpp`, plus the existing handle declaration header. Actual
`/showIncludes` closures in original authenticated receipts select **53
providers / 351 strict units**; 51 previously accepted objects are rebuilt
serially at `nice 15` into `build/core163-canonical/` without overwriting the
original objects or receipts. The other two are already fresh in this
canonical directory. All **351/351** complete strict comparisons pass after
25 MSVC-generated literal labels were reconciled. Each old/new COFF literal
has identical complete bytes, and each native constant agrees through NUL;
2 native string-pool padded extents differ outside the original literal. No
target byte was solved to obtain any relocation. The other **111 unaffected
providers** reuse their previously validated original receipts; no unfiltered
whole-graph replay is performed.

Protected input hashes and the 53/351 affected closure are recorded privately in
`core163-affected-scope.json`. The self-contained result index is
`core163-affected-final-proof.json`: 351/351 full exact replays covering 63,053
affected comparison bytes, all 53 current canonical receipts, all 106 protected
old-object/receipt hashes, and 111 valid unaffected receipts. Three disjoint
comparison batches and `core163-literal-reconciliation.json` retain all native
literal identity evidence. Original object and receipt SHA-256 values
match the frozen scope after all builds. Native game target SHA-256 stays locked.

Prior CORE161 validated 59 providers / 392 previous units and eleven new
whole units. That historical evidence was not recompiled outside this turn's
actual affected closure. Complete INT3 tails, Cursor cleanup and shared
exception metadata are retained.

The actual-owner fixture passes 512 guarded dirty constructions, 24 exception
unwinds, 2,049 live callbacks and 3,072 full-width ready reads. The affected
FrontInf fixture passes 1,706 cases; AsciiInf passes 256 dirty constructions,
81,920 complete line images and 768 shared-file selections. The historical CORE161 whole-root
fixture passed 36,232 cases; CORE170 passed 37,181; CORE173 passed
37,347; CORE175 passed 37,479; CORE176 passed 37,649;
CORE179 passed 37,985; current CORE181 passes 38,241. Source and fixture limitations are explicit in the
focused evidence; these are portable checks, not native game execution.

Historical CORE161 private proofs include `core161-cold-proof.json`,
`core161-affected-results.json.gz`, `core161-new-exact-results.json.gz`,
`core161-independent-bindings.json`, `core161-existing-role-reconciliation.json`,
`core161-protocol-native-identity.json`, `core161-public-test-proof.json`,
`core161-dispatch-host-recipe.json`, `core161-dispatch-host.log` and
`core161-gates.json`. Private filenames here are relative to `.analysis/`.
Registration/finalization scripts are not idempotent; consume their saved reports
rather than rerunning admission or cleanup.

`core161-retirement-plan.json` inventories 123 retired files / 5,306,440 bytes:
59 replaced object/receipt pairs, two superseded probe pairs and the successful
regenerable host binary. Authentic receipts and SHA-bound input texts are archived
before removal. `core161-cleanup.json` confirms all 328 current canonical files,
twenty private investigation products and 356 native evidence/active inputs
retain their protected hashes. The preceding CORE161 cleanup phase added zero compiler builds/replays; the
separate CORE163 phase above did rebuild exactly the affected 53 providers.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 66 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 6 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 3 | Every sibling `.receipt.json` |
| `build/core149-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core151-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core154-canonical/` | 5 | Every sibling `.receipt.json` |
| `build/core154-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core156-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core158-canonical/` | 10 | Every sibling `.receipt.json` |
| `build/core161-canonical/` | 6 | Every sibling `.receipt.json` |
| `build/core163-canonical/` | 19 | Every sibling `.receipt.json` |
| `build/core164-canonical/` | 8 | Every sibling `.receipt.json` |
| `build/core166-canonical/` | 2 | Every sibling `.receipt.json` |
| `build/core167-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core171-canonical/` | 8 | Every sibling `.receipt.json` |
| `build/core172-canonical/` | 14 | Every sibling `.receipt.json` |
| `build/core174-canonical/` | 2 | Every sibling `.receipt.json` |
| `build/core178-canonical/` | 9 | Every sibling `.receipt.json` |
| `build/core180-canonical/` | 29 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. Earlier authentic
object/receipt pairs remain in their original directories without alteration;
private CORE161 hashes and the new CORE163 scope both protect the old products.
The previous 279-path source freeze is `core161-final-frozen-source.json`.
Protected historical product, source, native-evidence and test hashes remain
in `core161-retirement-plan.json`.
Retain the nine root object/receipt pairs for core103-QueryProtocol-v5 and the
core109..core113 sound probes, plus `build/core144-probes/Alignment.obj` and its
receipt. These twenty files are historical unfinished-investigation snapshots;
their original receipts/inputs must not be rewritten as current builds. See
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Renderer ownership](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

Preserve `core161-pre-dialogue-inputs.json.gz`,
`core161-pre-registration-ledgers.json.gz`,
`core161-probe-v1-original-inputs.json.gz`,
`core161-probe-v2-original-inputs.json.gz`,
`core161-prior-dispatch-inputs.json.gz` and all earlier original-input/evidence
archives. Current private root inputs are `core181-enemy-dispatch-candidate.cpp`,
`core181-dispatch-host.cpp`, `core181-front-title-host-cases.inc` and the
CORE181 recipe/proof. The original CORE179 candidate, fixture and log remain
protected. CORE176 retains its
unaltered historic source and build evidence. CORE175, CORE173, CORE170, CORE169, CORE168, CORE161 and earlier candidates,
fixtures and unfinished protocols remain protected.

Historical archive lookup remains in the handoff146/149/152/154/157/160 and
core156/158/159/160 retirement plans. They preserve archived logs, snapshots and
original inputs. Read `.json.gz` / `.log.gz` through `gzip.open`; old plain paths
may have been retired losslessly. Preserve installed tools, reference source,
Ghidra, native exports and supplied `../game_exe/` files.

## Next work

1. Continue the whole Dialogue frame/message VM, native resource retirement,
   and Cursor constructor emission. Follow-box and its real child lookup are
   now closed; the Renderer and Animation pool integration remain open.
2. Continue the complete Enemy dispatcher at 0x48C010, including its 41,967-byte
   ordinary body, tables and compiler contributions. The 575 path has a verified
   exact Player flag dependency; opcode 516 now has a complete exact
   SoundInf positional pan dependency too. Neither grants partial root credit. Remaining
   502/503 are semantically integrated, but still need the genuine Renderer
   lookup and wrapper source/ABI. Opcode 517/518 now have tested ScreenInf
   and FrontInf/Bullet/Laser/Enemy call ordering, but the real Screen
   factory/message/cancellation bodies remain open. Opcode 524 and 553 now have verified
   whole-host integrations with real typed callees; 539 and 555
   still need native owner paths. Opcode548 now has three exact genuine
   Graphics/Session/FrontInf dependencies, but its original whole-root
   host integration remains open. The 549 branch was integrated in CORE179. Opcode 551
   now has a whole-host FogValue route, but its genuine global and forwarding
   interpolation owner at 0x005C069C are still unaccepted.
   Opcode 554 now has both an exact true BulletController vector setter and
   passing live Y-before-X whole-root caller integration; root byte emission
   and native startup are still open. Reuse [FrontInf callers](FRONT_OWNER_RECONSTRUCTION.md),
   [rank/control](ENEMY_RANK_CONTROL_RECONSTRUCTION.md),
   [state](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md),
   [Card](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [clear](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md) and
   [movement](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md) evidence. Preserve native
   stale-handle behavior and complete extents; no partial-root credit.
3. Resolve the genuine Renderer allocation 0x7D40E94 and +6000DFC..+6000DFF before
   declaring fields. Negative searches do not prove padding. This blocks whole
   File::clear, texture creators and the 922-byte File spawn producer. The
   40,752-byte Animation VM also remains open; see
   [pool/owner evidence](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md),
   [File lifetime](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md) and
   [whole dispatch](CORE_ECL_DISPATCH_RECONSTRUCTION.md).

The nine source-present whole nonexact roots are:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; [scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| create_bomb_controller | 0x478300 | Whole native123; [Bomb owner](BOMB_OWNER_RECONSTRUCTION.md) |
| EnemyState::update_mesh | 0x4A4190 | 1548/native1649; [mesh lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) |
| EnemyPattern::emit_items | 0x4A5350 | 628/native630; [drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md) |
| PlayerFeedback::record_hit | 0x4FB3A0 | 114/native115; [state protocol](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md) |
| create_hit_controller | 0x4C20D0 | 82/native92; [Hit lifecycle](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md) |
| ProgressSaveManager construction | 0x50E5D0 | 198/native199; [lifetime/profile](PROGRESS_LOAD_LIFETIME_EXACT_RECONSTRUCTION.md) |
| ProgressSaveManager::commit | 0x50F660 | 68/native70; same lifetime/profile evidence |
| archive_compress | 0x539550 | Whole native1036; [write protocol](ARCHIVE_WRITE_RECONSTRUCTION.md) |

Do not repeat unchanged rejected profile trials or insert inert operations to
shape output. Preserve actual void, lifetime and exception contracts. The whole
1,707-byte damage query remains unimplemented; its counter and release-before-read
ownership questions are in the focused evidence.

## Resume discipline

Follow [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[tool routing](TOOLS.md). Commit subjects use **`gpt-web: <description>`**.
Use one writable session, no REA or delegated reconstruction, and serial heavy
work at nice 15 / CPU 3 with bounded Ghidra memory. Use scripts/repo-python;
keep claims header-only and maintained prose in English, preserving the official
Japanese target title.

Reuse passing evidence for unchanged inputs. Before new validation, identify
changed inputs and actual affected providers from captured includes/manifest
roles; use explicit source filters or individual units. Documentation and cleanup
alone select zero replay units: skip Ghidra, MSVC and full CI. Never run an
unfiltered replay for handoff or reassurance. Preserve authentic original inputs
before edits/retirement and check protected hashes after cleanup.
