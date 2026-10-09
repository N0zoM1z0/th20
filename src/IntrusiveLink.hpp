#pragma once

// Five-pointer nodes, sentinel lists and single-observer iteration share one
// typed protocol. Reset requires detached storage; list operations do not own T.
namespace th20 {
template<class T> struct IntrusiveList;
template<class T> struct IntrusiveIterator;
template<class T> struct IntrusiveLink {
    T* node;
    IntrusiveLink* next;
    IntrusiveLink* previous;
    IntrusiveList<T>* owner;
    IntrusiveIterator<T>* iterator;
    IntrusiveLink() noexcept;
    explicit IntrusiveLink(T* value);
    void insert_after(IntrusiveLink* added);
    void insert_before(IntrusiveLink* added);
    IntrusiveLink* next_value();
    IntrusiveLink* previous_value();
    T* node_value();
    IntrusiveList<T>* owner_value();
    T*& node_ref();
    T*& node_access();
    void set_iterator(IntrusiveIterator<T>* input);
    void set_owner(IntrusiveList<T>* input);
    void initialize(T* input);
    void detach();
    void detach_inner();
    IntrusiveLink* find(T* input);
};
template<class T> struct IntrusiveList : IntrusiveLink<T> {
    IntrusiveLink<T>* tail;
    IntrusiveList();
    T* node_value();
    void remove(IntrusiveLink<T>* link);
    void append(IntrusiveLink<T>* link);
    void prepend(IntrusiveLink<T>* link);
    void reset(T* input);
    IntrusiveLink<T>* find(T* input);
    IntrusiveLink<T>* front();
    IntrusiveIterator<T> begin();
    IntrusiveIterator<T>* end();
};
template<class T> struct IntrusiveIterator {
    IntrusiveLink<T>* current;
    IntrusiveLink<T>* pending;
    IntrusiveIterator(IntrusiveLink<T>* start, IntrusiveLink<T>* next = nullptr) noexcept;
    ~IntrusiveIterator();
    IntrusiveIterator& advance();
    bool differs(const IntrusiveIterator* other) const;
    IntrusiveLink<T>* get();
};
template<class T> IntrusiveLink<T>::IntrusiveLink() noexcept : node(nullptr),next(nullptr),previous(nullptr),owner(nullptr),iterator(nullptr) {}
template<class T> IntrusiveLink<T>::IntrusiveLink(T* input) : node(input),next(nullptr),previous(nullptr),owner(nullptr),iterator(nullptr) {}
template<class T> void IntrusiveLink<T>::insert_after(IntrusiveLink* added) {
    if(next) {added->next=next;next->previous=added;} next=added;added->owner=owner;added->previous=this;
}
template<class T> void IntrusiveLink<T>::insert_before(IntrusiveLink* added) {
    if(previous){added->previous=previous;previous->next=added;}added->owner=owner;added->next=this;previous=added;
}
template<class T> IntrusiveLink<T>* IntrusiveLink<T>::next_value() {return next;}
template<class T> IntrusiveLink<T>* IntrusiveLink<T>::previous_value() {return previous;}
template<class T> T* IntrusiveLink<T>::node_value(){return node;}
template<class T> IntrusiveList<T>* IntrusiveLink<T>::owner_value(){return owner;}
template<class T> T*& IntrusiveLink<T>::node_ref(){return node;}
template<class T> T*& IntrusiveLink<T>::node_access(){return node_ref();}
template<class T> void IntrusiveLink<T>::set_iterator(IntrusiveIterator<T>* input){iterator=input;}
template<class T> void IntrusiveLink<T>::set_owner(IntrusiveList<T>* input){owner=input;}
template<class T> void IntrusiveLink<T>::initialize(T* input){node=input;previous=nullptr;next=nullptr;owner=nullptr;iterator=nullptr;}
template<class T> void IntrusiveLink<T>::detach(){
    if(owner){IntrusiveList<T>* list=owner;list->remove(this);} else detach_inner();
}
template<class T> void IntrusiveLink<T>::detach_inner(){
    if(iterator){
        if(iterator->current==this) iterator->current=nullptr;
        if(iterator->pending==this && iterator->pending){
            iterator->pending=next;
            if(iterator->pending){IntrusiveLink* node=iterator->pending;node->set_iterator(iterator);}
        }
        iterator=nullptr;
    }
    if(next) next->previous=previous;
    if(previous) previous->next=next;
    next=nullptr;previous=nullptr;owner=nullptr;
}
template<class T> IntrusiveLink<T>* IntrusiveLink<T>::find(T* input){
    IntrusiveLink* link=this;
    while(link){if(link->node_value()==input)return link;link=link->next_value();}
    return nullptr;
}
template<class T> IntrusiveList<T>::IntrusiveList():IntrusiveLink<T>(),tail(this){}
template<class T> T* IntrusiveList<T>::node_value(){return IntrusiveLink<T>::node_value();}
template<class T> void IntrusiveList<T>::remove(IntrusiveLink<T>* link){
    if (tail == link) { tail = link->previous_value(); }
    link->detach_inner();
}
template<class T> void IntrusiveList<T>::append(IntrusiveLink<T>* link){
    IntrusiveLink<T>* end=tail;end->insert_after(link);link->set_owner(this);tail=link;
}
template<class T> void IntrusiveList<T>::prepend(IntrusiveLink<T>* link){
    IntrusiveLink<T>& head=*this;head.insert_after(link);link->set_owner(this);
    if(tail==static_cast<IntrusiveLink<T>*>(this))tail=link;
}
template<class T> void IntrusiveList<T>::reset(T* input){
    IntrusiveLink<T>& head=*this;head.initialize(input);tail=this;
}
template<class T> IntrusiveLink<T>* IntrusiveList<T>::find(T* input){
    IntrusiveLink<T>& head=*this;return head.find(input);
}
template<class T> IntrusiveLink<T>* IntrusiveList<T>::front(){return this->next_value();}
template<class T> IntrusiveIterator<T> IntrusiveList<T>::begin(){return IntrusiveIterator<T>(this->next_value(),nullptr);}
template<class T> IntrusiveIterator<T>* IntrusiveList<T>::end(){return nullptr;}
template<class T> IntrusiveIterator<T>::IntrusiveIterator(IntrusiveLink<T>* start,IntrusiveLink<T>* next) noexcept:current(start),pending(next){
    if(current){IntrusiveLink<T>* link=current;link->set_iterator(this);}
    pending=start?start->next_value():nullptr;
    if(pending){IntrusiveLink<T>* link=pending;link->set_iterator(this);}
}
template<class T> IntrusiveIterator<T>::~IntrusiveIterator(){
    if(current){IntrusiveLink<T>* link=current;link->set_iterator(nullptr);}
    if(pending){IntrusiveLink<T>* link=pending;link->set_iterator(nullptr);}
}
template<class T> IntrusiveIterator<T>& IntrusiveIterator<T>::advance(){
    if(current){IntrusiveLink<T>* link=current;link->set_iterator(nullptr);}
    current=pending;pending=current;
    if(pending){
        pending=current->next_value();
        if(pending){IntrusiveLink<T>* link=pending;link->set_iterator(this);}
    }
    return *this;
}
template<class T> bool IntrusiveIterator<T>::differs(const IntrusiveIterator* other)const{
    return other ? (current!=other->current?1:0) : (current?1:0);
}
template<class T> IntrusiveLink<T>* IntrusiveIterator<T>::get(){return current;}
}

namespace th20 {
static_assert(sizeof(void*) != 4 || sizeof(IntrusiveLink<int>) == 20);
static_assert(sizeof(void*) != 4 || sizeof(IntrusiveList<int>) == 24);
static_assert(sizeof(void*) != 4 || sizeof(IntrusiveIterator<int>) == 8);
} // namespace th20
