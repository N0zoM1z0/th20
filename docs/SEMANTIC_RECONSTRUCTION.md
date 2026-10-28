# Semantic reconstruction policy

Exact reconstruction is the current priority. The historical portable semantic
suite has been retired; old test paths and scenario totals in evidence documents
refer to dated experiments preserved in Git (see [retained tests](../tests/README.md)).
Use a temporary probe under `.analysis/` only to resolve a specific native behavior
or ABI question. Exact acceptance requires the complete native comparison,
including original error paths and EH.

Use one canonical profile-independent owner declaration for each production
type and one maintained semantic body. Recover field widths, offsets, signedness,
lifetimes, pointer ownership, state transitions and protocols from target-local
producers and independent consumers. Use the pinned compiler for ABI-visible
layout, calling convention, vtable, RTTI, EH and aggregate-return experiments.

No `TH20_MATCH_EXACT` or `DIFFBUILD` source-body/layout branches are permitted
under `src/`. Do not introduce inert locals, fake returns, arbitrary padding,
assembly, target byte arrays or incorrect declarations to force an oracle.
If a clean shared source cannot explain emission, record the disagreement as
an open hypothesis and investigate a minimal probe. TH095's historical debt
baselines and user-authorized x87 exceptions do not transfer to TH20.

Close coherent protocols with storage, semantic, compiler-emission and build
ownership evidence. Byte identity alone does not prove a proposed name/meaning,
and runtime behavior alone does not prove exactness. Record observed facts,
compiler observations, independent corroboration, inferences and unknowns
separately in the knowledge base and handoff.

Native findings and the limits of historical behavioral experiments belong in
focused evidence documents: [child traversal](ANIMATION_CHILDREN_RECONSTRUCTION.md),
[binding](ANIMATION_BINDING_RECONSTRUCTION.md),
[frame updates](ANIMATION_UPDATE_RECONSTRUCTION.md),
[geometry](ANIMATION_GEOMETRY_RECONSTRUCTION.md) and
[operands](ANIMATION_OPERAND_RECONSTRUCTION.md).
