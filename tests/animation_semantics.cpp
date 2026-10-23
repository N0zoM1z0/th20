#include "Animation.hpp"
#include "AnimationCallback.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <new>
#include <memory_resource>
#include <thread>
#include <type_traits>
#include <vector>

namespace {
th20::Animation* releasing;
th20::AnimationCallback* expected_callback;
unsigned callback_calls;
struct LifetimeObserver final : th20::AnimationCallback {
    explicit LifetimeObserver(th20::Animation* a) : AnimationCallback(a) {}
    ~LifetimeObserver() override {
        assert(releasing && releasing->geometry == nullptr && releasing->geometry_bytes == 0);
        assert(releasing->callback == this && this == expected_callback);
        assert(releasing->handle.value == 0x12345678u && releasing->base.field_28 == 37);
        ++callback_calls;
    }
};
th20::AnimationCallback* owned_callback;

bool lock_available_to_another_thread() {
    bool available = false;
    std::thread observer([&] {
        auto& lock = th20::process_locks.slot(1);
        available = lock.try_lock();
        if (available) lock.unlock();
    });
    observer.join();
    return available;
}

struct StringResource final : std::pmr::memory_resource {
    struct Allocation {
        void* memory;
        std::size_t bytes, alignment;
        bool operator==(const Allocation&) const = default;
    };
    std::vector<Allocation> allocations, deallocations;
    bool cleared = false;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* result = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        allocations.push_back({result, bytes, alignment});
        return result;
    }
    void do_deallocate(void* memory, std::size_t bytes, std::size_t alignment) override {
        assert(cleared);
        Allocation released{memory, bytes, alignment};
        assert(std::find(allocations.begin(), allocations.end(), released) != allocations.end());
        assert(std::find(deallocations.begin(), deallocations.end(), released) == deallocations.end());
        deallocations.push_back(released);
        std::pmr::new_delete_resource()->deallocate(memory, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
StringResource* string_resource;
th20::AnimationFile* retiring_file;
unsigned retiring_filename_length;
unsigned clear_calls;
int next_array_index;
std::vector<int> retired_indices;

struct ArrayObserver final : th20::AnimationCallback {
    int index;
    th20::Animation* animation;
    ArrayObserver(th20::Animation* owner, int value)
        : AnimationCallback(owner), index(value), animation(owner) {}
    ~ArrayObserver() override {
        assert(index == next_array_index--);
        assert(animation->geometry == nullptr && animation->geometry_bytes == 0);
        assert(animation->callback == this && animation->handle.value == unsigned(index + 1));
        assert(animation->base.field_28 == 37);
        if (retired_indices.empty()) assert(!lock_available_to_another_thread());
        retired_indices.push_back(index);
    }
};

void check_file_and_template_lifetime(th20::DiagnosticAllocator& allocator) {
    using namespace th20;
    allocator.release_object(static_cast<AnimationFile*>(nullptr));
    for (unsigned length : {0u, 1u, 14u, 15u, 16u, 17u, 33u, 129u, 513u}) {
        StringResource resource;
        auto* previous = std::pmr::set_default_resource(&resource);
        auto* file = allocator.allocate_object<AnimationFile>("file lifetime fixture");
        std::pmr::set_default_resource(previous);
        assert(file && !file->bytes && !file->templates && !file->textures);
        file->filename.assign(length, 'f');
        file->stem.assign(length + 17, 's');
        void* filename = file->filename.data();
        void* stem = file->stem.data();
        std::vector<StringResource::Allocation> expected;
        for (void* data : {stem, filename}) {
            for (const auto& allocation : resource.allocations) {
                if (allocation.memory == data) expected.push_back(allocation);
            }
        }
        assert(expected.size() == resource.allocations.size());
        string_resource = &resource;
        retiring_file = file;
        retiring_filename_length = length;
        unsigned before = clear_calls;
        allocator.release_object(file);
        assert(clear_calls == before + 1);
        assert(resource.deallocations == expected);
        string_resource = nullptr;
        retiring_file = nullptr;
    }
    allocator.release_array(static_cast<Animation*>(nullptr));
    for (int count : {0, 1, 3, 17}) {
        Animation* values = allocator.allocate_array<Animation>("template lifetime fixture", count);
        retired_indices.clear();
        next_array_index = count - 1;
        for (int i = 0; i < count; ++i) {
            Animation& value = values[i];
            assert(value.link_4ec.node == &value && value.child_links[1].node == &value);
            assert(!value.geometry && !value.callback && value.handle.value == 0);
            value.handle = static_cast<unsigned>(i + 1);
            value.base.field_28 = 37;
            if (i & 1) {
                value.geometry = allocator.allocate_bytes(32 + i, "template geometry fixture");
                value.geometry_bytes = 32 + i;
            }
            new ArrayObserver(&value, i);
        }
        allocator.release_array(values);
        assert(next_array_index == -1 && retired_indices.size() == unsigned(count));
        for (int i = 0; i < count; ++i) assert(retired_indices[i] == count - i - 1);
    }
}

void check_descriptor_protocol(th20::DiagnosticAllocator& allocator) {
    using namespace th20;
    static_assert(std::is_trivially_copyable_v<SpriteData>);
    static_assert(std::is_trivially_destructible_v<SpriteData>);
    static_assert(std::is_trivially_destructible_v<TextureRecord>);
    static_assert(std::is_nothrow_constructible_v<SpriteData>);
    static_assert(std::is_nothrow_constructible_v<TextureRecord>);
    alignas(SpriteData) std::array<unsigned char,sizeof(SpriteData)> dirty;
    dirty.fill(0xa5);
    auto* initialized = new(dirty.data()) SpriteData;
    const std::array<unsigned char,sizeof(SpriteData)> zero{};
    assert(dirty == zero);
    initialized->~SpriteData();
    struct GuardedTexture {
        std::array<unsigned char,32> before;
        alignas(TextureRecord) std::array<unsigned char,sizeof(TextureRecord)> object;
        std::array<unsigned char,32> after;
    } guarded;
    std::memset(&guarded,0xa5,sizeof(guarded));
    auto* record = new(guarded.object.data()) TextureRecord;
    assert(!record->texture && !record->external_bytes && !record->header);
    assert(record->external_size == 0 && record->bytes_per_pixel == 0 && record->flags.bits == 0);
    for (auto b:guarded.before) assert(b == 0xa5);
    for (auto b:guarded.after) assert(b == 0xa5);
    record->~TextureRecord();
    for (int count:{0,1,7,31}) {
        auto* textures = allocator.allocate_array<TextureRecord>("texture records",count);
        auto* descriptors = allocator.allocate_array<SpriteData>("sprite records",count);
        auto** scripts = allocator.allocate_array<AnmInstruction*>("script table",count);
        std::array<std::array<std::uint8_t,16>,31> packet_storage{};
        for (int i=0;i<count;++i) {
            assert(!textures[i].texture && !textures[i].external_bytes && !textures[i].header);
            assert(textures[i].external_size == 0 && textures[i].bytes_per_pixel == 0 && textures[i].flags.bits == 0);
            assert(std::memcmp(&descriptors[i],zero.data(),zero.size()) == 0);
            // Only pointer transport is exercised; no packet object is read.
            scripts[i] = reinterpret_cast<AnmInstruction*>(packet_storage[i].data());
        }
        {
            AnimationFile view;
            view.scripts = scripts;
            view.script_count = static_cast<std::uint32_t>(count);
            for (int i=0;i<count;++i) assert(view.script(i) == scripts[i]);
            view.scripts = nullptr;
        }
        auto* image = static_cast<std::uint8_t*>(allocator.allocate_bytes(64,"external image"));
        std::memset(image,0x5a,64);
        if (count) {
            textures[0].external_bytes = image;
            textures[0].external_size = 64;
        }
        allocator.release_array(textures);
        allocator.release_array(descriptors);
        allocator.release_array(scripts);
        // Native array deletion does not retire an external image payload.
        for (unsigned i=0;i<64;++i) assert(image[i] == 0x5a);
        allocator.release_bytes(image);
    }
    allocator.release_array(static_cast<TextureRecord*>(nullptr));
    allocator.release_array(static_cast<SpriteData*>(nullptr));
    allocator.release_array(static_cast<AnmInstruction**>(nullptr));

    AnimationFile file;
    for (std::uint32_t id:{0u,1u,41u,0x00ffffffu,0x80000000u,0xffffffffu}) {
        file.id = id;
        for (std::uint32_t index:{0u,1u,255u,256u,0x10000u,0x80000000u,0xffffffffu}) {
            auto expected = static_cast<std::uint32_t>(std::uint64_t(id)*256u) | index;
            assert(file.texture_id(index) == expected);
        }
    }
    file.id = 29;
    auto* slots = allocator.allocate_array<SpriteData>("guarded sprite window",7);
    file.sprites = slots+3;
    file.sprite_count = 7;
    using SlotImage = std::array<unsigned char,7*sizeof(SpriteData)>;
    using FileImage = std::array<unsigned char,sizeof(AnimationFile)>;
    for (unsigned seed=0;seed<64;++seed) {
        const int x = int((seed*3)%17)-8, y = int((seed*7)%19)-9;
        const int width = int(seed%9)+1, height = int(seed%7)+1;
        const int sx = 1 << (seed%3), sy = 1 << ((seed/3)%3);
        const int x_exp = 5+int(seed%4), y_exp = 5+int((seed/4)%4);
        SpriteData source;
        source.file_id = file.id;
        source.texture_index = seed;
        source.texture_id = (file.id*256u) | seed;
        source.left = float(x*sx); source.right = float((x+width)*sx);
        source.top = float(y*sy); source.bottom = float((y+height)*sy);
        source.extent_20 = float(1 << x_exp); source.extent_1c = float(1 << y_exp);
        source.scale_50 = float(sx); source.scale_54 = float(sy);
        source.field_24 = std::bit_cast<float>(0x7fc00000u | seed);
        source.field_28 = -float(seed+1); source.field_2c = float(seed*2);
        source.field_30 = -0.0f; source.field_34 = float(seed+17);
        source.u0 = 17; source.u1 = 19; source.v0 = 23; source.v1 = 29;
        source.extent_48 = 31; source.extent_4c = 37;
        // The independent oracle starts with unscaled integer dimensions.
        SpriteData expected = source;
        expected.u0 = std::ldexp(float(x*sx),-x_exp);
        expected.u1 = std::ldexp(float((x+width)*sx),-x_exp);
        expected.v0 = std::ldexp(float(y*sy),-y_exp);
        expected.v1 = std::ldexp(float((y+height)*sy),-y_exp);
        expected.extent_4c = float(width); expected.extent_48 = float(height);
        std::array<unsigned char,sizeof(SpriteData)> source_before;
        std::memcpy(source_before.data(),&source,sizeof(source));
        for (int index:{-3,-1,0,2,3}) {
            for (bool self_alias:{false,true}) {
                auto* bytes = reinterpret_cast<unsigned char*>(slots);
                std::fill_n(bytes,7*sizeof(SpriteData),0xa5);
                if (self_alias) file.sprites[index] = source;
                SlotImage wanted;
                std::memcpy(wanted.data(),slots,wanted.size());
                std::memcpy(wanted.data()+(index+3)*sizeof(SpriteData),&expected,sizeof(expected));
                FileImage owner_before;
                std::memcpy(owner_before.data(),&file,sizeof(file));
                file.store_sprite(index,self_alias?file.sprites[index]:source);
                assert(std::memcmp(wanted.data(),slots,wanted.size()) == 0);
                assert(std::memcmp(owner_before.data(),&file,sizeof(file)) == 0);
                assert(std::memcmp(source_before.data(),&source,sizeof(source)) == 0);
            }
        }
    }
    file.sprites = nullptr;
    allocator.release_array(slots);
}

template<class T> void check_padding(const T& object, std::size_t first,
                                    std::size_t end) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&object);
    for (std::size_t i = first; i < end; ++i) assert(bytes[i] == 0xa5);
}

template<class T> void stopped_only(th20::Interpolation<T>& value) {
    value.timer.set(19);
    value.duration = 73;
    value.mode = 91;
}

template<class T> void retained_sample(const th20::Interpolation<T>& value) {
    assert(value.duration == 0 && value.mode == 91);
    assert(value.timer.current == 19);
}

std::vector<std::size_t> retired_pool_slots;
struct PoolObserver final : th20::AnimationCallback {
    std::size_t slot;
    th20::Animation* animation;
    PoolObserver(th20::Animation* owner, std::size_t index)
        : AnimationCallback(owner), slot(index), animation(owner) {}
    ~PoolObserver() override {
        assert(animation->geometry == nullptr && animation->geometry_bytes == 0);
        assert(animation->callback == this && animation->handle.value == slot + 1);
        assert(animation->base.field_28 == 37);
        if (retired_pool_slots.empty()) assert(lock_available_to_another_thread());
        retired_pool_slots.push_back(slot);
    }
};

void check_pool_lifetime() {
    using namespace th20;
    static_assert(AnimationPool::capacity == 65536);
    static_assert(std::is_nothrow_default_constructible_v<AnimationPool>);
    static_assert(std::is_nothrow_destructible_v<AnimationPool>);
    static_assert(!std::is_nothrow_default_constructible_v<PooledAnimation>);
    void* memory = ::operator new(sizeof(AnimationPool));
    std::memset(memory, 0xa5, sizeof(AnimationPool));
    auto* pool = ::new (memory) AnimationPool;
    for (std::size_t i = 0; i < AnimationPool::capacity; ++i) {
        auto& slot = pool->records[i];
        auto& animation = slot.animation;
        assert(!slot.active && !slot.index && !slot.free_link.node);
        assert(!slot.free_link.next && !slot.free_link.previous);
        assert(!slot.free_link.owner && !slot.free_link.iterator);
        assert(!animation.geometry && !animation.callback && !animation.handle.value);
        for (auto* link : {&animation.link_4ec, &animation.link_500,
                          &animation.child_links[0], &animation.child_links[1], &animation.link_53c}) {
            assert(link->node == &animation && !link->next && !link->previous);
            assert(!link->owner && !link->iterator);
        }
    }
    for (std::size_t i : {std::size_t{0}, std::size_t{32768}, std::size_t{65535}}) {
        const auto& slot = pool->records[i];
        check_padding(slot, offsetof(PooledAnimation, active) + sizeof(slot.active),
                      offsetof(PooledAnimation, index));
    }
    const std::array<std::size_t, 5> selected{0, 1, 32768, 65534, 65535};
    retired_pool_slots.clear();
    retired_pool_slots.reserve(selected.size());
    for (std::size_t i : selected) {
        auto& animation = pool->records[i].animation;
        assert(animation.allocate_geometry(32) && animation.geometry_bytes == 32);
        animation.handle.value = static_cast<std::uint32_t>(i + 1);
        animation.base.field_28 = 37;
        animation.callback = new PoolObserver(&animation, i);
    }
    pool->~AnimationPool();
    assert(std::equal(retired_pool_slots.begin(), retired_pool_slots.end(),
                      selected.rbegin(), selected.rend()));
    ::operator delete(memory);
}
}

