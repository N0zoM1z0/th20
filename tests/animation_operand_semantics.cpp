#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "GameRandom.hpp"
#include "Graphics.hpp"
#include "DiagnosticAllocator.hpp"
#include "WindowState.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <source_location>
#include <cstdio>
namespace th20 {
LockRegistry process_locks;
GameRandom progress_random{1}, script_random{0};
Graphics::~Graphics() {
    assert(!resource_19c && !resource_1a0 && !resource_1a4 && !surface_animation);
    assert(!direct3d && !device && !snapshot_pixels && !dynamic_buffer && !startup_scene);
}
Graphics process_graphics;
AnimationFile::~AnimationFile() { assert(!bytes && !templates && !sprites && !scripts && !textures); }
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_(){}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
WindowState window_state{};
const Matrix4 identity_matrix=[] {Matrix4 m;for(int i=0;i<4;++i)m.elements[i][i]=1;return m;}();
}
namespace {
using namespace th20;
using Point=std::array<float,3>;
template<class T> using Image=std::array<unsigned char,sizeof(T)>;
template<class T> Image<T> image(const T& object) {Image<T> r;std::memcpy(r.data(),&object,r.size());return r;}
Point point(const Vector3& v) {return {v.x,v.y,v.z};}
void write(Image<Animation>& out,std::size_t offset,Point p) {std::memcpy(out.data()+offset,p.data(),sizeof(p));}
bool same(float a,float b) {return std::isnan(a)?std::isnan(b):std::bit_cast<unsigned>(a)==std::bit_cast<unsigned>(b);}
void equal(float a,float b,std::source_location where=std::source_location::current()) {
    if(!same(a,b))std::fprintf(stderr,"operand mismatch at %u: %.9g %.9g\n",where.line(),a,b);
    assert(same(a,b));
}
void equal(Point a,Point b) {for(unsigned i=0;i<3;++i)equal(a[i],b[i]);}
float wrap(float x) {
    constexpr float p=3.1415927410125732f;
    if(x>p) {for(unsigned i=0;i<34 && x>p;++i)x-=2*p;}
    else if(x<-p) {for(unsigned i=0;i<34 && x<-p;++i)x=2*p+x;}
    return x;
}
void configure(Animation& a,unsigned seed) {
    auto& v=a.base.variables;
    v.field_00=-2147483647;v.field_04=16777217;v.field_08=-73;v.field_0c=97;
    v.field_10=-27.75f;v.field_14=0.5f;v.field_18=128.125f;v.field_1c=-0.0f;
    v.field_20=-91.875f;v.field_24=199.25f;v.field_28=13.5f;
    v.field_2c=-139;v.field_30=251;v.field_34=-17.75f;v.field_38=11.125f;v.field_3c=65536;
    float s=float(seed)+0.125f;
    a.base.vector_2c={s,-2*s,3*s};a.base.vector_38={9*s,-11*s,0.375f*s};
    a.base.vector_50={-1.5f*s,2.25f*s};a.vector_5d0={-987.0f,654.0f,-321.0f};
    a.base.flags.word_04=0x80000400u;
}
std::int32_t* integer_register(Animation& a,int code) {
    auto& v=a.base.variables;
    const std::array<int,7> ids{10000,10001,10002,10003,10008,10009,10029};
    const std::array<std::int32_t*,7> fields{&v.field_00,&v.field_04,&v.field_08,&v.field_0c,&v.field_2c,&v.field_30,&v.field_3c};
    for(unsigned i=0;i<ids.size();++i)if(code==ids[i])return fields[i];
    return nullptr;
}
float* float_register(Animation& a,int code) {
    auto& v=a.base.variables;
    const std::array<int,15> ids{10004,10005,10006,10007,10013,10014,10015,10023,10024,10025,10027,10028,10033,10034,10035};
    const std::array<float*,15> fields{&v.field_10,&v.field_14,&v.field_18,&v.field_1c,&a.base.vector_2c.x,&a.base.vector_2c.y,&a.base.vector_2c.z,&a.base.vector_38.x,&a.base.vector_38.y,&a.base.vector_38.z,&v.field_34,&v.field_38,&v.field_20,&v.field_24,&v.field_28};
    for(unsigned i=0;i<ids.size();++i)if(code==ids[i])return fields[i];
    return nullptr;
}
// Capture every ancestor before wrapping its local angles. Iterate from the
// root to the leaf: the cache contains pre-wrap values at this invocation.
Point rotation_model(Animation& leaf,std::array<Image<Animation>,3>& expected,const std::array<Animation*,3>& owners) {
    std::array<Animation*,3> chain{};unsigned n=0;Animation* a=&leaf;
    while(true) {assert(n<chain.size());chain[n++]=a;if(!a->parent_558 || (a->base.flags.word_04&(1u<<12)))break;a=a->parent_558;}
    Point sum{};
    for(unsigned k=n;k>0;--k) {
        auto* node=chain[k-1];auto local=point(node->base.vector_38);auto cached=local;
        if(k<n)for(unsigned axis=0;axis<3;++axis)cached[axis]+=sum[axis];
        unsigned owner=0;while(owners[owner]!=node){++owner;assert(owner<owners.size());}
        write(expected[owner],offsetof(Animation,vector_5d0),cached);
        if(k<n){for(auto& x:local)x=wrap(x);write(expected[owner],offsetof(Animation,base)+offsetof(AnimationBase,vector_38),local);}
        sum=cached;
    }
    return sum;
}
// Full-width argument predicates and parent-first composition. Each child
// decides the flags used for its parent; the caller decides its own flags.
Point direction_model(const Animation& leaf,Point value,int rotate,int scale) {
    struct Frame {const Animation* owner;int rotate,scale;};std::array<Frame,3> chain{};unsigned n=0;auto* a=&leaf;
    while(true) {
        assert(n<chain.size());chain[n++]={a,rotate,scale};
        if(!a->parent_558 || (a->base.flags.word_04&(1u<<12)))break;
        rotate=(a->base.flags.word_04>>5)&1u;scale=(a->base.flags.word_04>>22)&1u;a=a->parent_558;
    }
    while(n){const auto f=chain[--n];if(f.rotate){float sn=float(std::sin(double(f.owner->base.vector_38.z))),cs=float(std::cos(double(f.owner->base.vector_38.z)));float x=value[0]*cs-value[1]*sn;value[1]=value[1]*cs+value[0]*sn;value[0]=x;}if(f.scale){value[0]*=f.owner->base.vector_50.x;value[1]*=f.owner->base.vector_50.y;}}
    return value;
}
struct RandomModel {
    std::uint32_t state,modulus,last;
    std::uint32_t sample(){state=std::uint32_t((std::uint64_t(state)*48271u)%2147483647u);last=state;return state%modulus;}
    float range(float limit,bool signed_value){float value=float(sample());float denominator=signed_value?float(modulus)/2.0f-1.0f:float(modulus)-1.0f;value/=denominator;if(signed_value)value-=1.0f;return value*limit;}
    void verify(const GameRandom& actual,const GameRandom& original) const {
        GameRandom expected=original;expected.engine.seed(state);expected.last=last;assert(image(actual)==image(expected));
    }
};
float float_model(Animation& a,float input,RandomModel& r,std::array<Image<Animation>,3>& expected,const std::array<Animation*,3>& owners) {
    int code=int(input);auto& v=a.base.variables;
    if(auto* p=integer_register(a,code))return float(*p);
    if(auto* p=float_register(a,code))return *p;
    if(code==10026)return rotation_model(a,expected,owners)[2];
    if(code>=10016 && code<=10018){auto& p=process_graphics.viewports[3];return point(p.vector_00)[code-10016]+point(p.vector_3c)[code-10016];}
    if(code>=10019 && code<=10021)return point(process_graphics.viewports[3].vector_24)[code-10019];
    if(code==10022)return float(r.sample());
    if(code==10011 || code==10031)return r.range(v.field_34,false);
    if(code==10012 || code==10032)return r.range(v.field_34,true);
    if(code==10010 || code==10030)return r.range(v.field_38,true);
    return input;
}
}
int main() {
    using namespace th20;std::size_t cases=0;
    Animation a,b,c;std::array<Animation*,3> owners{&a,&b,&c};for(unsigned i=0;i<3;++i)configure(*owners[i],i+1);
    for(unsigned i=0;i<6;++i){auto& p=process_graphics.viewports[i];float x=float(i)*31+0.125f;p.vector_00={x,-x,2*x};p.vector_3c={3*x,4*x,-5*x};p.vector_24={-6*x,7*x,8*x};}
    const auto graphics=image(process_graphics);script_random.seed(0x12345678);const auto other=image(script_random);
    // Exhaust all uint16 masks, with each bit tested, including null masked
    // inputs and a mutable alias distinct from the instruction's storage.
    for(unsigned mask=0;mask<65536;++mask) {
        int index=int(mask%16);int selector=10000;float fs=10004.75f;auto before=image(a);bool set=(mask&(1u<<index))!=0;
        auto* ip=a.integer_argument(set?&selector:nullptr,std::uint16_t(mask),index);auto* fp=a.float_argument(set?&fs:nullptr,std::uint16_t(mask),index);
        assert(ip==(set?&a.base.variables.field_00:nullptr));assert(fp==(set?&a.base.variables.field_10:nullptr));assert(image(a)==before && selector==10000 && fs==10004.75f);++cases;
    }
    for(int code=9990;code<=10045;++code)for(int index=0;index<16;++index)for(bool set:{false,true}) {
        int operand=code;auto before=image(a);auto* field=integer_register(a,code);auto* expected=set&&field?field:&operand;auto* got=a.integer_argument(&operand,std::uint16_t(set?1u<<index:0),index);assert(got==expected && image(a)==before);
        int saved=*got;*got=-573;if(got!=&operand){auto after=before;std::ptrdiff_t offset=reinterpret_cast<unsigned char*>(got)-reinterpret_cast<unsigned char*>(&a);int value=-573;std::memcpy(after.data()+offset,&value,sizeof(value));assert(image(a)==after && operand==code);}else assert(image(a)==before);*got=saved;++cases;
        for(float fraction:{0.0f,0.75f,-0.75f}) {
            float input=float(code)+fraction;auto copy=image(a);auto* reg=float_register(a,int(input));auto* wanted=set&&reg?reg:&input;auto* actual=a.float_argument(&input,std::uint16_t(set?1u<<index:0),index);assert(actual==wanted && image(a)==copy);float saved_float=*actual;*actual=-39.125f;if(actual!=&input){auto after=copy;auto offset=reinterpret_cast<unsigned char*>(actual)-reinterpret_cast<unsigned char*>(&a);float value=-39.125f;std::memcpy(after.data()+offset,&value,sizeof(value));assert(image(a)==after);}else assert(image(a)==copy);*actual=saved_float;++cases;
        }
    }
    // Values include truncation, signed/unsigned conversions, zero-bounded
    // no-draw, unconditional floating draw, both range aliases and full RNG
    // object state. Each float lookup has its own mutable-rotation oracle.
    for(unsigned seed=1;seed<=256;++seed)for(int code=9990;code<=10045;++code) {
        configure(a,1);a.parent_558=nullptr;a.base.variables.field_3c=(seed%4==0)?0:(seed%4==1?-1:65536);progress_random.seed(seed*7919u);GameRandom initial=progress_random;RandomModel model{seed*7919u,progress_random.modulus,progress_random.last};auto before=image(a);
        int expected=code;if(auto* p=integer_register(a,code))expected=*p;else if(code==10022){unsigned bound=unsigned(a.base.variables.field_3c);expected=bound?std::bit_cast<int>(model.sample()%bound):0;}else if((code>=10004&&code<=10007)||(code>=10033&&code<=10035)||code==10027||code==10028)expected=int(*float_register(a,code));
        assert(a.integer_value(code)==expected && image(a)==before);model.verify(progress_random,initial);++cases;
        for(float fraction:{0.0f,0.75f,-0.75f}) {
            float input=float(code)+fraction;std::array<Image<Animation>,3> images{image(a),image(b),image(c)};float wanted=float_model(a,input,model,images,owners);equal(a.float_value(input),wanted);for(unsigned i=0;i<3;++i)assert(image(*owners[i])==images[i]);model.verify(progress_random,initial);++cases;
        }
    }
    // Non-finite register outputs bypass selector conversion; instruction
    // selectors themselves must remain finite and int32-representable.
    for(float value:{std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),-0.0f}){a.base.variables.field_10=value;auto before=image(a);equal(a.float_value(10004.0f),value);assert(image(a)==before);++cases;}
    for(unsigned packed=0;packed<512;++packed) {
        for(unsigned i=0;i<3;++i){configure(*owners[i],i+1);unsigned bits=(packed>>(3*i))&7u;owners[i]->base.flags.word_04|=((bits&1u)?1u<<12:0)|((bits&2u)?1u<<5:0)|((bits&4u)?1u<<22:0);owners[i]->parent_558=i<2?owners[i+1]:nullptr;}
        for(unsigned repeat=0;repeat<3;++repeat){std::array<Image<Animation>,3> expected{image(a),image(b),image(c)};auto wanted=rotation_model(a,expected,owners);if(repeat==1)equal(a.float_value(10026.75f),wanted[2]);else{auto& ref=a.rotation_sum();assert(&ref==&a.vector_5d0);equal(point(ref),wanted);}for(unsigned i=0;i<3;++i)assert(image(*owners[i])==expected[i]);++cases;}
        for(int rotate:{0,1,-1,256,-256})for(int scale:{0,1,-1,256,-256})for(bool alias:{false,true}) {
            a.base.vector_2c={1.125f,-2.25f,3.375f};Vector3 value{2.75f,-3.125f,-0.0f};auto* output=alias?&a.base.vector_2c:&value;auto input=point(*output);auto wanted=direction_model(a,input,rotate,scale);std::array<Image<Animation>,3> expected{image(a),image(b),image(c)};if(alias)write(expected[0],offsetof(Animation,base)+offsetof(AnimationBase,vector_2c),wanted);auto& returned=a.transform_direction(*output,rotate,scale);assert(&returned==output);equal(point(*output),wanted);for(unsigned i=0;i<3;++i)assert(image(*owners[i])==expected[i]);++cases;
        }
    }
    // Signed and endpoint literals outside the register interval, including
    // negative zero, are preserved without advancing either random stream.
    for(int value:{(-2147483647-1),2147483647,-2,-1,0,1,65535}){auto before=image(a);auto random=image(progress_random);assert(a.integer_value(value)==value && image(a)==before && image(progress_random)==random);int storage=value;assert(a.integer_argument(&storage,65535,0)==&storage);++cases;}
    for(float value:{-2147483648.0f,2147483520.0f,-3.75f,-0.0f,0.0f,1.0f,65535.0f}){auto before=image(a);auto random=image(progress_random);equal(a.float_value(value),value);assert(image(a)==before && image(progress_random)==random);float storage=value;assert(a.float_argument(&storage,65535,0)==&storage);++cases;}
    // File lookup borrows pointers without interpreting packet storage. An
    // interior table origin makes negative indices valid within this fixture.
    AnimationFile file;std::array<AnmInstruction*,9> table{};for(unsigned i=0;i<3;++i)table[i]=reinterpret_cast<AnmInstruction*>(owners[i]);file.scripts=table.data()+4;
    for(int index=-4;index<5;++index){auto before=image(file);assert(file.script(index)==table[unsigned(index+4)] && image(file)==before);++cases;}file.scripts=nullptr;
    for(unsigned seed=1;seed<=128;++seed)for(float limit:{0.0f,-0.0f,1.0f,-1.0f,123.75f}){progress_random.seed(seed);GameRandom initial=progress_random;RandomModel model{seed,progress_random.modulus,progress_random.last};equal(progress_random.range(limit),model.range(limit,false));model.verify(progress_random,initial);++cases;}
    assert(image(process_graphics)==graphics && image(script_random)==other);
    for(auto* owner:owners)owner->parent_558=nullptr;
    std::cout<<"PASS "<<cases<<" actual-owner operand/random/recursive-frame cases\n";
}
