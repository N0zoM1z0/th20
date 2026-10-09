#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "RenderMesh.hpp"
#include "Session.hpp"
#include "WindowState.hpp"
#include "DiagnosticAllocator.hpp"
#include "WeaponStoneInfo.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <limits>
#include <memory>
#include <vector>
#include <array>
#include <mutex>

namespace {
using namespace th20;
struct Allocation { void* pointer; int bytes; const char* label; };
struct Spawn { AnimationFile* file; const char* stem; int script,layer; const Vector3* position; float rotation; unsigned flags; Animation** output; Animation* animation; };
struct Event { int kind; void* pointer; unsigned handle; };
std::vector<Allocation> allocations;
std::vector<Spawn> spawns;
std::vector<Event> events;
std::vector<std::unique_ptr<Animation>> animations;
unsigned seed=0,clear_count=0;
Animation* add_animation() {
    auto animation=std::make_unique<Animation>();
    animation->base.flags.bytes_00.field_00=0xa5;
    animation->base.flags.bytes_00.field_01=0x9c;
    animation->base.flags.byte_08=static_cast<unsigned char>(seed);
    animation->base.flags.other_0b=0x2b;
    animation->base.flags.layer_mode=3;
    animation->base.flags.field_0c=0x6a;
    animation->base.flags.word_04=0xa5u|(seed&1?1u<<23:0);
    animation->base.variables.field_00=-971;
    animation->handle.value=static_cast<unsigned>(animations.size()+1);
    auto* result=animation.get();animations.push_back(std::move(animation));return result;
}
void reset() {
    animations.clear();assert(allocations.empty());events.clear();spawns.clear();clear_count=0;
}
void filled(const void* p,std::size_t bytes) {
    auto* data=static_cast<const unsigned char*>(p);
    for (std::size_t i=0;i<bytes;++i) assert(data[i]==0x35);
}
void check_animation(Animation* animation,int rows,bool grid) {
    assert(animation->geometry_bytes==sizeof(SpriteTexturedVertex)*rows*2);
    assert(animation->base.flags.bytes_00.field_00==(rows>2?12:0));
    assert(animation->base.flags.byte_08==(rows>2&&grid?(seed|0x30):seed));
    assert(animation->base.variables.field_00==(rows>2?rows:-971));
    if (rows<=2) {filled(animation->geometry,animation->geometry_bytes);return;}
    auto* vertices=animation->mesh_vertices();
    for(int i=0;i<rows*2;++i) {
        filled(&vertices[i].position.x,sizeof(float)*2);
        filled(&vertices[i].u,sizeof(float)*2);
        assert(vertices[i].position.z==0 && vertices[i].reciprocal_w==1);
        assert(vertices[i].color==0xffffffffu);
    }
}
}
namespace th20 {
// Genuine unresolved process/VM/renderer interfaces are explicit fixture boundaries.
// Heap captures execute malloc/free and actual slot-one guards, retaining ASan bounds.
LockRegistry process_locks;
WindowState window_state{};
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
DiagnosticAllocator::~DiagnosticAllocator()=default;
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
void* DiagnosticAllocator::allocate_bytes(std::int32_t bytes,const char* label) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    assert(bytes>=0);void* p=std::malloc(bytes);assert(p || bytes==0);
    if(bytes)std::memset(p,0x35,bytes);
    allocations.push_back({p,bytes,label});events.push_back({1,p,0});return p;
}
void DiagnosticAllocator::release_bytes(void* p) {
    if(!p)return;
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    auto it=allocations.begin();while(it!=allocations.end()&&it->pointer!=p)++it;
    assert(it!=allocations.end());events.push_back({2,p,0});allocations.erase(it);std::free(p);
}
void DiagnosticAllocator::release_animation_callback(AnimationCallback* p) {assert(!p);}
Graphics::~Graphics() {
    assert(!resource_19c&&!resource_1a0&&!resource_1a4&&!surface_animation);
    assert(!direct3d&&!device&&!snapshot_pixels&&!dynamic_buffer&&!startup_scene);
}
Graphics process_graphics;
// Empty original-file resource retirement is bounded; actual PMR string members retire.
AnimationFile::~AnimationFile() {assert(!bytes&&!templates&&!sprites&&!scripts&&!textures);}
WeaponStoneInfo::~WeaponStoneInfo(){std::abort();}
void WeaponStoneInfo::enable(){std::abort();}
void WeaponStoneInfo::disable(){std::abort();}
AnimationHandle AnimationFile::spawn(const char* stem,int script,const Vector3* position,
                                     float rotation,int layer,unsigned flags,Animation** output) {
    Animation* animation=add_animation();
    animation->base.field_14=layer;
    spawns.push_back({this,stem,script,layer,position,rotation,flags,output,animation});
    events.push_back({3,animation,animation->handle.value});
    if(output)*output=animation;
    return animation->handle;
}
Animation* AnimationHandle::resolve() {
    events.push_back({4,this,value});
    if(value&&value<=animations.size())return animations[value-1].get();
    value=0;return nullptr;
}
void AnimationHandle::retire() {
    events.push_back({5,this,value});value=0;
}
void Animation::clear_flag0_recursively() {
    assert(user_data);events.push_back({6,this,0});++clear_count;
    base.flags.word_04&=~1u;
}
}
int main() {
    using namespace th20;
    AnimationFile global_file,decoy_file;
    unsigned cases=0;
    for(int surface:{0,1,-1}) {
        reset();process_graphics.graphics_ready=1;
        {RenderMesh empty(std::numeric_limits<int>::min(),-9,surface,999);
         assert(!empty.columns&&!empty.rows&&!empty.root.value&&!empty.strip_handles);
         assert(!empty.strips&&!empty.vertices&&!empty.positions&&!empty.view_index&&!empty.context);
         assert(events.empty());}
        assert(events.size()==1&&events[0].kind==5&&!events[0].handle);++cases;
    }
    process_graphics.graphics_ready=0;
    for(int rows:{0,1,2,3,5})for(unsigned flag=0;flag<256;++flag)for(bool grid:{false,true}) {
        reset();seed=flag;process_graphics.surface_animation=&global_file;
        Graphics receiver;receiver.surface_animation=&decoy_file;
        AnimationHandle h=grid?receiver.create_grid_strip(rows,-71):receiver.create_surface_strip(rows,-71);
        auto* animation=h.resolve();assert(animation);
        assert(spawns.size()==1 && spawns[0].file==&global_file && spawns[0].script==-71);
        assert(spawns[0].layer==(grid?41:42) && !spawns[0].position);
        assert(spawns[0].rotation==0&&!spawns[0].flags&&!spawns[0].output&&!spawns[0].stem);
        assert(allocations.size()==1&&allocations[0].bytes==int(sizeof(SpriteTexturedVertex)*rows*2));
        assert(std::strstr(allocations[0].label,"sprtlib.h:911 void"));
        check_animation(animation,rows,grid);
        receiver.surface_animation=nullptr;process_graphics.surface_animation=nullptr;++cases;
    }
    reset();
    int resource_token=0; // Borrowed opaque API token; only pointer presence is consumed.
    for(int columns:{1,2,5})for(int rows:{1,2,3,4})for(int view:{0,1})
    for(int width:{640,960,1280})for(int surface:{0,1,-7})for(unsigned flag:{0u,1u,0x82u,0xffu}) {
        reset();seed=flag;window_state.scaled_width=width;
        process_graphics.resource_19c=reinterpret_cast<graphics_api::Resource*>(&resource_token);
        process_graphics.surface_animation=&global_file;
        std::array<void*,4> buffers{};unsigned root=0;std::vector<unsigned> handles;
        {
            RenderMesh mesh(columns,rows,surface,view);
            assert(mesh.columns==columns&&mesh.rows==rows&&mesh.view_index==view);
            assert(mesh.context==&session.contexts[view]);
            assert(allocations.size()==unsigned(4+columns));
            assert(allocations[0].bytes==int(sizeof(AnimationHandle)*columns-1));
            assert(allocations[1].bytes==int(sizeof(Animation*)*columns-1));
            assert(allocations[2].bytes==int(sizeof(SpriteTexturedVertex)*columns*rows));
            assert(allocations[3].bytes==int(sizeof(Vector3)*columns*rows));
            for(int i=0;i<4;++i)assert(std::strstr(allocations[i].label,"effect.cpp:"));
            buffers={mesh.vertices,mesh.positions,mesh.strip_handles,mesh.strips};
            filled(mesh.vertices,sizeof(SpriteTexturedVertex)*columns*rows);
            filled(mesh.positions,sizeof(Vector3)*columns*rows);
            auto* animation=mesh.root.resolve();root=mesh.root.value;
            assert(animation->user_data==&mesh&&clear_count==1);
            assert(!(animation->base.flags.word_04&1u));
            check_animation(animation,2,!surface);
            assert(spawns.size()==unsigned(columns));
            int script=surface?(width==640?13:width==960?14:15):0;
            for(const auto& call:spawns)assert(call.script==script&&call.layer==(surface?42:41));
            if(surface)assert(animation->base.field_14==27);
            for(int col=0;col<columns-1;++col) {
                auto* strip=mesh.strip_handles[col].resolve();assert(mesh.strips[col]==strip);
                handles.push_back(mesh.strip_handles[col].value);
                assert(!strip->base.flags.bytes_00.field_01&&!strip->base.flags.layer_mode);
                assert(strip->base.flags.other_0b==0x2b);
                assert(!strip->user_data);
                if(surface) {
                    assert(strip->base.field_14==27);
                    assert(strip->base.flags.field_0c==(flag&1?0x6a:1));
                }else assert(strip->base.field_14==41);
                check_animation(strip,rows,!surface);
            }
            events.clear();
        }
        assert(events.size()==unsigned(5+columns-1));
        assert(events[0].kind==5&&events[0].handle==root);
        assert(events[1].kind==2&&events[1].pointer==buffers[0]);
        assert(events[2].kind==2&&events[2].pointer==buffers[1]);
        for(int col=0;col<columns-1;++col)assert(events[3+col].kind==5&&events[3+col].handle==handles[col]);
        assert(events[2+columns].kind==2&&events[2+columns].pointer==buffers[2]);
        assert(events[3+columns].kind==2&&events[3+columns].pointer==buffers[3]);
        assert(allocations.size()==unsigned(columns));
        process_graphics.resource_19c=nullptr;process_graphics.surface_animation=nullptr;++cases;
    }
    reset();
    Vector3 position(1,-2,3);const char stem[]="surface";
    for(bool output_present:{false,true})for(int kind:{0,1,2}) {
        reset();Animation* output=nullptr;Animation** location=output_present?&output:nullptr;
        AnimationHandle handle=kind==0?global_file.spawn(stem,4,19,location):
          kind==1?global_file.spawn(stem,4,position,-0.25f,19,location):
                  global_file.spawn_flag8(stem,4,position,-0.25f,19,location);
        assert(handle.value==1&&spawns.size()==1);const auto& call=spawns.front();
        assert(call.file==&global_file&&call.stem==stem&&call.script==4&&call.layer==19);
        assert(call.position==(kind==0?nullptr:&position)&&call.rotation==(kind==0?0:-0.25f));
        assert(call.flags==(kind==2?8u:0u)&&call.output==location);
        assert(output==(output_present?call.animation:nullptr));++cases;
    }
    reset();
    std::printf("Whole maintained mesh lifetime: %u cases PASS\n",cases);
}
