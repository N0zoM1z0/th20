#include "EffectParameters.hpp"

namespace th20 {

PackedColor::PackedColor(std::uint32_t initial) : value(initial) {}

SelectionPulse::SelectionPulse() : enabled(0), radius(0) {}

EffectParameters::EffectParameters()
    : vector_00(), vector_0c(), scalar_18(0), scalar_1c(0), color(0),
      scalar_24(0), enabled(1), vector_2c() {}

EffectRequest::EffectRequest()
    : type(-1), original_parameters(nullptr), animation(nullptr), delay(0),
      parameters() {}

} // namespace th20
