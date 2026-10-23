#include "TextLine.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <tuple>

namespace {
th20::AsciiInf* constructing;
th20::AsciiInf* previous_ascii;
bool fail_diagnostic;
bool diagnostic_seen;
unsigned base_destructions, enables, disables;
}

namespace th20 {
// Process startup and the native AsciiInf resource lifecycle remain external.
// Construction uses the real values, Animation, Worker and standard containers.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
AnimationFile* shared_text_animation_file;
TaskInfo::~TaskInfo() { ++base_destructions; }
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { ++disables; }
AsciiInf::~AsciiInf() = default;
void AsciiInf::enable() { ++enables; }
void ecl_diagnostic_hint(const char* format, ...) {
    assert(!std::strcmp(format, "initialize AsciiInf\n"));
    assert(current_ascii == previous_ascii);
    assert(constructing->flags == 2 && constructing->line_count == 0);
    assert(constructing->font_width == 9 && constructing->font == 0);
    assert(constructing->animation_file == nullptr);
    assert(constructing->pending_tasks.empty());
    assert(dynamic_cast<AsciiInf*>(static_cast<TaskInfo*>(constructing)) == constructing);
    diagnostic_seen = true;
    if (fail_diagnostic) throw std::runtime_error("Captured diagnostic failure");
}
// Only unloaded real File values are used for borrowed resource identities.
void AnimationFile::clear() {
    assert(!bytes && !templates && !sprites && !scripts && !textures);
}
}

namespace {
void check_values(th20::AsciiInf& ascii) {
    using namespace th20;
    assert(ascii.flags == 2 && !ascii.update_node && !ascii.draw_node);
    const std::array<Animation*, 3> animations{
        &ascii.animation_10, &ascii.animation_5f4, &ascii.animation_bd8};
    for (auto* animation : animations) {
        assert(!animation->handle.value && !animation->geometry && !animation->callback);
        assert(animation->link_4ec.node == animation && animation->link_500.node == animation);
        assert(animation->child_links.nodes[0].node == animation);
        assert(animation->child_links.nodes[1].node == animation);
        assert(!animation->parent_558 && !animation->parent_55c);
        assert(!animation->field_550 && !animation->base.flags.word_04);
    }
    // Independent complete 320-byte record model: all state is zero except
    // the two alignment defaults. Check every record, including the last one.
    std::array<unsigned char, sizeof(TextLine)> expected{};
    const std::uint32_t one = 1;
    std::memcpy(expected.data() + offsetof(TextLine, align_x), &one, sizeof(one));
    std::memcpy(expected.data() + offsetof(TextLine, align_y), &one, sizeof(one));
    for (const auto& line : ascii.lines) {
        assert(!std::memcmp(&line, expected.data(), expected.size()));
    }
    assert(ascii.line_count == 0 && ascii.color == 0xFFFFFFFFu);
    assert(ascii.shadow_color == 0xFF000000u && ascii.field_1a1c8 == 0xFFFFFFFFu);
    assert(ascii.scale_x == 1.0f && ascii.scale_y == 1.0f);
    const auto zeros = std::tie(ascii.field_1a1d4, ascii.field_1a1d8, ascii.shadow,
        ascii.font, ascii.field_1a1e8, ascii.layer, ascii.frames, ascii.blend,
        ascii.texture_size.x, ascii.texture_size.y, ascii.field_1a240);
    std::apply([](const auto&... value) { assert(((value == 0) && ...)); }, zeros);
    assert(ascii.field_1a1e4 == 2 && ascii.align_x == 1 && ascii.align_y == 1);
    assert(static_cast<float>(ascii.rotation) == 0.0f && ascii.font_width == 9);
    assert(ascii.jobs.node == nullptr && ascii.jobs.previous == nullptr);
    assert(ascii.jobs.next == nullptr && ascii.jobs.owner == nullptr);
    assert(ascii.jobs.iterator == nullptr && ascii.jobs.tail == &ascii.jobs);
    assert(ascii.pending_tasks.empty() && !ascii.animation_file);
    assert(!ascii.animation_handle.value && !ascii.loading_handle.value);
    assert(!ascii.draw_node_1a250 && !ascii.draw_node_1a254);
    assert(!ascii.draw_node_1a258 && !ascii.draw_node_1a25c);
    assert(std::all_of(std::begin(ascii.text_buffer), std::end(ascii.text_buffer),
                       [](char value) { return value == 0; }));
}
}

