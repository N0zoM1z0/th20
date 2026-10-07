#include "Interpolation.hpp"
#include "Easing.hpp"
#include "ClockScalar.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <initializer_list>
#include <type_traits>

namespace {
bool close(float actual, double expected) {
    return std::fabs(double(actual)-expected) < 0.0002;
}

// Independent double-precision curves. Back curves use their reduced polynomial,
// rather than the repeated endpoint-normalization expression in production.
double curve(int mode, double t) {
    if (mode >= 1 && mode <= 3) return std::pow(t, mode+1);
    if (mode >= 4 && mode <= 6) return 1-std::pow(1-t, mode-2);
    if (mode >= 9 && mode <= 11) {
        const int power = mode-7;
        return t < 0.5 ? std::pow(2*t,power)/2 : 1-std::pow(2-2*t,power)/2;
    }
    if (mode >= 12 && mode <= 14) {
        const int power = mode-10;
        return t < 0.5 ? (1-std::pow(1-2*t,power))/2
                      : (1+std::pow(2*t-1,power))/2;
    }
    constexpr double pi = 3.1415927410125732;
    if (mode == 15) return 0;
    if (mode == 16) return 1;
    if (mode == 18) return std::sin(t*pi/2);
    if (mode == 19) return 1-std::sin(t*pi/2+pi/2);
    if (mode == 20) return t < 0.5 ? std::sin(t*pi)/2 : 1-std::sin(t*pi)/2;
    if (mode == 21) return t < 0.5 ? (1-std::sin(t*pi+pi/2))/2
                                 : (1+std::sin((t-0.5)*pi))/2;
    if (mode >= 22 && mode <= 31) {
        const double back[] = {0.25f,0.30f,0.35f,0.38f,0.40f};
        const double a = back[(mode-22)%5];
        const double x = mode < 27 ? t : 1-t;
        const double result = (x*x-2*a*x)/(1-2*a);
        return mode < 27 ? result : 1-result;
    }
    return t;
}

template<class T> T value(float input) {
    if constexpr (std::is_same_v<T, th20::Angle>) return th20::Angle(input/80);
    else if constexpr (std::is_same_v<T, th20::Vector2>) return th20::Vector2(input,input+2);
    else if constexpr (std::is_same_v<T, th20::Vector3>) return th20::Vector3(input,input+2,input-3);
    else if constexpr (std::is_same_v<T, th20::IntegerTriple>) {
        return th20::IntegerTriple(int(input*3),int(input*2),int(input));
    } else if constexpr (std::is_same_v<T, th20::FogValue>) {
        return th20::FogValue(input,2*input,input,input+1,2*input,250);
    } else return static_cast<T>(input);
}

template<class T> float component(const T& input) {
    if constexpr (std::is_same_v<T, th20::Angle>) return input.value;
    else if constexpr (std::is_same_v<T, th20::Vector2> || std::is_same_v<T, th20::Vector3>) return input.x;
    else if constexpr (std::is_same_v<T, th20::IntegerTriple>) return float(input.first);
    else if constexpr (std::is_same_v<T, th20::FogValue>) return input.near_distance;
    else return float(input);
}

template<class T> th20::Interpolation<T> fixture(int mode, int duration) {
    th20::Interpolation<T> result;
    result.start=value<T>(20); result.end=value<T>(40);
    result.tangent_start=value<T>(8); result.tangent_end=value<T>(12);
    result.current=value<T>(99);
    result.duration=duration; result.mode=mode;
    result.timer.flags=0xa5000001u;
    return result;
}

template<class T> void family() {
    for (int mode = 0; mode != 32; ++mode) {
        auto stopped=fixture<T>(mode,0);
        unsigned char before[sizeof stopped];std::memcpy(before,&stopped,sizeof stopped);
        const T terminal=stopped.sample();
        assert(std::memcmp(before,&stopped,sizeof stopped)==0);
        assert(component(terminal)==component(mode==7 || mode==17 ? stopped.start : stopped.end));

        struct Guarded { unsigned first; th20::Interpolation<T> state; unsigned last; };
        Guarded guarded{0x12345678u,fixture<T>(mode,4),0xabcdef01u};
        auto& state=guarded.state;
        const T output=state.sample();
        assert(guarded.first==0x12345678u && guarded.last==0xabcdef01u);
        assert(state.mode==mode && state.duration==4);
        assert(state.timer.current==1 && state.timer.fraction()==1 && state.timer.flags==0xa5000001u);
        assert(component(output)==component(state.current));
        double expected;
        if (mode==7) expected=60;
        else if (mode==17) {
            expected=32;
            assert(close(component(state.tangent_end),std::is_same_v<T,th20::Angle> ? 52.0/80 : 52));
        } else if (mode==8) {
            // Hermite basis at one quarter: 54/64,10/64,9/64,-3/64.
            if constexpr (std::is_same_v<T, th20::IntegerTriple>) expected=16+6+1+0;
            else expected=20*54.0/64+40*10.0/64+8*9.0/64-12*3.0/64;
        } else {
            const double factor=curve(mode,0.25);
            if constexpr (std::is_same_v<T,th20::IntegerTriple>) expected=20+std::trunc(20*factor);
            else expected=20+20*factor;
        }
        if constexpr (std::is_integral_v<T>) expected=std::trunc(expected);
        if constexpr (std::is_same_v<T,th20::Angle>) expected/=80;
        assert(close(component(output),expected));
        if constexpr (std::is_same_v<T,th20::FogValue>) {
            assert(close(output.far_distance,expected*2));
            unsigned packed=0;
            for (unsigned i=0;i!=4;++i) packed|=(unsigned(int(output.channels[i]))&255u)<<(i*8);
            assert(output.packed==packed);
        }

        auto last=fixture<T>(mode,1);const T end=last.sample();
        assert(last.duration==0 && last.timer.current==1 && last.timer.fraction()==1);
        assert(component(end)==component(mode==7 || mode==17 ? last.start : last.end));
        assert(component(last.current)==component(value<T>(99)));

        auto indefinite=fixture<T>(mode,-4);const th20::Timer timer=indefinite.timer;
        indefinite.sample();assert(std::memcmp(&timer,&indefinite.timer,sizeof timer)==0);
        indefinite.stop();assert(indefinite.duration==0 && indefinite.mode==mode);
    }
}
}

