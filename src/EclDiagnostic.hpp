#pragma once

namespace th20 {

// The locked release target's diagnostic hook has an empty complete body.
void ecl_diagnostic_hint(const char* format, ...);
extern const char ecl_missing_subroutine_format[];
extern const char ecl_invalid_magic_format[], ecl_invalid_version_format[];

} // namespace th20
