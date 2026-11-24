# TH20 reconstruction focus lock

- Repository: th20
- Target identity: target:th20-main
- Current function: StageResourceOwner::draw_objects_for_layer
- Target entry: 0x00474880
- Expected target extent: 1119 bytes
- Source: src/StageResourceObjectDraw.cpp

## Focus rule

Do not select or begin reconstructing another function until this function has a fresh Factory replay receipt with receipt_verdict=pass and acceptance_decision=accepted. A local byte comparison, matching section size, or semantic test is not a substitute for that gate.

## Current reconstruction state

The boss is restored as natural C++: the inline-animation prelude, render-state transitions, instance/object traversal, viewport culling, object-space Y rotation, sprite-relative scale, animation-pool submissions, instance visibility bit, and render counters are all represented directly in source.

The primitive stream advance is a separate natural C++ cdecl helper at 0x00471160, returning primitive plus signed size. Its 11-byte contribution is independently replayed exactly and its call relocation is included in the boss comparison. The instance visibility bit is represented as a one-bit C++ bitfield sharing the native 16-bit flags word.

## Local verification

- Pinned MSVC 19.44.35211 i386 COFF build.
- stage_resource_object_draw_layer: 1119/1119 bytes exact after replaying all 48 native relocations.
- stage_resource_primitive_advance: 11/11 bytes exact, no relocations.
- Original PE vs maintained C++ StageResource CPU oracle: 47,750 checks, 0 failures. The test harness routes source-side D3DX calls through the same deterministic test seams used for the native PE import slots.

These are local strict-COFF and semantic-oracle results. They do not, by themselves, establish Factory acceptance.

## Remaining acceptance gate

The registered Factory adapter currently exposes only the imported boundary claim for 0x00474880; it has not imported source-present or codegen-exact claims for this function. Submit and obtain the fresh Factory-controlled replay receipt, then verify both receipt_verdict=pass and acceptance_decision=accepted. Keep this focus lock in place until that happens.
