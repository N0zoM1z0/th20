# EXACT-063: Enemy dispatcher temporary owners

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

Eleven complete functions add 1,384 instruction bytes and five alignment bytes.
The frozen-source graph strictly replays 453 units / 86 cold objects / 85,406
disjoint comparison bytes. New origins remain pending; authored 64 / 16,948
is unchanged. The whole 48C010 / 41,967-byte dispatcher remains pending.

| Native entry | Complete body | Maintained owner and operation |
| --- | ---: | --- |
| 0047BB90 | 255 + 5 alignment | ShotMetadata construction |
| 0048BB00 | 241 | ShotMetadata move assignment |
| 0047C450 | 23 | ShotMetadata destruction |
| 0047C130 | 180 | LaserType0Parameters construction |
| 0047C4B0 | 23 | LaserType0Parameters destruction |
| 0047C030 | 246 | LaserType1Parameters construction |
| 0047C490 | 23 | LaserType1Parameters destruction |
| 0048B650 | 198 | LaserType2Parameters construction |
| 0048B8B0 | 23 | LaserType2Parameters destruction |
| 0048B5B0 | 149 | LaserType3Parameters construction |
| 0048B890 | 23 | LaserType3Parameters destruction |

## Actual values and lifetime protocol

ShotMetadata occupies 0x4C bytes on x86. Its PMR vector at +4 owns the already
accepted 44-byte BulletCommand values, and construction creates two commands.
Individual float/word/short fields retain observed widths; the final byte
fields are char and bool. +4A/+4B are implicit ABI padding, not explicit source
fields. Default sounds are 21 and 38. Unresolved operand roles keep neutral
names. EnemyQueuedRecord now refers to this complete shared owner rather than
an incomplete type; the host fixture's former empty payload is removed.

The native cleanup thunks in the whole Enemy dispatcher select actual values
in opcodes600/702/703/713/711. Each temporary owns a PMR command vector; their
vector offsets are +4/+38/+60/+3C/+2C respectively. They reuse Vector3 and
BulletCommand rather than generic word transports. LaserType1Parameters starts
with growth speed8.0. LaserType3Parameters +30 is a float: the reference's u32
declaration emits the wrong initialization instruction.

LaserType2Parameters +28 is a four-byte flag value. Native value initialization
addresses the subobject and zeros the complete word; opcode711 sets bit0 by
ordinary word operations. A neutral one-word aggregate preserves both this
construction and observed storage. The scalar brace-initialized candidate has
26 nonrelocation differences and is rejected. Original aggregate/union spelling
and individual bit meanings remain unknown. Its +48 curve pointer is initialized
to null and receives no destructor cleanup; the curve record's own layout and
production lifetime remain outside this batch.

## Copy, move and exceptions

The first private hypothesis labeled 48BB00 as copy assignment because its
outer scalar transfer matches either defaulted operation. Independent review
of the complete 48BA60 child corrects that inference: the native157-byte PMR
vector operation compares allocators, moves elements for unequal resources,
or destroys old storage and takes the source contents for equal resources.
The copy-vector candidate is121 bytes and does not explain the target. The
accepted operation is an out-of-line defaulted move assignment. Normal default
copy construction/assignment remain available for shared-value cloning; their
own native entries are not claimed exact here.

Native handler5679A0 occupies29 bytes, including its two leading NOPs, and
selects the complete36-byte FuncInfo at5A91B8, flags5. This independently
establishes ShotMetadata's nonthrowing constructor, including allocation failure
termination while creating the two commands. Its five compiler alignment bytes
are compared; no target-sized prefix is accepted. The whole Enemy dispatcher
retains its separately observed flags1 synchronous EH contract.

Five complete standard-library contributions independently replay without new
coverage: command-vector construction4141C0/63, destruction47C320/20,
resize4862F0/32, move assignment48BA60/157 and cleanup484790/158. The full
handler and FuncInfo also replay without duplicate credit. Independently
exported address helpers, allocator access/equality, unequal-resource move,
pointer takeover, resource deallocation and native8.0 data establish anchors;
none is obtained by solving a compared relocation field.

## Validation and remaining work

Owned C++20/O2/UBSan tests cover two zeroed default commands, sound defaults,
implicit construction padding, independent copy storage and allocator selection,
equal-resource pointer transfer, unequal-resource transfer without allocator
propagation, reset from a temporary, all four laser command-vector lifetimes,
and allocation rejection reaching the nonthrowing boundary. Existing Enemy
state/movement tests now use and link the actual ShotMetadata. These are host
semantic checks; no native gameplay execution or whole-program link is claimed.

The complete queue accessors498B80/396 and498D10/305 are still pending. Native
observations establish list growth, indexed advance, copy-on-write versus
ensure-only ownership, and a two-pointer aggregate return. Natural std::pair
forwarding construction explains467CC0/55, but allocator materialization and
temporary/reference emission in the full accessors disagree. Private C++20/17
probes stay nonexact; no new facade, raw ownership transport, shortened body
or canonical relocation for them is admitted. Finish their true allocation/
shared-control/return protocol, then integrate all actual temporaries into the
whole dispatcher, including all primary/nested tables and EH contribution.

Raw evidence and full replay receipts remain ignored under .analysis/build.
Periodic retirement protects every current canonical object and receipt and
records removed paths/bytes privately. See RE_HANDOFF.md for the latest totals.
