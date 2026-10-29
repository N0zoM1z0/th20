#include "DiagnosticLog.hpp"
#include "LockRegistry.hpp"
#include "SecureCrt.hpp"

namespace th20 {
const char* report_log_error(DiagnosticLog* log, const char* format, ...) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(3));
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    std::va_list arguments;
    va_start(arguments, format);
    vsprintf_s(buffer, format, arguments);
    va_end(arguments);
    log->text+=buffer;
    log->error=1;
    return format;
}
// Original whole 215B append-only diagnostic logger at 0x00454150.
// It shares the real PMR string, secure CRT buffer, and lock-guard
// semantics with the distinct 221B error-flagging log entry, but
// correctly leaves the native log error byte untouched.
const char* report_log_message(DiagnosticLog* log, const char* format, ...) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(3));
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    std::va_list arguments;
    va_start(arguments, format);
    vsprintf_s(buffer, format, arguments);
    va_end(arguments);
    log->text+=buffer;
    return format;
}
} // namespace th20
