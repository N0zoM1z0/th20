# CORE/RECON-1050 — complete original 681B GDI glyph-surface creation Boss, whole strict exact

Original target: immutable Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned `0x00415120..0x004153C8` contains the whole
**681B/176-instruction** GDI glyph bitmap creation method, immutable
native SHA-256 `62554c335c22f75345ca164715188e77712c1e8348c199e3757843b193aa33d3`.
It is physically invoked three times by the independently exact 104B
format fallback at `0x004153D0`: E8 `+0x16`, `+0x3F`, `+0x59`.

## Complete source, native behavior and the corrected ABI hypothesis

The maintained [`src/GlyphCanvasCreate681.cpp`](../src/GlyphCanvasCreate681.cpp)
constructs a genuine **108B `BITMAPV4HEADER`** and uses the real Win32
`CreateDIBSection`, `CreateCompatibleDC` and `SelectObject` imports.
Before creation it calls the distinct exact 182B canvas release method
and exact 82B format-descriptor lookup. It preserves the original
signed 32-bit stride/alignment computation, four authentic channel
masks, signed DIB height, native error exits, and publishes the actual
bitmap, device context, selected object, pixel pointer and stride
into the game-owned font canvas fields at `+0x100..+0x120`.

The original code then **reads the already-committed format from the
actual canvas receiver**, not from the original argument. Native
formats `0x15` and `0x1A` initialize the buffer with genuine
four-byte `0xFF000000` and two-byte `0xF000` alpha words respectively;
other formats skip initialization. These writes are real gameplay
rendering state, not compiler-shaping dummy operations.

Previous [CORE/RECON-1044 frontier](GLYPH_CANVAS_CREATE681_NATIVE_FRONTIER.md)
used an `if/else if` format dispatch and saved an unnecessary
`auto* bytes = reinterpret_cast<uint8_t*>(this)` receiver alias.
That earlier candidate compiled to **684B/176 instructions** with
correct initial GDI IAT positions but mismatched native stack
lifetimes and branch layout. Rebuilding a source preserving the same
actual behavior, while **directly using the existing `this` receiver**,
generated 666B. Changing the committed-format dispatch to the
native **`switch`** recovered the complete 681B extent. Finally,
within *each real alpha fill arm*, declaring the pixel writer before
the meaningful alpha constant local yielded the original stack slots,
register use and branch byte layout. Alternative declaration orders
still compiled to 681B but differed by 18 or 36 ordinary opcode bytes.
The retained source naturally matches **649/649 ordinary original
machine-code bytes** without assembly, NOPs, artificial locals,
patched instructions, shortened comparisons or altered error behavior.

## Independently attested original call/relocation graph

[`verify-glyph-canvas-create681-native.py`](../scripts/verify-glyph-canvas-create681-native.py)
SHA-pins the complete original body, 176 instruction boundaries, the
actual `ret 0x0C`, 108-byte V4 header, all four original E8 target
addresses and all four physical PE HIGHLOW data destinations:

| Native site | Type | Physical original target |
| --- | --- | --- |
| `+0x0A` | DIR32 | security cookie `0x005B25C0` |
| E8 `+0x19` / field `+0x1A` | REL32 | canvas cleanup `0x00416360` |
| E8 `+0x26` / field `+0x27` | REL32 | original CRT memset `0x00544760` |
| E8 `+0x35` / field `+0x36` | REL32 | glyph format descriptor lookup `0x00415640` |
| `+0xFB` | DIR32 | real GDI `CreateDIBSection` IAT `0x0056C020` |
| `+0x119` | DIR32 | real GDI `CreateCompatibleDC` IAT `0x0056C044` |
| `+0x133` | DIR32 | real GDI `SelectObject` IAT `0x0056C02C` |
| E8 `+0x29E` / field `+0x29F` | REL32 | original cookie check `0x005429EE` |

All physical sites, types and destinations were verified from the
**immutable executable**, not inferred by solving candidate COFF
fields. The locked MSVC 19.44 i386 C++20 profile
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
produces **681B/176 instructions**, all **649/649 ordinary bytes** and
exactly the eight native relocation sites and roles. The one-source
canonical unit `glyph_canvas_create_681` was built fresh and accepted:

```text
glyph_canvas_create_681: exact (681/681 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This admits **one newly whole-exact game-authored physical head /
681 genuine executable `.text` bytes**. The previously exact 182B
cleanup, 82B format lookup, 104B fallback and three 20B field getters
retain their **own** existing, separately credited physical heads;
none are counted twice. The original 73B allocator, 2,227B GDI text
core, 2,245B glyph compositor, 578B formatter and 294B submit
remain independent, nonexact/unaccepted work. This source did not
modify any shared glyph header layout; no full-graph cold replay ran.

```sh
scripts/repo-python scripts/verify-glyph-canvas-create681-native.py \
  --candidate-object build/core1050-canonical/GlyphCanvasCreate681.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasCreate681.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1051 — the fourth glyph canvas field accessor

A [whole-exact 20B width getter on the same native canvas](GLYPH_CANVAS_WIDTH20_STRICT_EXACT.md)
is now separately admitted below the 2,245B glyph compositor.
Recompiling the shared-view include closure preserves this 681B
GDI surface source's whole 681/681 strict result. No native parent
or previously accepted field getter is double-counted.

## CORE/RECON-1052 — associated 2,245B compositor source frontier

The game-owned GDI canvas used by this exact 681B creator now has a
[2,245B source-present two-format glyph mask compositor](GLYPH_MASK_COMPOSITE2245_NATIVE_AND_VECTOR_EXACT.md).
Its source calls the real observed pixel, stride and width getters and
reproduces the native 16B PMR-vector neighbor offset protocol. The
new 2,245B parent remains NONEXACT; this 681B method and four
existing GDI-view functions remain strictly exact after scoped builds.
