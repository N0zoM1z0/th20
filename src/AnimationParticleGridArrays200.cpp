#include "NativeParticleGridGroup.hpp"
#include <memory>
namespace th20 {
void construct200_color(std::array<AnimationHandle,200>& arr){std::construct_at(&arr);}
void construct200_vector3(std::array<Vector3,200>& arr){std::construct_at(&arr);}
}
