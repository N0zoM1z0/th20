#include "EnemyStateMeshOpcode.hpp"
#include "EnemyState.hpp"
#include "RenderMesh.hpp"
#include "DiagnosticAllocator.hpp"

namespace th20 {

extern const float native_screen_top_16_56cd90;
extern const float native_zero_56e0e8;

bool execute_enemy_mesh_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 621)
        return false;

    process_allocator->release_object(state.mesh);
    state.mesh = nullptr;
    state.mesh = process_allocator->allocate_object<EnemyMeshOwner>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\ecl.cpp:2387 EnemyDataInf::BossRenderInf");

    auto& mesh = *state.mesh;
    mesh.mesh = nullptr;
    mesh.radius = state.float_argument(0);
    mesh.current_radius = native_screen_top_16_56cd90;
    mesh.color = static_cast<std::uint32_t>(state.integer_argument(1));
    mesh.phase_x = 0.0f;
    mesh.phase_y = 0.0f;

    if (mesh.radius > native_zero_56e0e8) {
        mesh.mesh = process_allocator->allocate_object<RenderMesh>(
            "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\ecl.cpp:2395 RenderMeshInf",
            17, 17, 0, static_cast<std::int32_t>(state.field_2e8));
    }
    return true;
}

} // namespace th20
