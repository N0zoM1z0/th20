# CORE/RECON-1040 — original 294B native text submission Boss, real two-path C++20 frontier

The target is the locked Japanese TH20 v1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0044FFF0..0x00450115` is a **whole 294B/106-i386** native
text submit method, SHA-256
`daf9779671bfb7d0dfa8918eaadbbe26c68a659255a569e7ded769d0b3144f53`.
It receives the borrowed Renderer owner in **ECX**, a hidden 8B return
buffer at stack `+8` and the `std::function<void()>` task by value,
ending with **`ret 0x58`**. Its whole-original **578B ASCII text render
Boss** at `0x0044B020` physically calls it via E8 `+0x202`.

## Real original branch and return-lifetime behavior

The original examines the `bit10` argument, branching on zero. Both
paths construct a fresh copy of the **same by-value std::function**,
call the independent still source-absent **2,227B text renderer core**
at `0x00415830`, preserve both result words and return them in the hidden
8B output. `bit10 == 0` passes the original color and a true `1`
into the core. The other branch suppresses color to zero and passes
a true `0`. Each branch independently destroys its temporary function;
a third destructor belongs to the native exception-state cleanup path.
The actual core returns an 8-byte value in EDX:EAX, not the hidden
out pointer, so the wrapper writes two 32-bit fields to the caller
result. No invented game index or input validity handling is added.

All **seven physical E8 call instructions** in the original are
independently established from the locked PE:

| Original offsets | Actual physical callee | Role |
| --- | --- | --- |
| `+0x41`, `+0xAB` | `0x004140F0` | two full-exact 93B `std::function` copies |
| `+0x6C`, `+0xD4` | `0x00415830` | both independent 2,227B native text-core paths |
| `+0x92`, `+0xFA`, `+0x10F` | `0x00414400` | three full-exact 20B `std::function` destructors |

The original DIR32 relocation fields `+0x06 -> 0x005686FD` (real EH
handler) and `+0x15 -> 0x005B25C0` (MSVC security cookie) are separately
PE-confirmed. Read-only
[`verify-ascii-text-submit294-native.py`](../scripts/verify-ascii-text-submit294-native.py)
SHA-pins and decodes the entire original, its actual `ret 0x58`, the
following genuine `INT3` alignment, all seven E8/two HIGHLOW and the
original 578B caller's physical E8.

## Source presence, compiler comparison, and open question

[`src/AsciiTextSubmit294.cpp`](../src/AsciiTextSubmit294.cpp) is a
single maintained natural C++20 source for the genuine two-branch
result protocol. It implements the existing borrowed
[`NativeTextSubmitOwner::submit_text_44fff0`](../src/NativeAsciiTextDrawView.hpp)
member, copies the actual by-value 40B `std::function` through the
native C++ runtime, invokes the two correct native core argument
variants, and preserves the packed eight-byte EDX:EAX result in a
union of a `std::uint64_t` and the real two-word return structure.
The complete original 2,227B core is **not** claimed implemented.

Pinned MSVC 19.44 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` compiles this meaningful source to a **319B/112-i386
candidate**, not the native 294B/106. It has **seven E8 in the exact
original semantic callee order** (copy/core/destroy repeated, then
exception-state destroy), and two data DIR32. Alternate trials
included ordinary 64-bit shifts, `std::bit_cast`, and `std::memcpy`
returns. Shift-based source emitted an extra `_aullshr` call and lost
a native cleanup call; `bit_cast` and `memcpy` introduced unobserved
library calls. The retained union value representation yields a closer
native callee graph without claiming that its still longer MSVC
aggregate-copy/exception-handling lowering is exact.

The native branch path, full original code extent and all physical
callee identities are attested. **Status: SOURCE-PRESENT, NONEXACT.**
The source contributes **zero credited game-authored exact heads/bytes**
while those 25 extra bytes/six instructions and the original return/EH
store lifetimes are unresolved. The original 578B parent similarly
remains NONEXACT at five independent SSE register bytes, and the
2,227B original core is source-absent. This native source has no
configured strict unit and does not change any prior canonical object
or shared data layout; **zero cold replay is required for this
unaccepted-only source**.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AsciiTextSubmit294.cpp build/core1040-probes/AsciiTextSubmit294.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-ascii-text-submit294-native.py \
  --candidate-object build/core1040-probes/AsciiTextSubmit294.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1042 — bitmap-format fallback beneath 2,227B core whole exact

The original 2,227B glyph text core called twice by this 294B submit
method now has an independently exact [104B/43-i386 glyph bitmap
format negotiation child](GLYPH_CANVAS_FORMAT104_STRICT_EXACT.md).
It retries original pixel formats 0x19/0x1A as 0x15 and 0x17 as 0x16,
with all three real E8 to the 681B surface initializer. This adds
104 authored native bytes while the 2,227B core and 294B wrapper
remain unaccepted.

## CORE/RECON-1043 — bitmap memory/DC/stride getters under core accepted

The separate original 2,227B text core (called twice here) and its
2,245B glyph mask/compositing Boss now have [three new whole-exact
20B game-specific glyph canvas getters](GLYPH_CANVAS_ACCESSORS_20_20_20_STRICT_EXACT.md).
Their actual HDC/pixels/stride offsets are confirmed by the locked
original original callers and share a 104B native-exact format-fallback
owner. They do not establish source/exact status for either large Boss
or this 294B submit wrapper.
