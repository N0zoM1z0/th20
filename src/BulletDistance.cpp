#include "BulletDistance.hpp"
#include "RenderMesh.hpp"

namespace th20 {
// The original 122B gameplay predicate constructs and copies the complete
// Vector3 difference but compares XY squared distance against radius squared.
std::int32_t bullet_distance_within(const Vector3& first,
                                    const Vector3& second, float radius) {
    Vector3 difference;
    difference = first - second;
    return squared_norm_xy(difference) <= radius * radius;
}
} // namespace th20
