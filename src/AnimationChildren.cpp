#include "Animation.hpp"
namespace th20 {
IntrusiveLink<Animation>& AnimationChildLinks::operator[](std::int32_t index) { return nodes[index]; }
void Animation::clear_flag0_recursively() {
    base.flags.word_04 &= ~1u;
    if (child_links[1].next_value()) {
        IntrusiveLink<Animation>* children = child_links[1].next_value();
        IntrusiveIterator<Animation> it = children->begin();
        IntrusiveIterator<Animation>* end = children->end();
        for (; it.differs(end); it.advance()) {
            IntrusiveLink<Animation>* link = it.get();
            link->node_access()->clear_flag0_recursively();
        }
    }
}
void Animation::set_flag0_recursively() {
    base.flags.word_04 |= 1u;
    if (child_links[1].next_value()) {
        IntrusiveLink<Animation>* children = child_links[1].next_value();
        IntrusiveIterator<Animation> it = children->begin();
        IntrusiveIterator<Animation>* end = children->end();
        for (; it.differs(end); it.advance()) {
            IntrusiveLink<Animation>* link = it.get();
            link->node_access()->set_flag0_recursively();
        }
    }
}
void Animation::clear_flag_4b4_recursively() {
    base.flags.word_1c &= ~1u;
    if (child_links[1].next_value()) {
        IntrusiveLink<Animation>* children = child_links[1].next_value();
        IntrusiveIterator<Animation> it = children->begin();
        IntrusiveIterator<Animation>* end = children->end();
        for (; it.differs(end); it.advance()) {
            IntrusiveLink<Animation>* link = it.get();
            link->node_access()->clear_flag_4b4_recursively();
        }
    }
}
void Animation::set_flag_4b4_recursively() {
    base.flags.word_1c |= 1u;
    if (child_links[1].next_value()) {
        IntrusiveLink<Animation>* children = child_links[1].next_value();
        IntrusiveIterator<Animation> it = children->begin();
        IntrusiveIterator<Animation>* end = children->end();
        for (; it.differs(end); it.advance()) {
            IntrusiveLink<Animation>* link = it.get();
            link->node_access()->set_flag_4b4_recursively();
        }
    }
}
}
