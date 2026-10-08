#pragma once

#include "Interpolation.hpp"
#include "IntrusiveLink.hpp"
#include "ScriptStack.hpp"
#include "GameRandom.hpp"

#include <cstddef>
#include <cstdint>
#include <array>
#include <memory_resource>
#include <vector>

namespace th20 {

struct EclInstruction {
    std::int32_t time;
    std::int16_t opcode;
    std::uint16_t length;
    std::uint16_t references;
    std::uint8_t rank;
    std::uint8_t argument_count;
    std::uint8_t stack_drop;
    std::uint8_t field_0d;
    std::uint16_t field_0e;
};
static_assert(sizeof(EclInstruction) == 16);

struct EclScriptPosition {
    std::int32_t subroutine;
    std::int32_t offset;
    EclScriptPosition();
};
static_assert(sizeof(EclScriptPosition) == 8);

struct EclScriptInterpolation : FloatInterpolation {
    std::int32_t frame_base;
    EclScriptPosition position;
    void set_tangent_start(const float& value);
    void set_tangent_end(const float& value);
    void reset_time();
};

class EclManager;

// Aggregate flag storage preserves the observed four-byte initialization.
// The original source type name remains unknown.
struct EclRuntimeFlags { std::uint32_t bits; };
static_assert(sizeof(EclRuntimeFlags) == 4);

struct EclRuntime {
    float time;
    EclScriptPosition position;
    ScriptStack stack;
    std::int32_t async_id;
    EclManager* manager;
    std::int32_t signal;
    std::uint8_t rank;
    std::pmr::vector<EclScriptInterpolation> interpolators;
    EclRuntimeFlags flags;

    EclRuntime();
    EclInstruction* current();
    std::int32_t integer_argument(std::int32_t index);
    std::int32_t consuming_integer(std::int32_t index);
    float float_argument(std::int32_t index);
    float consuming_float(std::int32_t index);
    std::int32_t integer_argument_value(std::int32_t index, std::int32_t value);
    float float_argument_value(std::int32_t index, float value);
    std::int32_t* integer_destination(std::int32_t index);
    float* float_destination(std::int32_t index);
    float* float_destination_at(EclInstruction* instruction,
                                std::int32_t frame_base, std::int32_t index);
    std::int32_t consuming_integer_value(std::int32_t index, std::int32_t value);
    float consuming_float_value(std::int32_t index, float value);
    int call_into(EclRuntime* target, std::int32_t argument_skip,
                  std::int32_t name_skip);
    int tick(float delta);
};

struct EclSubroutineRecord {
    const char* name;
    std::uint8_t* header;
};

class EclLoader {
public:
    // File loading and include parsing precede the deleting destructor.
    // Derived loading borrows the process cache's writable resource buffers.
    virtual std::int32_t load(const char* path);
    virtual std::int32_t include_resources(std::uint8_t* block);
    virtual ~EclLoader();

    std::uint32_t file_count;
    std::uint32_t subroutine_count;
    std::array<std::uint8_t*, 64> files;
    std::uint32_t fields_10c[64];
    std::pmr::vector<EclSubroutineRecord> records;
    ScriptStack globals;

    EclLoader();
    // The complete append body is still under reconstruction. It borrows the
    // writable resource buffer and returns the old file index, or -1.
    int append(std::uint8_t* buffer);
    int activate(EclManager* manager, const char* name);
    int select(EclManager* manager, const char* name);
    std::int32_t subroutine_index(const char* name);
    EclInstruction* instruction(std::int32_t subroutine, std::int32_t offset);
};

class EclManager {
public:
    // Native defaults are concrete zero-return methods, not pure virtual slots.
    virtual ~EclManager();
    virtual std::int32_t execute_opcode();
    virtual std::int32_t read_integer(std::int32_t index);
    virtual std::int32_t* integer_destination(std::int32_t index);
    virtual float read_float(std::int32_t index);
    virtual float* float_destination(std::int32_t index);

    std::uint32_t field_04;
    std::uint32_t field_08;
    EclRuntime* current_runtime;
    EclRuntime main;
    EclLoader* loader;
    IntrusiveLink<EclRuntime> runtimes;

    EclManager();
    void reset();
    void set_loader(EclLoader* value);
    void select_subroutine(const char* name);
    void set_offset(std::int32_t value);
    void set_time(float value);
    EclLoader* loader_value() const;
    int spawn(std::int32_t async_id, std::int32_t argument_skip);
    IntrusiveLink<EclRuntime>* find_runtime(std::int32_t async_id);
    void terminate_async();
    int tick(float delta);
};

// Native shared random owner. Production construction remains unresolved.
extern GameRandom script_random;

#if defined(_M_IX86)
static_assert(sizeof(EclRuntime) == 72);
static_assert(offsetof(EclRuntime, stack) == 12);
static_assert(offsetof(EclRuntime, interpolators) == 52);
static_assert(offsetof(EclRuntime, flags) == 68);
static_assert(sizeof(EclScriptInterpolation) == 56);
static_assert(offsetof(EclScriptInterpolation, frame_base) == 44);
static_assert(sizeof(EclSubroutineRecord) == 8);
static_assert(sizeof(EclManager) == 112);
static_assert(offsetof(EclManager, main) == 16);
static_assert(offsetof(EclManager, loader) == 88);
static_assert(offsetof(EclManager, runtimes) == 92);
static_assert(sizeof(EclLoader) == 564);
static_assert(offsetof(EclLoader, files) == 12);
static_assert(offsetof(EclLoader, fields_10c) == 268);
static_assert(offsetof(EclLoader, records) == 524);
static_assert(offsetof(EclLoader, globals) == 540);
#endif

} // namespace th20
