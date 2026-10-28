# CORE/EXACT-449 — complete 246-byte AnimationPoolOwner interruption and 35-byte AnimationHandle wrapper

Original comparison target: immutable Japanese TH20 v1.00a Steamless PE,
whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two physically distinct complete game-owned native functions are now
strict original byte-exact:

| Actual original game method | Native physical address | Whole strict original bytes | Original x86 instructions | E8 / PE HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `AnimationPoolOwner::interrupt_handle(uint32_t,int)` | `0x0044EE90` | **246/246B** | **77** | **12 / 2** |
| `AnimationHandle::interrupt(int)` | `0x0044EF90` | **35/35B** | **15** | **1 / 1** |

The complete immutable original whole-interval SHA-256 digests are
`72e1c72d37e2295fb226b5ec1ee1547712f087fb5baa55927b08911831840bb8`
and
`8da5fa1b51223253fc46b61577a688327b5b502b75084b63a61a2d2f5366f301`.
They contribute **281 unique nonoverlapping original game-authored bytes**,
not two aliases for the same original function.

## Correct original owner, two arguments and real gameplay control flow

**Critical correction:** the 246B function at `0x0044EE90` is
**not** `AnimationHandle::interrupt`. Its genuine receiver
is the big `AnimationPoolOwner`; it takes two stack arguments
and finishes with native **`ret 8`**. The first argument is
the four-byte handle index, the second is the interruption
event. It asks its real `AnimationPoolOwner::resolve_handle`
at `0x0044CD00` to obtain an actual `Animation*`.
When the handle does not resolve, the function **returns
before constructing an iterator**.

For a live Animation the original chooses
`animation->child_links[1]` at native offset `+0x514`
and constructs a genuinely exception-aware
`IntrusiveIterator<Animation>`. It uses the real
link `begin/end` and iterator advance/differs/get
methods, follows `IntrusiveLink<Animation>::node_access`
to the actual `Animation*`, and forwards the **same
original integer event** to
`Animation::interrupt(int)` at `0x004388F0` for
every child reached. The iterator's genuine destructor
and native exception-handler registration/unregistration,
compiler stack cookie and cookie check are preserved.
No child-list storage or callback ABI was invented.

A natural `if (animation) { ... }` code shape compiled to
**245B/76 instructions** and combined the original
`jne` plus `jmp` invalid-handle branch into one `je`.
The correctly scoped source
`if (!animation) return;` followed by the real iterator
lifetime block emits **all 246 original bytes and 77
instruction heads**. No hand-inserted branch, dummy
buffer or padding instruction was added.

The separate original **35B `AnimationHandle::interrupt(int)`
at `0x0044EF90`** is a true bridge with a **four-byte
AnimationHandle receiver** and one stack event argument
(native `ret 4`). It obtains the actual global
`current_animation_pool` at `0x005C0028`,
passes `AnimationHandle::value` and the original
event into the above pool-owner two-argument method,
then returns. This wrapping method was already
declared in `src/AnimationHandle.hpp`, but its native
definition had not previously been implemented.

