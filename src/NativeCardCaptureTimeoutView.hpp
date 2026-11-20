#pragma once
#include <cstdint>
namespace th20 {
// Non-allocating receiver view of actual Card state.
struct NativeCardCaptureTimeoutView {
    std::int32_t elapsed_4887d0() const;
};
}
