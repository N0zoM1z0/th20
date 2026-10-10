# Animation geometry and parent position

CORE/EXACT-121 reconstructs the complete 5,388-byte geometry update and ten
position/value functions in the established Animation and WindowState owners.
All source is maintained C++ with a shared semantic body, real vertex records
and natural arithmetic/control flow. Original source names remain inferred.

## Complete contributions and tables

| Native head | Code bytes | Maintained operation |
| --- | ---: | --- |
| `0x00435C80` | 5,388 | `Animation::update_geometry` |
| `0x004376E0` | 103 | `Animation::position(Vector3&)` |
| `0x004379E0` | 660 | `Animation::transform_position(Vector3&)` |
| `0x00437930` | 17 | Direct rotation Z value |
| `0x004379C0` | 17 | Direct scale X value |
| `0x004379A0` | 17 | Direct scale Y value |
| `0x00438290` | 20 | Window scale value |
| `0x00437660` | 17 | Window offset +0058 value |
| `0x00437680` | 17 | Window offset +0060 value |
| `0x004376A0` | 17 | Window offset +005C value |
| `0x004376C0` | 17 | Window offset +0064 value |

Geometry also owns the six-pointer table at 43718C (24 bytes) and the compressed
selector table at 4371A4 (40 bytes). Its match unit keeps code size 5,388 and
comparison size 5,452; no code, table or selector is shortened. The complete
batch verifies 6,354 bytes across eleven implementations, adding 6,337
disjoint comparison bytes through ten new physical units and 134 independently resolved
relocations. A target-attested Ghidra export lists all 1,239 code instructions;
the dispatcher audit reports no omitted instruction heads or outside branches.

| Selector | Native case head | Geometry contract |
| --- | --- | --- |
| 9 | `0x00435CD9` | Closed screen ring, 28-byte records |
| 13 / 14 | `0x00436A49` | Open screen arc, 28-byte records |
| 24 / 25 | `0x00436E32` | Open world strips in XZ, 24-byte records |
| 47 | `0x0043617D` | Closed world ring, 24-byte records |
| 48 | `0x00436625` | World triangle relative to its first vertex |
| Other byte selectors | `0x00435CD4` | Preserve all state and buffer contents |

All 40 in-range selectors, including default paths, reconcile with the original
native audit. COFF local-label addresses derive from their whole function section
placements. Complete existing canonical dependencies and independent native heads
supply call/global anchors. Literal pool payloads are checked independently at
previously established addresses. No relocation target is solved from a field
under comparison. Ten complete canonical dependency bodies replay separately. The Window+0058
getter shares its physical17-byte head with the existing EclManager::loader_value
getter. Actual Window receiver/offset consumers establish the additional typed
role; its fresh whole WindowAnimation contribution is verified separately, with
no second match unit, function mapping, physical byte or authored-origin credit.

## Canonical owners and output ABI

Animation retains its actual 4C0 base and 5E4 x86 owner; WindowState retains its
2138 x86 owner and real scale/offset fields. The new SpriteWorldTexturedVertex
contains Vector3, packed color and two float UVs: 24 bytes with color at +12,
u at +16 and v at +20. Geometry producers write these fields with stride 24.
The independent draw consumer selects FVF 142 at 443797 and DrawPrimitiveUP
stride 18 hex at 443848. The existing 28-byte SpriteTexturedVertex has reciprocal
W at +12 and color/UVs at +16/+20/+24; the other draw consumer selects FVF 144
at 4454DB and stride 1C hex at 445596. These establish two actual records,
without adding padding or inventing a partial Renderer owner.

Both position functions mutate an explicit Vector3 reference and return that
same reference. Whole 38-byte consumer 44CC70 forwards an existing output
pointer and returns EAX directly. Whole 146-byte consumer 467820 constructs its
Vector3 local, passes that exact storage to position and uses the same local for
a later spawn call. Together with both full callees and fresh compiler emission,
these support the explicit output/reference hypothesis. The initial by-value
hypothesis is rejected: it emitted 85/678 bytes instead of native 103/660 and
introduced the wrong caller protocol. Its original compiler inputs and failure
results remain archived. Original C++ spellings are not independently known.

