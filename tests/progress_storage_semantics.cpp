#include "ProgressStorage.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <memory>
#include <new>

namespace {
template<class Range> void zero(const Range& values) {
    for (const auto value:values) assert(value==0);
}

void profile(const th20::ProgressProfile& value) {
    assert(value.header.magic==0 && value.header.version==0);
    assert(value.header.checksum==0 && value.header.size==0);
    assert(value.field_0c==0 && value.field_10==0 && value.field_76a8==0);
    for (const auto& row:value.scores) for (const auto& score:row) {
        assert(score.score==0 && score.timestamp==0 && score.slowdown==0);
        assert(score.stage==0 && score.continues==0);zero(score.name);
    }
    for (const auto& spell:value.spells) {
        zero(spell.name);zero(spell.captures);zero(spell.attempts);
        assert(spell.identifier==0 && spell.default_value==0 && spell.field_d8==0);
    }
    assert(value.statistics.field_00==0 && value.statistics.field_40==0 && value.statistics.field_44==0);
    zero(value.statistics.first);zero(value.statistics.second);
    for (const auto& row:value.practice) for (const auto& score:row) {
        assert(score.score==0 && score.field_08==0 && score.field_09==0);
        zero(score.field_0a);assert(!score.available());
    }
}

void metadata(const th20::ProgressMetadata& value, unsigned char pattern) {
    assert(value.header.magic==0 && value.header.version==0);
    assert(value.header.checksum==0 && value.header.size==0);
    std::array<unsigned char,10> preserved;preserved.fill(pattern);
    assert(std::memcmp(value.name,preserved.data(),preserved.size())==0);
    zero(value.field_16);zero(value.field_36);zero(value.field_56);zero(value.field_58);
    assert(value.field_60==0);zero(value.field_68);zero(value.field_e8);
    for (unsigned mode=0;mode<2;++mode) for (unsigned character=0;character<2;++character)
        for (unsigned slot=0;slot<4;++slot)
            assert(value.choices[mode*8+character*4+slot]==(slot==0 ? static_cast<int>(character) : 8));
    for (unsigned slot=0;slot<8;++slot) assert(value.stones[slot]==0);
    assert(value.stones[8]==9);zero(value.used_stones);
    zero(value.salt_1b0);zero(value.salt_1d2);
    assert(value.field_1d0==0 && value.checksum==0);
}
}

int main() {
    using namespace th20;
    constexpr unsigned guard=16;
    for (unsigned char pattern:{0u,0x55u,0xa5u,0xffu}) {
        alignas(ProgressMetadata) std::array<unsigned char,sizeof(ProgressMetadata)+2*guard> record;
        record.fill(pattern);
        auto* standalone=::new(record.data()+guard) ProgressMetadata;
        metadata(*standalone,pattern);standalone->~ProgressMetadata();
        for (unsigned i=0;i<guard;++i)assert(record[i]==pattern && record[record.size()-1-i]==pattern);

        // Construct the complete hierarchy twice in dirty guarded storage.
        // All nineteen real Profile constructors execute; no record fixture
        // or original data file supplies their contents.
        constexpr auto bytes=sizeof(ProgressSnapshot)+2*guard;
        auto first=std::make_unique<unsigned char[]>(bytes);
        auto second=std::make_unique<unsigned char[]>(bytes);
        std::fill_n(first.get(),bytes,pattern);std::fill_n(second.get(),bytes,pattern);
        auto* current=::new(first.get()+guard) ProgressSnapshot;
        auto* backup=::new(second.get()+guard) ProgressSnapshot;
        for (const auto* snapshot:{current,backup}) {
            assert(snapshot->file_size==0 && !snapshot->file_buffer && !snapshot->decoded_buffer);
            for (const auto& row:snapshot->profiles)
                for (const auto& selectable:row)profile(selectable);
            profile(snapshot->fallback);metadata(snapshot->metadata,pattern);
        }
        // The eighteenth selectable record, fallback, metadata and backup are
        // distinct live objects, including the final physical Spell slot.
        current->profiles[1][8].spells[122].attempts[1]=37;
        current->fallback.scores[6][9].score=100000;
        current->metadata.used_stones[8]=4;
        current->metadata.choices[15]=3;
        assert(current->profiles[1][7].spells[122].attempts[1]==0);
        assert(current->profiles[1][8].spells[122].attempts[0]==0);
        assert(current->fallback.spells[122].attempts[1]==0);
        assert(current->profiles[1][8].scores[6][9].score==0);
        assert(current->metadata.stones[8]==9 && current->metadata.used_stones[7]==0);
        assert(backup->metadata.used_stones[8]==0 && backup->metadata.choices[15]==8);
        assert(backup->fallback.scores[6][9].score==0);
        current->~ProgressSnapshot();backup->~ProgressSnapshot();
        for (unsigned i=0;i<guard;++i) {
            assert(first[i]==pattern && first[bytes-1-i]==pattern);
            assert(second[i]==pattern && second[bytes-1-i]==pattern);
        }
    }
}
