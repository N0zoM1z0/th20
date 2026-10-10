# Damage Region routing and configuration

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-050 reconstructs one coherent native region protocol: the 2,696-byte
collision dispatcher, its rectangle/circle configuration paths and position,
context, allocation-flag, Motion and identifier dependencies. Thirteen complete
units add 3,532 disjoint comparison bytes. All 343 units / 65 cold objects /
55,692 complete comparison bytes strictly replay after rebuilding the previous
graph. Authored-origin credit remains 57 functions / 4,074 bytes.

## Native evidence and storage

Attested Ghidra queries and independent decoding of the locked PE precede the
compiler probes. Allocation at 0x004BFE30 requests 196 bytes; construction at
0x004BFFB0 and the configuration, collision and controller consumers establish
these actual subobjects:

| Offset | Storage | Evidence and acceptance |
| --- | --- | --- |
| 00 | Five-pointer linked-node prefix | Self pointer, next, previous, opaque list owner and observer; constructor411970, mutations411EE0/411F30 and detach consumers |
| 14 | Four-byte flags | Active bit0, shape bits1..3; configuration clears bits4/6 and preserves bit5/upper bits |
| 18/1C/20 | Three floats | Polygon/star outer and inner radii; circle configuration also writes the third scalar |
| 24/28/2C | Angle, angular velocity, Vector2 | Shape orientation and rectangle/ellipse dimensions |
| 34/7C | Motion72 and Timer16 | Actual existing canonical value owners; position starts at Motion offset0 |
| 8C/A4/B0 | Four-byte identifiers | Existing zero constructor, value access and assignment; original tags remain unknown |
| 90..BC | Four-byte state slots | Damage94, signed cooldownA8 and groupAC independently consumed by controller branches; side countB8 consumed by polygon/star calls; other roles and signedness remain provisional |
| C0 | Opaque Context pointer | Native producer/consumer and getter; no invented complete Context layout |

The maintained linked prefix is a real first member. Member versus source-level
base inheritance is an inference from construction/access emission, not an
assertion of recovered original class spelling. Region and FunctionChainNode
now use one `IntrusiveLink<T>` body with correctly typed self/neighbor pointers;
neither value is cast to the other. Existing FunctionChain constructor and
insertion units retain their complete physical heads and exactness. List/iterator
owners stay opaque. No fabricated destructor, cleanup or allocator is introduced.

## Complete accepted functions

| Address | Bytes | Maintained operation |
| --- | ---: | --- |
| 004C1030 | 2696 | DamageRegion::intersects |
| 004C1C50 | 290 | DamageRegion::configure_rectangle |
| 004C1D80 | 260 | DamageRegion::configure_circle |
| 004C0F50 | 22 | DamageRegion::position |
| 004C0FE0 | 20 | DamageRegion::context_value |
| 004C1000 | 48 | DamageRegion::is_heap |
| 004C2030 | 37 | DamageRegion::set_position |
| 0040BDA0 | 14 | Motion::position_ref |
| 004393F0 | 35 | Motion::set_position |
| 004A73D0 | 27 | Motion::clear |
| 0040C300 | 16 | Identifier32::get |
| 004117A0 | 21 | Identifier32::operator= |
| 004C0210 | 46 | Identifier32::equals |

All thirteen are complete receiver functions. Dispatcher returns AL bool and
pops16 bytes; configurations return the full identifier word and pop24/20;
identifier equality returns full-EAX integer status and pops4. Native
controller4C0480 reads dispatcher AL with MOVZX; lookup4C0D00 tests equality EAX.
The apparent wide decompiler returns are rejected using these independent calls.

Position-reference head40BDA0 previously served an independent empty-PMR-base
constructor anchor; it had no canonical coverage unit. The new complete14-byte
unit counts that physical head once. Identifier get40C300 also serves linked
iterator/node pointer views. Constructor411970 and zero-word constructor425CC0
already have canonical coverage and receive no additional credit here. The
Angle float view4292E0 and memset544760 retain established independent anchors.
Identical head bytes do not prove original type/template names or library origin.

## State and routing behavior

The dispatcher repeatedly reads the three-bit kind and chooses rectangle,
circle, ellipse, regular polygon or star. A non-null Vector2 selects rectangle
query dimensions; a null size selects a circle query radius. Query and region
angles retain their distinct positions in each geometry call. Circle/circle
uses inclusive squared XY distance and computes the radius sums before the
position/distance calls. Kinds5..7 return false. Activation filtering belongs to
the caller: this function does not consult the active bit or Context. Existing
native geometry quirks and signed polygon counts remain unchanged.

