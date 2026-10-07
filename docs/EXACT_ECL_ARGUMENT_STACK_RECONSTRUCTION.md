# Whole ECL argument and tagged stack protocol

EXACT-070 closes fifteen whole native contributions, 2,886 bytes, on the locked
Japanese v1.00a Steamless executable. EclArguments.cpp supplies the real current
instruction lookup and eleven separate parameter/destination members on the
existing 72-byte EclRuntime. ScriptStackCopy.cpp supplies the actual generic
copy protocol on the existing 24-byte PMR ScriptStack. No receiver facade,
reference adapter, assembly, copied byte array or matching branch is introduced.

| Maintained member | Native entry | Complete bytes |
| --- | --- | ---: |
| EclRuntime::current | 005403D0 | 80 |
| integer_argument | 0053ED50 | 209 |
| float_argument | 0053E970 | 287 |
| consuming_integer | 0053EEE0 | 197 |
| consuming_float | 0053EB70 | 261 |
| integer_argument_value | 0053EE30 | 163 |
| float_argument_value | 0053EA90 | 212 |
| consuming_integer_value | 0053EFB0 | 158 |
| consuming_float_value | 0053EC80 | 196 |
| integer_destination | 0053E850 | 136 |
| float_destination | 0053E720 | 148 |
| float_destination_at | 0053E7C0 | 140 |
| ScriptStack::push | 0053F260 | 265 |
| ScriptStack::pop | 0053F0B0 | 242 |
| ScriptStack::peek | 00540450 | 192 |

The eleven resolvers are direct dependencies of the accepted whole ECL tick
and invocation bodies and the still-open 41 KB Enemy opcode root. This batch
closes their actual protocols together rather than crediting selected branches
inside those roots. Existing authored coverage remains 64 functions / 16,948
bytes: these fifteen new source origins remain unknown.

## Native observations

Current instruction lookup checks offset and subroutine against -1, in that
order. Either sentinel returns null. Otherwise it reads the actual runtime
manager at +28 and manager loader at +58, passing subroutine and byte offset to
the real resource instruction member at 0053E8E0. That complete 54-byte resource
member is an independently observed dependency and remains nonexact.

Each ordinary resolver calls current() once. The frame-specific float target
takes an explicit instruction and base and makes no current() call. The
16-bit references mask distinguishes literal words from references. Literal
reads preserve their representations, and literal destination requests return
null. The real instruction header is 16 bytes and payload words are four bytes.
Separate consuming/nonconsuming and supplied-value entries retain the observed
thiscall, RET4/RET8/RET12 and x87 float return conventions.

Referenced nonnegative integer values address local stack bytes. Float values
first truncate to an integer byte offset. Local addresses use the real frame
base; the explicit-frame destination calls absolute() with the supplied base.
Destination requests dispatch every negative value to the actual manager slots,
including the negative range that read-value members interpret as stack values.
The six-slot manager interface keeps integer read/destination at +8/+C and
float read/destination at +10/+14. No variable-number mapping is invented here.

Read references from -100 through -1 select the tagged stack protocol.
Nonconsuming integer references use a modulo-32 left shift by three; float
references multiply by **positive 8.0f** and truncate. Both therefore address
behind SP for integral negative references. Fractional float references retain
native truncation and subsequent signed division by four. Consuming variants
pop the top four-byte value and its tag irrespective of reference magnitude.
Other negative values dispatch to the manager. Float values between -1 and
zero also dispatch, after truncation. Negative zero selects local byte zero.

Push grows vector size, not just capacity, when fewer than
(SP + byte_count + 4) / 4 words exist. It reserves the extra word even for an
untagged request. A nonzero signed char tag is widened into a whole word before
copying data. The four-byte path assigns a word; all other lengths use memcpy.
SP advances after the copy. No capacity, sign, alignment or bounds checks are
invented beyond the observed vector growth.

Pop decrements SP by the supplied byte count before reading. It assigns one
word for four-byte copies and otherwise uses memcpy. A requested nonzero tag
also decrements SP by four and examines the stored tag. Stored f/requested i
truncates numerically; stored i/requested f converts numerically. Matching and
unknown tags preserve raw bytes. Conversion operates on the first output word,
including for larger copies. Pop leaves vector size/capacity intact.

Peek always copies four bytes. A requested tag adds four to its relative byte
offset; the preceding word supplies the type tag. It performs the same numeric
conversions as pop and leaves SP and storage unchanged. Neither pop nor peek
calls checked absolute()/local() access or grows the vector.

