// Original 187-byte ScreenInf constructor at 0x004233B0.
#include "NativeScreenEffect.hpp"
#include "EclDiagnostic.hpp"
namespace th20 {
NativeScreenInf::NativeScreenInf() noexcept
    : TaskInfo(), mode_10(0), field_14(0), alpha_18(0),
      field_1c(0), field_20(0), field_24(0), field_28(0), field_2c(0),
      timer_30(), view_40(0) {
    ecl_diagnostic_hint("initialize ScreenInf\n");
}
}
