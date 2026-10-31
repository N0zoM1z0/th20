**Current status correction (CORE/RECON-1032):** This historical 155B NONEXACT compiler-order frontier is now [whole 155/155 strict exact](ANIMATION_DYNAMIC_TEXTURE_155_STRICT_EXACT.md). A real format local assigned *within the D3D9 CreateTexture argument* preserves the original COM vtable lookup-before-format order; all seven original relocation roles match. The older alternatives below are retained as evidence, not current acceptance state.

# CORE/RECON-998 — complete 155B Renderer dynamic texture creator source frontier

The immutable original at `0x0044C0B0..0x0044C14A` is a **155-byte /
51-instruction** C++ `__thiscall` Renderer method. It takes the true
TextureRecord*, width, height, and format-index parameters. Original PE
SHA-256 `dd489bdd5a80aca4ee1b88db8b3535ec19b9eded7f19e3ec685ea5b443a81670`.
Its complete two real E8 targets and five PE HIGHLOW fields are independently
verified by `scripts/verify-animation-texture-creator-native.py --variant dynamic`.

The complete natural maintained
[`AnimationDynamicTexture155.cpp`](../src/AnimationDynamicTexture155.cpp)
uses the same actual non-owning `NativeRendererTextureOwner` as the newly
**139/139 strict-exact** render-target creator. It preserves existing upper
texture-record flag bits while selecting low bits `2`, obtains the native
Graphics device through `get_device()`, uses genuine D3D9 `CreateTexture`
with 1 mip level, `D3DUSAGE_DYNAMIC`, default pool and the independent
nine-entry source format table, invokes the existing diagnostic on **all
nonzero** HRESULTs, sets the size-per-pixel from the nine-entry native table,
and returns width * height * bytes-per-pixel as a 32-bit result. The separate
original 36-byte physical table at `0x0056E22C` contains nine 4-byte entries
of `4`; its canonical data placement is not yet established.

## The concrete compiler mismatch (do not claim exactness)

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits the **full original 155B /51 x86
instruction count**, but only **112/127 nonrelocated bytes match**.
The candidate accounts for the correct seven target roles; six are in
exact original positions. The format-table DIR32 field is at candidate
`+0x2E` versus original **`+0x39`**, because compiler evaluation order
loads the format argument *before* the COM vtable method. The real original
loads the COM virtual `CreateTexture` method at `+0x5C` first, then the
format word, and only then pushes the full argument sequence. This also
changes three saved stack-slot assignments and register choices. The
independently attested original roles are:

| Original field | Native target |
| --- | --- |
| DIR32 `+0x1C` | process Graphics `0x005C4D40` |
| REL32 `+0x21` | folded Graphics device getter `0x00412730` |
| DIR32 `+0x39` | nine-entry D3D format table `0x0056E208` |
| DIR32 `+0x67` | original diagnostic `0x0056E250` |
| REL32 `+0x6C` | diagnostic callee `0x0040C6B0` |
| DIR32 `+0x7C/+0x91` | native 4B-per-pixel array `0x0056E22C` |

Private, reproducible source/COFF probes under `.analysis/gptweb-texture-creators/`
and `build/gptweb-texture-creators/` test a direct C++ virtual call,
precomputed format value, and SDK `CINTERFACE` virtual dispatch. None matches
the complete original bytes; the `CINTERFACE` variants either retain the
wrong evaluation order or introduce an extra pointer spill and a 161B body.
No fake return, artificial dead local, assembly, relocated byte patching,
shrinking extent, or false exact claim is introduced.

Status: **SOURCE-PRESENT, NONEXACT.** The adjacent 139B original method is
independently whole exact and should remain protected. The full Renderer
class layout, 155B instruction ordering, target data layout and full-game
linkage remain unproven. No source or whole-native exact credit is added
for the 155B body at this checkpoint.

```bash
scripts/repo-python scripts/verify-animation-texture-creator-native.py --variant dynamic
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationDynamicTexture155.cpp build/core998-probes/AnimationDynamicTexture155.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/compare-coff-function.py \
  build/core998-probes/AnimationDynamicTexture155.obj \
  '?create_dynamic_texture_44c0b0@NativeRendererTextureOwner@th20@@QAEHPAUTextureRecord@2@HHH@Z' \
  0x0044C0B0 155
```
