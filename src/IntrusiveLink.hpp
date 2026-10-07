#pragma once

namespace th20 {

template<class T> struct IntrusiveList;
template<class T> struct IntrusiveIterator;

// Native five-pointer protocol shared by distinct linked value owners.
// List/iterator lifetime and allocation remain separate, unresolved protocols.
template<class T> struct IntrusiveLink {
    T* node;
    IntrusiveLink* next;
    IntrusiveLink* previous;
    IntrusiveList<T>* owner;
    IntrusiveIterator<T>* iterator;

    explicit IntrusiveLink(T* value = nullptr);
    void insert_after(IntrusiveLink* added);
    void insert_before(IntrusiveLink* added);
};

template<class T>
IntrusiveLink<T>::IntrusiveLink(T* value)
    : node(value), next(nullptr), previous(nullptr), owner(nullptr), iterator(nullptr) {}

template<class T>
void IntrusiveLink<T>::insert_after(IntrusiveLink* added) {
    if (next) {
        added->next = next;
        next->previous = added;
    }
    next = added;
    added->owner = owner;
    added->previous = this;
}

template<class T>
void IntrusiveLink<T>::insert_before(IntrusiveLink* added) {
    if (previous) {
        added->previous = previous;
        previous->next = added;
    }
    added->owner = owner;
    added->next = this;
    previous = added;
}

} // namespace th20
