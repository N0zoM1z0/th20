#include "Cursor.hpp"

namespace th20 {

Cursor::Cursor()
    : current(0), previous(0), count(999), minimum(0), wrapping(1) {}

Cursor::~Cursor() = default;

void Cursor::snapshot() {
    previous = current;
}

std::int32_t Cursor::changed() const {
    return previous != current;
}

std::int32_t Cursor::selected(std::int32_t index) const {
    return current == index;
}

void Cursor::set_count(std::int32_t value) {
    count = value;
}

void Cursor::set_wrapping(std::int32_t value) {
    wrapping = value;
}

void Cursor::save() {
    selection_history.push(current);
    count_history.push(count);
    excluded.clear();
}

void Cursor::restore() {
    if (selection_history.empty() != true) {
        current = selection_history.top();
        selection_history.pop();
        count = count_history.top();
        count_history.pop();
    }
    excluded.clear();
}

} // namespace th20
