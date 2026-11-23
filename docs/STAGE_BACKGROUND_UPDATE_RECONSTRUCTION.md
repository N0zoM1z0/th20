# Stage Background update, mesh deformation and object traversal

## Native owner chain

The stage frame owner enters `0x00472100` (473 bytes). The native body is a game-owned Background update, not a generic frame helper. It gates on owner state bits and the fade Timer, clears the three camera points and final vector, computes and normalizes the camera direction, sets the Background overlay color, conditionally updates objects and runs the `0x004751B0` stage VM, publishes the camera to `Graphics::viewports[3]` at `0x005C53FC`, updates the eight inline Animation records, calls the mesh updater on the Background subobject at owner `+0x10`, and increments the frame count. All early-return paths return `1`.

The mesh updater is `0x004722E0` (1,375 bytes). It owns two independent mesh slots at Background `fields_3294[9]` and `[10]`. Each non-null slot is processed only for mesh modes 1 and 2. The object updater is `0x004739E0` (305 bytes), called with the enclosing StageResource owner. It walks the file object count and object-pointer table, then follows each object's variable-length primitive stream until a negative primitive-type sentinel.

The adjacent 42-byte leaf at `0x00474DD0` is represented as `Animation::is_active()`: the original predicate tests whether `AnimationBase::field_28` is nonnegative. The source restores its behavior but deliberately leaves authored-versus-compiler origin unresolved.

Two more adjacent leaves are now restored. `0x00472840` fills a caller-provided 4x4 `Matrix4` with the identity matrix and returns that pointer; its implementation is `matrix_identity` in `src/Matrix4Identity.cpp`. `0x00472A10` clears bit zero of `AnimationBase::flags.byte_02` without changing the other flag bits; its implementation is `Animation::clear_flag_02` in `src/AnimationClearFlag02.cpp`. Both retain unknown origin because their short generic-looking bodies do not establish whether the original code was game-authored or emitted from a utility/accessor layer.

## Natural C++ reconstruction

- `src/StageResourceUpdate.cpp` restores the parent owner update, its fade/flag gates, camera reset and normalization, object/VM dispatch, viewport publication, eight Animation updates, mesh dispatch and frame counter.
- `src/StageResourceMeshUpdate.cpp` restores the two-slot mesh deformation boss. It initializes each real `RenderMesh` with the native rectangle, writes alpha `0xC0`, applies sine displacement only to interior vertices, clears the deformed vertex and position Z lanes, advances X phase by `pi / 4.7` per row and Y phase by `pi / 2.1` per column, advances the stored phases by `pi / 64` and `pi / 80`, and ticks the mode-2 Timer.
- `src/StageResourceObjectUpdate.cpp` restores variable-size primitive traversal, animation-pool forwarding, active-primitive counting, object-flag clearing and the state-bit-controlled angular-velocity update.
- src/RendererStageDrawReset.cpp restores the original 0x004750A0 AnimationPool post-stage-draw reset boss. It invokes the original reset leaves at 0x0041DB80, 0x00424080, 0x0041DBA0, 0x0041DB60, 0x0041DB40, 0x004240A0 and 0x0041DBC0 in native order, reproduces the four-field MFC CommonInit effect at 0x00475170, then resets the two large draw-cache words at 0x00475120, invalidates the owner byte at 0x00475150, and clears the scalar fields at +0xC8/+0xCC. The MFC routine is retained as a library boundary and receives no game-authored credit.
- src/StageResourceObjectVisibility.cpp restores the original 0x00473B20 object visibility boss as StageResourceObjectRecord::is_outside_viewport. The ECX receiver is the 0x30-byte StageResource object record, not an Animation: native +0x18 is the object-space center, +0x24 is the full bounds extent, and the raw DWORD at +0x04 bypasses the projected-bounds stage when nonzero (after the distance gate). The routine adds the per-instance translation, subtracts the Background camera center (vector_00 + vector_3c), rejects by squared distance, then samples the eight bounds corners plus the original eight center-plane points. It projects those 16 points with the current Viewport projection/view matrices and an instance-translation world matrix, ignores depths outside [0,1], and intersects their screen AABB against the fixed 640x480 stage rectangle with the original 8-pixel margin. Return 0 means visible; return 1 means outside.
- project_culling_vertices is the natural C++ D3DX Vec3ProjectArray equivalent used by the production culler. The focused oracle replaces only the original D3DXMatrixTranslation and D3DXVec3ProjectArray import slots with independent test implementations; the latter performs its own matrix products and clip-to-viewport transform rather than calling the production helper.
- `src/AnimationIsActive.cpp` restores the small Animation state predicate used by the object updater.
- `src/Matrix4Identity.cpp` restores the original 4x4 identity-matrix helper used before Y-axis object rotation.
- `src/AnimationClearFlag02.cpp` restores the isolated Animation flag-bit clear operation.
- `src/StageResource.hpp` now names the 0x30-byte object record and 8-byte primitive header with offset assertions.

