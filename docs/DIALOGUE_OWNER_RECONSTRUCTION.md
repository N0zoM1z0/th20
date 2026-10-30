# Dialogue construction, callbacks and ready state

CORE/EXACT-161 reconstructs the complete 0x140-byte nonvirtual Dialogue owner,
its entire 1,738-byte constructor, and the genuine 0x58-byte Laser controller
needed by its cancellation protocol. Source lives in DialogueText, HudGauge,
LaserParameters, Context and AnimationHandle. All evidence uses the locked
Japanese v1.00a Steamless target.

## Native owners and protocol

Dialogue allocation at 0x4AE930 independently supplies 0x140 bytes. Its first
word is script state, without a vptr. Native construction and later consumers
establish three separate Timers at +4/+14/+24, two typed four-handle arrays at
+34/+44, eight individual handles at +54..+70, the actual 0x4C-byte Cursor at
+7C, borrowed script at +CC, four Vector3 values at +D0, full-width ready state
at +100, real DialogueFlags at +104, four scalar words at +118 and text position
at +128. The maintained layout has no fabricated padding or resource facade.

The complete constructor preserves this observed sequence:

1. Construct values and Cursor, initialize flags without overwriting their upper
   25 bits, then assign all three Timers to zero. Their previous value becomes
   -1 through the existing real Timer assignment contract.
2. Resolve the current AsciiInf/shared text file four times and spawn scripts
   20,20,21,21 through the actual File wrappers. Interrupt the second and fourth
   handles with event 7 through the original offset member.
3. Perform sixteen actual handle resolutions, write bytes +578/+579 to 21,
   clear bit 10 of the +49C word, and register the native empty follow callback.
   The +49C word is AnimationFlags.word_04, rather than the word at +498.
4. Reset the observed words and initialize all four positions to (16,0,0), then
   cancel Bullet, Laser and Enemy in order using genuine owner interfaces.
5. Store text position (384,640,0), width 320, clear Dialogue flag 6 and reset
   +110 after cancellation. Earlier resource/cancellation side effects are not
   silently rolled back on failure.

The callback's 20-byte cdecl static invoker and 43-byte const thiscall operator
retain their original partition. A natural noncapturing lambda reads the live
current FrontInf, obtains its actual Dialogue, calls the follow-box boundary
and returns integer zero. The invoker is compiler-generated; the operator's
authored/compiler classification remains pending.

LaserInf's independent COL 0x5A4FD4 identifies the AV class and public TaskInf
base. Its vtable at 0x571400 contains 0x4C9250 / 0x421680 / 0x421760. Construction,
deleting size 88 and consumers establish an observed list at +10, count +28,
initial handle 0x10000 at +2C, two Vector3 values at +30/+3C, file +48, unresolved
word +4C, signed view index +50 and Context pointer +54. Native construction is
noexcept. Resource retirement and complete RTTI/vtable data exactness remain open.

Context +14 is the Laser controller pointer. Its complete 17-byte getter is
identical to the existing physical ScriptStack frame-value unit at 0x41CA90:
both return all bits of the +14 word in EAX. Each genuine owner retains its
correct type; only the existing physical unit receives mapping/byte credit.
Laser cancellation returns integer 1 at 0x4C9490, correcting the reference's
void declaration. Its implementation remains an external boundary here.

## Complete compilation and comparison

The eleven changed reconstruction inputs select 59 providers / 392 previous
units from original receipts' actual include closures. Authentic original
receipts and all 336 required source versions are archived before editing.
The 279-path source set remains fixed. Each affected provider is cold-built once,
serially at reduced priority; 105 other providers reuse valid evidence. Two
earlier diagnostic Dialogue builds are separately retained as original-input
archives. No unfiltered whole-graph replay or full CI runs.

All 392 affected previous units and these eleven new complete units strictly
pass every byte and canonical relocation:

