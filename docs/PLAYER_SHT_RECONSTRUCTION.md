# Player construction and SHT consumer reconstruction

CORE/EXACT-102 maintains complete actual Player construction, serialized SHT
loading/relocation and damage-limit selection, with actual Overlay value
construction and typed Context selection. Twelve whole contributions add
1,810 disjoint compared bytes and 70 independent relocations. The frozen
250-file graph passes 718 strict units across 141 objects and 137,378 disjoint bytes.
Source mappings are 732; fourteen whole nonexact methods remain. Authored,
reference and origin credit remain separate and unchanged.

## Whole contributions and ownership

| Native entry | Maintained contribution | Body / comparison bytes |
| --- | --- | --- |
| `4F46A0` | Player construction | 794 / 799 |
| `4F4110` | Ten PlayerOption values | 78 / 83 |
| `4F4170` | Twelve PlayerOption values | 78 / 83 |
| `4F40C0` | Thirty-three IntPoint values | 75 / 80 |
| `4F9B80` | Load SHT and relocate its offset table | 164 / 164 |
| `4FF4E0` | Complete damage limit selection | 241 / 241 |
| `4FF5E0` | Focus predicate | 47 / 47 |
| `532880` | WeaponStoneInfo construction | 208 / 208 |
| `4FF840` | Overlay phase-one predicate | 42 / 42 |
| `533700` | Overlay callback disabling | 20 / 20 |
| `464230` | Current Overlay selection | 26 / 26 |
| `464250` | Typed Context Overlay getter | 17 / 17 |

Player.hpp/Player.cpp own complete storage and its real arrays. ShotData.hpp
and ShotData.cpp own the serialized schema, loading and scalar relocation
helpers. PlayerDamageCap.cpp owns focus/cap selection and the current Overlay
lookup. WeaponStoneInfo.hpp/WeaponStoneInfo.cpp own actual Overlay storage,
construction, phase and callback disabling. Shared Context and PlayerRecord
methods retain their existing translation units.

All constructor alignment bytes are included. Four complete 29-byte EH handlers,
four 36-byte FuncInfo records and the complete 56-byte array helper replay as
support. SHT's 8-byte signed conversion and 11-byte address addition, both
17-byte Record getter aliases and both complete 49-byte deleting destructors
also replay as support. Getter aliases add no duplicate physical credit.

The SHT loader's extent is **164 bytes**, including `ret 8` at `4F9C21` through
`4F9C23`. Earlier private probe labels saying 162 were wrong; no comparison
truncates the function to that size. Every branch and exit is included.

## Storage and shared construction contracts

The complete x86 Player has native extent `0x1485C`, real Animation, ten and
twelve Option arrays, 33 IntPoint values, Feedback and a controller containing
256 actual Shot values. Construction leaves `+14850` untouched. Direction at
`+18` has a native floating-angle consumer: frame code at `4F7FDF` calls
`4FF710`, which reads the float and invokes the shared polar calculation.
The value at `+1484C` shares a floating-zero producer; its gameplay role remains
unknown. A linear instruction scan found no explicit `+14850` displacement;
this does not exclude computed accesses or establish an original declaration.

The actual `0x84` Overlay owns three Timers, an AnimationHandle, a real
8-byte counter, four Weapon pointers, a RenderMesh pointer, Vector3, phase,
radius, byte state, view index and Context pointer. Its phase-one consumer and
constructor establish the shared layout. Natural alignment supplies byte gaps;
no padding fields, service suffixes or raw clears are introduced.

CORE-101's ordinary 264-byte and nonthrowing 255-byte Overlay constructor
candidates did not match the native 208-byte body. Four actual shared default
constructors—Timer, AnimationHandle, Vector3 and OverlayCounter—have independently
exact store-only bodies. Their source default construction is now nonthrowing.
The enclosing Overlay constructor remains potentially throwing and non-final,
with the actual nontrivial TaskInfo destructor and the original `/EHsc` profile.
This explains the complete 208-byte emission without a constructor EH frame.

An independent private graph cold-builds all 70 affected objects: all 706
previous canonical units stay exact, and 70 complete associated compiler EH
contributions stay unchanged. Defaulting TaskInfo's destructor was rejected:
it produces an 11-byte body instead of the native 20-byte vtable-reset protocol,
and leaves a 264-byte Overlay constructor. The production base destructor stays
unchanged. Original exception-contract syntax and class finalness remain unknown;
source spelling is inferred from the observed bodies and consumers.

