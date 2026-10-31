// Evidence-only probe: instantiate the Animation-specific intrusive templates
// against their real shared header without changing canonical owner/ABI.
// The 63B link constructor and 61B initializer ALREADY have independent
// strict acceptance under DamageRegion (EXACT-051); do not double-count them.
// The 40B list constructor and 42B list reset remain NONEXACT here.
#include "IntrusiveLink.hpp"
#include "Animation.hpp"
namespace th20 {
template class IntrusiveLink<Animation>;
template struct IntrusiveList<Animation>;
}
