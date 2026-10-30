# CORE/RECON-969 — complete original 284B `AnimationFile::clear()` whole strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The actual original `0x0044AB00` is the **entire game-owned
284B/81-i386** resource retirement/clear routine, not an allocation
stub or abbreviated prefix. Earlier provenance audit
[CORE/EXACT-132](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md) correctly
identified the source owner and file fields but recorded the method
as **source absent**. This newer proof supersedes that historical
status with a real C++20 implementation and whole original-bound
compiler replay.

[`scripts/verify-animation-file-clear284-native.py`](../scripts/verify-animation-file-clear284-native.py)
reads the unchanged original PE and authenticates all 284 bytes and
81 instructions through the genuine `ret`, **every eight E8 instruction
site and its physical original target**, **all eight PE HIGHLOW
addresses/targets**, original `AnimationFile::bytes` at `+0x3C`,
texture count at `+0x44`, 24-byte (`0x18`) texture record stride,
and the **four** original `INT3` bytes following the function body.
It independently confirms two actual original callers:
`0x00449339` in the already accepted AnimationFile destructor and
`0x0044C491` in the separate RendererPool file release.

| Native original E8 | Original target and role |
| --- | --- |
| `+0x22` | `0x0044FD30` — remove/detach file-associated Renderer resources; original large callee **independently nonexact** |
| `+0x56` | `0x0044C510` — each 24B TextureRecord retirement; native callee **independently nonexact** |
| `+0x6B/+0x87/+0xA3` | `0x0040D840` — three original `DiagnosticAllocator::release_array<uint8_t>` calls (textures, sprites, scripts), each owner pointer set to null |
| `+0xC8/+0xED` | `0x0041F670` — genuine DiagnosticAllocator `release_bytes` of optional `+0x6C` and input file `+0x3C` buffers |
| `+0x109` | `0x004472C0` — separate existing strict `release_array<Animation>` for owner template array at `+0x40` |

The two physically original current-pool HIGHLOW fields point to
`0x005C0028`; the other six fields point to the real process allocator
at `0x005B8894`. These **16 exact original relocation roles**
are pinned in the canonical match manifest; no fake transitive
callee address or filename alias is substituted.

[`src/AnimationFileClear284.cpp`](../src/AnimationFileClear284.cpp)
uses the already existing, independently verified `AnimationFile`
layout and genuine typed `DiagnosticAllocator` template methods.
The provisional `NativeFileClearPoolView : AnimationPoolOwner`
declares only the **two real external original method ABIs**, with no
additional storage, allocation or fabricated Renderer definition.
The full method uses ordinary owner calls and a complete `texture_count`
loop. No handwritten assembly, dummy padding or target-byte editing
is needed; pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` directly yields **284B/81 i386,
220/220 nonrelocated bytes plus 16 native original relocations**.

```text
animation_file_clear_284: exact (284/284 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This adds **one original game-authored whole exact head /284 `.text`
bytes**. Original Runtime Renderer `0x0044FD30` and `0x0044C510`
remain separate large/medium source-absent functions and are not
claimed finished or recredited by this result. Whole-game linking and
playability remain unfinished. No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-file-clear284-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationFileClear284.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
