// Scene transitions of the Graphics owner (original game/mother.cpp).
#include <mutex>

#include "EclDiagnostic.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "ArchiveOwner.hpp"
#include "DiagnosticAllocator.hpp"
#include "GameController.hpp"
#include "GraphicsPasses.hpp"
#include "InputInf.hpp"
#include "Graphics.hpp"
#include "LockRegistry.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include "TaskInfo.hpp"
#include "WindowState.hpp"
#include "Worker.hpp"

namespace th20 {

extern GameController* current_game_controller;

// Scene task owners released when the game returns to the title or quits.
extern void* native_scene_task_5c4d24;
extern void* native_scene_task_5c4d28;
extern void* native_scene_task_5c4d2c;
extern void* native_scene_task_5c49e8;
extern void* native_scene_task_5c5b38;
extern void* native_scene_task_5c60b8;
extern void* native_scene_task_5c60fc;
extern void* native_scene_task_5c6114;
extern void* native_scene_task_5c6124;
extern std::int32_t native_stage_entry_mode_5c6128;

void release_scene_task_4217c0(void* task);
void destroy_game_controller_4bd3d0(GameController* controller);
void create_game_controller_4bec70(std::int32_t restart_mode);
void create_stage_scene_52cfe0();
void create_ending_scene_4a1010();
TaskInfo* create_title_scene_4d85c0();
void release_resources_49deb0(std::int32_t value);
void release_resources_534110(std::int32_t value);

extern InputInf* process_input_inf;

// Non-owning views of per-frame members still under review.
struct NativeSceneSound : SoundInf {
    std::int32_t update_4277f0();
    void update_streams_4d9710();
};
struct NativeSceneInput : InputInf {
    void poll_41fe80();
};
struct NativeScenePool : AnimationPoolOwner {
    std::int32_t update_44dfb0();
    void release_vertex_buffer_4dab40();
};
struct NativeTickGraphicsView : Graphics {
    void bail_out_4d9e30();
};
extern void* native_scene_task_5c4a00;

// Non-owning PlayerTable view for two members still under review.
struct NativeScenePlayerTable : PlayerTable {
    std::int32_t selection_4bd5c0();
    void select_card_table_4dd8d0();
};

void Graphics::release_scenes_4dd730() {
    session.set_flag0(0);
    session.set_flag1(0);
    if (process_graphics.flags.bits5_6 == 0) {
        process_graphics.flags.bits5_6 = 1;
    }
    release_scene_task_4217c0(native_scene_task_5c4d28);
    release_scene_task_4217c0(native_scene_task_5c60b8);
    destroy_game_controller_4bd3d0(current_game_controller);
    release_scene_task_4217c0(native_scene_task_5c6124);
    release_scene_task_4217c0(native_scene_task_5c4d2c);
    release_scene_task_4217c0(native_scene_task_5c49e8);
    release_scene_task_4217c0(native_scene_task_5c60fc);
    release_resources_49deb0(0);
    release_resources_534110(0);
    release_scene_task_4217c0(native_scene_task_5c4d24);
    release_scene_task_4217c0(native_scene_task_5c5b38);
    release_scene_task_4217c0(native_scene_task_5c6114);
}

// Applies a pending scene change under lock slot 5. Returns 4 after a
// failed title start or an explicit quit (scene 3), 5 for scene 17 and 1
// otherwise.
std::int32_t Graphics::update_scene_4da540() {
    if (field_b08 != field_b0c) {
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(5));
        field_b10 = field_b08;
        ecl_diagnostic_hint("scene %d -> %d\r\n", field_b08, field_b0c);
        clear_color = 0xFF000000;
        switch (field_b0c) {
        case 0: {
            field_b0c = 1;
            TaskInfo* scene = create_title_scene_4d85c0();
            startup_scene = scene;
            if (scene == nullptr) {
                field_b0c = 3;
                goto release_and_quit;
            }
            break;
        }
        case 4:
            switch (field_b08) {
            case 1:
            case 2:
                create_stage_scene_52cfe0();
                break;
            case 7:
                destroy_game_controller_4bd3d0(current_game_controller);
                create_stage_scene_52cfe0();
                break;
            case 15:
                release_scene_task_4217c0(native_scene_task_5c49e8);
                create_stage_scene_52cfe0();
                break;
            }
            break;
        case 16:
            switch (field_b08) {
            case 7:
                destroy_game_controller_4bd3d0(current_game_controller);
                field_b0c = 4;
                native_stage_entry_mode_5c6128 = 3;
                create_stage_scene_52cfe0();
                break;
            case 15:
                release_scene_task_4217c0(native_scene_task_5c49e8);
            case 2:
                field_b0c = 4;
                native_stage_entry_mode_5c6128 = 3;
                create_stage_scene_52cfe0();
                break;
            }
            break;
        case 7:
            switch (field_b08) {
            case 4:
                release_scene_task_4217c0(native_scene_task_5c6124);
            }
            field_b18 = 1;
            create_game_controller_4bec70(0);
            break;
        case 13:
            switch (field_b08) {
            case 4:
                release_scene_task_4217c0(native_scene_task_5c6124);
            }
            field_b0c = 7;
            field_b18 = 1;
            create_game_controller_4bec70(1);
            break;
        case 12: {
            std::int32_t restart_mode = current_game_controller->restart();
            field_b18 = 0;
            switch (field_b08) {
            case 7:
                destroy_game_controller_4bd3d0(current_game_controller);
            }
            field_b0c = 7;
            create_game_controller_4bec70(restart_mode);
            break;
        }
        case 10:
            destroy_game_controller_4bd3d0(current_game_controller);
            field_b0c = 7;
            field_b18 = 1;
            field_b1c = 0;
            static_cast<NativeScenePlayerTable&>(player_table()).select_card_table_4dd8d0();
            create_game_controller_4bec70(0);
            break;
        case 24:
            if (player_table().clamped_field_1f4() !=
                static_cast<NativeScenePlayerTable&>(player_table()).selection_4bd5c0()) {
                field_b0c = 7;
            }
            destroy_game_controller_4bd3d0(current_game_controller);
            if (player_table().clamped_field_1f4() ==
                static_cast<NativeScenePlayerTable&>(player_table()).selection_4bd5c0()) {
                field_b0c = 7;
            }
            field_b18 = 1;
            field_b1c = 0;
            static_cast<NativeScenePlayerTable&>(player_table()).select_card_table_4dd8d0();
            create_game_controller_4bec70(0);
            break;
        case 22:
            destroy_game_controller_4bd3d0(current_game_controller);
            field_b0c = 7;
            static_cast<NativeScenePlayerTable&>(player_table()).select_card_table_4dd8d0();
            create_game_controller_4bec70(0);
            break;
        case 11:
            destroy_game_controller_4bd3d0(current_game_controller);
            field_b18 = 1;
            field_b1c = 0;
            field_b0c = 7;
            static_cast<NativeScenePlayerTable&>(player_table()).select_card_table_4dd8d0();
            create_game_controller_4bec70(1);
            break;
        case 19:
            destroy_game_controller_4bd3d0(current_game_controller);
            field_b18 = 1;
            field_b1c = 1;
            field_b0c = 7;
            static_cast<NativeScenePlayerTable&>(player_table()).select_card_table_4dd8d0();
            create_game_controller_4bec70(0);
            break;
        case 14:
            destroy_game_controller_4bd3d0(current_game_controller);
            field_b18 = 1;
            field_b0c = 7;
            create_game_controller_4bec70(0);
            break;
        case 15:
            switch (field_b08) {
            case 7:
                destroy_game_controller_4bd3d0(current_game_controller);
            }
            create_ending_scene_4a1010();
            break;
        case 3:
        release_and_quit:
            release_scenes_4dd730();
            return 4;
        case 17:
            release_scenes_4dd730();
            return 5;
        }
        field_b08 = field_b0c;
    }
    return 1;
}

