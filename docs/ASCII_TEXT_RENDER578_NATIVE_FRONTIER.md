**CORE/RECON-1037 update:** The 111B Card text lambda calling this renderer is now [whole strict exact](CARD_TEXT_CALLBACK111_STRICT_EXACT.md); the 578B renderer still has five SSE operand bytes and an unverified correction-data symbol, so this original 578B function is still NONEXACT.

# CORE/RECON-1035 — whole 578-byte ASCII text rendering Boss, five SSE source-code bytes from native exactness

Locked target: TH20 Japanese Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original native `0x0044B020..0x0044B261` is a complete **578B /139-i386**
text formatting and renderer submission Boss. Its immutable original SHA-256
is `fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617`.
The complete native `0x00486E80` 111B Card text lambda calls it by a
physical E8 `+0x62`, not by an inferred decompiler symbol.

## Actual native owner ABI and source recovery

[`src/AsciiTextRender578.cpp`](../src/AsciiTextRender578.cpp) is a full
maintained natural C++ source for the Boss. The 8-byte result and
16-byte quartet of Animation+0x3A8/+0x3AC/+0x3B0/+0x3B4 words have their
own non-owning typed interface in
[`src/NativeAsciiTextDrawView.hpp`](../src/NativeAsciiTextDrawView.hpp).
The *outer* formatting method is a **variadic `__cdecl` C++ member**:
the native owner `this` is passed on the stack with its hidden 8-byte
return buffer. Its downstream original **294B** text submit method
`0x0044FFF0` is instead a normal `__thiscall` member (receiver in ECX),
ending with **`ret 0x58`**. A prior free-function approximation of that
submit path created false stack pushes and a wrong caller-cleanup sequence.
The native protocol is:

- Lock the real `process_locks.slot(9)` recursive mutex with `std::lock_guard`
  and preserve its EH/unwind ordering
- Select native per-font glyph-width data from the float table
  `0x0056C768`, format into the original 0x500-byte stack buffer via
  existing whole-exact 30B formatter at `0x00447940`, and resolve the
  genuine `Animation::sprite_data` at `0x00437CD0`
- Copy the four native Animation transform words into one 16B value
  declared **before the lock** to reproduce original frame allocation,
  set the actual Animation flag bit 0 of byte `+0x49A`, and read the
  native color/shadow bit from `+0x49C`
- Compute the glyph-based horizontal offset via `2.0f`/`1.0f` float
  constants and unsigned byte-string length conversion; resolve a real
  sprite texture with the native checked file/sprite lookup at `0x00445A00`
- Copy the real by-value 40B `std::function<void()>` via the original
  `0x004140F0` ctor and submit text through the 294B native method;
  release lock and function in their genuine exception-safe sequence

The original secure CRT wide formatter uses a count of `0x500` *wide
characters* yet the caller allocates `0x500` bytes and counts its result
with byte `_strlen`. These mixed-width details are directly observable
in machine code; **no bound, text-encoding safety, or runtime correctness
assumption** is made about unspecified inputs.

## Independent original E8 and PE HIGHLOW evidence

Read-only [`verify-ascii-text-render578-native.py`](../scripts/verify-ascii-text-render578-native.py)
SHA-pins all 578 original bytes, checks 139 decoded instructions through
actual `ret` and the five following `INT3` alignment bytes; all **11
physical original E8** offsets and their original destinations are checked:

| Native offset | Original destination / role |
| --- | --- |
| `+0x39`, `+0x45` | `0x0040C310` lock 9 and `0x0040B730` lock_guard acquire |
| `+0x7D`, `+0x92` | `0x00447940` formatter and `0x00437CD0` sprite lookup |
| `+0x12A`, `+0x19C` | `0x0054FE20` actual byte `strlen` and `0x00445A00` texture lookup |
| `+0x1B6`, `+0x202` | `0x004140F0` std::function copy and `0x0044FFF0` native text submit |
| `+0x211`, `+0x220`, `+0x239` | `0x0040B900` guard release, `0x00414400` function destruction, `0x005429EE` cookie check |

