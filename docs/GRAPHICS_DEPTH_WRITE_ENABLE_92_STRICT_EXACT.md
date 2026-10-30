# CORE/RECON-849 — complete original 92B Graphics Z-write-enable state leaf strictly exact

The immutable Japanese TH20 v1.00a Steamless original executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains one whole game-owned **92B/30-real-i386** Graphics depth-write
**enable** method at `0x004DDFE0`. This is a separate physical head from
previously strict exact `0x004DDF80` Graphics depth-write **disable**.
The freshly exact whole 2,136B Animation Mesh24/25 renderer calls this
function at its original E8 `0x004430B8` (offset `+0x98`).

The natural maintained C++
[`src/GraphicsEnableDepthWrites.cpp`](../src/GraphicsEnableDepthWrites.cpp)
now emits an entire **92/92B strict exact** native body under the pinned
MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
No duplicate compiler function, library code, padding or shortened extent
is claimed.

## Independent original PE semantics

[`scripts/verify-graphics-depth-enable-native.py`](../scripts/verify-graphics-depth-enable-native.py)
reads the locked original PE independently from the new COFF. All 30
original i386 heads are decoded through the native `ret`, establishing
the original one ECX fastcall Graphics receiver:

1. At native offset `+0x0C`, compare the game-owned `Graphics+0xDBC`
   render-state cache against **integer 1** and branch on equality.
2. If the cache is not already 1, load the original global live
   `current_animation_pool` pointer at `0x005C0028` through one actual PE
   HIGHLOW data field at `+0x17`. Call the existing whole-strict 192B
   `AnimationPoolOwner::flush_draws` at `0x004455C0`, with actual original
   direct E8 at `+0x1B`.
3. Write **1** to `Graphics+0xDBC` and invoke the original device's
   D3D9 vtable slot `+0xE4` (`IDirect3DDevice9::SetRenderState`) with
   real `(D3DRS_ZWRITEENABLE=14,value=1)` argument pushes. Otherwise
   return zero when no state transition was needed.

The previously reconstructed disable method at `0x004DDF80` has a distinct
original physical body and writes `(ZWRITEENABLE=14,value=0)`. Its source
was **not** edited for this checkpoint. The new enable method is a
real game-owned Graphics renderer-cache transition, not a compiler or STL
utility and not extra credit for the already exact Mesh parent.

## Full original byte/relocation acceptance

The one new `graphics_depth_write_enable_92` canonical unit in
[`config/match-units.toml`](../config/match-units.toml) builds exactly one
pinned x86 source provider `build/core849-canonical/GraphicsEnableDepthWrites.obj`.
Its complete native two relocation roles are verified independently:

| Original source role | Original physical site | Native target |
| --- | --- | --- |
| Pool-owner global HIGHLOW / DIR32 | `+0x17` | `0x005C0028` |
| Real `flush_draws` E8 / REL32 | `+0x1C` 4-byte displacement (`E8` at `+0x1B`) | `0x004455C0` |

The compiler emits **92 bytes/30 x86 instructions**, all **84/84
non-relocation bytes** identical before relocation. Both genuine COFF
fields have the original symbol, type, offset and independently established
target, yielding the strict whole-native result:

```text
graphics_depth_write_enable_92: exact (92/92 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Only this new source is built and replayed. No shared exact header,
previously accepted C++ source, compiler profile or old match unit was
modified; **previously exact provider replay scope=0**. There was no
unfiltered whole-graph cold replay. Exactly one new 92B physical game
function is credited, distinct from the already strict 2,136B mesh and
92B disable methods.

| Verified live metric | Before | After |
| --- | ---: | ---: |
| Game-authored strict whole functions | 602 | **603** |
| Original game strict `.text` bytes | 206,008 | **206,100** |
| Source-present mappings | 1,248 | **1,249** |
| Canonical strict units | 1,249 | **1,250** |
| Distinct pinned exact objects/receipts | 267 | **268** |

The enclosing original 5,993B Animation Draw dispatcher remains a
separate **SOURCE-PRESENT/NONEXACT** Boss. Current progress does not claim
a linked or playable reconstructed game.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-graphics-depth-enable-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsEnableDepthWrites.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
