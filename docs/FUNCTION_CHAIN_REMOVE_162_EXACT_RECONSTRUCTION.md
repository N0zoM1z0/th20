# CORE/EXACT-387 — complete original 162-byte FunctionChain owned-node removal

Immutable original: Japanese TH20 v1.00a Steamless, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire game-owned `FunctionChainController::remove_unlocked`
at `0x00412400..0x004124A1` is **162 native bytes /
52 native i386 instructions**, full original function SHA-256
`53572abfe9839b25531ee0c84e7b5a9fd4a167e495dbcdad3443e609a3557de4`.
The function now has a strictly exact maintained C++20 implementation
in the actual `src/FunctionChainController.cpp`, sharing the existing
true controller/list/node/allocator owner objects.

## Whole scheduler ownership and precise native source correction

The complete native method handles a real nullable node. If non-null,
it searches the actual `update_chain` intrusive links and, only if
missing, the `draw_chain`. A missing link returns without removal.
For a found link, if this link is the currently executing one,
the original advances the controller cursor via the native
`FunctionChainLink::next_value` method. It then detaches the link,
clears the actual node callback pointer and conditionally releases
the node through the real `process_allocator` if native owned bit 0
is set. The genuine caller is the separate original
`FunctionChainController::remove` and scheduler teardown paths.

The previous full C++ source emitted **156B / 52 instructions**.
Its tail had a compiler NOP at native `+0x95`, but the actual
original directly writes **zero to the by-value parameter slot
`dword ptr [ebp+8]`**, precisely after release in the
owned-node branch. This is an independently observed real original
write, not a fabricated compiler-shaping local.
The natural correct C++:
`if (node->flags.bits & 1u) {
    process_allocator->release_object(node);
    node = nullptr;
}`
emits native `mov dword ptr[ebp+8],0`, using original
branch-local lifetime. Moving the nulling outside the release
branch or splitting it into another scope produces **163B** and
a spurious NOP; those variants are rejected.
The genuine branch-scoped form matches **162/162 original bytes,
52/52 original instructions** without manual NOPs, assembly,
synthetic return or shortened prefix.

## Independently observed original reference fields

A fresh direct decode of original native E8 operands and the
immutable PE `.reloc` HIGHLOW table attests:

| Original field offset | Type | Original native destination |
| --- | --- | --- |
| `+0x25` | REL32 | `0x00411E70`, real update-chain search |
| `+0x43` | REL32 | `0x00411E70`, real draw-chain search |
| `+0x60` | REL32 | `0x0040FF90`, native next-link value |
| `+0x6D` | REL32 | `0x00411CE0`, real intrusive detach |
| `+0x8C` | DIR32 | `0x005B8894`, actual process allocator |
| `+0x91` | REL32 | `0x004118A0`, native node release |

Every **6/6 original position/type/target** agrees with
the real compiled COFF relocation and existing independent
native canonical destinations. Full original PE SHA and fields:
`.analysis/core387-original-full-chain-remove-refs.json`.
Pinned compiler for this owner: MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc /Gd`.

## Strict smallest affected source-provider regression

Only `src/FunctionChainController.cpp`'s actual branch was edited,
without public header or owner layout changes.
The original locked `build/core142-canonical/FunctionChainController.obj`
was rebuilt with precisely that source selected. Its **14 preexisting
strict units plus new complete 162B unit** all pass unchanged
original-target verification: **15/15 strict units in one cold object**,
including the original 611B scheduler update and 587B scheduler draw
contributions, and the genuine node destroy/release methods.
Complete focused log: `.analysis/core387-function-chain-replay.log`.
No unfiltered whole-repository cold replay occurred.

This checkpoint credits exactly one new original game-owned
162B function, not the already exact scheduler methods or the
whole game's worker/thread lifetime and executable linkage.
