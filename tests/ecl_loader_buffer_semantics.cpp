#include "EclRuntime.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <functional>
#include <memory_resource>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
// Synthetic, aligned SCPT buffers. No original game data is embedded here.
struct File {
    std::array<std::uint32_t,512> words{};
    std::vector<std::uint32_t> headers;
    std::uint8_t* bytes() { return reinterpret_cast<std::uint8_t*>(words.data()); }
    File(std::initializer_list<const char*> names, bool includes=false) {
        words[0]=0x54504353; words[1]=1 | (includes ? 4u<<16 : 0u);
        words[4]=names.size();
        auto* offsets=words.data()+9+(includes ? 1 : 0);
        auto* cursor=reinterpret_cast<char*>(offsets+names.size());
        for(auto* name:names) {std::strcpy(cursor,name);cursor+=std::strlen(name)+1;}
        auto position=(reinterpret_cast<std::uint8_t*>(cursor)-bytes()+3)&~std::size_t{3};
        unsigned i=0;
        for(auto* name:names) {
            (void)name;offsets[i++]=position;headers.push_back(position);
            th20::EclInstruction first{},second{};
            first.length=16;first.opcode=1;second.length=16;second.opcode=20;
            std::memcpy(bytes()+position+16,&first,16);
            std::memcpy(bytes()+position+32,&second,16);position+=48;
        }
    }
};
struct Resource : std::pmr::memory_resource {
    std::unordered_map<void*,std::pair<std::size_t,std::size_t>> live;
    unsigned attempts=0,fail_at=0;
    void* do_allocate(std::size_t bytes,std::size_t alignment) override {
        if(++attempts==fail_at) throw std::bad_alloc();
        auto* p=std::pmr::new_delete_resource()->allocate(bytes,alignment);
        assert(live.emplace(p,std::pair{bytes,alignment}).second);return p;
    }
    void do_deallocate(void* p,std::size_t bytes,std::size_t alignment) override {
        auto entry=live.find(p);assert(entry!=live.end());
        assert(entry->second==std::pair(bytes,alignment));live.erase(entry);
        std::pmr::new_delete_resource()->deallocate(p,bytes,alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {return this==&other;}
} resource;
struct Loader : th20::EclLoader {
    std::function<int(std::uint8_t*)> include;
    int include_resources(std::uint8_t* block) override {assert(include);return include(block);}
};
std::vector<std::string> record_names(const th20::EclLoader& loader) {
    std::vector<std::string> result;for(const auto& r:loader.records)result.emplace_back(r.name);return result;
}
}

int main() {
    auto* old=std::pmr::set_default_resource(&resource);
    {
        Loader loader;File first{"z","a","a"},second{"b","a"};
        assert(loader.append(first.bytes())==0);
        assert(loader.append(second.bytes())==1);
        assert(loader.file_count==2 && loader.subroutine_count==5);
        assert((record_names(loader)==std::vector<std::string>{"a","a","a","b","z"}));
        const std::array<std::uint8_t*,5> expected{
            first.bytes()+first.headers[1],first.bytes()+first.headers[2],
            second.bytes()+second.headers[1],second.bytes()+second.headers[0],first.bytes()+first.headers[0]};
        for(unsigned i=0;i<expected.size();++i) {
            assert(loader.records[i].header==expected[i]);
            auto* instruction=loader.instruction(i,16);assert(instruction->opcode==20);
            instruction->stack_drop=7;assert(expected[i][32+12]==7);
        }
        File rejected{"x"};rejected.words[0]=0;
        assert(loader.append(rejected.bytes())==-1);
        assert(loader.files[2]==nullptr && loader.file_count==2 && loader.subroutine_count==5);
        rejected.words[0]=0x54504353;rejected.words[1]=2;
        assert(loader.append(rejected.bytes())==-1);
        assert(loader.files[0]==first.bytes() && loader.files[1]==second.bytes());
        assert(loader.records.size()==5 && loader.files[2]==nullptr && loader.file_count==2);
        File parent({"parent"},true),child{"child"};unsigned calls=0;
        loader.include=[&](std::uint8_t* block) {
            ++calls;assert(block==parent.bytes()+36);
            assert(loader.file_count==3 && loader.subroutine_count==6);
            assert(loader.files[2]==parent.bytes() && loader.records[4].header==parent.bytes()+parent.headers[0]);
            assert(loader.append(child.bytes())==3);return -91;
        };
        assert(loader.append(parent.bytes())==2 && calls==1);
        assert(loader.file_count==4 && loader.subroutine_count==7);
        assert((record_names(loader)==std::vector<std::string>{"a","a","a","b","child","parent","z"}));
    }
    assert(resource.live.empty());
    // Native insertion failure is nontransactional: counts and the borrowed
    // slot are already published, whereas file_count has not advanced.
    {
        Loader loader;File input{"a"};resource.fail_at=resource.attempts+1;
        bool threw=false;try{loader.append(input.bytes());}catch(const std::bad_alloc&){threw=true;}
        assert(threw && loader.files[0]==input.bytes() && loader.file_count==0);
        assert(loader.subroutine_count==1 && loader.records.empty());resource.fail_at=0;
    }
    assert(resource.live.empty());
    {
        Loader loader;File empty{};
        for(unsigned i=0;i<loader.files.size();++i)assert(loader.append(empty.bytes())==static_cast<int>(i));
        assert(loader.file_count==64 && loader.subroutine_count==0 && loader.records.empty());
    }
    assert(resource.live.empty());std::pmr::set_default_resource(old);
}
