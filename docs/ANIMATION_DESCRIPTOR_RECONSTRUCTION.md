# ANM descriptors, pointer tables and sprite binding

CORE/EXACT-133 accepts seven complete functions / 1,260 disjoint comparison
bytes from the real File descriptor protocol. The existing shared allocator
templates retain their single semantic bodies. No Renderer facade, packed
storage substitute, manual SIMD, target bytes or explicit padding is introduced.

| Entry | Complete bytes | Maintained operation |
| --- | ---: | --- |
| 00448AF0 | 73 | TextureRecord construction |
| 004488F0 | 252 | SpriteData construction |
| 004475F0 | 205 | Allocate the texture-record array |
| 00447520 | 205 | Allocate the sprite-record array |
| 00447480 | 158 | Allocate the script-pointer table |
| 0044D000 | 24 | File texture-identity packing |
| 004506F0 | 343 | Copy and normalize one sprite descriptor |

Every byte of each complete COFF contribution strictly replays with independent
canonical relocations. These seven contributions contain no appended alignment
or jump tables. Source mapping, authored origin and exactness remain separate
from loaded-file clearing, Renderer integration and whole-game runtime.

## Actual storage and independent consumers

Native File preparation at `0044A700` walks entry links at +0x24, accumulates the
16-bit script and sprite counts, and allocates three distinct arrays. Complete
allocation bodies establish 24-byte texture records, 88-byte sprite records and
four-byte instruction pointers. Their actual constructor heads and independent
postload/texture/clear consumers establish the members; sizes alone are not
layout evidence. Existing File storage and class/exception declarations remain
unchanged. All declarations stay in the existing AnimationFile.hpp owner.

TextureRecord contains the actual Direct3D texture pointer, external image
pointer/size, pixel-byte count, borrowed ANM header pointer and four-byte flags.
Native texture preparation writes and consumes those same slots. The header is
an opaque borrowed type, not a fabricated truncated header layout. GPU and
external image retirement are explicit Renderer/File operations. The record has
a trivial destructor; array storage release must not substitute resource release.

SpriteData's first three words carry File identity, texture index and packed
texture identity. All nineteen remaining lanes are floats. In particular,
constructor MOVSS stores and five independent postload MOVSS copies establish
the +0x24..+0x34 fields as floating values. The reference's integer array in that
interval is not imported. Corner coordinates, texture extents, UVs, output
dimensions and scale occupy the independently used offsets. Unknown extra
roles retain offset names. Ordinary layout gives all 88 bytes without padding.

The constructors initialize integer/pointer members to zero/null and float
members to positive zero. Complete native array EH contains only the game-lock
cleanup state and uses the established nonthrowing vector constructor iterator.
Together with the complete data-only native constructors, this corroborates
their nonthrowing contracts. The candidate reproduces both 205-byte factories
with noexcept construction; the potentially throwing declarations produce 219
bytes and additional array-construction cleanup, and remain rejected probes.
No existing owner's exception declaration is changed for emission.

## Pointer table and physical release aliases

The pointer factory allocates raw four-byte pointer slots without value
initialization. Its natural `new T[count]` body leaves entries unwritten;
callers publish script addresses later. No source zeroing is inserted. The
existing 25-byte File::script getter transports those actual pointers unchanged.
Packet interpretation and object-lifetime rules for mutable packet data remain
outside this accepted scope.

Texture, sprite and script-table deletion each reproduces the full 120-byte
existing release-array body at `0040D840`. File::clear independently calls that
same head for its three real pointer members. The canonical uint8_t release
source/object/unit remains its sole physical owner. Three full typed alias
replays validate all relocations and add no unit, mapping or byte credit.
The actual implicit destructors remain trivial; external image payloads and
COM objects survive array deletion until their separate retirement operations.

The three allocation EH protocols also strictly replay in full: twelve support
records / 288 bytes cover each complete 39-byte handler, 36-byte FuncInfo,
eight-byte unwind entry and 13-byte guard cleanup. Texture/sprite metadata folds
to the existing handler/FuncInfo at `0056828D`/`005A9FB0`; pointer allocation uses
`005676ED`/`005A95AC`. All have one lock cleanup state. No supporting EH or
release alias earns duplicate physical credit.

## Whole sprite binding and identity

The 343-byte File method first copies the complete 88-byte descriptor with
ordinary trivial assignment. It re-reads the actual File sprite array for each
operation, then writes u0, u1, v0 and v1 from copied corners and texture extents.
Width and height follow, using copied corner differences and the original
input's scale lanes. Direct maintained C++ reproduces the native REP copy and
complete SSE operation order without intrinsics, cached substitute owners or
artificial locals.

