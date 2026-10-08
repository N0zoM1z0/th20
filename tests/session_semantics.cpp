#include "Session.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory>

namespace {
using namespace th20;
constexpr std::size_t guard = 16;
using Snapshot = std::array<unsigned char,sizeof(Session)>;
Snapshot snapshot(const Session& value) {
    Snapshot bytes{};
    std::memcpy(bytes.data(), &value, sizeof(value));
    return bytes;
}
void only_word_changed(const Session& value, Snapshot before, const std::int32_t& field) {
    const auto offset = reinterpret_cast<const unsigned char*>(&field)
        - reinterpret_cast<const unsigned char*>(&value);
    std::memcpy(before.data()+offset, &field, sizeof(field));
    assert(snapshot(value)==before);
}
void defaults(const Session& value) {
    assert(value.field_60==0 && value.field_68==0 && value.flags.bits==0);
    assert(value.field_70==0 && value.field_74==0 && value.field_78==0);
    assert(value.field_7c==0 && value.field_80==0 && value.field_2b0==0.0);
    assert(value.field_2b8==0 && value.field_2bc==1);
    assert(value.table.field_1e0==1 && value.table.continue_count==0);
    assert(value.table.field_200==-1 && value.table.field_204==-1);
    assert(value.table.field_208==0 && value.table.field_220==-1);
    for (const auto& record : value.table.players) {
        assert(record.current_score()==0 && record.field_34==400);
        assert(record.field_38==100 && record.field_40==10000);
        assert(record.field_48==5000 && record.field_50==100 && record.field_54==1);
        assert(record.field_98==-1 && record.field_b8==-1 && record.field_d4==2);
        assert(record.field_ec==0);
    }
    for (const auto& context : value.contexts) {
        const auto* words = reinterpret_cast<const unsigned char*>(&context);
        assert(std::all_of(words,words+sizeof(context),[](auto b){return b==0;}));
    }
}
}

