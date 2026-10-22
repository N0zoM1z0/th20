# Mesh resource access and ANM creation origins

CORE/EXACT-138 reviews the five previously exact but origin-pending
MeshResourceAccess contributions and their common full AnimationFile creation
callee. This is an origin/boundary audit. Production source, the canonical
manifest, profiles, object files and physical exact coverage remain unchanged.

| Address | Reviewed operation | Complete bytes | Result |
| --- | --- | ---: | --- |
| 0042B590 | Animation geometry allocation/publication | 63 | Authored, existing exact |
| 0045D0C0 | Animation variables reference | 19 | Authored, existing exact |
| 00450C70 | AnimationFile null-position spawn wrapper | 57 | Authored, existing exact |
| 004790E0 | AnimationFile position/output wrapper, flags zero | 61 | Authored, existing exact |
| 004ABA30 | AnimationFile position/output wrapper, flags eight | 61 | Authored, existing exact |
| 00450CB0 | Complete AnimationFile spawn protocol | 922 | Authored, source-absent |

## Independent application ownership

The geometry helper stores its signed byte count in Animation+56C, invokes the
actual process allocator and publishes the result at Animation+564. The retained
diagnostic literal identifies `src/core/sprtlib.h:911 void`. Both complete
Graphics strip creators call it with `28 * rows * 2`: calls at 004DE467 and
004DE397 precede the primitive/geometry initialization. The byte count, actual
owner fields, diagnostic source and independent vertex consumers establish a
custom application method rather than a generic SDK allocation function.

The nineteen-byte variables accessor returns Animation+444. The same Graphics
creators call it at 004DE499 and 004DE3B0 and store the strip row count through its
returned reference. This is the actual AnmVariables member within AnimationBase,
not an SDK identity instantiated over unknown storage. The member location and
independent application consumers establish authored composition; byte identity
alone would not establish that origin.

The null-position wrapper preserves the file receiver, requested stem, script,
layer, optional Animation** output and hidden AnimationHandle return storage.
It supplies a null position, floating zero rotation and flags zero to 00450CB0.
Graphics callers at 004DE44D and 004DE37D select their real global surface file
and layers 41/42 respectively. The wrapper is a custom overload of that resource
protocol, not an arbitrary compiler thunk.

Both position wrappers forward the caller's Vector3 address and rotation, with
flags zero or eight as distinct arguments before the optional output pointer.
The original Item effect method calls the flags-zero wrapper at 004C434B and
004C43E9 with Item+BE4 position, script 94 and layer -1. Actual Enemy movement
calls the flags-eight wrapper at 004A7B42 and publishes its returned handle in
its movement animation record. These independent consumers preserve the two
policies; the functions are not interchangeable generic forwarding helpers.
The complete wrappers end in RET 14h/1Ch, including their hidden result pointer.

## Common full producer remains unimplemented

The complete 922-byte body at 00450CB0 acquires process lock nine, increments
File+68, obtains an Animation through the Renderer interface and writes any
nonnull output pointer before checking the requested file stem. Script binding,
layer selection, position/rotation routing and flags operate on actual Animation
storage. It calls the full Animation VM at 0042B5D0, invokes the actual Animation position
interface at 004376E0 and registers the result through one of four Renderer paths
selected by flags.
Its final cleanup releases the guard, restores the exception chain, checks the
security cookie and returns the hidden handle with RET 20h.

Those complete custom resource, VM and registration policies establish authored
origin. They do not establish the unknown Renderer owner, original allocation
failure semantics, complete EH metadata, runtime execution or a maintained body.
The header declaration and exact calling wrappers are not source presence for
00450CB0. Its entire 922-byte native extent remains source-absent, with no
canonical unit or partial exact credit. Original source names and translation-unit
partition remain inferences.

## Evidence and verification

Fresh attested Ghidra exports cover all five wrapper/access bodies. Earlier
attested complete native exports supply the common producer, Graphics creators,
Item effect and Enemy movement; every retained listing instruction is checked
against the currently locked PE bytes. Bounded caller queries corroborate the
position-wrapper use; the known call sites, not automatic function labels,
establish the semantic associations.

All six complete bodies decode without gaps, retain every branch/return and
have no disconnected instructions under the complete control-flow walk. Nine
independent caller sites are verified. The five existing canonical units strictly
replay over all 261 bytes from their current object and immutable receipt. All
326 current product hashes and 278 frozen source hashes remain unchanged.
No MSVC compiler is invoked for this audit.

The unchanged CORE137 semantic evidence covers real geometry allocation and
strip initialization, all three wrapper policies with optional outputs, and
actual heap mesh ownership. Its sanitizer input hashes are rechecked. VM creation
and Renderer behavior remain explicit fixture boundaries; those fixtures are not
proof of full 00450CB0 execution. Current validation results are recorded below
and in [the handoff](RE_HANDOFF.md).

Public CI passes all 81 tests in 360.203 seconds. Final audit confirms exactly six
origin-row changes and five authored exact promotions, while preserving every
previous match record, all source mappings and the complete canonical manifest.
Authored totals become 190 reviewed functions and 180 exact functions / 46,989
bytes. Physical coverage remains 889 units / 167,588 comparison bytes. No
superseded build products are created or retired; no unchanged-source MSVC cold
replay or redundant full-object replay is performed.
