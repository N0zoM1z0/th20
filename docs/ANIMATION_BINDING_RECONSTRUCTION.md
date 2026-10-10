# Animation template preparation and scoped child lookup

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-119 reconstructs the actual template preparation dependency of VM
creation and the complete recursive identity lookup. Seven complete roots compare
465 bytes and replay 16 independently resolved relocations. Maintained declarations
use the existing canonical Animation and AnimationFile owners, rather than a
Renderer prefix or a substituted lifetime. The frozen 270-source graph passes 794 strict units / 155 fresh objects /
149,535 disjoint comparison bytes. The production O2/ASan/UBSan fixture passes
24,022 cases. Required public gates are recorded in the current handoff.

| Maintained operation | Native address | Complete bytes |
| --- | --- | ---: |
| Scoped child identity lookup | 0x44C6B0 | 241 |
| Copy AnimationBase state | 0x4371F0 | 34 |
| Clear field +570 | 0x429E50 | 24 |
| Set field +5DC | 0x438A50 | 25 |
| Set field +5E0 | 0x438A30 | 25 |
| Clear the two pending fields | 0x429E30 | 32 |
| Apply one file template | 0x438B70 | 84 |

All roots include their native returns and complete compiler contributions. No
associated EH section is emitted for these seven bodies. The actual node and next
getters separately replay their existing 16/17-byte physical aliases; they add no
duplicate comparison coverage. Canonical child indexing, Timer integer assignment
and memcpy identities already have independent evidence. New call destinations
follow complete attested callee bodies, not target fields being compared. Original
method spelling, semantic names for the pending fields and authored origin remain
unproven; these matches add no authored-origin credit.

## Template storage and lifetime

The original 84-byte method clears +570, clears +5DC then +5E0 through the actual
32-byte helper, selects `templates[script]` with stride 0x5E4 and copies exactly
0x4C0 bytes. It then assigns zero to the +4D8 Timer followed by the +4C8 Timer.
Both use the independently established integer assignment wrapper at 423520;
this is distinct from an unconditional Timer reset.

The source copies the actual `AnimationBase` member with ordinary memcpy.
`AnimationBase` is trivially copyable, has no owning pointer members and remains
0x4C0 in both the native and portable semantic builds. The base's complete object
representation, including its padding, is copied. Animation's resource pointers,
callback, handle, intrusive nodes, parents and other tail state are retained.
No complete nontrivial Animation object is copied or zeroed by this implementation.

As observed in native code, script bounds and source/destination overlap are
unchecked. The accepted domain supplies a valid template index and distinct live
objects. The native File owner remains 0x70 and Animation remains 0x5E4 on x86.
The maintained preparation operation does not perform loading, File retirement,
parent attachment, list publication or VM interpretation.

## Lookup behavior and signed reads

The 241-byte search starts at the receiver's actual index-one sentinel. It skips
null-valued nodes and nodes whose Animation pointer equals the receiver, traverses
siblings, and recursively examines nonempty child chains. It interprets +440 as
a signed 16-bit value for comparison with the full 32-bit requested identifier.
Identifier -1 is a wildcard. The receiver with identity -2 has a separate terminal
fallback: after unsuccessful matching/recursion on the last eligible sibling, it
returns that sibling even when the requested identifier does not match.

The ordinal is decremented only when the current frame sees a direct match. A
recursive call receives the current ordinal by value. Matches inside an
unsuccessful subtree do not modify the parent's ordinal. For matching siblings A
and B, with matching child C under A, ordinal zero returns A and ordinal one
returns C; ordinal two returns null. A flattened nth-descendant rewrite would
incorrectly return B for ordinal two. The implementation preserves the native
scoped behavior, including tested negative ordinals, rather than repairing it.
The accepted search domain requires remaining ordinal decrements to stay within
int32. Cyclic malformed graphs and a decrement from INT32_MIN are outside the
portable semantic claim; no wraparound implementation is inferred.

The storage declaration at +440 remains uint16. A local int16 interpretation
expresses the demonstrated signed consumer. Newly reviewed 338-byte preparation
at 4383A0 and 226-byte preparation at 438940 both write a truncated script index
there. Those writes corroborate width and index flow; truncation alone does not
establish a globally signed declaration or a unique semantic role for every use.

## Independent semantic checks

