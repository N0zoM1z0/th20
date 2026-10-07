#include "EclRuntime.hpp"

#include <array>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <memory_resource>
#include <type_traits>
#include <unordered_map>

namespace th20 {
// Unclosed boundaries are never executed by this lifetime test.
std::int32_t EclLoader::callback_0(std::uint32_t) { std::abort(); }
int ScriptStack::pop(std::int32_t, void*, char) { std::abort(); }
}

namespace {
class Resource final : public std::pmr::memory_resource {
public:
    struct Block { std::size_t bytes, alignment; };
    std::unordered_map<void*, Block> live;
    unsigned allocations = 0, releases = 0;
private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        auto* pointer = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        assert(live.emplace(pointer, Block{bytes, alignment}).second);
        ++allocations;
        return pointer;
    }
    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override {
        const auto block = live.find(pointer);
        assert(block != live.end());
        assert(block->second.bytes == bytes && block->second.alignment == alignment);
        live.erase(block);
        ++releases;
        std::pmr::new_delete_resource()->deallocate(pointer, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

struct DefaultResource {
    std::pmr::memory_resource* previous;
    explicit DefaultResource(Resource& resource)
        : previous(std::pmr::set_default_resource(&resource)) {}
    ~DefaultResource() { std::pmr::set_default_resource(previous); }
};

// Only the unresolved derived include behavior is a fixture. Base initialization
// and cleanup use the maintained bodies, including virtual deletion through base.
class IncludeFixture final : public th20::EclLoader {
public:
    bool& destroyed;
    std::uint8_t* seen = nullptr;
    explicit IncludeFixture(bool& flag) : destroyed(flag) {}
    ~IncludeFixture() override { destroyed = true; }
    std::int32_t include_resources(std::uint8_t* block) override {
        seen = block;
        return -1;
    }
};
}

int main() {
    static_assert(std::is_nothrow_constructible_v<th20::ScriptStack>);
    Resource original, replacement;
    DefaultResource restore(original);
    std::array<std::uint8_t, 32> borrowed{};
    borrowed[0] = 0xA5;
    bool destroyed = false;
    auto derived = std::make_unique<IncludeFixture>(destroyed);
    auto* observed = derived.get();
    std::unique_ptr<th20::EclLoader> loader = std::move(derived);
    assert(original.allocations == 0);
    assert(loader->file_count == 0 && loader->subroutine_count == 0);
    for (auto* file : loader->files) assert(file == nullptr);
    for (auto field : loader->fields_10c) assert(field == 0);
    assert(loader->records.empty() && loader->globals.words.empty());
    assert(loader->globals.pointer == 0 && loader->globals.frame_base == 0);
    assert(loader->records.get_allocator().resource() == &original);
    assert(loader->globals.words.get_allocator().resource() == &original);

    std::pmr::set_default_resource(&replacement);
    loader->files[0] = borrowed.data();
    loader->records.push_back({"owned fixture", borrowed.data()});
    loader->globals.reset();
    loader->globals.words.push_back(0x12345678);
    assert(original.allocations == 2 && original.live.size() == 2);
    assert(replacement.allocations == 0);
    assert(loader->include_resources(borrowed.data()) == -1);
    assert(observed->seen == borrowed.data());
    assert(loader->th20::EclLoader::include_resources(borrowed.data()) == 0);
    assert(loader->th20::EclLoader::include_resources(nullptr) == 0);
    loader.reset();
    assert(destroyed && original.live.empty());
    assert(original.releases == original.allocations);
    assert(replacement.live.empty() && replacement.releases == 0);
    assert(borrowed[0] == 0xA5);
}
