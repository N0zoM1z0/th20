# Effect and Special State reference review (REF-027)

The pinned Oracatt/Touhou20 reference has 191 Effect and 131 Special State
implementations. All 322 bodies were read individually, including inline
methods, templates, lambdas, fixture hooks, two generated C evidence bodies and
the complete evidence writer. Decisions are bound to individual body hashes in
`config/reference-function-reviews.csv`: six absorbed exact, 133 nonexact and
183 support. All eight parser-gap files were manually reconciled. Original
reference files remain unedited and ignored; their missing license remains
recorded in REFERENCE_REVIEW.md.

Global review coverage is 2,968 terminal and 3,976 pending out of 6,944. Parser
gap coverage is 53 reconciled and 60 pending. This is a component checkpoint;
the exhaustive review and whole-module reconstruction remain unfinished.

## Natural exact components

All sixteen additions pass complete canonical relocation replay against the
approved Japanese v1.00a Steamless target. The final replay cold-builds all
129 units across 32 objects, covering 8,464 complete bytes. These additions
account for 765 bytes. Authored credit remains 57 functions / 4,074 bytes;
68 origins remain pending and four units are library equivalents. Neutral type
names describe actual values rather than establishing original class spelling.

| Actual component | Original address | Complete bytes |
| --- | --- | ---: |
| PackedColor constructor | 0x004142A0 | 24 |
| EffectParameters constructor | 0x0047BA30 | 106 |
| EffectRequest constructor | 0x0049CE30 | 65 |
| SelectionPulse constructor | 0x00461840 | 31 |
| Byte interpolation constructor | 0x00511930 | 79 |
| Byte duration setter | 0x0041DE90 | 22 |
| Byte mode setter | 0x005141C0 | 25 |
| Byte start setter | 0x00514150 | 23 |
| Byte end setter | 0x00514110 | 24 |
| Byte begin | 0x005141E0 | 87 |
| Float interpolation constructor | 0x004479E0 | 99 |
| Float duration setter | 0x0041DF50 | 22 |
| Float mode setter | 0x004394D0 | 25 |
| Float start setter | 0x004393D0 | 23 |
| Float end setter | 0x00438A70 | 24 |
| Float begin | 0x00439550 | 86 |

EffectParameters is the real 56-byte record: three Vector3 members, three float
lanes, a four-byte PackedColor and an enabled byte. Its constructor initializes
typed members in native order and preserves bytes 0x29..0x2B. EffectRequest is
72 bytes on x86, with two pointers, type, delay and this real parameter member.
Host tests retain natural host pointer alignment; they do not fabricate a
72-byte host record. SelectionPulse is eight bytes with enabled at zero and
radius at four; its three alignment bytes remain unchanged. The StoneSelection
constructor's four-element array iterator independently identifies its callback
at 0x00461840, stride eight.

Interpolation<T> owns five actual value lanes, a Timer, signed duration and
mode. Byte and float instantiations are 32 and 44 bytes; byte alignment bytes
5..7 are preserved. Begin takes const references, calls the four distinct
setters, reads the current value from the live start reference, then assigns
Timer zero. The source reference's by-value signature loses endpoint aliasing;
maintained source restores the observed native ABI and mutation order. Mode
setter returns its signed assignment. Float endpoints copy raw bits, retaining
negative zero, infinities and NaN payloads.

Independent complete native routines and already established Timer/Vector3
constructors anchor all calls. Canonical targets were selected before comparison;
no solved diagnostic relocation field supplied an anchor. The new constructors
and setters do not implement interpolation evaluation or complete Effect /
Special State owners. There is no assembly, alternate exact body, padded owner,
byte template or shortened contribution.

## Compiler and boundary audit

All 22 unmodified production translation units compile serially with the locked
MSVC candidate: sixteen Effect and six Special State. Their actual CMake include
paths and strict FP propagation are preserved by compile-reference-probes.py.
The final source fingerprint invalidated earlier receipts; all 22 were rebuilt
following the last source change. Complete COFF diagnostics cover 163 mapped
contributions, including template instances and inline callback methods: 162
have different sizes; the original SelectionPulse contribution is structurally
identical. Structural equality alone never grants exact credit.

