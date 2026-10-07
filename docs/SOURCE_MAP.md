# Source and build ownership

EXACT-051 adds shared intrusive observation, sentinel operations, nonthrowing
Region construction/update and position/vector dependencies: 20 complete units /
1,827 body bytes plus 15 compiler alignment bytes. All 363 units / 66 cold objects /
57,534 disjoint complete comparison bytes strictly replay. IntrusiveLink.cpp owns
the Region template instantiations; FunctionChain keeps its existing typed owner.
All nine Region units use one precise-FP/GS/EHsc profile. Aliases count once.
List construction/reset, retirement and full controller ownership remain pending.
See EXACT_INTRUSIVE_LIFETIME_RECONSTRUCTION.md. Earlier entries are historical.

EXACT-050 adds the coherent Damage Region routing/configuration protocol and
Motion/identifier dependencies:13 units /3,532 bytes; all343 /65 coldobjects /
55,692 disjoint complete bytes strictly replay. Actual196-byte Region has typed
subobjects and an opaque Context pointer. Shared IntrusiveLink<T> preserves the
old constructor/insertion exact units; physical aliases count once. Natural
Region construction remains source-present/nonexact due to native EH ownership.
Controller/pool/observer lifetime and original names/origins remain pending.
See EXACT_DAMAGE_REGION_RECONSTRUCTION.md. Earlier entries are historical.

EXACT-049 adds all twelve rectangle/segment candidates and nine planar math
leaves: 21 complete units / 10,759 bytes; all330 /63 coldobjects /52,160 disjoint
bytes strictly replay. Actual arrays, typed shared scalar rotation, separate
array strides, cdecl return widths and original geometry quirks are retained.
See EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md. Earlier summaries are historical.

EXACT-048 closes seven collision predicates and three vector/math dependencies:
ten complete units / 3,841 bytes; all 309 units / 61 cold objects / 41,401 disjoint bytes
strictly replay. Native edge arrays, cdecl AL predicates, normalization threshold,
finite perimeter sampling and collinear quirks are preserved. Full collision
controller ownership and origins remain open. See EXACT_COLLISION_SHAPES_RECONSTRUCTION.md.
Earlier summaries are historical.

EXACT-047 closes the current-first Enemy curve update and direct movement helpers:
eight complete units / 2,716 bytes; all 299 / 60 cold objects / 37,560 disjoint
comparison bytes strictly replay. Real axis slots, indexed coordinate references, full signed duration and
native Motion assignment retain canonical owners. Full Enemy/PMR/ECL/resource
lifetime and original origins remain open. See EXACT_ENEMY_INTERPOLATION_RECONSTRUCTION.md.
Earlier summaries are historical.

EXACT-046 closes shared easing and the generic interpolation update protocol:
32 complete units / 13,952 bytes. All 291 / 60 cold objects / 34,844 disjoint
comparison bytes strictly replay. Component-scoped behavior, shared physical
heads, arithmetic ABIs and open ownership/origin boundaries are recorded in
EXACT_INTERPOLATION_RECONSTRUCTION.md. Earlier summaries are historical.

EXACT-045 adds the shared Motion update protocol and its immediate dependencies:
18 complete units / 2,572 comparison bytes. All 259 canonical units across 59
cold objects strictly replay over 20,892 disjoint bytes. The source and native
semantics are documented in EXACT_MOTION_RECONSTRUCTION.md; origins, enclosing
owners, linkage and full runtime acceptance remain open.

REF-044 completes individual review of all 6,945 existing reference bodies and
113 grammar files. Final tools/bridges provide support evidence and add no
maintained production owner. All 241 canonical units remain exact; the source
owners below retain their component-scoped acceptance and unresolved origins/
enclosing lifetimes. See REFERENCE_SUPPORT_REVIEW.md for complete review counts
and the separate whole-game boundary.

