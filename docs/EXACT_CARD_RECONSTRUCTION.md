# Actual Card construction and time state

EXACT-075 reconstructs the complete native Card owner and six complete callable
contributions required by the Enemy reader dependency graph. Source and exact
comparison do not establish whole Card gameplay, disposal or a playable game.

## Complete native owner

The original diagnostic allocator at `486A80` requests `0xC8` bytes, clears
that extent through the native compiler helper and calls `486BB0`. Independent
RTTI identifies `CardInf`; the original vtable at `56FD88` has the scalar
deleting destructor `486F20` followed by inherited Task enable/disable. The
constructor writes this vtable and calls the real 16-byte Task constructor.

The maintained owner has five actual AnimationHandle subobjects: one at `10`,
three raw-array elements at `14`, and one at `20`. A real Timer starts at `24`,
the 64-byte name at `34`, and a zero-initialized flag aggregate at `78`.
Scalar score/time/state fields precede two double clocks at `98` and `A0`, the
encoded word at `A8`, an actual Vector3 at `AC`, an unknown word at `B8`, and
the player index/Context pointer at `BC`/`C0`. Natural alignment supplies the
four-byte gap at `94` and trailing four bytes; no padding members or introduced
Services suffix are used. Existing Card update/start/finish/draw consumers from
REF-018 corroborate these storage accesses. Original names beyond the observed
roles remain uncertain.

The native constructor's real member calls, original
`initialize CardInf\n` literal at `56FD94`, full 29-byte EH handler and 36-byte
nonthrowing information record are checked independently. The constructor's
348-byte body and all five following compiler INT3 bytes are compared.
Native vtable/type identity anchors the constructor's relocation; this does
not claim a linked reproduction of all RTTI/vtable data or native disposal.

## Complete contributions

| Native address | Maintained body | Body / comparison bytes |
| --- | --- | --- |
| `486BB0` | `Card::Card` | 348 / 353 |
| `488990` | `Card::encode_time` | 105 / 105 |
| `4885E0` | `Card::invalid_encoded_time` | 148 / 148 |
| `4887A0` | `Card::active` | 44 / 44 |
| `488A20` | `Card::bind_context` | 54 / 54 |
| `478EA0` | Process `card` lookup | 26 / 26 |

These add 725 body /730 disjoint comparison bytes. Per-source flags are
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Original authored versus compiler origins remain pending.

After the shared Context header change, the complete frozen graph passes
568 strict comparisons using 104 freshly attested objects, covering 99,122
disjoint bytes. All 6,945 reference reviews remain terminal, 180 absorbed;
origins are 495 pending, nine library and 64 authored /16,948 authored bytes.
All 46 public tests pass (83.163 seconds), including the owned O2/UBSan Card
test. Target, tracking, reference and progress gates pass.

Time encoding performs three stores to the actual member. Signed IDIV
remainders are preserved; unsigned intermediates and conversions retain
native 32-bit addition/multiplication wrap without C++ signed-overflow
undefined behavior. Validation reads the actual word and returns a full-width
integer 0 or 1, preserving the original quotient/remainder/checksum evaluation.
The reference free function's bool return is not the original ABI.

Active-state observation tests bit 0 of the Card flag word and returns bool.
The Context slot at `10` is now a borrowed `Card*`. Real typed Context getter
and setter bodies reproduce the existing shared physical heads `411700` and
`412DA0`, respectively; these receive no duplicate unit or byte credit and do
not establish exclusive original type ownership. Binding stores the index,
then resolves the actual process Session using that member; it does not publish
the Card. Context publication is an independently tested operation.

Three complete reference associations close: constructor together with its
already accepted Vector3/AnimationHandle dependencies, encoding, and validation.
The association containing binding and full initialization remains nonexact.
The separately reviewed DamageRegion binding association uses the same physical
address but retains its own unclosed source/owner protocol; Card acceptance does
not import a Region method. Factory and destructor associations remain nonexact.

## Owned verification and boundaries

The O2/UBSan test uses real Card/Task/Timer/handle/vector construction and the
actual global Session/Context bodies. Dirty guarded storage checks all typed
defaults, natural gaps and boundary preservation. Independent wide-integer
calculations check signed extremes and complete 32-bit wrapping; valid times
and deliberately damaged checksum words test full integer returns. Whole-object
snapshots check that queries preserve state and encoding/binding change only
their intended members. Two-context publication, null lookup and replacement
effects run through production code.

Card destruction is explicitly a fixture boundary. Factory pre-initialization,
callback registration, start/finish/update/draw, animation cleanup, complete
game startup/linking/runtime, both whole Enemy readers and the 41 KB opcode
root remain open. Player native construction at `4F46A0` confirms a much larger
owner containing fixed Option/Shot arrays; its source declaration still needs
all allocation, typed-field and complete child-construction evidence. No
partial whole-reader or Player exact credit is granted.

Private evidence is retained in `core075-owner-construction.asm`,
`core075-card-publication.asm`, `core075-audit.py`, `core075-support.json`, and
`core075-defs.json`. The first probe's checksum-local ordering/return expression
and index-argument use failed whole comparison; original source and diagnostics
are retained as `core075-card-probe-v1.cpp` and its results. The subsequent
natural body preserves evaluation order and the stored index. Canonical replay
is compressed from the outset; completed configuration/registration/cleanup
writers are one-time operations and must never be rerun.

Protected cleanup retires four probe object/receipt files /60,070 bytes while
all 208 canonical hashes and private native/failed source evidence stay
unchanged. Post-cleanup strict replay passes 568/568 with existing objects.
Two earlier inactive successful snapshots were archived losslessly before source
changes, saving 861,845 bytes with original-content hashes and all 562 prior
comparisons checked. This batch frees 921,915 bytes in total; build retains only
current canonical objects/receipts. Installed tools/game/reference are preserved.
