# Target inventory and initial architecture boundary

EXACT-054 closes signed block decryption, the persistent LZSS decoder, seven
shared compression-tree operations and actual malloc/array/PMR allocation:
sixteen complete bodies add 2,676 bytes. All 393 units / 70 cold objects / 61,579
disjoint comparison bytes strictly replay. The allocator owns the real PMR
resource; startup and its first word's meaning remain open. The compressor and
full archive manager are audited and remain pending. See
EXACT_ARCHIVE_CODEC_RECONSTRUCTION.md. The user now prioritizes core large
dispatchers: pursue the complete 11,110-byte ECL tick at 0053B5C0 and its real
owner before returning to additional archive leaves. Earlier entries are
historical checkpoints.

EXACT-053 closes the actual Worker16 launch/replacement and shutdown lifetime:
five complete bodies / 666 instruction bytes plus five destructor alignment
bytes. All 377 units / 67 cold objects / 58,903 disjoint comparison bytes strictly
replay. Shared slot-6 guards, real jthread/atomic storage and complete EH metadata
preserve native nested detach and join ownership. The 4,119-byte loading body
and graphics/snapshot callers are completely audited, but their full owners and
resource/allocator/global lifetimes remain open. Two standard thread constructor/
move library bodies also retain emission differences. See
EXACT_WORKER_RECONSTRUCTION.md. Earlier entries are historical checkpoints.

EXACT-052 closes node construction/access, actual shared recursive locking and
the random stream seed/next protocol: nine complete units / 693 body bytes plus
five alignment bytes. All 372 units / 67 cold objects / 58,232 disjoint complete
comparison bytes strictly replay. The registry owns 22 real std::recursive_mutex
values and byte depths; stream operations unconditionally guard slot 10. Tests
use an owned registry; production global/thread startup remains undefined.
The 611/587-byte update/draw dispatchers and both 381-byte sorted insertions are
fully reviewed but remain nonexact pending iterator initialization policy and
controller/allocator lifetime. See EXACT_LOCK_RANDOM_RECONSTRUCTION.md.
Earlier entries are historical checkpoints.

EXACT-051 closes the actual 20-byte linked node, 24-byte sentinel list and
8-byte current/pending observer protocol. Twenty complete contributions include
Region nonthrowing construction/update and position/vector dependencies:
1,827 body bytes plus 15 compiler alignment bytes; all 363 units / 66 cold objects /
57,534 disjoint complete comparison bytes strictly replay. Native EH metadata
corroborates the nonthrowing contract, closing the previous Region constructor
mismatch. Complete damage control is reviewed; enclosing Context and controller,
retirement, locking and allocation lifetimes remain open. See
EXACT_INTRUSIVE_LIFETIME_RECONSTRUCTION.md. Earlier entries are historical.

EXACT-050 closes the2,696-byte Damage Region collision dispatcher with its
rectangle/circle configuration and direct Motion/identifier protocols:13 complete
units /3,532 new bytes. All343 units /65 coldobjects /55,692 disjoint complete
comparison bytes strictly replay. Actual196-byte Region uses a shared typed
linked-prefix body with FunctionChainNode. Constructor EH and full controller /
list/pool lifetime stay unresolved. See EXACT_DAMAGE_REGION_RECONSTRUCTION.md.
Earlier entries are historical checkpoints.

EXACT-049 closes the twelve-root rectangle/segment neighborhood and nine direct
planar dependencies: 21 complete units / 10,759 new bytes. All 330 units / 63 cold
objects / 52,160 disjoint complete comparison bytes strictly replay. Actual
Vector2/Vector3 arrays and one typed XY rotation protocol preserve native owner
boundaries and share scalar head458FA0 without duplicate coverage. Complete
collision controller, origins and runtime remain open. See
EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md. EXACT-048 previously added ten
collision/vector contributions / 3,841 bytes; all previous units are rebuilt.
Earlier entries are historical checkpoints.

EXACT-047 reconstructs the distinct current-first100-byte Enemy position curve:
eight complete units / 2,716 bytes, centered on its 2,433-byte update. Existing
Movement388, Vector3 and Motion owners retain their layouts. All 299 / 60 cold
objects / 37,560 disjoint comparison bytes strictly replay. Native caller stride, hidden result,
signed duration and direct assignment corroborate component ownership; full
Enemy/PMR/ECL/resource lifetime remains open. See EXACT_ENEMY_INTERPOLATION_RECONSTRUCTION.md.
Earlier entries are historical checkpoints.

