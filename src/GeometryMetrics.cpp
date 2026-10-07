#include "CollisionGeometry.hpp"
#include "ScalarMath.hpp"
namespace th20 {
namespace geometry {
float squared_norm_xy(float x, float y) { return x*x + y*y; }
float norm_xy(float x, float y) { return scalar_math::square_root(squared_norm_xy(x,y)); }
float squared_distance_xy(float x1, float x2, float y1, float y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}
float distance_xy(float x1, float x2, float y1, float y2) {
    return scalar_math::square_root(squared_distance_xy(x1,x2,y1,y2));
}
float squared_distance_xy(const Vector3& first, const Vector3& second) {
    return (first.x-second.x)*(first.x-second.x) + (first.y-second.y)*(first.y-second.y);
}
float distance_xy(const Vector3& first, const Vector3& second) {
    return scalar_math::square_root(squared_distance_xy(first,second));
}
int line_parameters(float& slope, float& intercept, float ax,float ay,float bx,float by) {
    if (absolute(bx-ax) < 0.01f) {
        slope=0.0f;
        intercept=ax;
        return 1;
    }
    slope=(by-ay)/(bx-ax);
    intercept=ay-(by-ay)*ax/(bx-ax);
    return 0;
}
}
}