| Owner | Maintained source | Target component | Acceptance |
| --- | --- | --- | --- |
| FogValue | src/FogValue.hpp, src/FogValue.cpp | construction 0x00471940/0x004718D0; pack 0x00473400; scale/subtract/add 0x00471DB0/0x00471E60/0x00471F50 | Six complete exact members on actual 28-byte value; representable int32 channel truncation, original names/origins/full background owners pending |
| IntegerTriple | src/IntegerTriple.hpp, src/IntegerTriple.cpp | constructors414090/4291E0; add4295D0/subtract4294A0/scale429340 | Five complete exact members; actual three-int value, reversed constructor arguments, by-value RHS ABI, modulo32 arithmetic and per-component truncation; original tag/roles/origins pending |
| Matrix4 | src/Matrix4.hpp, src/Matrix4.cpp | constructor 0x00447DC0 | Complete 30-byte exact constructor on sixteen floats; matrix consumers independently observed, original spelling/origin pending |
| Sprite vertices | src/SpriteVertices.hpp, src/SpriteVertices.cpp | constructors 0x00449110/0x00449140/0x00449170 | Three complete exact constructors on real 20/20/28-byte values; array strides/pointers independently observed, full Controller owner pending |
| AnmVariables | src/AnmVariables.hpp, src/AnmVariables.cpp | constructor 0x00449050 | Complete 182-byte exact constructor on actual seven-integer/nine-float member; field roles/origin/full Base pending |
| TextureTexels | src/TextureTexels.hpp, src/TextureTexels.cpp | accumulation 0x00451640/0x00451700/0x004517C0/0x00451880 | Four complete exact cdecl helpers; packed channels, alpha gate, wrapping and alias order; full texture repair/resource owner pending |
| PlayerRecord | src/PlayerRecord.hpp, src/PlayerRecord.cpp | construction423050;43 unique setter heads;score44C090;mutating power4B81D0 | 46 full exact units3654bytes on real240-byte scalar/byte value;two alreadycanonical shared setters get no duplicate credit;original names/origins/full Table/Session/HUD owners pending |
| EnemyHealth | src/EnemyHealth.hpp, src/EnemyHealth.cpp | construction4A3360; reset4A7310; apply4A3F80; record4AA050; positive4AB240; forced_end4AB290 | Six full exact members on real28-byte value; modulo32/signed division7 and full-EAX queries; field04 role/origin/enclosing owner pending |
| EnemyPattern | src/EnemyPattern.hpp, src/EnemyPattern.cpp | construction4A34A0; reset4A7360; clear_counts497270 | Three full exact members on real168-byte value with two16-element arrays and Timer; native fifteen emitted kinds do not shorten arrays; origins/full drop owner pending |
| EnemySpawn | src/EnemySpawn.hpp, src/EnemySpawn.cpp | construction47BB30 | Full95-byte exact constructor on real84-byte value; Counter48 and four-byte Identifier32 tail, original tail tag/role/enclosing owner pending |
| EnemyMotionInterpolation / EnemyMovement | src/EnemyMovement.hpp, src/EnemyMovement.cpp | construction48B270/48B550; sample4A8D70; factors4AAB10/4AAB70; duration438500 | Six complete exact contributions on actual100/388-byte values; current-first shared/per-axis update, signed duration and six child values; configuration/full Enemy owner/origins pending |
| ScriptStack | src/ScriptStack.hpp, src/ScriptStack.cpp | construction4A36D0; absolute53E630; local53E6A0; leave_frame540300 | Four complete exact members on actual PMR Stack24; generic output-pointer/status pop explicitly undefined, allocator/full VM ownership and origins pending |
| EnemyCounters | src/EnemyCounters.hpp, src/EnemyCounters.cpp | construction47BAA0; reset4AB1B0 | Two complete exact members on actual48-byte four-integer/eight-float value; full EnemyData/controller ownership and field roles/origins pending |
| DialogueFlags | src/DialogueFlags.hpp, src/DialogueFlags.cpp | construction0x004AEC90 | Complete66-byte exact constructor on real four-byte Dialogue+104 member; upper25 retained, bit meanings/origin pending |
| DialogueText | src/DialogueText.hpp, src/DialogueText.cpp | lead predicate0x004B6460; decoder0x004B7C90 | Complete62/197-byte exact cdecl contributions; uint8/full-int lead ABI, shared external BSS, valid terminated/paired-lead domain; storage/lifetime and origins pending |
| ScoreEntry | src/ScoreEntry.hpp, src/ScoreEntry.cpp | construction0x0050FD50 | Complete127-byte exact member on actual68-byte record; typed Vector3/Timer, implicit padding3A/B preserved, float30/34 roles and origin pending |
| HudGauge | src/HudGauge.hpp, src/HudGauge.cpp | construction0x004AECE0 | Complete34-byte exact constructor on actual8-byte gauge; first word float, second word role and origin pending |
| OverlayCounter | src/OverlayCounter.hpp, src/OverlayCounter.cpp | construction0x00532850 | Complete33-byte exact constructor on actual8-byte member;0/1500 initial state, arithmetic/signedness and origin pending |
| BulletStyle | src/BulletStyle.hpp, src/BulletStyle.cpp | radius query 0x00485700 | Complete18-byte exact cdecl query; actual writable50*344-byte array, radius+144 and BSS base independently audited; storage/initializer undefined, origin pending |
| BulletValues | src/BulletValues.hpp, src/BulletValues.cpp | constructors 0x0047BD90/0x0047BD20/0x0047BCA0 | Three complete exact constructors on actual64/40/44x86-byte values; shared array strides/signed counts/script pointer independently observed; origins and full owners pending |
| Vector2 | src/Vector2.hpp, src/Vector2.cpp | constructors4398A0/429250; add429640/subtract429520/scale4293C0 | Five complete exact members on actual two-float value; native member/result ABI, original spelling/origin pending |
| CollisionGeometry / CollisionShapes | src/CollisionGeometry.hpp, src/CollisionGeometry.cpp, src/CollisionShapes.cpp | absolute445680; circle456FE0; rectangle457300; circleellipse4562E0; circlepolygon456690; circlestar4567D0; segment456920; ellipsepoint457040; polygonpoint4570F0; starpoint457380 | Ten complete exact routines; native inclusivity, finite sampling, count behavior and collinear quirks; origins/full controller pending |
| PackedColor / EffectParameters / EffectRequest / SelectionPulse | src/EffectParameters.hpp, src/EffectParameters.cpp | constructors 0x004142A0/0x0047BA30/0x0049CE30/0x00461840 | Four complete exact constructors on actual4/56/72x86/8-byte values; implicit padding kept, origins pending |
| Interpolation<T> | src/Interpolation.hpp, src/Interpolation.cpp | existing constructors/setters/begin; sample429E90/42A110/42A3A0/42A980/42AD80/42B1F0/473590/513710; five stop/factor heads; evaluate511CF0/511AF0; duration41CAF0/438520 | Forty complete exact contributions on actual32/44/64/84/164-byte values; shared protocol, ordered accumulation/Hermite and typed narrowing; other evaluation emissions, original origins and enclosing owners unbound |
| Easing | src/Easing.hpp, src/Easing.cpp | dispatch454EF0 | Complete4,284-byte contribution including32-entry table; zero-duration override, unclamped ratio, polynomial/sine/calibrated back curves; origins and global compiler/CRT recipe pending |
| RandomState | src/Random.hpp, src/Random.cpp | transition 0x00422CB0; invocation 0x004235F0 | Exact library equivalents; excluded from authored credit |
| Timer | src/Timer.hpp, src/Timer.cpp | construction, current/fraction reads, remainder, assignment/subtraction/postfix wrappers, reset/set/mode, add/tick, prefix increment and signed predicates | Nineteen complete exact functions; additional construction/wrapper/predicate origins pending; integer += remains nonexact |
| FunctionChain | src/FunctionChain.hpp, src/FunctionChain.cpp | link construction/insertion and eight node field operations | Eleven complete exact functions; allocator, iterator, dispatch and enclosing owner remain open |
| ClockScalar | src/ClockScalar.hpp, src/ClockScalar.cpp | float read 0x004292E0; multiply 0x00452F50; set 0x004292A0 | Exact four-byte float view; enclosing owner and origin pending |
| LockRegistry | src/LockRegistry.hpp, src/LockRegistry.cpp | enable 0x0041CCC0; disable 0x0041CA30 | Two exact flag assignments; tracked locking and original global lifetime pending |
| DebugMemoryResource | src/DebugMemoryResource.hpp, src/DebugMemoryResource.cpp | constructor 0x00418DB0; destructor 0x00418E90; equality 0x0041C9F0 | Three complete exact custom PMR functions; allocation/deallocation remain undefined and this is not a linked allocator |
| TaskInfo | src/TaskInfo.hpp, src/TaskInfo.cpp | TaskInf destructor and separate virtual/helper enable/disable entries | Five complete exact functions; native constructor and allocator-based deletion pending |
| Worker | src/Worker.hpp, src/Worker.cpp | constructor 0x0040B780 | Exact 44-byte construction; close/join/detach and destructor remain undefined/pending |
| ArchiveCrypt | src/ArchiveCrypt.hpp, src/ArchiveCrypt.cpp | counted filename byte sum 0x00456270 | Exact 71-byte helper; parameter table selection, decryption and native archive owner remain pending |
| InputState | src/InputState.hpp, src/InputState.cpp | Device initializers, byte binding, button update, three mask queries and held-frame query | Eleven complete exact functions including Replay reset/update; constructor, OS polling and Controller owner remain pending |
| Configuration | src/Configuration.hpp, src/Configuration.cpp | binding construction 0x0041FB10; default slots 0x0041FC50; option flags 0x004B9B80 | Three complete exact functions; slots/flags origin pending; full configuration owner remains open |
| GameRandom | src/GameRandom.hpp, src/GameRandom.cpp | construction 0x00422C50; bounded 0x00423EA0; float wrappers 0x00429830/0x004298E0; engine helpers | Four authored and two library complete exact units; next/seed locking and global startup remain undefined |
| TrophyText | src/TrophyText.hpp, src/TrophyText.cpp | shared decoder 0x0052F060 and message id reset 0x0052F590 | Two complete exact functions; PMR encoder, parsing, record allocation and whole Trophy owner remain open |
| WindowState | src/WindowState.hpp, src/WindowState.cpp, src/WindowApi.cpp | five field methods, system restoration, repeat reset and flags construction | Seven authored and one origin-pending complete exact units; original construction/global startup remain undefined |
| WindowApi | src/WindowApi.cpp | foreground wrapper 0x0041B480; locale detection 0x0041D0C0 | Two complete exact units; foreground source/origin identity pending |
| FontDetection | src/FontDetection.hpp, src/FontDetection.cpp | font enumeration callback 0x00414820 | Authored complete exact callback; initialization/global pointer storage remain undefined |
| SceneResources | src/SceneResources.hpp, src/SceneResources.cpp | initialization 0x004D82C0; release 0x004D8560 | Two authored complete exact orchestration functions; dependency owners remain undefined |
| SoundEffects | src/SoundEffects.hpp, src/SoundEffects.cpp, src/SoundEffectsApi.cpp | request/command/channel construction 0x00425CE0/0x00425FC0/0x00425D20; channel release 0x00428380 | Four complete exact units; release authored, three constructor origins pending; enclosing SoundInf and stream owners remain open |
| AnimationHandle | src/AnimationHandle.hpp, src/AnimationHandle.cpp | value construction 0x00425CC0 | Complete 23-byte exact constructor; authored/compiler origin pending; resolve, interruption and enclosing Controller remain undefined |
| Angle / Motion | src/Angle.hpp, src/Angle.cpp, src/Motion.hpp, src/Motion.cpp, src/MotionUpdates.cpp | constructors/reduction/update/bounds; velocity453E40, position453AC0, snap4543D0, vector4562C0, set-vector47A5E0, Z4591F0; angle452F20/4530C0/452FC0/4294E0/429610/429390 | Twenty-one complete exact contributions on actual4/72-byte values; position/get/set/clear protocol added; complete motion protocol, bounded normalization, flags and full-int bounds; origins/enclosing owners pending |
| Damage Region | src/DamageRegion.hpp, src/DamageRegion.cpp | Routing4C1030, configuration4C1C50/4C1D80, position/context/allocation flag and set-position | Nine complete exact members on the real 196-byte value, including nonthrowing construction/update; retirement/controller lifetime pending |
| Identifier word protocol | src/Identifier32.hpp, src/Identifier32.cpp | get40C300, assignment4117A0, equality4C0210; zero ctor425CC0 shared | Three complete exact units; shared ctor has no duplicate credit, original semantic tags/origins pending |
| Typed linked prefix | src/IntrusiveLink.hpp, src/IntrusiveLink.cpp, src/FunctionChain.cpp | Shared typed link/list/observer protocol with real FunctionChainNode and Region pointers | Three previous contributions retained plus sixteen new link/list/iterator units; list construction/reset, locking and enclosing lifetime remain open |
| Rectangle collision neighborhood | src/RectangleCollisions.cpp, src/CollisionGeometry.hpp | 4545D0/4547E0/454D80;456B40/456D50;457610/4578B0/457C10/4580C0/458670/458B60/458E90 | Twelve complete exact routines; native array storage, status/bool/float ABI, finite sampling and shortcut/boundary quirks; enclosing owner/origins pending |
| Planar geometry metrics | src/GeometryMetrics.cpp, src/CollisionGeometry.hpp | 455FB0/455FE0/456030/456050/456080/4560D0/456170 | Seven complete exact routines; interleaved scalar endpoints, XY-only Vector3 distance, full-EAX vertical status; origins pending |
| Motion math | src/MotionMath.hpp, src/MotionMath.cpp | polar439330, rotation458FA0, direction456210, floor4592B0, difference4396C0; ellipsepolar459190; normalization4532C0; arrays459030/4590E0; float overloads4371D0/439530 | Eleven complete exact contributions; typed scalar shared head covered once; alias-safe planar arithmetic, destinationZ preservation, original origins pending |
| Vector3 | src/Vector3.hpp, src/Vector3.cpp | constructors 0x00422E10/0x00422DD0; subtract 0x00429440; scale 0x004292F0; add assignment 0x004296E0; multiply assignment 0x00429690; add 0x00429570; subtract assignment 0x00429740; indexed reference 0x00414580; division0x00452FF0 | Ten complete exact members including indexed reference414580 and division; actual named float subobjects, domain0..2, original class spelling/origins pending |
| Cursor | src/Cursor.hpp, src/Cursor.cpp | shared menu history, predicates, setters and reverse resource destruction | Eight complete exact members on real PMR vector/two-stack owner; natural constructor source present but native EH nonexact, origins pending |
| PauseFlags | src/PauseFlags.hpp, src/PauseFlags.cpp | four-byte flags construction 0x004E1CB0 | Complete 40-byte exact constructor; two-bit mode/one-bit practice, upper 29 retained, origin pending |
| TitleFlags | src/TitleFlags.hpp, src/TitleFlags.cpp | four-byte flags construction 0x0051D9B0 | Complete 66-byte exact constructor; four UI bits, upper 28 retained, original name/origin pending |
| ReplayFileHeader | src/ReplayRecords.hpp, src/ReplayRecords.cpp | disk value construction 0x00507480 | Complete 161-byte exact constructor on 48-byte value; implicit padding, retained byte-block inference and origin pending |
| ProgressRecordHeader / ProgressScore / PracticeScore | src/ProgressRecords.hpp, src/ProgressRecords.cpp | constructors 0x0050E500/0x0050E4A0/0x0050E6A0; availability 0x0052CA30 | Four complete exact members on actual 12/40/16-byte values; signed-byte availability reads +9 then +8, original declarations/origins and enclosing records remain open |
| ColoredVertex | src/ColoredVertex.hpp, src/ColoredVertex.cpp | typed value construction 0x00423470 | Complete 43-byte exact constructor; actual 20-byte value and Vector3 member established; original spelling/origin pending |
| TextLine | src/TextLine.hpp, src/TextLine.cpp | value construction 0x0046ABA0 | Complete 219-byte exact constructor; actual 320-byte ASCII record; origin pending |
| Rectangle | src/Rectangle.hpp, src/Rectangle.cpp | overlap 0x00470920; point construction 0x0040DE00/0x00414030; addition 0x004F58F0; rectangle construction 0x0040DE30 | Five complete exact contributions; actual atlas/Player integer pairs, modulo32 addition and inclusive wrapped arithmetic; origins pending |
| TextOutline | src/TextOutline.hpp, src/TextOutline.cpp | next-scale assignment 0x00416CF0 | Complete 18-byte authored exact setter; externally declared storage/raster lifetime remain open |

