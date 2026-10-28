// Whole native BulletController firing path, including shared ownership,
// signed row/column traversal, early-stop status and positional sound.
#include "Bullet.hpp"
#include "Player.hpp"
#include "SoundInf.hpp"
namespace th20 {
int BulletController::fire(const ShotParameters& params, std::shared_ptr<ShotMetadata> metadata) {
    float base_angle = context->player()->direction_to(params.position);
    for (int row = 0; row < params.rows; ++row) {
        for (int col = 0; col < params.count; ++col) {
            const int result=emit(params, metadata, col, row, base_angle);
            if (result != 0) {
                if (result == 1) goto finished;
                else if (result == -1) continue;
            }
        }
    }
finished:
    if (metadata.get()->sound >= 0)
        process_sound.request_effect_at(metadata.get()->sound, params.position.x);
    return 0;
}
}