int main() {
    using namespace th20;
    defaults(session); // Runs the real global definition and static initializer.
    alignas(Session) std::array<unsigned char,sizeof(Session)+2*guard> storage;
    storage.fill(0xa5);
    auto* value = std::construct_at(reinterpret_cast<Session*>(storage.data()+guard));
    defaults(*value);
    auto untouched = [&](std::size_t first,std::size_t end) {
        for (auto i=first;i<end;++i) assert(storage[guard+i]==0xa5);
    };
    untouched(offsetof(Session,field_80)+4,offsetof(Session,table));
    untouched(offsetof(Session,table)+offsetof(PlayerTable,field_220)+4,
        offsetof(Session,table)+sizeof(PlayerTable));
    for (unsigned index=0;index<2;++index) {
        const auto base=offsetof(Session,table)+offsetof(PlayerTable,players)+index*sizeof(PlayerRecord);
        untouched(base+0xa6,base+0xa8);
        untouched(base+0xb1,base+0xb4);
        assert(&value->context(index)==&value->contexts[index]);
        assert(&value->player_table().player(index)==&value->table.players[index]);
    }
    assert(&player_table()==&session.table);
    for (int mode : {-1,0,1,2,3,4,100}) {
        value->table.field_1e0=mode;
        const auto before=snapshot(*value);
        assert(value->mode()==mode && value->table.mode()==mode);
        assert(snapshot(*value)==before);
    }
    value->contexts[0].current_player=&value->table.players[1];
    assert(value->contexts[0].player_record()==&value->table.players[1]);
    assert(value->contexts[1].player_record()==nullptr);
    assert(player_record(0)==nullptr && player_record(1)==nullptr);
    session.context(0).current_player=&session.table.player(1);
    assert(player_record(0)==&session.table.players[1]);
    assert(player_record(1)==nullptr);
    session.context(0).current_player=nullptr;
    // Opaque Controller identity tokens are borrowed and never dereferenced.
    alignas(void*) std::array<unsigned char,2*sizeof(void*)> owner_tokens{};
    auto* first=reinterpret_cast<EnemyController*>(owner_tokens.data());
    auto* second=reinterpret_cast<EnemyController*>(owner_tokens.data()+sizeof(void*));
    assert(enemy_controller(0)==nullptr && enemy_controller(1)==nullptr);
    session.context(0).enemies=first; session.context(1).enemies=second;
    assert(enemy_controller(0)==first && enemy_controller(1)==second);
    session.context(0).enemies=second;
    assert(enemy_controller(0)==second && enemy_controller(1)==second);
    session.context(0).enemies=nullptr; session.context(1).enemies=nullptr;

    constexpr auto low=std::numeric_limits<std::int32_t>::min();
    constexpr auto high=std::numeric_limits<std::int32_t>::max();
    for (auto input : {low,-1,0,1,998,999,1000,9998,9999,10000,99998,99999,100000,high}) {
        value->table.field_1fc=input;
        auto before=snapshot(*value);
        assert(value->clamped_field_1fc()==std::clamp(input,0,999));
        only_word_changed(*value,before,value->table.field_1fc);
        value->table.field_204=input; before=snapshot(*value);
        assert(value->clamped_field_204()==std::clamp(input,-1,9999));
        only_word_changed(*value,before,value->table.field_204);
        value->table.field_208=input; before=snapshot(*value);
        assert(value->table.clamped_field_208()==std::clamp(input,0,99999));
        only_word_changed(*value,before,value->table.field_208);
    }
    for (auto initial : {low,high,-10,-1,0,1,8,9,10}) {
        for (auto delta : {low,high,-10,-1,0,1,8,9,10}) {
            value->table.continue_count=initial;
            auto before=snapshot(*value);
            const auto bits=static_cast<std::uint32_t>(initial)+static_cast<std::uint32_t>(delta);
            const auto signed_value=static_cast<std::int64_t>(bits)
                - ((bits & 0x80000000u) ? 0x100000000LL : 0LL);
            value->table.add_continue_count(delta);
            assert(value->table.continue_count==std::clamp<std::int64_t>(signed_value,0,9));
            only_word_changed(*value,before,value->table.continue_count);
        }
        value->table.continue_count=initial;
        auto before=snapshot(*value);
        const auto bits=static_cast<std::uint32_t>(initial)+1u;
        const auto signed_value=static_cast<std::int64_t>(bits)
            - ((bits & 0x80000000u) ? 0x100000000LL : 0LL);
        value->increment_continue_count();
        assert(value->table.continue_count==std::clamp<std::int64_t>(signed_value,0,9));
        only_word_changed(*value,before,value->table.continue_count);
    }
    for (auto bits : {0u,0xffffffffu,0xaaaaaaaau,0x55555555u,0x80000000u}) {
        for (auto input : {0u,1u,2u,3u,0xffffffffu}) {
            value->flags.bits=bits;
            auto before=snapshot(*value);
            value->set_flag0(input);
            const auto expected0=(bits & ~1u) | (input & 1u);
            std::uint32_t actual;
            std::memcpy(&actual,&value->flags,4);
            assert(actual==expected0);
            std::memcpy(before.data()+offsetof(Session,flags),&expected0,4);
            assert(snapshot(*value)==before);
            value->flags.bits=bits; before=snapshot(*value);
            value->set_flag1(input);
            const auto expected1=(bits & ~2u) | ((input & 1u)<<1);
            std::memcpy(&actual,&value->flags,4);
            assert(actual==expected1);
            std::memcpy(before.data()+offsetof(Session,flags),&expected1,4);
            assert(snapshot(*value)==before);
        }
    }
    std::destroy_at(value);
    for (std::size_t i=0;i<guard;++i) {
        assert(storage[i]==0xa5 && storage[guard+sizeof(Session)+i]==0xa5);
    }
}
