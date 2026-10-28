# CORE/EXACT-307 — complete 237-byte Player option handle-sweep boss and four original accessors

Comparison target: user-selected Japanese TH20 v1.00a Steamless, original
whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint adds **five distinct entire original function boundaries,
327 exact native bytes** and two natural C++20 source providers. None is a
prefix comparison, artificial NOP, private target patch, or manually generated
machine-code sequence.

| Whole function | Native address | Bytes | Original whole-interval SHA-256 |
| --- | --- | ---: | --- |
| `Player::clear_option_animations` | `0x004FF8F0` | **237** | `b96dc3fecae541d332a6ea92b29910a922d975c0a4c732540716e0210ed4d446` |
| `PlayerValues<PlayerOption,10>::at` | `0x004BA3E0` | **23** | `e32f32e045adbe4ca8112ee275c3f3802c1d0bf48180ae603f5ff08cff93ac0a` |
| `Player::fixed_position_ref` | `0x004FF690` | **19** | `eaaa44b371568bb471981422f871946528ea0785ccceeeb0f60c2800295ec79c` |
| `Player::set_clock_scale` | `0x004AB590` | **29** | `5fc193dbdcf5a363230ad39981f6db3aa493663a31bf01d928f9ab81d3d4316d` |
| `PlayerValues<IntPoint,33>::end` | `0x004FCE40` | **19** | `e040194ae1c51309628ca4c346730ae7412914822e242b95b4a0cc1d7f30c4d9` |

## Native proof: one complete 237-byte gameplay state method

The original at `0x004FF8F0..0x004FF9DC` consists of **72 original x86
instructions**, all now emitted byte-for-byte by `src/PlayerOptionClear.cpp`.
Fresh target-attested Ghidra and independent Capstone original-PE decoding
establish the entire entry, return, caller and callee graph.

The first step clears Player entity flag bit 1, preserving all other bits.
A signed increasing index loops over all ten actual `PlayerOption` records
at Player+`0x684`; for each record, the original invokes the 23-byte
`PlayerValues::at` index getter **separately** before passing each of its
two actual `AnimationHandle` members at +`0xDC` and +`0xE0` to the already
exact `cancel_animation_handle_mode2`. A second, separate signed loop covers
all twelve records starting Player+`0x123C` with the same order. Finally it
sets the original Player+`0x20E8` word to zero. This is the complete routine;
there are no hidden early-exits or omitted arms.

The **eight original `REL32` call fields** were independently extracted
from original x86 `call` instructions and reconciled with native callees
at these offsets, in original order:

| Original field offsets | Independent original target | Meaning |
| --- | --- | --- |
| `+0x44`, `+0x67`, `+0xA5`, `+0xC9` | `0x004BA3E0` | typed `PlayerValues<PlayerOption,N>::at` |
| `+0x50`, `+0x73`, `+0xB1`, `+0xD5` | `0x00486310` | exact mode-2 AnimationHandle interrupt |

All eight native call words, complete byte extent, all 205 non-relocated
bytes, local loop variables and return paths strictly replay. The original
uses one shared native 23-byte index body for `PlayerOption` arrays of
**different template sizes** (10 and 12): locked MSVC independently emits
both full 23-byte index instantiations with the same exact bytes. The two
original use sites resolve to the same native `0x004BA3E0`, so the ledger
credits **one physical original function only**, not 46 bytes or two
separate addresses. Whether the original linker used ICF or a shared
template instantiation remains an inferred linkage mechanism; byte identity,
source type, complete code and original branch destinations are observed.

## Player data accessors, real types and widths

`Player::fixed_position_ref` returns the real `IntPoint&` at Player+`0x620`,
not the existing three-float position at +`0x614`.
`Player::set_clock_scale(float)` writes the original 32-bit floating value
to the real Player+`0x223C` member. The separate `PlayerValues<IntPoint,33>::end`
returns one-past-end at +`0x108` from the start of the actual fixed-position
history array (33 elements x 8 bytes each). These are complete independent
native 19B/29B/19B whole functions and native call dependencies of the
**966-byte, still-open** Player initialization/reset boss `0x004FB450`.
Their source lives together in `src/PlayerAccessors.cpp`.

## Scoped compiler replay and preservation

Every new strict unit used the repository's locked MSVC x86 19.44.35211
profile `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`. All **five newly admitted original native bodies** exactly
replay, including the 237-byte boss, and the independently emitted
12-slot alias to the physical 23-byte index method matches without a
second match-unit credit.

Adding genuine method declarations to the shared `src/Player.hpp` affects
**16 previous canonical source providers** plus **2 new providers**,
identified from the **live compiler receipt include closures**. Exactly
**49/49 strict canonical units in 18 freshly built source objects** passed
in four reduced-priority, serialized batches. Their accepted sources include
previously exact 2,018B Bullet collision, 898B Bullet command-3, 661B Player
rotated hit/graze, 777B Player rectangle and 466B Player circle bosses.
Focused proof logs are `.analysis/core307-replay-batch{0,1,2,3}.log` and the
ignored receipt-derived input grouping `.analysis/core307-replay-groups.json`.

One **compiler-private** Player constructor diagnostic string symbol changed
`$SG82056` to `$SG82072` after the new Player template/member declarations;
its original `+0x2FC DIR32` relocation address and independently grounded
target **`0x00572BB8`** remain unchanged. Its entire parent constructor
remains strictly exact; only the private COFF symbol spelling in the
manifest changed. No other original relocation, target, source ABI or
canonical comparison range was relaxed, and no unfiltered whole-graph cold
replay was run.

The larger 966-byte Player reset/initialization boss at `0x004FB450`, the
1,404-byte Bullet command-11 source and the 273-byte single Bullet draw-group
routine remain separately **nonexact**. This checkpoint does not imply
whole-game linker or runtime closure.

## Later CORE/EXACT-314 status

The complete original 966-byte Player reset owner at `0x004FB450` is now
**strict native exact**, superseding the historical open-parent statements
above. See [the whole 966-byte proof](PLAYER_INITIAL_RESET_966_EXACT_RECONSTRUCTION.md).
The separately larger 1,518-byte option rebuild callee remains open.
