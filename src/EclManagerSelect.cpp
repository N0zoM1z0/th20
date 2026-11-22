#include "EclRuntime.hpp"

namespace th20 {

int EclManager::select(const char* name) {
    EclLoader* source = loader;
    return source->select(this, name);
}

} // namespace th20
