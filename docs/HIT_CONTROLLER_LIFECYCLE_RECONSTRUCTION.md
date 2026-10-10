# Hit controller lifecycle reconstruction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-099 now closes full ordinary destruction, find and update. The
current graph has 689 strict units/135 objects/134,296 disjoint bytes; whole
query and creator/factory questions remain open. See [current core evidence](CORE_ITERATION_EXACT_RECONSTRUCTION.md).

CORE/EXACT-098 closes actual HitCtrlInf initialization, region creation and
pool/heap retirement on the shared scheduler, allocator and Context owners.
The full damage query at 0x004C0480 remains open; see
[query evidence](DAMAGE_CONTROLLER_RECONSTRUCTION.md).

## Storage and ownership

RTTI and constructor/consumer evidence establish the 0xC460 owner: TaskInfo
at +0, 256 actual 0xC4-byte DamageRegion values at +0x10, next identifier at
+0xC410, active/free observer lists at +0xC414/+0xC42C, visit count at +0xC444,
Timer at +0xC448, view index at +0xC458 and Context pointer at +0xC45C.
The maintained std::array declaration naturally reproduces complete native
pool construction. Original template/source spelling remains inferred.

Context +0x28 is now a typed HitCtrlInf pointer. Initialization publishes the
owner and registers its real disabled priority-28 update callback. It resets
both lists, initializes every region's link and appends all 256 to the free
list. It does not invent region-ID resets or repeated-initialization cleanup.
Actual TaskInfo enable/disable methods control the registered callback.

Pooled allocation detaches the first free link, appends it to the active list,
assigns the next identifier and advances its low sixteen bits. Zero wraps to
one; advancing drops the view prefix, matching the original. Heap fallback
uses the shared generic allocator, initializes and publishes the region link,
sets bit 24 and initially selects Context zero. Rectangle/circle creation then
selects the owning view and calls the shared native configuration methods.
Their Identifier32 results use the real aggregate-return ABI, including the
hidden result pointer; no replacement explicit-output signature is used.

Retirement first rejects a zero identifier, saves its heap bit, obtains the
actual owner through the region Context and detaches the region. Pooled nodes
return to the free list. It then clears active bit zero and the identifier;
heap objects run the actual allocator release protocol after these stores.
No field is read after heap release. The ordinary owner destructor removes
its scheduler node and retires the remaining active regions before automatic
TaskInfo destruction. Original Context publication remains dangling after
destruction; source does not fabricate an unpublication operation.

## Complete compiler contributions

The pinned x86 candidate compiler uses /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc /Gd. Independent native functions, existing
canonical anchors, RTTI and complete NUL-terminated literal identity resolve
all 72 relocations in sixteen new physical contributions:

| Operation | Address | Body bytes | Compared bytes |
| --- | --- | ---: | ---: |
| Region array construction | 0x004BFE80 | 81 | 86 |
| HitCtrlInf construction | 0x004BFEE0 | 191 | 196 |
| Context selection | 0x004C2090 | 54 | 54 |
| Identifier advance | 0x004C0C60 | 67 | 67 |
| Detach/free-list return | 0x004C1EB0 | 70 | 70 |
| Initialization | 0x004C0B30 | 265 | 265 |
| Allocation | 0x004C0E60 | 225 | 225 |
| Update callback | 0x004C0CB0 | 13 | 13 |
| Rectangle creation | 0x004C1AE0 | 151 | 151 |
| Circle creation | 0x004C1B80 | 140 | 140 |
| Global owner getter | 0x00478EC0 | 26 | 26 |
| Free-list front | 0x004859F0 | 19 | 19 |
| Region array end | 0x004C0C40 | 19 | 19 |
| Region retirement | 0x004C1F30 | 138 | 138 |
| Generic owner allocation | 0x004BFDE0 | 73 | 73 |
| Compiler automatic class initialization | 0x0040C080 | 31 | 31 |

All 1,573 bytes include both five-byte constructor alignment tails. Independent
decoding closes every direct branch and reconciles all full exits. Region
context selection at 0x00488A20 also reproduces its full 54 bytes but aliases
existing card_bind_context; it adds no physical credit. Context getter/setter
and the Identifier32 input constructor likewise share existing physical units.
Fresh production deleting destruction (49 bytes), both complete constructor
handlers (29 bytes each) and both zero-state flags-5 FuncInfo records (36 bytes
each) also strictly replay as ABI support. They do not establish exactness of
the ordinary destructor or add duplicate physical coverage.

## Whole nonexact source and remaining evidence

| Operation | Complete compiler bytes | Native body bytes |
| --- | ---: | ---: |
| Ordinary destructor | 224, including five alignment bytes | 230 |
| Find | 254 | 264 |
| Update | 238 | 248 |
| Global creation | 82 | 92 |
| Generic region allocation | 60 | 73 |
| Generic chain-node allocation | 57 | 67 |

Find and update now destroy their iterator in a normal inner block, matching
native teardown before the final miss return and before visit-count/Timer
writes. Both retain a ten-byte auto-class-clear emission difference. Native
destruction also has this clear and an additional post-removal NOP. Its body
ends at 0x004C0205; ten following INT3 bytes precede the independently established
Identifier32 equality head at 0x004C0210. The source destructor body is 219
bytes plus five compiler alignment bytes. Body and contribution lengths are
distinct facts; no shortened prefix or artificial padding is accepted.

Global creation retains a native otherwise-unused pointer reset and branch
partition difference. Allocation factories keep one shared natural new-T
template; their pre-clear/temporary partitioning remains unresolved. No fake
iterator default constructor, raw clear, inert reset or owner-specific allocator
specialization is added to force emission. The unchanged shared new-T template
naturally emits the exact HitCtrlInf factory and its complete compiler-generated
__autoclassinit2 helper. Independent region-factory consumers identify that
helper as the thiscall memset wrapper at 0x0040C080. Microsoft's
[/sdl documentation](https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks?view=msvc-170)
describes automatic member-pointer initialization under specified constructor
and allocation conditions. That corroborates the observed mechanism; it does
not explain every remaining type's emission or justify adding source clears.

## Owned semantic checks and limits

tests/hit_controller_semantics.cpp links the actual maintained owners and
bodies. Process placement and diagnostic memory-resource startup are fixtures.
O2/UBSan and O2/ASan/UBSan checks cover both views, actual Context publication,
disabled callback registration and enable/disable, both shapes, zero/missing
lookup, first-view prefix and subsequent generation behavior, 65535-to-one wrap,
pool reuse, duplicate retirement, region/owner clocks and observer repair.
They update and retire 261 simultaneous regions, then destruct an owner with
259 active regions, exercising actual pool and heap release and scheduler
removal. Heap Context-zero selection and subsequent owning-view selection are
checked separately. These checks do not establish game startup, real Windows
runtime, exception/failure domains or the complete active damage query.

Production presence, semantic checks and byte matching are separate evidence.
Native origins stay pending; this batch adds no authored or reference-absorption
credit. Private proof inputs are core098-production-bindings.json,
core098-native-roots-audit.json, core098-owned-lifecycle-check.log and the
attested core098 native exports. The additional factory/helper proof is
core098-factory-bindings.json. Frozen 240-file source passes all 682 canonical
units across 135 fresh objects and 131,527 disjoint comparison bytes. All 64
public tests pass; protected cleanup
repeats the same 682 strict results without rebuilding. See the current handoff
for retained proof paths and retirement counts.
