#include "Animation.hpp"
#include "SpriteVertices.hpp"
#include "WindowState.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_(){}
WindowState window_state{}; // Fixture global; native startup remains unresolved.
const Matrix4 identity_matrix=[] {Matrix4 m;for(int i=0;i<4;++i)m.elements[i][i]=1;return m;}();
}
namespace {
using namespace th20;
using Point=std::array<float,3>;
using Image=std::array<unsigned char,sizeof(Animation)>;
Image image(const Animation& a) {Image r;std::memcpy(r.data(),&a,r.size());return r;}
Point read(const Vector3& v) {return {v.x,v.y,v.z};}
float normalized(float x) {
    constexpr float p=3.1415927410125732f;
    for(unsigned i=0;i<34;++i) {
        if(x>p)x-=2*p;else if(x<-p)x=2*p+x;else break;
    }
    return x;
}
bool same(float a,float b) {return std::isnan(a)?std::isnan(b):std::bit_cast<unsigned>(a)==std::bit_cast<unsigned>(b);}
void equal(Point a,Point b) {for(unsigned i=0;i<3;++i)assert(same(a[i],b[i]));}
Point sum(Point a,Point b) {for(unsigned i=0;i<3;++i)a[i]+=b[i];return a;}
// Independent frame oracle: compose a chain from the root back towards the leaf.
// Rotation uses the independently recovered scalar(double)->float boundary.
Point framed(const Animation& leaf,Point point) {
    std::array<const Animation*,5> chain{};unsigned n=0;const Animation* a=&leaf;
    while(true) {
        assert(n<chain.size());chain[n++]=a;
        if(!a->parent_558 || (a->base.flags.word_04&(1u<<12)))break;
        a=a->parent_558;
    }
    Point accumulated{};
    for(unsigned k=n;k>0;--k) {
        const Animation& node=*chain[k-1];Point local=k==1?point:sum(sum(read(node.vector_5bc),read(node.base.vector_2c)),read(node.base.vector_484));
        unsigned screen=node.base.flags.field_0c;
        if(screen>=1 && screen<=4) {
            float factor=window_state.scale*(screen%2?1.0f:0.5f);
            for(float& v:local)v*=factor;
        }
        if(k==n) {
            unsigned layer=node.base.flags.layer_mode;
            if(layer) {local[0]+=float(layer==1?window_state.field_0058:window_state.field_0060);local[1]+=float(layer==1?window_state.field_005c:window_state.field_0064);}
            accumulated=local;
        } else {
            const Animation& parent=*chain[k];unsigned flags=node.base.flags.word_04;
            if(flags&(1u<<5)) {
                float sn=float(std::sin(double(parent.base.vector_38.z))),cs=float(std::cos(double(parent.base.vector_38.z)));
                float x=local[0]*cs-local[1]*sn;
                local[1]=local[1]*cs+local[0]*sn;local[0]=x;
            }
            if(flags&(1u<<22)) {local[0]*=parent.base.vector_50.x;local[1]*=parent.base.vector_50.y;}
            accumulated=sum(local,accumulated);
        }
    }
    return accumulated;
}
Point position_model(const Animation& a) {return framed(a,sum(sum(read(a.vector_5bc),read(a.base.vector_2c)),read(a.base.vector_484)));}
void configure(Animation& a,unsigned seed) {
    float s=float(seed)+0.125f;
    a.vector_5bc={s,-s,0.5f*s};a.base.vector_2c={3.25f*s,-4.75f,6.25f};a.base.vector_484={-7.5f,8.75f*s,-9.25f*s};
    a.base.vector_38={1.75f,-0.5f,0.375f*s};a.base.vector_50={-1.5f*s,2.25f*s};
    a.base.variables.field_10=2.75f;a.base.variables.field_14=-1.75f;a.base.variables.field_18=4.25f;a.base.variables.field_1c=-2.125f;
    a.base.variables.field_04=-3;a.base.field_78=0.125f;a.base.field_7c=-0.375f;
    a.base.color_490=0x12345678;a.base.color_494=0xa1b2c3d4;
    for(unsigned i=0;i<4;++i)a.base.vectors_378[i]={float(i)*0.125f-0.25f,float(i)*0.375f-0.125f};
    a.base.flags.word_04=0x80200400u;a.geometry_bytes=0x11223344;
}
struct Expected {Point p;float rhw;unsigned color;float u,v;};
Expected initial() {return {{-91.25f,92.5f,-93.75f},94.25f,0xdeadbeef,-95.5f,96.75f};}
template<class T> void fill(T& v) {auto e=initial();v.position={e.p[0],e.p[1],e.p[2]};v.color=e.color;v.u=e.u;v.v=e.v;if constexpr(requires {v.reciprocal_w;})v.reciprocal_w=e.rhw;}
template<class T> void check(const T& v,const Expected& e) {equal(read(v.position),e.p);assert(v.color==e.color && same(v.u,e.u) && same(v.v,e.v));if constexpr(requires {v.reciprocal_w;})assert(same(v.reciprocal_w,e.rhw));}
// Shape specifications feed one independent vertex oracle. The oracle never
// invokes maintained geometry, position, polar or angle helper implementations.
void geometry_model(const Animation& a,std::array<Expected,34>& e) {
    unsigned kind=a.base.flags.bytes_00.field_00;
    const bool screen=kind==9||kind==13||kind==14;
    const bool closed=kind==9||kind==47;
    const bool strip=kind==24||kind==25;
    const bool triangle=kind==48;
    if(!screen&&!closed&&!strip&&!triangle)return;
    unsigned color=a.base.flags.color_mode?a.base.color_494:a.base.color_490;
    auto xy=[](float angle,float radius) {return Point{std::cos(angle)*radius,std::sin(angle)*radius,0.0f};};
    auto scale_radius=[&](float r,unsigned axis) {
        if(a.parent_55c && !(a.base.flags.word_04&(1u<<12)))r=(axis?a.parent_55c->base.vector_50.y:a.parent_55c->base.vector_50.x)*r;
        if(a.base.flags.field_0c==1)r*=window_state.scale;
        if(a.base.flags.field_0c==2)r=(window_state.scale*0.5f)*r;
        return r;
    };
    constexpr float p=3.1415927410125732f;
    if(triangle) {
        float radius=scale_radius(a.base.variables.field_10,0);
        std::array<float,3> angles={-p/2,-p/2+(p*2)/3*2,-p/2+(p*2)/3};
        Point origin=xy(angles[0],radius);
        for(unsigned i=0;i<3;++i) {
            e[i].p=xy(angles[i],radius);
            for(unsigned c=0;c<3;++c)e[i].p[c]-=origin[c];
            e[i].color=i?color:a.base.color_490;
            unsigned uv=i+1;e[i].u=i?a.base.vectors_378[uv].x+a.base.field_78:(a.base.vectors_378[1].x-a.base.vectors_378[0].x)/2+a.base.vectors_378[0].x+a.base.field_78;
            e[i].v=a.base.vectors_378[i?uv:0].y+a.base.field_7c;
        }
        e[0].p={0,0,0};return;
    }
    int count=a.base.variables.field_00;
    float width=screen?a.base.vector_50.x:a.base.variables.field_10;
    float middle=screen?a.base.vector_50.y:a.base.variables.field_14;
    std::array<float,2> radii={middle+width*0.5f,middle-width*0.5f};
    Point center=screen?position_model(a):Point{};
    float height=0;
    float arc=closed?p*2:strip?a.base.variables.field_10:a.base.vector_38.x;
    float angle=closed?a.base.vector_38.z:normalized((strip?a.base.variables.field_1c:a.base.vector_38.z)-arc/2);
    if(kind==14)angle=normalized(a.base.vector_38.z);
    if(strip) {
        height=a.base.variables.field_14/2;
        radii={a.base.variables.field_18,a.base.variables.field_18};
        if(kind==25) {radii[0]-=height;radii[1]+=height;height=0;}
    } else for(unsigned j=0;j<2;++j)radii[j]=scale_radius(radii[j],j);
    float step=arc/float(count-1),uv=0,uv_step=float(a.base.variables.field_04)/float(count-1);
    unsigned pairs=closed?unsigned(count-1):unsigned(count);
    for(unsigned i=0;i<pairs;++i) {
        for(unsigned j=0;j<2;++j) {
            auto& v=e[2*i+j];Point q=xy(angle,radii[j]);
            v.p=strip?Point{q[0],j?-height:height,q[1]}:sum(q,center);
            v.rhw=1;v.color=closed&&!j?a.base.color_490:color;
            v.u=a.base.vectors_378[j].x+a.base.field_78;v.v=uv+a.base.field_7c;
        }
        uv+=uv_step;angle=normalized(angle+step);
    }
    if(closed) for(unsigned j=0;j<2;++j) {e[2*pairs+j]=e[j];e[2*pairs+j].v=uv+a.base.field_7c;}
}
template<class T> void geometry_case(Animation& a,unsigned& cases) {
    std::array<T,36> vertices;for(auto& v:vertices)fill(v);
    std::array<Expected,34> expected;expected.fill(initial());geometry_model(a,expected);
    a.geometry=&vertices[1];Image before=image(a);std::uint32_t flags=a.base.flags.word_04&~0x200000u;
    std::memcpy(before.data()+offsetof(Animation,base)+offsetof(AnimationBase,flags)+offsetof(AnimationFlags,word_04),&flags,sizeof(flags));
    a.update_geometry();assert(image(a)==before);
    check(vertices.front(),initial());check(vertices.back(),initial());
    for(unsigned i=0;i<34;++i)check(vertices[i+1],expected[i]);
    a.geometry=nullptr;++cases; // Borrowed typed storage must not enter owned free.
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    window_state.scale=1.75f;window_state.field_0058=101;window_state.field_005c=-103;window_state.field_0060=-107;window_state.field_0064=109;
    std::array<unsigned char,sizeof(WindowState)> window_before;std::memcpy(window_before.data(),&window_state,window_before.size());
    unsigned cases=0;
    for(unsigned seed=0;seed<6;++seed)for(unsigned depth=0;depth<4;++depth)for(unsigned screen=0;screen<6;++screen)for(unsigned layer=0;layer<4;++layer)for(unsigned flags=0;flags<8;++flags)for(unsigned alias=0;alias<6;++alias) {
        std::array<Animation,4> nodes;for(unsigned i=0;i<4;++i) {configure(nodes[i],seed+i);nodes[i].base.flags.field_0c=(screen+i)%6;nodes[i].base.flags.layer_mode=(layer+i)%4;nodes[i].base.flags.word_04|=(flags&1?1u<<12:0)|(flags&2?1u<<5:0)|(flags&4?1u<<22:0);if(i<depth)nodes[i].parent_558=&nodes[i+1];}
        auto& a=nodes[0];Vector3 local{-0.0f,0.375f,-0.625f};Vector3* destinations[]={&local,&a.vector_5bc,&a.base.vector_2c,&a.base.vector_484,&a.base.vector_38,&a.base.vector_44};Vector3& out=*destinations[alias];
        std::array<Image,4> before;for(unsigned i=0;i<4;++i)before[i]=image(nodes[i]);
        Point expected=position_model(a);assert(&a.position(out)==&out);equal(read(out),expected);
        if(alias) {Vector3 v{expected[0],expected[1],expected[2]};std::memcpy(before[0].data()+(reinterpret_cast<unsigned char*>(&out)-reinterpret_cast<unsigned char*>(&a)),&v,sizeof(v));}
        for(unsigned i=0;i<4;++i) {assert(image(nodes[i])==before[i]);}
        ++cases;
        before[0]=image(a);expected=framed(a,read(out));assert(&a.transform_position(out)==&out);equal(read(out),expected);
        if(alias) {Vector3 v{expected[0],expected[1],expected[2]};std::memcpy(before[0].data()+(reinterpret_cast<unsigned char*>(&out)-reinterpret_cast<unsigned char*>(&a)),&v,sizeof(v));}
        for(unsigned i=0;i<4;++i) {assert(image(nodes[i])==before[i]);}
        ++cases;
        assert(same(a.rotation_z_value(),a.base.vector_38.z));assert(same(a.scale_x_value(),a.base.vector_50.x));assert(same(a.scale_y_value(),a.base.vector_50.y));
    }
    const std::array<unsigned,7> kinds={9,13,14,24,25,47,48};
    for(unsigned kind:kinds)for(int count:{2,3,7,16})for(unsigned screen=0;screen<6;++screen)for(unsigned layer=0;layer<4;++layer)for(unsigned bits=0;bits<8;++bits)for(unsigned topology=0;topology<3;++topology)for(unsigned color:{0u,7u}) {
        Animation a,parent,radius_parent;configure(a,1);configure(parent,3);configure(radius_parent,5);
        parent.base.flags.layer_mode=2;parent.base.flags.field_0c=3;
        a.base.flags.bytes_00.field_00=kind;a.base.variables.field_00=count;a.base.flags.field_0c=screen;a.base.flags.layer_mode=layer;a.base.flags.color_mode=color;
        a.base.flags.word_04|=(bits&1?1u<<12:0)|(bits&2?1u<<5:0)|(bits&4?1u<<22:0);
        if(topology) a.parent_558=&parent;
        if(topology==1)a.parent_55c=&parent;else if(topology==2)a.parent_55c=&radius_parent;
        Image parent_before=image(parent),radius_before=image(radius_parent);
        if(kind==9||kind==13||kind==14)geometry_case<SpriteTexturedVertex>(a,cases);else geometry_case<SpriteWorldTexturedVertex>(a,cases);
        assert(image(parent)==parent_before && image(radius_parent)==radius_before);
    }
    for(unsigned kind=0;kind<256;++kind) {
        if(kind==9||kind==13||kind==14||kind==24||kind==25||kind==47||kind==48)continue;
        Animation a;configure(a,2);a.base.flags.bytes_00.field_00=kind;a.geometry=nullptr;auto before=image(a);a.update_geometry();assert(image(a)==before);++cases;
    }
    // Value helpers retain signed zero/infinity and portable NaN classification.
    for(float f:{0.0f,-0.0f,1.0f,-1.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()}) {
        Animation a;a.base.vector_38.z=f;a.base.vector_50={f,f};window_state.scale=f;
        assert(same(a.rotation_z_value(),f)&&same(a.scale_x_value(),f)&&same(a.scale_y_value(),f)&&same(window_state.scale_value(),f));++cases;
    }
    window_state.scale=1.75f;assert(window_state.field_0058_value()==101&&window_state.field_005c_value()==-103&&window_state.field_0060_value()==-107&&window_state.field_0064_value()==109);
    assert(std::memcmp(window_before.data(),&window_state,window_before.size())==0);
    std::cout<<"PASS "<<cases<<" geometry/position/value state cases\n";
}
