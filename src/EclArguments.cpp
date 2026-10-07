#include "EclRuntime.hpp"

// Read payload words without changing the instruction or consuming the stack.
#define ECL_FLOAT(ins, index) reinterpret_cast<const float*>((ins) + 1)[index]
#define ECL_INTEGER(ins, index) (reinterpret_cast<std::int32_t*>((ins) + 1)[index])

namespace th20 {

float EclRuntime::float_argument_value(std::int32_t index, float value) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (value >= 0.0f) {
            auto& source = stack;
            return *reinterpret_cast<float*>(&source.local(static_cast<std::int32_t>(value)));
        } else if (value <= -1.0f && value >= -100.0f) {
            auto& source = stack;
            source.peek(static_cast<std::int32_t>(value * 8.0f), &value, 'f');
            return value;
        } else {
            return manager->read_float(static_cast<std::int32_t>(value));
        }
    } else {
        return value;
    }
}

std::int32_t EclRuntime::integer_argument_value(std::int32_t index, std::int32_t value) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (value >= 0) {
            auto& source = stack;
            return static_cast<std::int32_t>(source.local(value));
        } else if (value >= -100) {
            auto& source = stack;
            source.peek(static_cast<std::int32_t>(static_cast<std::uint32_t>(value) << 3), &value, 'i');
            return value;
        } else {
            return manager->read_integer(value);
        }
    } else {
        return value;
    }
}


float EclRuntime::float_argument(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_FLOAT(instruction, index) >= 0.0f) {
            auto& source = stack;
            return *reinterpret_cast<float*>(&source.local(static_cast<std::int32_t>(ECL_FLOAT(instruction, index))));
        } else if (ECL_FLOAT(instruction, index) <= -1.0f && ECL_FLOAT(instruction, index) >= -100.0f) {
            float value;
            auto& source = stack;
            source.peek(static_cast<std::int32_t>(ECL_FLOAT(instruction, index) * 8.0f), &value, 'f');
            return value;
        } else {
            return manager->read_float(static_cast<std::int32_t>(ECL_FLOAT(instruction, index)));
        }
    } else {
        return ECL_FLOAT(instruction, index);
    }
}
float EclRuntime::consuming_float(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_FLOAT(instruction, index) >= 0.0f) {
            auto& source = stack;
            return *reinterpret_cast<float*>(&source.local(static_cast<std::int32_t>(ECL_FLOAT(instruction, index))));
        } else if (ECL_FLOAT(instruction, index) <= -1.0f && ECL_FLOAT(instruction, index) >= -100.0f) {
            float value;
            auto& source = stack;
            source.pop(4, &value, 'f');
            return value;
        } else {
            return manager->read_float(static_cast<std::int32_t>(ECL_FLOAT(instruction, index)));
        }
    } else {
        return ECL_FLOAT(instruction, index);
    }
}
float EclRuntime::consuming_float_value(std::int32_t index, float value) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (value >= 0.0f) {
            auto& source = stack;
            return *reinterpret_cast<float*>(&source.local(static_cast<std::int32_t>(value)));
        } else if (value <= -1.0f && value >= -100.0f) {
            auto& source = stack;
            source.pop(4, &value, 'f');
            return value;
        } else {
            return manager->read_float(static_cast<std::int32_t>(value));
        }
    } else {
        return value;
    }
}
std::int32_t EclRuntime::integer_argument(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_INTEGER(instruction, index) >= 0) {
            auto& source = stack;
            return static_cast<std::int32_t>(source.local(ECL_INTEGER(instruction, index)));
        } else if (ECL_INTEGER(instruction, index) >= -100) {
            auto& source = stack;
            source.peek(static_cast<std::int32_t>(static_cast<std::uint32_t>(ECL_INTEGER(instruction, index)) << 3), &index, 'i');
            return index;
        } else {
            return manager->read_integer(ECL_INTEGER(instruction, index));
        }
    } else {
        return ECL_INTEGER(instruction, index);
    }
}
std::int32_t EclRuntime::consuming_integer(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_INTEGER(instruction, index) >= 0) {
            auto& source = stack;
            return static_cast<std::int32_t>(source.local(ECL_INTEGER(instruction, index)));
        } else if (ECL_INTEGER(instruction, index) >= -100) {
            auto& source = stack;
            source.pop(4, &index, 'i');
            return index;
        } else {
            return manager->read_integer(ECL_INTEGER(instruction, index));
        }
    } else {
        return ECL_INTEGER(instruction, index);
    }
}
std::int32_t EclRuntime::consuming_integer_value(std::int32_t index, std::int32_t value) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (value >= 0) {
            auto& source = stack;
            return static_cast<std::int32_t>(source.local(value));
        } else if (value >= -100) {
            auto& source = stack;
            source.pop(4, &value, 'i');
            return value;
        } else {
            return manager->read_integer(value);
        }
    } else {
        return value;
    }
}
std::int32_t* EclRuntime::integer_destination(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_INTEGER(instruction, index) >= 0) {
            auto& source = stack;
            return reinterpret_cast<std::int32_t*>(&source.local(ECL_INTEGER(instruction, index)));
        } else {
            return manager->integer_destination(ECL_INTEGER(instruction, index));
        }
    }
    return nullptr;
}
float* EclRuntime::float_destination(std::int32_t index) {
    auto* instruction = current();
    if (instruction->references & (1 << index)) {
        if (ECL_FLOAT(instruction, index) >= 0.0f) {
            auto& source = stack;
            return reinterpret_cast<float*>(&source.local(static_cast<std::int32_t>(ECL_FLOAT(instruction, index))));
        } else {
            return manager->float_destination(static_cast<std::int32_t>(ECL_FLOAT(instruction, index)));
        }
    }
    return nullptr;
}
float* EclRuntime::float_destination_at(EclInstruction* instruction, std::int32_t frame_base, std::int32_t index) {
    if (instruction->references & (1 << index)) {
        if (ECL_FLOAT(instruction, index) >= 0.0f) {
            auto& source = stack;
            return reinterpret_cast<float*>(&source.absolute(static_cast<std::int32_t>(ECL_FLOAT(instruction, index)) + frame_base));
        } else {
            return manager->float_destination(static_cast<std::int32_t>(ECL_FLOAT(instruction, index)));
        }
    }
    return nullptr;
}

EclInstruction* EclRuntime::current() {
    EclInstruction* instruction;
    if (position.offset != -1 && position.subroutine != -1) {
        instruction = manager->loader->instruction(position.subroutine, position.offset);
    } else {
        instruction = nullptr;
    }
    return instruction;
}
} // namespace th20
