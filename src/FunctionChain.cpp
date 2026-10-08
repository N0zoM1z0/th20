#include "FunctionChain.hpp"

namespace th20 {

template struct IntrusiveLink<FunctionChainNode>;

FunctionChainNode::FunctionChainNode() noexcept : priority(0), flags{},
    callback(nullptr), before_insert(nullptr), on_shutdown(nullptr), link(this),
    userdata(nullptr) {}

FunctionChainCallback FunctionChainNode::shutdown_callback_value() { return on_shutdown; }
void* FunctionChainNode::userdata_value() { return userdata; }

void FunctionChainNode::set_callback(FunctionChainCallback value) {
    callback = value;
    before_insert = nullptr;
    on_shutdown = nullptr;
}

void FunctionChainNode::set_userdata(void* value) {
    userdata = value;
}

void FunctionChainNode::set_owned() {
    flags.bits |= 1u;
}

void FunctionChainNode::enable() {
    flags.bits |= 2u;
}

void FunctionChainNode::disable() {
    flags.bits &= ~2u;
}

void FunctionChainNode::set_before_insert(FunctionChainCallback value) {
    before_insert = value;
}

void FunctionChainNode::set_shutdown_callback(FunctionChainCallback value) {
    on_shutdown = value;
}

FunctionChainNode::~FunctionChainNode() {
    callback = nullptr;
    before_insert = nullptr;
    on_shutdown = nullptr;
}

} // namespace th20
