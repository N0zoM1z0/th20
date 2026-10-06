#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include "SoundEffects.hpp"

namespace th20 {

void SoundEffectChannel::release() {
    if (buffer) {
        buffer->Release();
        buffer = nullptr;
    }
}

} // namespace th20
