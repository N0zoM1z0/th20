# Overlay, HUD, SmallScore and StageCompletion review

## REF-033 — HUD batch and Dialogue protocol

All134 HUD implementations now have individual hash-bound decisions:2 absorbed,
59 nonexact and73 support, across36 fully read indexed files. Together with
REF-032's162 score/completion bodies,296 of this672-body family are reviewed;
Overlay's376 implementations remain pending. Global4,561 terminal /2,383 pending
of6,944. Three retained-C grammar files/eleven sites are manually reconciled;
global70 complete /43 pending gap files. Source reading, individual review,
compilation and whole native-owner recovery remain separate facts.

Three independently rewritten natural contributions add325 complete bytes:

| Component | Native entry | Complete bytes | Independently observed contract |
| --- | --- | --- | --- |
| DialogueFlags construction | 4AEC90 | 66 | Actual four-byte member at Dialogue+104; zero bit0/bit1/bits2..5/bit6, preserve upper25 |
| SJIS lead predicate | 4B6460 | 62 | One byte argument, full-int0/1 return; inclusive81..9F andE0..FC |
| Dialogue text decoder | 4B7C90 | 197 | Signed input load, modulo-byte XOR key, shared BSS5C4A20, paired-lead trail skip, remaining underscore to space |

The real140-byte Dialogue constructor4AF310 independently calls the flags
constructor on+104. Its four field meanings remain provisional. Decoder callers
49F3D0/4AFFF0/4B00B0/4B0720 and the predicate's sole decoder caller establish
separate function ownership. The decoder calls4B6460 and tests fullEAX, while
the reference helper declares unsigned/bool. Original buffer stores/reads/return
and six Ghidra data xrefs establish5C4A20 before canonical relocation anchors;
no diagnostic solved field is used as evidence.

All three entire native contributions are independently PE-decoded with closed
internal branches and actual final RET. The predicate retains disconnected
JMP4B6498..6499, omitted by Ghidra's instruction iterator. The decoder uses one
shared semantic body and external result storage. The next BSS buffer5C4B20 has
independent256-bound copy writers51E4CC and523E07; this corroborates adjacency,
not the allocation/extent/lifetime of the preceding Dialogue buffer. Production
storage therefore remains undefined instead of introducing an inferred array.

The decoder has the original unbounded asset-domain contract: encoded NUL must
decode within available result storage, and every lead byte must have a non-NUL
trail byte. An unmatched final lead skips the terminator and can read stale or
out-of-range storage; malformed inputs are not accepted as equivalent to the
reference's bounds exception. Each call overwrites the shared result. Portable
C++20/UBSan tests use separate synthetic256-byte storage, all256 predicate
arguments, all leads with underscore trails, nonlead high bytes, lengths0..255,
closed-form encoding keys, retained trailing storage, unchanged input/guards,
shared-pointer overwrite and512 dirty flag patterns.

Full cold canonical replay:152/152 units,43 objects,10,405 complete bytes.
Source152, pending origins91/library4; confirmed authored57/4,074 unchanged.
No enclosing Dialogue/HUD source, allocator, renderer, resource or game linkage
is accepted from these value/text contributions.

All43 original family production TUs were rebuilt serially after final source
freeze with actual inherited paths/strict FP. All18 HUD objects have current
receipts and defined static/external symbol inventories, including genuine load
templates, array helpers, lambdas and EH/deleting contributions. Forty complete
candidate comparisons all reject by contribution length; no target-sized prefix
is compared. Three complete49-byte deleting wrappers structurally match:
FrontInf emitted in core/lifecycle, and Dialogue. Original owner/vtable/dtor/EH
and sized-delete lifetime remain unclosed, so these earn no canonical credit.
Constructor/destructor stores independently bind HUD vtable57062C to
4B06A0/4B5BB0/421760. Its deleting wrapper calls4AFAA0 and sized delete54278D
with2D8. The broader436-head family export remains provisional. Missing native
JMPs4B1528..152C and4B90B5..90B6 were separately PE-decoded; rejected VM/table
and factory extents are not shortened.

Native4AC290's stack-local closure calls thiscall4AFEE0; the reference callback
flattens that partition. Native resource wrapper4B5900 pushes0 to4B5920 and
returns fullEAX0. Native4B5920 returns fullEAX0/1; the reference no-argument/bool
loader omits this callback argument and changes ABI. Its argument type and
original Worker/global resource ownership remain unresolved. The constructor
and resource paths cannot be recovered with fabricated receivers/parameters.

Dialogue VM defaults3/30 and codes>36, skip held9/0>=20, Timer countdown,
forty-frame cooldown, music/completion and opcode36 advancement were read.
Opcodes15/16 decode the live script when the queued worker executes; opcode17
owns an earlier string snapshot. Source merges original clear/write/completion
functors using booleans and captures. Ruby comma/atoi, outline.5/.6, slot9 locking,
Cursor destruction and handle70 retention are distinct ownership/domain issues.
Full original switch tables, callback identity/capture lifetimes and EH remain
unclosed; retained918/631-line decompiler files are evidence only.