The relevant original constants were checked at their actual PE addresses: amplitude `0x56F7B4 = 24.0f`, row divisor `0x56FA24 = 4.7f`, column divisor `0x56FA20 = 2.1f`, phase-frame divisors `0x56FA28 = 64.0f` and `0x56FA30 = 80.0f`, origin X `0x56FA6C = -192.0f`, mesh widths/heights `0x56CDA4 = 384.0f`, `0x56CD98 = 128.0f`, and `0x56D7C0 = 448.0f`. In particular, the `2.1f` divisor is not `2.1088f`; using the latter produces a visible Y displacement mismatch.

## Origin boundary

`0x00472100`, `0x004722E0` and `0x004739E0` are classified as authored StageResource behavior. Their original control flow is tied to the game's Background owner, stage VM, mesh modes, object records, Animation pool and Graphics viewport state. The source class spellings are reconstruction names; this classification does not claim original PDB/RTTI names.

`0x00474DD0`, `0x00472840` and `0x00472A10` remain origin-unknown. Their semantics are restored, but these short member/utility helpers alone are insufficient to decide whether the standalone native bodies came from hand-authored code or compiler-emitted accessors/utilities. The primitive pointer-advance helper at `0x00471160` and the Angle subtraction wrapper at `0x00472060` also remain outside this authored-origin claim.

## Focused original-PE differential

Run `scripts/repo-python scripts/run-stage-resource-vm-cpu.py`. The current result is **46,918 checks, 0 failures**. The 45,480 existing VM/camera/interpolation/opcode checks are retained. The extension adds 18 parent-update cases (six fade/flag combinations, three consecutive ticks), 12 object-update cases, 128 Matrix4 identity cases, 128 Animation flag-clear cases, 1,024 original object-visibility cases and 128 sparse-memory AnimationPool reset cases. The parent fixture covers both mesh modes with two live 3x3 grids; the object fixtures cover object counts 1 through 3, 12-byte and 16-byte primitive advances, 8-byte records, negative sentinels, active/inactive Animation states, NaN/zero/nonzero angular rates and the rotation-lock bit.

The two new leaf comparisons call original `0x00472840` and `0x00472A10` directly and compare both return values (where applicable) and complete affected object bytes.

## Next rendering frontier

The adjacent render-pass bosses `0x00472A30` (732 bytes) and `0x00472D10` (1,063 bytes) remain the next large targets. Both dispatch the shared `0x00474880` object-layer draw helper (1,119 bytes), which in turn uses the 5,993-byte `AnimationPoolOwner::draw` path. Several important dependencies are already independently reconstructed: `AnimationPoolOwner::flush_draws` at `0x004455C0` is strict exact, as are the Graphics fog transitions at `0x004DDA60`/`0x004DDAC0` and depth-write transitions at `0x004DDF80`/`0x004DDFE0`. The shared object-layer helper and the two pass state machines are not yet claimed as reconstructed; their D3D state ordering and object visibility/transform logic are the next investigation boundary.

The mesh oracle deliberately patches original `RenderMesh::initialize` (`0x0049D850`) to return immediately so it isolates the deformation body. Production C++ still calls the real `RenderMesh::initialize`; that 503-byte function has its own existing strict exact reconstruction. The oracle therefore does not claim fresh initialization, mesh allocation/destruction, positive ANM rebinding, the nontrivial 39KB `Animation::update` path, full stage rendering or byte-exactness for these three large bosses. The semantic CPU comparison is evidence for the restored behavior only.