All **eight original PE HIGHLOW** fields are likewise checked:
`+0x06 -> 0x00568578` EH, `+0x18 -> 0x005B25C0` cookie,
`+0x35 -> 0x005C0240` lock registry, `+0x56 -> 0x0056C768` glyph table,
`+0x10F/+0x172 -> 0x0056C8D0` native float `2.0f`,
`+0x117 -> 0x0056C8CC` float `1.0f`,
`+0x14E -> 0x0056CDD0` unsigned length correction (two doubles
`0.0` and `4294967296.0`). The generated C++ object uses an
`__xmm@41f000...` symbol at `+0x14E`; the **physical site and value
are equal**, but the exact original data-symbol owner is unresolved,
so this diagnostic does **not** constitute a canonical relocation receipt.

## Full-length source diagnostic — NONEXACT

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits a whole **578B /139-instruction** candidate
with **all 19 native relocation field positions** (11 E8/8 DIR32).
The code scores **497/502 non-relocated identical bytes**. The five
remaining mismatches are actual SSE accumulator/register operand bytes
at `+0x16D`, `+0x171`, `+0x17F`, `+0x184`, and `+0x188`:

- Source uses `mulss xmm1,xmm0` rather than original `mulss xmm0,xmm1`
- The subsequent divide, sprite-scale subtract and float-to-int conversion
  operate on the other XMM register

All five differences concern a coherent original text-width computation.
Alternative ordinary C++ source local lifetimes, operand association and
reordered multiply were tested; they either changed the function size
or introduced genuine other opcode differences. No target opcode patch,
manual assembly, dead local, dummy write, shortened function extent or
unverified strict credit is used.

**Status: SOURCE-PRESENT, NONEXACT.** The original 111B Card lambda, 294B
text submit and 1,896B Card start Boss remain separate unfinished native
parents/callees. Game-authored exact count and `config/match-units.toml`
are **unchanged** by this checkpoint. This is an independently attested,
complete-source Boss frontier, **not a strict acceptance**. No full cold
replay is needed for a newly authored unaccepted source.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AsciiTextRender578.cpp build/core1035-probes/AsciiTextRender578.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-ascii-text-render578-native.py \
  --candidate-object build/core1035-probes/AsciiTextRender578.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1036 — exact native 93B/20B standard-function children

Both original `std::function<void()>` copy and destructor E8 callees
inside the 578B text render Boss now have [their own distinct complete
93/93B and 20/20B canonical exact units](ASCII_FUNCTION_COPY_DTOR_93_20_STRICT_EXACT.md).
Both are naturally emitted from the same maintained 578B C++ parent
translation unit; the original 578B text render remains NONEXACT
at five SSE register bytes and its unsigned correction data-symbol
ownership. No game-authored parent credit is inferred.

## CORE/RECON-1040 — native 294B text submit child source now maintained

The original E8 `+0x202` inside this native 578B Boss targets the actual
[294B/106-instruction text submit member](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md),
which now has complete two-path C++20 source, seven pinned original
callee roles and two physical PE HIGHLOW. The 294B child still compiles
319B/112 and remains NONEXACT, as does this 578B parent at five
SSE register bytes. No parent or child game exact credit follows.

## CORE/RECON-1041 — native standard-function base closure now exact

The original 93B std::function copy/20B destructor in this 578B Boss
have four separately exact [25B/71B/20B/30B function base children](ASCII_STD_FUNCTION_BASE_25_71_20_30_EXACT.md).
Their complete 146 physical bytes and original E8 graph are reproduced
naturally from this **same** C++ owner in a six-unit scoped replay.
The 578B parent still differs at five real SSE operand bytes and
retains NONEXACT status.

## CORE/RECON-1063 — native text submit 294B gap narrowed to two NOPs

The separate original 294B text submit child called by this 578B
text renderer at E8 `+0x202` now has a [292B/104-i386 source candidate](ASCII_TEXT_SUBMIT294_TWO_NOP_FRONTIER.md)
with the true direct packed EDX:EAX/8B return and all native
instruction mnemonics/sizes equal except two original post-dtor
NOPs. Both original 294B and original 578B parents remain NONEXACT;
no newly authored exact credit is inferred from the source gap.
