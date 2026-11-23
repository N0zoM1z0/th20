#include "Animation.hpp"

namespace th20 {

bool Animation::is_active() const {
    return base.field_28 >= 0;
}

} // namespace th20
