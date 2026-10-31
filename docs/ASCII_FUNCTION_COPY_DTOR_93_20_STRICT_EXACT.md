# CORE/RECON-1036 — native 93B std::function copy and 20B destructor, whole strict exact

Target: immutable Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete original **578B** ASCII text render Boss at `0x0044B020`
(SHA-256 `fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617`)
physically calls two distinct generic `std::function<void()>` methods:

| Native original | Complete body | Actual physical parent E8 | Internal original roles |
| --- | ---: | --- | --- |
| `0x004140F0` copy constructor | **93B/29 i386** | `+0x1B6` | E8 `+0x29 -> 0x00413F80` default base and `+0x3C -> 0x00414B90` copy-reset; PE HIGHLOW `+0x06 -> 0x00567C8D` EH and `+0x13 -> 0x005B25C0` cookie |
| `0x00414400` destructor | **20B/10 i386** | `+0x220` | E8 `+0x0A -> 0x00414310` actual function-base destruction; no HIGHLOW |

The native physical bodies are independently SHA-attested:
`0x4140F0` `557c7cd46e973490cb1c19336e4988976baedac63924d7d6226fe4efa1c13bad`,
`0x414400` `9f2ba240a91fa75f8c7bf95b1de5f98309e802f6922cdf0b4c847d2fd1cffdbe`.
The read-only verifier
[`verify-ascii-function-copy-dtor-native.py`](../scripts/verify-ascii-function-copy-dtor-native.py)
proves entire native instruction bounds through their true `ret 4`/`ret`,
all three original E8 destinations, two PE HIGHLOW fields and the actual
calling positions in the SHA-pinned original 578B Boss. It does **not**
infer physical targets from a candidate COFF field.

The ordinary by-value `std::function<void()>` in
[`src/AsciiTextRender578.cpp`](../src/AsciiTextRender578.cpp)
naturally generates **both** full original implementations under pinned
MSVC 19.44 x86 C++20. They share one new canonical object and fresh
receipt; only those two independently exact function extents are
accepted, **not the enclosing nonexact 578B Boss**:

```text
ascii_function_copy_93: exact (93/93 bytes)
ascii_function_dtor_20: exact (20/20 bytes)
Exact replay: 2/2 units, 1 cold objects
```

These are **two new whole strict units /113 distinct original native
code bytes**; folded C++ standard-library source ownership is not
proven as authored game code. Both are recorded `origin=unknown/review`
and contribute **zero new credited game-authored heads/bytes**.
Their native original 578B caller currently compiles to a whole
578B/139 source candidate with **497/502 nonrelocated byte equality**
but has five real SSE register-operand differences plus an unresolved
compiler correction-table data symbol. It remains
[SOURCE-PRESENT, NONEXACT](ASCII_TEXT_RENDER578_NATIVE_FRONTIER.md),
as do the original 111B Card lambda and full 1,896B Card start.
No project-wide cold replay was run.

```sh
scripts/repo-python scripts/verify-ascii-function-copy-dtor-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AsciiTextRender578.cpp
```
