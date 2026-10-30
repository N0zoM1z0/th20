// Two native game renderer math helpers, original whole 73B and 86B.
// 73B: natural three-component Euclidean norm then scalar sqrt wrapper.
// 86B: original 2D rotation with translation to caller's output record.
#include "AnimationProjectionMath.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "ScalarMath.hpp"

namespace th20 {
float animation_vector3_length(const Vector3& vector) {
    return scalar_math::square_root(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

void AnimationDrawDetailedOwner::transform_projected_xy(Vector2* output,
        float x, float y, float sine, float cosine, float tx, float ty) {
    output->x = x * cosine - y * sine + tx;
    output->y = x * sine + y * cosine + ty;
}
}
