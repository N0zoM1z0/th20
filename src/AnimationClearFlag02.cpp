#include "Animation.hpp"

namespace th20 {

void Animation::clear_flag_02() {
    base.flags.byte_02 &= 0xfeu;
}

} // namespace th20