EXACT-046 reconstructs the shared 4 KB easing dispatch and all eight generic
interpolation updates, with their immediate arithmetic/storage dependencies.
32 complete units add 13,952 bytes; all 291 / 60 cold objects / 34,844 disjoint
comparison bytes strictly replay. The existing typed owners and layouts remain
canonical. Enemy's distinct current-first/per-axis protocol remains separate.
See EXACT_INTERPOLATION_RECONSTRUCTION.md. Earlier entries are historical.

EXACT-045 closes the shared Motion72 velocity/position protocol and direct
angle/vector/math dependencies in one 18-unit native reconstruction batch.
Complete dispatch-table and security-cookie evidence accompanies both primary
bodies. All 259 units / 59 cold objects / 20,892 disjoint comparison bytes
strictly replay; authored origin totals remain separate. See
EXACT_MOTION_RECONSTRUCTION.md. Existing reference review is complete; the
current goal advances substantive native reconstruction in coherent batches.
The sections below are historical checkpoints.

REF-044 closes the existing-reference review: all 6,945 implementation bodies
have individual terminal decisions and all 113 parser-gap files are manually
reconciled. One historical naked ABI invoker was recovered from a parser
omission; all prior IDs/hashes are unchanged. The final support/bridge batch
adds no native unit. All 241 complete units / 57 objects / 18,320 comparison
bytes still replay exactly. Full native owners, origins, linkage and gameplay
remain open; see REFERENCE_SUPPORT_REVIEW.md. The entries below are earlier
component checkpoints.

REF-043 establishes actual FogValue28 and shared FogInterpolation164 through
native camera construction, five value strides, seven-word copies and hidden
result arithmetic. Six natural members and one shared template constructor add
1,043 complete bytes; all 241 units / 57 cold objects / 18,320 bytes replay.
Packing retains low bytes after representable int32 channel truncation. Full
Camera/Background/ScriptState/ANM/VM/vptr/EH/resource lifetimes remain unclosed.
All 121 StageBackground bodies individually reviewed; global 6,761/183,
grammar 97/16. See REFERENCE_STAGE_BACKGROUND_REVIEW.md.

REF-042 establishes genuine IntegerTriple12, Matrix4 with sixteen floats,
AnmVariables64, three Sprite vertex values and three additional instantiations
of the shared Interpolation template. Native nested calls and array constructor
pointers/strides corroborate actual storage. Four cdecl texel accumulators retain
packed channel widths, alpha gating, wrapping and alias order. Thirteen new
complete units add 1,387 bytes; all 234 units / 56 cold objects / 17,277 bytes
exactly replay. Full Animation/Controller/Worker/VM/EH/resource owners remain
unclosed; natural Base construction is 707 versus 725 bytes and rejected whole.
All 540 Sprite bodies individually reviewed; global 6,640/304, grammar 96/17.
See REFERENCE_SPRITE_REVIEW.md.

REF-041 establishes genuine PlayerRecord240 through original array stride/count,
complete constructor,64-bit score and mutating power consumers.45 setters have
natural individual members; two alreadycanonical shared heads get no second
credit.46 new complete units add3654bytes;221units/51coldobjects/15890bytes replay.
Actual integer/byte fields and implicit gaps avoid a whole-owner facade. Table/
Session/Game/HUD/worker/EH/resource lifetimes and original names/origins remain
unclosed. All169 remaining Gameplay bodies individually reviewed; Gameplay1019
complete, global6100/844 and gaps91/22. See REFERENCE_GAME_LOADING_REVIEW.md.

REF-040 reviews all remaining entity opcode/adapter/fixture implementations:
243 bodies across22 files, without adding canonical source. The original State
member48C010 owns a shared EH/aligned frame and a174-slot/704-byte jump-table
pair;224 defined opcodes/default-zero routing are independently verified. Free
optional-int handlers and virtual Services do not restore that single native
member or complete owner/lifetime graph. All175 unchanged canonical units remain
exact; Gameplay169 remains pending. See REFERENCE_ENTITY_OPCODE_REVIEW.md.

