#include "SoundInf.hpp"
#include "LockRegistry.hpp"
#include "NativeSoundCommandArrayView.hpp"
#include "SecureCrt.hpp"
#include "EclDiagnostic.hpp"
#include <cstddef>
#include <cstdint>
#include <mutex>

namespace th20 {

void SoundInf::enqueue(std::int32_t type, std::int32_t argument, const char* name) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(11));
    std::int32_t index = 0;
    goto check;
increment:
    ++index;
check:
    if (index >= 31)
        goto finished;
    if ((*reinterpret_cast<NativeSoundCommandArrayView*>(
            reinterpret_cast<std::uint8_t*>(this) + offsetof(SoundInf, commands)))[index].type == 0)
        goto enqueue;
    goto increment;
enqueue:
    (*reinterpret_cast<NativeSoundCommandArrayView*>(
        reinterpret_cast<std::uint8_t*>(this) + offsetof(SoundInf, commands)))[index].type = type;
    (*reinterpret_cast<NativeSoundCommandArrayView*>(
        reinterpret_cast<std::uint8_t*>(this) + offsetof(SoundInf, commands)))[index].argument = argument;
    strcpy_s((*reinterpret_cast<NativeSoundCommandArrayView*>(
        reinterpret_cast<std::uint8_t*>(this) + offsetof(SoundInf, commands)))[index].name,
        0x100, name);
    (*reinterpret_cast<NativeSoundCommandArrayView*>(
        reinterpret_cast<std::uint8_t*>(this) + offsetof(SoundInf, commands)))[index].stage = 0;
finished:
    ecl_diagnostic_hint("Sound Que Add %d\r\n", type);
}

} // namespace th20