void check_interpolation_protocol() {
    const float saved_clock=th20::default_timer_clock.value;
    th20::ClockScalar* saved_source=th20::timer_clock_sources[0];
    th20::timer_clock_sources[0]=&th20::default_timer_clock;
    th20::default_timer_clock.value=1;
    for (int mode=-2;mode!=35;++mode) {
        assert(th20::easing(mode,7,0)==1 && th20::easing(mode,7,-0.0f)==1);
        for (int step=-64;step<=128;++step) {
            const float t=step/64.0f;
            assert(close(th20::easing(mode,t,1),curve(mode,t)));
            assert(th20::easing(mode,t*4,4)==th20::easing(mode,t,1));
        }
    }
    family<float>(); family<std::int32_t>(); family<std::uint8_t>();
    family<th20::Vector2>(); family<th20::Vector3>(); family<th20::Angle>();
    family<th20::IntegerTriple>(); family<th20::FogValue>();

    for (float clock : {0.0f,0.5f,1.0f,1.25f}) {
        th20::default_timer_clock.value=clock;
        auto state=fixture<float>(0,4);
        assert(close(state.sample(),20+5*clock));
        assert(state.timer.fraction()==clock && state.timer.current==int(clock));
    }
    for (int mode=0;mode!=32;++mode) {
        auto floating=fixture<float>(mode,4);auto byte=fixture<std::uint8_t>(mode,4);
        floating.timer.current_fraction=1;byte.timer.current_fraction=1;
        const th20::Timer before=floating.timer;
        const float actual=floating.evaluate();const auto narrowed=byte.evaluate();
        assert(std::memcmp(&before,&floating.timer,sizeof before)==0);
        assert(std::memcmp(&before,&byte.timer,sizeof before)==0);
        assert(floating.duration==4 && byte.duration==4);
        assert(narrowed==std::uint8_t(std::int32_t(actual)));
    }
    auto signed_wrap=fixture<std::int32_t>(7,-1);
    signed_wrap.start=std::numeric_limits<std::int32_t>::max();signed_wrap.end=1;
    assert(signed_wrap.sample()==std::numeric_limits<std::int32_t>::min());
    auto byte_wrap=fixture<std::uint8_t>(7,-1);byte_wrap.start=250;byte_wrap.end=10;
    assert(byte_wrap.sample()==4);
    auto truncation=fixture<std::uint8_t>(22,4);
    truncation.start=0;truncation.end=200;truncation.timer.current_fraction=0.5f;
    assert(truncation.evaluate()==std::uint8_t(std::int32_t(200*curve(22,0.125))));

    const th20::IntegerTriple first(11,7,3),second(13,9,5);
    assert(first.first==3 && first.second==7 && first.third==11);
    auto triple=fixture<th20::IntegerTriple>(8,4);
    triple.start=first;triple.end=second;
    triple.tangent_start=th20::IntegerTriple(3,2,1);
    triple.tangent_end=th20::IntegerTriple(5,4,3);
    th20::default_timer_clock.value=1;
    const auto weighted=triple.sample();
    assert(weighted.first==2+0+0+0 && weighted.second==5+1+0+0 && weighted.third==9+2+0+0);
    const th20::IntegerTriple high(0,0,std::numeric_limits<std::int32_t>::max()),one(0,0,1);
    assert((high+one).first==std::numeric_limits<std::int32_t>::min());
    assert((one-high).first==-2147483646);

    auto angle=fixture<th20::Angle>(0,4);
    angle.start=3.1f;angle.end=-3.1f;
    const float result=angle.sample().value;
    const double shortest=std::atan2(std::sin(-6.2f),std::cos(-6.2f));
    assert(close(std::sin(result),std::sin(3.1f+shortest/4)));
    assert(close(std::cos(result),std::cos(3.1f+shortest/4)));
    th20::default_timer_clock.value=saved_clock;th20::timer_clock_sources[0]=saved_source;
}
