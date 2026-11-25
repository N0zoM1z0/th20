#include "Animation.hpp"

namespace th20 {

void Animation::clear_flag_02() {
    base.flags.bits_02.bit_10 = 0;
}

} // namespace th20
