# Actual Bomb ownership and dispatch

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-100 reconstructs the actual BombBaseInf/BombInf storage, lifetime,
scheduler registration, Context publication and virtual dispatch. Seventeen
complete contributions add 1,272 disjoint comparison bytes and 63 independently
bound relocations. Authorship and original source spelling remain separate
questions. The complete creation entry is maintained but remains nonexact.

The frozen 243-file source graph passes 706 strict units across 137 fresh
comparison objects and 135,568 disjoint bytes. Source mappings are 720,
including fourteen whole nonexact methods. The source change rebuilds 134
stale objects once and reuses the three freshly verified protocol objects.
Six compiler literal-label changes are reconciled from complete native
NUL-terminated string identity before strict replay. Authored exact coverage
stays 84 functions/24,209 bytes; reference absorption stays 238.

## Native observations

The locked Japanese Steamless target identifies two separate polymorphic
owners: BombBaseInf has six virtual slots and occupies 0xB8 bytes; BombInf
inherits the actual 0x10-byte TaskInfo, has three virtual slots and occupies
0x3C bytes. Maintained names are Bomb and BombController. Original RTTI names
are evidence for roles; the candidate's different RTTI spelling is not an
identity claim.

Bomb contains two Timers, Motion, three AnimationHandles and an
IntegerInterpolation at +0x80. The native constructor calls 0x00447980;
the reference's float interpolation declaration is inconsistent with that
producer. BombController contains the active Bomb pointer at +0x14, active
state at +0x18, Timer at +0x1C and Context pointer at +0x38. Context +0x18
is now a typed BombController pointer.

Initialization registers **enabled** update/draw nodes at priorities 33/44
through the actual scheduler. This corrects the reference's disabled
registration calls. The event consumer forwards two pointer arguments to
Bomb slot five, discards its return and returns zero, including the null case.
Draw similarly discards the virtual result and returns one. Finish propagates
the active Bomb's result, or returns zero when absent. Position/dimensions
pointer spellings are inferred from the whole damage-query caller.

Bomb destruction retires handles +0x70/+0x74 and clears controller **zero**'s
active pointer and state, even when the Bomb selects Context one. This observed
quirk is preserved. Controller destruction virtually destroys its active Bomb,
then removes both owned scheduler nodes. The shared allocator performs virtual
destruction outside recursive allocator lock slot one, followed by deallocation
under that lock. Context release destroys its owned controller before clearing
the publication pointer; repeated release is harmless.

## Complete comparison roots

| Root | Native address | Body bytes | Compared bytes |
| --- | --- | ---: | ---: |
| Bomb construction | 0x00478430 | 162 | 162 |
| Bomb ordinary destruction | 0x00477A60 | 118 | 123 |
| Bomb event | 0x00477CE0 | 15 | 15 |
| BombController construction | 0x004779B0 | 167 | 172 |
| BombController ordinary destruction | 0x00477AE0 | 149 | 154 |
| BombController initialization | 0x00477DC0 | 100 | 100 |
| BombController draw | 0x00477CB0 | 45 | 45 |
| BombController event | 0x00477CF0 | 64 | 64 |
| BombController finish | 0x00477F00 | 56 | 56 |
| Bomb Context selection | 0x00478290 | 54 | 54 |
| BombController Context selection | 0x004782D0 | 45 | 45 |
| Context controller getter | 0x00424010 | 17 | 17 |
| Selected controller getter | 0x00478040 | 26 | 26 |
| Shared allocator Bomb release | 0x0041F7C0 | 97 | 97 |
| Context controller release | 0x004BD1B0 | 48 | 48 |
| Selected controller destruction | 0x00477FD0 | 27 | 27 |
| Shared controller allocation | 0x00477960 | 67 | 67 |

Three contributions include five compiler alignment bytes each. Full native
bodies, terminal returns and closed internal branch targets are independently
audited. Typed Context setter 0x0041DE90 strictly compares all 22 bytes, but
aliases the existing byte_interpolation_set_duration physical contribution;
it earns no new unit or bytes. Existing source, origin and authored credit for
that physical head remain unchanged.

Support replay covers complete no-state EH handlers and FuncInfo records,
deleting destructors, callback thunks, destroy_at, typed allocator release and
the compiler auto-class initializer. Shared identical support receives no
duplicate physical credit. The unchanged generic new-T allocator naturally
emits the complete 67-byte allocation and 31-byte initialization helper.

The maintained controller is non-final: this candidate preserves the native
27-byte indirect virtual destroy_at protocol. A final candidate instead
devirtualized it to 16 bytes and failed. This is compiler-emission evidence,
**not** proof of the original class's final spelling or template instantiation
type. The original could have released through a base type.

## Source ownership and verification scope

Bomb.hpp is the shared declaration. Bomb.cpp owns lifetime, registration and
dispatch. Context.cpp owns the dependency-light getter/setter. BombCreation.cpp
owns allocation, global creation/destruction and Context's typed release body,
keeping allocator/lock dependencies out of existing Context callers.

The portable O2 fixture runs these actual shared bodies together with the
actual scheduler, allocator, TaskInfo, Context, Session, Timer and interpolation
protocols. It checks enabled registration, priorities, callback metadata,
draw disable/re-enable, null dispatch, pointer forwarding, discarded event
return, propagated finish result, both Context views, virtual derived
destruction, self-release, publication clearing and scheduler-node cleanup.
A different-thread try-lock establishes destruction outside allocator slot
one; a same-thread recursive-lock check would not establish that fact.

Startup/process placement and AnimationHandle::retire are explicit fixture
bindings. The latter records requested handles and clears the fixture handle;
it does not accept an original ANM implementation. Original Bomb::start and
BombController::update remain declarations. Their fixture definitions abort
if reached; the real scheduler update node is disabled before executing the
scheduler update fixture. There are no substitute gameplay bodies in maintained
source. Portable sanitizer results do not establish original game runtime.

The actual protocol also passes O2/ASan/UBSan with its temporary binary retired
automatically. All 65 public tests pass in 199.043 seconds; existing callers
of the shared Context declaration remain covered. Target-required tracking,
progress and public artifact checks pass.

## Remaining work

The complete create_bomb_controller entry at 0x00478300 emits 113 bytes against
the whole native 123-byte body. The remaining native failure path clears a
dead local pointer. No inert local reset is added to force its emission. Its
full native extent remains registered with zero exact credit.

Original Bomb start/update, character-specific implementations, ANM resources,
Player ownership and the full 1,707-byte hit damage query remain open. This
batch closes the query's actual Bomb getter/event dependency without replacing
the query with a host environment or claiming whole-game linkage/startup.

Private reproducible evidence: core100-production-bindings.json,
core100-native-roots-audit.json, core100-final-frozen-source.json,
exact100-canonical-results.json.gz and core100-final-literal-reconciliation.json.
Historical trial inputs and receipts are archived before retiring obsolete
objects and copied headers. Completed proof writers must not be rerun.

Protected periodic retirement removes 85 products/3,809,702 bytes gross during
and after this batch. The final cleanup saves 3,221,374 bytes net after its
historical-ledger archive. All 274 canonical object/receipt hashes remain
unchanged, and all 706 strict existing-object results equal the frozen proof.
No redundant cold build or duplicate large replay report is generated.
Native exports, active source, installed tools and historical input archives
remain protected.