RandomState represents the four-byte STL engine subobject. It does not replace
its enclosing 28-byte game RNG, distribution state, four streams or locking.
Timer is a checked 16-byte value record with a raw-word/bit-field flag view.
Add/tick use the independently anchored default global clock slot and repeated
float receiver calls. Other timer modes and the enclosing clock protocol remain
open; the shared float view does not establish the full clock-controller owner.

`config/match-units.toml` owns sixty objects and one canonical profile per source.
Two hundred ninety-nine units cover complete COFF function contributions. Library units and units
with pending origin review can be replayed without becoming authored progress.

REF-032 absorbs the score-record constructor through an independently rewritten
real member, while reviewing all162 SmallScore/StageCompletion implementations.
The reference free helper itself remains nonexact. HUD/Overlay values add two
more complete constructors. REF-033 closes all134 HUD body reviews and adds
three real Dialogue value/text contributions through an independent rewrite.
REF-034 closes all376 Overlay body reviews,180 nonexact/196 support, without
adding canonical units. Fifty structural matches still require real native
owners/prototypes/vtables/relocations; synthetic StandardWeapon construction and
trivial destruction differ from original lifetimes. Shared decoder storage remains external;
unmatched final SJIS leads and malformed/unbounded inputs are outside acceptance.
Actual owner/vtable/Animation/Scheduler/SaveManager/Replay resource, checked-array
and EH lifetimes remain unclosed. See REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md.

