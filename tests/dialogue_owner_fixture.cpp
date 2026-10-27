#include "dialogue_owner_fixture.hpp"
#include "Animation.hpp"
#include "Bullet.hpp"
#include "EnemyController.hpp"
#include "LaserParameters.hpp"
#include "Session.hpp"
#include "TextLine.hpp"
#include "WindowState.hpp"
#include <cmath>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <new>

namespace th20::test {
namespace {
DialogueOwnerFixture* active;
OtherSpawn other_spawn;
}

struct DialogueOwnerFixture::State {
    AsciiInf* saved_ascii = current_ascii;
    FrontInf* saved_front = current_front;
    AnimationFile* saved_file = shared_text_animation_file;
    Context saved_context = session.context(0);
    DialogueOwnerFixture* saved_active = active;
    std::unique_ptr<BulletController> bullets = std::make_unique<BulletController>();
    std::unique_ptr<LaserController> lasers = std::make_unique<LaserController>();
    std::unique_ptr<EnemyController> enemies = std::make_unique<EnemyController>();
    AsciiInf ascii[2];
    FrontInf frame;
    AnimationFile files[4];
    Animation animations[4];
    alignas(Dialogue) std::array<unsigned char, sizeof(Dialogue) + 64> storage;
    std::vector<DialogueEvent> events;
    Dialogue* value = nullptr;
    Dialogue* constructing = nullptr;
    Dialogue* followed = nullptr;
    Animation* followed_animation = nullptr;
    Vector3 followed_position;
    std::int32_t failure = -1;
    unsigned spawns = 0;
    bool mutate = false;
    State() { events.reserve(128); }
};

struct DialogueFixtureBackend {
    static DialogueOwnerFixture::State& state() {
        assert(active);
        return *active->state_;
    }
    static AnimationHandle spawn(AnimationFile& file, const char* stem,
            std::int32_t script, const Vector3* position, float rotation,
            std::int32_t layer, std::uint32_t flags, Animation** output) {
        if (!active || flags != 0) {
            assert(other_spawn);
            return other_spawn(file, stem, script, position, rotation, layer, flags, output);
        }
        auto& s = state();
        const unsigned index = s.spawns++;
        assert(index < 4 && &file == &s.files[index]);
        assert(!std::strcmp(stem, "text") && script == (index < 2 ? 20 : 21));
        assert(!position && rotation == 0.0f && layer == -1 && !output);
        s.events.push_back({'s', script});
        if (s.failure == static_cast<std::int32_t>(index)) throw DialogueFailure{s.failure};
        current_ascii = &s.ascii[(index + 1) & 1u];
        shared_text_animation_file = &s.files[(index + 1) & 3u];
        if (s.mutate && index == 3) {
            auto& d = *s.constructing;
            d.field_108 = 123; d.field_10c = 456; d.fields_118[1] = 789;
            d.field_114 = 2; d.positions[0].y = 123.0f;
        }
        AnimationHandle result;
        result.value = 0x200u + index;
        return result;
    }
    static bool resolve(AnimationHandle& handle, Animation*& result) {
        if (!active || handle.value < 0x200u || handle.value >= 0x204u) return false;
        auto& s = state();
        const auto index = handle.value - 0x200u;
        s.events.push_back({'r', static_cast<std::int32_t>(index)});
        result = &s.animations[index];
        return true;
    }
    static void retire(AnimationHandle& handle) {
        auto& s = state();
        s.events.push_back({'d', static_cast<std::int32_t>(handle.value)});
        handle.value = 0;
    }
    static void interrupt(AnimationHandle& handle, std::int32_t event) {
        auto& s = state();
        assert((handle.value == 0x201u || handle.value == 0x203u) && event == 7);
        s.events.push_back({'i', event});
    }
    static std::int32_t bullets(BulletController& owner, std::int32_t mode) {
        auto& s = state();
        assert(&owner == s.bullets.get() && mode == 0 && s.spawns == 4);
        s.events.push_back({'b', mode});
        if (s.failure == 4) throw DialogueFailure{4};
        if (s.mutate) {
            s.constructing->field_108 = 432;
            s.constructing->field_110 = 73;
            s.constructing->flags.flag_6 = 1;
        }
        return 7;
    }
    static std::int32_t lasers(LaserController& owner, std::int32_t mode,
                               std::int32_t argument) {
        auto& s = state();
        assert(&owner == s.lasers.get() && mode == 0 && argument == 0);
        s.events.push_back({'l', argument});
        if (s.failure == 5) throw DialogueFailure{5};
        if (s.mutate) {
            s.constructing->field_10c = 567;
            s.constructing->field_110 = 99;
            s.constructing->flags.flag_6 = 1;
            s.constructing->text_position = Vector3(-1.0f, -2.0f, -3.0f);
            s.constructing->text_width = -4.0f;
        }
        return 1;
    }
    static void set_follow_position(Animation& destination, const Vector3& position) {
        auto& s = state();
        assert(s.value);
        s.followed = s.value;
        s.followed_animation = &destination;
        s.followed_position = position;
    }
};

DialogueOwnerFixture::DialogueOwnerFixture() : state_(std::make_unique<State>()) {
    active = this;
    auto& s = *state_;
    auto& context = session.context(0);
    context.primary_owner = s.bullets.get();
    context.object_14 = s.lasers.get();
    context.enemies = s.enemies.get();
    current_ascii = &s.ascii[0];
    current_front = &s.frame;
}

DialogueOwnerFixture::~DialogueOwnerFixture() {
    destroy();
    const auto ascii = state_->saved_ascii;
    const auto front = state_->saved_front;
    const auto file = state_->saved_file;
    const auto context = state_->saved_context;
    const auto previous = state_->saved_active;
    state_.reset();
    current_ascii = ascii; current_front = front;
    shared_text_animation_file = file;
    session.context(0) = context;
    active = previous;
}

Dialogue* DialogueOwnerFixture::construct(unsigned char pattern, std::uint8_t* script,
                                         std::int32_t failure, bool mutate) {
    destroy();
    auto& s = *state_;
    active = this;
    s.spawns = 0; s.events.clear(); s.failure = failure; s.mutate = mutate;
    s.followed = nullptr; s.followed_animation = nullptr;
    s.storage.fill(pattern);
    s.constructing = reinterpret_cast<Dialogue*>(s.storage.data() + 32);
    for (unsigned i = 0; i < 4; ++i) {
        s.animations[i].~Animation();
        ::new (&s.animations[i]) Animation;
        s.animations[i].base.flags.word_04 = 0xABCDEF00u + i;
        s.animations[i].field_578 = 0xA7;
        s.animations[i].field_579 = 0xB8;
    }
    current_ascii = &s.ascii[0];
    current_front = &s.frame;
    shared_text_animation_file = &s.files[0];
    // Distinct instance files must never replace the shared text resource.
    s.ascii[0].animation_file = &s.files[3];
    s.ascii[1].animation_file = &s.files[2];
    s.value = ::new (s.storage.data() + 32) Dialogue(script);
    s.frame.dialogue = s.value;
    // Link real Animation child nodes and identifiers, not a fabricated tree
    // lookup. The native recursive selector is linked from AnimationBinding.
    s.animations[0].child_links[1].next = &s.animations[1].link_500;
    s.animations[1].link_500.previous = &s.animations[0].child_links[1];
    s.animations[1].base.field_440 = 166;
    return s.value;
}

void DialogueOwnerFixture::destroy() {
    if (state_->value) {
        state_->value->~Dialogue();
        state_->value = nullptr;
        state_->frame.dialogue = nullptr;
    }
}
Dialogue* DialogueOwnerFixture::subject() { return state_->value; }
FrontInf& DialogueOwnerFixture::front() { return state_->frame; }
Animation& DialogueOwnerFixture::animation(unsigned index) { assert(index < 4); return state_->animations[index]; }
const std::vector<DialogueEvent>& DialogueOwnerFixture::events() const { return state_->events; }
void DialogueOwnerFixture::check_guards(unsigned char pattern) const {
    const auto& s = state_->storage;
    assert(std::all_of(s.begin(), s.begin()+32, [&](auto c) { return c == pattern; }));
    assert(std::all_of(s.end()-32, s.end(), [&](auto c) { return c == pattern; }));
}
void DialogueOwnerFixture::check_follow(Dialogue* receiver, Animation* animation) const {
    assert(state_->followed == receiver && state_->followed_animation == animation);
}
void DialogueOwnerFixture::check_position(float x, float y, float z) const {
    const auto& p = state_->followed_position;
    assert(std::fabs(p.x-x) < 0.0001f && std::fabs(p.y-y) < 0.0001f && std::fabs(p.z-z) < 0.0001f);
}
bool try_dialogue_resolve(AnimationHandle& handle, Animation*& output) {
    return DialogueFixtureBackend::resolve(handle, output);
}
void record_dialogue_retirement(AnimationHandle& handle) { DialogueFixtureBackend::retire(handle); }
void set_other_spawn(OtherSpawn function) { other_spawn = function; }
} // namespace th20::test

