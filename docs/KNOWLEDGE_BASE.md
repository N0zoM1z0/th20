# Verified facts and open hypotheses

This page collects durable cross-module findings. Focused native/semantic evidence
is indexed in [EVIDENCE_INDEX.md](EVIDENCE_INDEX.md); current counts, local receipts
and next work belong in [the handoff](RE_HANDOFF.md). Git preserves superseded
session logs. Batch-local counts and pending statements are historical evidence,
not current repository status.

## Identity and evidence scope

The locked Japanese v1.00a Steamless file also contains 1.00c title/replay strings.
The reference matches this executable hash. Version labels alone do not select
a different oracle. Ghidra attestation proves the database corresponds to the
target; it does not validate inferred names, prototypes or function boundaries.
See [provenance](TARGET_PROVENANCE.md) and [oracles](ORACLES.md).

Reference fixtures, architecture rankings, decompiler output and structural COFF
matches are navigation/corroboration. Native producers and independent consumers
establish ABI contracts. Complete strict replay establishes exact code within
the recorded profile; it does not independently establish authorship, semantic
naming, original translation-unit identity or whole-game runtime.

## Whole dispatch and ownership

The ECL Runtime tick is exact as a complete 11,504-byte contribution. The whole
Enemy and Animation VMs remain open. Ghidra function membership omits valid
instruction heads in large dispatchers. Complete listing/PE interval audits
retain every case, internal jump and associated table; omitted jumps are not
padding. See [ECL evidence](EXACT_ECL_TICK_RECONSTRUCTION.md),
[Enemy layout](CORE_ENEMY_DISPATCH_LAYOUT.md) and [current VM scope](RE_HANDOFF.md).

Real typed Timer, PMR/vector, intrusive observer, lock, allocation and virtual
lifetime contracts are shared across owners. Allocation families remain distinct:
scalar storage uses new/delete, arrays use new[]/delete[], and File/decoded byte
buffers use the observed C heap family. Callback object destruction precedes
allocator lock 1; actual storage release runs under that lock. Process startup
remains separate. See [callback retirement](ANIMATION_CALLBACK_RECONSTRUCTION.md)
and [archive ownership](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md).

## Animation contracts

AnimationBase is 0x4C0 and Animation is 0x5E4 on x86. Reset is partial and retains
ownership; it is not a whole-object memset. +5C8 is generic user_data because
native callbacks consume different real owners. +558 and +55C have independently
observed, distinct parent roles. Geometry retains actual vertex layout/stride,
shape routing and native buffer domains. Full renderer/buffer integration is open.

The native eight-byte SprtFuncBaseInf has five virtual slots. Maintained
AnimationCallback reproduces layout/code, while its different RTTI name is not
claimed exact. EffectMenuWindowInf is directly derived and 72 bytes; reference
extra-base hierarchy is contradicted by native RTTI. +5DC is a signed32 cdecl
VM-entry hook, +5E0 a signed32 cdecl script selector. No collision trigger is
established for the entry hook. See [callback evidence](ANIMATION_CALLBACK_RECONSTRUCTION.md).

The Bullet script callback sign-extends type/color and checks the signed view of
the first style word. A negative sentinel returns the original script without
reading color/word indices. The positive path retains unchecked native index
domains. One signed consumer does not change the owner's unsigned word storage.

ANM integer/float operand masks preserve writable aliases. Floating random
selectors draw unconditionally; zero-bound integer selection does not draw.
The Progress and ANM consumers share the real GameRandom owner at 0x5BA4C4.
Rotation caches retain pre-wrap local angles; direction predicates are full int32.
Parent-chain tests require live acyclic storage. Float-to-int paths require
representable inputs in portable fixtures. See [operand evidence](ANIMATION_OPERAND_RECONSTRUCTION.md).

Motion wraps UV channels once, rather than normalizing arbitrarily large deltas.
RGB interpolation reads stored current separately at terminal duration, while
alpha uses the returned endpoint. Template copy changes only the trivially
copyable base. Child lookup passes remaining ordinals by value to descendants;
it is not flattened nth-descendant enumeration. Portable iterator return-copy
elision may retain observer hooks longer than native temporaries; accepted
traversals do not mutate topology. See [updates](ANIMATION_UPDATE_RECONSTRUCTION.md),
[binding](ANIMATION_BINDING_RECONSTRUCTION.md) and [children](ANIMATION_CHILDREN_RECONSTRUCTION.md).

## Open owner and runtime boundaries

The Renderer allocation is observed, but +6000DFC..+6000DFF is not explained.
Negative direct-access searches do not establish padding, and a plausible layout
does not establish a genuine owner. Raw mutable ANM packet/buffer lifetime,
remaining callbacks/lambda adapters, global startup and rendering remain open.
Do not substitute guessed fields, inert stores or fake method-only owners.

The public fixtures execute actual maintained owners inside documented domains.
Their explicit VM/OS/resource captures do not implement those missing production
boundaries. Whole-program compile/link and playable reconstruction require
independent verification. Follow [semantic policy](SEMANTIC_RECONSTRUCTION.md).
