# Pbg::File allocation profile evidence

## CORE/EXACT-141 production admission

`src/PbgFileAllocation.cpp` now owns the sole explicit File allocation
instantiation, using the existing shared scalar body and the C++20 profile
established below. Canonical unit `pbg_file_allocate` strictly replays all
67 bytes and three independently anchored relocations. PbgFile.cpp retains
its original `/EHsc` profile and all twelve accepted methods. No constructor,
layout, exception declaration or allocation semantics changed.

Adding the provider changes the conservative receipt snapshot path set from
278 to 279 entries. Original inputs and receipts were preserved before editing
in `.analysis/core141-pre-header-inputs.json.gz`. All 163 prior objects were
rebuilt under their unchanged profiles, then all 890 prior units strictly
replayed. The new provider adds one object and one complete physical unit:
891 units / 164 objects / 167,737 disjoint comparison bytes. The graph audit
preserves all previous extents, targets and relocation roles. No old receipt was
rewritten. This one-time path-set migration is distinct from cleanup replay.

The 162 unchanged providers also preserve every section payload, relocation,
size and flag outside compiler debug/checksum sections; the changed object-path
record explains those auxiliary differences. PbgFile.cpp loses the old factory
instantiation. Its deleting destructors, wide wrappers and EH metadata, plus
the new provider's folded initializer, strictly replay all 232 support bytes.
These contributions receive no additional physical credit.

The Archive, Progress file, Player SHT and DamageQuery fixtures now link the
dedicated provider and continue to exercise their actual owner protocols. The isolated
File fixture still links the real File methods. OS, startup and valid-input CRT
fixtures retain their documented limits; native disk/game execution remains open.

The factory's source mapping and complete boundary are accepted, while its
authored/library provenance remains pending. The 899 source mappings and 891
physical units must not be conflated with the unchanged 181 authored exact
functions / 47,071 bytes. See `.analysis/core141-new-exact-results.json`,
`core141-graph-audit.json`, `core141-section-audit.json` and `core141-support.json`.
The historical private experiments below are preserved evidence.

## Historical CORE-140 probes

The locked target's complete scalar factory at `00539C80..00539CC2`
contains 67 bytes. Both branches join at `00539CBA`, followed by `ret 4`;
there is no jump table, external tail or disconnected cleanup in this body.
The attested caller query finds Archive open at `0053A6F0`, whose existing
canonical relocation identifies the actual Pbg::File allocation interface.
This is a boundary and compiler-profile result, not production admission.

The existing user-provided File constructor and shared variadic scalar factory
produce the complete native factory under both C++17 and C++20 when compiled
without `/EHsc`. The tested profile retains `/Od /Ob0 /GS /sdl /Gy /Zl
/arch:SSE2 /fp:precise /Gd`; the C++20 probe is the retained active input.
All 67 bytes strictly replay after resolving these independent identities:

| Relocation offset | Identity | Native address |
| --- | --- | --- |
| 12 | Existing scalar operator new | `0054275D` |
| 34 | Complete 31-byte compiler initialization helper | `0040C080` |
| 42 | Existing canonical Pbg::File constructor | `00539000` |

The initialization helper independently replays its complete 31 bytes against
the already-covered helper. Its folded identity receives no additional credit.
None of these destinations was obtained by solving a field in the factory.
The private compiler receipt, complete COFF contribution and relocation list
are verified in `.analysis/core140-private-proof.json`.

The old in-file instantiation emitted 129 bytes with `/EHsc`. Removing that flag
from the whole PbgFile.cpp provider would affect its accepted destructor and EH
support. This motivated CORE141's dedicated provider and explicit receipt
migration, preserving the File/IFile methods, exception declarations and
destructor profile. The shared source body required no special-case allocation.

## Rejected constructor hypothesis

A private first-declaration defaulted File constructor with in-class handle and
access initializers preserves the existing 51-byte constructor, but its factory
is 80 bytes. In addition to the compiler helper it emits a second three-word
zero initialization. The native 67-byte body does not contain that sequence.
Keep the current user-provided constructor; do not add manual clears, change
exception contracts or retain the rejected declaration in production.

The trial results are `.analysis/core140-private-results.json` and
`.analysis/core140-original-results.json`. Attested native evidence is
`.analysis/core140-pbg-factory.asm` and `.analysis/core140-pbg-callers.txt`.
Source, object receipts and original input closures are preserved privately.
CORE140 left canonical units, source mappings and origins unchanged. CORE141's
production admission above adds physical coverage and source presence while
leaving authored provenance and whole-game linkage unresolved.