Ghidra exports were checked for internal holes. Six omitted branches in four
heads were independently decoded: float sample 0x0042A110, factory 0x0049E0C0,
byte sample 0x00513710 and color query 0x00513F70. Full candidate extents remain
intact. These rejected owner/sample diagnostics do not settle native table,
shared-tail, exception or linkage ownership.

Current Ghidra has no containing function for either Converging update
0x0045C360 or Wavering update 0x00467430. Original six-slot vtables identify both
entries independently. Approved PE decoding recovers all 2,884 bytes / 768
instructions through RET at 0x0045CEA3 and 993 bytes / 277 instructions through
RET at 0x00467810. All 17 and 18 direct branches respectively land on internal
instruction boundaries; following 12 and 15 INT3 bytes are padding. The source
comment claiming Wavering lies inside the 0x004673F0 function is incorrect for
the current attested database: that earlier function is the deleting destructor.
Generated decompiler C remains evidence only and was neither imported nor
compiled; its inferred void return is not proof of the native callback ABI.

## Effect ownership and semantics

The real 0x13044-byte Controller derives from CallbackOwner. It owns six file
slots, Worker at 0x28, ready at 0x38, 1,024 typed handles at 0x3C, 1,024 requests
at 0x103C and view/context at 0x1303C/0x13040. Callback priorities are 41/42;
asset loading uses bullet, effect and screenswitch ANMs. Destruction joins the
Worker, clears, removes callbacks and unloads files 8/7/21. Original allocator,
thread, callback, template-array, vtable and EH ownership remain open.

Independent read-only data checks establish fifteen complete 32-byte descriptor
records at 0x005AFAB8, followed by only an eight-byte terminator (-1, zero).
The next words are unrelated pointers, so the source's declared sixteen full
records do not establish ownership of a complete zeroed final record. Ten
six-slot callback vtables were checked against their native head families.
Normal and secondary spawning are separate native functions; source merges
them through a bool and adds type bounds checks. Native typed handle/sret and
recursive child enabling differ from this source interface. Enqueue returns a
parameter pointer or the request-array start when full. Clear copies a local
Request with three indeterminate padding bytes; the reference normalizes them.

Each callback family was reviewed with its own initialization, update, draw,
interrupt, retirement and descriptor factory:

- RoundedPanel uses two Timers, ordered rounded primitives and event-one
  twenty-frame position/size interpolation. Literal integer-zero base callbacks
  differ from empty source void returns; RoundedPanel's interrupt slot is
  0x004613D0, not the generic empty callback.
- ShortLine instantiates 20/30/64 samples with RNG1 and byte alpha changes.
  LongLine combines separate orange/gray initialization through an extracted
  bool helper; alpha wraps after entry 47. Native constructor/template-array
  and helper partitions differ.
- Spiral and ReverseSpiral own 80 samples. Raw RNG1 stepping holds lock ten,
  with no modulus in random_byte. Reverse ordering/fade and optional Player0
  following were individually checked; extracted common helpers change ABI.
- Filled/triple rings merge distinct native geometry helpers through bool.
  Burst rings have 61 positions/colors and 62 radii. Thick-polyline rendering
  writes 2N vertices and advances the cursor by N after submission; this odd
  behavior is intentional. Capacity checks precede count guards.
- Radial trails contain 32 groups of 30 samples. The per-trail initializer has
  four stack arguments (RET16); the outer initializer has two (RET8). Byte
  alpha wraps in its forward loop.
- Wavering shifts 29 positions and uses ordered double sin/sqrt, float scaling
  and the unordered normalization branch. Player0's corner region gates alpha.
- Converging owns 200 child handles, ages 149/150 and two Hermite phases. It
  spawns real named children and touches ANM pools, RNG and file counters;
  native vector/handle/closure/allocator graphs remain different.
- TransitionPanels owns five real ANMs. Manual aggregate construction and
  destruction differ from native array/EH ownership. Mask/stencil/render
  ordering is recorded; empty-owned destructor coverage does not prove release.
