#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "DiagnosticAllocator.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
// Native process startup alone is a fixture; all codec/allocation bodies run.
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
}

namespace {
using Byte=std::uint8_t;
using Bytes=std::vector<Byte>;
using namespace th20;

struct Decoded {
    Bytes bytes;
    unsigned literals=0, matches=0, bits=0;
};

// Independent logical reader: zero-extended exhaustion, fresh ring, and
// explicit token grammar. No production reader/writer macros or tree search.
Decoded decode(const Bytes& input) {
    Decoded result;
    std::array<Byte,8192> ring{};
    unsigned cursor=1;
    auto read=[&](unsigned count) {
        unsigned value=0;
        while (count--) {
            value<<=1;
            if (result.bits<input.size()*8)
                value|=(input[result.bits/8]>>(7-result.bits%8))&1;
            ++result.bits;
        }
        return value;
    };
    auto append=[&](Byte byte) {
        assert(result.bytes.size()<100000);
        result.bytes.push_back(byte); ring[cursor]=byte;
        cursor=(cursor+1)%ring.size();
    };
    for (;;) {
        if (read(1)) { append(read(8)); ++result.literals; }
        else {
            unsigned offset=read(13);
            if (!offset) return result;
            unsigned count=read(4)+3;
            assert(offset<ring.size() && count>=3 && count<=18);
            for (unsigned index=0; index<count; ++index) append(ring[(offset+index)%ring.size()]);
            ++result.matches;
        }
    }
}

void compressors() {
    unsigned total_matches=0;
    bool saw_partial=false;
    for (unsigned size : {1u,2u,3u,7u,17u,18u,19u,31u,32u,33u,8191u,8192u,8210u,20000u}) {
        for (unsigned pattern=0; pattern<4; ++pattern) {
            Bytes input(size);
            unsigned state=0x12345678;
            for (unsigned index=0; index<size; ++index) {
                state=state*1664525+1013904223;
                input[index]=pattern==0 ? 0 : pattern==1 ? 'A' : pattern==2 ? index%23 : state>>24;
            }
            // Compression must reset shared state, including after a previous
            // decode left a completely different dictionary/tree.
            std::memset(archive_dictionary,0xa7,sizeof(archive_dictionary));
            std::memset(archive_lzss_nodes,0xcc,sizeof(archive_lzss_nodes));
            std::int32_t count=-123;
            Byte* owned=archive_compress(input.data(),input.size(),&count);
            assert(owned && count>0 && static_cast<unsigned>(count)<=2*size);
            Bytes packet(owned,owned+count);
            const auto parsed=decode(packet);
            assert(parsed.bytes==input);
            assert(static_cast<unsigned>(count)==parsed.bits/8); // No final partial flush.
            saw_partial|=parsed.bits%8!=0;
            total_matches+=parsed.matches;
            assert(parsed.literals>0);
            // Supply the native decoder's required readable guard explicitly.
            packet.push_back(0xff);
            Bytes output(size+16,0xce);
            archive_decompress(packet.data(),count,output.data()+8,size);
            assert(std::equal(input.begin(),input.end(),output.begin()+8));
            for (unsigned index=0; index<8; ++index)
                assert(output[index]==0xce && output[output.size()-1-index]==0xce);
            // Real encrypt/decrypt on the returned allocation; both preserve
            // byte count, ownership, untransformed tails and the input pointer.
            assert(archive_encrypt(owned,count,0xac,0x35,16,count)==owned);
            assert(archive_decrypt(owned,count,0xac,0x35,16,count)==owned);
            assert(std::equal(packet.begin(),packet.end()-1,owned));
            process_allocator->release_bytes(owned);
        }
    }
    assert(total_matches>0 && saw_partial);
    // Wrapped allocation failure must precede ring/tree reset and size output.
    std::array<Byte,8192> dictionary;
    std::array<ArchiveLzssNode,8193> nodes;
    std::memcpy(dictionary.data(),archive_dictionary,sizeof(archive_dictionary));
    std::memcpy(nodes.data(),archive_lzss_nodes,sizeof(archive_lzss_nodes));
    std::int32_t untouched=37;
    assert(archive_compress(nullptr,-1,&untouched)==nullptr && untouched==37);
    assert(std::memcmp(dictionary.data(),archive_dictionary,sizeof(archive_dictionary))==0);
    assert(std::memcmp(nodes.data(),archive_lzss_nodes,sizeof(archive_lzss_nodes))==0);
}

void encryption() {
    for (int block : {8,16,128,256}) for (int size : {0,1,2,7,17,129,257,515}) {
        for (int limit : {block,block*2,block*4}) {
            Bytes plain(size+16,0xd7);
            for (int index=0; index<size; ++index) plain[index+8]=index*73+19;
            auto expected=plain;
            const int tail=(size%block<block/4 ? size%block : 0)+(size&1);
            const int transformed=size-tail;
            unsigned key=0xf3;
            int consumed=0;
            for (int start=0; start<transformed && start<limit; start+=block) {
                const int count=std::min(block,transformed-start);
                for (int parity : {count-1,count-2}) for (int index=parity; index>=0; index-=2) {
                    expected[8+consumed++]=plain[8+start+index]^key;
                    key=(key+0xad)&255;
                }
            }
            assert(consumed<=std::min(size,limit));
            auto actual=plain;
            assert(archive_encrypt(actual.data()+8,size,0xf3,0xad,block,limit)==actual.data()+8);
            assert(actual==expected);
            assert(archive_decrypt(actual.data()+8,size,0xf3,0xad,block,limit)==actual.data()+8);
            assert(actual==plain);
        }
    }
}
}

int main() {
    th20::DiagnosticAllocator allocator;
    th20::process_allocator=&allocator;
    encryption(); compressors();
    th20::process_allocator=nullptr;
}
