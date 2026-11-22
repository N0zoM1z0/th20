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

This is a source fragment, not a separate native function. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.

## Maintained root-host execution closure — CORE/RECON-1248

The maintained ASan/UBSan Enemy dispatcher host previously supplied a
false-returning execute_enemy_mesh_opcode test stub. CORE/RECON-1248 removes
that stub and links the production 621 helper, EnemyMeshOwner lifetime source,
and the actual MeshResourceAccess translation unit.

The test now exercises the real DiagnosticAllocator allocate_object and
release_object template paths, the real EnemyMeshOwner destructor, and the
real 213B signed-int RenderMesh allocator specialization. The renderer-bound
RenderMesh constructor/destructor and the not-yet-recovered process allocator
startup constructor remain explicit host fixtures: the constructor fixture
records the requested dimensions/surface/view, while the production helper
and owner allocation/release paths execute unchanged. The helper explicitly
narrows field_2e8 to int32 so its COFF call binds to the original
allocate_object<RenderMesh,int,int,int,int> ABI and the already exact
MeshResourceAccess instantiation, rather than emitting an unowned unsigned
template specialization.

Root assertions cover positive radius (17x17, surface 0, selected view),
zero and negative radii (no RenderMesh allocation), replacement/destruction
of a previous owner, and two partial-failure boundaries: a float operand
exception leaves the freshly published default owner in place; an integer
color exception preserves the radius write but skips RenderMesh allocation.
The same root build now links the actual MeshResourceAccess short
AnimationFile::spawn wrapper; its full 922B renderer/VM producer remains a
capture-only test boundary.

The root verifier runs the immutable native 621 audit on every pass:
**346 bytes / 70 x86 instructions / 7 ordered E8 calls**, both diagnostic
strings and the original 16.0f/0.0f constants. It also checks all seven
ordered natural-C++ COFF relocations and executes the production helper under
ASan/UBSan. Affected-only exact replays passed EnemyMesh.cpp **7/7**,
MeshInterfaces.cpp **10/10**, and MeshResourceAccess.cpp **8/8**. The
maintained verifier compiles **32** locked-profile i386 COFF units. No full
cold replay, whole-parent exactness or 41,967B parent byte credit is claimed.
