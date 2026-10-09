#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
void* Animation::allocate_geometry(std::int32_t bytes) {
    geometry_bytes=bytes;
    geometry=process_allocator->allocate_bytes(bytes,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.h:911 void");
    return geometry;
}
AnmVariables& Animation::variables() {return base.variables;}
AnimationHandle AnimationFile::spawn(const char* expected,std::int32_t script,
                                    std::int32_t layer,Animation** output) {
    return spawn(expected,script,nullptr,0.0f,layer,0,output);
}
AnimationHandle AnimationFile::spawn(const char* expected,std::int32_t script,
                                    const Vector3& position,float rotation,
                                    std::int32_t layer,Animation** output) {
    return spawn(expected,script,&position,rotation,layer,0,output);
}
AnimationHandle AnimationFile::spawn_flag8(const char* expected,std::int32_t script,
                                    const Vector3& position,float rotation,
                                    std::int32_t layer,Animation** output) {
    return spawn(expected,script,&position,rotation,layer,8,output);
}
} // namespace th20
