# CORE/EXACT-463 — complete original InputButtonState and InputDevice constructors, 442 native bytes

Immutable comparison target: Japanese TH20 v1.00a Steamless,
`resources/th20.exe`, full original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two complete and physically distinct game-owned input constructor
functions from the real original `InputInf` initialization chain
are now strict whole native exact C++ in the existing
`src/InputState.cpp` and `src/InputState.hpp`:

| Whole original constructor | Original entry | Complete strict native bytes | Complete x86 instructions | Native PE E8 / HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `InputButtonState::InputButtonState()` | `0x0041F9B0` | **340/340** | **81** | **6 / 0** |
| `InputDevice::InputDevice()` | `0x0041FCB0` | **102/102** | **28** | **2 / 0** |

These two entirely original nonoverlapping source-owned functions
total **442 newly accepted original bytes and 109 entire i386 instructions**.
Their immutable original SHA-256 interval values respectively are
`a5259f09c63056522280128720e61ee73201ec02e87f69978013882c0a7d4044`
and
`e0ec1be3d141beba7975ee6edb2cd6870aaee72ce37960c88f2d5a59163a44a7`.

## Complete native InputButtonState state construction

The genuine original `InputButtonState` is **0x2C0 bytes**,
with six initial 32-bit button state words, five separate
`std::array<uint32_t,32>` histories at offsets
`+0x18`, `+0x98`, `+0x118`, `+0x198` and
`+0x218`, followed by ten native replay and held-count
state words from `+0x298` through `+0x2BC`.
The whole original constructor initializes all six first
words to zero, value-initializes each of the five true
128-byte arrays with **five separate native CRT memset
calls**, sets all ten trailing state words to zero,
and performs one final **real native four-byte memset
on the `current` state word at +0x00**.

That final write was independently observed in the immutable
original machine code, even though the first field was
already initialized earlier. It is not a fabricated
stack-local or hand-generated instruction. Natural C++20
source with real member initializers and
`std::memset(&current, 0, sizeof current)` in the
actual constructor body emits the complete original
**340-byte/81-instruction** function; an experiment
omitting this true final operation emitted only
324 bytes, and a direct redundant assignment
`current=0` emitted 333 bytes. A source using manual
per-array `memset` instead of true array value-initialization
generated the right length but had wrong native register
selection, so it was **not** accepted.

The six complete original `E8/REL32` fields
at `+0x51`, `+0x6A`, `+0x83`, `+0x9B`,
`+0xB4` and `+0x146` independently
target the actual original CRT `_memset`
at **`0x00544760`**. The original PE has
no HIGHLOW field in this whole body.

## Whole native InputDevice construction and genuine parent ownership

The real `InputDevice` is **0x3D4 bytes**:
four 32-bit header fields at offsets +0x00..+0x0C;
the genuine nested `InputButtonState` at +0x10;
256 live raw input bytes beginning at +0x2D0;
and one retained 32-bit word at +0x3D0.
The original 102B default constructor
initializes each of the four header fields to zero,
constructs the actual whole-exact 340B state object,
zeros the real 256-byte raw storage and clears
the retained tail word before returning its true receiver.

Its original E8 call at **`+0x35`** targets the whole
`InputButtonState` constructor at `0x0041F9B0`,
and at **`+0x4B`** calls the original CRT
`_memset` at `0x00544760`. The exact C++
member-initializer list with real nested
`buttons()` and `raw{}` generates all
**102 bytes/28 instructions** naturally,
including the genuine `__thiscall` ABI.
There is no padded fake owner or hidden
shorter-than-original comparison.

The separately actual **261B original InputInf constructor**
at `0x0041F8A0` uses the original MSVC vector constructor
helper to build exactly **12** of these
0x3D4-byte `InputDevice` records at
`InputInf+0x20`, immediately followed by
two device status scalars, input routing
arrays, the two actual InputButtonState view
pointers at +0x2E30 and the original four
0x30-byte InputBindings records at +0x2E38.
The true manager class identity `InputInf`
is proven by original RTTI
`.?AVInputInf@@` at `0x005B41F8`.
See [the original InputInf constructor and RTTI layout proof](INPUT_INF_RTTI_OWNER_LAYOUT_CORRECTION.md).
The **whole 261B enclosing manager constructor
still remains separately NONEXACT**, and this
checkpoint gives it no inherited exact credit.

