#pragma once
#include "IntrusiveLink.hpp"
namespace th20 {
class Animation;
// Consistent original Animation-specific class-key template specialization.
// Generic IntrusiveList<T> stays a struct for unrelated T; the original
// MSVC /sdl Animation list users need this 24B class to emit native preclear.
// Every actual IntrusiveList<Animation> owner must include this header first.
template<> class IntrusiveList<Animation> : public IntrusiveLink<Animation> {
public:
    IntrusiveLink<Animation>* tail;
    IntrusiveList();
    Animation* node_value();
    void remove(IntrusiveLink<Animation>* link);
    void append(IntrusiveLink<Animation>* link);
    void prepend(IntrusiveLink<Animation>* link);
    void reset(Animation* input);
    IntrusiveLink<Animation>* find(Animation* input);
    IntrusiveLink<Animation>* front();
    IntrusiveIterator<Animation> begin();
    IntrusiveIterator<Animation>* end();
};
inline IntrusiveList<Animation>::IntrusiveList() : IntrusiveLink<Animation>(),tail(this) {}
inline Animation* IntrusiveList<Animation>::node_value(){return IntrusiveLink<Animation>::node_value();}
inline void IntrusiveList<Animation>::remove(IntrusiveLink<Animation>* link){
    if(tail==link)tail=link->previous_value();link->detach_inner();
}
inline void IntrusiveList<Animation>::append(IntrusiveLink<Animation>* link){
    IntrusiveLink<Animation>* end=tail;end->insert_after(link);link->set_owner(this);tail=link;
}
inline void IntrusiveList<Animation>::prepend(IntrusiveLink<Animation>* link){
    IntrusiveLink<Animation>& head=*this;head.insert_after(link);link->set_owner(this);
    if(tail==static_cast<IntrusiveLink<Animation>*>(this))tail=link;
}
inline void IntrusiveList<Animation>::reset(Animation* input){
    IntrusiveLink<Animation>& head=*this;head.initialize(input);tail=this;
}
inline IntrusiveLink<Animation>* IntrusiveList<Animation>::find(Animation* input){
    IntrusiveLink<Animation>& head=*this;return head.find(input);
}
inline IntrusiveLink<Animation>* IntrusiveList<Animation>::front(){return next;}
inline IntrusiveIterator<Animation> IntrusiveList<Animation>::begin(){return IntrusiveIterator<Animation>(this->next_value(),nullptr);}
inline IntrusiveIterator<Animation>* IntrusiveList<Animation>::end(){return nullptr;}
static_assert(sizeof(void*) != 4 || sizeof(IntrusiveList<Animation>)==24);
}