## Compiler and independent relocation evidence

All fifteen use the existing candidate MSVC x86 19.44.35211 profile:
Od, Ob0, GS, Gy, Zl, SSE2, fp:precise, sdl and EHsc, with C++20. The full
contributions include normally unreachable compiler jumps between returning
if/else branches; Ghidra's existing function/range listing omits some of these
instructions. Read-only decoding of the locked complete PE spans confirms their
presence. Natural if/else-if/else source reproduces them without inserting
explicit dead statements or shortening boundaries.

Direct virtual member expressions reproduce the native repeated manager loads.
The earlier private receiver-reference hypothesis suppressed one load. The
combined receiver and branch differences accounted for the previously reported
nine-byte discrepancy; it was not evidence for a different virtual interface.

Private whole-body float experiments distinguish direct read expressions from
an additionally parenthesized floating return expression. On this compiler and
profile the latter produces an extra SSE load/spill before the x87 return,
adding ten bytes. Maintained direct const float payload access reproduces the
whole native return. This is an emission observation and a natural source
inference, not a claim about the original macro spelling or global flags.

Full native callees and earlier independently closed owner members bind current,
local, absolute, instruction, pop, peek, vector access/size/resize, memcpy and
security-cookie support. Native constant data independently confirms zero,
-1.0f, -100.0f and positive 8.0f at 0056E0E8, 0056E0F4, 005732DC and
0056D7BC. The earlier private -8.0f hypothesis was structurally identical when
relocation fields were masked, but failed this constant identity check. It is
rejected; only the corrected full replay earns credit.

Three complete standard vector supports also replay independently: unchecked
word indexing at 0053B530/35, size at 0053F750/36 and value-initializing resize
at 0053F370/32. The resize wrapper's actual child at 0053AAE0 has the observed
shrink/grow/capacity and value-initialization protocol. These support comparisons
add no duplicate unit or authored coverage and do not close the entire STL.

## Owned checks and limits

The O2/UBSan fixture runs all fifteen production bodies, actual stack access,
PMR lifetime and base loader lifetime. It bounds the unresolved original runtime
and manager constructors, resource instruction lookup and game variable dispatch
explicitly. All sixteen mask positions cover literal representation, NaN payload
preservation on unmasked reads, negative zero, fractional local offsets, actual
destination addresses, supplied values, -1/-100 stack boundaries, consuming
versus nonconsuming behavior and real virtual-slot dispatch. Stack checks cover
0..32 byte copies, untouched output tails, signed high-bit tags, i/f conversion,
nonmutation on peek, saved-frame restoration, allocation failure before pointer
mutation and resource release. Existing owned whole tick and invocation checks
now use production push/pop instead of four-byte-only stack fixtures.

The valid portable domain requires enough input/output/vector storage and
representable signed byte arithmetic, valid payload/mask indices and finite
representable values whenever float-to-int conversion occurs. Native CVTTSS2SI
has an observed hardware result for exceptional inputs; C++ out-of-range/NaN
casts are not given a fabricated portable meaning. Raw literal representations
are checked independently. No nullable-instruction handling is added to readers:
their valid calls require an active instruction.

Full runtime/manager construction, resource append/include and production
variable owners, process startup, complete Enemy root and whole-game linkage/
runtime remain open. ECL root, loading, calls, library support and source origin
are separate claims; this batch does not imply a playable reconstructed game.

## Checkpoint validation and artifact retirement

The frozen-source graph cold-builds all 97 objects once and strictly replays
524/524 units over 93,941 disjoint comparison bytes. Canonical audit replays all
fifteen new bodies and three complete library supports. All 43 public checks
pass, including the new actual-protocol fixture and whole tick/call integration.
Target, tracking, reference-review, progress and public-tree gates pass. All
6,945 reference reviews remain terminal; eighteen new complete associations
bring absorbed-exact to 157. Historical swapped adapter labels are retained in
review notes, while actual native entries govern these associations.

Protected retirement removes 28 completed probe object/receipt files,
1,096,445 bytes. All 194 current canonical hashes remain unchanged; full strict
existing-object replay checks the graph afterward without another cold build.
Cumulative retirement is 2,468 files / 1,000,370,970 bytes. Private evidence,
failed source/diagnostics, reference, target and installed tools are retained.