- StoneSelection owns four pulses/buttons, twelve triangles and six handles.
  Selection events, repeated transforms, RGB averaging and alpha multiplication
  were checked. Fixtures replace Weapon queries with configured values and use
  smaller raw Save storage, rather than recovering the actual metadata owner.

## Special State ownership and semantics

The real nonvirtual Controller is 0xB4 bytes: a 24-byte intrusive list, two
Timers, float/byte/float interpolations and active at 0xB0. Entry is 0x34 bytes
with link, two actual typed handles, age and retained color/level. The reference
uses raw aggregates and casts Entry* to scheduler Node*; exact member values do
not accept the whole owner. Native list construction writes tail twice, which
is still unexplained by a natural initializer-only source. The active getter
returns the raw unsigned byte, while the source bool converts corrupt values.

Evaluation does not tick. Modes seven and seventeen accumulate; eight uses
Hermite; others use easing. Samples tick only for positive durations, pin the
end and set duration zero, returning start for seven/seventeen and end otherwise.
Negative duration continues evaluation. Byte conversion wraps. The unused
cubic(byte_order=true) branch has no call in this module.

Color returns the first active entry or chooses strict greatest Player meter
through mutating clamps. The fourth winning branch deliberately does not update
best. Frame processing includes modulo-three charge, boss/block gates, forced
color [-1,4], twenty health values, StoneR/B/Y/G, meter debit and 60/120/1320
interpolations. Entry pulses consume three RNG0 modulo64 draws after age60;
retirement includes missing-enemy and age1800 paths.

Initialization constructs Enemy file2/script selected+0x13F, effect11 and its
RGBA table, four clamped levels, twenty StoneAttack scripts, sequence-dependent
patterns, sprite/size values and Player counters. Original captures and
std::function<Enemy*>/ANM callback ownership remain open. Collection is a callable
receiver holding Entry*, not a native Entry member: it cancels bullets/lasers at
radius320, clamps level, adjusts meter and max, then returns zero. Draw emits
notice/level text at three scales and restores style after unticked alpha eval.

The source destructor advances the iterator BEFORE free; native frees first
then touches the observer. The fixture records free without releasing memory,
so this real semantic difference is outside its comparison. Source GameEnvironment
is an invented service interface; its 34 methods and four module bridges were
individually reviewed without attributing a new original virtual owner.

## Retained oracle evidence and current checks

No native Windows CPU oracle or evidence writer ran in this batch. Reports
are historical evidence, separately audited against the pinned current tree:

| Retained report | Passed / failed | Current source hashes | Limits |
| --- | --- | --- | --- |
| Special CPU | 116,736 / 0 | 32 of 34 | Enemy entity and Text header stale; writer attaches post-execution hashes |
| Effect Spiral | 69,120 / 0 | 189 of 204 | Fifteen stale dependencies and an old shared report digest |
| Effect Additional | 357,860 / 0 | 389 of 389 | Current hashes and matching shared report digest, no current execution |
| Shared Sprite pool | 2,915,831 / 0 | 389 of 389 | Effect subtotal 485,796 across 266 groups, overlapping reports |

Spiral and Additional totals must not be added to the shared Effect subtotal.
The shared current digest is 605f8e33...62e80e8b; the older Spiral report records
0dd7360b...77c976. All 389 relative shared source paths were resolved against
the report directory and hashed independently.

Fixtures cover finite interpolation/RNG/VM domains, normalized constructor
vptr/owner identities, full stored sample objects, vertex submissions and COM
traces. They do not establish startup, real GPU/device errors, resources,
concurrency, allocator lifetime or whole-game equivalence. Special text events
compare string length rather than content; effect parameters mask three padding
bytes. Special frame tests replace SpawnParameters construction with zero-fill
and exclude the actual entry initializer and production services.

Current portable C++20/UBSan tests check dirty implicit padding, parameter/request
values, all 256 byte endpoint values, endpoint alias order, retained tangents /
Timer flags and six float bit cases including NaN/infinity/negative zero. These
and final 129-unit canonical replay pass. Public tracking, reference and CI
gates must also pass before committing this checkpoint.
