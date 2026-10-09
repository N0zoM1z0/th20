#include "Animation.hpp"
#include "Graphics.hpp"
#include "WeaponStoneInfo.hpp"
#include <cstdlib>
#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "RenderMesh.hpp"
#include "Session.hpp"
#include "WindowState.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cfenv>
#include <cstring>
#include <cstdio>
#include <limits>
#include <source_location>
#include <vector>

namespace th20 {
// Original VM creation is uncalled: resource-absent mesh construction executes.
AnimationHandle Graphics::create_grid_strip(std::int32_t,std::int32_t) {std::abort();}
AnimationHandle Graphics::create_surface_strip(std::int32_t,std::int32_t) {std::abort();}
Animation* AnimationHandle::resolve() {std::abort();}
void AnimationHandle::retire() {assert(!value);value=0;}
void Animation::clear_flag0_recursively() {std::abort();}

// Only process allocation/window startup and unused callback retirement are
// boundaries. Mesh, Animation/Session lifetimes and math execute maintained bodies.
LockRegistry process_locks;
WindowState window_state{};
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
// Native graphics resource teardown is outside this host fixture. Construction,
// viewport members and both Worker member lifetimes execute maintained bodies.
Graphics::~Graphics() {
    assert(!direct3d&&!device&&!resource_19c&&!resource_1a0&&!resource_1a4);
    assert(!surface_animation&&!snapshot_pixels&&!dynamic_buffer&&!startup_scene);
}
Graphics process_graphics;
// Uncalled Overlay virtual boundaries supply RTTI for Context's maintained
// cast. This fixture constructs no Overlay and cannot execute these methods.
WeaponStoneInfo::~WeaponStoneInfo() {std::abort();}
void WeaponStoneInfo::enable() {std::abort();}
void WeaponStoneInfo::disable() {std::abort();}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
void DiagnosticAllocator::release_animation_callback(AnimationCallback* p) { assert(!p); }
}
namespace {
using namespace th20;
void close(float actual,float expected,std::source_location location=std::source_location::current()) {
    if (!((std::isnan(actual)&&std::isnan(expected)) || actual==expected ||
          std::abs(actual-expected)<=2e-4f*(1+std::abs(expected))))
        std::fprintf(stderr,"mesh model mismatch at %u: %.9g != %.9g\n",location.line(),actual,expected);
    assert((std::isnan(actual)&&std::isnan(expected)) || actual==expected ||
           std::abs(actual-expected)<=2e-4f*(1+std::abs(expected)));
}
struct Grid {
    RenderMesh mesh{0,0,0,0};
    std::vector<SpriteTexturedVertex> vertices;
    std::vector<Vector3> positions;
    std::vector<Animation> strips;
    std::vector<Animation*> strip_pointers;
    std::vector<std::vector<SpriteTexturedVertex>> strip_vertices;
    Grid(int columns,int rows):vertices(columns*rows+2),positions(columns*rows),
        strips(columns?columns-1:0),strip_pointers(strips.size()),strip_vertices(strips.size()) {
        mesh.columns=columns;mesh.rows=rows;
        mesh.vertices=vertices.data()+1;mesh.positions=positions.data();
        vertices.front().color=0x12345678;vertices.back().color=0x76543210;
        for (unsigned i=0;i<strips.size();++i) {
            strip_vertices[i].resize(2*rows);
            strips[i].geometry=strip_vertices[i].data();
            strip_pointers[i]=&strips[i];
        }
        mesh.strips=strip_pointers.data();
    }
    ~Grid() { for (auto& strip:strips) strip.geometry=nullptr;
        mesh.root.value=0;mesh.columns=0;mesh.vertices=nullptr;mesh.positions=nullptr;
        mesh.strip_handles=nullptr;mesh.strips=nullptr; }
    void check_strips() const {
        assert(vertices.front().color==0x12345678&&vertices.back().color==0x76543210);
        for (int col=0;col<mesh.columns-1;++col) for (int row=0;row<mesh.rows;++row) {
            const auto& out=strip_vertices[col];
            assert(std::memcmp(&out[2*row],mesh.vertices+col*mesh.rows+row,sizeof(SpriteTexturedVertex))==0);
            assert(std::memcmp(&out[2*row+1],mesh.vertices+(col+1)*mesh.rows+row,sizeof(SpriteTexturedVertex))==0);
        }
    }
};
}
int main() {
    using namespace th20;
    window_state.scaled_width=640;window_state.scaled_height=480;
    window_state.client_width=1279;window_state.client_height=959;
    window_state.mesh_offset_x[0]=391;window_state.mesh_offset_x[1]=-97;
    window_state.mesh_offset_y[0]=-193;window_state.mesh_offset_y[1]=83;
    const float nan=std::numeric_limits<float>::quiet_NaN();
    const std::array<std::array<float,4>,7> shapes{{
        {10,20,100,60},{-64,-96,800,1200},{-0.0f,-0.0f,0,0},
        {1280,960,-320,-240},{nan,40,100,60},{30,nan,100,60},{10,20,nan,nan}}};
    unsigned cases=0;
    RenderMesh empty{0,0,0,0};empty.view_index=std::numeric_limits<int>::max();
    empty.rows=1;
    std::feclearexcept(FE_ALL_EXCEPT);
    empty.initialize_surface_grid(nan,nan,0,0);
    assert(!empty.vertices&&!empty.positions);
    assert(std::fetestexcept(FE_INVALID|FE_DIVBYZERO)==0);
    for(int columns:{1,2,5}) for(int rows:{1,2,4})
    for(int view:{std::numeric_limits<int>::min(),-1,0,1,std::numeric_limits<int>::max()})
    for(const auto& shape:shapes) for(int offset:{0,517,-631}) {
        for(int i=0;i<6;++i) {
            process_graphics.viewports[i].offset_x=offset+101*i;
            process_graphics.viewports[i].offset_y=-offset-73*i;
        }
        Grid grid(columns,rows);grid.mesh.view_index=view;
        grid.mesh.context=&session.contexts[1];grid.mesh.root.value=0x12345678;
        std::array<unsigned char,sizeof(RenderMesh)> original{};
        std::memcpy(original.data(),&grid.mesh,sizeof(grid.mesh));
        std::array<unsigned char,sizeof(Graphics)> before{};
        std::memcpy(before.data(),&process_graphics,sizeof(process_graphics));
        grid.mesh.initialize_surface_grid(shape[0],shape[1],shape[2],shape[3]);
        assert(std::memcmp(original.data(),&grid.mesh,sizeof(grid.mesh))==0);
        assert(std::memcmp(before.data(),&process_graphics,sizeof(process_graphics))==0);
        float x=shape[0];
        const float dx=shape[2]/float(columns-1),dy=shape[3]/float(rows-1);
        for(int col=0;col<columns;++col) {
            float y=shape[1];
            for(int row=0;row<rows;++row) {
                const auto& p=grid.positions[col*rows+row];
                const auto& vertex=grid.vertices[1+col*rows+row];
                close(p.x,x);close(p.y,y);assert(p.z==0);
                close(vertex.position.x,x+float(offset+202));
                close(vertex.position.y,y+float(-offset-146));
                assert(vertex.position.z==0&&vertex.color==0xffffffffu&&vertex.reciprocal_w==1);
                close(vertex.u,x<0?0:x/640);close(vertex.v,y<0?0:y/480);
                if(col==0&&shape[0]==0) assert(std::signbit(vertex.u)==std::signbit(shape[0]));
                if(row==0&&shape[1]==0) assert(std::signbit(vertex.v)==std::signbit(shape[1]));
                y+=dy;
            }
            x+=dx;
        }
        grid.check_strips();++cases;
    }
    assert(cases==945);
    std::printf("945 surface grids plus null-buffer zero-column early exit passed\n");
}
