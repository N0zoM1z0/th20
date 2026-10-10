#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>
namespace {
using Image=std::array<unsigned char,sizeof(th20::Animation)>;
Image image(const th20::Animation& a) {Image r;std::memcpy(r.data(),&a,r.size());return r;}
Image vm_expected;
th20::Animation* vm_receiver;
unsigned vm_calls;
std::int32_t vm_return;
}
namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_(){}
const Matrix4 identity_matrix=[] {Matrix4 r;for(int i=0;i<4;++i)r.elements[i][i]=1.0f;return r;}();
// Borrowed-only File fixture; original loading and retirement remain undefined.
AnimationFile::~AnimationFile() {assert(!bytes&&!sprites&&!scripts&&!textures&&!templates);}
// Capture the actual unresolved interpreter ABI and its complete entry state.
std::int32_t Animation::update() {
    assert(this==vm_receiver && image(*this)==vm_expected);
    ++vm_calls;
    base.field_438=0x11223344;
    field_574^=0xa5a5u;
    return vm_return;
}
}
namespace {
using namespace th20;
template<class T> void replace(Image& e,std::size_t offset,const T& v) {std::memcpy(e.data()+offset,&v,sizeof(v));}
float angle_model(float v) {
    constexpr float p=3.1415927410125732f;
    if(v>p) for(unsigned i=0;i<34 && v>p;++i)v-=2.0f*p;
    else if(v<-p) for(unsigned i=0;i<34 && v<-p;++i)v+=2.0f*p;
    return v;
}
float sum(float a,float b) {return a+b;}
float product(float a,float b) {return a*b;}
bool same(float a,float b) {return std::isnan(a)?std::isnan(b):std::bit_cast<std::uint32_t>(a)==std::bit_cast<std::uint32_t>(b);}
void check_float(Image& e,std::size_t offset,float expected,float actual) {
    assert(same(expected,actual));
    // Portable NaN payload choice is not the native byte-exact compiler oracle.
    replace(e,offset,std::isnan(expected)?actual:expected);
}
Timer assigned_zero(Timer t) {t.previous=-1;t.current=0;t.current_fraction=0;if(!(t.flags&1u))t.flags=(t.flags&~6u)|1u;return t;}
float linear(float s,float e,float f) {return sum(product(e-s,f),s);}
std::int32_t wrapped_add(std::int32_t a,std::int32_t b) {return static_cast<std::int32_t>(static_cast<std::uint32_t>(a)+static_cast<std::uint32_t>(b));}
IntegerTriple triple(std::int32_t first,std::int32_t second,std::int32_t third) {return IntegerTriple(third,second,first);}
float plus(float a,float b) {return sum(a,b);}
std::int32_t plus(std::int32_t a,std::int32_t b) {return wrapped_add(a,b);}
Vector2 plus(Vector2 a,Vector2 b) {return {sum(a.x,b.x),sum(a.y,b.y)};}
Vector3 plus(Vector3 a,Vector3 b) {return {sum(a.x,b.x),sum(a.y,b.y),sum(a.z,b.z)};}
IntegerTriple plus(IntegerTriple a,IntegerTriple b) {return triple(wrapped_add(a.first,b.first),wrapped_add(a.second,b.second),wrapped_add(a.third,b.third));}
Angle plus(Angle a,Angle b) {Angle r;r.value=angle_model(sum(a.value,b.value));return r;}
float lerp(float a,float b,float f) {return linear(a,b,f);}
std::int32_t lerp(std::int32_t a,std::int32_t b,float f) {return static_cast<std::int32_t>(linear(static_cast<float>(a),static_cast<float>(b),f));}
Vector2 lerp(Vector2 a,Vector2 b,float f) {return {linear(a.x,b.x,f),linear(a.y,b.y,f)};}
Vector3 lerp(Vector3 a,Vector3 b,float f) {return {linear(a.x,b.x,f),linear(a.y,b.y,f),linear(a.z,b.z,f)};}
IntegerTriple lerp(IntegerTriple a,IntegerTriple b,float f) {
    return triple(wrapped_add(a.first,static_cast<std::int32_t>(product(static_cast<float>(b.first-a.first),f))),
                  wrapped_add(a.second,static_cast<std::int32_t>(product(static_cast<float>(b.second-a.second),f))),
                  wrapped_add(a.third,static_cast<std::int32_t>(product(static_cast<float>(b.third-a.third),f))));
}
Angle lerp(Angle a,Angle b,float f) {Angle r;r.value=angle_model(linear(a.value,b.value,f));return r;}
template<class T> void configure(Interpolation<T>& i,bool active,int duration,int mode,T a,T b,T c,T old) {
    i.start=a;i.end=b;i.tangent_start=old;i.tangent_end=c;i.current=old;
    i.timer.previous=-19;i.timer.current=0;i.timer.current_fraction=0;i.timer.flags=1;
    i.duration=active?duration:0;i.mode=mode;
}
// Table-contract oracle for the tested linear/velocity/acceleration modes.
// It uses independent component arithmetic and explicit timer expectations.
template<class T> T expected_sample(Interpolation<T>& e,float clock) {
    bool terminal=false;
    if(e.duration>0) {
        e.timer.previous=0;e.timer.current_fraction=clock;
        e.timer.current=static_cast<std::int32_t>(clock);
        terminal=e.timer.current>=e.duration;
    }
    if(terminal) {
        int d=e.duration;e.timer.previous=d-1;e.timer.current=d;e.timer.current_fraction=static_cast<float>(d);e.duration=0;
        return e.mode==7||e.mode==17?e.start:e.end;
    }
    if(e.mode==7) {e.start=plus(e.start,e.end);e.current=e.start;}
    else if(e.mode==17) {e.start=plus(e.start,e.tangent_end);e.tangent_end=plus(e.tangent_end,e.end);e.current=e.start;}
    else e.current=lerp(e.start,e.end,e.timer.current_fraction/static_cast<float>(e.duration));
    return e.current;
}
constexpr std::size_t base_at=offsetof(Animation,base);
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    unsigned cases=0;
    const float nan=std::numeric_limits<float>::quiet_NaN(),inf=std::numeric_limits<float>::infinity();
    const std::array<float,10> clocks={0.0f,-0.0f,0.5f,1.0f,2.0f,-0.25f,100.0f,nan,inf,-inf};
    const std::array<float,12> positions={0,-0.0f,0.2f,-0.2f,2,-2,17,-17,1000,nan,inf,-inf};
    for(unsigned seed=0;seed<12;++seed) for(unsigned mask=0;mask<128;++mask) for(float clock:clocks) {
        Animation a;
        default_timer_clock.value=clock;
        a.base.flags.word_04=0xa5a55a50u;
        std::array<float,7> v;
        for(unsigned i=0;i<7;++i)v[i]=(mask&(1u<<i))?positions[(seed+i+2)%12]:-0.0f;
        a.base.vector_44={v[0],v[1],v[2]};a.base.vector_60={v[4],v[3]};a.base.field_3a0=v[5];a.base.field_3a4=v[6];
        a.base.vector_38={positions[seed],positions[(seed+1)%12],positions[(seed+2)%12]};
        a.base.vector_50={positions[(seed+3)%12],positions[(seed+4)%12]};a.base.field_78=positions[(seed+5)%12];a.base.field_7c=positions[(seed+6)%12];
        Image e=image(a);
        std::array<float,7> expected={a.base.vector_38.x,a.base.vector_38.y,a.base.vector_38.z,a.base.vector_50.y,a.base.vector_50.x,a.base.field_78,a.base.field_7c};
        std::uint32_t flags=a.base.flags.word_04;
        for(unsigned i=0;i<7;++i) if(v[i]!=0.0f) {
            float grown=sum(expected[i],product(v[i],clock));
            expected[i]=i<3?angle_model(grown):i<5?grown:(grown>=2?grown-2:grown<0?grown+2:grown);
            if(i<3)flags|=2;else if(i<5)flags|=4;
        }
        a.update_motion();
        const std::array<std::size_t,7> offsets={offsetof(AnimationBase,vector_38),offsetof(AnimationBase,vector_38)+4,offsetof(AnimationBase,vector_38)+8,offsetof(AnimationBase,vector_50)+4,offsetof(AnimationBase,vector_50),offsetof(AnimationBase,field_78),offsetof(AnimationBase,field_7c)};
        const std::array<float,7> actual={a.base.vector_38.x,a.base.vector_38.y,a.base.vector_38.z,a.base.vector_50.y,a.base.vector_50.x,a.base.field_78,a.base.field_7c};
        for(unsigned i=0;i<7;++i)check_float(e,base_at+offsets[i],expected[i],actual[i]);
        replace(e,base_at+offsetof(AnimationBase,flags)+offsetof(AnimationFlags,word_04),flags);
        assert(image(a)==e);assert(same(default_timer_clock.value,clock));++cases;
    }
    const std::array<int,8> modes={0,0,0,7,7,17,17,17};
    const std::array<int,8> durations={3,1,-3,3,1,3,1,-3};
    for(unsigned variant=0;variant<8;++variant) for(unsigned mask=0;mask<4096;++mask) {
        Animation a;
        float clock=(variant==0||variant==3||variant==5)?0.5f:1.0f;
        default_timer_clock.value=clock;
        int d=durations[variant],m=modes[variant];
        a.base.flags.word_04=0x80001000u|((variant&1u)?64u:0u);
        a.base.color_490=0xabcdef01u;a.base.color_494=0x98765432u;
        configure(a.base.interpolation_8c,mask&1,d,m,Vector3{1,2,3},Vector3{4,6,8},Vector3{3,2,1},Vector3{-1,-2,-3});
        configure(a.base.interpolation_e0,mask&2,d,m,triple(7,260,-20),triple(4,-5,300),triple(3,2,1),triple(9,10,11));
        configure(a.base.interpolation_134,mask&4,d,m,std::int32_t(260),std::int32_t(-15),std::int32_t(3),std::int32_t(91));
        configure(a.base.interpolation_1e0,mask&8,d,m,Vector2{1,2},Vector2{4,6},Vector2{3,2},Vector2{-1,-2});
        configure(a.base.interpolation_220,mask&16,d,m,Vector2{2,3},Vector2{5,7},Vector2{2,1},Vector2{-2,-3});
        configure(a.base.interpolation_260,mask&32,d,m,Vector2{3,4},Vector2{6,8},Vector2{1,2},Vector2{-3,-4});
        configure(a.base.interpolation_160,mask&64,d,m,Vector3{0.1f,0.2f,0.3f},Vector3{0.3f,0.2f,0.1f},Vector3{0.1f,0.1f,0.1f},Vector3{-0.2f,-0.1f,0});
        configure(a.base.interpolation_1b4,mask&128,d,m,Angle(0.2f),Angle(-0.1f),Angle(0.3f),Angle(0.7f));
        configure(a.base.interpolation_2a0,mask&256,d,m,triple(270,-20,17),triple(-10,300,-3),triple(1,2,3),triple(33,34,35));
        configure(a.base.interpolation_2f4,mask&512,d,m,std::int32_t(-15),std::int32_t(260),std::int32_t(3),std::int32_t(92));
        configure(a.base.interpolation_320,mask&1024,d,m,2.0f,4.0f,3.0f,-7.0f);
        configure(a.base.interpolation_34c,mask&2048,d,m,3.0f,5.0f,2.0f,-8.0f);
        AnimationBase e=a.base;
        // Route each independent sampled contract to its actual destination.
        if(mask&1) {auto value=expected_sample(e.interpolation_8c,clock);if(e.flags.word_04&64u)e.vector_484=value;else e.vector_2c=value;}
        if(mask&2) {expected_sample(e.interpolation_e0,clock);auto v=e.interpolation_e0.current;e.channels_490.red=static_cast<std::uint8_t>(v.third);e.channels_490.green=static_cast<std::uint8_t>(v.second);e.channels_490.blue=static_cast<std::uint8_t>(v.first);}
        if(mask&4)e.channels_490.alpha=static_cast<std::uint8_t>(expected_sample(e.interpolation_134,clock));
        if(mask&8) {e.vector_50=expected_sample(e.interpolation_1e0,clock);e.flags.word_04|=4u;}
        if(mask&16) {e.vector_58=expected_sample(e.interpolation_220,clock);e.flags.word_04|=4u;}
        if(mask&32) {e.vector_68=expected_sample(e.interpolation_260,clock);e.flags.word_04|=8u;}
        if(mask&64) {e.vector_38=expected_sample(e.interpolation_160,clock);e.flags.word_04|=2u;}
        if(mask&128) {e.vector_38.z=expected_sample(e.interpolation_1b4,clock).value;e.flags.word_04|=2u;}
        if(mask&256) {expected_sample(e.interpolation_2a0,clock);auto v=e.interpolation_2a0.current;e.channels_494.red=static_cast<std::uint8_t>(v.third);e.channels_494.green=static_cast<std::uint8_t>(v.second);e.channels_494.blue=static_cast<std::uint8_t>(v.first);}
        if(mask&512)e.channels_494.alpha=static_cast<std::uint8_t>(expected_sample(e.interpolation_2f4,clock));
        if(mask&1024)e.field_3a0=expected_sample(e.interpolation_320,clock);
        if(mask&2048)e.field_3a4=expected_sample(e.interpolation_34c,clock);
        Image expected=image(a);replace(expected,base_at,e);
        a.update_interpolations();assert(image(a)==expected);assert(default_timer_clock.value==clock);++cases;
    }
    for(unsigned seed=0;seed<128;++seed) for(unsigned kind=0;kind<6;++kind) {
        std::array<Animation,3> templates;
        Animation a,parent,root,ancestor,child;
        AnimationFile file;file.templates=templates.data();
        unsigned script=seed%3;
        for(unsigned i=0;i<3;++i) {templates[i].base.flags.word_04=0x45a596e1u+seed*0x9e3779b9u+i;templates[i].base.field_438=static_cast<std::int32_t>(i+7);}
        a.parent_558=&root;a.parent_55c=&ancestor;a.field_4e8=0xffffffffu;a.field_574=0x1234u;
        a.geometry=allocator.allocate_bytes(33,"parent binding");a.geometry_bytes=33;
        a.timer_4c8.flags=seed*7u;a.timer_4d8.flags=seed*11u;
        parent.base.flags.word_04=0xa5e3967au+seed*0x9e3779b9u;
        parent.field_4e8=seed*17u+5;root.field_4e8=seed*13u+9;root.parent_558=&ancestor;
        parent.parent_558=(kind==2)?&root:nullptr;
        Animation* supplied=kind==0?nullptr:kind==3?&a:kind==4?&templates[script]:&parent;
        a.child_links[1].insert_after(&child.child_links[0]);
        {
            IntrusiveIterator<Animation> observer(&a.child_links[1]);
            Image expected=image(a);
            replace(expected,base_at,templates[script].base);
            replace(expected,offsetof(Animation,field_570),std::uint32_t(0));replace(expected,offsetof(Animation,field_5dc),AnimationHitCallback(nullptr));replace(expected,offsetof(Animation,field_5e0),AnimationScriptCallback(nullptr));
            replace(expected,offsetof(Animation,timer_4c8),assigned_zero(a.timer_4c8));replace(expected,offsetof(Animation,timer_4d8),assigned_zero(a.timer_4d8));
            Animation* chosen=supplied;
            if(supplied) {
                std::uint32_t parent_word=supplied==&a?templates[script].base.flags.word_04:supplied->base.flags.word_04;
                std::uint32_t word=(templates[script].base.flags.word_04&~0x01000000u)|(parent_word&0x01000000u);
                replace(expected,base_at+offsetof(AnimationBase,flags)+offsetof(AnimationFlags,word_04),word);
                if(supplied->parent_558)chosen=supplied->parent_558;
                replace(expected,offsetof(Animation,field_4e8),chosen->field_4e8);
            }
            replace(expected,offsetof(Animation,parent_55c),supplied);replace(expected,offsetof(Animation,parent_558),chosen);
            vm_expected=expected;vm_receiver=&a;vm_calls=0;vm_return=static_cast<std::int32_t>(seed%2);
            file.bind_animation(&a,static_cast<std::int32_t>(script),supplied);
            assert(vm_calls==1);
            replace(expected,base_at+offsetof(AnimationBase,field_438),std::int32_t(0x11223344));replace(expected,offsetof(Animation,field_574),std::uint32_t(0x1234u^0xa5a5u));assert(image(a)==expected);++cases;
        }
        child.child_links[0].detach();file.templates=nullptr;
    }
    for(unsigned seed=0;seed<96;++seed) {
        std::array<Animation,8> a;
        for(unsigned i=0;i<8;++i) {a[i].field_560=positions[(seed+i)%12];a[i].parent_558=i<7?&a[i+1]:nullptr;a[i].base.flags.word_04=((seed>>(i%7))&1u)?0x1000u:0;}
        std::array<Image,8> before;for(unsigned i=0;i<8;++i)before[i]=image(a[i]);
        for(unsigned i=0;i<8;++i) {unsigned selected=i;while(selected<7 && !(a[selected].base.flags.word_04&0x1000u))++selected;assert(same(a[i].slowdown(),a[selected].field_560));++cases;}
        for(unsigned i=0;i<8;++i)assert(image(a[i])==before[i]);
    }
    assert(cases==49664);
    std::cout<<"PASS "<<cases<<" real Animation motion/interpolation/parent cases\n";
}
