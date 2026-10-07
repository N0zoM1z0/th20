#include "Easing.hpp"
#include "ScalarMath.hpp"
namespace th20 {
namespace {
constexpr float pi = 3.1415927410125732f;
constexpr float back_a = 0.25f, back_b = 0.30f, back_c = 0.35f,
                back_d = 0.38f, back_e = 0.40f;
}
// Normalize the shifted square against its values at zero and one. Repeated
// endpoint terms retain float evaluation rather than algebraically cancelling.
#define TH20_NORMALIZED_BACK(t, a) \
    (((t-a)*(t-a)/((1.0f-a)*(1.0f-a)) - \
      a*a/((1.0f-a)*(1.0f-a))) / \
     (1.0f-a*a/((1.0f-a)*(1.0f-a))))
float easing(std::int32_t mode, float elapsed, float duration) {
    if (duration == 0.0f) return 1.0f;
    float t = elapsed / duration;
    switch (mode) {
    case 1: return t*t;
    case 4: return 1.0f-(1.0f-t)*(1.0f-t);
    case 2: return t*t*t;
    case 5: return 1.0f-(1.0f-t)*(1.0f-t)*(1.0f-t);
    case 3: return t*t*t*t;
    case 6: return 1.0f-(1.0f-t)*(1.0f-t)*(1.0f-t)*(1.0f-t);
    case 9:
        t *= 2.0f;
        return t < 1.0f ? t*t/2.0f : (2.0f-(2.0f-t)*(2.0f-t))/2.0f;
    case 12:
        t *= 2.0f;
        return t < 1.0f ? 0.5f-(1.0f-t)*(1.0f-t)/2.0f
                        : (t-1.0f)*(t-1.0f)/2.0f+0.5f;
    case 10:
        t *= 2.0f;
        return t < 1.0f ? t*t*t/2.0f : (2.0f-(2.0f-t)*(2.0f-t)*(2.0f-t))/2.0f;
    case 13:
        t *= 2.0f;
        return t < 1.0f ? 0.5f-(1.0f-t)*(1.0f-t)*(1.0f-t)/2.0f
                        : (t-1.0f)*(t-1.0f)*(t-1.0f)/2.0f+0.5f;
    case 11:
        t *= 2.0f;
        return t < 1.0f ? t*t*t*t/2.0f : (2.0f-(2.0f-t)*(2.0f-t)*(2.0f-t)*(2.0f-t))/2.0f;
    case 14:
        t *= 2.0f;
        return t < 1.0f ? 0.5f-(1.0f-t)*(1.0f-t)*(1.0f-t)*(1.0f-t)/2.0f
                        : (t-1.0f)*(t-1.0f)*(t-1.0f)*(t-1.0f)/2.0f+0.5f;
    case 15: return 0.0f;
    case 16: return 1.0f;
    case 18: return scalar_math::sine(t*pi/2.0f);
    case 19: return 1.0f-scalar_math::sine(t*pi/2.0f+pi/2.0f);
    case 20:
        t *= 2.0f;
        return t < 1.0f ? scalar_math::sine(t*pi/2.0f)/2.0f
                        : (1.0f-scalar_math::sine(t*pi/2.0f))/2.0f+0.5f;
    case 21:
        t *= 2.0f;
        return t < 1.0f ? (1.0f-scalar_math::sine(t*pi/2.0f+pi/2.0f))/2.0f
                        : scalar_math::sine((t-1.0f)*pi/2.0f)/2.0f+0.5f;
    case 22: t = TH20_NORMALIZED_BACK(t, back_a); return t;
    case 23: t = TH20_NORMALIZED_BACK(t, back_b); return t;
    case 24: t = TH20_NORMALIZED_BACK(t, back_c); return t;
    case 25: t = TH20_NORMALIZED_BACK(t, back_d); return t;
    case 26: t = TH20_NORMALIZED_BACK(t, back_e); return t;
    case 27: t = 1.0f-t; t = 1.0f-TH20_NORMALIZED_BACK(t, back_a); return t;
    case 28: t = 1.0f-t; t = 1.0f-TH20_NORMALIZED_BACK(t, back_b); return t;
    case 29: t = 1.0f-t; t = 1.0f-TH20_NORMALIZED_BACK(t, back_c); return t;
    case 30: t = 1.0f-t; t = 1.0f-TH20_NORMALIZED_BACK(t, back_d); return t;
    case 31: t = 1.0f-t; t = 1.0f-TH20_NORMALIZED_BACK(t, back_e); return t;
    case 0:
    case 7:
    case 8:
    case 17:
    default: return t;
    }
}
#undef TH20_NORMALIZED_BACK
}