Disjoint live input/destination objects and exact self-assignment are accepted.
Partially overlapping object storage is not modeled as valid C++ lifetime or
silently repaired with the reference's memmove. Index bounds and zero/invalid
texture dimensions are not guarded by new production checks. Portable numeric
tests use finite values, nonzero dimensions/scales and valid array windows.

The 24-byte identity method returns `(id << 8) | index` over full unsigned
32-bit words. It does not mask the input index to eight bits. Native postload
calls that method and stores its result beside the separate File identity and
texture index in the actual descriptor. Original identifier tags, class names
and source-level parameter spelling remain inferences.

## Origin, boundary and semantic checks

Nine application origins are reviewed independently: the seven new roots,
the existing script getter and the canonical shared release-array body. Native
preload diagnostics, game File counts/publication, actual Direct3D/image/UV
consumers and custom lock-one allocator protocol establish game ownership;
using STL guards and ordinary new/delete does not make the whole allocator an
STL implementation. These decisions add 1,405 bytes to reviewed authored exact
coverage, including 145 already-covered bytes with no repeated physical credit.

Complete locked-PE decoding reconciles all nine bodies, every direct branch and
all returns. The real-owner host fixture checks dirty construction and outer
guards; zero/one/seven/thirty-one element arrays; external image survival across
array deletion; pointer publication and actual File getter use; 42 identity
bit-pattern combinations; and 640 sprite writes over five signed valid windows,
disjoint/self aliases and 64 integer-lattice inputs. An independent oracle uses
unscaled integer dimensions and power-of-two coordinate scaling. Full descriptor
and File images verify untouched lanes, source values, quiet-NaN payloads and
neighboring slots. Tests do not supply replacement descriptor/allocator layouts.

The first fixture compile rejects a typed raw memset under strict warnings;
explicit byte filling of the trivially copyable test storage resolves it.
A second run identifies the missing maintained getter TU; linking actual
AnimationOperands.cpp resolves it without a test replacement. Failed logs and
original compiler probes remain private evidence.

All 163 original object/receipt pairs are verified before editing. Captured
includes select 23 affected objects; each builds once and all 106 prior affected
units remain strict exact. The other 140 objects retain immutable receipts.
Six original complete literal payloads and fresh roles identify six generated
label changes without solving compared fields. All 278 source/probe paths remain
present. All 80 public CI tests pass in 302.972 seconds. The private real-owner
ASan/UBSan fixture passes in 8.279 seconds, including the descriptor checks and
existing nonreturning-path assertion. Frozen source and sanitizer input hashes
remain unchanged.

Retirement removes 52 replaced object/receipt products totaling 1,879,665 bytes.
The 683,817-byte lossless archive preserves 26 original input closures and their
immutable receipts. All 163 current pairs are protected before deletion; the
complete 868-unit existing-object replay remains strict exact afterward, with
all 326 product hashes and 278 source hashes unchanged and zero compiler calls.
The final audit verifies archive contents, retained headers, test inputs and the
source-absent clear boundary. Private proofs are indexed in [the handoff](RE_HANDOFF.md).

The graph contains 868 units / 163 objects / 166,363 disjoint comparison bytes,
with 876 source mappings and eight mapped whole nonexact functions. Reviewed
origins are 172 authored and 40 excluded, with 6,716 pending. Authored exact
coverage is 167 functions / 46,032 bytes; the source-absent authored File::clear
remains in the denominator. These are not whole-game completion percentages.

## Preserved ownership uncertainties

The Renderer +6000DFC..+6000DFF interval remains unclassified. Existing complete
constructor, destructor and allocation evidence does not identify a member or
prove padding. No maintained Renderer declaration is introduced.

CORE135 additionally checks 35,796 listed consumer instructions over
`00410000..0042FFFF` for direct +6000DFC..+6000DFF operands and finds no matches.
An attempted whole-text operand query exceeds the wrapper's bounded-range limit
and is rejected; it supplies no evidence. The earlier core105 constructor export
is truncated at `0044848F`; the retained overlapping core114 tail supplies the
remaining complete constructor coverage. These navigation observations do not
classify the interval or exclude computed accesses.

Bounded native operand navigation over `0044A700..0044F14F` inspects 5,425 listed
instructions and finds three +6C matches, all in File clearing. This does not
prove the absence of computed/external writes or establish an allocation
producer. The maintained opaque +6C word is not promoted to an owned pointer.
File::clear remains unimplemented, source-absent and nonexact. Loaded resources,
mutable ANM packet lifetime, whole VM, Renderer and native startup/runtime remain
open. Private core133 native listings, complete primary/support results,
boundary/graph audits and SHA-bound original input archives preserve the evidence.
