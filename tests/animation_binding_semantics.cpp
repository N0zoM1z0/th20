#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
void DiagnosticAllocator::release_animation_callback(AnimationCallback* callback) {
    assert(this == process_allocator && callback == nullptr);
}
const Matrix4 identity_matrix = [] { Matrix4 value; for (int i=0;i<4;++i) value.elements[i][i]=1.0f; return value; }();
// Original file retirement/loading is still undefined. This fixture permits
// only a borrowed template view; no owned file resource reaches destruction.
// Three-argument VM binding is not exercised; accidental entry fails hard.
void AnimationFile::bind_animation(Animation*, std::int32_t, Animation*) { std::abort(); }
AnimationFile::~AnimationFile() {
    assert(bytes == nullptr && sprites == nullptr && scripts == nullptr && textures == nullptr);
    assert(templates == nullptr);
}
}
namespace {
using namespace th20;
using Image = std::array<unsigned char,sizeof(Animation)>;
Image image(const Animation& a) { Image r; std::memcpy(r.data(), &a, r.size()); return r; }
template<class T> void replace(Image& r, std::size_t offset, const T& value) {
    std::memcpy(r.data()+offset,&value,sizeof(value));
}
Timer zero_assignment(Timer before) {
    before.previous=-1; before.current=0; before.current_fraction=0.0f;
    if (!(before.flags&1u)) before.flags=(before.flags&~6u)|1u;
    return before;
}
// Independent metadata model: a frame's remaining ordinal counts direct
// matching siblings. A descendant receives a copy of the remaining value.
// Each ancestry path can therefore select a different scoped ordinal.
int expected(const std::array<std::vector<int>,33>& edges,
             const std::array<std::int16_t,33>& identities,
             int selected,int identifier,int ordinal) {
    struct Frame {int root, remaining; std::size_t index; int completed_child;};
    std::vector<Frame> stack{{selected,ordinal,0,-1}};
    while(!stack.empty()) {
        auto& f=stack.back();
        if(f.completed_child>=0) {
            if(identities[f.root]==-2 && f.index==edges[f.root].size()) return f.completed_child;
            f.completed_child=-1;
        }
        if(f.index==edges[f.root].size()) {stack.pop_back();continue;}
        int child=edges[f.root][f.index++];
        bool match=identifier==-1 || identities[child]==identifier;
        if(match && f.remaining==0) return child;
        if(match) --f.remaining;
        f.completed_child=child;
        int inherited=f.remaining;
        stack.push_back({child,inherited,0,-1});
    }
    return -1;
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator; process_allocator=&allocator;
    unsigned cases=0;
    const std::array<std::int16_t,8> identities_pool={0,1,7,-1,-2,-32768,32767,2};
    const std::array<int,11> requests={-32768,-2,-1,0,1,2,7,32767,32768,65535,65536};
    const std::array<int,6> ordinals={-3,-1,0,1,2,40};
    for(unsigned seed=0;seed<72;++seed) {
        std::array<Animation,33> values;
        std::array<std::vector<int>,33> edges;
        std::array<std::int16_t,33> identities;
        for(unsigned i=0;i<33;++i) {
            identities[i]=identities_pool[(seed+i*5)%identities_pool.size()];
            values[i].base.field_440=static_cast<std::uint16_t>(identities[i]);
        }
        for(unsigned i=1;i<32;++i) {
            unsigned p=seed%3==0?i-1:seed%3==1?0:(i-1)/2;
            values[p].child_links[1].insert_after(&values[i].child_links[0]);
            edges[p].insert(edges[p].begin(),static_cast<int>(i));
            values[i].parent_558=&values[p];
        }
        // A null-valued node must be skipped without terminating siblings.
        IntrusiveLink<Animation> placeholder(nullptr);
        values[0].child_links[1].insert_after(&placeholder);
        {
            IntrusiveIterator<Animation> observer(&values[0].child_links[1]);
            std::array<Image,33> before;
            for(unsigned i=0;i<33;++i) before[i]=image(values[i]);
            auto placeholder_before=placeholder;
            for(int selected : {0,1,15,31,32}) for(int id : requests) for(int ordinal : ordinals) {
                int e=expected(edges,identities,selected,id,ordinal);
                assert(values[selected].find_child(id,ordinal)==(e<0?nullptr:&values[e]));
                for(unsigned i=0;i<33;++i) assert(image(values[i])==before[i]);
                assert(std::memcmp(&placeholder,&placeholder_before,sizeof(placeholder))==0);
                ++cases;
            }
        }
        placeholder.detach();
        for(auto& a:values) a.child_links[0].detach();
    }
    // This table independently distinguishes scoped ordinals from a flattened
    // nth-descendant implementation: A's unsuccessful subtree does not consume
    // B's ordinal. Negative ordinals remain native decrementing values.
    {
        std::array<Animation,4> a;
        a[0].child_links[1].insert_after(&a[3].child_links[0]);
        a[0].child_links[1].insert_after(&a[1].child_links[0]);
        a[1].child_links[1].insert_after(&a[2].child_links[0]);
        for(auto& v:a) v.base.field_440=7;
        assert(a[0].find_child(7,0)==&a[1]);
        assert(a[0].find_child(7,1)==&a[2]);
        assert(a[0].find_child(7,2)==nullptr);
        assert(a[0].find_child(-1,2)==nullptr);
        assert(a[0].find_child(7,-1)==nullptr);
        a[0].base.field_440=static_cast<std::uint16_t>(-2);
        assert(a[0].find_child(999,0)==&a[3]);
        for(auto& v:a) v.child_links[0].detach();
        cases+=6;
    }
    for(unsigned seed=0;seed<128;++seed) {
        std::array<Animation,3> templates;
        Animation dest, child;
        AnimationFile file;
        file.templates=templates.data();
        dest.child_links[1].insert_after(&child.child_links[0]);
        dest.geometry=allocator.allocate_bytes(static_cast<std::int32_t>(32+seed%7), "template fixture");
        dest.geometry_bytes=32+seed%7;
        dest.handle.value=0x9234u+seed;
        dest.user_data=&file;
        dest.parent_558=&child;
        dest.field_550=0; // Native retirement's nonreturning branch is excluded.
        for(unsigned i=0;i<3;++i) {
            auto* bytes=reinterpret_cast<unsigned char*>(&templates[i].base);
            for(unsigned j=0;j<sizeof(AnimationBase);++j)
                bytes[j]=static_cast<unsigned char>((seed*17+i*11+j*3)&0x3fu);
        }
        {
            IntrusiveIterator<Animation> observer(&dest.child_links[1]);
            auto source_before=image(templates[seed%3]);
            dest.field_570=0x12345678;dest.field_5dc=0xffffffff;dest.field_5e0=0x80000000;
            dest.timer_4c8.flags=seed*13u;dest.timer_4d8.flags=seed*7u;
            dest.timer_4c8.previous=17;dest.timer_4c8.current=19;dest.timer_4c8.current_fraction=19.5f;
            dest.timer_4d8.previous=-17;dest.timer_4d8.current=-19;dest.timer_4d8.current_fraction=-19.5f;
            Image e=image(dest);
            std::memcpy(e.data(),&templates[seed%3].base,sizeof(AnimationBase));
            replace(e,offsetof(Animation,field_570),std::uint32_t(0));
            replace(e,offsetof(Animation,field_5dc),std::uint32_t(0));
            replace(e,offsetof(Animation,field_5e0),std::uint32_t(0));
            replace(e,offsetof(Animation,timer_4c8),zero_assignment(dest.timer_4c8));
            replace(e,offsetof(Animation,timer_4d8),zero_assignment(dest.timer_4d8));
            file.apply_template(&dest,static_cast<std::int32_t>(seed%3));
            assert(image(dest)==e);
            assert(image(templates[seed%3])==source_before);
            ++cases;
            dest.set_field_5dc(0x80000000u+seed);
            dest.set_field_5e0(0xffffffffu-seed);
            assert(dest.field_5dc==0x80000000u+seed && dest.field_5e0==0xffffffffu-seed);
            dest.clear_pending_fields();
            assert(dest.field_5dc==0 && dest.field_5e0==0);
            ++cases;
        }
        child.child_links[0].detach();
        file.templates=nullptr;
    }
    assert(cases==24022);
    std::cout<<"PASS "<<cases<<" Animation template and scoped lookup cases\n";
}
