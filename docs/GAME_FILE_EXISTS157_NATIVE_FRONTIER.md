# CORE/RECON-1085 — original complete 157B native game filesystem-exists wrapper, 155B C++20 source frontier

Immutable TH20 Japanese v1.00a Steamless original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The previously unclassified game-owned `0x004107A0` is a complete
**157B/47-instruction i386** native file-existence query, original
whole-function SHA-256
`59d4263ec85f2e658ccf89ab882725dbd54578bc167d5affea7a61f43ba2830b`.
It acquires the original process-global `LockRegistry::slot(2)` guard,
constructs a local native `std::filesystem::path` from the caller's
path reference, asks the native 104B filesystem-exists query
`0x00410610`, destroys that temporary path, releases the guard, and
returns the genuine Boolean outcome. This is a game-specific
slot-2-serialized filesystem operation, not a generic `std::filesystem`
method renamed as gameplay code.

The complete original has **seven physical E8 and three HIGHLOW**:

| Original native E8 | Original target |
| --- | --- |
| `+0x2F` | `0x0040C310` game lock registry slot 2 |
| `+0x38` | `0x0040B730` native recursive mutex lock guard |
| `+0x4D` | `0x0040C720` **44B legacy path-copy constructor**, physical original next-argument format word **0** |
| `+0x5A` | `0x00410610` original complete **104B filesystem-exists backend** |
| `+0x6C` | `0x0040E6C0` native filesystem-path destructor |
| `+0x7B` | `0x0040B900` native guard destructor |
| `+0x94` | `0x005429EE` native cookie check |

The physical PE HIGHLOW at `+0x06` references actual native SEH
registration `0x00567A15`, `+0x15` references cookie `0x005B25C0`,
and `+0x2B` references actual process lock registry `0x005C0240`.
Both the complete original 44B legacy path constructor and 104B
filesystem backend have independently SHA-attested locked original
physical extents. The original path-copy constructor uses two
arguments and ends in `ret 8`.

## Typed full-source C++20 is close, but not yet whole exact

[`src/GameFileExists157.cpp`](../src/GameFileExists157.cpp)
maintains the real game-specific operation with a borrowed
`const std::filesystem::path&`, native slot-2 lock, an owned local
`std::filesystem::path filename(source)`, and actual
`std::filesystem::exists(filename)` followed by automatic path and
lock destruction. Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
emits a complete **155B/46 i386** method with **seven E8/three
DIR32**, not the original 157B/47. The entire instruction-stream
difference is confined to legacy path construction:

```text
Original +0x44: push 0
Original +0x46: lea eax,[ebp+8]
Original +0x49: push eax
Original +0x4A: lea ecx,[ebp-0x2C]
Original +0x4D: call legacy 44B path constructor

C++20 +0x44: mov eax,[ebp+8]
C++20 +0x47: push eax
C++20 +0x48: lea ecx,[ebp-0x2C]
C++20 +0x4B: call current STL path copy constructor
```

The original genuinely passes an additional format enum/zero
argument, not an arbitrary inactive `push 0` pad. Explicitly using
current C++20 standard `std::filesystem::path::auto_format`,
`native_format`, `generic_format`, or constructing from `path.c_str()`
was tested in isolated compiler probes and generated 162B–191B
paths with additional calls, not the original 157B method. The
155B source is therefore retained for its **real filesystem
semantics**, with original C++/compiler ownership explicitly
unresolved. There is no fake `_Path` constructor or altered original
target to force acceptance.

[`verify-game-file-exists157-native.py`](../scripts/verify-game-file-exists157-native.py)
SHA-pins the **whole original 157B/47-i386** function, every
native E8/HIGHLOW original destination, the actual legacy 44B
constructor and original 104B filesystem backend, then checks the
complete **155B/46-i386** modern C++20 code and its authentic source
call counts. It checks the exact two-byte/one-instruction native
copy-constructor ABI difference without creating a 157B canonical
match. **Status: SOURCE-PRESENT, NONEXACT**; this game-owned head
receives **zero whole-exact byte credit**. The separately whole-exact
368B CP932 opener, 266B input reader, 493B one-shot writer and their
shared Win32 diagnostics remain unchanged. No full-project cold
replay is needed for this new unaccepted-only source owner.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/GameFileExists157.cpp build/core1085-probes/GameFileExists157.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-game-file-exists157-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
