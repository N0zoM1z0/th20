// Exercise the maintained LaserController::reset_all_lasers() against actual
// typed Laser and intrusive-iterator owners. Only upstream TaskInfo startup,
// native Laser destructor and ECL diagnostic are fixture boundaries.
#include "LaserParameters.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace th20 {
Laser::~Laser() = default; // Fixture-only: native destructor and heap owner are separate.
LaserController::~LaserController() = default;
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() {}
void TaskInfo::disable() {}
void ecl_diagnostic_hint(const char*, ...) {}
}

namespace {
using namespace th20;
struct TestLaser final : Laser {
    enum Action { Keep, RemoveSelf, RemoveNext, Throw };
    LaserController& controller;
    std::vector<int>& visits;
    int id;
    Action action;
    unsigned calls = 0;
    TestLaser(LaserController& c, std::vector<int>& v, int n, Action a)
        : controller(c), visits(v), id(n), action(a) {
        link.initialize(this);
        field_6cc = static_cast<std::uint32_t>(9000 + n);
        timer_6ac.flags = (id & 1) ? 5u : 0u;
        timer_6ac.current = 97;
        timer_6ac.current_fraction = 123.0f;
        timer_6ac.previous = 128;
    }
    void set_position(const Vector3&) override {}
    void point_at_distance(float, Vector3&) override {}
    void set_parameter_flag(std::uint32_t) override {}
#define EMPTY_SLOT(S) void slot_##S() override {}
    EMPTY_SLOT(08)
    EMPTY_SLOT(10) EMPTY_SLOT(14) EMPTY_SLOT(18)
    EMPTY_SLOT(24) EMPTY_SLOT(28)
    EMPTY_SLOT(34) EMPTY_SLOT(38) EMPTY_SLOT(3c) EMPTY_SLOT(40)
    EMPTY_SLOT(50) EMPTY_SLOT(54) EMPTY_SLOT(58) EMPTY_SLOT(5c)
    EMPTY_SLOT(60) EMPTY_SLOT(64) EMPTY_SLOT(68) EMPTY_SLOT(6c)
    EMPTY_SLOT(70) EMPTY_SLOT(74) EMPTY_SLOT(78) EMPTY_SLOT(7c)
    EMPTY_SLOT(80)
#undef EMPTY_SLOT
    std::int32_t update() override { return 0; }
    std::int32_t draw() override { return 0; }
    std::int32_t cancel_rectangle(const Vector3&, const Vector3&,
                                  float, std::int32_t, std::int32_t) override {return 0;}
    std::int32_t cancel_circle(const Vector3&, float,
                               std::int32_t, std::int32_t) override {return 0;}
    std::int32_t proximity(const Vector3&, float) override {return 0;}
    std::int32_t cancel_all(std::int32_t) override {return 0;}
    std::int32_t erase(std::int32_t first, std::int32_t second) override {
        assert(first == 1 && second == 0);
        assert(timer_6ac.current == 0 && timer_6ac.previous == -1);
        assert(timer_6ac.current_fraction == 0.0f);
        assert(timer_6ac.flags == ((id & 1) ? 5u : 1u));
        assert(field_6cc == 0);
        visits.push_back(id);
        ++calls;
        if (action == Throw) throw std::runtime_error("laser erase boundary");
        if (action == RemoveSelf) controller.active.remove(&link);
        if (action == RemoveNext && link.next) controller.active.remove(link.next);
        return 123;
    }
};

void exercise(int seed, TestLaser::Action action) {
    LaserController controller;
    std::vector<int> visits;
    std::array<std::unique_ptr<TestLaser>,3> l;
    for (int i=0;i<3;++i) {
        const auto member_action = i==0 ? action : TestLaser::Keep;
        l[static_cast<std::size_t>(i)]=std::make_unique<TestLaser>(controller,visits,i+1,member_action);
        controller.active.append(&l[static_cast<std::size_t>(i)]->link);
    }
    controller.count = static_cast<std::uint32_t>(seed + 8);
    bool threw=false;
    try {
        assert(controller.reset_all_lasers() == 0);
    } catch (const std::runtime_error&) {threw=true;}
    assert(threw == (action == TestLaser::Throw));
    switch(action) {
    case TestLaser::Keep: assert((visits == std::vector<int>{1,2,3}));break;
    case TestLaser::RemoveSelf: assert((visits == std::vector<int>{1,2,3}));break;
    case TestLaser::RemoveNext: assert((visits == std::vector<int>{1,3}));break;
    case TestLaser::Throw: assert((visits == std::vector<int>{1}));break;
    }
    assert(controller.count == static_cast<std::uint32_t>(seed + 8));
    for (const auto& p:l) {
        assert(p->link.iterator == nullptr);
        if (p->link.owner) controller.active.remove(&p->link);
        assert(p->link.owner == nullptr);
    }
    assert(controller.active.front() == nullptr);
}
}

int main() {
    using namespace th20;
    {
        LaserController empty;
        assert(empty.reset_all_lasers() == 0);
        assert(empty.active.front() == nullptr);
        assert(empty.active.tail == &empty.active);
    }
    unsigned cases=1;
    for (int repeat=0;repeat<150;++repeat)
    for (auto action : {TestLaser::Keep, TestLaser::RemoveSelf,
                        TestLaser::RemoveNext, TestLaser::Throw}) {
        exercise(repeat,action);
        ++cases;
    }
    std::cout << "LaserController reset_all_lasers real typed owner/iterator scenarios: "
              << cases << '/' << cases << " passed\n";
}
