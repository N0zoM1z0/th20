#include "Interpolation.hpp"
#include "Easing.hpp"

namespace th20 {

template<class T> Interpolation<T>::Interpolation()
    : start(), end(), tangent_start(), tangent_end(), current(),
      timer(), duration(0), mode(0) {}

template<class T> void Interpolation<T>::set_duration(std::int32_t value) {
    duration = value;
}

template<class T> std::int32_t Interpolation<T>::set_mode(std::int32_t value) {
    return mode = value;
}

template<class T> void Interpolation<T>::set_start(const T& value) {
    start = value;
}

template<class T> void Interpolation<T>::set_end(const T& value) {
    end = value;
}

template<class T> void Interpolation<T>::begin(std::int32_t frames,
    std::int32_t easing_mode, const T& from, const T& to) {
    set_duration(frames);
    set_mode(easing_mode);
    set_start(from);
    set_end(to);
    current = from;
    timer = 0;
}

template<class T> std::int32_t Interpolation<T>::duration_value() const { return duration; }

template<class T> void Interpolation<T>::stop() { duration = 0; }
template<class T> float Interpolation<T>::factor() const {
    return easing(mode, timer.fraction(), static_cast<float>(duration));
}
template<class T> T Interpolation<T>::sample() {
    if (duration > 0) {
        ++timer;
        if (timer.at_least(duration)) {
            timer = duration;
            stop();
            if (mode != 7 && mode != 17) return end;
            else return start;
        }
    } else if (duration == 0) {
        if (mode != 7 && mode != 17) return end;
        else return start;
    }
    if (mode == 7) {
        if constexpr (std::is_integral_v<T>)
            start = static_cast<T>(static_cast<std::uint32_t>(start) + static_cast<std::uint32_t>(end));
        else start = T(start) + end;
        current = start;
    } else if (mode == 17) {
        if constexpr (std::is_integral_v<T>) {
            start = static_cast<T>(static_cast<std::uint32_t>(start) + static_cast<std::uint32_t>(tangent_end));
            tangent_end = static_cast<T>(static_cast<std::uint32_t>(tangent_end) + static_cast<std::uint32_t>(end));
        } else {
            start = T(start) + tangent_end;
            tangent_end = tangent_end + end;
        }
        current = start;
    } else if (mode == 8) {
        const float t = timer.fraction() / static_cast<float>(duration);
        const float from_weight = (t-1.0f)*(t-1.0f)*(2.0f*t+1.0f);
        const float to_weight = t*t*(3.0f-2.0f*t);
        const float from_tangent_weight = (1.0f-t)*(1.0f-t)*t;
        const float to_tangent_weight = (t-1.0f)*t*t;
        if constexpr (std::is_same_v<T, std::uint8_t>)
            current = static_cast<T>(static_cast<std::int32_t>(start * from_weight + end * to_weight
                    + tangent_start * from_tangent_weight + tangent_end * to_tangent_weight));
        else current = start * from_weight + end * to_weight
                    + tangent_start * from_tangent_weight + tangent_end * to_tangent_weight;
    } else {
        const float amount = factor();
        if constexpr (std::is_same_v<T, std::int32_t>)
            current = static_cast<T>(static_cast<std::int32_t>(static_cast<std::uint32_t>(end) - static_cast<std::uint32_t>(start)) * amount + start);
        else if constexpr (std::is_same_v<T, std::uint8_t>)
            current = static_cast<T>(static_cast<std::int32_t>((end - start) * amount + start));
        else current = (end - start) * amount + start;
    }
    return current;
}

template<class T> T Interpolation<T>::evaluate() {
    if (mode == 7) {
        if constexpr (std::is_integral_v<T>)
            start = static_cast<T>(static_cast<std::uint32_t>(start) + static_cast<std::uint32_t>(end));
        else start = T(start) + end;
        current = start;
    } else if (mode == 17) {
        if constexpr (std::is_integral_v<T>) {
            start = static_cast<T>(static_cast<std::uint32_t>(start) + static_cast<std::uint32_t>(tangent_end));
            tangent_end = static_cast<T>(static_cast<std::uint32_t>(tangent_end) + static_cast<std::uint32_t>(end));
        } else {
            start = T(start) + tangent_end;
            tangent_end = tangent_end + end;
        }
        current = start;
    } else if (mode == 8) {
        const float t = timer.fraction() / static_cast<float>(duration);
        const float from_weight = (t-1.0f)*(t-1.0f)*(2.0f*t+1.0f);
        const float to_weight = t*t*(3.0f-2.0f*t);
        const float from_tangent_weight = (1.0f-t)*(1.0f-t)*t;
        const float to_tangent_weight = (t-1.0f)*t*t;
        if constexpr (std::is_same_v<T, std::uint8_t>)
            current = static_cast<T>(static_cast<std::int32_t>(start * from_weight + end * to_weight
                    + tangent_start * from_tangent_weight + tangent_end * to_tangent_weight));
        else current = start * from_weight + end * to_weight
                    + tangent_start * from_tangent_weight + tangent_end * to_tangent_weight;
    } else {
        const float amount = factor();
        if constexpr (std::is_same_v<T, std::int32_t>)
            current = static_cast<T>(static_cast<std::int32_t>(static_cast<std::uint32_t>(end) - static_cast<std::uint32_t>(start)) * amount + start);
        else if constexpr (std::is_same_v<T, std::uint8_t>)
            current = static_cast<T>(static_cast<std::int32_t>((end - start) * amount + start));
        else current = (end - start) * amount + start;
    }
    return current;
}

template struct Interpolation<std::uint8_t>;
template struct Interpolation<float>;
template struct Interpolation<std::int32_t>;
template struct Interpolation<IntegerTriple>;
template struct Interpolation<Angle>;
template struct Interpolation<FogValue>;
template struct Interpolation<Vector2>;
template struct Interpolation<Vector3>;

} // namespace th20
