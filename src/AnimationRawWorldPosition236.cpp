#include "Animation.hpp"
#include "MotionMath.hpp"
namespace th20 {
struct NativeAnimationRawPositionView : Animation {
    Vector3& raw_position_44cb80(Vector3& output);
};
Vector3& NativeAnimationRawPositionView::raw_position_44cb80(Vector3& output) {
    output=vector_5bc + base.vector_2c + base.vector_484;
    if (parent_558 && !((base.flags.word_04 >> 12) & 1u)) {
        if ((base.flags.word_04 >> 5) & 1u) {
            rotate_xy(output,output,parent_558->rotation_z_value());
        }
        Vector3 parent_position;
        reinterpret_cast<NativeAnimationRawPositionView*>(parent_558)->raw_position_44cb80(parent_position);
        output+=parent_position;
    }
    return output;
}
}
