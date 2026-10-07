#pragma once

#include "AnimationHandle.hpp"
#include "BulletValues.hpp"
#include "EnemyCounters.hpp"
#include "EnemyHealth.hpp"
#include "EnemyMovement.hpp"
#include "EnemyPattern.hpp"
#include "Identifier32.hpp"
#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <memory>
#include <memory_resource>
#include <vector>

namespace th20 {

struct Enemy;
struct Context;
struct ShotMetadata;
struct EnemyMeshOwner;

struct EnemyAnimationLink {
    AnimationHandle handle;
    Vector3 offset;
    std::int32_t parent;
    EnemyAnimationLink();
};

// The shared owner supplies shot metadata. Its pointed-to layout and lifetime
// producers remain open; the queued value owns the real shared_ptr subobject.
struct EnemyQueuedRecord {
    std::shared_ptr<ShotMetadata> owner;
    ShotParameters parameters;
    std::uint32_t field_30;
    Vector3 vector_34, vector_40;
    EnemyQueuedRecord();
};

// Native phase configuration writes two independently terminated 64-byte names.
struct EnemyPhase {
    std::int32_t life, time;
    char script[64], timeout_script[64];
};

struct EnemyBounds {
    float x, y, width, height;
    EnemyBounds();
};

struct EnemyStateFlags {
    std::uint32_t word_00, word_04, word_08;
};

// Actual 752-byte subobject at Enemy+88. Neutral scalar names retain unresolved
// roles. Callback address words retain storage until their full ABI is proven.
struct EnemyState {
    Identifier32 identifier, identifier_04;
    Enemy* entity;
    std::pmr::vector<EnemyAnimationLink> animations;
    std::int32_t field_1c, field_20, field_24, field_28, field_2c, field_30, field_34;
    float field_38, field_3c, field_40;
    std::int32_t field_44, field_48;
    float field_4c;
    std::int32_t field_50, field_54, field_58;
    Vector2 bounds_5c, bounds_64;
    Vector3 vector_6c;
    EnemyCounters counters;
    Timer timer_a8, timer_b8;
    Motion motion_c8, motion_110;
    std::pmr::vector<EnemyMovement> movements;
    std::pmr::forward_list<EnemyQueuedRecord> queued;
    Vector2 vector_170;
    EnemyBounds bounds_178;
    Identifier32 identifier_188;
    EnemyHealth health;
    EnemyPattern pattern;
    std::int32_t field_250, field_254, field_258, field_25c, field_260;
    std::int32_t field_264, field_268, field_26c, field_270;
    float field_274;
    std::int32_t field_278, field_27c, field_280, field_284;
    Timer timer_288, timer_298, timer_2a8;
    std::pmr::vector<EnemyPhase> phases;
    EnemyStateFlags flags;
    EnemyMeshOwner* mesh;
    std::uint32_t field_2d8, field_2dc, field_2e0, field_2e4, field_2e8;
    Context* context;

    EnemyState();
    ~EnemyState();
    int initialize();
    void combine_movements();
    // The whole 48C010 dispatcher remains undefined while its owners are closed.
    int execute_opcode();
    std::int32_t integer_argument(std::int32_t index);
    float float_argument(std::int32_t index);
};

static_assert(sizeof(EnemyPhase) == 136);
static_assert(offsetof(EnemyPhase, script) == 8);
static_assert(offsetof(EnemyPhase, timeout_script) == 0x48);
static_assert(sizeof(EnemyBounds) == 16);
static_assert(sizeof(EnemyStateFlags) == 12);
static_assert(sizeof(EnemyAnimationLink) == 20);
#if defined(_M_IX86)
static_assert(sizeof(EnemyQueuedRecord) == 76);
static_assert(offsetof(EnemyQueuedRecord, parameters) == 8);
static_assert(offsetof(EnemyQueuedRecord, vector_34) == 0x34);
static_assert(offsetof(EnemyQueuedRecord, vector_40) == 0x40);
static_assert(sizeof(EnemyState) == 752);
static_assert(offsetof(EnemyState, entity) == 8);
static_assert(offsetof(EnemyState, animations) == 0xc);
static_assert(offsetof(EnemyState, field_38) == 0x38);
static_assert(offsetof(EnemyState, counters) == 0x78);
static_assert(offsetof(EnemyState, motion_110) == 0x110);
static_assert(offsetof(EnemyState, movements) == 0x158);
static_assert(offsetof(EnemyState, queued) == 0x168);
static_assert(offsetof(EnemyState, bounds_178) == 0x178);
static_assert(offsetof(EnemyState, health) == 0x18c);
static_assert(offsetof(EnemyState, pattern) == 0x1a8);
static_assert(offsetof(EnemyState, phases) == 0x2b8);
static_assert(offsetof(EnemyState, flags) == 0x2c8);
static_assert(offsetof(EnemyState, context) == 0x2ec);
#endif

} // namespace th20
