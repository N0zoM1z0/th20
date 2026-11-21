#include "IntrusiveLink.hpp"

#include <cassert>

int main() {
    th20::IntrusiveList<int> list;
    int first = 1;
    int second = 2;
    int third = 3;
    th20::IntrusiveLink<int> first_link(&first);
    th20::IntrusiveLink<int> second_link(&second);
    th20::IntrusiveLink<int> third_link(&third);

    list.prepend(&first_link);
    assert(list.front() == &first_link);
    assert(list.tail == &first_link);
    assert(first_link.owner == &list);

    list.prepend(&second_link);
    assert(list.front() == &second_link);
    assert(second_link.next == &first_link);
    assert(first_link.previous == &second_link);
    assert(list.tail == &first_link);
    assert(second_link.owner == &list);

    list.prepend(&third_link);
    assert(list.front() == &third_link);
    assert(third_link.next == &second_link);
    assert(second_link.previous == &third_link);
    assert(first_link.next == nullptr);
    assert(list.tail == &first_link);
    assert(third_link.owner == &list);
}