int main(int argc, char**) {
    using namespace th20;
    static_assert(std::is_nothrow_constructible_v<TextLine>);
    static_assert(std::is_nothrow_constructible_v<std::array<TextLine, 320>>);
    static_assert(std::is_nothrow_constructible_v<AsciiInf>);
    DiagnosticAllocator allocator;
    process_allocator = &allocator;
    alignas(AsciiInf) std::array<unsigned char, sizeof(AsciiInf)> prior_storage{};
    constructing = reinterpret_cast<AsciiInf*>(prior_storage.data());
    previous_ascii = nullptr;
    auto* prior = ::new (prior_storage.data()) AsciiInf;
    if (argc > 1) {
        alignas(AsciiInf) std::array<unsigned char, sizeof(AsciiInf)> storage{};
        constructing = reinterpret_cast<AsciiInf*>(storage.data());
        previous_ascii = prior;
        diagnostic_seen = false;
        fail_diagnostic = true;
        std::set_terminate([] {
            std::_Exit(diagnostic_seen && th20::current_ascii == previous_ascii ? 42 : 43);
        });
        ::new (storage.data()) AsciiInf;
        return 44;
    }
    AnimationFile shared_file, instance_file;
    alignas(AsciiInf) std::array<unsigned char, sizeof(AsciiInf) + 64> storage;
    unsigned selected_files = 0;
    for (unsigned pattern = 0; pattern != 256; ++pattern) {
        storage.fill(static_cast<unsigned char>(pattern));
        constructing = reinterpret_cast<AsciiInf*>(storage.data() + 32);
        previous_ascii = pattern & 1u ? prior : nullptr;
        current_ascii = previous_ascii;
        diagnostic_seen = false;
        auto* ascii = ::new (storage.data() + 32) AsciiInf;
        assert(diagnostic_seen && current_ascii == ascii);
        check_values(*ascii);
        assert(std::all_of(storage.begin(), storage.begin() + 32,
                           [&](unsigned char byte) { return byte == pattern; }));
        assert(std::all_of(storage.end() - 32, storage.end(),
                           [&](unsigned char byte) { return byte == pattern; }));
        ascii->animation_file = &instance_file;
        for (auto* file : {static_cast<AnimationFile*>(nullptr), &shared_file, &instance_file}) {
            shared_text_animation_file = file;
            assert(ascii->text_animation_file() == file && prior->text_animation_file() == file);
            assert(ascii->animation_file == &instance_file);
            ++selected_files;
        }
        auto token = std::make_shared<int>(0);
        ascii->pending_tasks.push_back([token] { ++*token; });
        ascii->pending_tasks.push_back([token] { *token *= 7; });
        for (auto& task : ascii->pending_tasks) task();
        assert(*token == 7 && token.use_count() == 3);
        auto* base = static_cast<TaskInfo*>(ascii);
        const auto old_enables = enables, old_disables = disables;
        base->enable(); base->disable();
        assert(enables == old_enables + 1 && disables == old_disables + 1);
        const auto old_destructions = base_destructions;
        ascii->~AsciiInf();
        assert(base_destructions == old_destructions + 1 && token.use_count() == 1);
        current_ascii = prior;
    }
    prior->~AsciiInf();
    current_ascii = nullptr;
    shared_text_animation_file = nullptr;
    std::cout << "AsciiInf: 256 dirty constructions, 81920 TextLines, "
              << selected_files << " shared-file selections passed\n";
}
