#pragma once
#include "DialogueText.hpp"
#include "AnimationFile.hpp"
#include "HudGauge.hpp"
#include <memory>
#include <vector>

namespace th20::test {
struct DialogueEvent {
    char kind;
    std::int32_t value;
    bool operator==(const DialogueEvent&) const = default;
};
struct DialogueFailure { std::int32_t stage; };
struct DialogueFixtureBackend;

// Real owners surround a captured File/Renderer/cancellation boundary.
class DialogueOwnerFixture {
    struct State;
    std::unique_ptr<State> state_;
    friend struct DialogueFixtureBackend;
public:
    DialogueOwnerFixture();
    ~DialogueOwnerFixture();
    DialogueOwnerFixture(const DialogueOwnerFixture&) = delete;
    DialogueOwnerFixture& operator=(const DialogueOwnerFixture&) = delete;
    Dialogue* construct(unsigned char pattern, std::uint8_t* script,
                        std::int32_t failure = -1, bool mutate = false);
    void destroy();
    Dialogue* subject();
    FrontInf& front();
    Animation& animation(unsigned index);
    const std::vector<DialogueEvent>& events() const;
    void check_guards(unsigned char pattern) const;
    void check_follow(Dialogue* receiver, Animation* animation) const;
};

bool try_dialogue_resolve(AnimationHandle& handle, Animation*& output);
void record_dialogue_retirement(AnimationHandle& handle);
using OtherSpawn = AnimationHandle (*)(AnimationFile&, const char*, std::int32_t,
    const Vector3*, float, std::int32_t, std::uint32_t, Animation**);
void set_other_spawn(OtherSpawn function);
} // namespace th20::test
