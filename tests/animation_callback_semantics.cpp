#include "Animation.hpp"
#include "AnimationCallback.hpp"
#include "Bullet.hpp"
#include "BulletStyle.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <thread>

namespace th20 {
// Full controller destruction/enable remain external; this fixture never owns one.
BulletController::~BulletController() { std::abort(); }
void BulletController::enable() { std::abort(); }
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
BulletStyle bullet_styles[50];
const Matrix4 identity_matrix = [] {
    Matrix4 value;
    for (int i=0;i<4;++i) value.elements[i][i]=1.0f;
    return value;
}();
}
namespace {
using namespace th20;
std::size_t cases;
struct Observer final : AnimationCallback {
    std::int32_t seen = 0;
    std::int32_t incoming = 0;
    unsigned calls = 0;
    bool* destroyed;
    bool check_release = false;
    Observer(Animation* a, bool* d) : AnimationCallback(a), destroyed(d) {}
    std::int32_t update() override { return -7; }
    std::int32_t draw() override { return 19; }
    std::int32_t slot_0c() override { return -31; }
    std::int32_t interrupt(std::int32_t event) override {
        seen=animation->base.field_438;
        incoming=event;
        ++calls;
        animation->base.field_438=0x1234;
        return std::numeric_limits<std::int32_t>::min();
    }
    ~Observer() override {
        if (check_release) {
            assert(animation->geometry==nullptr && animation->geometry_bytes==0);
            assert(animation->callback==this && animation->handle.value==0x12345678u);
            assert(animation->base.field_28==37);
            bool available=false;
            std::thread other([&] {
                auto& mutex=process_locks.slot(1);
                available=mutex.try_lock();
                if (available) mutex.unlock();
            });
            other.join();
            assert(available);
        }
        *destroyed=true;
    }
};
std::int32_t hit(Animation* a) { a->base.field_438=-97; return -9; }
std::int32_t script(Animation* a, std::int32_t value) {
    a->base.field_438=value;
    return value;
}
template<class T> auto image(const T& value) {
    std::array<unsigned char,sizeof(T)> out;
    std::memcpy(out.data(),&value,sizeof(T));
    return out;
}
template<class T, std::size_t N> void replace(std::array<unsigned char,N>& bytes,
                                            std::size_t offset, const T& value) {
    std::memcpy(bytes.data()+offset,&value,sizeof(T));
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;
    process_allocator=&allocator;
    Animation a;
    {
        AnimationCallback callback(&a);
        assert(callback.animation==&a && a.callback==&callback);
        assert(callback.update()==0 && callback.draw()==0 && callback.slot_0c()==0);
        for (auto event : {0,1,-1,256,-256,INT32_MIN,INT32_MAX}) {
            assert(callback.interrupt(event)==0);
            a.base.field_438=79;
            a.interrupt(event);
            assert(a.base.field_438==event);
            ++cases;
        }
        auto before=image(a);
        assert(a.set_callback(nullptr)==nullptr);
        replace(before,offsetof(Animation,callback),static_cast<AnimationCallback*>(nullptr));
        assert(image(a)==before);
        ++cases;
    }
    bool destroyed=false;
    {
        Observer callback(&a,&destroyed);
        AnimationCallback* base=&callback;
        assert(base->update()==-7 && base->draw()==19 && base->slot_0c()==-31);
        for (auto event : {0,1,-1,256,-256,INT32_MIN,INT32_MAX}) {
            a.base.field_438=-83;
            auto expected=image(a);
            a.interrupt(event);
            replace(expected,offsetof(Animation,base)+offsetof(AnimationBase,field_438),event);
            assert(image(a)==expected);
            assert(callback.seen==-83 && callback.incoming==event);
            ++cases;
        }
        assert(callback.calls==7);
        a.set_callback(nullptr);
    }
    assert(destroyed);
    for (auto event : {0,1,-1,256,-256,INT32_MIN,INT32_MAX}) {
        auto expected=image(a);
        a.interrupt(event);
        replace(expected,offsetof(Animation,base)+offsetof(AnimationBase,field_438),event);
        assert(image(a)==expected);
        ++cases;
    }
    a.set_field_5dc(hit); a.set_field_5e0(script);
    assert(a.field_5dc(&a)==-9 && a.base.field_438==-97);
    for (auto value : {0,1,-1,256,-256,INT32_MIN,INT32_MAX}) {
        assert(a.field_5e0(&a,value)==value && a.base.field_438==value);
        ++cases;
    }
    a.clear_pending_fields();
    assert(!a.field_5dc && !a.field_5e0);
    ++cases;
    Bullet bullet;
    for (std::uint32_t bits=0;bits<65536;++bits) {
        auto expected=std::bit_cast<std::int16_t>(static_cast<std::uint16_t>(bits));
        bullet.field_4c=expected; bullet.field_4e=expected;
        assert(bullet.type()==static_cast<std::int32_t>(expected));
        assert(bullet.color_index()==static_cast<std::int32_t>(expected));
        cases+=2;
    }
    a.user_data=&bullet;
    for (unsigned seed=0;seed<4;++seed) {
        for (int type=0;type<50;++type) {
            bullet.field_4c=static_cast<std::int16_t>(type);
            auto& style=bullet_styles[type];
            for (int color=0;color<16;++color)
                for (int index=0;index<5;++index)
                    style.colors[color].words[index]=0x80000000u+seed*7919u+type*8191u+color*521u+index*31u;
            style.colors[0].words[0]=seed*12345u;
            for (int color=0;color<16;++color) {
                bullet.field_4e=static_cast<std::int16_t>(color);
                for (int index=0;index<5;++index) {
                    auto animation_before=image(a);
                    auto bullet_before=image(bullet);
                    auto style_before=image(style);
                    auto result=bullet_animation_script(&a,index);
                    assert(result==std::bit_cast<std::int32_t>(style.colors[color].words[index]));
                    assert(image(a)==animation_before && image(bullet)==bullet_before && image(style)==style_before);
                    ++cases;
                }
            }
            for (auto sentinel : {0x80000000u,0xffffffffu}) {
                style.colors[0].words[0]=sentinel;
                // The negative sentinel bypasses both unchecked color and word indexes.
                bullet.field_4e=INT16_MIN;
                for (auto index : {0,1,-1,256,-256,INT32_MIN,INT32_MAX}) {
                    assert(bullet_animation_script(&a,index)==index);
                    ++cases;
                }
            }
        }
    }
    destroyed=false;
    auto* owned=new Observer(&a,&destroyed);
    owned->check_release=true;
    a.geometry=allocator.allocate_bytes(64,"callback lifetime fixture");
    a.geometry_bytes=64;
    a.handle=0x12345678u;
    a.base.field_28=37;
    a.release_resources();
    assert(destroyed && a.callback==nullptr && a.handle.value==0 && a.base.field_28==-1);
    a.release_resources();
    allocator.release_object(static_cast<AnimationCallback*>(nullptr));
    ++cases;
    std::cout << "PASS " << cases << " callback owner, virtual ABI, release order and signed script cases\n";
}