namespace th20 {
// These resource lifecycles remain explicit fixture boundaries. Typed members
// use their actual maintained destructors; no native resource retirement claim.
AsciiInf::~AsciiInf() = default;
void AsciiInf::enable() { std::abort(); }
BulletController::~BulletController() = default;
void BulletController::enable() { std::abort(); }
LaserController::~LaserController() = default;
// Production Dialogue destructor is linked; only resource backends are fixtures.
// Real Dialogue::follow_box and AnimationHandle::find_child are linked.
// Native animation tree/geometry/update owners are separate verified boundaries.
WindowState window_state{};
Vector3& Animation::position(Vector3& output) { output = vector_5bc; return output; }
float Animation::scale_x_value() { return base.vector_50.x; }
void Animation::set_position(const Vector3& value) {
    vector_5bc = value;
    test::DialogueFixtureBackend::set_follow_position(*this, value);
}
void AnimationHandle::interrupt(std::int32_t event) { test::DialogueFixtureBackend::interrupt(*this, event); }
std::int32_t BulletController::cancel_all(std::int32_t mode) { return test::DialogueFixtureBackend::bullets(*this, mode); }
std::int32_t LaserController::cancel_all(std::int32_t mode, std::int32_t argument) { return test::DialogueFixtureBackend::lasers(*this, mode, argument); }
AnimationHandle AnimationFile::spawn(const char* stem, std::int32_t script,
        const Vector3* position, float rotation, std::int32_t layer,
        std::uint32_t flags, Animation** output) {
    return test::DialogueFixtureBackend::spawn(*this, stem, script, position, rotation, layer, flags, output);
}
} // namespace th20