REF-035 adds src/ScalarMath.hpp and src/ScalarMath.cpp with four complete cdecl
float/double CRT wrappers,153 bytes. All16 original ECL math implementations
have scoped decisions; wrap_angle uses existing normalize_angle rather than
another canonical unit. The original CRT startup/error/exception domains and
actual VM/Enemy/vector/interpolation owners remain open. REF-036 closes all144
ECL implementations, including the remaining128 with1 absorbed/26 nonexact/101
support. Existing GameRandom::signed_unit absorbs the semantic adapter; no
additional source/units. REF-037 closes230 Gameplay bodies and adds six natural
ScriptStack/EnemyCounters members,595 complete bytes; Gameplay789 remains pending at that checkpoint. REF-038 adds
src/EnemySpawn.hpp/.cpp and src/EnemyMovement.hpp/.cpp, and extends the shared
Interpolation template naturally to Vector2. Four complete constructors405
bytes exactly replay with actual84/100/388/64-byte values; all236 additional
bodies individually reviewed, prior movement constructor upgraded separately.
Gameplay553 remained pending at that checkpoint. See REFERENCE_ENEMY_MOVEMENT_REVIEW.md.
REF-039 adds EnemyHealth/EnemyPattern actual28/168-byte values and nine complete
members677 bytes. All141 damage/drop/defeat/cleanup/mesh bodies individually
reviewed, plus two prior reset upgrades; Gameplay412 remains pending. Full
health status widths and real count/Timer protocols are accepted independently
of the unresolved whole owners. See REFERENCE_ENEMY_DAMAGE_REVIEW.md.
REF-040 closes243 additional entity-opcode body reviews without new source.
All175 existing canonical contributions remain exact. Original224 defined
cases/174-slot table/704-byte index are independently verified, but optional-int
source handlers and Services do not establish full native dispatcher ownership.
Gameplay169 remains pending. See REFERENCE_ENTITY_OPCODE_REVIEW.md.
Native Stack/runtime/
resource/vtable/allocator ownership differs from reference owning objects;
see REFERENCE_GAMEPLAY_ECL_REVIEW.md.

