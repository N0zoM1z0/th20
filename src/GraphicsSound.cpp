#include "Graphics.hpp"
namespace th20 {
std::int32_t Graphics::uses_preloaded_music() const {
    return configuration.flags.preload_music;
}
}
