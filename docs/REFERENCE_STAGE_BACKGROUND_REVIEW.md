# Stage background, fog, camera and STD review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## REF-043 — 2026-10-07

All **121 remaining StageBackground implementations** were individually read
across **16 indexed files**, including static helpers, nested closures, both
CPU drivers and all three integration fragments. Original CRLF body and file
hashes were rebound to the clean pinned reference. All five type/API headers,
CMake, README, drawing validation notes and retained state/VM reports were read.

Decisions are **5 absorbed / 26 nonexact / 90 support**. The missing grammar
node at `vm_cpu_compare.cpp:13` is the default initializer of the already indexed
instruction builder. Its complete body and all 37 local definitions/closures
were read; no omitted implementation was found. Grammar coverage is now
**97 complete / 16 pending files**. Global body coverage is **6,761 terminal /
183 pending** of 6,944; the exhaustive review goal remains active.

## Natural fog value batch

Native `471790` constructs a real fog member at camera+150. Native `471410`
constructs five 28-byte fog values followed by Timer at8C, duration9C and modeA0.
The independently read `473590` sampler copies seven words per value and invokes
scale, subtraction and addition with a hidden result pointer. These establish
actual value storage and member ABI without an enclosing Background facade.

| Complete maintained contribution | Address | Bytes |
| --- | --- | ---: |
| FogValue default constructor | `0x00471940` | 64 |
| FogValue six-float constructor | `0x004718D0` | 112 |
| FogValue channel pack | `0x00473400` | 137 |
| FogValue scale | `0x00471DB0` | 172 |
| FogValue subtraction | `0x00471E60` | 226 |
| FogValue addition | `0x00471F50` | 226 |
| Shared FogInterpolation constructor | `0x00471410` | 106 |

**Seven new canonical units add 1,043 complete disjoint bytes. All 241 units
cold-replay from 57 objects over 18,320 disjoint bytes.** Source presence 241,
pending origins 180 and library 4 remain separate from authored 57 / 4,074 bytes,
which are unchanged. Original declarations/names and authored/compiler/library
origins remain open.

FogValue contains two distances, four float channels in blue/green/red/alpha
order and one packed word. Construction clears the actual value. Parameter
construction stores all six inputs before packing. Arithmetic creates a new
value and repacks its channels instead of carrying a stale packed color.
Indexed channel reads and legal byte access to the packed word naturally
reproduce complete original emission; no union aliasing or assembly is needed.
The existing Interpolation template supplies one shared semantic body.

Packing truncates each channel to int32 and retains its low byte, without
clamping. The maintained portable C++ domain requires that truncation be
representable in int32. Native CVTTSS2SI has hardware behavior for nonfinite or
out-of-range channels; historical Windows all-bit tests do not establish portable
C++ behavior for those conversions. Arithmetic tests use finite inputs with
representable resulting channels. Constructor tests separately preserve raw
NaN distance payloads and signed zero; they do not assert nonfinite channel
conversion equivalence.

All seven accepted native ranges were completely decoded, flow-closed and checked
against attested Ghidra. Native fog/pack/Timer call destinations were read before
probing and supply independent canonical relocation anchors. The compiler is the
locked candidate, with strict FP for FogValue and the existing precise profile
for shared interpolation construction. No solved diagnostic relocation is used.

Public independent C++20/g++13/UBSan tests cover every dirty byte pattern for
FogValue and FogInterpolation with guards, integer/fraction channel edges,
negative/modulo-byte conversion, repacking, signed zero and distance NaN payload,
10,000 widened-reference arithmetic cases, input preservation and assignment
aliasing. All checks pass on maintained source without the game binary.

## Whole reference comparisons and unresolved owners

All **11 unmodified production translation units** were freshly compiled serially
after the maintained source freeze, preserving strict FP and public transitive
ECL/native/binary/scheduler include paths from the reviewed CMake dependency graph.
They define **528 functions, including 91 static functions**. All **35 complete
comparisons across 32 bodies differ in length**. Associations are diagnostic,
not accepted mappings; no function was sliced to fit a target prefix.

The reference's free camera initializer clears around preserved matrices;
original construction instead calls seven Vector3 constructors, receiver-identity
matrix accessors, viewport values, Vector2 values/array construction and FogValue.
Using the separately recovered zeroing Matrix4 constructor would change those
preserved camera bytes. Native ScriptState constructs eight ANMs through a
constructor/destructor-aware array helper, typed Angle phase arrays and a final
four-byte value. Its original EH and full embedded lifetimes remain unclosed.

Background construction, loading, initialization, callbacks and destruction retain
raw STD relocation and ANM dependencies. The reference loader uses owned resource
vectors and explicit bad_alloc paths. Destruction performs eight embedded cleanup
calls and then another reverse member cleanup sequence. Full allocator/base/vptr/
EH/rollback ownership and real concurrent/resource lifetimes remain open.

Camera movement modes preserve distinct component writes, amplitudes, wrapping,
secondary fade and timer reset thresholds. The source extracts this switch from
original `4751B0`; it is not a separate complete original member. The source STD
loop has 21 explicit cases, signed instruction-size advancement, future-time tick,
opcode0 stop without tick, opcode1 byte-offset jump/time reset, five curve kinds,
ANM negative variants, mesh reset, interrupt and global color/rotation updates.
These source cases do not establish full original VM control flow or member ABI.

Object drawing preserves signed sentinels/layers, rotation and temporary Y-angle
restoration, current-sprite scale, fog/depth state and counters. Projection uses
16 actual sample points and inclusive viewport bounds after a distance gate.
Distortion initializes strips before changing main vertices, preserving the
otherwise surprising copy order. Draw/update fade gates, overlay consumption,
camera publication and cache restoration were read in full. COM traces and
finite prepared-object fixtures do not prove full rendered gameplay/device loss.

## Retained oracle limits

| Historical evidence | Recorded checks | Current source hashes | Scope |
| --- | ---: | ---: | --- |
| State/fog CPU | 62,048 | 3/3 | Same-address dirty construction; random-bit fog arithmetic and selected 32-mode sampling |
| STD VM CPU | 43,080 | 7/7 | Whole 0x3310 prepared state, finite camera domains, negative ANM variants and selected globals |
| Shared Sprite pool CPU | 2,915,831 | 389/389 | Multiple subsystems; Stage subset is 35,476 field comparisons in 77 groups |

The shared report covers 4,096 culls, 512 perspective cases, 400 cases each of
objects/geometry/foreground drawing, 384 each positive binding/interrupt cases,
48 mesh resets, 512 distortion cases and 1,024 frame updates. It normalizes
separate allocation/geometry/mesh pointers and uses COM recorders. Mesh grids
are valid 2..17; the transition allocation with geometry fade<30 is explicitly
excluded, and foreground global animation lists39/40 are empty. Factories,
malformed files, concurrent ownership and complete same-input rendered stages
remain unverified. The drawing prose's 239,658 shared count is historical;
the retained current JSON total is 2,915,831 across multiple suites.

No Windows driver or report writer was executed here. Matching source hashes
do not bind the executed binaries, compiler, startup state or all transitive
runtime behavior. Fresh evidence applies to the maintained natural fog values;
retained reference reports remain historical corroboration.
