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
} // namespace th20
