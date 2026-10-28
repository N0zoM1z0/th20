# CORE/EXACT-472 — exact original InputInf destructor and deleting wrapper

Original immutable comparison target is Japanese TH20 v1.00a Steamless PE,
whole file SHA256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The entire game-owned `InputInf::~InputInf` at `0x0041FD70`
is **120/120 original bytes / 35/35 instructions** strict exact.
The original compiler physically emits another five genuine `CC`
alignment bytes, so its entire canonical contribution
`size=120, compare_size=125` compares **125/125 original bytes**.
Original body SHA256:
`7785d9c8ceff5946e953b0b5cd1d21711d676a8263603ce90e19aea15e7584ea`.

The separate compiler-generated virtual scalar deleting destructor
at `0x0041FE10` is **49/49 original bytes / 18 instructions**
strict exact; original SHA256:
`b1ebe60b0c1e959d904d9ebf8995cf18fb4a972776cf54c50529aa67611b2e63`.
This second complete native function is **compiler glue, not an
additional authored gameplay body**. It has its own strict native
canonical unit but no new game-authored-function/byte credit.
It is naturally emitted by the real virtual `~InputInf() override`
in the original class. It tests deletion flags, calls the true
120B dtor, and conditionally invokes native sized delete for the
actual 0x2EF8-byte manager, returning through `ret 4`.

## Authentic whole native game lifecycle

Original RTTI `.?AVInputInf@@` at `0x005B41F8` and vtable
`0x0056D4D0` independently establish this real game owner.
The 120B native destructor reinstalls that vtable, issues
the real `shutdown InputInf` diagnostic, removes the true
`TaskInfo+0x08` update callback through global
`FunctionChainController*` at `0x005B66D8`, invokes the
**separate 466-byte InputInf device/pad shutdown**
at `0x004202C0`, clears the real `InputInf*` global
`0x005B8898`, then destructs the underlying TaskInfo
base at `0x0041FDF0`. Its original EH registration,
return path and native security cookie remain complete.

**The 466B InputInf::shutdown callee remains NONEXACT**;
an exact caller does not imply its child or the 3,490B
input processor is complete.

## Independently original PE relocations

The original complete 120B function has four E8/REL32 and
six PE HIGHLOW/DIR32 relocations, at real native offsets:

| Native field | Type | Original PE destination |
| --- | --- | --- |
| `+0x06` | DIR32 | `0x00567600` EH descriptor |
| `+0x13` | DIR32 | `0x005B25C0` security cookie |
| `+0x2B` | DIR32 | `0x0056D4D0` true input vtable |
| `+0x30` | DIR32 | `0x0056D684` shutdown literal |
| `+0x35` | REL32 | `0x0040C6B0` diagnostic |
| `+0x45` | DIR32 | `0x005B66D8` global chain |
| `+0x4A` | REL32 | `0x004124B0` exact callback removal |
| `+0x52` | REL32 | `0x004202C0` still-open shutdown |
| `+0x58` | DIR32 | `0x005B8898` global InputInf |
| `+0x64` | REL32 | `0x0041FDF0` exact TaskInfo destructor |

The separately original 49B wrapper has two E8 targets:
`+0x0B -> 0x0041FD70` and `+0x21 -> 0x0054278D`
(sized original operator delete). Every field location,
type, physical original target, actual compiler COFF
symbol and addend was independently checked from the
immutable PE, without solving target destinations from
candidate output. Complete independent evidence and hashes:
`.analysis/core471-inputinf-dtor-original-pe-proof.json`.

The existing strict 261B InputInf constructor shares the
same translation unit. Adding this destructor changed only
its private MSVC diagnostic symbol name
`$SG50531` to `$SG78649` at original ctor `+0xDF`.
The original PE still targets `0x0056D4DC`
(the genuine initializer diagnostic string). Original
field offset/type and all unrelocated bytes remain
unchanged. The exact 120B destructor uses its distinct
`$SG78653` string at original `0x0056D684`.
No original target was changed.

## True changed-source closure and credit

The only existing shared header change is the authentic
`src/InputInf.hpp` virtual destructor and real, separate
`shutdown` declaration. The method is maintained in the
existing canonical `src/InputInfConstruction.cpp` owner
under its original MSVC x86 `/GS /sdl /EHsc` profile.
The compiler generates the deleting wrapper without
a fake handwritten implementation.

**Pre-edit locked compiler include receipts** for this
header selected exactly **two source providers and two
earlier whole strict units**. The two new physical native
units increase this to **4/4 strict units in exactly two
freshly cold-built objects**, including the still exact
261B constructor (266/266 aligned compare) and 26B
InputInf input-index reader.
Actual source-scoped replay evidence:
`.analysis/core472-inputinf-lifetime-scoped-replay.log`,
and pre-edit closure:
`.analysis/core468-inputinf-preedit-closure.json`.

**New game-authored exact credit: one 120-byte destructor.**
The 49B compiler deleting wrapper is separately source-exact
support without false gameplay authorship. The independently
original 466B shutdown and 3,490B input processor remain
open. No unfiltered whole-repository cold replay was run.
