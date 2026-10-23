#include "Card.hpp"
#include "Session.hpp"
#include "EnemyHealth.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory>
#include <functional>
#include <stdexcept>
#include <cstdio>

namespace {
th20::Card* retiring_card;
unsigned retirement_calls, retired_value, retirement_flags;
std::function<void()> retirement_hook;
}

namespace th20 {
// Explicit disposal boundary. This fixture performs no native Card cleanup;
// all construction, encoding, queries, Session and Context bodies are production.
Card::~Card() = default;
// Only the unresolved Renderer retirement is captured. The actual Card caller
// must publish its flag before passing the real effect-handle subobject here.
void AnimationHandle::retire() {
    assert(retiring_card && this==&retiring_card->effect_handle);
    ++retirement_calls;retired_value=value;retirement_flags=retiring_card->spell_flags.bits;
    if(retirement_hook)retirement_hook();
    value=0;
}
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
    unsigned flag_cases=0;retiring_card=value;
    const std::array<unsigned,6> flag_words{0u,1u,2u,3u,0x80000000u,0xffffffffu};
    for(unsigned flags:flag_words) {
        value->spell_flags.bits=flags;auto before=snapshot(*value);
        value->request_flag_3();assert(value->spell_flags.bits==(flags|8u));
        replace(before,*value,value->spell_flags);assert(before==snapshot(*value));++flag_cases;
        for(unsigned handle:{0u,1u,11u,0xffffffffu}) {
            value->spell_flags.bits=flags;value->effect_handle.value=handle;
            before=snapshot(*value);const auto calls=retirement_calls;
            value->request_flag_4();assert(retirement_calls==calls+1);
            assert(retirement_flags==(flags|16u) && retired_value==handle && value->effect_handle.value==0);
            replace(before,*value,value->spell_flags);replace(before,*value,value->effect_handle);
            assert(before==snapshot(*value));++flag_cases;
        }
        for(unsigned input:flag_words) {
            value->spell_flags.bits=flags;before=snapshot(*value);const auto calls=retirement_calls;
            value->set_flag_8(input);assert(value->spell_flags.bits==((flags&~0x100u)|((input&1u)<<8)));
            replace(before,*value,value->spell_flags);assert(before==snapshot(*value) && retirement_calls==calls);++flag_cases;
            EnemyHealth health;health.health=7;health.field_04=17;health.phase_health=23;
            health.scaled_health=31;health.threshold=41;health.damage=47;health.flags.bits=flags;
            const std::array<unsigned,7> expected{7,17,23,31,41,47,(flags&~1u)|(input&1u)};
            health.set_scaled_enabled(input);assert(!std::memcmp(&health,expected.data(),sizeof(health)));++flag_cases;
        }
    }
    value->spell_flags.bits=1;value->effect_handle.value=91;
    retirement_hook=[&]{assert(value->spell_flags.bits==17);value->spell_flags.bits=0x80000101u;};
    value->request_flag_4();retirement_hook={};
    assert(value->spell_flags.bits==0x80000101u && value->effect_handle.value==0);++flag_cases;
    value->spell_flags.bits=3;value->effect_handle.value=73;auto before=snapshot(*value);
    retirement_hook=[] {throw std::runtime_error("Captured Renderer retirement failure");};
    bool threw=false;try {value->request_flag_4();}catch(const std::runtime_error&){threw=true;}
    retirement_hook={};assert(threw && value->spell_flags.bits==19 && value->effect_handle.value==73);
    replace(before,*value,value->spell_flags);assert(before==snapshot(*value));++flag_cases;
    retiring_card=nullptr;value->effect_handle.value=0;
    std::printf("Card/health flags passed: %u whole-owner/mask/retirement-order cases; Renderer retirement remains captured.\n",flag_cases);
    std::destroy_at(value); // Declared fixture disposal boundary only.
    untouched(storage.data(),storage.data()+guard);
    untouched(storage.data()+guard+sizeof(Card),storage.data()+storage.size());
}