namespace th20 {
// Owned host allocator startup fixture. Real virtual destruction observes
// callback release order; process startup remains undefined in production.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
// Logical identity value for portable execution only. This does not reconstruct
// the native constant's production initialization or accept a data unit.
const Matrix4 identity_matrix = [] {
    Matrix4 value;
    for (int i = 0; i < 4; ++i) value.elements[i][i] = 1.0f;
    return value;
}();
// The native clear early exit is exercised only with no loaded resources.
// Renderer-mediated detachment and loaded-buffer retirement remain external.
void AnimationFile::clear() {
    assert(!bytes && !templates && !sprites && !scripts && !textures);
    if (!string_resource) { assert(this != retiring_file); return; }
    assert(this == retiring_file);
    assert(!string_resource->cleared && string_resource->deallocations.empty());
    assert(filename.size() == retiring_filename_length);
    assert(stem.size() == retiring_filename_length + 17);
    assert(lock_available_to_another_thread());
    string_resource->cleared = true;
    ++clear_calls;
}
}

int main(int argc, char**) {
    using namespace th20;
    static_assert(std::is_nothrow_constructible_v<AnimationBase>);
    static_assert(std::is_nothrow_constructible_v<Animation>);
    static_assert(std::is_nothrow_destructible_v<Animation>);
    static_assert(!std::is_trivially_destructible_v<Animation>);
    DiagnosticAllocator allocator;
    process_allocator = &allocator;
    if (argc > 1) {
        Animation looping;
        looping.field_550 = 1;
        looping.release_resources();
        return 2; // The native nonzero-word path must not return.
    }
    check_file_and_template_lifetime(allocator);
    check_descriptor_protocol(allocator);
    check_pool_lifetime();

    alignas(PooledAnimation) std::array<unsigned char, sizeof(PooledAnimation)> storage;
    storage.fill(0xa5);
    auto* pooled = ::new (storage.data()) PooledAnimation;
    Animation& a = pooled->animation;
    assert(a.base.timer.current == 0 && a.handle.value == 0 && a.index == 0);
    assert(a.geometry == nullptr && a.callback == nullptr && a.geometry_bytes == 0);
    assert(a.parent_558 == nullptr && a.parent_55c == nullptr);
    for (auto* link : {&a.link_4ec, &a.link_500, &a.child_links[0], &a.child_links[1], &a.link_53c}) {
        assert(link->node == &a && link->next == nullptr && link->previous == nullptr);
        assert(link->owner == nullptr && link->iterator == nullptr);
    }
    assert(pooled->free_link.node == nullptr && pooled->free_link.next == nullptr);
    assert(pooled->free_link.previous == nullptr && pooled->free_link.owner == nullptr);
    assert(pooled->free_link.iterator == nullptr && pooled->active == 0 && pooled->index == 0);
    check_padding(a.base, offsetof(AnimationBase, field_440) + sizeof(a.base.field_440),
                  offsetof(AnimationBase, variables));
    check_padding(a, offsetof(Animation, field_579) + sizeof(a.field_579),
                  offsetof(Animation, matrix_57c));
    check_padding(*pooled, offsetof(PooledAnimation, active) + sizeof(pooled->active),
                  offsetof(PooledAnimation, index));
    assert(a.base.interpolation_1b4.current.value == 0.0f);
    for (const auto& row : a.base.matrix_3b8.elements)
        for (float value : row) assert(value == 0.0f);

    Animation parent, grandparent;
    a.base.vector_50 = {2.0f, -3.0f};
    a.base.vector_70 = {5.0f, 7.0f};
    parent.base.vector_50 = {4.0f, 6.0f};
    grandparent.base.vector_50 = {-0.5f, 2.0f};
    a.parent_558 = &parent;
    a.parent_55c = &grandparent; // Only +558 participates in scale inheritance.
    parent.parent_558 = &grandparent;
    assert(a.width() == -20.0f && a.height() == -252.0f);
    parent.base.flags.word_04 = 0x1000u;
    assert(a.width() == 40.0f && a.height() == -126.0f);
    a.base.flags.word_04 = 0x1000u;
    assert(a.width() == 10.0f && a.height() == -21.0f);
    a.base.vector_50.x = -0.0f;
    assert(std::signbit(a.width()));
    a.base.vector_50.y = std::numeric_limits<float>::quiet_NaN();
    assert(std::isnan(a.height()));
    a.position_ref().z = 23.0f;
    assert(a.base.vector_2c.z == 23.0f);

    // Dirty reset verifies retained state and ownership, not just default values.
    a.base.timer.set(31);
    a.base.field_28 = 37;
    a.base.field_10 = 123;
    a.base.variables.field_00 = 51;
    a.base.variables.field_34 = -7.0f;
    a.base.variables.field_38 = -9.0f;
    a.base.variables.field_3c = -1;
    a.base.color_494 = 0xabcdef12u;
    a.base.vector_398 = {71.0f, 72.0f};
    a.base.vectors_378[3] = {11.0f, 12.0f};
    a.base.matrix_3f8.elements[1][2] = 13.0f;
    a.matrix_57c.elements[2][1] = 14.0f;
    a.base.vector_484 = {1.0f, 2.0f, 3.0f};
    a.base.vector_80 = {4.0f, 5.0f, 6.0f};
    a.base.field_78 = a.base.field_7c = 17.0f;
    a.timer_4c8.set(42);
    a.timer_4d8.set(43);
    a.field_570 = 9;
    a.field_574 = 81;
    std::memset(&a.base.flags, 0xff, sizeof(a.base.flags));
    stopped_only(a.base.interpolation_8c);
    stopped_only(a.base.interpolation_e0);
    stopped_only(a.base.interpolation_134);
    stopped_only(a.base.interpolation_160);
    stopped_only(a.base.interpolation_1b4);
    stopped_only(a.base.interpolation_1e0);
    stopped_only(a.base.interpolation_220);
    stopped_only(a.base.interpolation_260);
    stopped_only(a.base.interpolation_2a0);
    stopped_only(a.base.interpolation_2f4);
    stopped_only(a.base.interpolation_320);
    stopped_only(a.base.interpolation_34c);
    a.geometry = allocator.allocate_bytes(64, "animation test");
    a.geometry_bytes = 64;
    owned_callback = new LifetimeObserver(&a);
    a.handle = 0x12345678u;
    a.reset();
    assert(callback_calls == 0 && a.geometry != nullptr && a.geometry_bytes == 64);
    assert(a.callback == owned_callback);
    assert(a.handle.value == 0x12345678u && a.base.timer.current == 31);
    assert(a.base.field_28 == 37 && a.base.field_10 == 123);
    assert(a.base.variables.field_00 == 51 && a.base.variables.field_34 == 1.0f);
    assert(std::bit_cast<std::uint32_t>(a.base.variables.field_38) == 0x40490fdbu);
    assert(a.base.variables.field_3c == 65536 && a.base.color_490 == 0xffffffffu);
    assert(a.base.color_494 == 0xabcdef12u && a.field_570 == 0 && a.field_574 == 81);
    assert(a.parent_558 == nullptr && a.parent_55c == nullptr);
    assert(a.timer_4c8.current == 0 && a.timer_4d8.current == 0);
    assert(a.base.vector_2c.z == 0 && a.base.vector_484.y == 0 && a.base.vector_80.x == 0);
    assert(a.base.vector_50.x == 1 && a.base.vector_50.y == 1);
    assert(a.base.vector_58.x == 1 && a.base.vector_68.y == 1);
    assert(a.base.vector_60.x == 0 && a.base.vector_70.y == 0);
    assert(a.base.field_78 == 0 && a.base.field_7c == 0);
    assert(a.base.vector_398.x == 71 && a.base.vectors_378[3].y == 12);
    assert(a.base.matrix_3f8.elements[1][2] == 13 && a.matrix_57c.elements[2][1] == 14);
    const auto* flag_bytes = reinterpret_cast<const unsigned char*>(&a.base.flags);
    for (unsigned i = 0; i < sizeof(a.base.flags); ++i)
        assert(flag_bytes[i] == ((i == 2 || i == 4 || i == 8) ? 1 : 0));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            assert(a.base.matrix_3b8.elements[i][j] == (i == j ? 1.0f : 0.0f));
    retained_sample(a.base.interpolation_8c);
    retained_sample(a.base.interpolation_e0);
    retained_sample(a.base.interpolation_134);
    retained_sample(a.base.interpolation_160);
    retained_sample(a.base.interpolation_1b4);
    retained_sample(a.base.interpolation_1e0);
    retained_sample(a.base.interpolation_220);
    retained_sample(a.base.interpolation_260);
    retained_sample(a.base.interpolation_2a0);
    retained_sample(a.base.interpolation_2f4);
    retained_sample(a.base.interpolation_320);
    retained_sample(a.base.interpolation_34c);

    expected_callback = a.callback;
    releasing = &a;
    a.release_resources();
    releasing = nullptr;
    assert(callback_calls == 1 && a.callback == nullptr && a.handle.value == 0);
    assert(a.base.field_28 == -1 && a.base.field_10 == 123);
    assert(a.link_4ec.node == &a && a.base.timer.current == 31);
    pooled->~PooledAnimation();
    assert(callback_calls == 1); // Null callback cleanup performs no virtual destruction.
}
