#include "ProgressSaveManager.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>
#include <cassert>
#include <chrono>
#include <cstring>
#include <future>
#include <memory>
#include <new>
#include <vector>

namespace {
struct Gate {
    std::promise<void> entered, release;
};
struct Fixture {
    Gate load;
    std::array<Gate,3> saves;
    std::array<std::uint8_t*,4> buffers{};
    std::atomic<unsigned> save_count{0};
    unsigned released=0, parses=0;
    std::int32_t parse_result=0;
    bool allocate_buffers=true;
    th20::ProgressSaveManager* owner=nullptr;
};
Fixture* fixture=nullptr;

constexpr auto record_offset=offsetof(th20::ProgressSnapshot, profiles);
constexpr auto record_bytes=offsetof(th20::ProgressSnapshot, metadata)-record_offset;
static_assert(record_bytes==19*sizeof(th20::ProgressProfile));

unsigned char* records(th20::ProgressSnapshot& snapshot) {
    return reinterpret_cast<unsigned char*>(&snapshot)+record_offset;
}
std::vector<unsigned char> image(th20::ProgressSnapshot& snapshot) {
    const auto* first=records(snapshot);
    return {first, first+record_bytes+sizeof(snapshot.metadata)};
}
void fill_records(th20::ProgressSnapshot& snapshot, unsigned seed) {
    auto* bytes=records(snapshot);
    for (std::size_t i=0; i<record_bytes+sizeof(snapshot.metadata); ++i)
        bytes[i]=static_cast<unsigned char>(i*37+seed);
}
void preserved_buffers(const th20::ProgressSaveManager& owner, const Fixture& f) {
    assert(owner.current.file_size==123 && owner.backup.file_size==456);
    assert(owner.current.file_buffer==f.buffers[0]);
    assert(owner.current.decoded_buffer==f.buffers[1]);
    assert(owner.backup.file_buffer==f.buffers[2]);
    assert(owner.backup.decoded_buffer==f.buffers[3]);
}
void merge_protocol(th20::ProgressSaveManager& owner, Fixture& f) {
    fill_records(owner.current, 0x19);
    fill_records(owner.backup, 0xa7);
    auto before=image(owner.current);
    assert(owner.copy_current_to_backup()==0);
    assert(image(owner.backup)==before);
    preserved_buffers(owner,f);
    for (auto result : {17, -3}) {
        fill_records(owner.current, 0x51);
        fill_records(owner.backup, 0xde);
        f.parse_result=result;
        unsigned count=f.parses;
        assert(owner.merge_current()==result && f.parses==count+1);
        assert(image(owner.current)==image(owner.backup));
        assert(records(owner.current)[record_bytes-1]==0x63);
        assert(owner.current.metadata.checksum==0x91);
        preserved_buffers(owner,f);
    }
}
}

// Observe the real maintained allocator's delete[] without replacing release
// or ownership logic. Startup and the three pending file callbacks below are
// explicit fixtures; they do not claim native disk parsing or game execution.
void operator delete[](void* memory) noexcept {
    if (fixture && fixture->released<fixture->buffers.size() &&
        memory==fixture->buffers[fixture->released]) {
        assert(fixture->save_count==3);
        ++fixture->released;
    }
    ::operator delete(memory);
}
void operator delete[](void* memory, std::size_t) noexcept { ::operator delete[](memory); }

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}

void ProgressSaveManager::load(void* argument) {
    assert(argument==nullptr && fixture && fixture->owner==nullptr);
    fixture->owner=this;
    assert(current.file_size==0 && backup.file_size==0);
    assert(!current.file_buffer && !current.decoded_buffer);
    assert(!backup.file_buffer && !backup.decoded_buffer);
    assert(field_124280==0);
    for (auto value : field_124284) assert(value==0);
    assert(current.profiles[17].header.size==0 && backup.fallback.header.size==0);
    assert(current.metadata.stones[8]==9 && backup.metadata.used_stones[8]==0);
    if (fixture->allocate_buffers) {
        for (auto& buffer : fixture->buffers) buffer=new std::uint8_t[64];
        current.file_size=123; backup.file_size=456;
        current.file_buffer=fixture->buffers[0];
        current.decoded_buffer=fixture->buffers[1];
        backup.file_buffer=fixture->buffers[2];
        backup.decoded_buffer=fixture->buffers[3];
    }
    fixture->load.entered.set_value();
    fixture->load.release.get_future().get();
}

void ProgressSaveManager::save(void* argument) {
    assert(argument==nullptr && fixture->owner==this && fixture->released==0);
    auto index=fixture->save_count++;
    assert(index<fixture->saves.size());
    if (fixture->allocate_buffers) preserved_buffers(*this,*fixture);
    else {
        assert(!current.file_buffer && !current.decoded_buffer);
        assert(!backup.file_buffer && !backup.decoded_buffer);
    }
    fixture->saves[index].entered.set_value();
    fixture->saves[index].release.get_future().get();
}

std::int32_t ProgressSaveManager::parse(ProgressSnapshot* snapshot) {
    assert(fixture->owner==this && snapshot==&current);
    assert(image(current)==image(backup));
    ++fixture->parses;
    records(current)[record_bytes-1]=0x63;
    current.metadata.checksum=0x91;
    return fixture->parse_result;
}
}

int main() {
    using namespace std::chrono_literals;
    Fixture f;
    fixture=&f;
    th20::DiagnosticAllocator allocator;
    th20::process_allocator=&allocator;
    auto loaded=f.load.entered.get_future();
    std::array<std::future<void>,3> saved;
    for (unsigned i=0; i<3; ++i) saved[i]=f.saves[i].entered.get_future();
    auto owner=std::make_unique<th20::ProgressSaveManager>();
    loaded.get();
    assert(f.owner==owner.get());
    // Loading is blocked and touches no records; verify the whole merge extent.
    merge_protocol(*owner,f);
    auto commit=std::async(std::launch::async, [&] { return owner->commit(); });
    assert(commit.wait_for(10ms)==std::future_status::timeout && f.save_count==0);
    f.load.release.set_value();
    assert(commit.get()==0);
    saved[0].get();
    auto replacement=std::async(std::launch::async, [&] { return owner->commit(); });
    assert(replacement.wait_for(10ms)==std::future_status::timeout && f.save_count==1);
    f.saves[0].release.set_value();
    assert(replacement.get()==0);
    saved[1].get();
    auto destroyed=std::async(std::launch::async, [&] { owner.reset(); });
    assert(destroyed.wait_for(10ms)==std::future_status::timeout && f.released==0);
    f.saves[1].release.set_value();
    saved[2].get();
    assert(destroyed.wait_for(10ms)==std::future_status::timeout && f.released==0);
    f.saves[2].release.set_value();
    destroyed.get();
    assert(f.save_count==3 && f.released==4 && !owner);

    Fixture empty;
    empty.allocate_buffers=false;
    fixture=&empty;
    th20::process_allocator=nullptr;
    auto empty_loaded=empty.load.entered.get_future();
    empty.load.release.set_value();
    for (auto& gate : empty.saves) gate.release.set_value();
    owner=std::make_unique<th20::ProgressSaveManager>();
    empty_loaded.get();
    owner.reset();
    assert(empty.save_count==1 && empty.released==0);
    fixture=nullptr;
}