## Independent original PE and original compiler COFF proof

Original 340B and 102B machine-code intervals were fully decoded
independently before recording matching units. All
**eight original direct E8 relocation offsets,
types and physical target addresses** match the
fresh locked MSVC COFF compiler symbols.
There are **no original PE HIGHLOW fields** in
these two whole native constructor bodies.
The unchanged original strict comparator accepts
**316/316 nonrelocation + 24/24 relocated bytes**
for the 340B constructor, and
**94/94 nonrelocation + 8/8 relocated bytes**
for the 102B constructor. Their exact original
target SHA, entire code SHA, original x86 instruction
counts, all eight PE fields, COFF symbols/addends
and original child call targets are preserved in
`.analysis/core463-input-construct-native-proof.json`.

Pinned original source profile for the existing canonical
`src/InputState.cpp` object:
MSVC 19.44.35211 i386
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy
/Zl /arch:SSE2 /fp:precise /Gd`.
All 442 bytes come from ordinary typed C++ member initialization,
`std::array` value construction and genuine raw storage reset:
no hand-written assembly, target byte arrays, artificial
stack locals, inert branches, padded NOPs or fake signatures.

## Exact original input-header receipt closure

Only the real constructor declarations in `src/InputState.hpp`
and genuine whole method implementations in the **existing**
`src/InputState.cpp` canonical owner were modified.
The original `InputButtonState` and `InputDevice` sizes,
field offsets and the previously exact buttons update,
replay, device configuration and input lookup code
remain unchanged.

**Before changing the common input header**, the actual prior
compiler-receipt include graph identified exactly **two source
providers with thirteen old strict units**:
`src/InputState.cpp` and `src/InputInf.cpp`.
The two new complete original game constructors join
the **existing InputState source object**
`build/core141-canonical/InputState.obj`,
so the entire truly affected set is now
**15/15 whole strict native units in two freshly
cold-built source objects**. The original 26B
`InputInf::for_view` remains separately whole exact,
with no duplicated source or native byte credit.
The entire 1,081B Player option-frame boss remains
strict exact under its previously locked source profile.

Old real receipt source closure:
`.analysis/core463-input-ctor-preedit-scope.json`;
actual full low-priority scoped exact replay:
`.analysis/core463-input-construct-scoped-replay.log`.
No whole repository cold replay, new physical
array helper credit, complete game runtime linkage
or exactness of the still-open 261B InputInf owner
constructor is asserted.


## Subsequent CORE/EXACT-467 complete original InputInf manager constructor

**CURRENT STATUS:** the original 261-byte `InputInf::InputInf()`
at `0x0041F8A0`, previously open in this historical
checkpoint, is now **261/261 complete strict original
native exact** (72 i386 instruction heads, 4 independent
E8 call fields and 7 independent PE HIGHLOW fields).
The source's **real C-array construction** and
`noexcept` ABI naturally invoke the original
four-argument native vector constructor iterator,
without the two unobserved compiler EH cleanup
state writes. The entire source compiler contribution
of **266 bytes** including the **five actual
original PE trailing CC alignment bytes** is
**266/266 strictly exact**, while **only 261
native game-body bytes** are credited.
The actual original `InputInf.hpp` compiler
receipt include closure passed **2/2 strict units
in two cold sources**. All earlier exact 26B
input accessor, 340B ButtonState and 102B Device
constructors remain separately full exact and
are not recredited. Historical statements above
that the 261B manager ctor remains nonexact
are **superseded**. See
[the entire InputInf manager construction PE proof](INPUT_INF_CONSTRUCTOR_261_EXACT_RECONSTRUCTION.md).
