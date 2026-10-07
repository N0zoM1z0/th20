#include "EclDiagnostic.hpp"

namespace th20 {

void ecl_diagnostic_hint(const char*, ...) {}

// Original target text. The x86 data profile uses the native CP932 encoding.
const char ecl_missing_subroutine_format[] = " error : 未定義の関数名 %s\n";

} // namespace th20
