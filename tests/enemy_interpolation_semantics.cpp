#include "EnemyMovement.hpp"
#include "ClockScalar.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <limits>

namespace {
using th20::EnemyMotionInterpolation;
using th20::Vector3;

bool near(float a, float b) {
    return std::fabs(double(a)-b) <= 0.00002 * (1 + std::fabs(double(b)));
}
void same(const Vector3& a, const Vector3& b) {
    assert(near(a.x,b.x) && near(a.y,b.y) && near(a.z,b.z));
}
EnemyMotionInterpolation fixture(int mode, int duration) {
    EnemyMotionInterpolation state;
    state.current=Vector3(91,92,93);
    state.start=Vector3(2,-4,7);state.end=Vector3(10,12,-1);
    state.tangent_start=Vector3(3,-2,4);state.tangent_end=Vector3(5,6,-3);
    state.mode=mode;state.duration=duration;
    state.axis_modes={{7,17,8}};state.flags.bits=0xd5000000u;
    state.timer.flags=0xa5000001u;
    return state;
}
// A second already-verified protocol is a metamorphic oracle for shared mode.
// Separate closed-form cases below establish the concrete coordinate results.
th20::VectorInterpolation generic(const EnemyMotionInterpolation& state) {
    th20::VectorInterpolation out;
    out.current=state.current;out.start=state.start;out.end=state.end;
    out.tangent_start=state.tangent_start;out.tangent_end=state.tangent_end;
    out.timer=state.timer;out.mode=state.mode;out.duration=state.duration;
    return out;
}
th20::FloatInterpolation scalar(const EnemyMotionInterpolation& state, int axis) {
    const float current[]={state.current.x,state.current.y,state.current.z};
    const float start[]={state.start.x,state.start.y,state.start.z};
    const float end[]={state.end.x,state.end.y,state.end.z};
    const float first[]={state.tangent_start.x,state.tangent_start.y,state.tangent_start.z};
    const float last[]={state.tangent_end.x,state.tangent_end.y,state.tangent_end.z};
    th20::FloatInterpolation out;
    out.current=current[axis];out.start=start[axis];out.end=end[axis];
    out.tangent_start=first[axis];out.tangent_end=last[axis];
    out.timer=state.timer;out.mode=state.axis_modes.values[axis];out.duration=state.duration;
    return out;
}
}

