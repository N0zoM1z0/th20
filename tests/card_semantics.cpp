#include "Card.hpp"
#include "Session.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory>

namespace th20 {
// Explicit disposal boundary. This fixture performs no native Card cleanup;
// all construction, encoding, queries, Session and Context bodies are production.
Card::~Card() = default;
}

namespace {
using namespace th20;
using Snapshot = std::array<unsigned char,sizeof(Card)>;
Snapshot snapshot(const Card& value) {
    Snapshot bytes{};
    std::memcpy(bytes.data(),&value,sizeof(value));
    return bytes;
}
template<class T> void replace(Snapshot& before, const Card& value, const T& field) {
    auto offset=reinterpret_cast<const unsigned char*>(&field)
        -reinterpret_cast<const unsigned char*>(&value);
    std::memcpy(before.data()+offset,&field,sizeof(field));
}
std::int64_t signed_word(std::uint64_t value) {
    value &= 0xffffffffULL;
    return value <= 0x7fffffffULL ? static_cast<std::int64_t>(value)
        : static_cast<std::int64_t>(value)-0x100000000LL;
}
// An independent wide-integer model of the three native stores. No signed
// intermediate overflow and no call into a production arithmetic helper.
std::int64_t encoded(std::int32_t seconds,std::int32_t hundredths) {
    auto s=signed_word(static_cast<std::uint64_t>(seconds)+66);
    auto h=signed_word(static_cast<std::uint64_t>(hundredths)+33);
    auto lower=s%1000*100+h%100;
    auto checksum=(static_cast<std::int64_t>(seconds)+hundredths+22)*100000;
    return signed_word(static_cast<std::uint64_t>(lower+checksum));
}
void defaults(const Card& value) {
    assert(value.flags==2 && value.update_node==nullptr && value.draw_node==nullptr);
    assert(value.background_handle.value==0 && value.effect_handle.value==0);
    for (const auto& handle:value.info_handles) assert(handle.value==0);
    assert(value.age.previous==0 && value.age.current==0);
    assert(value.age.current_fraction==0.0f && value.age.flags==0);
    assert(std::all_of(std::begin(value.name),std::end(value.name),[](char c){return c==0;}));
    assert(value.spell_index==0 && value.spell_flags.bits==0);
    assert(value.bonus==0 && value.initial_bonus==0 && value.duration==0);
    assert(value.capture_index==0 && value.frames==0 && value.last_frames==0);
    assert(value.start_time==0.0 && value.elapsed==0.0 && value.encoded_time==0);
    assert(value.position.x==0.0f && value.position.y==0.0f && value.position.z==0.0f);
    assert(value.field_b8==0 && value.player_index==0 && value.context==nullptr);
}
}

int main() {
    using namespace th20;
    constexpr std::size_t guard=16;
    alignas(Card) std::array<unsigned char,sizeof(Card)+2*guard> storage;
    storage.fill(0xa5);
    auto* value=std::construct_at(reinterpret_cast<Card*>(storage.data()+guard));
    defaults(*value);
    const auto* origin=reinterpret_cast<const unsigned char*>(value);
    auto untouched=[&](const unsigned char* first,const unsigned char* end) {
        for (;first<end;++first) assert(*first==0xa5);
    };
    untouched(reinterpret_cast<const unsigned char*>(&value->last_frames)+4,
              reinterpret_cast<const unsigned char*>(&value->start_time));
    untouched(reinterpret_cast<const unsigned char*>(&value->context)+sizeof(value->context),
              origin+sizeof(Card));
    constexpr auto low=std::numeric_limits<std::int32_t>::min();
    constexpr auto high=std::numeric_limits<std::int32_t>::max();
    const std::array inputs{low,low+1,-100001,-1000,-100,-67,-66,-34,-33,-22,-1,
                           0,1,33,66,99,100,933,934,999,1000,100001,high-66,high};
    for (auto seconds:inputs) for (auto hundredths:inputs) {
        auto before=snapshot(*value);
        value->encode_time(seconds,hundredths);
        assert(value->encoded_time==encoded(seconds,hundredths));
        replace(before,*value,value->encoded_time);
        assert(before==snapshot(*value));
    }
    for (int seconds=0;seconds<1000;seconds+=7) for (int hundredths=0;hundredths<100;++hundredths) {
        value->encode_time(seconds,hundredths);
        auto before=snapshot(*value);
        assert(value->invalid_encoded_time()==0);
        assert(before==snapshot(*value));
        value->encoded_time+=100000;
        before=snapshot(*value);
        assert(value->invalid_encoded_time()==1);
        assert(before==snapshot(*value));
    }
    for (auto code:inputs) {
        value->encoded_time=code;
        auto before=snapshot(*value);
        std::int64_t word=code;
        auto expected=word/100000-22 != ((word/100)%1000+934)%1000+(word%100+67)%100;
        assert(value->invalid_encoded_time()==(expected?1:0));
        assert(before==snapshot(*value));
    }
    for (auto bits:{0u,1u,2u,3u,0x80000000u,0xffffffffu}) {
        value->spell_flags.bits=bits;
        auto before=snapshot(*value);
        assert(value->active()==((bits&1u)!=0));
        assert(before==snapshot(*value));
    }
    assert(card(0)==nullptr && card(1)==nullptr);
    for (int index:{1,0,1,0}) {
        auto before=snapshot(*value);
        value->bind_context(index);
        assert(value->player_index==index && value->context==&session.contexts[index]);
        replace(before,*value,value->player_index);replace(before,*value,value->context);
        assert(before==snapshot(*value));
        assert(card(index)==nullptr); // Binding alone has no publication effect.
        std::array<unsigned char,sizeof(Context)> previous{};
        std::memcpy(previous.data(),value->context,sizeof(Context));
        value->context->set_card(value);
        auto offset=reinterpret_cast<const unsigned char*>(&value->context->card_owner)
            -reinterpret_cast<const unsigned char*>(value->context);
        std::memcpy(previous.data()+offset,&value->context->card_owner,sizeof(Card*));
        assert(std::memcmp(previous.data(),value->context,sizeof(Context))==0);
        assert(value->context->card()==value && card(index)==value);
        assert(card(1-index)==nullptr);
        value->context->set_card(nullptr);
        assert(card(index)==nullptr);
    }
    std::destroy_at(value); // Declared fixture disposal boundary only.
    untouched(storage.data(),storage.data()+guard);
    untouched(storage.data()+guard+sizeof(Card),storage.data()+storage.size());
}
