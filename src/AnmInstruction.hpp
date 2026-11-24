#pragma once
#include <cstddef>
#include <cstdint>

namespace th20 {
// The fixed header and first operand word of a variable-length ANM record.
// Further operands continue in the same script buffer; byte_advance, not
// sizeof(AnmInstruction), advances the VM cursor.
struct AnmInstruction {
    std::int16_t opcode;
    std::uint16_t byte_advance;
    std::int16_t frame;
    std::uint16_t operand_flags;
    std::uint32_t first_operand;
};
static_assert(offsetof(AnmInstruction, opcode) == 0);
static_assert(offsetof(AnmInstruction, byte_advance) == 2);
static_assert(offsetof(AnmInstruction, frame) == 4);
static_assert(offsetof(AnmInstruction, operand_flags) == 6);
static_assert(offsetof(AnmInstruction, first_operand) == 8);
static_assert(sizeof(AnmInstruction) == 12);
} // namespace th20
