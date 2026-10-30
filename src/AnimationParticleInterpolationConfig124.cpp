#include "Interpolation.hpp"
namespace th20 {
struct NativeVectorInterpolationConfigView : VectorInterpolation {
    void configure_45d190(std::int32_t duration_value, std::int32_t mode_value,
        const Vector3& from, const Vector3& to,
        const Vector3& tangent_first, const Vector3& tangent_last);
};
static_assert(sizeof(NativeVectorInterpolationConfigView)==84);
void NativeVectorInterpolationConfigView::configure_45d190(
        std::int32_t duration_value, std::int32_t mode_value,
        const Vector3& from, const Vector3& to,
        const Vector3& tangent_first, const Vector3& tangent_last) {
    set_duration(duration_value);
    set_mode(mode_value);
    set_start(from);
    set_end(to);
    set_tangent_start(tangent_first);
    set_tangent_end(tangent_last);
    current = from;
    timer = 0;
}
}
