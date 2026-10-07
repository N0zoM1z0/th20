#include "Random.hpp"
#include "Timer.hpp"
#include "ClockScalar.hpp"
#include "FunctionChain.hpp"
#include "LockRegistry.hpp"
#include "TaskInfo.hpp"
#include "ArchiveCrypt.hpp"
#include "InputState.hpp"
#include "Configuration.hpp"
#include "GameRandom.hpp"
#include "WindowState.hpp"
#include "SoundEffects.hpp"
#include "AnimationHandle.hpp"
#include "Vector3.hpp"
#include "TrophyText.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <new>

void check_scene_resource_protocol();
void check_cursor_history();
void check_replay_records();
void check_effect_values();
void check_bullet_values();
void check_motion_values();
void check_display_values();
void check_dialogue_values();
void check_scalar_math();
void check_script_values();
void check_enemy_values();
void check_enemy_health_pattern();

namespace {
unsigned callback_calls;
std::uint32_t random_sample;
unsigned random_sample_calls;
std::int32_t callback_a(void*) { ++callback_calls; return 1; }
std::int32_t callback_b(void*) { ++callback_calls; return 2; }
std::int32_t callback_c(void*) { ++callback_calls; return 3; }
th20::Timer timer_fixture(std::int32_t previous, std::int32_t current,
                          float fraction, std::uint32_t flags) {
    th20::Timer timer;
    timer.previous = previous;
    timer.current = current;
    timer.current_fraction = fraction;
    timer.flags = flags;
    return timer;
}
}

// Wrapper tests supply one deterministic observation. This is not a maintained
// implementation of the unresolved original lock-slot-10 sampling protocol.
std::uint32_t th20::GameRandom::next() {
    ++random_sample_calls;
    return random_sample;
}

