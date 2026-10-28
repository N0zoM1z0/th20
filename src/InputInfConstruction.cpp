// Entire original 261-byte game-owned InputInf constructor plus five
// original MSVC alignment CC bytes. The native base, RTTI/vtable, twelve
// 0x3D4 InputDevices, two view slots and four 0x30 InputBindings all
// have independently observed original storage and constructor calls.
#include "InputInf.hpp"
#include "EclDiagnostic.hpp"
#include "FunctionChainController.hpp"

namespace th20 {
// Original native startup publishes the actual InputInf* at 0x005B8898.
extern InputInf* process_input_inf;

InputInf::InputInf() noexcept
    : state_10(0), state_14(0), state_18(0), direct_input_1c(nullptr),
      devices(), direct_device_2e10(nullptr), pad_devices{nullptr},
      routing_2e24{}, active_buttons{}, bindings()
{
    ecl_diagnostic_hint("initialize InputInf\n");
    process_input_inf = this;
}
// Whole original 120-byte owner destruction: announce teardown,
// unregister the live scheduled update callback, shut down input devices,
// clear the actual global owner and destroy the true TaskInfo base.
// The compiler emits the distinct 49B virtual scalar-deleting wrapper.
InputInf::~InputInf() {
    ecl_diagnostic_hint("shutdown InputInf\n");
    process_chain->remove(update_node);
    shutdown();
    process_input_inf = nullptr;
}

} // namespace th20
