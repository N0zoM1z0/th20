// Execute actual 75-byte FrontInf stage-title owner method with actual
// Graphics/Session/AnimationFile C++ owners. Only original renderer/VM
// AnimationFile::spawn is captured; no production facade is introduced.
#include "HudGauge.hpp"
#include "Graphics.hpp"
#include "Session.hpp"
#include "AnimationFile.hpp"
#include "LockRegistry.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace {
std::uint32_t spawn_count;
bool throw_on_spawn;
th20::AnimationFile* observed_file;
std::int32_t observed_script,observed_layer;
const char* observed_stem;
th20::Animation** observed_output;
template<class T> std::array<unsigned char,sizeof(T)> image(const T& value) {
    std::array<unsigned char,sizeof(T)> bytes{};
    std::memcpy(bytes.data(),&value,sizeof(value));
    return bytes;
}
}
namespace th20 {
// Genuine process-type objects and genuine production constructors execute.
LockRegistry process_locks;
Graphics process_graphics;
Graphics::~Graphics() = default;
AnimationFile::~AnimationFile() = default;
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { }
void TaskInfo::disable() { }
FrontInf::~FrontInf() = default;
void FrontInf::enable() { }
void ecl_diagnostic_hint(const char* format, ...) {
    assert(format && std::strcmp(format,"initialize FrontInf\n") == 0);
}
AnimationHandle AnimationFile::spawn(const char* stem,std::int32_t script,
                                      std::int32_t layer,Animation** output) {
    observed_file=this;
    observed_stem=stem;
    observed_script=script;
    observed_layer=layer;
    observed_output=output;
    ++spawn_count;
    if(throw_on_spawn)throw std::runtime_error("native renderer / VM pending");
    AnimationHandle result;
    result.value=0xFEED1234u;
    return result;
}
}
int main() {
    using namespace th20;
    AnimationFile stage_file;
    FrontInf front;
    front.message_file=&stage_file;
    const auto baseline_front=image(front);
    const auto initial_graphics=process_graphics.field_b0c;
    const auto initial_session=session.flags.bits;
    unsigned checked=0,spawned=0;
    for(int graphics_mode:{-2,-1,0,7,8,9,0x7fffffff})
    for(std::uint32_t flags:{0u,1u,31u,32u,33u,~0u,0x80000000u,0xffffffe0u})
    for(bool fail:{false,true}) {
        process_graphics.field_b0c=graphics_mode;
        session.flags.bits=flags;
        const auto graphic_image=image(process_graphics);
        const auto session_image=image(session);
        const auto before_calls=spawn_count;
        throw_on_spawn=fail;
        observed_file=nullptr;observed_script=314;observed_layer=733;
        observed_stem=reinterpret_cast<const char*>(std::uintptr_t(1));
        observed_output=reinterpret_cast<Animation**>(std::uintptr_t(1));
        const bool enabled=graphics_mode!=8 && !(flags & 32u);
        assert(process_graphics.field_b0c_value()==graphics_mode);
        assert(session.flag5_value()==static_cast<int>((flags>>5)&1u));
        bool threw=false;
        try { front.show_stage_title(); }
        catch(const std::runtime_error&){threw=true;}
        assert(threw==(enabled&&fail));
        assert(spawn_count==before_calls+static_cast<unsigned>(enabled));
        if(enabled) {
            assert(observed_file==&stage_file);
            assert(observed_script==0 && observed_layer==-1);
            assert(observed_stem==nullptr && observed_output==nullptr);
            ++spawned;
        } else {
            assert(observed_file==nullptr && observed_script==314 && observed_layer==733);
        }
        assert(image(front)==baseline_front);
        assert(image(process_graphics)==graphic_image);
        assert(image(session)==session_image);
        ++checked;
    }
    process_graphics.field_b0c=initial_graphics;
    session.flags.bits=initial_session;
    throw_on_spawn=false;
    assert(checked==112 && spawned==48);
    std::cout<<"PASS "<<checked<<" native FrontInf stage title checks ("<<spawned
             <<" full four-argument animation spawn boundaries); actual Graphics/"
                "Session global owners, native short-circuit and full owner images."
                " Missing renderer/VM remains captured.\n";
}