int main() {
    check_scene_resource_protocol();
    check_cursor_history();
    check_replay_records();
    check_effect_values();
    check_bullet_values();
    check_motion_values();
    check_display_values();
    check_dialogue_values();
    check_scalar_math();
    check_script_values();
    check_enemy_values();
    check_enemy_health_pattern();
    th20::trophy_text::Message message;
    std::memset(&message, 0xa5, sizeof(message));
    message.reset();
    assert(message.id == -1);
    const auto* message_bytes = reinterpret_cast<const unsigned char*>(&message);
    for (std::size_t i = 4; i != sizeof(message); ++i) assert(message_bytes[i] == 0xa5);
    const std::uint8_t empty_text[]{0x77};
    const std::uint8_t letter_text[]{0x36, 0x7e};
    auto* shared_text = th20::trophy_text::decode(letter_text);
    assert(std::strcmp(shared_text, "A") == 0);
    assert(th20::trophy_text::decode(empty_text) == shared_text && shared_text[0] == 0);
    // All lengths, high bytes, key wrap and the final buffer byte are covered.
    for (unsigned length = 0; length != 256; ++length) {
        std::array<std::uint8_t, 256> encoded{};
        std::array<char, 256> expected{};
        for (unsigned i = 0; i <= length; ++i) {
            const unsigned value = i == length ? 0 : 1 + (i * 97 + length) % 255;
            expected[i] = static_cast<char>(value);
            const unsigned key = 0x77 + 7 * i + 8 * i * (i - 1);
            encoded[i] = static_cast<std::uint8_t>(value ^ key);
        }
        std::memset(th20::trophy_text::decoded_text, 0xa5, 256);
        assert(th20::trophy_text::decode(encoded.data()) == shared_text);
        assert(std::memcmp(shared_text, expected.data(), length + 1) == 0);
        for (unsigned i = length + 1; i != 256; ++i) {
            assert(static_cast<unsigned char>(shared_text[i]) == 0xa5);
        }
    }
    alignas(th20::Timer) std::array<unsigned char, 24> timer_storage;
    timer_storage.fill(0xa5);
    auto* zero_timer = ::new(timer_storage.data() + 4) th20::Timer;
    assert(zero_timer->previous == 0 && zero_timer->current == 0);
    assert(zero_timer->current_fraction == 0.0f && zero_timer->flags == 0);
    for (std::size_t i = 0; i != timer_storage.size(); ++i) {
        assert(timer_storage[i] == (i >= 4 && i < 20 ? 0 : 0xa5));
    }
    th20::InputButtonState held_input{};
    held_input.current = 0x80000001u;
    for (std::uint32_t i = 0; i != 32; ++i) held_input.held_frames[i] = i + 100;
    const auto held_input_before = held_input;
    assert(held_input.current_bits(0x80000000u) == 0x80000000u);
    for (std::uint32_t i = 0; i != 32; ++i) {
        assert(held_input.held_frame_count(i) == (i == 0 || i == 31 ? i + 100 : 0));
    }
    assert(std::memcmp(&held_input, &held_input_before, sizeof(held_input)) == 0);
    alignas(th20::Vector3) std::array<unsigned char, 20> vector_storage;
    vector_storage.fill(0xa5);
    auto* zero_vector = ::new(vector_storage.data() + 4) th20::Vector3;
    assert(zero_vector->x == 0 && zero_vector->y == 0 && zero_vector->z == 0);
    for (std::size_t i = 0; i != vector_storage.size(); ++i) {
        assert(vector_storage[i] == (i >= 4 && i < 16 ? 0 : 0xa5));
    }
    const auto negative_zero = std::bit_cast<float>(0x80000000u);
    const auto payload_nan = std::bit_cast<float>(0x7fc12345u);
    const th20::Vector3 special_vector(negative_zero, payload_nan, 1.25f);
    assert(std::bit_cast<std::uint32_t>(special_vector.x) == 0x80000000u);
    assert(std::bit_cast<std::uint32_t>(special_vector.y) == 0x7fc12345u);
    th20::Vector3 position(10.0f, -8.0f, 4.0f);
    const th20::Vector3 target(18.0f, 4.0f, -12.0f);
    const auto delta = (target - position) * 0.25f;
    assert(delta.x == 2.0f && delta.y == 3.0f && delta.z == -4.0f);
    assert(position.x == 10.0f && position.y == -8.0f && position.z == 4.0f);
    assert(&(position += delta) == &position);
    assert(position.x == 12.0f && position.y == -5.0f && position.z == 0.0f);
    assert(&(position += position) == &position);
    assert(position.x == 24.0f && position.y == -10.0f && position.z == 0.0f);
    alignas(th20::AnimationHandle) std::array<unsigned char, 12> handle_storage;
    handle_storage.fill(0xa5);
    auto* handle = ::new(handle_storage.data() + 4) th20::AnimationHandle;
    assert(handle->value == 0);
    for (std::size_t i = 0; i != handle_storage.size(); ++i) {
        assert(handle_storage[i] == (i >= 4 && i < 8 ? 0 : 0xa5));
    }
    alignas(th20::SoundEffectRequest) std::array<unsigned char, sizeof(th20::SoundEffectRequest)> request_storage;
    request_storage.fill(0xa5);
    auto* request = ::new(request_storage.data()) th20::SoundEffectRequest;
    for (auto byte : request_storage) assert(byte == 0);
    assert(request->id == 0 && request->count == 0);
    alignas(th20::SoundCommand) std::array<unsigned char, sizeof(th20::SoundCommand)> command_storage;
    command_storage.fill(0xa5);
    auto* command = ::new(command_storage.data()) th20::SoundCommand;
    for (auto byte : command_storage) assert(byte == 0);
    assert(command->type == 0 && command->argument == 0 && command->stage == 0);
    th20::SoundEffectChannel channel;
    assert(channel.buffer == nullptr && channel.definition == nullptr);
    assert(channel.cooldown == -1 && channel.id == 0 && channel.pan == 0 && channel.was_playing == 0);
    th20::WindowState window{}; // Explicit fixture, not native startup.
    window.current_time = 123.5;
    window.user_data_directory[200] = 'x';
    window.repeat[3].elapsed = 19;
    for (std::uint32_t flags : {0u, 1u, 2u, 0xffffffffu, 0x12345678u}) {
        for (std::uint32_t value : {0u, 1u, 2u, 3u, 0xffffffffu}) {
            window.flags.word = flags;
            assert(window.needs_device_reset() == ((flags >> 1) & 1));
            std::array<unsigned char, sizeof(window)> expected;
            std::memcpy(expected.data(), &window, sizeof(window));
            const auto updated = (flags & ~2u) | ((value & 1u) << 1);
            std::memcpy(expected.data() + offsetof(th20::WindowState, flags), &updated, sizeof(updated));
            window.set_device_reset(value);
            assert(window.flags.word == updated);
            assert(std::memcmp(expected.data(), &window, sizeof(window)) == 0);
        }
    }
    for (unsigned value = 0; value != 256; ++value) {
        const auto signed_value = std::bit_cast<std::int8_t>(static_cast<std::uint8_t>(value));
        window.set_draw_counter(signed_value);
        assert(window.draw_counter == signed_value);
    }
    for (std::uint32_t value : {0u, 10u, 0x80000000u, 0xffffffffu}) {
        window.set_reset_delay(value);
        assert(window.reset_delay == value);
    }
    for (std::int32_t value : {-1, 0, 2, 3, 8, 9}) {
        window.display_mode_value = value;
        assert(window.display_mode() == value);
    }
    assert(window.current_time == 123.5 && window.user_data_directory[200] == 'x');
    assert(window.repeat[3].elapsed == 19);
    for (std::int32_t value : {-1, 0, 8, 12, 15, 0x7fffffff}) {
        window.repeat[1] = {3, 4, 5};
        window.repeat[2].reset(value);
        assert(window.repeat[2].first == value && window.repeat[2].second == value);
        assert(window.repeat[2].elapsed == 0);
        assert(window.repeat[1].first == 3 && window.repeat[1].second == 4);
        assert(window.repeat[1].elapsed == 5 && window.repeat[3].elapsed == 19);
    }
    th20::InputButtonState query_input{};
    query_input.pressed = 0x80000001u;
    query_input.repeat8 = 2;
    query_input.repeat12 = 4;
    std::array<unsigned char, sizeof(query_input)> query_before;
    std::memcpy(query_before.data(), &query_input, sizeof(query_input));
    assert(query_input.pressed_bits(0xffffffffu) == 0x80000001u);
    assert(query_input.pressed_bits(0x80000000u) == 0x80000000u);
    assert(query_input.pressed_bits(0) == 0);
    assert(query_input.repeated_or_pressed(1) == 1);
    assert(query_input.repeated_or_pressed(2) == 1);
    assert(query_input.repeated_or_pressed(0x80000000u) == 1);
    assert(query_input.repeated_or_pressed(4) == 0); // repeat12 is excluded.
    assert(query_input.repeated_or_pressed(0) == 0);
    assert(std::memcmp(query_before.data(), &query_input, sizeof(query_input)) == 0);
    for (const std::uint32_t initial : {0u, 0xffffffffu, 0x12345678u, 0xffu, 0xffffff00u}) {
        alignas(th20::WindowFlags::Bits) std::array<unsigned char, 4> storage{};
        std::memcpy(storage.data(), &initial, sizeof(initial));
        auto* flags = ::new (storage.data()) th20::WindowFlags::Bits;
        std::uint32_t result;
        std::memcpy(&result, flags, sizeof(result));
        assert(result == (initial & ~0xffu));
        flags->~Bits();
    }

    th20::GameRandom game_random(3);
    assert(game_random.field_00 == 0 && game_random.minimum == 0 && game_random.upper == 0x00ffff00);
    assert(game_random.modulus == 0 && game_random.last == 0 && game_random.id == 3);
    assert(game_random.engine == th20::GameRandomEngine(1));
    for (std::uint32_t seed : {0u, 1u, 0x7fffffffu, 0xfffffffeu, 0xffffffffu}) {
        game_random.engine.seed(seed);
        const auto normalized = seed % 0x7fffffffu;
        assert(game_random.engine() == th20::random_step(normalized ? normalized : 1));
    }
    random_sample = 0xffffffff;
    random_sample_calls = 0;
    assert(game_random.bounded(0) == 0 && random_sample_calls == 0);
    for (std::uint32_t count : {1u, 2u, 7u, 0x80000000u, 0xffffffffu}) {
        const auto before = random_sample_calls;
        assert(game_random.bounded(count) == random_sample % count);
        assert(random_sample_calls == before + 1);
    }
    struct Sample { std::uint32_t numerator, modulus, unit_bits, signed_bits; };
    // Independently staged binary32 fixtures include rounding near 2^24,
    // high-bit unsigned conversion, and the observed non-clamped signed range.
    constexpr Sample samples[]{
        {0x00000000u, 0x00000004u, 0x00000000u, 0xbf800000u},
        {0x00000003u, 0x00000004u, 0x3f800000u, 0x40000000u},
        {0x00000001u, 0x00000003u, 0x3f000000u, 0x3f800000u},
        {0x7fffffffu, 0xffffffffu, 0x3f000000u, 0x00000000u},
        {0x80000001u, 0x7fffffffu, 0x3f800000u, 0x3f800000u},
        {0xfffffffeu, 0xffffffffu, 0x3f800000u, 0x3f800000u},
        {0x01000001u, 0x01000003u, 0x3f7ffffcu, 0x3f7ffffcu},
    };
    for (const auto sample : samples) {
        random_sample = sample.numerator;
        game_random.modulus = sample.modulus;
        const auto before = random_sample_calls;
        assert(std::bit_cast<std::uint32_t>(game_random.unit()) == sample.unit_bits);
        assert(std::bit_cast<std::uint32_t>(game_random.signed_unit()) == sample.signed_bits);
        assert(random_sample_calls == before + 2);
    }
    for (std::uint32_t bits : {0u, 0x80000000u, 0x3f800000u, 0x7f800000u, 0x7fc12345u}) {
        th20::ClockScalar scalar{2.0f};
        scalar.set(std::bit_cast<float>(bits));
        assert(std::bit_cast<std::uint32_t>(scalar.value) == bits);
    }

    const th20::InputBindings bindings;
    const std::array<std::int16_t, 24> expected_bindings{
        0, 1, 2, 3, -1, -1, -1, -1,
        0, 1, 5, 10, -1, -1, -1, -1,
        0x5a, 0x58, 0x10, 0x1b, 0x26, 0x28, 0x25, 0x27};
    std::array<std::int16_t, 24> stored_bindings{};
    std::memcpy(stored_bindings.data(), &bindings, sizeof(bindings));
    assert(stored_bindings == expected_bindings);
    const th20::InputBindingSlots empty_bindings;
    std::array<std::int16_t, 8> stored_slots{};
    std::memcpy(stored_slots.data(), &empty_bindings, sizeof(empty_bindings));
    assert((stored_slots == std::array<std::int16_t, 8>{}));
    for (const std::uint32_t initial : {0u, 0xffffffffu, 0x12345678u, 0x1ffu, 0xfffffe00u}) {
        alignas(th20::ConfigurationFlags) std::array<unsigned char, 4> storage{};
        std::memcpy(storage.data(), &initial, sizeof(initial));
        auto* options = ::new (storage.data()) th20::ConfigurationFlags;
        std::uint32_t result;
        std::memcpy(&result, options, sizeof(result));
        assert(result == ((initial & ~0x1ffu) | 0x80u));
        options->~ConfigurationFlags();
    }

    th20::InputButtonState buttons{};
    buttons.retained_118.fill(0x12345678);
    buttons.retained_218.fill(0x87654321);
    buttons.field_298 = buttons.replay_current = buttons.replay_previous = 0xaabbccdd;
    buttons.replay_repeat = buttons.replay_pressed = buttons.replay_released = 0xaabbccdd;
    buttons.retained_2b4 = 7;
    buttons.last_input_kind = 2;
    buttons.suppress_previous = 1;
    for (unsigned frame = 1; frame <= 60; ++frame) {
        buttons.previous = buttons.current;
        buttons.current = 0x80000001;
        buttons.update();
        assert(buttons.pressed == (frame == 1 ? 0x80000001u : 0));
        assert(buttons.released == 0);
        assert(buttons.repeat8 == (frame >= 26 && (frame - 26) % 8 == 0 ? 0x80000001u : 0));
        assert(buttons.repeat12 == (frame >= 26 && (frame - 26) % 12 == 0 ? 0x80000001u : 0));
        assert(buttons.held8 == (frame >= 8 ? 0x80000001u : 0));
        assert(buttons.held_frames[0] == frame && buttons.held_frames[31] == frame);
        assert(buttons.held_frames[15] == 0);
    }
    buttons.previous = buttons.current;
    buttons.current = 0;
    buttons.update();
    assert(buttons.released == 0x80000001 && buttons.pressed == 0);
    assert(buttons.repeat8_count[31] == 0 && buttons.repeat12_count[0] == 0);
    assert(buttons.held_frames[31] == 0 && buttons.held8 == 0);
    assert(buttons.retained_118[17] == 0x12345678 && buttons.retained_218[31] == 0x87654321);
    assert(buttons.replay_released == 0xaabbccdd && buttons.retained_2b4 == 7);
    assert(buttons.last_input_kind == 2 && buttons.suppress_previous == 1);
    buttons.current = 1;
    buttons.repeat8_count[0] = buttons.repeat12_count[0] = buttons.held_frames[0] = 0xffffffff;
    buttons.update();
    assert(buttons.repeat8_count[0] == 0 && buttons.repeat12_count[0] == 0);
    assert(buttons.held_frames[0] == 0 && buttons.held8 == 0);

    th20::InputDevice device{};
    device.buttons = buttons;
    device.raw.fill(0x85);
    device.retained_3d0 = 0xabcdef01;
    device.initialize_xinput(3, 7);
    assert(device.kind == 2 && device.xinput_index == 3 && device.logical_index == 7);
    device.initialize_keyboard(-1);
    assert(device.kind == 0 && device.logical_index == -1 && device.xinput_index == 3);
    device.reset_header();
    assert(device.kind == 0 && device.logical_index == 0);
    assert(device.direct_input == nullptr && device.xinput_index == 0);
    assert(std::memcmp(&device.buttons, &buttons, sizeof(buttons)) == 0);
    assert(device.raw[0] == 0x85 && device.raw[255] == 0x85);
    assert(device.retained_3d0 == 0xabcdef01);

    std::uint32_t mapped = 0x400;
    const std::uint8_t raw_buttons[]{0x7f, 0x80, 0xff};
    assert(th20::map_input_byte(&mapped, -1, 2, nullptr) == 0 && mapped == 0x400);
    assert(th20::map_input_byte(&mapped, 0, 2, raw_buttons) == 0 && mapped == 0x400);
    assert(th20::map_input_byte(&mapped, 1, 2, raw_buttons) == 2 && mapped == 0x402);
    assert(th20::map_input_byte(&mapped, 2, 8, raw_buttons) == 8 && mapped == 0x40a);

    assert(th20::archive_name_sum(nullptr, 0) == 0);
    const char name_bytes[]{'A', '\0', 'B', static_cast<char>(0x81), static_cast<char>(0xff)};
    assert(th20::archive_name_sum(name_bytes, 1) == 65);
    assert(th20::archive_name_sum(name_bytes, 3) == 131);
    assert(th20::archive_name_sum(name_bytes, 5) == 3);
    std::array<char, 256> all_bytes{};
    for (unsigned index = 0; index != all_bytes.size(); ++index)
        all_bytes[index] = static_cast<char>(index);
    assert(th20::archive_name_sum(all_bytes.data(), 256) == 128);

    // Independent division-based oracle, including states outside normal seeds.
    std::uint32_t sample = 0x81a7b393u;
    for (unsigned i = 0; i != 100000; ++i) {
        sample = sample * 1664525u + 1013904223u;
        const auto expected = static_cast<std::uint32_t>(
            (static_cast<std::uint64_t>(sample) * 48271u) % 2147483647u);
        assert(th20::random_step(sample) == expected);
    }
    assert(th20::random_step(0) == 0);
    assert(th20::random_step(2147483647u) == 0);
    assert(th20::random_step(0xffffffffu) == 48271u);
    th20::RandomState random{1};
    for (const auto value : {48271u, 182605794u, 1291394886u, 1914720637u}) {
        assert(random.next() == value);
        assert(random.state == value);
    }

    constexpr std::array<std::int32_t, 7> values = {
        std::numeric_limits<std::int32_t>::min(), -999999, -1, 0, 1,
        16777217, std::numeric_limits<std::int32_t>::max()};
    // Signed boundary comparisons read current only and preserve every byte.
    for (const auto current : values) {
        const th20::Timer timer = timer_fixture(-19, current, -0.0f, 0xabcdef01u);
        std::array<unsigned char, sizeof(timer)> before;
        std::memcpy(before.data(), &timer, sizeof(timer));
        assert(static_cast<std::int32_t>(timer) == current);
        for (const auto divisor : {3, 6, 12, -3}) {
            assert(timer % divisor == current % divisor);
        }
        for (const auto value : values) {
            assert(timer.at_least(value) == (current >= value));
            assert(timer.equals(value) == (current == value));
            assert(timer.less_than(value) == (current < value));
            assert(timer.greater_than(value) == (current > value));
            assert(std::memcmp(before.data(), &timer, sizeof(timer)) == 0);
        }
    }
    for (std::uint32_t flags = 0; flags != 256; ++flags) {
        th20::Timer timer = timer_fixture(12, 34, 56.0f, flags);
        timer.reset();
        assert(timer.previous == -999999 && timer.current == 0);
        assert(std::bit_cast<std::uint32_t>(timer.current_fraction) == 0);
        assert(timer.flags == flags);
        for (const auto mode : {0u, 1u, 2u, 3u, 4u, 0xffffffffu}) {
            timer.flags = flags;
            timer.set_mode(mode);
            assert((timer.flags & ~6u) == (flags & ~6u));
            assert(((timer.flags >> 1) & 3u) == (mode % 4u));
        }
        for (const auto value : values) {
            timer.flags = flags;
            timer.set(value);
            assert(timer.current == value);
            assert(static_cast<std::uint32_t>(timer.previous)
                   == static_cast<std::uint32_t>(value) - 1u);
            assert(timer.current_fraction == static_cast<float>(value));
            assert(timer.flags == ((flags & 1u) ? flags : ((flags & ~6u) | 1u)));
        }
    }

    assert(th20::timer_clock_sources[0] == &th20::default_timer_clock);
    assert(th20::default_timer_clock.value == 1.0f);
    th20::Timer stepping;
    stepping = 10;
    stepping += 7;
    assert(stepping.previous == 10 && stepping.current == 17);
    stepping -= 3;
    assert(stepping.previous == 17 && stepping.current == 14);
    stepping++;
    assert(stepping.previous == 14 && stepping.current == 15);
    stepping--;
    assert(stepping.previous == 15 && stepping.current == 14);
    th20::ClockScalar half{0.5f};
    th20::timer_clock_sources[0] = &half;
    th20::Timer fractional = timer_fixture(99, 17, 0.25f, 0xfffffff7u);
    assert(fractional.tick() == 0);
    assert(fractional.previous == 17 && fractional.current_fraction == 0.75f);
    assert(fractional.flags == 0xfffffff1u);
    assert(fractional.tick() == 1 && fractional.current_fraction == 1.25f);
    fractional.add(-0.5f);
    assert(fractional.previous == 1 && fractional.current == 1);
    assert(fractional.current_fraction == 1.0f);

    // Near-one paths advance the integer independently of the float value.
    th20::ClockScalar near_one{0.995f};
    th20::timer_clock_sources[0] = &near_one;
    th20::Timer independent = timer_fixture(0, 100, 2.25f, 1u);
    assert(independent.tick() == 101 && independent.current_fraction == 3.25f);
    independent.add(2.0f);
    assert(independent.current == 5 && independent.current_fraction == 5.25f);

    // Strict interval endpoints use scaling; null uses an unscaled step.
    for (float rate : {0.99f, 1.01f}) {
        th20::ClockScalar endpoint{rate};
        th20::timer_clock_sources[0] = &endpoint;
        th20::Timer timer = timer_fixture(0, 0, 0.0f, 1u);
        timer.add(100.0f);
        assert(timer.current_fraction == rate * 100.0f);
        assert(timer.current == (rate < 1.0f ? 99 : 101));
    }
    th20::timer_clock_sources[0] = nullptr;
    th20::Timer null_clock = timer_fixture(0, std::numeric_limits<std::int32_t>::max(), 4.25f, 1u);
    assert(null_clock.tick() == std::numeric_limits<std::int32_t>::min());
    assert(null_clock.current_fraction == 5.25f);
    th20::Timer uninitialized = timer_fixture(91, 71, 44.0f, 0xfffffffeu);
    assert(uninitialized.tick() == 1 && uninitialized.current_fraction == 1.0f);
    assert(uninitialized.previous == 0 && uninitialized.flags == 0xfffffff9u);
    th20::timer_clock_sources[0] = &th20::default_timer_clock;

    int context = 22;
    for (std::uint32_t flags = 0; flags != 256; ++flags) {
        th20::FunctionChainNode node{0, 0, nullptr, nullptr, nullptr,
                                    th20::FunctionChainLink{}, nullptr};
        th20::FunctionChainLink link{&node};
        assert(link.node == &node && link.next == nullptr && link.previous == nullptr);
        assert(link.owner == nullptr && link.iterator == nullptr);
        node.priority = -31;
        node.flags = flags;
        node.link.node = &node;
        node.link.next = &node.link;
        node.link.previous = &node.link;
        node.set_userdata(&context);
        node.set_before_insert(callback_b);
        node.set_shutdown_callback(callback_c);
        assert(node.before_insert == callback_b && node.on_shutdown == callback_c);
        node.set_callback(callback_a);
        assert(node.callback == callback_a && node.before_insert == nullptr && node.on_shutdown == nullptr);
        node.set_before_insert(callback_b);
        node.set_shutdown_callback(callback_c);
        node.clear_callbacks();
        assert(node.callback == nullptr && node.before_insert == nullptr && node.on_shutdown == nullptr);
        node.set_owned();
        assert(node.flags == (flags | 1u));
        node.enable();
        assert(node.flags == (flags | 3u));
        node.disable();
        assert(node.flags == ((flags | 1u) & ~2u));
        assert(node.priority == -31 && node.userdata == &context);
        assert(node.link.node == &node && node.link.next == &node.link && node.link.previous == &node.link);
    }
    assert(callback_calls == 0); // Setters never invoke or dispatch a callback.

    th20::FunctionChainLink first, middle, last;
    first.insert_after(&last);
    assert(first.next == &last && last.previous == &first && last.next == nullptr);
    last.insert_before(&middle);
    assert(first.next == &middle && middle.previous == &first);
    assert(middle.next == &last && last.previous == &middle);
    assert(first.previous == nullptr && last.next == nullptr);
    assert(middle.owner == nullptr && last.owner == nullptr);
    th20::FunctionChainLink before_first;
    first.insert_before(&before_first);
    assert(before_first.next == &first && first.previous == &before_first);
    assert(before_first.previous == nullptr);

    th20::LockRegistry registry;
    assert(!registry.enabled());
    std::array<unsigned char, sizeof(registry)> registry_before{}, registry_after{};
    std::memcpy(registry_before.data(), &registry, sizeof(registry));
    registry.enable();
    assert(registry.enabled());
    std::memcpy(registry_after.data(), &registry, sizeof(registry));
    unsigned changed = 0;
    for (std::size_t index = 0; index != registry_before.size(); ++index) {
        if (registry_before[index] != registry_after[index]) {
            ++changed;
            assert(registry_before[index] == 0 && registry_after[index] == 1);
        }
    }
    assert(changed == 1); // Locks, tracked depths and adjacent storage survive.
    registry.disable();
    assert(!registry.enabled());
    std::memcpy(registry_after.data(), &registry, sizeof(registry));
    assert(registry_before == registry_after);

    th20::TaskInfo task;
    assert(task.flags == 2 && task.update_node == nullptr && task.draw_node == nullptr);
    th20::TaskInfo* virtual_task = &task;
    virtual_task->enable();
    virtual_task->disable();
    th20::FunctionChainNode update{0, 0xffffffffu, callback_a, callback_b, callback_c,
                                  th20::FunctionChainLink{}, &context};
    th20::FunctionChainNode draw{0, 0x12345678u, callback_a, callback_b, callback_c,
                                th20::FunctionChainLink{}, &context};
    task.update_node = &update;
    virtual_task->disable();
    assert(update.flags == 0xfffffffdu && draw.flags == 0x12345678u);
    task.draw_node = &draw;
    virtual_task->enable();
    assert(update.flags == 0xffffffffu && draw.flags == 0x1234567au);
    task.update_node = nullptr;
    virtual_task->disable();
    assert(update.flags == 0xffffffffu && draw.flags == 0x12345678u);
    assert(task.flags == 2 && callback_calls == 0);
    assert(update.callback == callback_a && draw.userdata == &context);
}
