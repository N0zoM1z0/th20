#include "EclDiagnostic.hpp"

namespace th20 {

void ecl_diagnostic_hint(const char*, ...) {}

// Original target text. The x86 data profile uses the native CP932 encoding.
const char ecl_missing_subroutine_format[] = " error : 未定義の関数名 %s\n";
const char ecl_invalid_magic_format[] = "error : Spt FileHeader ID error\n";
const char ecl_invalid_version_format[] = "error : Spt FileHeader Version error\n";

} // namespace th20
