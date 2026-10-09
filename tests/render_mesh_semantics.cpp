#include "Graphics.hpp"
#include "WeaponStoneInfo.hpp"
#include <cstdlib>
#include "Animation.hpp"
#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "EnemyState.hpp"
#include "RenderMesh.hpp"
#include "Session.hpp"
#include "WindowState.hpp"
#include <array>
#include <cassert>
#include <cmath>
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
Graphics::~Graphics() {
    assert(!resource_19c&&!resource_1a0&&!resource_1a4&&!surface_animation);
    assert(!direct3d&&!device&&!snapshot_pixels&&!dynamic_buffer&&!startup_scene);
}
Graphics process_graphics;
WeaponStoneInfo::~WeaponStoneInfo() {std::abort();}
void WeaponStoneInfo::enable() {std::abort();}
void WeaponStoneInfo::disable() {std::abort();}

// Only process allocation/window startup and unused callback retirement are
// boundaries. All mesh, State/Animation/Session lifetimes and math are real.
LockRegistry process_locks;
WindowState window_state{};
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
void DiagnosticAllocator::release_animation_callback(AnimationCallback* p) { assert(!p); }
}
namespace {
using namespace th20;
constexpr float pi=3.1415927410125732f;
float wrap(float value) {
    while (value>pi) value-=2*pi;
    while (value<-pi) value+=2*pi;
    return value;
}
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
        mesh.columns=0;mesh.vertices=nullptr;mesh.positions=nullptr;
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
    window_state.mesh_offset_x[0]=17;window_state.mesh_offset_x[1]=-11;
    window_state.mesh_offset_y[0]=29;window_state.mesh_offset_y[1]=13;
    assert(window_state.mesh_view_x(0)==17&&window_state.mesh_view_x(1)==-11);
    assert(window_state.mesh_view_y(0)==29&&window_state.mesh_view_y(1)==13);
    assert(window_state.mesh_width()==640&&window_state.mesh_height()==480);
    RenderMesh empty{0,0,0,0};empty.initialize(1,2,3,4);empty.update_strips();
    for (int index:{0,1}) {
        empty.select_context(index);
        assert(empty.view_index==index&&empty.context==&session.contexts[index]);
    }
    float u=7,v=9;
    render_mesh_uv({-64,960,73},u,v);assert(u==0&&v==2);
    render_mesh_uv({-0.0f,240,0},u,v);assert(std::signbit(u)&&v==0.5f);
    float nan=std::numeric_limits<float>::quiet_NaN();
    render_mesh_uv({nan,nan,0},u,v);assert(std::isnan(u)&&std::isnan(v));
    render_mesh_uv({320,120,999},u,u);assert(u==0.25f);
    assert(squared_norm_xy({3,4,100})==25);
    Angle angle(3);angle-=1;assert(float(angle)==2);angle-=6;close(angle,wrap(-4));
    EnemyMeshOwner defaults;
    assert(!defaults.mesh&&!defaults.field_04&&defaults.radius==0&&defaults.current_radius==0&&
           !defaults.color&&float(defaults.phase_x)==0&&float(defaults.phase_y)==0);
    EnemyState state;
    state.update_mesh();assert(&state.position_ref()==&state.motion_110.position);
    for (int columns:{1,2,5}) for (int rows:{1,2,4}) for (int view:{0,1}) {
        Grid grid(columns,rows);grid.mesh.view_index=view;
        grid.mesh.initialize(10,20,100,60);
        for (int col=0;col<columns;++col) for (int row=0;row<rows;++row) {
            const auto& p=grid.positions[col*rows+row];
            close(p.x,float(window_state.mesh_offset_x[view])+10+(col?float(col)*100/(columns-1):0));
            close(p.y,float(window_state.mesh_offset_y[view])+20+(row?float(row)*60/(rows-1):0));
            assert(p.z==0);
            const auto& vertex=grid.vertices[1+col*rows+row];
            close(vertex.position.x,p.x);close(vertex.position.y,p.y);
            assert(vertex.position.z==0&&vertex.color==0xffffffffu&&vertex.reciprocal_w==1);
            close(vertex.u,p.x<0?0:p.x/640);close(vertex.v,p.y<0?0:p.y/480);
        }
        grid.check_strips();
    }
    // Independent coordinate/color model checks the real whole deformation,
    // including old radius, XY weights, XYZ normalization and separate UV data.
    // Finite valid color conversions are required; malformed/NaN casts are open.
    for (int columns:{2,5}) for (int rows:{2,4}) for (int view:{0,1})
    for (float radius:{0.0f,25.0f,100.0f}) for (float clock:{-1.0f,0.0f,0.5f,2.0f})
    for (float z:{0.0f,13.0f}) {
        Grid grid(columns,rows);grid.mesh.view_index=view;
        EnemyMeshOwner owner;owner.mesh=&grid.mesh;owner.current_radius=radius;
        owner.radius=radius+1;owner.color=0x12345678;owner.phase_x.value=0.3f;owner.phase_y.value=-0.2f;
        state.mesh=&owner;state.field_2e8=view;state.motion_110.position={180,200,z};
        default_timer_clock.value=clock;
        std::array<unsigned char,sizeof(EnemyState)> before{};
        std::memcpy(before.data(),&state,sizeof(state));
        state.update_mesh();
        assert(std::memcmp(before.data(),&state,sizeof(state))==0);
        close(owner.current_radius,radius+clock*2);
        close(owner.phase_x,wrap(0.3f+(pi/16)*clock));
        close(owner.phase_y,wrap(-0.2f+(pi/32)*clock));
        float phase_x=0.3f,phase_y=-0.2f;
        for (int col=0;col<columns;++col) for (int row=0;row<rows;++row) {
            float x=180-radius-20+float(window_state.mesh_offset_x[view])+float(col)*(radius*2+40)/(columns-1);
            float y=200-radius-20+float(window_state.mesh_offset_y[view])+float(row)*(radius*2+40)/(rows-1);
            float dx=x-(180+float(window_state.mesh_offset_x[view]));
            float dy=y-(200+float(window_state.mesh_offset_y[view]));
            float dz=-z,weight=radius*radius-(dx*dx+dy*dy);
            unsigned color=0x00ffffff;
            if (weight>=0) {
                weight/=radius*radius;
                float length=float(std::sqrt(double((dx*dx+dy*dy)+dz*dz)));
                float magnitude=weight*32;
                if (length>=0.01f) { dx=(dx/length)*magnitude;dy=(dy/length)*magnitude; }
                else { dx*=magnitude;dy*=magnitude; }
                x+=(float(std::sin(double(phase_x)))*weight)*8+dx;
                y+=(float(std::sin(double(phase_y)))*weight)*8+dy;
                color=0xff000000;
                for (unsigned shift:{0u,8u,16u}) {
                    unsigned channel=(0x12345678u>>shift)&255;
                    color|=(unsigned(int(255.0f-float(255-channel)*weight))&255u)<<shift;
                }
            }
            auto& vertex=grid.vertices[1+col*rows+row];
            close(vertex.position.x,x);close(vertex.position.y,y);assert(vertex.color==color);
            const auto& p=grid.positions[col*rows+row];
            close(vertex.u,p.x/640);close(vertex.v,p.y/480);
            phase_x=wrap(phase_x+pi/32);phase_y=wrap(phase_y-pi/64);
        }
        grid.check_strips();state.mesh=nullptr;
    }
    Grid edge(2,2);EnemyMeshOwner owner;owner.mesh=&edge.mesh;owner.current_radius=0;
    state.mesh=&owner;state.field_2e8=0;state.motion_110.position={-100,-100,0};
    state.update_mesh();
    for (const auto& p:edge.positions) assert(p.x==1&&p.y==1);
    for (unsigned i=1;i<edge.vertices.size()-1;++i)
        assert(edge.vertices[i].position.x==1&&edge.vertices[i].position.y==1);
    edge.check_strips();state.mesh=nullptr;
    window_state.scaled_width=50;window_state.scaled_height=60;
    owner.current_radius=25;owner.radius=25;state.mesh=&owner;state.motion_110.position={200,200,0};
    state.update_mesh();
    for (const auto& p:edge.positions) assert(p.x==49&&p.y==59);
    for (unsigned i=1;i<edge.vertices.size()-1;++i)
        assert(edge.vertices[i].position.x==49&&edge.vertices[i].position.y==59);
    edge.check_strips();state.mesh=nullptr;
}