The same maintained bodies pass 24,022 C++20/O2/ASan/UBSan cases. Seventy-two seeds
cover deep, wide and balanced trees, selected subtrees, isolated roots, signed
identity extremes, wildcard and -2 fallback, negative and exhausted ordinals,
null-valued placeholder nodes and a live observer. An independent metadata model
uses explicit ancestry frames and per-frame remaining counts. Six hand-written
cases distinguish scoped search from flattened counting. Every search checks the
complete representation of all 33 real Animation objects and the placeholder
for accidental changes.

Another 128 seeds use three genuine templates, an actual allocated geometry
buffer, real child links and a live observer. Expected whole Animation state is
constructed independently from the source base and the explicitly changed tail
fields. Timer expectations distinguish initialized and uninitialized flags. Each
seed checks full destination bytes, unchanged source bytes and both full-width
pending setters. Nodes detach while their owners remain alive; real Animation
retirement releases geometry through the maintained allocator.

File retirement remains undefined in production. The host fixture permits only
borrowed template views, clears the view before retirement and asserts that no
owned file resources are present. Its unresolved three-argument binding fixture
aborts if accidentally called. These fixtures do not claim original loading,
File retirement, VM execution, renderer resources or game runtime equivalence.
The first private semantic compile found a missing allocator label; the second
found the unresolved three-argument binding linkage. Corrected fixtures passed
before production migration; failed logs remain preserved.

## VM and Renderer boundaries

Attested full bodies distinguish three different preparation operations:

- Parent/VM binding is 194 bytes at 4382B0. It calls the 84-byte template method,
  inherits parent flag bit24, preserves the direct parent separately, selects a
  root parent and field +4E8, then enters the 39,470-byte VM update at 42B5D0.
- Preparation at 438940 is 226 bytes. Its null-script path zeroes an entire
  0x5E4 Animation and returns -1; the valid path resets and assigns state. Its
  valid lifetime/preconditions and complete maintained body remain unaccepted.
- Preparation at 4383A0 is 338 bytes. It additionally tests File stage, invokes
  Renderer processing and increments a Renderer counter. Its whole-object zero
  path and original Renderer ownership remain open.

The full 922-byte VM creation function at 450CB0 remains a separate open root.
The current batch closes its template-state dependency without inventing the
Renderer owner or claiming its update/interpreter.

Fresh decoded-operand navigation reviewed 10,453 existing instructions in the
Renderer interval and 23,733 in the selected VM interval. Matches established
actual Animation construction/retirement and 0x5E4 template-array stride leads.
They did not identify an actual owner for Renderer+6000DFC..6000DFF. The allocation
at 418830 is 0x7D40E94 bytes, consistent with known sized-delete consumers; its
size modulo 8 and 16 is four, contradicting whole-owner alignment padding as an
explanation. This does not rule out nested storage, packed types or an
uninitialized field. Absence of a directly matched displacement is not evidence
of padding or of absent dynamic access. Keep the four-byte interval unresolved.

## Evidence retention

Private attested exports, failed experiments, whole compiler/support proofs,
original SHA-bound compiler inputs and semantic receipts stay under `.analysis/`.
Current accepted products are selected by `config/match-units.toml`. Historical
private receipts cannot be relabeled fresh after shared declaration migration.
Superseded object pairs are retired only after closure archival and replacement
verification; all current objects, target, native evidence, tools and reference
sources are protected. CPU-heavy work remains serial at nice15.

All75 public tests pass in255.761 seconds; the complete public gate passes in
257.834 seconds. The seven production roots/supports strictly
replay and the actual maintained production bodies pass24022 O2/ASan/UBSan cases.
All155 affected objects compile once. Complete independent literal identities
reconcile30 label changes across45 relocation roles; no compared target field
is used to discover a destination.

Protected retirement removes316 final files/8743326B;
combined with mid-batch retirement,318 files/
8778108B (8.37 MiB) retire. The retired scope is154 previous canonical
pairs, the migrated private batch pair, the superseded private lookup pair,
three copied host dependency TUs and regenerable bytecode. Original actual
compiler input/receipt/SDK closures are SHA-verified before deletion. All794
completed exact results,270 source hashes,310 current canonical hashes and
20 retained native evidence hashes remain unchanged. Current products,
native evidence, original target/reference/tools/database and historical input
archives are protected. No unchanged-source cold rebuild is performed for cleanup.
