# Mesh flag ownership, grid creation and origin review

CORE/EXACT-129 accepts the complete 223-byte Graphics grid-strip creator at
`004DE430`. All seven relocations strictly replay from fresh maintained source.
The function retains its final RET12; the single following native CC byte is
outside its complete COFF contribution and receives no coverage. The paired
198-byte surface creator remains exact.

## Independent two-bit field evidence

Native renderer code at `00445550` reads Animation+4A0, shifts the byte right
four, masks with three, and compares with three. It then passes either zero or
three to `00446690`. This establishes an independently consumed two-bit view;
the renderer state meaning and original source spelling remain unresolved.
The existing grid producer at `004DE484..004DE495` sets exactly these two bits.
No compared relocation field supplies this association.

AnimationModeBits now preserves its existing low-two-bit mode and exposes a
neutral field_4_5 between two other two-bit intervals. Grid creation assigns
three to that field when rows exceeds two. All other flag bits retain their
values, and the smaller-row path leaves this byte unchanged. This is the same
external flag behavior as the earlier byte OR, with a more precise owner view.
No Animation size, field offset, calling convention or source-profile branch
changes.

The pinned compiler emits byte MOV/OR/MOV for the two-bit assignment. The
earlier uint8 expression emitted MOVZX and a promoted 32-bit OR, making the
whole function 224 bytes against native 223. Byte-typed RHS, an explicit 8-bit
literal and /Os probes retain promotion; they do not explain the original.
A two-bit OR assignment also differs. The natural field assignment matches the
entire function without padding, an inert local or a false volatile contract.

All other behavior is preserved: use the process Graphics surface file even
with another receiver, spawn on layer 41, allocate 28*rows*2 bytes, publish rows
through the real AnmVariables integer, and initialize only Z/RHW/color for
larger strips. The process Graphics base remains `005C4D40`; its actual surface
file reference preserves the COFF +B40 addend. Complete prior spawn, resolve,
allocation, variables, vertex access and float-one identities supply the seven
canonical anchors independently of this root's fields.

## Separate application-origin decisions

Eight previously strict-exact roots now have independently reviewed authored
origins. These 935 bytes were already physical comparison coverage; the origin
review does not add them to the physical total again.

| Native entry | Application operation | Body bytes |
| --- | --- | ---: |
| `0049E050` | Mesh view/Session Context selection | 45 |
| `0049D850` | Window-offset grid initialization | 503 |
| `0049DDC0` | Adjacent-column Animation strip publication | 194 |
| `0049DF40` | Scaled Window UV conversion and lower clamp | 107 |
| `0049DF00` | Window per-view X offset | 23 |
| `0049DF20` | Window per-view Y offset | 23 |
| `0049DFD0` | Window scaled width | 20 |
| `0049DFB0` | Window scaled height | 20 |

The actual constructor, Enemy deformation and screen-surface consumers bind
the nine-word mesh to Session Context, the game Window and Animation geometry.
Full grid/publication/UV bodies retain those custom owner/global interactions.
Window accessors receive the independently established process WindowState
receiver and access its +38/+40 view arrays or +20A0/+20A4 scaled dimensions.
These concrete game storage and consumer protocols establish application-owned
logic separately from byte identity or Ghidra labels. They are not installed SDK
iterator/copy implementations. Original class and method names remain inferred.

Five other CORE095 exact support origins remain pending: EnemyMeshOwner
construction, Angle subtraction, XY norm, Animation geometry access and Enemy
position access. Whole Enemy deformation also remains nonexact and unclassified;
its unused radius conversion is not introduced as an emission-only local.

## Affected-header builds and immutable receipts

Before changing the header, all 162 current object/receipt pairs are verified.
Actual compiler /showIncludes records identify 24 Animation.hpp consumers and
138 other objects. The original 24 input closures, complete native literal
payloads and all current product hashes are archived before editing.

Receipt verification now permits edits to existing C/C++ headers absent from
the recorded compiler include closure, as it already did for unrelated source
implementations. The source, every included file, compiler, profile, target and
object still require their original hashes. Added/removed paths and non-C/C++
control inputs still invalidate receipts. No old receipt is rewritten.

Synthetic controls check included source/header changes, unrelated source/header
changes, path addition/removal, non-C/C++ inputs and missing include metadata.
The actual graph independently rejects all 24 affected old objects and accepts
the 138 unaffected old receipts. Each affected production object builds once;
all 140 prior affected strict units pass. Ten generated literal labels change
names, with complete original payloads and fresh COFF reference roles preserving
their independent native identities. No target instruction field is solved.

The graph now has 847 disjoint physical units and 163,938 compared bytes.
Authored exact coverage is separately 108 functions / 33,389 bytes, with 110
confirmed authored origins. This reviewed subset does not measure the whole-game
95% byte-exact objective.

The existing actual-owner O2/ASan/UBSan mesh fixture covers all 256 initial flag
bytes, five row counts, both factories and 3,433 lifetime/resource cases. Other
geometry fixtures cover per-view grids, complete strip copies, clipping and UV
domains. Native rendering, malformed allocation/dimensions, remaining renderer
fields, startup and a playable whole program remain open.

All 80 public tests pass in 273.867 seconds. Protected retirement removes 170
replaced object/receipt products and private source/header copies, totaling
1,988,745 bytes, after preserving original SHA-bound inputs and immutable
receipts. All 324 current canonical object/receipt hashes remain unchanged.
Post-cleanup strict replay passes all 847 complete units using existing objects,
with zero compiler invocations.

Private evidence is retained in core129-original-inputs.json.gz,
core129-header-invalidation.json, core129-cold-proof.json,
core129-affected-results.json.gz, core129-grid-exact-result.json,
core129-boundaries.json and attested native exports under `.analysis/`.
