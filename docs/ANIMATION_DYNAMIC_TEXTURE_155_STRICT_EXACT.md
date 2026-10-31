# CORE/RECON-1032 — whole original 155B Renderer dynamic D3D9 texture creation strict exact

Locked target: immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native game-owned `0x0044C0B0..0x0044C14A` is a complete
**155B/51-i386** Renderer dynamic texture creator (original whole-body
SHA-256 `dd489bdd5a80aca4ee1b88db8b3535ec19b9eded7f19e3ec685ea5b443a81670`).
This is a real `__thiscall` method receiving a borrowed Renderer ECX
pointer and four stack parameters: `TextureRecord*`, width, height,
and format index. It is now independently **whole 155/155 strict exact**,
not a normalised 149B candidate or shorter prefix.

## Original native semantics and independently physical relocation roles

The function preserves all existing texture record flag bits other than the
low two and selects mode **2**. It obtains the real process Graphics
D3D9 device via the original `Graphics::get_device` head; through the genuine
COM `CreateTexture` vtable slot `+0x5C`, it creates a single-mip
`D3DUSAGE_DYNAMIC`, `D3DPOOL_DEFAULT` texture. The requested texture
format is read from the real game-specific nine-word API-format table
`0x0056E208`, containing `(0, 21, 21, 21, 21, 21, 21, 21, 21)`.
The method reports **any nonzero HRESULT** through the original
`error D3DXCreateTexture\n` diagnostic, then stores its byte size using
the adjacent nine-word table at `0x0056E22C` (nine copies of `4`)
and returns the 32-bit product `width * height * bytes_per_pixel`.
There is no inserted domain check or changed success/error branch.

[`verify-animation-texture-creator-native.py`](../scripts/verify-animation-texture-creator-native.py)
pins the entire native original 155B and independently proves its
51 instruction boundaries, actual `ret 0x10`, genuine five trailing
`INT3`, both physical original E8 destinations and all five PE HIGHLOW
sites. The separate canonical manifest uses precisely those fields,
without solving source relocation targets from byte equality:

| Native field | Type | Original physical destination |
| --- | --- | --- |
| `+0x1C` | DIR32 | process Graphics `0x005C4D40` |
| `+0x21` | REL32 | actual Graphics device getter `0x00412730` |
| `+0x39` | DIR32 | actual format table `0x0056E208` |
| `+0x67` | DIR32 | original diagnostic string `0x0056E250` |
| `+0x6C` | REL32 | original game diagnostic method `0x0040C6B0` |
| `+0x7C` and `+0x91` | DIR32 | nine-entry 4-byte pixel-size table `0x0056E22C` |

## A real C++ argument evaluation order, not a byte patch

The earlier whole semantic source
[`AnimationDynamicTexture155.cpp`](../src/AnimationDynamicTexture155.cpp)
was **NONEXACT** even though it compiled to a full 155B/51 i386:
`const auto selected_format = texture_api_formats[format]` executed before
the `device->CreateTexture` expression. It produced only **112/127
matching nonrelocated bytes** and misplaced the genuine table DIR32 at
candidate `+0x2E` rather than native `+0x39`. That old hypothesis is
superseded by this complete source proof.

Decoding the original first showed the compiler evaluates the COM method
pointer **before** assigning the table-selected format into the local
format word. Moving the format assignment into the real SDK call argument:

```cpp
graphics_api::TextureFormat selected_format;
if (device->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC,
                          (selected_format = texture_api_formats[format]),
                          D3DPOOL_DEFAULT, &record->texture, nullptr) != 0) {
    ecl_diagnostic_hint("error D3DXCreateTexture\n");
}
```

reproduces the actual native read/order and two genuine local stack
values, without dummy operations or invalid ABI assumptions. Another
natural comma-argument expression produced identical bytes, but the
simpler single meaningful assignment is retained. In contrast, a direct
inline format expression without the local generates a **149B** body;
a precomputed format local is the earlier non-matching 155B alternative.
No artificial NOP, inline assembly, original-opcode transplant, inert
variable, comparison-field masking or non-source shortcut is used.

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` now generates **all 155 original bytes**,
including **127/127 identical nonrelocated code bytes and all 7
independently anchored relocation fields**, with the original
51 instructions. A new one-source canonical unit
`animation_dynamic_texture_155` has one fresh build/receipt and passes:

```text
animation_dynamic_texture_155: exact (155/155 bytes)
Exact replay: 1/1 units, 1 cold objects
PASS native dynamic: 155B/51 i386, 2 E8/5 original PE HIGHLOW
PASS entire 155/155 natural MSVC bytes and all seven original roles
```

This adds **one real game-authored head /155 original executable `.text`
bytes**. The neighbouring 139B render-target creation at
`0x0044C150` remains an independent whole-exact game method with its
own canonical provider; its public headers and receipts are untouched.
There is no need to migrate `IntrusiveList`'s class tag or to alter
Graphics/TextureRecord layouts. The surrounding Renderer ownership,
Card start Boss, full game linkage and running game remain separate.
No project-wide cold replay was run.

```sh
scripts/repo-python scripts/verify-animation-texture-creator-native.py \
  --variant dynamic \
  --candidate-object build/core1032-canonical/AnimationDynamicTexture155.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationDynamicTexture155.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
