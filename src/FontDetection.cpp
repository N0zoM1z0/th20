#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "FontDetection.hpp"

namespace th20 {

int CALLBACK mark_font_available(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM) {
    *current_font_probe = 1;
    return 1;
}

} // namespace th20
