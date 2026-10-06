#include "ReplayRecords.hpp"
#include "ProgressRecords.hpp"
#include "InputState.hpp"
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <new>

void check_replay_records() {
    for (unsigned pattern : {0u, 0x55u, 0xa5u, 0xffu}) {
        alignas(th20::ReplayFileHeader) unsigned char header[sizeof(th20::ReplayFileHeader)];
        std::memset(header, pattern, sizeof(header));
        const auto* value = ::new(header) th20::ReplayFileHeader;
        assert(value->magic == 0x72303274 && value->version == 1);
        assert(value->field_10 == 0x100 && value->header_size == 0);
        for (unsigned i = 0; i < sizeof(header); ++i)
            if (i >= 9 && i < 12) assert(header[i] == pattern);
            else if (i > 4 && !(i == 16 || i == 17)) assert(header[i] == 0);
        alignas(th20::ProgressScore) unsigned char score[sizeof(th20::ProgressScore)];
        std::memset(score, pattern, sizeof(score));
        const auto* s = ::new(score) th20::ProgressScore;
        assert(s->score == 0 && s->timestamp == 0 && s->slowdown == 0);
        for (unsigned i = 0; i < sizeof(score); ++i)
            assert(score[i] == ((i >= 20 && i < 24) || i >= 36 ? pattern : 0));
        alignas(th20::PracticeScore) unsigned char practice[sizeof(th20::PracticeScore)];
        std::memset(practice, pattern, sizeof(practice));
        ::new(practice) th20::PracticeScore;
        for (unsigned i = 0; i < sizeof(practice); ++i)
            assert(practice[i] == (i >= 12 ? pattern : 0));
        th20::ProgressRecordHeader prefix;
        assert(prefix.magic == 0 && prefix.version == 0 && prefix.checksum == 0 && prefix.size == 0);
    }
    th20::PracticeScore practice;
    practice.score = 0x123456789;
    practice.field_0a[0] = 0xa5;
    practice.field_0a[1] = 0x5a;
    for (int first = -128; first <= 127; ++first) {
        for (int second = -128; second <= 127; ++second) {
            practice.field_08 = static_cast<std::int8_t>(first);
            practice.field_09 = static_cast<std::int8_t>(second);
            unsigned char before[sizeof(practice)];
            std::memcpy(before, &practice, sizeof(practice));
            assert(practice.available() == (first != 0 || second != 0));
            assert(std::memcmp(before, &practice, sizeof(practice)) == 0);
        }
    }
    for (unsigned selected = 0; selected < 32; ++selected) {
        th20::InputButtonState input{};
        input.current = input.previous = 0xabcdef01;
        input.repeat8_count.fill(77);
        input.repeat12_count.fill(88);
        input.held_frames.fill(99);
        input.last_input_kind = 2;
        input.suppress_previous = 1;
        input.held8 = 0xffffffff;
        input.reset_replay();
        const auto reset = input;
        const unsigned bit = 1u << selected;
        for (unsigned frame = 1; frame <= 80; ++frame) {
            input.replay_previous = input.replay_current;
            input.replay_current = bit;
            input.update_replay();
            assert(input.replay_pressed == (frame == 1 ? bit : 0));
            assert(input.replay_released == 0);
            assert(input.replay_repeat == (frame >= 26 && (frame - 26) % 8 == 0 ? bit : 0));
            assert(input.retained_2b4 == (frame >= 8 ? bit : 0));
            assert(input.retained_218[selected] == frame);
        }
        input.replay_previous = bit;
        input.replay_current = 0;
        input.update_replay();
        assert(input.replay_released == bit && input.replay_pressed == 0);
        assert(input.retained_118 == reset.retained_118 && input.retained_218 == reset.retained_218);
        input.reset_replay();
        assert(std::memcmp(&input, &reset, sizeof(input)) == 0);
        input.replay_current = bit;
        input.retained_118[selected] = input.retained_218[selected] = std::numeric_limits<unsigned>::max();
        input.update_replay();
        assert(input.retained_118[selected] == 0 && input.retained_218[selected] == 0);
        assert(input.replay_repeat == 0 && input.retained_2b4 == 0);
    }
}
