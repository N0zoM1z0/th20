#include "Interpolation.hpp"

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

template struct Interpolation<std::uint8_t>;
template struct Interpolation<float>;
template struct Interpolation<std::int32_t>;
template struct Interpolation<IntegerTriple>;
template struct Interpolation<Angle>;
template struct Interpolation<Vector2>;
template struct Interpolation<Vector3>;

} // namespace th20
