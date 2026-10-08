#include "ProgressSaveManager.hpp"
#include "DiagnosticAllocator.hpp"
#include "ArchiveLzss.hpp"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <memory>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
// Only native process startup and disk boundaries are fixtures. Parsing,
// checksums, cipher, decoder, locks, allocation and merge execute production.
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
void ProgressSaveManager::load(void*) {}
void ProgressSaveManager::save(void*) {}
}

namespace {
using namespace th20;
using Byte=std::uint8_t;
using Bytes=std::vector<Byte>;

std::uint32_t checksum(const Bytes& bytes) {
    std::uint32_t result=0;
    for (std::size_t i=8; i<bytes.size(); ++i) result+=bytes[i];
    return result;
}

template<class T> Bytes record(const T& value, unsigned magic, unsigned version) {
    Bytes bytes(sizeof(T));
    std::memcpy(bytes.data(), &value, bytes.size());
    auto* header=reinterpret_cast<ProgressRecordHeader*>(bytes.data());
    header->magic=magic;
    header->version=version;
    header->size=bytes.size();
    header->checksum=checksum(bytes);
    return bytes;
}

// Synthetic literal-only bit stream, independent of the production decoder.
Bytes compressed(const Bytes& bytes) {
    Bytes output;
    unsigned used=0;
    auto bits=[&](unsigned value, unsigned count) {
        while (count--) {
            if (!(used%8)) output.push_back(0);
            output.back()|=((value>>count)&1)<<(7-used%8);
            ++used;
        }
    };
    for (auto byte : bytes) { bits(1,1); bits(byte,8); }
    bits(0,14);
    return output;
}

// Invert the independently specified block permutation to produce a fixture.
// This supplies no production encoder/compressor or native file I/O.
Bytes encrypted(const Bytes& plain) {
    Bytes result=plain;
    unsigned key=0xac;
    const int size=plain.size();
    const int tail=(size%16<4 ? size%16 : 0)+(size&1);
    int position=0;
    for (int start=0; start<size-tail; start+=16) {
        const int count=std::min(16,size-tail-start);
        for (int parity : {count-1,count-2}) {
            for (int index=parity; index>=0; index-=2) {
                result[position++]=plain[start+index]^key;
                key=(key+0x35)&255;
            }
        }
    }
    return result;
}

Bytes install(ProgressSnapshot& snapshot, const Bytes& records, int decoded=-1) {
    auto payload=compressed(records);
    auto cipher=encrypted(payload);
    ProgressFileHeader header{};
    header.magic=0x32304854;
    header.version=4;
    header.spell_size=sizeof(ProgressSpell);
    header.profile_size=sizeof(ProgressProfile);
    header.metadata_size=sizeof(ProgressMetadata);
    header.snapshot_size=sizeof(ProgressSnapshot);
    header.compressed_size=cipher.size();
    header.decoded_size=decoded<0 ? records.size() : static_cast<unsigned>(decoded);
    // The parser deliberately ignores this disk field.
    header.file_size=0x87654321;
    snapshot.file_size=sizeof(header)+cipher.size();
    snapshot.file_buffer=static_cast<Byte*>(process_allocator->allocate_bytes(
        snapshot.file_size+1,"synthetic encrypted progress file"));
    assert(snapshot.file_buffer);
    std::memcpy(snapshot.file_buffer,&header,sizeof(header));
    std::memcpy(snapshot.file_buffer+sizeof(header),cipher.data(),cipher.size());
    snapshot.file_buffer[snapshot.file_size]=0xff; // Decoder fetch-before-bound guard.
    return payload;
}

void clear(ProgressSnapshot& snapshot) {
    TH20_RELEASE_BYTES_AND_RESET(snapshot.file_buffer);
    TH20_RELEASE_BYTES_AND_RESET(snapshot.decoded_buffer);
}

// Portable member assignment may leave alignment bytes alone. The complete
// native REP MOVSD and padding transfer are checked by the x86 oracle.
void same_metadata(const ProgressMetadata& actual, const ProgressMetadata& expected) {
    assert(actual.header.magic==expected.header.magic);
    assert(actual.header.version==expected.header.version);
    assert(actual.header.checksum==expected.header.checksum);
    assert(actual.header.size==expected.header.size);
#define CHECK_MEMBER(member) assert(std::memcmp(&actual.member,&expected.member,sizeof(actual.member))==0)
    CHECK_MEMBER(name); CHECK_MEMBER(field_16); CHECK_MEMBER(field_36);
    CHECK_MEMBER(field_56); CHECK_MEMBER(field_58); CHECK_MEMBER(field_60);
    CHECK_MEMBER(field_68); CHECK_MEMBER(field_e8); CHECK_MEMBER(choices);
    CHECK_MEMBER(stones); CHECK_MEMBER(used_stones); CHECK_MEMBER(salt_1b0);
    CHECK_MEMBER(field_1d0); CHECK_MEMBER(checksum); CHECK_MEMBER(salt_1d2);
#undef CHECK_MEMBER
}

void default_header(ProgressSaveManager& manager) {
    auto& snapshot=manager.current;
    snapshot.file_size=12345;
    snapshot.metadata.choices[0]=37;
    assert(manager.parse(&snapshot)==0);
    ProgressFileHeader expected{};
    expected.magic=0x32304854; expected.version=4; expected.field_20=0x100;
    expected.spell_size=sizeof(ProgressSpell); expected.profile_size=sizeof(ProgressProfile);
    expected.metadata_size=sizeof(ProgressMetadata); expected.snapshot_size=sizeof(ProgressSnapshot);
    assert(std::memcmp(snapshot.file_buffer,&expected,sizeof(expected))==0);
    assert(snapshot.file_size==12345 && snapshot.metadata.choices[0]==37);
    // Every observed header rejection creates the same cleared header; existing
    // decoded storage and record contents survive the fallback path.
    for (unsigned field : {0u,2u,3u,4u,5u,6u,9u}) {
        auto* words=reinterpret_cast<std::uint32_t*>(snapshot.file_buffer);
        std::memcpy(words,&expected,sizeof(expected));
        snapshot.file_size=44;
        words[field]^=1;
        snapshot.decoded_buffer=static_cast<Byte*>(process_allocator->allocate_bytes(16,"retained decoded"));
        auto* retained=snapshot.decoded_buffer;
        std::memset(retained,0xab,16);
        assert(manager.parse(&snapshot)==0);
        assert(std::memcmp(snapshot.file_buffer,&expected,sizeof(expected))==0);
        assert(snapshot.decoded_buffer==retained && retained[15]==0xab);
        assert(snapshot.metadata.choices[0]==37 && snapshot.file_size==44);
        TH20_RELEASE_BYTES_AND_RESET(snapshot.decoded_buffer);
    }
    clear(snapshot);
}

void whole_records(ProgressSaveManager& manager) {
    auto profile=std::make_unique<ProgressProfile>();
    auto metadata=std::make_unique<ProgressMetadata>();
    std::memset(metadata->name,'N',sizeof(metadata->name));
    metadata->choices[15]=6; metadata->stones[8]=77;
    Bytes all;
    std::vector<Bytes> expected;
    for (int character=0; character<2; ++character) for (int choice=0; choice<9; ++choice) {
        profile->field_0c=character; profile->field_10=choice;
        profile->scores[0][0].score=1000+character*9+choice;
        expected.push_back(record(*profile,0x5243,1));
        all.insert(all.end(),expected.back().begin(),expected.back().end());
    }
    profile->field_0c=2; profile->field_10=123; // Fallback ignores the second selector.
    expected.push_back(record(*profile,0x5243,1));
    all.insert(all.end(),expected.back().begin(),expected.back().end());
    const auto st=record(*metadata,0x5453,2);
    all.insert(all.end(),st.begin(),st.end());
    auto& snapshot=manager.current;
    const auto payload=install(snapshot,all);
    auto* file=snapshot.file_buffer;
    const auto file_size=snapshot.file_size;
    assert(manager.merge_current()==0); // Real backup -> parse -> copy-back pipeline.
    assert(snapshot.file_buffer==file && snapshot.file_size==file_size);
    assert(std::memcmp(file+44,payload.data(),payload.size())==0);
    assert(std::memcmp(snapshot.decoded_buffer,all.data(),all.size())==0);
    unsigned index=0;
    for (auto& row : snapshot.profiles) for (auto& value : row) {
        assert(std::memcmp(&value,expected[index].data(),sizeof(value))==0); ++index;
    }
    assert(std::memcmp(&snapshot.fallback,expected.back().data(),sizeof(snapshot.fallback))==0);
    same_metadata(snapshot.metadata,*reinterpret_cast<const ProgressMetadata*>(st.data()));
    assert(std::memcmp(manager.backup.profiles,snapshot.profiles,
        sizeof(snapshot.profiles)+sizeof(snapshot.fallback))==0);
    same_metadata(manager.backup.metadata,snapshot.metadata);
    assert(!manager.backup.file_buffer && !manager.backup.decoded_buffer);
    clear(snapshot);
}

void rejected_records(ProgressSaveManager& manager) {
    auto metadata=std::make_unique<ProgressMetadata>();
    std::memset(metadata->name,'X',sizeof(metadata->name));
    metadata->choices[0]=71;
    const auto valid=record(*metadata,0x5453,2);
    for (unsigned mode=0; mode<5; ++mode) {
        auto broken=valid;
        auto* header=reinterpret_cast<ProgressRecordHeader*>(broken.data());
        int extent=broken.size();
        if (mode==0) ++header->version;
        if (mode==1) ++header->checksum;
        if (mode==2) { header->size-=4; header->checksum=checksum(broken); extent-=4; }
        if (mode==3) header->magic=0;
        if (mode==4) { header->size+=4; header->checksum=checksum(broken); }
        manager.current.metadata.choices[0]=19;
        install(manager.current,broken,extent);
        assert(manager.parse(&manager.current)==0);
        assert(manager.current.metadata.choices[0]==19);
        clear(manager.current);
    }
    auto profile=std::make_unique<ProgressProfile>();
    profile->field_0c=1; profile->field_10=8; profile->scores[0][0].score=71;
    const auto cr=record(*profile,0x5243,1);
    for (unsigned mode=0; mode<4; ++mode) {
        auto broken=cr;
        auto* header=reinterpret_cast<ProgressRecordHeader*>(broken.data());
        int extent=broken.size();
        if (mode==0) ++header->version;
        if (mode==1) ++header->checksum;
        if (mode==2) { header->size-=4; header->checksum=checksum(broken); extent-=4; }
        if (mode==3) { header->size+=4; header->checksum=checksum(broken); }
        auto& destination=manager.current.profiles[1][8];
        destination.scores[0][0].score=19;
        install(manager.current,broken,extent);
        assert(manager.parse(&manager.current)==0 && destination.scores[0][0].score==19);
        clear(manager.current);
    }
    // Native copy precedes the remaining-length subtraction. The decoder's
    // output allocation is still large enough for this complete ST record.
    manager.current.metadata.choices[0]=19;
    install(manager.current,valid,valid.size()-4);
    assert(manager.parse(&manager.current)==0 && manager.current.metadata.choices[0]==71);
    clear(manager.current);
    auto first=valid;
    auto stop=valid; reinterpret_cast<ProgressRecordHeader*>(stop.data())->magic=0;
    auto last=valid;
    reinterpret_cast<ProgressMetadata*>(last.data())->choices[0]=99;
    reinterpret_cast<ProgressRecordHeader*>(last.data())->checksum=checksum(last);
    first.insert(first.end(),stop.begin(),stop.end()); first.insert(first.end(),last.begin(),last.end());
    install(manager.current,first);
    assert(manager.parse(&manager.current)==0 && manager.current.metadata.choices[0]==71);
    clear(manager.current);
    // Size zero is intentionally excluded: the native parser cannot advance it.
}

void checksum_contract() {
    ProgressMetadata metadata;
    std::memset(metadata.name,'C',sizeof(metadata.name));
    auto bytes=record(metadata,0x5453,2);
    auto* header=reinterpret_cast<ProgressRecordHeader*>(bytes.data());
    assert(header->calculate_checksum(bytes.size())==checksum(bytes));
    std::fill(bytes.begin(),bytes.begin()+8,0xff);
    assert(header->calculate_checksum(bytes.size())==checksum(bytes));
    for (int extent : {-7,0,7,8}) assert(header->calculate_checksum(extent)==0);
}
}

int main() {
    th20::DiagnosticAllocator allocator;
    th20::process_allocator=&allocator;
    th20::archive_lzss_reset();
    checksum_contract();
    {
        auto manager=std::make_unique<th20::ProgressSaveManager>();
        manager->worker.close_and_join();
        default_header(*manager);
        whole_records(*manager);
        rejected_records(*manager);
    }
    th20::process_allocator=nullptr;
}
