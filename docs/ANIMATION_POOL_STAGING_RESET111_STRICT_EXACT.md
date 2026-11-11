# Whole-native 111B Animation pool staging-buffer reset

The Japanese TH20 Steamless v1.00a original, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a complete **111B/29-instruction** function at `0x00445A40`
(SHA-256 `5926f138147b933a68c1e3d7e85d7bbf87cafd36c812a160b82ead7fd171f16d`).
It has **no E8 call or physical PE HIGHLOW field**. Pinned MSVC 19.44 x86
C++20 now reproduces the **entire 111/111 original bytes** as
`src/AnimationPoolResetStaging111.cpp`, verified through its fresh canonical
object and strict `animation_pool_staging_reset_111` replay.

## Actual owner and staging protocol

The three independent original frame-recovery sites `0x00419D1C`,
`0x00419F72` and `0x0041A0ED` each execute `mov ecx,[0x005C0028]`
followed immediately by `call 0x00445A40`. Thus the receiver is the
existing process `AnimationPoolOwner` used by rendering, not a separate
hypothetical allocation. The native function clears the queue count at
`this+0x06000E70`; it computes the stream base `this+0x06000E74`
and publishes it into the two primary stream pointers at
`this+0x07C00E74/+0x07C00E78`; it zeros the second count at
`this+0x07C00E7C`, then publishes `this+0x07C00E80` into both
secondary stream pointers `this+0x07D40E80/+0x07D40E84`.

The already independently whole-strict-exact **192B**
`AnimationPoolOwner::flush_draws()` uses the same native queue count
and primary stream cursor to issue D3D9 `DrawPrimitiveUP` and reset its
primary cursor after submission. The original caller identity and shared
fields establish the authored game staging behavior. The new method uses a
local non-instantiated `NativeAnimationPoolStagingView : AnimationPoolOwner`
with no new fields, vtable, storage, or shared-header edits. Typed address
operations preserve actual native offsets rather than allocating a synthetic
~130 MiB C++ structure or copying executable bytes. The historical class
spelling remains provisional.

## Complete evidence and bounded replay

`verify-animation-pool-staging-reset111-native.py` independently checks
whole original SHA, all 29 instruction heads and return, absence of E8 and
PE HIGHLOW, the three actual receiver-load/call pairs, complete COFF
contribution, and canonical exactness. The only new native provider is this
source; all existing shared type headers and previous units remain unchanged.

```sh
nice -n 15 scripts/repo-python scripts/build.py --unit animation_pool_staging_reset_111
scripts/repo-python scripts/verify-animation-pool-staging-reset111-native.py
scripts/repo-python scripts/compare-coff-function.py --unit animation_pool_staging_reset_111
scripts/repo-python scripts/validate-tracking.py --require-target
```

This adds **one genuine game-authored whole-exact function and 111 original
`.text` bytes** without changing the still-NONEXACT 5,993B enclosing
Animation Draw dispatcher. It is independently source-exact but does not imply
a linked or playable game. No full-graph cold replay is necessary.
