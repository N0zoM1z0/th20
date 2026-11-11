# CORE/RECON-1104 — Renderer formatted sprite-text call, whole 417B strict exact

The original Japanese TH20 Steamless v1.00a (`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`) has a complete game-authored Renderer formatted-text function at **`0x0044AC20`**, exactly **417 bytes /114 i386 instructions**. Its original whole-code SHA-256 is `fcb32fddd7049419c2626a3bea36aaed056156b99d07c59862f51459ccbb3c84`; the last instruction ends at `0x0044ADC1`, followed by 15 actual `0xCC` bytes before the next function at `0x0044ADD0`. The following alignment bytes are not included as code credit.

The maintained source is [`AnimationRendererFormattedText417.cpp`](../src/AnimationRendererFormattedText417.cpp), with the borrowed variadic Renderer method in [`NativeRendererFormattedTextView.hpp`](../src/NativeRendererFormattedTextView.hpp). This replaces the prior unfinished private 418B candidate without changing the shared `Animation` layout. The original Ghidra 417B body and callers were inspected through the target-bound TH20 Ghidra provider; the complete physical x86 and PE relocation sites were then decoded independently from the hash-locked executable.

## Reconstructed original behavior

The `__cdecl` variadic Renderer member returns an eight-byte result through the hidden pointer, with `this` on the stack. It locks `process_locks.slot(9)` using `std::lock_guard<std::recursive_mutex>`, formats the incoming varargs through the already-exact 30B `format_text_447940` into a **640-`wchar_t`** buffer, retrieves the animation's sprite, and copies four actual transform words from `Animation+0x3A8..0x3B4`.

It performs the original **byte** flag setting at `Animation+0x49A` (`flags.bit_10 = 1`); the separate bit-10 predicate is read from the original **word at `Animation+0x49C`**, not from the changed byte. The texture is looked up by the sprite's texture ID. Finally the function passes the original shifted horizontal/align parameters and a **by-value `std::function<void()>`** to the 294B text submit call. The 294B submit function itself remains independently **NONEXACT**; this parent's exactness does not imply that callee's exactness. The original 417B body has 17 observed callers.

## Independent original relocations

All ten original E8 instructions were decoded from the native machine-code operands, not inferred from candidate relocation fields:

| Native instruction offset | Physical target | Role |
| --- | --- | --- |
| `+0x39` | `0x0040C310` | Lock slot 9 |
| `+0x45` | `0x0040B730` | Lock guard constructor |
| `+0x69` | `0x00447940` | Wide-text formatting |
| `+0x7E` | `0x00437CD0` | Sprite lookup |
| `+0xFC` | `0x00445A00` | Texture lookup |
| `+0x116` | `0x004140F0` | `std::function` copy |
| `+0x161` | `0x0044FFF0` | Text submit |
| `+0x170` | `0x0040B900` | Lock guard destruction |
| `+0x17F` | `0x00414400` | `std::function` destruction |
| `+0x198` | `0x005429EE` | Security cookie check |

There are **three** native PE HIGHLOW fields at `+0x06 -> 0x00568528` (the original EH handler), `+0x18 -> 0x005B25C0` (security cookie), and `+0x35 -> 0x005C0240` (lock registry). The canonical COFF has exactly **ten REL32 + three DIR32** relocations at corresponding operand-field offsets. Original native SHA, every E8 destination and all physical HIGHLOW fields were checked before writing the target destinations into [`animation_renderer_formatted_text_417`](../config/match-units.toml).

## Strict native result

Pinned MSVC 19.44 x86 C++20 profile: `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`. The private prototype and the promoted maintained source both emitted the entire **417B** with **365/365 identical non-relocation bytes** (13 fields × 4 bytes masked diagnostically). The canonical single-source build and its complete independent-relocation replay passed **417/417 relocated bytes** with no ignored ordinary bytes, shortened function body or fake padding. The new source is an independent original game-authored exact head: **+417 credited native bytes**; neither its formatted-text helpers nor the pending 586B sibling are counted again.

Reproduce only the touched unit, without cold-replaying the whole game:

```sh
nice -n 15 scripts/repo-python scripts/build.py --unit animation_renderer_formatted_text_417
scripts/repo-python scripts/compare-coff-function.py --unit animation_renderer_formatted_text_417
```

The original two 508B/511B Renderer list-update Bosses remain open on the separately investigated compiler `/sdl` list preclear; their local derived-list probe did not cause the expected 10B initialization. No public intrusive-list ABI change was made in this checkpoint.
