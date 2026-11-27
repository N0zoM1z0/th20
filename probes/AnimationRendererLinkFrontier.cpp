// Bounded probe for the physical Animation list leaves. The 63B link
// constructor and 61B initializer are already exact under DamageRegion;
// this probe instantiates the maintained Animation-specific class-key list
// so the 40B constructor and 42B reset are checked from their real source.
#include "IntrusiveListAnimation.hpp"
namespace th20 {
void probe_animation_list_helpers(Animation* input) {
    IntrusiveList<Animation> list;
    list.reset(input);
}
}
