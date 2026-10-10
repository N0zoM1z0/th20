# EXACT-047: current-first Enemy position interpolation

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

This coherent native movement batch reconstructs the 2,433-byte Enemy position
update and its direct factor, indexing, duration and motion-assignment dependencies.
Eight complete functions add 2,716 comparison bytes, using the existing actual
100-byte EnemyMotionInterpolation, 388-byte EnemyMovement, Vector3 and Motion
owners. The earlier generic interpolation protocol supplies verified dependencies.

## Complete units and native callers

| Operation | Native entry | Complete bytes |
| --- | --- | ---: |
| Enemy position update/sample | 0x004A8D70 | 2,433 |
| Shared-mode factor | 0x004AAB70 | 83 |
| Per-axis factor | 0x004AAB10 | 89 |
| Enemy signed duration read | 0x00438500 | 17 |
| Vector3 indexed float reference | 0x00414580 | 22 |
| Float interpolation signed duration read | 0x0041CAF0 | 17 |
| Vector2 interpolation signed duration read | 0x00438520 | 17 |
| Motion vector_38 assignment | 0x0047A5E0 | 38 |

Wrapper-attested Ghidra and independently decoded locked-PE instructions reconcile
743 instructions across all eight complete contributions. Three unreachable
return/else jumps outside Ghidra's AddressSet are decoded, checked against their
predecessors and incoming edges, and retained in the full sample extent. No unit
has shortened prefix comparison or copied instruction/padding bytes in source.

Native caller 0x004A7710 walks movement values with stride 0x184 (388), tests full
signed durations at offsets 0xAC, 0xD8, 0x104 and 0x48, and calls the appropriate
float/Vector2/Enemy samples. Its position path supplies a twelve-byte hidden result
to 0x004A8D70, subtracts the previous Motion position and assigns the result to
Motion+0x38 before the already reconstructed position update. That independently
corroborates the existing six-child movement owner and the new direct assignment.
The entire enclosing caller remains unclosed; its PMR containers, Enemy fields,
animation resources, callback paths and security-cookie dependencies are separate.

## Storage, indexing and ABI

Current remains first at 0x00, followed by start/end/tangents at 0x0C/0x18/0x24/0x30.
Timer is at 0x3C, signed duration at 0x4C, three signed axis modes at 0x50, shared
mode at 0x5C and flags at 0x60. AxisModes now exposes the actual three-element
int32 array instead of treating distinct named members as an array.
Construction and all existing enclosing contributions retain their native bytes.

The native indexed Vector3 member returns the actual float subobject reference
at receiver+4*index and cleans one four-byte argument. Source addresses the named
coordinate storage through the object's byte representation, then casts the
aligned subobject address to float; it does not index a float pointer across
separate members or introduce alternate storage. Static assertions retain the
0/4/8 offsets and twelve-byte size. The established index domain is 0, 1 or 2;
there is no native bounds check or additional const overload claim.

Both factors return float through ST0 and call existing Timer::fraction and the
shared cdecl easing. The axis factor reads one actual signed mode slot; the shared
factor reads mode at 0x5C. Complete duration readers return full signed EAX,
preserving negative durations rather than narrowing to an activity boolean.
Only Enemy/float/Vector2 duration heads receive mappings; other generic template
emissions remain unbound. Motion assignment copies the actual three words and
retains all other fields, including flags, with a const-reference/void member ABI.

The Enemy stop member shares the previously accepted 0x00429990 duration-at-0x4C
head. Its complete native body and current-first caller establish this binding;
there is no duplicate coverage unit. All canonical relocation destinations come
from independently reviewed callees, existing physical heads and verified float
constant objects. Structural diagnostic solved destinations are not used.

## Recovered state protocol

Positive duration advances time, tests the signed endpoint, clamps Timer to the
original duration, then stops. Zero duration returns immediately. Both terminal
paths choose start for shared modes 7 or 17 and otherwise choose end, **even when
axis mode is enabled**. Terminal returns leave the stored current value unchanged.
Negative duration evaluates without advancing time.

Flags bit zero selects shared versus per-axis interpolation, preserving all upper
bits. Shared mode follows the verified Vector3 protocol: mode 7 adds end to start;
mode 17 adds the current end tangent before increasing it by end; mode 8 applies
four Hermite coefficients calculated before vector arithmetic; ordinary modes
calculate the easing factor before subtracting, scaling and adding vectors.

The axis path walks exactly three signed indices. Each coordinate independently
selects these same modes. Accumulation changes only that coordinate, accelerated
accumulation retains the same mutation order, Hermite coefficients precede indexed
value operations, and ordinary interpolation calculates the axis factor before
reading coordinates. Every active path updates current and returns its value.
The original flags/mode names, initial configuration producers and enclosing
Enemy/ECL lifetime remain separate unresolved questions.

## Compiler and acceptance

Existing precise profiles for EnemyMovement, Vector3, Interpolation and Motion
are retained, with no profile-selected body, fake return, assembly, replacement
owner or inert compiler-shaping local. First natural private probes matched all
complete structural extents; subsequent production replay verifies relocations.
These local profiles do not prove the game's global compiler/SDK/CRT recipe.

All 299 units / 60 cold objects strictly replay over 37,560 disjoint complete
comparison bytes. The entire prior graph is rebuilt after the shared headers
change. C++20/UBSan checks cover shared-mode equivalence to the previously verified
protocol, all 32 mixed-axis modes, four clock rates, positive/zero/negative duration,
closed-form quarter-time Hermite coordinates, accelerated accumulation over
multiple half-speed frames, negative unclamped factors, terminal shared-mode
selection, unchanged early-return current, raw indexed subobject references,
full signed duration extremes, guarded and embedded storage, flag preservation,
raw assignment payloads and self-aliasing.

These finite component checks do not establish exceptional floating-control/CRT
behavior, out-of-range index access, full native configuration/ownership, original
resources, linkage or playable runtime. Source rises to 299, with 238 pending
origins and four classified library comparisons. Authored exact credit remains
57 functions / 4,074 bytes. The completed reference review remains 6,945 bodies
and 113 reconciled grammar files.

## Deferred native neighbors

Observed neighboring 0x004AA9B0/0x004AA9E0/0x004AAA10 entries forward through
external VM/controller pointers; 0x004AAAC0 resolves a native handle through a
manager; 0x004AAC00 performs a resource/EH-backed nearest-Enemy search. They do not
belong to the current-first interpolation owner. Array getters 0x0048BCE0 and
0x0048BD10 corroborate twenty-byte animation and 388-byte movement strides but
retain their distinct PMR container ownership. None is promoted through an
incomplete owner facade or receives exact coverage in this batch.
