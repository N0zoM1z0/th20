#include "BulletValues.hpp"

namespace th20 {

ExtendedCommand::ExtendedCommand()
    : timer(), scalar_10(0), scalar_14(0), vector_18(), vector_24(),
      word_30(0), word_34(0), word_38(0), word_3c(0) {}

ShotParameters::ShotParameters()
    : type(0), color(0), position(), angle(0), angle_step(0), speed(0),
      speed_step(0), count(0), rows(0) {}

BulletCommand::BulletCommand()
    : operand_00(0), operand_04(0), operand_08(0), operand_0c(0),
      operand_10(0), operand_14(0), operand_18(0), operand_1c(0),
      opcode(0), flags(0), script(nullptr) {}

} // namespace th20
