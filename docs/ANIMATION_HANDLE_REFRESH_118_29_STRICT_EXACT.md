# CORE/RECON-1089 — complete original 118B game Animation handle rebind and distinct 29B native file getter

Immutable Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two physically separate originally source-absent **game-owned** native
functions from the 42-slot Renderer/AnimationFile spawn and handle
refresh protocol now have genuine C++20 source and WHOLE strict exact
canonical replay from the **same** maintained owner:
[`src/AnimationHandleRefresh118.cpp`](../src/AnimationHandleRefresh118.cpp).

| Original physical head | Full original native | Original whole SHA-256 | Strict result |
| --- | --- | --- | --- |
| `0x00437470` alternate AnimationFile lookup | **29B /12 i386** | `5d522088adaae7cf6dd7874b1fb8dffce62e06decfa592bc4877f4f3d745a246` | **29/29B exact, 21/21 nonrelocated** |
| `0x0044BCD0` AnimationHandle rebind/restart | **118B /41 i386** | `970c832112e93d29c132e7ebcce3077c751848ef4004a1a4797117a2b7162d3c` | **118/118B exact, 90/90 nonrelocated** |

## Original game ABI and actual native invocation graph

The **29B `0x00437470` file getter** is *not* an alias of the
previously accepted distinct **29B**
`Animation::animation_file()` at `0x00437500`. Both use the
original game `AnimationPoolOwner* current_animation_pool` global
**`0x005C0028`** and call `AnimationPoolOwner::file_by_index` at
**`0x00437970`** (original E8 `+0x14`, PE HIGHLOW `+0x10`). But
the previously exact 29B body reads native **`AnimationBase+0x1C`**
while the new 29B body reads **`AnimationBase+0x18`**. They are
**different physical native game function heads and different game
file slots**; the source retains a non-allocating
`NativeAnimationLegacyFileView : Animation` borrower, rather than
falsely sharing or duplicating the two functions.

The original game **118B `0x0044BCD0` Animation rebind** has exactly
**six original E8** and one actual PE HIGHLOW:

| Original physical site | Actual original callee/data role |
| --- | --- |
| HIGHLOW `+0x11` | process-global AnimationPoolOwner pointer `0x005C0028` |
| E8 `+0x15` | independently whole-exact **456B** `AnimationPoolOwner::resolve_handle` `0x0044CD00` |
| E8 `+0x26` | this now whole-exact **29B** alternate file lookup `0x00437470`, using AnimationBase+0x18 |
| E8 `+0x31` | separately reconstructed original **42B** `Animation::stop` `0x0044FD00` |
| E8 `+0x48` | previously whole-exact **57B** `AnimationFile::spawn` wrapper `0x00450C70` |
| E8 `+0x57`, `+0x65` | original **16B** Identifier32 value getter `0x0040C300`, reading current AnimationFile identity to republish both original AnimationBase file fields |

The 118B function owns an actual four-byte `AnimationHandle`
at `this+0`, resolves it through the authentic game pool; returns
without changing state when the old handle is absent; otherwise
retrieves the legacy file from AnimationBase+0x18, stops the previous
Animation, calls the real 57B nonspatial `AnimationFile::spawn`
with filename null, script number, layer -1 and optional Animation*
output null, and publishes its newly returned handle. It then
reads the original file identity twice and updates old Animation
**`base.field_18` and `base.field_1c`**, preserving the observed
native side effects.

## Crucial by-value C++ struct assignment, not an ABI workaround

The first meaningful C++ candidate used:

```cpp
handle.value = file->spawn(nullptr,script,-1,nullptr).value;
```

which compiled to the correct **118B/41 instructions**, all six E8
and one HIGHLOW, but with **five ordinary bytes in the hidden return
handle assignment area differing**. The native original evaluates
the returned four-byte `AnimationHandle` value before acquiring the
destination handle pointer for the store. Writing the ordinary C++20
**by-value structure assignment** instead:

```cpp
handle = file->spawn(nullptr,script,-1,nullptr);
```

naturally recovers all five bytes, both native stack-lifetime roles,
and the compiler-generated one original NOP after `Animation::stop`.
There is no handwritten NOP, target byte patch, return-ABI forgery,
artificial alignment or source-only fake variable. An independent
private probe of local-copy return variables produced a distinct
138B/46-i386 body, so that misleading form was rejected.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
now generates full **118/118** from the true game handle owner,
and **29/29** from the observed alternate file field. The
read-only original PE verifier
[`verify-animation-handle-refresh118-native.py`](../scripts/verify-animation-handle-refresh118-native.py)
independently hashes both *entire native original extents*, checks
all real E8 and PE HIGHLOW physical site/target roles, native
instruction counts and returns, distinguishes the already strict
29B +0x1C file getter, and inspects both fresh canonical whole
strict receipts. All code is real source-produced x86:

```text
animation_legacy_file_29: exact (29/29 bytes)
animation_handle_refresh_boss_118: exact (118/118 bytes)
Exact replay: 2/2 units, 1 cold object
```

This credits **two distinct original authored game function heads /
147 newly covered original executable `.text` bytes**. The earlier
29B AnimationBase+0x1C file getter, 456B resolve, 42B stop, 57B
spawn, 16B ID getter and other folded code are **not re-credited**.
The whole game is not yet globally linked/playable, and no
full-repository cold replay was run.

```sh
scripts/repo-python scripts/verify-animation-handle-refresh118-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationHandleRefresh118.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