| Unit | Entry | Code / comparison bytes |
| --- | --- | ---: |
| Dialogue constructor | 0x4AF310 | 1738 / 1738 |
| Dialogue ready getter | 0x499560 | 20 / 20 |
| Four-handle array constructor | 0x4616E0 | 75 / 80 |
| Follow static invoker | 0x4AC290 | 20 / 20 |
| Follow callable operator | 0x4AFEE0 | 43 / 43 |
| FrontInf ready forwarding | 0x499110 | 25 / 25 |
| FrontInf Dialogue pointer | 0x4B8070 | 20 / 20 |
| Laser controller constructor | 0x4C87C0 | 179 / 184 |
| Laser context selection | 0x4D7E10 | 45 / 45 |
| Laser process selector | 0x478EE0 | 26 / 26 |
| Handle offset-7 interruption | 0x464510 | 29 / 29 |

The new physical comparison total is 2,230 bytes. Authored additions are the
two complete constructors, 1,917 bytes. The array and static invoker are compiler
exclusions; other origins remain pending. Both complete emitted INT3 tails are
included. The folded Context getter adds no duplicate physical unit.

Complete separate EH support replays 157 bytes: shared 29-byte handler and
36-byte flags-5 metadata, the full 48-byte Dialogue cleanup/handler section and
44-byte flags-1 metadata. The latter preserves state-zero Cursor cleanup after
construction. These support bytes are outside canonical progress totals.

Generated literal labels are reconciled using complete old/new COFF literal
symbol extents and unchanged independently established roles. Two old narrow
strings have different COFF/native pool alignment; their complete text including
NUL agrees. Pool packing receives no data-exact credit. Native component exports,
storage/RTTI/deleting-size evidence and prior bindings establish destinations;
no compared target field is solved. Manifest formatting is preserved, with a
parsed-graph equality check after formatting cleanup.

## Complete native destructor (CORE/EXACT-162)

The native `Dialogue::~Dialogue` at 0x4AFC00 performs four iterations over
its two independently owned `std::array<AnimationHandle, 4>` rows, retiring
both handles per iteration. It then retires seven individual handles at
+54, +58, +5C, +60, +64, +68 and +6C. **The +70 handle is not retired** by
this destructor. The actual `Cursor` subobject at +7C is destroyed automatically,
after all explicit retirement. The body is 228 bytes; the complete compiler
contribution additionally includes five genuine INT3 bytes (233 compared).

The natural source emits all 233 bytes with zero differences under the pinned
MSVC x86 `/Od` profile. All 14 relocations are mapped to the separately
observed common EH handler, process security cookie, four-handle array index,
AnimationHandle retire operation and actual Cursor destructor. The new
`dialogue_dtor` unit and seven pre-existing Dialogue units cold-replay exactly
from one fresh `core162-canonical/DialogueText.obj`, preserving the earlier
`core161` object and its authentic build receipt.

The existing actual-owner O2/UBSan fixture now verifies full 15-call release
order for 512 dirty constructions, with distinct nonzero handle values,
checks that +70 is not released, and populates all three Cursor containers
before destruction. The AnimationHandle backend remains captured, not a
claim about the native handle allocator. Full Dialogue resource/frame execution
and actual process-global startup remain open.

## Follow-box and child lookup (CORE/EXACT-163)

Native `Dialogue::follow_box` at 0x4B89A0 is now reconstructed as a complete
387-byte method, with **24 independently established relocations**. The natural
code resolves handle +6C, searches child identifier `field_13c + 166` at ordinal
zero, returns without modifying the destination if none exists, gets a 3D child
position, and multiplies X and Y separately by `2.0f / window_state.scale`.
It deliberately leaves Z unchanged. Position mode +114 selects the original
X correction: mode zero subtracts 36; mode one caps the child X scale at one
or adds 0.125 below one before multiplying by 32 and subtracting eight;
mode two uses the same added fraction times 16 minus eight; other modes leave
X alone. The result is written through the actual `Animation::set_position`.

