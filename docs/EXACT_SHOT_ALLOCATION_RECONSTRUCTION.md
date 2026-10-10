# EXACT-064: actual shot allocation and shared-control protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

Eight complete contributions add 1,131 instruction bytes and ten compiler
alignment bytes. The frozen-source graph replays 461 units / 87 cold objects /
86,547 disjoint comparison bytes. The whole Enemy dispatcher remains pending.

| Entry | Complete body | Compiler contribution | Maintained role |
| --- | ---: | ---: | --- |
| 004848B0 | 138 | 138 | DebugAllocator control-block allocation |
| 00485240 | 77 | 77 | DebugAllocator control-block release |
| 0048B400 | 248 | 248 | EtamaArgInf copy construction |
| 0047B290 | 223 | 223 | Default std::allocate_shared factory |
| 0047A660 | 173 | 173 | Default std::_Ref_count_obj_alloc3 construction |
| 00484670 | 103 | 108 | Control-block managed-payload destruction |
| 004845F0 | 123 | 128 | Control-block self release |
| 0047C760 | 46 | 46 | Library control-block scalar deleting destructor |

Each entry retains every instruction, exit, branch and complete COFF extent.
The two five-byte INT3 suffixes are emitted by the compiler and compared;
they receive no instruction or authored credit. Explicit anchors come from
independently reviewed native definitions, RTTI structures, vptr producers,
CRT entry behavior and the existing canonical lock protocol. Supporting
contributions receive no duplicate coverage.

## Original type names and storage

Both native control-block constructors store vptr 0056FD20. Its complete
object locator at 005A403C names type descriptor 005B47F0. The original name is
`std::_Ref_count_obj_alloc3<EtamaArgInf, DebugAllocator<EtamaArgInf>>`:
both `EtamaArgInf` and `DebugAllocator` are global structs. The maintained
payload now uses the original global name; `th20::ShotMetadata` is a semantic
alias of that same type. It introduces no extra object, base, vtable or lifetime.

The native block is 88 bytes: the 12-byte reference-count base and the 76-byte
payload. The real payload still owns PMR BulletCommand records and retains its
implicit padding. No payload fields or padding are replaced by opaque arrays.
Original names of the command type and several operands remain unknown.

All generated vtable and RTTI sections, including complete base descriptors,
hierarchies, arrays and type names, independently replay. The COFF weak external
vector-deleting name resolves to the emitted scalar deleting implementation;
the actual native vtable slot selects that complete 46-byte function. This
alias follows compiler symbol records, rather than a fabricated entry point.

The reference queue declaration uses `shared_ptr<void>`. Its erased owner is
a useful ABI lead; folded pointer helpers do not uniquely prove the native
field's static qualification. The canonical semantic owner remains typed.
The runtime control block's payload and allocator names are independently
established by RTTI.

## Allocation, exceptions and destruction

DebugAllocator raw allocation and release both acquire the actual process
registry's recursive mutex at slot 1. Allocation calls scalar operator new
with `count * sizeof(T)`; release calls unsized scalar operator delete and
does not consume the supplied count. The locked CRT scalar allocation entry,
release thunk, array-release forwarding and sized deleting entries are
independent evidence. The allocator neither constructs nor destroys raw values.

The converting allocator constructor is potentially throwing in the native
control-block exception protocol. An earlier private `noexcept` declaration
removed the entire handler from `_Delete_this`, producing 88 versus 123 body
bytes. Removing that unsupported declaration reproduces the complete native
function. Its 39-byte handler at 005691C0 selects the independently decoded
flags-5 FuncInfo at 005A91B8. The allocator's 39-byte handler at 0056808D
selects flags-1 metadata and one unwind state that releases the live lock.
Factory and default control construction retain their real cleanup states.
No exception contract is added to the whole Enemy dispatcher.

Payload `_Destroy` invokes the real metadata destructor. `_Delete_this`
destroys the control block and releases raw storage; its union storage does
not destroy the payload a second time. Metadata copying owns a separate PMR
command vector selected through the default resource. This is distinct from
the allocator-sensitive metadata move assignment established in EXACT-063.

The probe translation unit explicitly instantiates the actual standard
`allocate_shared` specializations. It supplies no alternate STL implementation
or custom control block. Five std-associated contributions have independently
corroborated library origin and are excluded from authored totals. Allocation,
release and metadata copying retain pending origins. Source-present totals
become 388 pending / 9 library / 64 authored, with authored bytes 16,948.

## Tests and remaining whole-function differences

Owned C++20/O2/UBSan tests exercise both allocation and release blocking on
slot 1, recursive acquisition, copied command isolation, allocator selection,
move transfer, erased sharing, and strong/weak payload lifetimes. The actual
production global's definition/startup remains pending; fixtures own their
registry and resources. These tests do not establish whole-game linkage or
runtime behavior.

The copying factory at 0048A8A0 remains 227 versus 236 native body bytes;
copying control construction at 00488FB0 remains 177 versus 192. The candidate
STL marks forward/move as `[[msvc::intrinsic]]`, eliminating native forwarding
calls. The default factory can agree while its in-place and empty-base child
emissions differ. Those callees have independently reviewed ABI/semantics but
receive no exact coverage; complete library linkage is not claimed. See
EXACT_WORKER_RECONSTRUCTION.md for the same previously observed header issue.

Whole queue accessors 00498B80/396 and 00498D10/305 remain nonexact because
factory-result reference materialization also differs. Do not insert inert
temporaries, casts or substitute headers to conceal those differences.
The next core work is the complete 0048C010 dispatcher, all primary/nested
tables and its five real temporary cleanup states. No partial opcode or
shortened function is accepted.

After the stable checkpoint, retire superseded private probes while protecting
all current canonical objects and receipts. Preserve native exports, source
probes and evidence; record retired paths/bytes and strictly replay unchanged
canonical products without another cold build solely for cleanup.

The stable cleanup retires 18 superseded files / 978,879 bytes and preserves all
174 canonical object/receipt hashes. All 461 units strictly replay afterward;
cumulative retirement is 2,021 files / 68,418,873 bytes. All 38 public tests pass.
