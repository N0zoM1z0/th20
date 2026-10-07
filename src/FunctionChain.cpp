#include "FunctionChain.hpp"

namespace th20 {

template struct IntrusiveLink<FunctionChainNode>;

void FunctionChainNode::set_callback(FunctionChainCallback value) {
    callback = value;
    before_insert = nullptr;
    on_shutdown = nullptr;
}

void FunctionChainNode::set_userdata(void* value) {
    userdata = value;
}

void FunctionChainNode::set_owned() {
    flags |= 1u;
}

void FunctionChainNode::enable() {
    flags |= 2u;
}

void FunctionChainNode::disable() {
    flags &= ~2u;
}

void FunctionChainNode::set_before_insert(FunctionChainCallback value) {
    before_insert = value;
}

void FunctionChainNode::set_shutdown_callback(FunctionChainCallback value) {
    on_shutdown = value;
}

void FunctionChainNode::clear_callbacks() {
    callback = nullptr;
    before_insert = nullptr;
    on_shutdown = nullptr;
}

} // namespace th20
