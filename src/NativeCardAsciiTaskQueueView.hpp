#pragma once
#include <functional>
namespace th20 {
// Borrowed receiver on the actual AsciiInf owner. The source implementation
// uses its real task list and global recursive lock 18.
struct NativeCardAsciiTaskQueueView {
    void enqueue_470180(std::function<void()> task);
};
}