The scale read at 0x5B8818 belongs to the independently established global
`WindowState` at 0x5B6758, offset **+20C0**. The actual COFF relocation
retains that source addend, rather than introducing another fake global.
The whole function needs `/fp:strict`; `/fp:precise` produced a shorter and
nonexact conditional path. All eight previous `DialogueText.cpp` units remain
strictly exact after the translation unit's necessary profile change. The
four compiler-renamed `"text"` literals in the constructor were reconciled by
comparing their unmodified old/new COFF bytes and native NUL-terminated bytes,
not by solving the target relocation fields.

The corresponding `AnimationHandle::find_child` at 0x44C670 has a natural
63-byte exact wrapper, with two pre-established relocation roles. It resolves
the mutating handle, delegates identifier/ordinal to the real animation tree
search when nonnull, and returns null otherwise. This is a separate method;
its complete exactness does not imply the animation pool or handle backend
has been implemented. No new fictitious class or field is introduced.

The guarded portable owner fixture now invokes both production methods with a
real intrusive animation child link, concrete handle-resolution boundary and
captured actual destination writes. It checks modes 0, 1 (below and above
unity), 2, unrecognized modes, three coordinate scales, invalid handle clearing,
missing child, z preservation, cross-FrontInf callback routing, and original
constructor/destructor resources. This is O2/UBSan host-side corroboration,
not native engine execution. Original build-receipt include closures select exactly 53 affected providers
and 351 strict units. All are freshly cold-compiled (51 previous outputs are
redirected to new protected products), and all 351 completely replay exact.
Original artifact/receipt hashes are preserved. Twenty-five compiler-local
literal names shift while the full old/new COFF bytes and native C-string
contents agree independently. Two native pooled ranges differ only outside
the terminating NUL. The other 111 providers reuse unchanged inputs and
receipts; no whole-graph replay is claimed.

## Semantic corroboration and remaining work

O2/UBSan passes 512 guarded dirty-memory constructions, 24 exception-unwind
failures, 2,049 live callback invocations and 3,072 full-width ready reads.
It uses actual Dialogue, Cursor and standard-container lifetimes, actual AsciiInf,
Bullet/Laser construction, real File wrappers and empty real Enemy clear.
The full File producer, handle backend, cancellation resource bodies, and
native resource/frame execution remain explicit fixture boundaries. Follow-box
logic itself now executes with real animation child traversal and a captured
position backend.
Allocation balance verifies Cursor cleanup after captured resource failures.
No native CPU, GPU, whole VM or playable-game result is claimed.

The affected FrontInf 1,706-case fixture and AsciiInf fixture also pass with the
current inputs. The private whole Enemy draft remains at 110 effective values /
81 primary heads and passes 36,232 cases. Twelve old synthetic ready-getter
mutation/exception cases are retired: the recovered getters are pure and now
read a live complete Dialogue instead of opaque storage. Production dispatch
remains undefined; it receives no fragment source acceptance or partial credit.

The whole Dialogue frame/message VM remains open, along with native resource
retirement and Cursor construction emission. Renderer ownership and fourteen
nondefault Enemy dispatch paths remain unverified. All completed follows use
the independently supported WindowState owner, not a facade. Reuse existing
negative trials and follow the affected-only workflow.

Private reproducibility records are core161-pre-dialogue-inputs and original
probe/ledger/previous-fixture archives, core161-final-frozen-source.json,
core161-canonical-build-recipe.json, core161-independent-bindings.json,
core161-existing-role-reconciliation.json, core161-protocol-native-identity.json,
strict result archives, public/whole-root test recipes and the retirement plan.
They are relative to .analysis/; raw native evidence is not committed.

> **CORE/RECON-990 update:** The actual 29B Dialogue `interrupt_offset_7` E8
> at `0x00464521` targets the distinct 35B child-event Handle wrapper
> `0x0044F0D0`, not the older 35B ordinary `AnimationHandle::interrupt`
> at `0x0044EF90`. Both original 35B wrappers and their separate
> 261B/246B callees are now explicitly distinguished, with corrected
> C++ caller symbol and 8/8 scoped exact replay.
> [Original evidence](ANIMATION_HANDLE_EVENT_DESCENDANTS_BRIDGE35_STRICT_EXACT.md).
