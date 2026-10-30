// Complete original 520B/149-i386 64-point trail ribbon AnimationCallback
// update Boss. Real Timer<64 gate, alpha fade of previous colors, RNG
// radial point generation, cumulative Vector2 position and bounded angle.
// Lexical if/else state paths naturally emit the original final branches.
#include "NativeRibbonTrailGroup.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include "Vector3.hpp"
#include "Cursor.hpp"
#include "Angle.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_five, native_four;
struct ColorChannels { unsigned char r,g,b,a; };
struct NativeRibbonGate { std::int32_t changed_45d030(); };
std::int32_t NativeRibbonTrailGroup::update() {
    if (timer_30c.less_than(64)) {
        if (reinterpret_cast<NativeRibbonGate*>(&timer_30c)->changed_45d030()) {
            std::int32_t count = static_cast<std::int32_t>(timer_30c);
            for (std::int32_t index=0;index<count;++index) {
                if ((reinterpret_cast<ColorChannels*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->a) >= 16) {
                    std::uint8_t* const alpha = reinterpret_cast<std::uint8_t*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))+3;
                    *alpha-=16;
                } else {
                    reinterpret_cast<ColorChannels*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->a=0;
                }
            }
            float radius = native_polygon_random_5ba4c4.unit()*native_five + native_four;
            float direction=angle_308;
            Vector2* const point = &vertices_08[count];
            polar(*reinterpret_cast<Vector3*>(point), direction, radius);
            if (count>0) {
                (void)(vertices_08[count] += vertices_08[count-1]);
            }
            angle_308=add_angles(angle_308,native_polygon_random_5ba4c4.radians()/native_five);
        }
    } else {
        return 1;
    }
    timer_30c++;
    return 0;
}
}
