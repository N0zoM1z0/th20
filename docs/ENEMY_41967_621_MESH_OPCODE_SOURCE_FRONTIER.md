# CORE/RECON-1151 — natural-C++ source for Enemy ECL opcode 621 mesh owner lifecycle

The maintained source now contains `execute_enemy_mesh_opcode(EnemyState&, opcode)` in `src/EnemyStateMeshOpcode.cpp` for original opcode 621. This is an inline case region inside the **41,967-byte** `EnemyState::execute_opcode()` Boss, not a standalone original function.

## Original native case proof

The immutable Japanese TH20 1.00a Steamless PE branch is `0x00495A9A..0x00495BF4`: **346 bytes / 70 x86 instructions / 7 direct E8 calls**, SHA-256 `d67fb1c10517cb0b3f45d27f2347427d8680935751b62a62ac5e18fc00756f6e`. `scripts/verify-enemy-mesh-opcode-source.py` extracts the original bytes directly from the locked PE, disassembles them, and checks every original E8 site/target pair.

The native branch uses these exact original allocator labels and constants:

- `0x0056FEE8`: `ecl.cpp:2387 EnemyDataInf::BossRenderInf`
- `0x0056FF38`: `ecl.cpp:2395 RenderMeshInf`
- `0x0056CD90`: `16.0f` initial current radius
- `0x0056E0E8`: `0.0f` strict radius threshold

## Restored owner and render-mesh behavior

1. Release the previous `EnemyMeshOwner` through the real process `DiagnosticAllocator`, then publish null to `EnemyState::mesh`.
2. Allocate a fresh `EnemyMeshOwner` with the original `BossRenderInf` diagnostic label and publish it.
3. Explicitly set its `RenderMesh*` member to null, read float operand 0 into `radius`, set `current_radius` to the original 16.0f constant, and read integer operand 1 into the color word.
4. Assign zero to both real `Angle` phase members through their typed operators.
5. Only when `radius > 0.0f`, allocate a real `RenderMesh` with the original `RenderMeshInf` label, 17 columns, 17 rows, surface 0, and the EnemyState view index; store it in the owner.

The implementation reuses the already exact 97B `DiagnosticAllocator::release_object<EnemyMeshOwner>`, 82B `allocate_object<EnemyMeshOwner>`, 213B `allocate_object<RenderMesh,int,int,int,int>`, and the existing 88B `EnemyMeshOwner` construction / 36B `RenderMesh` type. It does not invent a mesh owner, a renderer global, or an allocator boundary.

## Scoped verification and exactness boundary

`src/EnemyStateMeshOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. The focused original-PE verifier checks the entire 346B branch, 70 instruction heads, all seven E8 destinations, both original diagnostic labels, both original float constants, and the C++ source mutation/call order.

This is a source fragment, not a separate native function. No `config/functions.csv` mapping or parent byte credit is added. The original 41,967B Enemy dispatcher remains **SOURCE-ABSENT, NONEXACT**. No full cold replay was performed.
