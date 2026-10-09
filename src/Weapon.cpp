#include "Weapon.hpp"
namespace th20 {
Weapon::Weapon() noexcept:stone_id(0),field_08(0),role(0),field_10(1),active(0),passive(0) {}
// The original destructor is nonvirtual and only restores the base vptr.
// Both actual Timer subobjects are trivial to destroy.
Weapon::~Weapon() {}
void Weapon::set_passive(std::uint8_t value){passive=value;}
}