bool Worker::joinable() const {
    return thread_.joinable();
}

// Graphics update node: requests scene 3 once a pending shutdown has no
// running worker, steps sound and input, and applies scene changes. Returns
// 4 to stop the frame loop.
std::int32_t __cdecl graphics_update_4dc510(void* graphics) {
    if (static_cast<Graphics*>(graphics)->flags.bits5_6 == 1 &&
        !static_cast<Graphics*>(graphics)->worker_0.joinable()) {
        process_graphics.set_next_scene_4be250(3);
    }
    static_cast<NativeSceneSound&>(process_sound).update_4277f0();
    static_cast<NativeSceneSound&>(process_sound).update_streams_4d9710();
    static_cast<NativeSceneInput*>(process_input_inf)->poll_41fe80();
    if (static_cast<NativeScenePool*>(current_animation_pool)->update_44dfb0() != 0) {
        return 4;
    }
    if (window_state.reset_delay_value() != 0) {
        window_state.add_reset_delay(-1);
    }
    // The native evaluates the delay once more as part of this condition.
    if (window_state.reset_delay_value(), static_cast<Graphics*>(graphics)->field_db0 != 0) {
        if (static_cast<Graphics*>(graphics)->field_db0 == 2) {
            return 4;
        }
        return 1;
    }
    std::int32_t result = static_cast<Graphics*>(graphics)->update_scene_4da540();
    if (result != 1) {
        return result;
    }
    return 1;
}

// Process shutdown of the Graphics owner: drains the sound queue, stops both
// workers, releases the version data, scenes, vertex buffer, music, archive
// and the five surface sprites.
std::int32_t shutdown_graphics_4dd490() {
    ecl_diagnostic_hint("shutdown MotherInf\n");
    while (static_cast<NativeSceneSound&>(process_sound).update_4277f0() != 0) {
    }
    process_graphics.worker_1.close_and_join();
    static_cast<NativeTickGraphicsView&>(process_graphics).bail_out_4d9e30();
    if (process_graphics.dynamic_buffer != nullptr) {
        TH20_RELEASE_BYTES_AND_RESET(process_graphics.dynamic_buffer);
        process_graphics.dynamic_buffer = nullptr;
    }
    process_graphics.release_scenes_4dd730();
    release_scene_task_4217c0(native_scene_task_5c4a00);
    release_scene_task_4217c0(process_input_inf);
    ecl_diagnostic_hint("VertexBuffer delete\n");
    static_cast<NativeScenePool*>(current_animation_pool)->release_vertex_buffer_4dab40();
    ecl_diagnostic_hint("Sound Stop\n");
    process_sound.enqueue(4, 0, "dummy");
    archive_owner.close();
    process_allocator->release_object(process_graphics.surface_sprite_0);
    process_graphics.surface_sprite_0 = nullptr;
    process_allocator->release_object(process_graphics.surface_sprite_1);
    process_graphics.surface_sprite_1 = nullptr;
    process_allocator->release_object(process_graphics.surface_sprite_2);
    process_graphics.surface_sprite_2 = nullptr;
    process_allocator->release_object(process_graphics.surface_sprite_3);
    process_graphics.surface_sprite_3 = nullptr;
    process_allocator->release_object(process_graphics.surface_sprite_4);
    process_graphics.surface_sprite_4 = nullptr;
    return 0;
}

} // namespace th20