REF-029 closes the413-body Bullet, Laser and Damage Regions review begun at
REF-028: three absorbed,214 nonexact,196 support. Eight natural contributions
add658 complete bytes with independent array/allocator/typed-vector/signed-count/
script consumers and PE anchors. The complete style initializer establishes all
4300 data words and the actual writable BSS array; maintained source declares
storage externally and supplies only the radius member read. The twelve other
reference structural matches lack closed native owner/vtable/lifetime identity.
Full pool/ANM/PMR/metadata/EH and resources remain open. See
REFERENCE_BULLET_LASER_DAMAGE_REVIEW.md for individual-record and oracle limits.

REF-027 batches all Effect and Special State implementations. Shared actual
value members add765 complete exact bytes with no enclosing owner facade.
Interpolation begins with live const references and separate signed setters;
implicit padding and float payload copying follow native code. The real
Effect13044/SpecialB4 owners, typed intrusive lists/handles/arrays, original
vtable/EH/resource/callback lifetimes remain open. See
REFERENCE_EFFECT_SPECIAL_REVIEW.md for all family and oracle limits.

REF-026 reviews Title as one coherent batch. Its four-byte flags at +0x58D4 are
a real independent value, with four source bit fields and upper bits retained.
The practice availability predicate is a member on the already recovered
sixteen-byte score value; whole-Profile selector validation remains separate.
These add 121 complete exact bytes without a padded Title/Profile facade.
Native handle arrays, mesh, callbacks, five Cursors, Worker, resource ownership,
EH and whole-page ABI remain open. See REFERENCE_TITLE_REVIEW.md.

