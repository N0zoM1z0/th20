// Complete original 30B viewport mode forwarder: actual 806B category
// Boss calls this method twice, which calls our strict-exact 280B setter.
#include "NativeGraphicsModeAction.hpp"
namespace th20 {
void NativeGraphicsModeAction::set_mode_44f700(int mode,int variant) {
    this->set_mode_44f720(mode,variant);
}
}
