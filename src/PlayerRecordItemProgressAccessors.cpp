#include "PlayerRecord.hpp"
#include <algorithm>
namespace th20 {
std::int32_t PlayerRecord::clamped_field_b8() {
    field_b8=std::clamp(field_b8,-1,7);
    return field_b8;
}
std::int32_t PlayerRecord::clamped_field_bc() {
    field_bc=std::clamp(field_bc,0,7);
    return field_bc;
}
std::int32_t PlayerRecord::clamped_field_c0() {
    field_c0=std::clamp(field_c0,0,10);
    return field_c0;
}
std::int32_t PlayerRecord::clamped_field_cc() {
    field_cc=std::clamp(field_cc,0,10);
    return field_cc;
}
std::int32_t PlayerRecord::clamped_field_d0() {
    field_d0=std::clamp(field_d0,0,10);
    return field_d0;
}
std::int32_t PlayerRecord::clamped_field_d8() {
    field_d8=std::clamp(field_d8,0,7);
    return field_d8;
}
}