REF-025 batches Progress and Replay. Actual disk/score/practice values and Replay
operations on the existing InputButtonState add 986 complete exact bytes. The
six Replay words are scalar fields, alongside two std::array histories. Original
fill/index callee identities precede probes; source preserves modulo32 arithmetic
and natural constructor padding. Full Profile/Metadata/Snapshot/SaveManager and
Replay/Stage/UserHeader/chunk/link/Configuration/PlayerTable resource and EH
ownership remain open. The reference bool append ABI and merged rewind(bool)
are recorded as differences, without importing a padded whole receiver.

REF-023 batches Options and Key Config and adds the complete 46-byte Timer
signed greater-than member at 0x00461070. Independent callers establish its
current-field read and thiscall bool/RET4 ABI on the existing sixteen-byte value.
Origin and original spelling remain pending. Options/Key/Cursor/Graphics/Sound
lifetimes and native helper partitions remain open; none is represented by a
padded facade to promote a state setter or callback.

REF-022 reviews all text-renderer implementations together. TextLine recovers the
actual 320-byte queue value, including a typed Vector3 and two separately stored
unknown words. Its natural initialization preserves char[256] clearing followed
by Vector3 construction and individual scalar initialization. IntPoint and
IntRectangle are actual atlas/job value records, without resources or padding.
The overlap predicate uses unsigned modulo32 endpoint sums before signed tests.
The next-outline-scale setter declares its original storage externally; native
raster consumes this state and restores one. Vector3's multiply assignment
retains the actual scalar-lane member and reference-return ABI. These small
components do not supply a fabricated Bitmap or Renderer owner. Full typed ANM,
PMR/callable-list/Worker/allocator, GDI/COM and renderer lifetimes remain open.

REF-021 reviews ScreenEffect as a complete batch and adds two real Timer members:
the 17-byte fractional-age read at 0x00423BD0 and the 46-byte signed <= predicate
at 0x00423590. The original read returns through x87 ST0; the predicate retains
thiscall/bool/RET4. Original names and origins remain pending.

The native rectangle routine constructs four ColoredVertex values through an
array-construction helper with stride 20 and constructor 0x00423470. Each value
contains the existing typed Vector3, reciprocal w and color at offsets 0/12/16.
Its constructor calls the independently recovered Vector3 zero constructor,
then clears the remaining fields. Rectangle drawing later sets reciprocal w to
one and packs diffuse color before FVF 0x44/stride-20 submission. This accepts
the complete value constructor; full ScreenInf, renderer caches, D3D device and
allocator lifetimes remain open. No enclosing owner facade is introduced.

REF-019 batches the Timer and physical input protocols used by Ending. Timer's
actual constructor initializes four words, including positive floating zero.
Its conversion and signed remainder read current only. Postfix operations have
the independently observed dummy integer argument and delegate to actual tick
or subtraction members. Integer subtraction uses modulo unsigned negation
before converting back, preserving the x86 NEG result including INT32_MIN.
The natural integer += body is maintained as a dependency but remains nonexact:
the compiler emits an extra XORPS before conversion, 33 versus 31 bytes.
Exact wrapper contributions retain independent native call anchors without
claiming that dependency matches. These six additional Timer origins and the
original operator spelling remain pending. Tests construct dirty Timer storage,
check sentinels, signed edges and stepping through shared production bodies.

