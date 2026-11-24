# TH20 reconstruction focus lock

- Repository: `th20`
- Target identity: `target:th20-main`
- Current function: `StageResourceOwner::draw_objects_for_layer`
- Target entry: `0x00474880`
- Expected target extent: `1119` bytes
- Source: `src/StageResourceObjectDraw.cpp`

## Focus rule

Do not select or begin reconstructing another function until this function has a fresh canonical replay receipt with `receipt_verdict=pass` and `acceptance_decision=accepted`. A matching section size or a local compile is not exactness.

## Current state

The source models the owner loop, object visibility/culling, primitive transform dispatch, animation state updates, fog/depth-write transitions, draw calls, and render counters in C++. The primitive-advance dependency at `0x00471160` is currently represented as a member-style `StageResourcePrimitiveHeader::advance(size)` call so the x86 call ABI can be compared against the target call site. Its exact signature/relocation remains subject to the target-attested comparison.

An earlier local COFF build was `1126` bytes against the `1119`-byte target extent. The remaining seven-byte difference is being investigated at the primitive-advance call boundary; no exactness claim is made until the strict comparison and canonical replay both pass.

## Acceptance gate

1. Compile the current source with the repository's pinned MSVC profile.
2. Match all function bytes and relocations against `0x00474880`.
3. Submit only this function's replay claim.
4. Continue only after the Factory accepts the fresh receipt.