REF-039 establishes real EnemyHealth28 at EnemyState+18C and EnemyPattern168
at+1A8 through original constructor calls. Health exposes wrapping accounting,
signed division7 and full-EAX queries; pattern owns two sixteen-element arrays,
Timer and radii. Nine natural complete members add677 bytes;175 canonical units/
50 cold objects/12236 disjoint bytes replay. Full Enemy/Player/HUD/ANM/PMR/ECL
owners and active dependency paths remain unresolved. All141 additional bodies
individually reviewed; Gameplay412 remains pending. See REFERENCE_ENEMY_DAMAGE_REVIEW.md.

REF-038 establishes native EnemySpawn84 with Counter48 at20 and a four-byte
value at50 (original tag/role unknown), current-first Enemy position interpolation
100, generic Vector2 interpolation64 and movement388 with six real subobjects.
Four complete natural constructors add405 bytes;166 canonical units/48 objects/
11559 bytes replay. No whole Enemy or padding facade.236 more bodies individually
reviewed, Gameplay553 pending; resource report has five stale source hashes.
See REFERENCE_ENEMY_MOVEMENT_REVIEW.md.

REF-037 establishes native ScriptStack24 as a PMR vector16 plus byte SP/BP,
and EnemyCounters48 as four integer words/eight floats inside EnemyData.
Six natural members add595 complete exact bytes, without reconstructing the
enclosing runtime/controller/Enemy owners. Generic stack pop is a genuine
output-pointer/status dependency whose implementation remains undefined.
Gameplay's72-byte reference runtime and correct virtual slots still differ in
parser/frame/call/list/pool prototypes;230 bodies reviewed,789 Gameplay pending.
See REFERENCE_GAMEPLAY_ECL_REVIEW.md.

REF-036 closes all144 ECL implementations for individual review. Native Stack24,
Runtime72 and eight-byte name/code records differ from the reference20/80/44-byte
owning types; Engine vtable order, pool allocation, status/output-pointer stack
ABI and original runtime ownership remain open. General53B5C0 dispatch has75
supported cases in98-entry table53E128; interpolation53E00C is inlined within
that function. Entity48C010 remains separate. Existing signed-unit exact source
absorbs one semantic adapter; no new canonical contribution. Gameplay1019
remains pending; see REFERENCE_GAMEPLAY_ECL_REVIEW.md.

REF-035 accepts four153-byte scalar math wrappers with genuine cdecl float
arguments,double CRT dependencies and narrowed ST0 results. All16 ECL math
implementations were individually reviewed at that checkpoint; REF-036 closes
the remaining ECL128, while Gameplay1019 remains pending.
Original CRT startup/error domains and native vector/interpolation/VM/Enemy
owners remain open. See REFERENCE_GAMEPLAY_ECL_REVIEW.md.

REF-034 closes all376 Overlay implementations; the entire672-body display/weapon
family is individually reviewed. Eighteen native factory positions bind sixteen
30-slot strategy owners directly to Weapon52FAD0, without the reference's extra
StandardWeapon construction layer. Destruction restores base vptr through a
separate deleting wrapper. Original allocator/owner/prototype/vtable/EH identity
remains unclosed;50 structural COFF matches add no canonical credit. Native
phase consumers test full EAX, beyond several fixture AL-only checks. See
REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md.

Dialogue contains a real four-byte flags member at104, retaining upper25 bits
on construction. Its shared text decoder uses BSS5C4A20 and a separate uint8 /
full-int SJIS predicate; all three complete contributions are exact. Result
storage remains external and decoding requires terminated assets with paired
lead bytes. All134 HUD implementations have REF033 decisions; actual140-byte
Dialogue/2D8-byte HUD vtable/EH/Worker/resource owners remain unclosed.

SmallScore owns an Animation and two eighteen-record arrays. Its actual68-byte
ScoreEntry contains typed Vector3/Timer members and preserves two alignment bytes.
HUD boss panels construct four8-byte gauges, and Overlay constructs an8-byte
counter. Three natural value constructors are complete exact; original float
roles, counter arithmetic and enclosing owner/vtable/EH lifetimes remain open.
All162 score/completion bodies have individual REF032 decisions; Overlay's376
are separately reviewed at REF034. Completion's raw-byte/full-EAX unlock return differs from
reference bool; Environment fixtures do not prove original getter/return ABI.
See REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md.

Player / Bomb / Item share actual Angle4, Motion72, VectorInterpolation84
and IntPoint8 values. Nine complete contributions cover constructors, arithmetic,
Motion update orchestration and full-int bounds;765 bytes without enclosing
facades. All884 related implementations have individual REF031 review decisions.
Underlying motion updates and full Player/Bomb/Item resource/vtable/EH owners
remain open; see REFERENCE_PLAYER_BOMB_ITEM_REVIEW.md.