Both configurations activate the region, assign kind, clear only bits4/6, clear
all72 Motion bytes, then copy the supplied position. They reset target/cooldown/
group and the observed damage/cap/state slots, preserving identifier, linked
prefix, Context and unrelated fields. Rectangle configuration writes dimensions,
normalizes angle and clears angular velocity. Circle configuration writes its
radius and third scalar, preserving dimensions, angle and angular velocity.
Timer assignment retains the canonical initialization and signed-duration rules.
A position reference into the cleared Motion observes zero when copied later;
this native aliasing order is explicitly tested. Motion position assignment
copies all XYZ lanes and otherwise preserves Motion state.

## Compiler observation and verification

DamageRegion, Motion and Identifier32 use local precise-FP/no-GS profiles. Existing FunctionChain retains its cdecl-default profile.
Shared template manglings replace only the three canonical link symbols; old
coverage addresses, extents and authored-origin decisions remain unchanged.
These locally matching recipes do not prove a whole-game build recipe.

Each full target contribution, return cleanup, branch destination and direct
callee is reconciled against attested instructions. Canonical relocations bind
independently audited existing/new method anchors; diagnostic solved destinations
are never promoted. No comparison prefix, target byte array, assembly, padding,
inert local, profile-selected body or fake ABI is used.

Public C++20/UBSan checks cover all ten shape/query combinations, near/far cases,
ignored Z, inactive/high flags, invalid kinds without input reads, rotation,
inclusive circle tangency, configuration field preservation, negative duration,
clear-before-copy aliasing, full Motion clearing/assignment, self-position alias,
identifier high bits/equality/allocation bit and actual typed node insertion.
All previous public semantic checks and complete cold exact units are replayed.

## Reviewed but deferred neighborhood

| Candidate | Current result / remaining dependency |
| --- | --- |
| 4BFFB0/359 Region construction | Natural source317 preserves member construction/default state; native FS registration, cookie and shared handler5679A0 add42 bytes. Lifetime/EH ownership is unresolved. Nontrivial-link destructor probes add cleanup states absent from native and are rejected. No exact credit. |
| 4C03D0/164 Region update | Complete native body reviewed: motion update, radius growth, angle update, target clear, timer/cooldown and conditional retirement. Motion update47A1F0 is already canonical; retirement4C1F30/controller ownership remains open. |
| 4C1F30/138 retirement | Complete body reviewed; uses Context lookup, controller detach, active/identifier reset and heap ownership. Controller/allocator lifecycle remains open. |
| 4C0D00/264 controller lookup and 4C0E60/225 allocation | Complete bodies reviewed; list iterator EH, pool and fallback heap paths require the real controller/container lifetime. No wide controller facade is introduced. |
| 4C0120/230 destructor, 4C02D0/248 controller update | Complete bodies reviewed; actual pool/list/iterator destruction and timer/controller storage remain unresolved. |
| 4C0480/1707 damage controller | Used for specific independently inspected AL/field consumers; full body acceptance is pending. |
| 4BFE30/73 allocator | Complete body reviewed, including196-byte allocation and initialization40C080. Allocation base/factory ownership remains open. |
| 4C0E10/67, 4C1C10/54, 4C1F00/39, 4C1FF0/51 handles | Lookup/retire/set-position forwarding depends on global Context/controller and handle lifetime. |
| 4C1AE0/151, 4C1B80/140 creation wrappers; 4C1EB0/70 detach | Observed configuration/list routing; full controller/pool ownership is pending. |
| 4C0C40/19, 4C0C60/67, 4C0CB0/13, 4C0CC0/27 | Controller endpoint/generation/callback/pool helpers require actual controller storage and ownership. |
| 4C0CE0/25, 4C0F70/55, 4C0FB0/38 | Player/context record paths require their real owners. |
| 4C1AC0/26, 4C1E90/26, 4C1FC0/45 | Distinct Enemy/Context flags outside the accepted Region owner. |

Original names, unobserved signedness and semantic tags, exceptional FP/traps,
list observer/lifetime ownership, source partition identity, origins, full
controller resources, linkage and whole-game runtime remain open. Natural
construction in portable fixtures validates its observed default state, not
native EH equivalence. Existing reference decisions remain complete and unchanged
at6,945 bodies /113 grammar files. The native reconstruction goal continues.
