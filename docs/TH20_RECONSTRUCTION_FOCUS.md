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

The primitive stream advance is a separate natural C++ cdecl helper at 0x00471160, returning primitive plus signed size. Its 11-byte contribution is independently replayed exactly and its call relocation is included in the boss comparison. The instance visibility bit is represented as a one-bit C++ bitfield sharing the native 16-bit flags word. The object layer byte now has explicit signed and unsigned C++ union views, and the draw boss reads the signed layer view required by native MOVSX. The object flag byte likewise has signed and unsigned views: the draw boss uses the signed view required by the native MOVSX/OR sequence, while other object logic retains its unsigned flag view. The script state's formerly raw owner+0x32c4 cull-distance read is now a standard C++ typed overlay at StageBackgroundScriptScalars::cull_distance_squared, statically anchored at script-state+0x32b4 (owner+0x32c4). The 17-word storage view remains available to existing VM code. The object's formerly raw +0x0c rotation parameter is now StageResourceObjectParameters::rotation_y, overlaid with the existing eleven-float parameter array. Both typed overlays preserve record layout and exact codegen.

## Local verification

- Pinned MSVC 19.44.35211 i386 COFF build.
- stage_resource_object_draw_layer: 1119/1119 bytes exact, 48/48 native relocations, no first differences. Pinned COFF object SHA-256: d2b1beda1fcfbef4ad45b8de3f48054ac60ad1b1bd677890d63e3925b450dc07.
- stage_resource_primitive_advance: 11/11 bytes exact, no relocations.
- Original PE vs maintained C++ StageResource CPU oracle: 47,750 checks, 0 failures. The test harness routes source-side D3DX calls through the same deterministic test seams used for the native PE import slots.

These are local strict-COFF and semantic-oracle results. They do not, by themselves, establish Factory acceptance.

## Remaining acceptance gate

The registered Factory adapter currently exposes only the imported boundary claim for 0x00474880; it has not imported source-present or codegen-exact claims for this function. A replay submission using that boundary claim was attempted, but Factory returned that repository th20 is not registered with the configured replay worker. The Factory authority currently binds replay submission only to th04, th08, th09, th095, th10 and th105; the exposed tool set has no worker-registration operation. Until the Factory operator registers th20 and a fresh Factory-controlled replay returns receipt_verdict=pass plus acceptance_decision=accepted, keep this focus lock in place. The local strict replay and CPU differential results above remain valid but are not Factory acceptance.