void check_enemy_interpolation() {
    const auto old_clock=th20::default_timer_clock.value;
    auto* old_source=th20::timer_clock_sources[0];
    th20::timer_clock_sources[0]=&th20::default_timer_clock;

    Vector3 indexed;
    assert(&indexed[0]==&indexed.x && &indexed[1]==&indexed.y && &indexed[2]==&indexed.z);
    const std::array<std::uint32_t,3> raw{0x80000000u,0x7fc12345u,0x3f800000u};
    for (int axis=0;axis!=3;++axis) indexed[axis]=std::bit_cast<float>(raw[axis]);
    assert(std::bit_cast<std::uint32_t>(indexed.x)==raw[0]);
    assert(std::bit_cast<std::uint32_t>(indexed.y)==raw[1]);
    assert(std::bit_cast<std::uint32_t>(indexed.z)==raw[2]);

    for (int value : {0,-1,1,1234567,std::numeric_limits<int>::min(),std::numeric_limits<int>::max()}) {
        auto state=fixture(0,value);
        auto vector=generic(state);auto floating=scalar(state,0);
        th20::Vector2Interpolation planar;planar.duration=value;
        const auto before=state;
        assert(state.duration_value()==value && vector.duration_value()==value);
        assert(floating.duration_value()==value && planar.duration_value()==value);
        assert(std::memcmp(&before,&state,sizeof state)==0);
        state.stop();assert(state.duration==0);
        assert(std::memcmp(&before,&state,offsetof(EnemyMotionInterpolation,duration))==0);
        assert(state.mode==before.mode && state.flags.bits==before.flags.bits);
    }

    for (float clock : {0.0f,0.5f,1.0f,1.25f}) {
        th20::default_timer_clock.value=clock;
        for (int mode=-1;mode<=32;++mode) for (int duration : {0,1,4,-4}) {
            auto state=fixture(mode,duration);auto expected=generic(state);
            same(state.sample(),expected.sample());
            same(state.current,expected.current);same(state.start,expected.start);
            same(state.tangent_end,expected.tangent_end);
            assert(state.duration==expected.duration && state.mode==mode);
            assert(std::memcmp(&state.timer,&expected.timer,sizeof state.timer)==0);
            assert(state.flags.bits==0xd5000000u);
        }
        for (int mode=0;mode!=32;++mode) {
            struct Guarded { unsigned first; EnemyMotionInterpolation state; unsigned last; };
            Guarded guarded{0x12345678u,fixture(0,4),0xabcdef01u};
            auto& state=guarded.state;state.flags.bits|=1;
            state.axis_modes={{mode,(mode+7)%32,(mode+17)%32}};
            auto x=scalar(state,0),y=scalar(state,1),z=scalar(state,2);
            const Vector3 expected(x.sample(),y.sample(),z.sample());
            same(state.sample(),expected);
            same(state.start,Vector3(x.start,y.start,z.start));
            same(state.tangent_end,Vector3(x.tangent_end,y.tangent_end,z.tangent_end));
            assert(guarded.first==0x12345678u && guarded.last==0xabcdef01u);
            assert(state.flags.bits==0xd5000001u && state.duration==4);
            assert(std::memcmp(&state.timer,&x.timer,sizeof state.timer)==0);
        }
    }

    // Terminal selection follows the shared mode even with mixed axis modes.
    th20::default_timer_clock.value=1;
    for (int mode : {0,7,8,17}) for (int duration : {0,1}) {
        auto state=fixture(mode,duration);state.flags.bits|=1;
        const auto before=state;
        same(state.sample(),mode==7 || mode==17 ? before.start : before.end);
        same(state.current,before.current);same(state.start,before.start);
        same(state.tangent_start,before.tangent_start);same(state.tangent_end,before.tangent_end);
        assert(state.duration==0 && state.mode==mode && state.flags.bits==before.flags.bits);
        if (duration==0) assert(std::memcmp(&before,&state,sizeof state)==0);
        else assert(state.timer.current==1 && state.timer.fraction()==1);
    }

    // Independent Hermite weights at t=1/4 are 54,10,9,-3 over 64.
    auto shared=fixture(8,4);
    const Vector3 hermite((2*54+10*10+3*9-5*3)/64.0f,
                         (-4*54+12*10-2*9-6*3)/64.0f,
                         (7*54-1*10+4*9+3*3)/64.0f);
    same(shared.sample(),hermite);
    auto axes=fixture(0,4);axes.flags.bits|=1;
    same(axes.sample(),Vector3(12,2,hermite.z));
    same(axes.start,Vector3(12,2,7));same(axes.tangent_end,Vector3(5,18,-3));

    // A negative duration evaluates the unclamped, negative time ratio without
    // ticking. Linear/quadratic/cubic axes have independent closed-form values.
    axes=fixture(17,-4);axes.flags.bits|=1;axes.axis_modes={{0,1,2}};
    axes.timer.current_fraction=1;
    const auto before=axes;
    same(axes.sample(),Vector3(0,-3,7.125f));
    // z = 7 + (-8)*(-1/64) = 7.125.
    assert(near(axes.current.z,7.125f));
    assert(std::memcmp(&axes.timer,&before.timer,sizeof axes.timer)==0);
    same(axes.start,before.start);same(axes.tangent_end,before.tangent_end);

    // Repeated half-speed frames distinguish per-call accumulation from elapsed
    // time. Acceleration follows n*v0 + n*(n-1)/2*a; clamping must not add once
    // more on the terminal call, and its output leaves current at the prior frame.
    th20::default_timer_clock.value=0.5f;
    auto sequence=fixture(0,5);sequence.flags.bits|=1;sequence.axis_modes={{7,17,0}};
    for (int n=1;n<=9;++n) {
        same(sequence.sample(),Vector3(2+10.0f*n,-4+6.0f*n+6.0f*n*(n-1),7-0.8f*n));
        assert(sequence.timer.fraction()==0.5f*n && sequence.duration==5);
    }
    const auto last_active=sequence;
    same(sequence.sample(),sequence.end);
    same(sequence.current,last_active.current);same(sequence.start,last_active.start);
    same(sequence.tangent_end,last_active.tangent_end);
    assert(sequence.duration==0 && sequence.timer.current==5 && sequence.timer.fraction()==5);
    const auto stopped=sequence;
    same(sequence.sample(),sequence.end);assert(std::memcmp(&sequence,&stopped,sizeof sequence)==0);
    th20::default_timer_clock.value=1;

    // Factors use separate signed mode slots and leave the entire owner intact.
    axes=fixture(4,4);axes.axis_modes={{0,1,16}};axes.timer.current_fraction=1;
    const auto factor_before=axes;
    assert(near(axes.factor(),7.0f/16));
    assert(axes.factor(0)==0.25f && axes.factor(1)==0.0625f && axes.factor(2)==1);
    assert(std::memcmp(&axes,&factor_before,sizeof axes)==0);

    // Sampling one real embedded curve must not touch other movement values.
    th20::EnemyMovement movement;movement.position=fixture(0,4);
    movement.motion.flags.bits=0xfedcba98u;movement.scalar_ac.current=19;
    movement.vector_144.current=th20::Vector2(17,-21);
    std::array<unsigned char,sizeof movement> enclosing_before,enclosing_after;
    std::memcpy(enclosing_before.data(),&movement,sizeof movement);
    movement.position.sample();
    std::memcpy(enclosing_after.data(),&movement,sizeof movement);
    for (std::size_t i=0;i!=sizeof movement;++i)
        if (i<offsetof(th20::EnemyMovement,position) || i>=offsetof(th20::EnemyMovement,scalar_ac))
            assert(enclosing_before[i]==enclosing_after[i]);

    th20::Motion motion;
    const auto motion_before=motion;
    motion.set_motion_vector(indexed);
    assert(std::memcmp(&motion.vector_38,&indexed,sizeof indexed)==0);
    assert(std::memcmp(&motion,&motion_before,offsetof(th20::Motion,vector_38))==0);
    assert(motion.flags.bits==motion_before.flags.bits);
    motion.set_motion_vector(motion.vector_38);
    assert(std::memcmp(&motion.vector_38,&indexed,sizeof indexed)==0);

    th20::default_timer_clock.value=old_clock;th20::timer_clock_sources[0]=old_source;
}
