#include "Vector2.hpp"
namespace th20 {
extern const float native_spawn_width_640;
extern const float native_spawn_height_480;
void __cdecl normalize_coordinates_438eb0(Vector2* output,const Vector2* input) {
    output->x=input->x/native_spawn_width_640;
    output->y=input->y/native_spawn_height_480;
    if(output->x<0.0f) output->x=0.0f;
    if(output->y<0.0f) output->y=0.0f;
}
}
