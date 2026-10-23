# Exact asynchronous ECL node allocation

## CORE/EXACT-142 acceptance

The complete factory at `0053B410..0053B452` is now canonical as
`ecl_runtime_link_allocate`: 67 bytes and three independently resolved
relocations. EclRuntimeLifetime.cpp instantiates the existing shared scalar
allocation body for `IntrusiveLink<EclRuntime>`, alongside the Runtime factory.
Its provider retains its C++20, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` profile. No allocation-body specialization or handwritten clear was
introduced.

IntrusiveLink is now declared as a class with all five fields and methods public.
Its field order, 20-byte x86 size, constructor body and existing noexcept
contract are preserved. The two explicit class instantiations use the matching
class key. Original C++ spelling remains inferred: the compiler result supports
this maintained declaration, while native RTTI does not independently establish
the original class key.

## Native boundary and independent identities

The attested listing and complete PE decoding agree on all 22 instructions.
Both conditional routes join inside the 67-byte body, which ends in `ret 4`.
There is no external tail, table or disconnected body fragment. The existing
canonical EclManager::spawn caller already identifies this typed factory.

| Factory relocation offset | Independent identity | Address |
| --- | --- | --- |
| 12 | Existing scalar operator new | `0054275D` |
| 34 | Complete compiler initialization helper | `0040C080` |
| 42 | Complete five-pointer default constructor | `00418A10` |

The emitted 31-byte initializer strictly replays against the existing
`hit_controller_auto_class_initialize` unit, including its independently
anchored memset call. The emitted 63-byte constructor independently replays
against `link_default_ctor`. Both are complete folded identities and receive no
additional physical credit. These anchors come from the existing units and
complete callee comparisons, not from solving a factory field.

The current struct baseline emits 57 bytes; the public class declaration emits
the native 67 bytes, including the compiler-generated clear before construction.
Both retain the same 63-byte constructor. The historical 73-byte trial recorded
in the earlier async checkpoint is not the native extent or the current baseline.
The accepted change preserves the genuine nonthrowing pointer-initialization
contract rather than changing it to adjust emission.

## Shared declaration and comparison closure

Original source versions, receipts and all 328 product hashes were preserved
before editing in `.analysis/core142-pre-header-inputs.json.gz`. Captured include
closures select 70 affected providers / 425 prior units; 94 other objects are
reused. All affected providers were built once and all 425 units strictly replay.
The snapshot path set remains 279 entries. Every prior profile, extent, target,
relocation role and addend is preserved.

Thirty-three decorated identities change with the class tag, including compressed
self-type references in member signatures. Local literal labels are reconciled
by relocation offset and original content/address, so renaming one cannot
overwrite another role. All 30 literal roles retain their original targets.
The final manifest preserves its existing numeric formatting.

The graph now has 892 physical units / 164 objects / 167,804 disjoint comparison
bytes and 900 source mappings. Factory provenance remains pending, matching the
separate Runtime allocation origin policy. Authored coverage remains 181 exact
functions / 47,071 bytes. Compiler correspondence, source presence and physical
exactness do not establish authored provenance or whole-game linkage.

## Actual owner checks and durable evidence

The VM/Manager/Enemy fixture now links the production node factory. Its former
factory specialization and synthetic allocation-event markers are removed.
Real node initialization/release, head insertion, sentinel lookup, rank/frame
propagation, delayed child execution, failed lookup retention and ordered Runtime
retirement continue to execute through the shared owners. PMR/startup fixtures,
unused routes and outer Enemy movement/destruction remain explicit boundaries.
Positive allocation checks do not establish the native out-of-memory domain.

The focused O2/UBSan fixture passes after the substitution. The complete CI result
and final cleanup replay are recorded in the current handoff. Private evidence is
`.analysis/core142-ecl-node-factory.asm`, `core142-boundaries.json`,
`core142-probe-results.json`, `core142-new-exact-results.json`,
`core142-support.json`, `core142-cold-proof.json` and `core142-graph-audit.json`.
The affected replay is `core142-affected-results.json.gz`; native and rejected
probe inputs are retained separately from regenerable build products.
