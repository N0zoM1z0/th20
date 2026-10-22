#include "EclRuntime.hpp"
#include "EclDiagnostic.hpp"
#include <algorithm>
#include <cstring>

namespace th20 {
namespace {
// Only consumed fields are typed; the remaining fixed file header is opaque.
struct EclFilePrefix {
    std::uint32_t magic;
    std::uint16_t version;
    std::uint16_t include_size;
    std::uint8_t fields_08[8];
    std::uint16_t subroutine_count;
    std::uint8_t fields_12[18];
};
static_assert(offsetof(EclFilePrefix, subroutine_count) == 0x10);
static_assert(sizeof(EclFilePrefix) == 36);
struct EclSubroutinePrefix { std::uint8_t bytes[16]; };
static_assert(sizeof(EclSubroutinePrefix) == 16);
}

int EclLoader::append(std::uint8_t* buffer) {
    files[file_count] = buffer;
    if (reinterpret_cast<EclFilePrefix*>(files[file_count])->magic != 0x54504353) {
        ecl_diagnostic_hint(ecl_invalid_magic_format);
        files[file_count] = nullptr;
        return -1;
    }
    if (reinterpret_cast<EclFilePrefix*>(files[file_count])->version != 1) {
        ecl_diagnostic_hint(ecl_invalid_version_format);
        files[file_count] = nullptr;
        return -1;
    }
    auto* offsets = reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(&reinterpret_cast<EclFilePrefix*>(files[file_count])[1]) +
        reinterpret_cast<EclFilePrefix*>(files[file_count])->include_size);
    auto* name = reinterpret_cast<char*>(offsets +
        reinterpret_cast<EclFilePrefix*>(files[file_count])->subroutine_count);
    subroutine_count += reinterpret_cast<EclFilePrefix*>(files[file_count])->subroutine_count;
    for (std::int32_t i = 0;
         i < reinterpret_cast<EclFilePrefix*>(files[file_count])->subroutine_count;
         ++i, ++offsets) {
        EclSubroutineRecord record{name, reinterpret_cast<std::uint8_t*>(
            *offsets + reinterpret_cast<std::uintptr_t>(files[file_count]))};
        auto position = std::find_if(records.begin(), records.end(),
            [name](EclSubroutineRecord record) { return std::strcmp(name, record.name) < 0; });
        records.insert(position, record);
        name += std::strlen(name) + 1;
    }
    auto file = file_count;
    ++file_count;
    if (reinterpret_cast<EclFilePrefix*>(files[file])->include_size) {
        include_resources(reinterpret_cast<std::uint8_t*>(&reinterpret_cast<EclFilePrefix*>(files[file])[1]));
    }
    return file;
}

EclInstruction* EclLoader::instruction(std::int32_t subroutine, std::int32_t offset) {
    auto& table = records;
    return reinterpret_cast<EclInstruction*>(
        reinterpret_cast<std::uint8_t*>(&reinterpret_cast<EclSubroutinePrefix*>(table[subroutine].header)[1]) + offset);
}
} // namespace th20
