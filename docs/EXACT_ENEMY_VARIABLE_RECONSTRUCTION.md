# Whole Enemy variable destinations and Controller data

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-072 closes six complete contributions on the actual Enemy, Context,
EnemyController and identifier owners. Independent original vtable `5703CC`
places integer/float reading and destination resolution in four separate slots.
These implementations use the maintained production layouts and natural C++.
Canonical replay includes every relocation, default path, compressed index,
jump-table pointer and compiler alignment byte.

| Complete contribution | Original entry | Body bytes | Comparison bytes |
| --- | --- | ---: | ---: |
| Enemy::integer_destination | 00498600 | 663 | 838 |
| Enemy::float_destination | 00498210 | 818 | 1,001 |
| EnemyController::selected | 00485660 | 43 | 43 |
| EnemyHandle::resolve | 004AAAC0 | 73 | 73 |
| EnemyData construction | 004A2FC0 | 148 | 148 |
| EnemyHandles array construction | 0049EBE0 | 75 | 80 |

The batch adds 1,820 body bytes and 2,183 disjoint comparison bytes. New source
origins remain pending; none adds confirmed authored credit. EnemyHandles is an
alias of the real `std::array<EnemyHandle,16>` rather than an additional wrapper.
Its implicit constructor contribution includes five natural trailing INT3 bytes.
EnemyHandle's allocation-free zero constructor folds with the existing physical
23-byte contribution at `425CC0`, without a second unit or duplicate coverage.
Original type/field names and complete enclosing Controller lifetime remain open.

## Independently observed storage and dispatch

The Controller constructor at `4A2E80` constructs Data at `+10` through `4A2FC0`.
Data owns the existing 48-byte EnemyCounters, five separate words, sixteen
four-byte handles at `+44`, a four-byte aggregate at `+84`, another word, the
actual Timer at `+8C` and two trailing words. The aggregate's semantic role and
original spelling remain unknown. Its native initialization is retained by the
plain EnemyDataWord value, without padding, inert locals or matching branches.
The observed Data stride is `A4`; Controller remains `134` on x86.

Native array construction passes stride 4, count 16 and child constructor
`425CC0` to the real compiler construction helper `40BC20`. The complete 29-byte
EH handler `567600` and 36-byte zero-state FuncInfo `5A91B8` independently replay,
including the native nonthrowing flag 5. Each handle constructor only writes its
four-byte zero identifier. The resulting allocation-free, nonthrowing contract
also reproduces natural array construction; a throwing child experiment emits a
different full contribution and is retained privately.

Controller selection adds `54` to the receiver, passes the unsigned slot to the
complete 34-byte checked array accessor `484980`, then invokes `4AAAC0` on the
returned element. The native check is `index < 16`, with the original CRT
out-of-range path `428C80` and message `invalid array<T, N> subscript`. Natural
`array::at`, rather than unchecked indexing, reproduces the complete child.
Its full 16-byte throw helper, including natural compiler alignment, is checked
as support without extra coverage. Existing declarations incorrectly named this
storage as animation handles. Its actual Enemy lookup now supplies the type.

Handle resolution starts with null, calls the actual cdecl player-0 Controller
lookup `478060`, repeats that lookup when non-null and calls whole-list lookup
`498A80` with the stored identifier. It preserves a stale identifier after a
failed lookup. The Controller's own player index does not redirect resolution.
The unresolved Session lookup and list-find bodies remain declared dependencies;
these six matches do not claim those implementations or process startup.

## Complete writable variable protocol

Integer resolution has nineteen writable selections plus null default. It
returns actual signed views of corresponding four-byte unsigned word storage,
retaining the existing producer declarations and modulo-32 representation.
Float resolution has twenty-four selections plus null default. It returns
pointers to real float subobjects, including the first two Movement positions.
Native position access delegates through the actual Motion member.

| Integer IDs | Actual destination |
| --- | --- |
| -9985 through -9982 | Enemy State's four integer counters |
| -9949 through -9947 | Controller Data words 38, 3C and 40 |
| -9943 through -9940 | Selected Enemy's four counters, otherwise self |
| -9926 through -9923 | Controller Data's four integer counters |
| -9895 through -9892 | Four process script words at 5C49D8 through 5C49E4 |