HUD frame/score/icons/notifications/draw/feedback/resource code and all nine
fixture fragments were read. Boss marker scratch Z accumulates across visible
markers because458FA0 writes only XY. Life-threshold source supports actual41
data entries and throws above40 despite native0..100 clamp/adjacent reads.
Score draw sign-extends the low word; repeated mutating getters remain visible.
StoneMenu and active Dialogue paths are excluded from the frame fixture;
viewport/matrix COM and text/GPU callbacks are substituted. Pixel output,
thread/resource lifetimes and unrestricted game integration are unverified.

Retained HUD report232192/0 is a subset of shared Sprite2915831/0, not an extra
total: draw/scene20480/18432, feedback/wrapper16384/2816, icons16384,
notifications18432, enable36864, frame36864 and score65536. All389 hashes and
shared digest are current. The historical first-failure report1798099/960 has
235 current/17 stale hashes, including HUD update/notification changes; all960
failures are hud_frame_pool. The empty update_failures log adds no proof.
All28 retained draw constant words independently match the locked PE.

Overlay's full production/fixture/recipe/writer text has also been read, but
its individual original-owner/table/COFF review is still pending. Its retained
870400/0 report has42 current post-run source hashes; the oracle does not link
owner/lifecycle/factory/visuals objects and compares several virtual returns
only in AL. This is no whole-owner or executed-build identity. No Windows CPU
oracle or evidence writer was executed during this review.

## REF-032 — historical score/completion checkpoint

REF-032 is a coherent 672-body family: Overlay376, HUD134, SmallScore74 and
StageCompletion88. This checkpoint closes all162 SmallScore/StageCompletion
bodies individually. Their nineteen indexed files, headers, production/oracle
recipes, retained reports and evidence writers were read in full. Decisions:
one absorbed,28 nonexact,133 support. Overlay/HUD's510 bodies remain pending;
compilation and address inventories alone do not count as their review.

Global4,427 terminal /2,517 pending of6,944 pinned implementations. Two oracle
grammar files/six calling-convention sites are manually reconciled:67 complete
/46 pending gap files. Each decision binds the exact body hash and its source
location in `config/reference-function-reviews.csv`.

## Complete value contributions

| Actual value | Native member | Complete bytes | Independent evidence |
| --- | --- | --- | --- |
| ScoreEntry,68 bytes | construction50FD50 | 127 | SmallScore constructor builds two arrays of eighteen records; typed Vector3/Timer calls and native field stores |
| HudGauge,8 bytes | construction4AECE0 | 34 | Boss panel constructs four gauges; HUD consumers read first word as float |
| OverlayCounter,8 bytes | construction532850 | 33 | Overlay constructor constructs member at38, initializes0/1500 |

These are natural shared C++ types, with no enclosing owner facade. All three
complete native ranges end at their actual RET and are independently PE-attested.
ScoreEntry uses existing Vector3 and Timer constructors with independently
established relocation anchors422E10/422D90. Its two native float fields30/34
correct the reference's integer declarations; their semantic roles remain
unknown. Implicit alignment bytes3A/B are untouched. HudGauge's second word
and OverlayCounter's arithmetic/signedness are not accepted from construction
alone. Names and authored/compiler origins remain pending.

Full canonical replay:149/149 units across41 cold objects,10,080 complete bytes.
Three additions contribute193 bytes; source149, pending origins88/library4.
Confirmed authored57/4,074 is unchanged. Portable C++20/UBSan tests construct
each actual value over255 nonzero dirty patterns, test fields and guard bytes,
and verify ScoreEntry's retained padding. The reference207-byte free constructor
helper itself is nonexact; its semantics are absorbed through the independently
rewritten127-byte real member.

A natural84-byte HudPanel constructor emits109 versus native159 bytes, including
unrecovered native array/EH construction. Default, EHsc, EHa and externally
partitioned gauges preserve that difference. It remains private and unaccepted.
No inert locals, padding, assembly or compiler-specific semantic branches were
introduced to hide it.

## Production compilation and native diagnostics

All43 original production translation units compile serially after maintained
source freeze, with the four modules' actual inherited include paths and strict
FP recipes. Their fresh receipts bind source/compiler/flags and complete objects.
SmallScore's four and StageCompletion's five production objects have explicit
static-storage and external function inventories, including inline wrappers,
both callback thunks, adapter bodies and the deleting destructor.

Thirty complete comparisons produce28 size differences, one mismatch and one
structural match. Full COFF contributions were inspected after size rejection;
target-sized prefixes were never compared. The132-byte SmallScore destructor
mismatches despite equal sizes. Its49-byte deleting wrapper structurally matches,
but references the unclosed destructor and sized delete54278D(F98). Actual owner,
vtable/EH/resource identity is not canonical, so the wrapper earns no exact unit.
Diagnostic solved relocation fields in a mismatching body are not usable anchors.

