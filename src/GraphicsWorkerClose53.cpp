// Native Graphics worker interruption cleanup 53B at 0x004D9E30.
#include "Graphics.hpp"
#include "EclDiagnostic.hpp"
#include "Worker.hpp"
namespace th20 {
struct NativeTickGraphicsView : Graphics {
    void bail_out_4d9e30();
};
extern const char graphics_worker_close_message_571e48[];
void NativeTickGraphicsView::bail_out_4d9e30() {
    ecl_diagnostic_hint(graphics_worker_close_message_571e48);
    worker_0.close_and_detach();
    worker_0.close_and_join();
}
}
