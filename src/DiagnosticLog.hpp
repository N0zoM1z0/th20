#pragma once
#include <cstddef>
#include <cstdint>
#include <memory_resource>
#include <string>

namespace th20 {
// The native log owns a byte PMR string at +0 and an error byte at +1c.
// Original process construction and flushing remain separate pending owners.
struct DiagnosticLog {
    std::pmr::string text;
    std::int8_t error;
};
extern DiagnosticLog diagnostic_log;
// Native variadic cdecl entry returns its format pointer after formatting.
const char* report_log_error(DiagnosticLog* log, const char* format, ...);
#if defined(_M_IX86)
static_assert(sizeof(std::pmr::string) == 28);
static_assert(offsetof(DiagnosticLog, error) == 0x1c);
static_assert(sizeof(DiagnosticLog) == 32);
#endif
} // namespace th20