| Float IDs | Actual destination |
| --- | --- |
| -9995 through -9992 | Movement 0/1 position x/y |
| -9981 through -9978 | Enemy State's first four float counters |
| -9939 through -9936 | Selected Enemy's first four float counters, otherwise self |
| -9935 through -9932 | Enemy State's remaining four float counters |
| -9922 through -9915 | Controller Data's eight float counters |

The selected-or-self expressions deliberately retain two selection calls when
the first succeeds. Each successful selection itself performs two player-0
lookups. Missing/stale selections fall back to self; pointer resolution does
not substitute the reading functions' distinct null/default behavior.
Movement indexing retains the native unchecked vector protocol and requires the
selected record to exist. The four script words have an extern declaration;
original global initialization is still unimplemented.

The integer switch has twenty pointers at `498898` and 94 compressed indices at
`4988E8`; the float switch has twenty-five pointers at `498544` and 81 indices at
`4985A8`. Both complete bodies decode through their sole final RET4, with every
instruction represented in the attested Ghidra listing and no external direct
branch. Canonical generated labels bind to independently decoded original case
heads/tables; diagnostic solved relocations are not used as evidence.

## Whole reading and search work retained

The complete integer reader at `49ABC0` has 4,157 instruction bytes and a
127-entry table, totaling 4,668 comparison bytes before the next contribution.
The float reader at `4995D0` has 5,102 instruction bytes and its own 127-entry
table, totaling 5,612 bytes. Normal-flow audits preserve 112 and 107 distinct
case heads, respectively, all default paths and every original table slot.
There are 51 and 47 distinct direct dependencies. The integer function export
omits one otherwise unreferenced JMP; the locked full-body decode retains it.
These are navigation/boundary evidence, not partial source or exact acceptance.

Reading is not a shared tagged accessor: native integer and floating slots have
different available IDs, conversions, null policies, random calls, player/state
queries and defaults. Full production Player, Session and other game-owner
interfaces must be established before claiming either whole reader. The
existing 41 KB Enemy opcode dispatcher also remains unclosed.

A natural full list-find experiment retains real observer lifetime and cleanup,
but emits 241 bytes instead of native 251 after capturing the end once. The
remaining compiler auto-initialization call for the iterator is also observed in
earlier scheduler work. A shorter 235-byte experiment queried the end repeatedly
and is rejected. No artificial iterator constructor or redundant source clear
is introduced; all failed bodies and native evidence are retained privately.

## Verification and limits

The frozen graph strictly replays 540 units from 100 objects over 96,830
disjoint comparison bytes. Owned O2/UBSan checks extend the actual creation
fixture with real Data/handle construction and all four accepted variable/handle
members. They cover signed bit writes, float/Movement aliasing, untouched self
storage, repeated lookups, stale/null selection, slot 15, rejecting slot 16 and
UINT_MAX before lookup, all 19/24 writable selections and invalid signed IDs.
Session lookup, full list find and remaining VM/game methods are explicit test
boundaries; semantic checks do not establish their native implementations.
Existing movement and file-loading fixtures now use real Data/handle lifetimes.

Whole-game compilation/linkage/runtime, original globals/startup, Controller
construction/destruction and the two whole readers are separate open gates.

## Protected storage maintenance

Protected cleanup retires 12 completed probe object/receipt files /379,171 bytes.
Two inactive EXACT-071 successful snapshots are losslessly archived as .json.gz,
saving another 1,559,710 bytes. Original content/hash roundtrips and all 200
current canonical hashes are verified. This batch frees 1,938,881 bytes
(1.85 MiB); cumulative retirement is 2,500 files /1,001,401,012 bytes, with
5,230,954 archival savings recorded separately. Native/failed evidence and all
receipt-verified original private header snapshots are retained. All 44 public
tests pass; post-cleanup comparison uses existing objects without a cold rebuild.
Cleanup/configuration/registration writers are completed; never rerun them.