The entire **456B AnimationPoolOwner::resolve_handle`
at `0x0044CD00` remains a distinct, nonexact
large native callee**. Its original x86 control flow
was independently inspected; this checkpoint never
claims or credits any of those 456 original bytes.
The separately exact 243B
`IntrusiveLink<Animation>::begin`, child-link indexing,
iterator ABI, child Animation interruption and
other previously accepted physical callees remain
separate original functions.

## Whole immutable original PE E8 and HIGHLOW audit

The complete 246B body was independently decoded from
the original PE as **77 whole native instructions**,
with **twelve** direct E8 call fields and **two**
`.reloc` HIGHLOW fields. The first two absolute fields
are original `+0x06 DIR32 -> 0x005685FD`
(native exception-handler descriptor) and
`+0x15 DIR32 -> 0x005B25C0`
(real compiler security cookie). Original E8 calls:

| Original code field | Native PE target | What the actual code invokes |
| --- | --- | --- |
| `+0x33` | `0x0044CD00` | separate **nonexact 456B** pool handle resolver |
| `+0x57` | `0x004494B0` | exact child-link [1] getter |
| `+0x64` | `0x0040C080` | folded iterator auto-initializer |
| `+0x70` | `0x0044B9F0` | exact IntrusiveLink Animation begin |
| `+0x7F` | `0x00412540` | exact folded link end |
| `+0x8C` | `0x00411C30` | exact iterator advance |
| `+0x99` | `0x00411BB0` | exact iterator differs |
| `+0xA8` | `0x0040C300` | exact folded iterator get |
| `+0xB3` | `0x0040F160` | exact folded node access |
| `+0xC4` | `0x004388F0` | real exact Animation::interrupt |
| `+0xD6` | `0x00411B00` | exact folded iterator destructor |
| `+0xEC` | `0x005429EE` | original native security-cookie check |

The 35B wrapper independently has the real
`+0x13 DIR32 -> 0x005C0028` global pool pointer and
`+0x18 REL32 -> 0x0044EE90` new whole-exact pool
interruption member. All **16 native field offsets,
types, actual original targets, COFF symbol identities
and real zero addends** match these freshly compiled
complete functions.

The unchanged strict canonical comparator matches
**190/190 nonrelocation bytes +56/56 relocated
bytes for the pool boss**, and **27/27 nonrelocation
+8/8 relocated bytes for the handle wrapper**.
Full independent original PE, original sha256,
compiler symbols, actual field locations and prior
canonical callee origin evidence:
`.analysis/core449-animation-pool-interrupt-native-pe-proof.json`.

## Actual previous-header-receipt source closure and exact regression

The real `AnimationPoolOwner::interrupt_handle` method
declaration was added to `src/AnimationRuntimeOwner.hpp`;
its definition is co-owned with the previous exact
`set_handle_position` and actual handle forwarding
in `src/AnimationHandlePosition.cpp`, using that
same existing canonical object and pinned MSVC i386
`/Od /Ob0 /GS /sdl /EHsc` profile.
The 35B `AnimationHandle::interrupt` definition was
added to the existing `src/AnimationHandle.cpp`
with its native pinned `/GS-` profile; that source
newly includes `AnimationRuntimeOwner.hpp`.
There is **no new public AnimationHandle.hpp
declaration or field layout change**.

Before these edits, old locked compiler receipts
established exactly **ten existing source providers
and twenty old strict units** including
`AnimationRuntimeOwner.hpp`. The newly included
`src/AnimationHandle.cpp` adds five earlier strict
units to the actual closure; the two new complete
methods add one strict unit in each existing owner.
Consequently, **27/27 native strict exact units in
11 cold source objects** were replayed in three
serial reduced-priority batches of **15 + 11 + 1**.
The independent 1,081B Player option frame,
1,518B Player option animation rebuild and
earlier exact animation/handle methods remain exact.
One compiler-private BulletCancel `$SG` label changed
with the header update and was accepted only after
re-attesting the immutable original string target
`0x0056FD14`, relocation position/type and
complete nonrelocation bytes. The unchanged
strict oracle then accepted its full original body.

Private preedit compiler receipt closure:
`.analysis/core449-animation-pool-preedit-closure.json`;
exact changed source grouping:
`.analysis/core449-animation-pool-replay-groups.json`;
complete actual replay:
`.analysis/core449-animation-pool-replay-batch0.log`
through `batch2.log` and
`.analysis/core449-reconciled-private-symbols.json`.

The still-nonexact **3,111B Player main-frame**
at `0x004F9C30` calls the 246B pool method
once; after this checkpoint **65/67** original
parent E8 call sites have separately whole-exact
native callees. The remaining two native calls
lead to the 26B input-provider accessor and
555B Player movement/clamp function, both
unclosed here. Nothing about the entire 3,111B
parent, 456B pool resolver or linked game runtime
is automatically credited; no unfiltered full
repository cold replay was run.
