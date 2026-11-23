# Stage Background update, mesh deformation and object traversal

## Native owner chain

The stage frame owner enters `0x00472100` (473 bytes). The native body is a game-owned Background update, not a generic frame helper. It gates on owner state bits and the fade Timer, clears the three camera points and final vector, computes and normalizes the camera direction, sets the Background overlay color, conditionally updates objects and runs the `0x004751B0` stage VM, publishes the camera to `Graphics::viewports[3]` at `0x005C53FC`, updates the eight inline Animation records, calls the mesh updater on the Background subobject at owner `+0x10`, and increments the frame count. All early-return paths return `1`.

The mesh updater is `0x004722E0` (1,375 bytes). It owns two independent mesh slots at Background `fields_3294[9]` and `[10]`. Each non-null slot is processed only for mesh modes 1 and 2. The object updater is `0x004739E0` (305 bytes), called with the enclosing StageResource owner. It walks the file object count and object-pointer table, then follows each object's variable-length primitive stream until a negative primitive-type sentinel.

The adjacent 42-byte leaf at `0x00474DD0` is represented as `Animation::is_active()`: the original predicate tests whether `AnimationBase::field_28` is nonnegative. The source restores its behavior but deliberately leaves authored-versus-compiler origin unresolved.

## Natural C++ reconstruction

- `src/StageResourceUpdate.cpp` restores the parent owner update, its fade/flag gates, camera reset and normalization, object/VM dispatch, viewport publication, eight Animation updates, mesh dispatch and frame counter.
- `src/StageResourceMeshUpdate.cpp` restores the two-slot mesh deformation boss. It initializes each real `RenderMesh` with the native rectangle, writes alpha `0xC0`, applies sine displacement only to interior vertices, clears the deformed vertex and position Z lanes, advances X phase by `pi / 4.7` per row and Y phase by `pi / 2.1` per column, advances the stored phases by `pi / 64` and `pi / 80`, and ticks the mode-2 Timer.
- `src/StageResourceObjectUpdate.cpp` restores variable-size primitive traversal, animation-pool forwarding, active-primitive counting, object-flag clearing and the state-bit-controlled angular-velocity update.
- `src/AnimationIsActive.cpp` restores the small Animation state predicate used by the object updater.
- `src/StageResource.hpp` now names the 0x30-byte object record and 8-byte primitive header with offset assertions.

The relevant original constants were checked at their actual PE addresses: amplitude `0x56F7B4 = 24.0f`, row divisor `0x56FA24 = 4.7f`, column divisor `0x56FA20 = 2.1f`, phase-frame divisors `0x56FA28 = 64.0f` and `0x56FA30 = 80.0f`, origin X `0x56FA6C = -192.0f`, mesh widths/heights `0x56CDA4 = 384.0f`, `0x56CD98 = 128.0f`, and `0x56D7C0 = 448.0f`. In particular, the `2.1f` divisor is not `2.1088f`; using the latter produces a visible Y displacement mismatch.

## Origin boundary

`0x00472100`, `0x004722E0` and `0x004739E0` are classified as authored StageResource behavior. Their original control flow is tied to the game's Background owner, stage VM, mesh modes, object records, Animation pool and Graphics viewport state. The source class spellings are reconstruction names; this classification does not claim original PDB/RTTI names.

`0x00474DD0` remains origin-unknown. Its semantic predicate is restored, but a short member query alone is insufficient to decide whether the standalone native body came from hand-authored code or a compiler-emitted accessor. The primitive pointer-advance helper at `0x00471160` and the Angle subtraction wrapper at `0x00472060` also remain outside this authored-origin claim.

## Focused original-PE differential

Run `scripts/repo-python scripts/run-stage-resource-vm-cpu.py`. The current result is **45,510 checks, 0 failures**. The 45,480 existing VM/camera/interpolation/opcode checks are retained. The extension adds 18 parent-update cases (six fade/flag combinations, three consecutive ticks) and 12 object-update cases. The parent fixture covers both mesh modes with two live 3x3 grids; the object fixtures cover object counts 1 through 3, 12-byte and 16-byte primitive advances, 8-byte records, negative sentinels, active/inactive Animation states, NaN/zero/nonzero angular rates and the rotation-lock bit.

The mesh oracle deliberately patches original `RenderMesh::initialize` (`0x0049D850`) to return immediately so it isolates the deformation body. Production C++ still calls the real `RenderMesh::initialize`; that 503-byte function has its own existing strict exact reconstruction. The oracle therefore does not claim fresh initialization, mesh allocation/destruction, positive ANM rebinding, the nontrivial 39KB `Animation::update` path, full stage rendering or byte-exactness for these three large bosses. The semantic CPU comparison is evidence for the restored behavior only.