InputButtonState::current_bits preserves the full uint32 mask, including bit31.
The held-frame member requires a valid receiver and index 0..31, calls the real
current-query member, then indexes the actual thirty-two-counter std::array at
offset 0x198. Both native call anchors were independently read before compilation;
the shared array helper does not receive another authored function credit.
Portable tests check every valid index, full counter values and complete-byte
nonmutation. These methods add no original polling, nullable slot selection,
input-global startup or Ending scene lifetime implementation.

REF-020 adds Trophy's shared-buffer decoder and its complete 0x704-byte Message
record: signed id, title[256], description[2][3][256]. Native resource allocation
uses that stride and parsing writes the seven actual string rows. Reset changes
only id to -1. Decode follows the byte-key recurrence, includes the terminating
NUL, and overwrites the actual shared 256-byte result. Its valid domain requires
an encoded NUL within 256 bytes; concurrent/reentrant use is unsupported. Tests
use a closed-form key calculation for all lengths, high bytes and wraparound,
checking untouched trailing bytes and shared-result replacement. These functions
do not supply a PMR string encoder, parser, record allocator or TrophyInf lifetime.
The actual Timer integer assignment wrapper delegates to existing set; this
additional complete member retains pending origin/operator spelling.

AnimationHandle is the actual four-byte value used by Notice's seven-element
array and separate secondary member. Native construction zeros that word and
returns the receiver. Resolve reads the word and clears it after a failed lookup;
interrupt members pass the stored word to the real Controller. These consumers
establish value storage without defining an artificial Notice or Controller.
Only construction is maintained. Full member protocols, allocator/resource
lifetimes and authored versus compiler-synthesized constructor identity remain open.

Vector3 is the actual twelve-byte three-float value used by Card's position.
Its default constructor writes positive zero to each lane; coordinate construction
copies all three float representations. Native smoothing uses separate subtraction,
scalar multiplication and in-place addition, with hidden aggregate return storage
and a receiver reference for addition. Natural C++ preserves those member
boundaries and the independently observed coordinate-constructor anchor.
All five complete contributions replay exactly, including relocation fields.
Original type spelling and source/library origin remain unknown; none adds
authored progress. This value owner does not reconstruct Card, enemy lookup,
animation ownership or the original numerical exception environment.

TaskInfo's observed RTTI is TaskInf. Its three-slot vtable contains deleting
destructor, enable and disable; reference callback-owner naming does not change
this identity. Separate callback helpers preserve the original virtual-wrapper
partition. The constructor's observed flags=2 and null pointers are represented
in member defaults, but its full original contribution is not accepted.

DebugMemoryResource's RTTI is debug_memory_resource. Its four-slot PMR interface
and pointer-sized receiver are independently observed. An always-true equality
override belongs to this custom class, unlike standard identity-equal resources.
The std base constructor/destructor helpers have shared empty code; their
anchors do not establish a unique owner for each shared target address.

Worker owns a real std::jthread and atomic<bool>. Its user-provided constructor
initializes those members while preserving tail padding; no matching-only body
or explicit padding is used. Do not instantiate/destroy it as a complete linked
worker until its native lifetime and synchronization protocol are reconstructed.

`probes/` remains infrastructure-only. Production currently builds objects for
component comparison; no whole-game linker or runtime acceptance is available.
Future owners must close storage, initialization, ABI and lifetime protocols.
Reference module names do not prescribe our directories or translation units.

InputButtonState retains all 704 observed bytes, including state outside the
update routine copied by native aggregate frames. InputDevice has its observed
x86 980-byte layout and a real forward-declared COM pointer. Its three partial
initializers preserve history and other header fields. No original constructor,
device polling, ownership or enlarged reference Controller is imported. Portable
tests initialize these records explicitly and do not prove game-global lifetime.

InputBindings owns three real 16-byte records of eight signed int16 fields.
Default slot initialization precedes the twenty-four binding assignments.
ConfigurationFlags represents nine observed low option bits and retains the
other twenty-three; native consumers identify six named graphics options.
The default-slot and flag contributions may be compiler generated, so exact
replay does not add authored credit. These declarations do not replace the
original 176-byte configuration, its raw-copy/load/save lifetime or fixed globals.

GameRandom closes the observed 28-byte object storage using the actual uint32
standard engine. Its default range differs from the explicitly seeded range.
Bounded and floating wrappers preserve original calls, arithmetic and return
ABI, but next and seed require the native tracked slot-10 locking protocol.
They remain undefined. Portable wrapper tests explicitly supply a deterministic
next observation and establish no linked game sampler/global startup.

WindowState's x860x2138 storage follows independently observed global clearing,
complete native construction and frame/path consumers. It contains real typed
pairs, paths, clock values, flags and repeat counters with natural alignment.
Five field members, repeat-counter reset and fixed-global system restoration are authored exact;
flags default construction is origin pending. The original constructor and
window_state storage are undefined. Portable fixture{} initialization is test
setup and does not supply original startup. WindowApi compiles Windows imports
separately; no test invokes foreground/system-setting APIs. Its exact foreground
wrapper has pending source/origin identity because the observed caller ignores
its result. Locale detection preserves the original full-width int result.
No linked window or whole-frame runtime is accepted.

