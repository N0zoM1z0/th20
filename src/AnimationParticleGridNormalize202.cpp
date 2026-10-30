#include "Vector3.hpp"
#include "CollisionGeometry.hpp"
#include "ScalarMath.hpp"
namespace th20 {
extern const float native_0_01;
void normalize_vector3_45cf10(Vector3& output, const Vector3& input) {
    float magnitude=scalar_math::square_root(input.x*input.x + input.y*input.y + input.z*input.z);
    if (geometry::absolute(magnitude) < native_0_01) {
        output = input;
    } else {
        output.x = input.x / magnitude;
        output.y = input.y / magnitude;
        output.z = input.z / magnitude;
    }
}
}
