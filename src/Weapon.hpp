#pragma once
#include "Timer.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include <cstddef>
namespace th20 {
struct PlayerOption;
// Native storage and table slot order are observed. Names and uncalled
// virtual prototypes remain inferred; original gameplay definitions stay open.
class Weapon {
public:
    virtual void reset();
    virtual void initialize_main();
    virtual void shoot_main(int,int,int);
    virtual void shoot_focused(int,int,int);
    virtual void shoot_unfocused(int,int,int);
    virtual const Vector2* focused_offset(int,int);
    virtual const Vector2* unfocused_offset(int,int);
    virtual void activate_main();
    virtual void activate_focused();
    virtual void activate_unfocused();
    virtual void initialize_focused_option(PlayerOption*,int);
    virtual void initialize_unfocused_option(PlayerOption*,int);
    virtual void update_focused_option(PlayerOption*,int);
    virtual void update_unfocused_option(PlayerOption*,int);
    virtual void initialize_passive();
    virtual void update_main();
    virtual void update_focused();
    virtual void update_unfocused();
    virtual void update_passive();
    virtual int script_variant();
    virtual void start_phase();
    virtual int update_phase();
    virtual int end_phase();
    virtual int cancel_phase();
    virtual const Vector3* phase_position();
    virtual int shot_script_index();
    virtual bool phase_active();
    virtual bool unfocused_shooting();
    virtual bool focused_shooting();
    virtual bool passive_active();
    std::int32_t stone_id,field_08,role;
    std::uint32_t field_10;
    Timer timer_14,timer_24;
    std::uint8_t active,passive;
    Weapon() noexcept;
    ~Weapon();
    void set_passive(std::uint8_t value);
};
#if defined(_M_IX86)
static_assert(sizeof(Weapon)==0x38);
static_assert(offsetof(Weapon,timer_14)==0x14);
static_assert(offsetof(Weapon,timer_24)==0x24);
static_assert(offsetof(Weapon,active)==0x34);
static_assert(offsetof(Weapon,passive)==0x35);
#endif

}
