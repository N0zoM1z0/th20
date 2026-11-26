# Exact GDI glyph text core and temporary queue submission

`th20::native_text_core_415830` at `0x00415830` now strictly replays its
complete **2,227B / 470-instruction** body. The comparison covers the full
**2,316B contribution**: code, one original alignment NOP, and all 22 font
switch pointers. All 25 E8 calls, 43 body data fields and 22 table fields
match. Its complete 99B exception-code contribution and 76B five-state
metadata also match. This adds one authored exact function and 2,227 game
code bytes; compiler support and table bytes receive no additional credit.

The locked target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original code SHA-256 is
`c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70`.
The compiler is pinned MSVC 19.44.35211, x86, with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Findings that close the whole contribution

The old 2,308B candidate named the glyph job, a reference to that job and
its `std::function` wrapper. The native sequence instead materializes the
job temporary as an argument to an implicitly constructed function, submits
that function, then destroys the function before the job at the same full
expression boundary. The maintained source now expresses that directly:

```cpp
reinterpret_cast<NativeGlyphQueueView*>(&native_glyph_task_queue_5b66e0)
    ->submit_4162f0(NativeGlyphRenderJob{
        *std::addressof(canvas), texture, native_rectangle, pixel_rectangle,
        completion_flag, callback});
```

The queue interface takes `std::function<void()>&&` and retains its existing
`std::_Unfancy` forwarding before moving into the list backend. Its complete
56B body and both relocations are byte-identical to the previously accepted
lvalue-reference declaration. The x86 reference argument remains one pointer;
its value category now supports the temporary-consuming caller in standard
C++. The bridge alone did not distinguish the two reference categories. The
whole caller, bridge behavior and cleanup order support the revised interface.

Implicit conversion matters here. An explicit `std::function<void()>(job)`
argument adds two function-constructor result-pointer locals, producing a
2,336B contribution. Implicit conversion avoids those extra words while
retaining the job constructor's two native pointer stores at `+0x7EC/+0x7F8`.
The function constructor, queue and two destructors then align at
`+0x80F`, `+0x824`, `+0x833` and `+0x842`. The job's post-destructor NOP and
the switch alignment NOP are emitted naturally.

The spaced-text branch also uses one X-position local. Initialize it before
the two-character buffer and `SetTextColor`, advance it through the optional
outline loop, then reset it from `horizontal_offset` before the ordinary
loop. Two separately declared X locals occupied one extra word and changed
many scalar slots despite matching every call position. Reusing the real
position restores the native `0x310` frame and all remaining ordinary bytes.

The existing `NativeGlyphRenderJob` remains the single shared owner of its
132B constructor, 23B destructor and independently exact 360B upload body.
No lambda implementation or duplicate upload body is maintained. The typed
completion pointer, address helper, font aliases, GDI color channels,
CP932 conversion, outline/alpha operations and packed extent return remain.

## Complete exception ownership and independent bindings

| Native address | Full extent | Cleanup role |
| --- | ---: | --- |
| `0x00567DA0` | 8B | By-value callback argument |
| `0x00567DA8` | 11B | Raster lock guard |
| `0x00567DB3` | 11B | Submit lock guard |
| `0x00567DBE` | 11B | Glyph job temporary |
| `0x00567DC9` | 16B, including five INT3 bytes | Function temporary |
| `0x00567DD9` | 42B | Cookie-checking EH handler |

The five cleanup actions and handler form a complete 99B COFF contribution.
Masking its real relocation fields gives one matching location in the
original `.text`, independently anchoring the handler and actions without
using the root's compared EH field. Filling those action targets into the
76B metadata, while masking only its map pointer, gives one `.rdata` match
at `0x005A9880`. The 36B FuncInfo selects the 40B unwind map at `0x005A98A4`.
All six metadata DIR32 fields and their physical HIGHLOW positions match.

External call/data bindings use the established native owners and imports.
Font pointers are bound to the generated same-section case labels relative
to the independently fixed root address; canonical replay checks those
label definitions and all 17 alias groups against the original fields.
The allocation diagnostic's actual literal bytes are also checked. No
relocation destination is solved from the field under comparison.

## Scope, controls and reproduction

Captured include closures show only two affected providers for
`NativeGlyphTextQueueView.hpp`: the text core and 56B queue bridge. Fresh
locked builds pass **10/10 complete canonical units**: the root, six EH
code units, and the existing 132B constructor, 23B destructor and 56B bridge.
The 2,316B compared extent is explicit in `glyph_text_core_2227`; the ledger
credits only its 2,227B function. Other providers retain their evidence.

```sh
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextCore2227.cpp \
  --source src/GlyphTextQueueSubmit56.cpp --existing-objects
nice -n15 scripts/repo-python scripts/verify-glyph-text-core2227-native.py \
  --candidate-object build/gpt61-glyph-text-canonical/GlyphTextCore2227.obj
```

Private controls reject a text/outline color swap, a redirected font-case
pointer, the old 2,308B contribution, and malformed EH state count, map symbol
and cleanup symbol. Early temporary-reference controls did not improve the
root; ordinary lambda captures reproduced the 132B/23B children but also
left the 2,308B frontier. These controls explain why changing the closure's
spelling alone did not recover the caller's lifetime boundary.

Canonical objects/receipts remain in `build/gpt61-glyph-text-canonical/`;
the old `core1059-canonical` and `core1060-canonical` products are preserved.
The unit manifest records the active provider and complete comparison settings.

The downstream [151B list insertion and allocator construction](GLYPH_QUEUE_FORWARDING_STRICT_EXACT.md)
are now independently exact. The 294B submit and 578B/586B formatting callers
remain open. The exact text core does not establish a complete linked game.
