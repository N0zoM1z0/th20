#include "EclFileLoader.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "ClockScalar.hpp"
#include <array>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <memory_resource>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
class Resource final : public std::pmr::memory_resource {
public:
    struct Block { std::size_t size, alignment; };
    std::unordered_map<void*, Block> live;
    unsigned attempts = 0, fail_at = 0;
private:
    void* do_allocate(std::size_t size, std::size_t alignment) override {
        if (++attempts == fail_at) throw std::bad_alloc();
        auto* pointer = std::pmr::new_delete_resource()->allocate(size, alignment);
        assert(live.emplace(pointer, Block{size, alignment}).second);
        return pointer;
    }
    void do_deallocate(void* pointer, std::size_t size, std::size_t alignment) override {
        auto record = live.find(pointer);
        assert(record != live.end());
        assert(record->second.size == size && record->second.alignment == alignment);
        live.erase(record);
        std::pmr::new_delete_resource()->deallocate(pointer, size, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
} resource;
std::array<std::uint8_t, 64> first_buffer{}, second_buffer{};
std::uint8_t* read_result = first_buffer.data();
unsigned reads = 0, appends = 0, paths = 0;
std::vector<std::string> events;
std::function<int(th20::EclLoader*, std::uint8_t*)> append_hook;
bool fail_cache_node = false;
std::size_t blocks_at_read = 0;
}

namespace th20 {
// These fixtures supply unresolved enclosing startup and dependency bodies.
// The actual file loader, base resource lifetime and Context getter are linked.
EnemyController::EnemyController() noexcept : field_124(0), player_index(0), context(nullptr) {}
EnemyController::~EnemyController() = default;
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { std::abort(); }
int ScriptStack::pop(int, void*, char) { std::abort(); }
int EclFileLoader::include_resources(std::uint8_t*) { std::abort(); }
const char ecl_duplicate_file_format[] = "%s is skiped.\n";
const char ecl_cached_file_format[] = "%s was loaded in 1P.\n";
std::pmr::list<EclCachedFile> process_ecl_cache{&resource};
const char* ecl_resource_path(const char* path) {
    ++paths; events.emplace_back("path:"); return path;
}
std::uint8_t* read_game_resource(const char* path, std::int32_t* size, std::int32_t mode) {
    assert(size == nullptr && mode == 0);
    ++reads; events.emplace_back(path);
    blocks_at_read = resource.live.size();
    if (fail_cache_node) resource.fail_at = resource.attempts + 2;
    return read_result;
}
int EclLoader::append(std::uint8_t* buffer) {
    ++appends;
    assert(append_hook);
    return append_hook(this, buffer);
}
}

int main() {
    using namespace th20;
    auto* previous = std::pmr::set_default_resource(&resource);
    {
        EnemyController first, second;
        Context first_context, second_context;
        first_context.enemies = &first; second_context.enemies = &second;
        EclFileLoader first_loader, second_loader;
        assert(first_loader.player_index == 0 && first_loader.context == nullptr);
        assert(second_loader.file_count == 0 && second_loader.records.empty());
        first_loader.context = &first_context; second_loader.context = &second_context;
        EclLoader* virtual_loader = &first_loader;
        const char* root = "owned-root-script-long.ecl";
        append_hook = [&](EclLoader* loader, std::uint8_t* buffer) {
            assert(loader == &first_loader && buffer == first_buffer.data());
            assert(first.loaded_names.size() == 1 && first.loaded_names[0] == root);
            assert(process_ecl_cache.size() == 1 && process_ecl_cache.front().first == buffer);
            assert(virtual_loader->load(root) == -1); // Include cycle already marked.
            return 7; // Every nonnegative append result becomes load success.
        };
        assert(virtual_loader->load(root) == 0);
        assert(reads == 1 && paths == 1 && appends == 1);
        assert(virtual_loader->load(root) == -1);
        assert(reads == 1 && appends == 1);
        append_hook = [&](EclLoader* loader, std::uint8_t* buffer) {
            assert(loader == &second_loader && buffer == first_buffer.data());
            assert(second.loaded_names.size() == 1 && second.loaded_names[0] == root);
            return 0;
        };
        assert(second_loader.load(root) == 0);
        assert(reads == 1 && paths == 1 && appends == 2 && process_ecl_cache.size() == 1);

        read_result = second_buffer.data();
        append_hook = [&](EclLoader*, std::uint8_t* buffer) {
            assert(buffer == second_buffer.data()); return -9;
        };
        assert(first_loader.load("Owned-Root-script-long.ecl") == -1);
        assert(first.loaded_names.size() == 2 && process_ecl_cache.size() == 2);
        assert(reads == 2 && appends == 3);
        assert(first_loader.load("Owned-Root-script-long.ecl") == -1);
        assert(reads == 2 && appends == 3); // Failed append keeps registration/cache.
    }
    process_ecl_cache.clear();
    assert(resource.live.empty());
    assert(first_buffer[0] == 0 && second_buffer[0] == 0);

    {
        EnemyController controller;
        Context context;
        context.enemies = &controller;
        EclFileLoader loader;
        loader.context = &context;
        resource.fail_at = resource.attempts + 1;
        bool failed = false;
        try { loader.load("owned-first-temporary-allocation-failure.ecl"); }
        catch (const std::bad_alloc&) { failed = true; }
        assert(failed && controller.loaded_names.empty() && process_ecl_cache.empty());
        assert(reads == 2 && appends == 3 && resource.live.empty());
        resource.fail_at = 0;
        fail_cache_node = true;
        failed = false;
        try { loader.load("owned-cache-node-allocation-failure.ecl"); }
        catch (const std::bad_alloc&) { failed = true; }
        assert(failed && process_ecl_cache.empty() && controller.loaded_names.size() == 1);
        assert(resource.live.size() == blocks_at_read); // Pair temporary string unwound.
        assert(reads == 3 && appends == 3);
        resource.fail_at = 0;
        assert(loader.load("owned-cache-node-allocation-failure.ecl") == -1);
        assert(reads == 3 && appends == 3);
    }
    assert(resource.live.empty());
    std::pmr::set_default_resource(previous);
}