Both complete three-slot virtual tables corroborate the owners. MSVC emits an
`_E` deleting-slot reference with search-kind-one weak `_G` fallback. The full
49-byte scalar `_G` bodies and native slot destinations replay. Strong vector
`_E` definitions and full-link resolution remain separate gates. Preceding RTTI
COL and type-name payloads are outside this acceptance; original type/template
and RTTI spelling remain unknown.

## Actual serialized SHT protocol

Both original `pl00.sht` and `pl01.sht` were extracted through maintained
ArchiveOwner, PbgFile, resource I/O, allocator, cipher and LZSS bodies with
read-only host file bindings. The source archive, resource hashes and consumed
native cipher fields are pinned privately. Sizes are 57,012 and 51,252 bytes;
both files contain 160 offset entries. No original resource bytes are public.

The serialized prefix is `0x5D4` bytes. Entry count is a 16-bit value at `+2`;
121 rows of three signed damage caps start at `+28`. Nine intervening words
are actual serialized header fields whose individual roles remain open.
The variable tail contains `entry_count` four-byte offset words. The shared
flexible-array declaration uses the MSVC/GCC extension and the allocation extent
supplied by resource I/O; it adds no one-element surrogate or padding.

Loading writes the output pointer, returns -1 when resource loading fails,
and otherwise converts each nonnegative signed offset into a 32-bit address
word by adding the loaded base. Negative sentinel words remain untouched.
Portable checks validate these words without dereferencing truncated addresses
on a 64-bit host.

The complete damage limit always queries global Context zero, including for a
Player bound to Context one. Phase one selects Record zero's `field_10` row and
column two; otherwise focus selects that row and column one; normal mode selects
its `field_14` row and column zero. Actual typed 240-byte records and shared
getters replace the reference's raw offset assumptions. The Context getter uses
the observed base-at-zero Overlay ownership invariant; native selection adds
no null or bounds checks.

The complete native 237-byte Overlay initializer at `532FB0` selects its view
through `5345D0`, reads its Context pointer at `+80` and publishes its own
`this` through `5347B0`. The complete setter stores that pointer at Context
`+2C`. This independently corroborates the typed getter's ownership precondition.
The initializer's ANM loading, Weapon selection and enabled update/draw
registration at priorities 27/55 remain native evidence; no initializer body
or additional exact contribution is claimed.

## Semantic checks and open lifetime boundaries

O2/ASan/UBSan checks execute actual maintained Player/Overlay construction in
dirty storage, actual archive/SHT relocation and the complete cap consumer.
Public fixtures construct synthetic resources with the real 121-by-three
schema and 160-entry table; private checks use both original assets. Together
768 cap selections cover both tables, multiple independent rows, phases and
focus byte values. Signed sentinels, zero-count and missing-resource exits pass.
Actual shared Context/Record getters and Overlay callback disabling execute.
Temporary host binaries are removed automatically.

All 66 public tests pass. Six older narrow Context fixtures use function/data
sections and linker reclamation for the uncalled typed getter, preserving UBSan
checks on exercised bodies. Protected interim/final retirement removes 479
obsolete products and saves 13,104,441 net bytes after lossless archives.
All 718 existing-object results remain identical to the frozen proof; all 282
canonical object/receipt hashes and 250 source hashes remain unchanged.

The public test uses actual archive, cipher, LZSS and resource bodies with
explicit OS/process bindings. Original Player and Overlay destruction/activation
fixture definitions abort if called. This scope manually closes accepted
Animation and TaskInfo child lifetimes before releasing enclosing storage.
Overlay publication, ANM callback retirement and identity-matrix placement remain
explicit startup bindings. The checks establish neither native game startup
nor original character gameplay.

The whole 449-byte Player ordinary destructor depends on original ANM ownership
and resource retirement. Its actual owner declaration/lifetime remains open.
Overlay destruction/activation, Player frame/activation and the whole
1,707-byte damage query remain open. These interfaces have no fabricated
production bodies, empty receiver classes or ABI casts. Function-level canonical
acceptance of the maintained constructor/resource consumer scope is separate
from those remaining protocols and whole-game compile/link/runtime.

Evidence: core102-production-bindings.json, core102-native-roots-audit.json,
core102-contract-proof.json, core102-semantics.json, core102-publication-evidence.json,
core102-final-frozen-source.json, exact102-canonical-results.json.gz and
core102-registered.json. CORE-101's asset hashes and attested exports remain
native evidence. Historical SHA-bound inputs/receipts are losslessly archived
before superseded trial products are retired; completed writers never rerun.