Position adds (offset + base position) + base auxiliary position before applying
its frame. Screen modes 1/3 multiply XYZ by window scale; 2/4 use half scale.
A +558 parent is used while bit12 is clear. Bit5 rotates XY by that parent's
rotation Z; bit22 then multiplies XY by its direct scale, retaining Z. The
parent's own recursive position is added. Without that parent path, layer 1
adds offsets +0058/+005C; layers 2/3 use +0060/+0064. Direct scale getters are
separate from the previously accepted recursive inherited-scale methods.

## Vertex behavior

Closed rings write two records per sample, copy both initial records to the
closing pair, and replace only their V with the accumulated UV. Screen rings
and arcs use computed position; world rings use zero center. Screen/world ring
radius sources differ: actual base scale versus actual variable floats. A +55C
parent scales the two radii independently by its direct X/Y values while bit12
is clear. This pointer is distinct from the +558 position parent. Radius scaling
uses only screen modes 1/2. Mode 2 retains native multiplication order.

Open arcs write count pairs without closure. Selector 13 centers the sweep at
rotation Z; selector 14 starts at normalized rotation Z. Both use the selected
secondary-or-primary color for both sides. Closed rings retain primary color
for side zero and the selected color for side one. Screen records write RHW=1.
UV offset and signed integer repetition preserve native float conversion.

World selector 24 maps polar XY to XZ with positive/negative half-height in Y.
Selector 25 instead offsets the two radii by half-width and uses signed zero
height. Neither performs a position, parent-radius or window transform. The
triangle uses its native three angle order, subtracts its original first
position from the other two, then makes vertex zero exactly zero. It retains
the native midpoint U expression and three distinct UV slots.

The strict candidate MSVC profile emits all eleven complete roots. Two semantic
zero-vector assignments use brace assignment to constructed temporary storage;
the triangle's assignment uses its constructor-returned object. Both forms
express real assignments and retain native temporary/copy behavior. Namespace
pi is used in actual math; no inert local PI store, arbitrary padding, fake ABI,
assembly or profile-selected body is added. Per-TU success does not prove the
original game-wide compiler flags, SDK or runtime.

## Semantic and exact gates

The actual production owners pass 87,808 O2/ASan/UBSan cases against independent
component/frame and shape-specification oracles: all seven recognized selectors,
all 249 default byte selectors, counts 2/3/7/16, six screen modes, four layers,
eight flag combinations, three parent-pointer configurations and two color
choices. Parent chains have depths zero through three. Output tests cover a
separate Vector3 and five live Vector3 subobjects, verifying returned reference
identity and full owner images. Vertices have typed live storage and guard
records; tests check XYZ/RHW/color/UV and every untouched record, plus complete
owner, parent and WindowState state. Value helpers additionally check signed
zero, infinities and portable NaN classification.

The accepted geometry domain has adequate, nonoverlapping, live typed record
storage and positive counts at least two, with finite tested shape inputs.
Fixtures borrow their vertex arrays and detach before ordinary owned cleanup.
They do not establish the native allocation-to-object-lifetime transition,
malformed counts/cycles, arbitrary aliasing into vertex storage or gameplay
rendering. Those questions remain open rather than being hidden by byte identity.
Position chains are finite and acyclic. Portable float behavior and original
x86 byte emission are separate oracles.

The frozen 273-source production graph passes 810 complete strict units from
158 fresh objects and 158,071 disjoint comparison bytes. All production receipts,
complete canonical/support replay and 77 public tests pass. Every one of 158
objects compiles once; 45 independent literal roles reconcile 30 label changes.
Protected cleanup retires 329 files / 9,103,020 bytes (8.68 MiB), preserving all
810 replay results, 273 source hashes, 316 current product hashes, 42 native
evidence hashes and five SHA-bound original compiler-input archives. Authored-origin credit
remains 94 functions / 30,383 bytes, with 98 confirmed authored functions; no
origin conclusion is inferred solely from this batch's exact emission.
The 39,470-byte VM, 922-byte File VM creation, reset zero-lifetime questions,
unknown Renderer +6000DFC ownership and Item update/draw remain open.
