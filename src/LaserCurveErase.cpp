#include "LaserCurveInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "Context.hpp"

namespace th20 {

std::int32_t LaserCurveInf::erase(std::int32_t, std::int32_t argument) {
    if (argument!=0) {
        if (field_6cc!=0) return 0;
    }

    std::int32_t result=0;
    Vector3 position;
    LaserCurvePathPoint* point=point_data;
    for (std::int32_t index=0;
         index<static_cast<std::int32_t>(parameters.count); ++index) {
        position=point->position;
        if (index%3==0) {
            context->bullet_controller()->animation_file()->spawn(
                "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                position,0.0f,-1,nullptr);
        }
        ++point;
    }
    state=1;
    return 0;
}

} // namespace th20
