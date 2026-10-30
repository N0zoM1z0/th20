# CORE/RECON-972 — original entire 691B RendererPool file-detachment Boss whole strict exact

Original immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native game-owned RendererPool method at **`0x0044FD30`** is now a
complete **691B/205-i386 whole strict original-executable match**. This
is the previously unimplemented large direct original E8 callee
`0x0044AB22 -> 0x0044FD30` of the independently whole-exact
[284B `AnimationFile::clear()`](ANIMATION_FILE_CLEAR284_STRICT_EXACT.md).
It marks all live render-list Animations referring to the departing
file; it does not release the real texture or file memory itself.

## Original native PE evidence, not inferred Ghidra labels

[`scripts/verify-animation-renderer-file-detach691-native.py`](../scripts/verify-animation-renderer-file-detach691-native.py)
checks the entire original physical body digest
`0b30f104f40e2e7790066ef155a9f1a6fc66ff907fc3e702c91d1ec587591d11`,
all 205 decoded x86 instructions through genuine `ret 8`, **all 29
original E8 locations AND actual physical destinations** and **both
actual PE HIGHLOW fields**:

| Original relocation | Actual target/role |
| --- | --- |
| DIR32 `+0x06` | `0x005686C5`, actual original x86 exception-handler descriptor |
| DIR32 `+0x15` | `0x005B25C0`, real original security cookie |
| E8 `+0x65/+0x184` | `0x00449490`, true `0x48`-stride slot index for the single visited Renderer group at pool `+0x6C8` |
| E8 `+0x72/+0x194` | `0x0040C080`, folded `IntrusiveIterator` compiler auto-initializer |
| E8 `+0x7E/+0x1A0` | `0x00412280`, genuine `IntrusiveList<Animation>::begin()`-compatible physical source |
| E8 `+0x8D/+0x1AF` | `0x00412540`, real folded list end |
| E8 `+0x9A/+0x1BC`, `+0xA7/+0x1C9`, `+0xBA/+0x1DC` | Exact iterator advance/differs/get: `0x00411C30`, `0x00411BB0`, `0x0040C300` |
| Twelve E8 references (six per list) | `0x0040F160`, real `IntrusiveLink<Animation>::node_access()` source body |
| E8 `+0x16B/+0x28D` | `0x00411B00`, real iterator destruction and MSVC exception-state cleanup |
| E8 `+0x2A8` | `0x005429EE`, actual security-cookie verifier |

Each Renderer group holds two actual **24B `IntrusiveList<Animation>`**
subobjects, the primary at offset zero and the secondary at `+0x18`.
For every original Animation node, the method compares file ID against
both `AnimationBase::field_18` and `field_1c`. The optional byte
argument applies the real original `Animation+0x4B0` byte bit-1 filter.
When the match passes, the method sets original `Animation+0x570` to
`1`, requesting retirement. The original normal traversal includes
proper iterator lifetimes/exception unwinding and processing of only
one Renderer slot (`index` from zero to below one).

## Whole natural C++ and causal compiler differences

[`src/AnimationRendererFileDetach691.cpp`](../src/AnimationRendererFileDetach691.cpp)
uses the already accepted **one shared**
[`NativeFileClearPoolView`](../src/NativeFileClearPoolView.hpp),
[`NativeSpawnRendererView`](../src/NativeSpawnRendererView.hpp),
[`NativeRendererPoolSelector`](../src/NativeSpawnAnimationPoolView.hpp),
real `Animation`, and the maintained `IntrusiveIterator` and
`IntrusiveLink` protocol. The byte `0x4B0` flag is represented with
an explicit two-bit **unsigned-byte bitfield view**, not a broken
signed word shift or a fabricated extra renderer allocation.

Three complete pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` experiments established the
precise source-level structure:

| Candidate | Whole original code contribution | Actual issue |
| --- | --- | --- |
| Cache one `Animation*` from each iterator | **629B/182-i386**, 18 E8/2 DIR32 | Original performs **six** separate link-to-Animation accesses in each list, not a single cached result |
| Restore six native `node_access()` calls per list and separately index both lists | **716B/206-i386**, 29 E8/2 DIR32 | Unnecessary signed flag byte promotion, synthetic byte-array indexing, extra `begin` receiver local and wrong null-file lexical branch |
| Represent original byte bit-1 as a true C++ byte bitfield and check unsigned flag | **694B/206-i386**, 29 E8/2 DIR32 | Only an original-absent pointer temporary and null-file branch shape remain |
| Use direct `IntrusiveList<Animation>` receiver for the first `begin()`, and preserve original empty null-file branch | **691B/205-i386**, **29 E8/2 DIR32**, **567/567 nonrelocation bytes** | **All original full-machine-code structure now correct** |

The final source uses a genuine unoptimized null-file `if`/`else`
lexical structure. The original `jne short` then `jmp` cannot be
reproduced by the semantically equivalent simple `if (file)` source,
which gives a different near-conditional layout. It is a natural C++
control-flow choice, **not** an inserted NOP, inline assembly, a byte
patch, or an unverified truncated-prefix comparison.

Pinned original-target-bound canonical replay against real source
symbols/EH descriptor and all native code bytes:

```text
animation_renderer_file_detach_691: exact (691/691 bytes)
animation_file_clear_284: exact (284/284 bytes)
animation_texture_record_release_94: exact (94/94 bytes)
animation_file_slot_release_209: exact (209/209 bytes)
Exact replay: 4/4 affected units, 4 cold objects
```

This adds **one distinct original game-authored 691B function/+691
`.text` bytes**. The other three independently exact files are
regression checked, not counted again. Original child iterator/
folded methods, Renderer allocation/startup, and the separately
source-absent 2,884B particle Update and 39,470B Animation VM remain
independent work. No full cold replay or playable-game claim.

```bash
scripts/repo-python scripts/verify-animation-renderer-file-detach691-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererFileDetach691.cpp --source src/AnimationFileClear284.cpp --source src/AnimationTextureRelease94.cpp --source src/AnimationFileSlotRelease209.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
