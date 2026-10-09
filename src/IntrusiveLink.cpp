#include "IntrusiveLink.hpp"
#include "DamageRegion.hpp"

namespace th20 {
template struct IntrusiveLink<DamageRegion>;
template struct IntrusiveList<DamageRegion>;
template class IntrusiveIterator<DamageRegion>;
} // namespace th20