Bullet / Laser / Damage Regions share an actual64-byte extended-command value,
40-byte shot parameters and44-byte x86 ECL operands, alongside two-float Vector2.
Four value constructors, three geometry routines and the bullet-radius query are
complete exact. All 413 implementations have individual review decisions at
REF-029. Original writable50*344-byte style storage is externally declared;
its complete initializer/data was independently audited without importing literals.
Full resource/EH/typed-array and pool owners remain open. See
REFERENCE_BULLET_LASER_DAMAGE_REVIEW.md.

The canonical executable is the user-selected Japanese TH20 v1.00a Steamless
variant. Exact release/provenance is in `TARGET_PROVENANCE.md`; machine and
section details are pinned in `config/target.toml`.

| Property | Observed |
| --- | --- |
| Format | PE32 / i386 / Windows GUI |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |
| Image size | `0x001F9000` (2,068,480 bytes) |
| `.text` virtual extent | `0x00401000..0x0056B47A` inclusive |
| Linker | 14.44 |
| Rich header | absent in game; present in companion `custom.exe` |
| Base relocations | present |
| Sections | `.text`, `.rdata`, `.data`, `.fptable`, `.rsrc`, `.reloc` |

Target-observed imports cover KERNEL32, USER32, GDI32, ole32, OLEAUT32,
DINPUT8, DSOUND, d3d9, d3dx9_43, WINMM, XINPUT1_4 and gdiplus. These establish
API dependencies, not ownership of specific game subsystems.

The target contains a CodeView/PDB path ending in `bin/Release/th20.pdb`,
plus authored source-path strings under `src/game`, `src/pack` and `src/script`.
Those strings can route owner discovery; a `Release` path does not prove
optimization flags. Preserve the original Japanese semantics and source
provenance where independently corroborated.

Ghidra's initial import exports 6,928 provisional function candidates. All
origins remain unknown and all boundaries remain unreviewed. Do not inherit
TH095's engine roles or authorship classifications from similar function names.
Private architecture metrics/call edges/global and string references are
exported under `.analysis/architecture/`; they rank leads, not completeness.

The state model follows TH095: candidate boundary (`functions.csv`), origin
(`function-origins.csv`), mapping (`reccmp-functions.csv`), source presence
(`implemented.csv`), and exactness (`matches.csv` plus canonical units) are
separate. Semantic acceptance, whole-game linkage and playable behavior are
also independent.

The shared menu Cursor uses a PMR vector and two standard stack/deque owners.
Native constructor, iterator and stack adapter graphs establish its storage and
resource ownership. Eight methods are exact; constructor exception emission is
still unresolved. The separate four-byte PauseFlags value is exact without
introducing an enclosing menu facade. These additions remain component objects,
with no complete menu or original allocator/runtime linkage claim.

Progress and Replay share actual disk-value protocols and Replay input history.
Four small constructors and two members on the existing InputButtonState are
complete exact contributions. They do not close the reference's raw giant disk
owners, original thread/file/allocator lifetimes or full Replay integration.
Native intrusive-template/std::array ownership and full-int append ABI differ
from the reference helpers and remain explicitly recorded for further recovery.

Title's four-byte UI flags are an independently constructed value at +0x58D4;
construction preserves 28 upper bits. Its practice-page predicate belongs to
the actual sixteen-byte disk score, reading signed bytes +9 then +8. Both small
components are complete exact. The 0x5978 Title callback owner, native handle
arrays, mesh, thread/resource/EH lifetimes and whole-Profile accessors remain
open. Injected Environment interfaces and CPU page fixtures do not establish
original virtual ownership, startup linkage or full rendered gameplay.

Effect / Special State share actual parameter and interpolation values. Four
small value constructors and twelve byte/float interpolation members are
complete exact; the native owners remain unclosed. Effect owns typed handle /
request arrays and Worker; Special owns actual intrusive list and typed handles.
Reference injected Environment interfaces, raw aggregate constructors and
recording-only allocator/GPU hooks do not establish these native lifetimes.
Original callback vtables independently identify Converging and Wavering update
heads missing from current Ghidra; full approved PE instruction flows were
reconciled without editing the database. See REFERENCE_EFFECT_SPECIAL_REVIEW.md.
