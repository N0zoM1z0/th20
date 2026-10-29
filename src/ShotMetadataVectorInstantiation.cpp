#include "ShotMetadata.hpp"

#include <cstddef>
#include <memory_resource>
#include <vector>

// The game executable contains these actual MSVC standard-library
// instantiations for the native 44-byte shot command element type.
// They are library-origin functions and must not earn game-authored credit.
template th20::BulletCommand&
std::vector<th20::BulletCommand,
            std::pmr::polymorphic_allocator<th20::BulletCommand>>::operator[](
    std::size_t) noexcept;

template std::size_t
std::vector<th20::BulletCommand,
            std::pmr::polymorphic_allocator<th20::BulletCommand>>::size()
    const noexcept;

// The original 12,140-byte Bullet command runner copies and retires the
// actual PMR vector of 44-byte BulletCommand values. Preserve both native
// library template instantiations here, alongside its existing operator[]
// and size() specializations, not as dummy game-owned wrapper functions.
// The runtime's 121B copy and 20B destructor are distinct STL-origin code.
using BulletCommandVector = std::pmr::vector<th20::BulletCommand>;
template BulletCommandVector& BulletCommandVector::operator=(const BulletCommandVector&);
template BulletCommandVector::~vector();
