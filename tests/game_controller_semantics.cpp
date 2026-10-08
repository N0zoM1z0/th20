#include "GameController.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory>

namespace th20 {
// Explicit teardown boundary: this does not execute the native subsystem,
// callback, graphics/audio or global retirement protocol.
GameController::~GameController() = default;
}

namespace {
using namespace th20;
using Snapshot = std::array<unsigned char,sizeof(GameController)>;
Snapshot snapshot(const GameController& value) {
    Snapshot bytes{};
    std::memcpy(bytes.data(),&value,sizeof(value));
    return bytes;
}
void zero(const Timer& t) {
    assert(t.previous==0 && t.current==0 && t.current_fraction==0 && t.flags==0);
}
void defaults(const GameController& value) {
    assert(value.flags==2 && !value.update_node && !value.draw_node);
    zero(value.frame_timer); zero(value.secondary_timer);
    assert(value.load_stage==0 && value.field_34==0 && value.game_flags.bits==0);
    assert(value.field_ec==0 && value.field_f0==0 && value.field_f4==0);
    assert(value.field_f8==0.0 && value.field_100==0.0);
    assert(value.restart_mode==0 && value.field_10c==0);
    const auto& c=value.configuration;
    assert(c.version==0x200002 && c.size==176);
    assert(c.value_70==600 && c.value_72==600 && c.saved_display_mode==8);
    assert(c.saved_window_x==std::numeric_limits<std::int32_t>::min());
    assert(c.saved_window_y==std::numeric_limits<std::int32_t>::min());
    const std::array<std::int16_t,8> pad{0,1,2,3,-1,-1,-1,-1};
    const std::array<std::int16_t,8> alternate{0,1,5,10,-1,-1,-1,-1};
    const std::array<std::int16_t,8> keyboard{90,88,16,27,38,40,37,39};
    for (const auto& bindings:c.bindings) {
        assert(std::memcmp(&bindings.pad,pad.data(),16)==0);
        assert(std::memcmp(&bindings.alternate_pad,alternate.data(),16)==0);
        assert(std::memcmp(&bindings.keyboard,keyboard.data(),16)==0);
    }
    // The native Configuration constructor initializes only its low nine
    // option bits. Game construction must preserve the upper dirty bits.
    std::uint32_t bits;
    std::memcpy(&bits,&c.flags,sizeof(bits));
    assert(bits==((0xa5a5a5a5u&~0x1ffu)|0x80u));
}
}

int main() {
    using namespace th20;
    constexpr std::size_t guard=16;
    alignas(GameController) std::array<unsigned char,sizeof(GameController)+2*guard> storage;
    storage.fill(0xa5);
    auto* value=std::construct_at(reinterpret_cast<GameController*>(storage.data()+guard));
    defaults(*value);
    auto untouched=[](const unsigned char* begin,const unsigned char* end) {
        for (;begin<end;++begin) assert(*begin==0xa5);
    };
    const auto& c=value->configuration;
    untouched(&c.value_76+1,reinterpret_cast<const unsigned char*>(&c.saved_display_mode));
    untouched(&c.value_a4+1,reinterpret_cast<const unsigned char*>(&c.values_a8));
    for (std::uint32_t bits=0;bits<512;++bits) {
        // Include unrelated high flags while enumerating every low-bit state.
        value->game_flags.bits=bits|0xa5a50000u;
        auto before=snapshot(*value);
        assert(value->update_suppressed()==((bits&5u)!=0?1:0));
        assert(value->animation_frozen()==((bits&2u)!=0?1:0));
        assert(snapshot(*value)==before);
        value->clear_flag_6();
        const auto expected=(bits|0xa5a50000u)&~0x40u;
        assert(value->game_flags.bits==expected);
        const auto offset=reinterpret_cast<const unsigned char*>(&value->game_flags)
            -reinterpret_cast<const unsigned char*>(value);
        std::memcpy(before.data()+offset,&expected,sizeof(expected));
        assert(snapshot(*value)==before);
    }
    for (auto mode:{std::numeric_limits<std::int32_t>::min(),-1,0,1,2,
                    std::numeric_limits<std::int32_t>::max()}) {
        value->restart_mode=mode;
        const auto before=snapshot(*value);
        assert(value->restart()==mode && snapshot(*value)==before);
    }
    std::destroy_at(value); // Explicit fixture boundary only.
    untouched(storage.data(),storage.data()+guard);
    untouched(storage.data()+guard+sizeof(GameController),storage.data()+storage.size());
}
