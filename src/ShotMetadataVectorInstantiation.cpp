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
