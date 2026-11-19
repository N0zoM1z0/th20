#include "Animation.hpp"
#include "MotionMath.hpp"

namespace th20 {

Vector3& Animation::world_position_for_spawn(Vector3& output) {
    output=vector_5bc+base.vector_2c+base.vector_484;
    if(parent_558 && !((base.flags.word_04>>12)&1u)) {
        if((base.flags.word_04>>5)&1u)
            rotate_xy(output,output,parent_558->rotation_z_value());
        Vector3 parent_position;
        parent_558->world_position_for_spawn(parent_position);
        output+=parent_position;
    }
    return output;
}

} // namespace th20