Fifty-five focused native heads cover thirty SmallScore, twenty-two completion
and three additional helper bodies. All are below instruction caps and every
displayed instruction matches the locked PE. Four omitted two-byte direct JMPs
were independently decoded and attested; ranges retain those jumps. The native
SmallScore constructor-bound vtable573954 exposes deleting destructor50FF30,
enable4A0A70 and disable421760. All three entries were independently read.
The larger436-head family export remains provisional pending full Overlay/HUD
range and owner review; its existence is not a completeness claim.

## SmallScore observations and limits

The actual F98-byte CallbackOwner embeds an owned584-byte Animation at1C,
primary/secondary18*68 arrays at600/AC8, viewF90 and ContextF94. The constructor
uses typed array construction. Spawn rotates the first ten records; signed
negative cursors remain unguarded. Reversed decimal digits include zero's one
digit and negative glyph10. Timer0, position, speed1, color and cursor update
follow independent native field uses.

Update moves/damps the first thirteen active records and expires them after60.
The last five fade alpha by4 after60; the secondary array is unused here. Draw
configures layer21, conditionally disables fog, preserves age-based spacing and
distance alpha, stages glyph fading at52/56/60 and handles the negative glyph.
Bonus text preserves the three formats, float-to-double promotion, alignment,
style, color restoration and operation order. Initialization installs enabled
callbacks at25/51, ANM script121 and Context objects_04[6]. Native allocation,
Scheduler, Animation, text/graphics resources, real callback owner and EH remain
unclosed; Environment injection changes original ABI and function partitions.

The retained46208/0 report covers4096 record constructors,128 whole constructors,
4096 spawns,4096 update/draw frames and128 initialization/destruction cases.
Both retained reports bind29 hashes:28 current and one stale `text_renderer/text.hpp`.
The full driver maps selected original instructions, binds Kernel32 IAT/heap and
Scheduler, and replaces eight initialization/view/layer/fog/sprite/descriptor/
quad/text-commit boundaries. Text setters retain original field writes. It
compares mutable owner bytes, events and Text state while normalizing vptr and
equivalent Context/node/callback/link pointers. Corrupt indexes/ownership, OOM,
full renderer and graphics output are outside its domain.

The writer rejects a failing report but subsequently rebinds source hashes;
it supplies no identity for the executable/build that produced the report.
Neither writer nor Windows CPU oracle was executed in this checkpoint. Retained
counts are scoped historical observations, not current semantic acceptance.

## StageCompletion observations and limits

The full1836-byte native completion member separates replay end, Player finish,
practice/spell completion, main-stage6 clear, extra-stage7 selection/clear and
ordinary stage advancement. The source factors those into injected Environment
helpers; individual helper bodies have no independently accepted native extent.
Continue/death clamps mutate before achievements; stone notification/grant and
profile clear counters preserve their conditional ordering. Guarded scene writes
substitute scene2 when graphics event bit200 is set; ordinary advancement uses
scene12, at-most7 stage increment and Session flags4. Spell best score truncates
to tens: native4BE2D0 multiplies the unsigned quotient by10 before comparison.

Native unlock4BD780 returns the raw metadata byte in full EAX; reference bool
normalizes it. The completion caller tests EAX, so valid0/1 fixtures cannot prove
the return ABI or arbitrary-byte behavior. Notification writes/increments its
checked16-entry queue before checking flag64, setting byteE8 and advancing RNG1
checksum. Stone grant checks index9, caps counts9, but always updates checksum.
Actual SaveManager, lock20, checked arrays, getters and EH remain open.

Playtime4BCE10 separately calls scene getters, then two clock reads. Nonnegative
elapsed*100 uses two original CRT542D20 uint64 conversions and separate metadata
60/profile76B0 helpers4BCF30/4BCEF0. Its second clock store to Session2B0 remains
after negative/NaN elapsed. Source std::function, injected scene/restart and
out-of-range/nonfinite C++ unsigned conversions are not accepted as exact.

Replay mode488800 returns full-int0/1; reference free bool and its one-byte oracle
comparison do not attest ABI. Recording/recorded pointers use real receiver
array helpers414580/486E30, differing from raw global views. Header/inherited
stone access has no independently bound original extent. Replay owning lifetime,
allocation and invalid-index domains remain unresolved.

The retained126976/0 report comprises16384 completion cases with seven checks
plus4096 cases for three Replay getters. Thirteen local hashes are current but
exclude inherited Session/Profile/runtime/getter dependencies. The full driver
replaces sixteen completion boundaries, then restores488770's original prologue
before testing Replay getters. Synthetic bool unlock hooks omit raw-byte return
behavior. Shared49152 Progress checks were already reviewed and are not counted
again. Its writer does not check failed count before post-run hash rebinding;
neither report binds an executed build. No Windows CPU oracle or writer ran here.

## Continuation

Continue all510 Overlay/HUD bodies, remaining production/header/fixture/writer
reads, complete native control-flow/owner/table review, retained-report audits
and parser reconciliation before recording their decisions. All43 frozen
production receipts are current and can be reused until maintained source/profile
changes invalidate them. The full exhaustive review remains active. Credits and
reference pin/license limits remain in README and REFERENCE_REVIEW.md; no reference
implementation source was copied into maintained production.
