# Pbg::File allocation profile evidence

## CORE-140 private closure

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

The previous 129-byte production emission uses `/EHsc`. Removing that flag from
the whole PbgFile.cpp provider would also affect its accepted destructor and EH
support, so this result does not authorize a blanket profile change. A dedicated
allocation provider with the tested profile is the next production step; retain
the existing File/IFile methods, exception declarations and destructor profile.
Adding that source currently changes the conservative receipt snapshot path set;
plan the required receipt/build migration explicitly rather than rewriting old
receipts or placing this instantiation in an unrelated owner merely to avoid it.

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
Canonical units, source mappings and origin classifications remain unchanged;
this profile result does not establish authored provenance or whole-game linkage.
