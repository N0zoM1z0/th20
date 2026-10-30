# CORE/RECON-970 — complete original 94B `TextureRecord` release whole strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The real `0x0044C510` is the full game-owned **94B/33-i386**
Renderer-side `TextureRecord` release routine. It is physically called
at E8 `0x0044AB56` from the independently whole-exact
[284B `AnimationFile::clear()`](ANIMATION_FILE_CLEAR284_STRICT_EXACT.md).
The source is not a manual copy of the original x86 instructions: the
native virtual-call ABI has been derived from actual COM semantics.

## Immutable original native proof

[`scripts/verify-animation-texture-release94-native.py`](../scripts/verify-animation-texture-release94-native.py)
checks all 94 original executable bytes through the native `ret 4`, all
33 actual i386 instructions, the indirect vtable+8 call for the real
`IDirect3DTexture9::Release()`, both original external buffer null
checks, full original E8 `+0x49 -> 0x0041F670`, the one physical original
HIGHLOW `+0x45 -> 0x005B8894` (real process DiagnosticAllocator), and
the 284B parent E8 site/target. The native method clears the actual
TextureRecord `texture` at offset 0 and `external_bytes` at offset 4;
the already established `TextureRecord` occupies **24B**.

[`src/AnimationTextureRelease94.cpp`](../src/AnimationTextureRelease94.cpp)
uses the existing `TextureRecord` type, real Direct3D9 header,
`record->texture->Release()` and the actual typed
`process_allocator->release_bytes` call. The native double guard for
external storage is retained in natural source rather than removed as
an imagined redundant check. There is no handwritten x86, fake NOP,
source shorter than the original function, or target-byte patch.

[`src/NativeFileClearPoolView.hpp`](../src/NativeFileClearPoolView.hpp)
declares a **single non-owning Renderer/File teardown receiver** shared
with `AnimationFile::clear()`; original whole Renderer lifetime and the
large 691B file-detachment method remain separate unresolved work.
The shared header was integrated into both accepted sources, with
strict local replay under the pinned MSVC 19.44 x86 C++20 `/Od /Ob0
/GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` profile:

```text
animation_texture_record_release_94: exact (94/94 bytes)
animation_file_clear_284: exact (284/284 bytes)
Exact replay: 2/2 units, 2 cold objects
```

The compiler emits **86/86 matching nonrelocated bytes** plus both
original physical relocation roles. This contributes **one new
original game-authored function/+94 unique `.text` bytes**, without
recrediting its 284B parent or the existing allocator callee.
No unfiltered full cold replay or claim of a linked/playable game.

```bash
scripts/repo-python scripts/verify-animation-texture-release94-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationTextureRelease94.cpp --source src/AnimationFileClear284.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
