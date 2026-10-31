# CORE/RECON-1063 — original 294B text submit Boss now two compiler-generated NOPs from whole exact

Immutable original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete native `0x0044FFF0` is **294B/106 i386 instructions**,
SHA-256 `daf9779671bfb7d0dfa8918eaadbbe26c68a659255a569e7ded769d0b3144f53`.
Its original 578B glyph/text formatting parent calls it directly at
E8 `+0x202`. This real game-owned method receives a by-value
`std::function<void()>`, selects one of two semantic text-rendering
paths, and copies the resulting packed eight-byte EDX:EAX words into
the hidden 8B caller return buffer. The native method has **seven
physical original E8/two PE HIGHLOW** and a true `ret 0x58`.

## Correct original return ABI, not an extra source-copy buffer

The previous maintained
[`src/AsciiTextSubmit294.cpp`](../src/AsciiTextSubmit294.cpp)
correctly invoked both original 2,227B GDI text core calls but
stored each `uint64_t` in a union and then copied the pair into the
native result struct through **two intermediate local 8B values**.
This was a real compiler-lifetime mistake, not missing branch logic:
pinned MSVC 19.44 i386 C++20 generated **319B/112 instructions**,
seven E8/two DIR32. Source alternatives using `std::bit_cast`,
explicit `memcpy`, a separate local 64-bit shift, and alias-return
references introduced extra ordinary function calls, overlarge
EH scopes or a wrong result layout.

The revised maintained C++ source now constructs the **actual returned
`NativeTextDrawResult8`** separately in each true native branch,
and stores the original EDX:EAX-packed result directly into that
same native eight-byte object. The cast to `std::uint64_t*` expresses
the **specific pinned MSVC i386 native representation** of the
observed hidden return object; it is not claimed to be portable ISO
C++ strict-aliasing behavior. Crucially, the source has no extra
reference or `NativePackedTextResult` union local whose second
struct copy would change the original register/stack lifetime.
Both branches retain original game-specific color and special-mode
settings and independently destroy the copied 40B callback argument.

This produces a complete natural **292B/104-instruction** candidate,
with **seven E8/two DIR32** matching the original semantic callee
order. The ordinary C++ source has the same **104 native instruction
mnemonics and instruction sizes** after excluding exactly the two
extra original one-byte `NOP` instructions at native `+0x97` and
`+0xFF`. The original has three post-destructor NOP instructions
at `+0x97`, `+0xFF` and `+0x114`; the source naturally emits the
third and **omits the first two**. Because those bytes are absent,
subsequent native E8 offsets and short branch displacements shift
by exactly their cumulative difference; this does **not** constitute
all-294-byte equality. The first two actual E8 positions and original
EH/cookie data field positions already agree. No manual NOP, inline
assembly, inert/dead variable, target-code transplant or shortened
original target comparison is used to hide this compiler difference.

## Independent original proof and admission boundary

The updated read-only
[`verify-ascii-text-submit294-native.py`](../scripts/verify-ascii-text-submit294-native.py)
SHA-attests the full original 294B body and its native instruction
boundaries, all seven **original** E8 targets and two HIGHLOW fields,
`ret 0x58` and the complete original 578B caller E8. It separately
checks the new complete **292B/104** source object's seven E8 and
two data roles and aligns all 104 real decoded instructions with
the immutable original **only after explicitly listing the two
omitted native NOP offsets**. The verifier does not rewrite either
byte stream or award source credit for a hypothetical 294B result.

```text
Original physical Boss: 294B /106 i386; 7 E8/2 physical HIGHLOW
Maintained C++20 candidate: 292B /104 i386; 7 E8/2 DIR32
Precisely unmatched native instructions: NOP +0x97, NOP +0xFF
Whole original game-author source admission: NONEXACT /zero bytes
```

This corrects the earlier 319B historical hypothesis recorded in
[`ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md`](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md),
while preserving the meaningful native protocol and full extent.
The separately reconstructed 2,227B glyph text core is also
SOURCE-PRESENT/NONEXACT; its original 132B job ctor, 23B job dtor,
56B queue bridge, GDI canvas and other accepted physical children
retain their own strict receipts. Neither parent becomes exact by
transitive matching. No shared accepted source header or match unit
is changed here, so **no cold canonical replay** is necessary for
this unaccepted-only source checkpoint.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AsciiTextSubmit294.cpp build/core1063-probes/AsciiTextSubmit294.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-ascii-text-submit294-native.py \
  --candidate-object build/core1063-probes/AsciiTextSubmit294.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```
