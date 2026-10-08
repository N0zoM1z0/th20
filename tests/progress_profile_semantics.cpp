#include "ProgressProfile.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>

int main() {
    using namespace th20;
    constexpr unsigned guard=16;
    for (unsigned char pattern : {0u,0x55u,0xa5u,0xffu}) {
        alignas(ProgressProfile) std::array<unsigned char,sizeof(ProgressProfile)+2*guard> bytes;
        bytes.fill(pattern);
        auto* profile=::new(bytes.data()+guard) ProgressProfile;
        assert(profile->header.magic==0 && profile->header.version==0);
        assert(profile->header.checksum==0 && profile->header.size==0);
        assert(profile->field_0c==0 && profile->field_10==0 && profile->field_76a8==0);
        for (const auto& row:profile->scores) for (const auto& score:row) {
            assert(score.score==0 && score.stage==0 && score.continues==0);
            assert(score.timestamp==0 && score.slowdown==0);
            assert(std::all_of(std::begin(score.name),std::end(score.name),[](char c){return c==0;}));
        }
        // Check every physical slot, including the ten outside startup's active
        // range. A 113-record facade would shift all following native members.
        assert(profile->spells.size()==123);
        for (const auto& spell:profile->spells) {
            assert(std::all_of(std::begin(spell.name),std::end(spell.name),[](char c){return c==0;}));
            for (int mode=0;mode<2;++mode)assert(spell.captures[mode]==0 && spell.attempts[mode]==0);
            assert(spell.identifier==0 && spell.default_value==0 && spell.field_d8==0);
        }
        const auto& statistics=profile->statistics;
        assert(statistics.field_00==0 && statistics.field_40==0 && statistics.field_44==0);
        for (int difficulty=0;difficulty<7;++difficulty)
            assert(statistics.first[difficulty]==0 && statistics.second[difficulty]==0);
        for (const auto& row:profile->practice) for (const auto& score:row) {
            assert(score.score==0 && score.field_08==0 && score.field_09==0);
            assert(score.field_0a[0]==0 && score.field_0a[1]==0 && !score.available());
        }
        for (unsigned i=0;i<guard;++i)assert(bytes[i]==pattern && bytes[bytes.size()-1-i]==pattern);
        // Live record aliases remain independent across modes, slots and rows.
        profile->spells[122].captures[1]=17;
        profile->spells[112].attempts[0]=23;
        profile->scores[6][9].score=100000;
        profile->practice[6][8].field_09=1;
        assert(profile->spells[122].captures[0]==0 && profile->spells[121].captures[1]==0);
        assert(profile->spells[112].attempts[1]==0 && profile->scores[6][8].score==0);
        assert(profile->practice[6][8].available() && !profile->practice[6][7].available());
        profile->~ProgressProfile();
    }
}
