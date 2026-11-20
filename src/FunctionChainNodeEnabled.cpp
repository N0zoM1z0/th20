#include "FunctionChain.hpp"

namespace th20 {

std::uint32_t FunctionChainNode::enabled() const {
    return (flags.bits>>1)&1u;
}

}
