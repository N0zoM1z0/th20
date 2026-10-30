# CORE/RECON-908 — rotated-corner 1,486B Boss and original 44B C++ dual-word helper bounded compiler probes

The immutable Japanese TH20 Steamless 1.00a target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This note records independently bounded, **NONEXACT** whole-parent source
probes, not a new strict unit or code-credit claim.

## Native 1,486B rotated four-corner Boss `0x0043EF20`

Original has **1,486B /372 i386**, 13 real E8, nine original HIGHLOW,
including the genuine single **NOP at `+0x41`** immediately after the
`Angle(float)` ctor and before `Angle::operator float`. The original
96B native two-axis quad-corner `.rdata` table remains independently exact,
but is not code credit. Maintained
[`src/AnimationCornerRotated1486.cpp`](../src/AnimationCornerRotated1486.cpp)
still compiles **1,485B /371 i386**, without this native NOP. Inserting a
byte only in a temporary in-memory diagnostic is **not** exact C++ source.

18 new **full-body used-local/lifetime probes** moved genuinely used `xs/ys`
arrays, forward-declared sine/cosine and offset/scale variables, tried
meaningful `Angle` references and copy/braced/direct construction. All
ordinary profiles emitted **1,485B /371 x86 /13 E8** and lacked the
original `+0x41` NOP; introducing a separate heading float gave 1,495B,
and used `Angle&` references gave 1,491B, both worse. Sources, candidate
COFFs, scores and compile logs are preserved under ignored
`.analysis/gptweb-corner1486-lifetimes/` and `build/gptweb-probe/`.

Nine additionally isolated changes to the actual shared `Angle.hpp`
(`noexcept` ctor, conversion and default ctor, defaulted destructor,
`class` vs `struct`, and combinations) all compiled this same **1,485B**
whole candidate without the NOP. The shared header was restored to its
**identical original SHA-256** at the end of the bounded experiment;
no accepted original unit or compiler receipt was changed. This strongly
limits the current compiler-lowering hypothesis, but does **not** justify
inserting an artificial NOP or declaring the Boss whole exact.

## Original C++ 44B /18-i386 dual-word helper `0x0045F310`

The new independent, **original-PE-only**
[`scripts/verify-cxx-pair44-native.py`](../scripts/verify-cxx-pair44-native.py)
authenticates its entire original 44B extent and final `ret 8`, the one
real E8 instruction at `+0x0B → 0x0040B280`, and **zero** PE HIGHLOW fields.
It also checks **five original physical E8 callers** individually:

| Original physical E8 site | Original head invoked |
| --- | --- |
| `0x0045EE7F` | `0x0045F310` |
| `0x0046B887` | `0x0045F310` |
| `0x0046BAA9` | `0x0045F310` |
| `0x00481129` | `0x0045F310` |
| `0x00483BDC` | `0x0045F310` |

The native method receives two 32-bit constructor arguments, calls an
8B folded address/move/forward helper for the first value and writes two
four-byte fields, returning the receiver. Its *actual source type names*
are still unproven. Natural C++17 candidate scalar constructors produce
**44B/18 x86**, but only **35/40 nonrelocation bytes** match: the native
loads the forwarded value into ECX and `this` into EDX, while MSVC's
candidate allocates those registers in the reverse order. Twelve real
integer/pointer/const/volatile type probes leave this five-byte
register-order difference unchanged. Ordinary `std::pair` forwarding
constructors instead generate **55B** and are not suitable exact owners.

Private full-body probes and their complete COFF objects are in
`.analysis/gptweb-pair44-types/`, `.analysis/gptweb-pair44-stdlib/`,
`.analysis/gptweb-pair44/`, and `build/gptweb-probe/Pair44_*.obj`.
No native function source identity, matching unit or authored credit is
asserted. The original five physical callers and complete helper are
now independently auditable without relying on Ghidra's nominal `move<>`
label, and new variants must improve **the whole method and relocation
roles**, not a selected matching prefix.