Input mask queries retain uint32 bit31 and leave all 704 bytes unchanged.
The repeat query calls the actual pressed method and inspects repeat8 only.
Window repeat reset updates first/second/elapsed in a real twelve-byte record;
native window creation supplies four separate threshold values.

FontDetection preserves the stdcall/RET16 enumeration callback. The original
initializer selects availability bytes through a global pointer at 0x5B6748;
only its declaration is maintained. The full font table, indexed slot methods,
fallback selection and OS resource lifetime are not reconstructed by this unit.

SceneResources closes the two observed free cdecl orchestration routines,
including eight ordered calls per routine, early failure returns, three optional
zero-helper calls and the unused zero argument passed to stone-menu release.
The forward-declared resource pointer types define no owner layout or storage.
All dependency functions remain undefined; independent original caller/callee
observations establish their anchors and ABI. Test-only observations check
failure stopping and teardown order without original OS/resource execution.

SoundEffects declares real request (0x208), command (0x10C) and x86 channel
(24-byte) records, with natural scalar/array/COM pointer storage. Construction
preserves separate scalar stores and array memset calls rather than changing
the entire enclosing SoundInf initialization. The independently queried memset
entry supplies two canonical anchors. Constructor exactness does not resolve
authored versus compiler-generated origin; all three remain excluded from the
authored ledger. Release uses the real SDK COM slot and a separate Windows TU.
Portable dirty-storage tests cover every request/command byte and channel field;
no COM object or driver is invoked by those fixtures. Full SoundInf, PMR arrays,
WaveReader SDK fields, CSound/CStreaming vtables and diagnostic allocator
lifetimes remain unresolved. No opaque class padding or merged reference owner
is imported to force small stream methods exact.

REF-024 closes the actual Cursor container storage without defining Pause, Key,
Options or Stone Menu as padded facades. The PMR vector uses the native default
resource; each std::stack owns a real std::deque and its release-mode proxy.
Save/restore keep both histories paired and clear exclusions without freeing
capacity. Full-width predicates reflect independently observed EAX consumers.
The natural constructor is maintained for the shared semantic body and portable
resource tests, but its native exception emission remains nonexact. The eight
canonical members do not accept complete original construction, library runtime
or menu linkage. PauseFlags is the real four-byte bitfield value constructed
inside Pause; it introduces no enclosing owner or global definition.

REF-030 adds seven shared Player/Bomb value contributions,581 complete bytes.
Angle has a34-step reduction cap; Motion contains three typed Angle and Vector3
members and a genuine control word. Existing generic interpolation supports
five Vector3 values at size84; only its constructor adds exact credit. IntPoint
extends the existing atlas value through an independently shared coordinate
constructor. All144 units replay; the884-entry reference batch remains ongoing.
See REFERENCE_PLAYER_BOMB_ITEM_REVIEW.md for boundary, profile and oracle limits.

REF-031 adds Motion update28 and outside-bounds156 without extending its72-byte
storage. Update preserves same-receiver velocity-before-position dependency
calls; the actual dependency implementations remain undefined. Bounds preserves
full-int return, strict edges and unordered comparisons; native caller tests EAX.
Portable tests observe dependencies and check geometry/IEEE/nonmutation. All146
units cold-replay across38 objects. All884 related reference bodies reviewed;
owner/resource/vtable/EH and whole-game acceptance remain open.

REF-041 adds genuine PlayerRecord240,46 canonical units3654bytes and natural
implementations of all45 setters. Two shared native heads remain credited only
once through existing owners. All169 remaining Gameplay implementations have
individual decisions; all1019 Gameplay reviewed, global6100terminal/844pending,
gaps91/22. Full221unit/51object/15890byte cold replay and24080 independent guarded
C++20/UBSan checks pass; real Table/Session/Game/HUD/worker/resource lifetimes and
original field names/origins remain pending. See REFERENCE_GAME_LOADING_REVIEW.md.

REF-042 adds five genuine value/texel source owners and three instantiations of
the existing Interpolation template. Thirteen complete units add 1,387 bytes;
all 234 units cold-replay from 56 objects over 17,277 disjoint bytes. All 540
Sprite implementations have individual decisions. Natural Base construction
remains nonexact; full Animation/Controller/Worker/VM/resource lifetimes and
original names/origins remain open. See REFERENCE_SPRITE_REVIEW.md.

REF-043 adds actual FogValue28 and shared FogInterpolation164 without accepting
complete Camera/Background/ScriptState/ANM/VM/EH/resource owners. Seven complete
units add 1,043 bytes; all 241 units / 57 cold objects / 18,320 disjoint bytes
replay. All 121 StageBackground implementations have individual decisions.
Packing requires representable int32 channel truncation in portable C++; see
REFERENCE_STAGE_BACKGROUND_REVIEW.md for native emission and historical limits.
