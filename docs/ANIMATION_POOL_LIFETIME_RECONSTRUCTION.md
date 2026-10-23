# Animation pool lifetime

## CORE/EXACT-143 acceptance

The maintained AnimationPool owns 65,536 real PooledAnimation records. Native
Renderer construction passes its `+710` subobject to `00447C60`; destruction
passes the same subobject to `004491E0`. The child constructors/destructors and
the vector iterators establish a 1,536-byte stride and a complete `0x06000000`-byte
storage extent, ending at Renderer `+6000710`. This closes the fixed-array
lifetime component; Renderer `+6000DFC..+6000DFF` remains unresolved.

| Complete contribution | Entry | Body bytes | Compared bytes |
| --- | --- | ---: | ---: |
| PooledAnimation construction | `004489F0` | 59 | 59 |
| PooledAnimation destruction | `004492F0` | 20 | 20 |
| AnimationPool construction | `00447C60` | 86 | 91 |
| AnimationPool destruction | `004491E0` | 78 | 83 |

All four units are owned by Animation.cpp under its unchanged C++20, precise-FP,
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /sdl /EHsc` profile. Pool construction is ordinary
member-array initialization; destruction is defaulted. The complete compiler
contributions retain five trailing INT3 bytes for each pool wrapper. No smaller
prefix is accepted. These units add 253 disjoint comparison bytes.

## Storage and exception evidence

PooledAnimation retains its existing Animation, five-pointer free link, byte
activity word and uint32 index. Its native size is `0x600`, with the existing
implicit alignment gap before the index. AnimationPool contains only the real
record array and has no additional instance bookkeeping or invented storage.
Native layout assertions are restricted to x86.

The shared child declarations and the PooledAnimation constructor body are
unchanged. The current production object already emits the native 59 bytes;
the historical 115-byte trial predates the current shared pointer-node contract.
No new noexcept annotation is applied to PooledAnimation to adjust code size.

The new pool wrapper's nonthrowing contract is independently corroborated by
its complete native EH handler and FuncInfo. The 29-byte code and 36-byte data
fold to the previously established `00567600` / `005A91B8` identities, including
the accepted flags5 contract. Constructor/destructor aliases replay 130 bytes
over 65 unique support bytes; no additional physical credit is assigned.

## Independent anchors and complete boundaries

The complete 59-byte slot constructor is uniquely identified across the locked
text section using the existing Animation and intrusive-link constructors.
The 20-byte slot destructor is independently unique using the existing Animation
destructor. This identification does not use callback fields in either pool
wrapper. The wrapper entries come from the external Renderer lifetime calls.

The EH vector constructor/destructor addresses `00542EAF` / `00542F23` are
already established by the Bullet, Item and Animation-template array protocols.
Cookie, frame-handler and shared EH identities also predate this comparison.
Every relocation is resolved through these independent owners or complete
callee identities. Attested listing bytes and complete PE decoding reconcile
all four bodies, returns and comparison tails.

Original source/receipts and 328 product hashes were preserved before editing.
Captured include closures select 24 providers / 167 prior units; all are freshly
built once and strictly replay, with 140 objects reused. The source path set
remains 279 entries. Previous profiles, extents, addresses and addends are
preserved; literal labels retain their original content and destination.

## Actual owner checks and current credit

The O2/UBSan fixture constructs all 65,536 records on dirty heap storage, checks
every free link and all five Animation self links, and samples untouched padding.
Five records at the beginning, middle and end own real geometry and callback
objects. Complete pool destruction retires them in reverse order, releases
geometry before each callback and performs callback destruction outside the
allocator lock. The fixture uses the maintained geometry allocator and release
protocol. Its compile/run peak RSS is 190,960 KiB, with heavy work kept serial.
Native Renderer integration, loaded-file behavior and allocation failure remain
separate boundaries.

The graph contains 896 physical units / 164 objects / 168,057 disjoint comparison
bytes and 904 source mappings. Original authored/compiler/library provenance
and C++ spelling for the four new roles remain pending. Authored exact coverage
therefore remains 181 functions / 47,071 bytes; these counts do not measure the
whole-game 95% objective.

Private evidence includes `core143-independent-slot-identities.json`,
`core143-private-proof.json`, the attested `core143-pool-lifetime.asm` and
`core143-slot-destructor.asm`, `core143-new-exact-results.json`,
`core143-support.json`, `core143-boundaries.json` and `core143-graph-audit.json`.
All are under `.analysis/`; original input archives, failed logs and probe
sources are retained when regenerable objects are retired. Final CI and cleanup
replay are recorded in the current handoff.

## CORE144 continuation: enclosing owner alignment

A separate synthetic MSVC 19.44.35211 x86 probe tests eight layouts with explicit
8/16-byte type/member alignment, default packing and pack(1/4). In each tested
combination, explicit alignment propagates to the containing type even under
reduced packing. The resulting owner alignment is 8 or 16, so these combinations
do not explain the Renderer allocation size 0x7D40E94, which is 4 modulo 8.
Natural uint64 alignment and other packing combinations were not tested. This
compiler observation neither identifies the +6000DFC interval nor proves padding;
the genuine Renderer owner remains unresolved.

Private source/results are `.analysis/core144-alignment.cpp` and
`.analysis/core144-alignment-results.json`; the authentic object and receipt are
`build/core144-probes/Alignment.obj` and its sibling `.receipt.json`. Preserve
these current investigation inputs without awarding canonical credit or repeating
the unchanged trial.
