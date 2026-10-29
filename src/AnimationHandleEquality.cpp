// Native four-byte AnimationHandle equality used by original Player frame.
// Byte-identical to the separately accepted 45-byte effect-handle equality
// at physical 0x00449430; native ICF provenance remains an open question.
// This defines a genuine method on the live AnimationHandle object rather
// than aliasing it to an unrelated C++ object through a cast.
#include "AnimationHandle.hpp"
namespace th20 {
bool AnimationHandle::operator==(std::uint32_t input) const {
    return value == input;
}
}
