# CORE/EXACT-410 — five entire original IntPoint gameplay coordinate operations

The approved immutable target is Japanese TH20 v1.00a Steamless,
whole SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Five **physically different, complete native game-authored functions**
using the real 8-byte `IntPoint` x/y coordinate object are now
**strict original byte-exact**, maintained in the existing typeful
`src/Rectangle.cpp` source object and `src/Rectangle.hpp` interface.
They were discovered while examining the separate **1,081-byte /
325-instruction Player per-option frame boss** at `0x004FA860`,
which calls all five original physical addresses.

| Whole original C++ operation | Native address | Complete native body | Original x86 instructions | Original PE E8/HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `operator!=(const IntPoint&,int)` | `0x004F5700` | **49/49 B** | 18 | 0/0 |
| `IntPoint::operator*(int) const` | `0x004F57C0` | **45/45 B** | 18 | 1/0 |
| `IntPoint::operator-(const IntPoint&) const` | `0x004F5890` | **48/48 B** | 20 | 1/0 |
| `IntPoint::operator/(int) const` | `0x004F5920` | **45/45 B** | 20 | 1/0 |
| `IntPoint::operator+=(const IntPoint&)` | `0x004F70F0` | **65/65 B** | 26 | 0/0 |

Total **252 uniquely original bytes** and **102 distinct original
instruction heads**; no function in this group overlaps another
or any previously accepted native function. Their complete original
function SHA-256 values, in table order, are:

- `1e2239b17408bdd7483d5adf5785fb32a49e4e9cd35af9d0bc9c6d50e6d2c26d`
- `17780b4e76dfdc4807f779bfaa6f8f70dcc1a475895bf24a353ca3f0b37d031b`
- `c49c599ecd1ec058ae7e38f3d759e2273e62c0b9bcf65dd3055450564cde056b`
- `5eecf8652ed6b023df420206a5da41138b21e5dda0add7721498da0b2ced02e0`
- `e7bb04002cd1330cb844cb06163723e369734dfb51ad516d75e04849a10d9226`

## Independently original gameplay and machine ABIs

The original full 1,081-byte `Player` option-frame method at
`0x004FA860` is called twice per option in the 3,111-byte
`Player` frame-update boss at `0x004F9C30`. Its actual
coordinate path uses these exact operations to test a two-lane
nonzero displacement, subtract the saved previous position,
multiply the result by a frame scalar, divide the two components
with **original x86 signed `idiv`**, and add back the
smoothed displacement. The whole 1,081-byte caller is still
**not** strict exact and receives **zero** native credit here.

`IntPoint::operator-` and `operator*` preserve the original
wraparound low 32 bits of integer arithmetic, then create
a real returned `IntPoint` through its actual already exact
33-byte native `IntPoint(int,int)` constructor at
`0x0040DE00`. Signed division uses actual signed operands,
including native integer division failure behavior, rather
than an unsupported unsigned division optimization.

A particularly important original ABI distinction:
`IntPoint::operator+=(const IntPoint&)`, at `0x004F70F0`,
mutates **both** receiver coordinates and returns a **fresh
whole eight-byte coordinate value through the native MSVC i386
hidden aggregate-result pointer**. It does **not** return
`IntPoint&` as a conventional C++ arithmetic operator often
would. This original return-type distinction is independently
established by the entire 65-byte native caller convention and
complete existing C++20 compiler output, and is retained as
genuine source semantics.

`operator!=(const IntPoint&,int)` is a genuine free
`__cdecl` predicate testing both components against the same
signed scalar. All four other methods have the original
`__thiscall` member receiver and proper hidden aggregate
return where required. The actual game-specific two-coordinate
type, its existing `operator+`, and all previously exact
constructors retain their original physical source owners.

## Whole immutable PE reference audit and exactness criteria

Before canonical admission, the entire original PE was reread
and each complete 49/45/48/45/65-byte interval fully decoded.
The three constructor-using functions have exactly one original
`E8/REL32` field each:

| Whole function | Original field | Independent original target |
| --- | --- | --- |
| 45B coordinate multiplication | `+0x20` | `0x0040DE00` |
| 48B subtraction | `+0x23` | `0x0040DE00` |
| 45B division | `+0x20` | `0x0040DE00` |

No other original E8 calls or PE `.reloc` HIGHLOW
absolute fields exist in these five whole functions.
All **three native relocation positions/types/targets**
agree with the actual COFF symbols and their zero addends.
The two remaining methods have no external relocated bytes.
The complete original native bodies match **252/252
bytes** under strict canonical relocation replay,
not just ordered opcode names.

The original immutable target hashes, full original native
function code hashes and all PE fields are independently
recorded in
`.analysis/core410-intpoint-native-original-refs.json`.
The pinned original source-owner MSVC 19.44.35211 i386
profile remains
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy
/Zl /arch:SSE2 /fp:precise`. None of the five
functions uses copied machine code, NOP padding, fake
locals, assembly or a shortened original byte range.

## Actual shared-header receipt closure, strictly bounded cold replay

The only changed maintained code is the real `IntPoint`
method declarations in `src/Rectangle.hpp` and natural
implementations in `src/Rectangle.cpp`. The class remains
8 bytes; no member layout, previous operator signature,
compiler profile or other source provider is changed.

Before editing, the **real previous locked compiler receipts**
for `src/Rectangle.hpp` were captured. Their include closure
selects exactly **31 prior original source providers, 100 old
strict units**. The five new physically distinct native methods
join the already present `src/Rectangle.cpp` canonical
source object `build/core141-canonical/Rectangle.obj`,
giving **105/105 actual impacted strict native units
across 31 freshly cold-built objects**. Their complete
serial low-priority replay batches have **5 + 37 + 12
+ 6 + 11 + 30 + 4** units. In particular, native
966B Player initial reset, 1,518B Player option-animation
rebuild, 2,018B Bullet collision, and existing
48B `IntPoint::operator+` remain exact. No unfiltered
whole-repository cold replay was run.

The compiler's private `$SG` IDs renumbered in one
Player constructor, a Dialogue constructor (four fields),
and an Ascii constructor. All **six** were reconciled
**only** after checking the unchanged independent original
PE constant target, relocation field position and type,
actual C++ compiler receipt and complete native
nonrelocation bytes, then were reaccepted by the unchanged
strict native comparator. Private original-target audit:
`.analysis/core410-reconciled-private-symbols.json`.
Full frozen prior header include closure:
`.analysis/core410-intpoint-preedit-closure.json`;
actual replay groups and complete strict logs:
`.analysis/core410-intpoint-replay-groups.json`,
`.analysis/core410-intpoint-replay-batch0.log` through
`batch6.log`.

The complete 1,081-byte Player option-frame caller and the
separate 3,111-byte Player frame boss remain **independent
unfinished source reconstruction**, not automatically
credited from these newly exact five real coordinate
dependencies. Whole-game linkage and runtime behavior
are also separate unproven tasks.
