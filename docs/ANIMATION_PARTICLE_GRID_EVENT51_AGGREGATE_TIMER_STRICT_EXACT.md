# CORE/RECON-1108 — whole 51B particle-grid event and the real aggregate Timer ABI

**WHOLE STRICT EXACT:** The immutable Japanese TH20 Steamless v1.00a
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains a complete **51B /18-i386** particle-grid virtual event at
`0x0045D060..0x0045D092`, native body SHA-256
`37e9d7d0695daa98eab8d5f10b120d932d7192c8727c03cf404fe0990a67e0e4`.
Vtable `0x0056EC14` slot 4 physically points to this event method.
The sole real native E8 at **opcode `+0x25`**, COFF field **`+0x26`**,
targets original `0x0045C300`; no in-body HIGHLOW fields exist.
The event has native `ret 4`, contains the original post-call NOP and
returns zero after handling event 1 by advancing the Timer at
`NativeParticleGridGroup+0x1930` by **300**.

## Resolving the previous event/constructor contradiction

The previous [folded Timer frontier](ANIMATION_PARTICLE_GRID_EVENT51_FOLDED_TIMER_ABI_FRONTIER.md)
correctly rejected ordinary `Timer += 300`, which emitted this event's
51B instructions but called `Timer::operator+=(int)` at **`0x004297A0`**
*directly*, rather than the original folded **26B forwarding helper**
`0x0045C300`. It also rejected a derived Timer that changed the already
independently exact 172B particle-grid constructor. That constructor
has original E8 **`+0x9D -> 0x00422D90`**, the genuine
`Timer::Timer()` constructor; replacing it with a derived-type
constructor changes original relocation identity.

The natural maintained solution uses a **16B standard aggregate** with a
real `Timer` member at offset zero:

```cpp
struct NativeGridTimedDelta {
    Timer time;
    void operator+=(std::int32_t amount) { time += amount; }
};
```

The original group Timer remains at offset **`+0x1930`**. Crucially, the
maintained group constructor value-initializes this aggregate with
**`timer_1930{}`** (braces), so locked MSVC directly calls the existing
`Timer::Timer()` member. Parentheses `timer_1930()` instead generate a
non-native additional constructor wrapper and produce a **194B**
constructor. Under braces, the real **172B/46-i386** group constructor
remains strict exact, preserving its original E8 target and all other
nine original relocation roles. The other group owners are unchanged.

For the 51B event, a real source `switch(event)` (not a shortened `if`
with different compiler lowering) invokes `NativeGridTimedDelta::operator+=`
on event 1. The compiler emits the complete original **51B/18-i386**
body and its genuinely used forwarding helper is itself
**26B/12-i386**, **22/22** nonrelocation bytes matching original
`0x0045C300`. That helper's single original E8 targets
`0x004297A0` (`Timer::operator+=(int)`) at opcode `+0x0E`.
The physical 26B helper was already canonically exact under the folded
`PlayerFeedback::operator+=(int)` source; its potential source-owner
alias does **not** add new authored code credit. The maintained wrapper
name is a source hypothesis, not an assertion that the original binary
stores a second copy of the 26B method.

## Complete native comparison and affected exact scope

| Full native function | Original source-independent body | Pinned MSVC C++20 result |
| --- | --- | --- |
| Particle-grid event | 51B/18 instructions, E8 target `0x0045C300` | **51/51 whole relocated exact**, 47/47 ordinary bytes |
| Group constructor | 172B/46 instructions, real Timer E8 `0x00422D90` | **172/172 whole relocated exact** |
| Folded forwarding leaf | 26B/12 instructions, original E8 `0x004297A0` | 22/22 ordinary bytes, **already** separately canonical under another owner |

Pinned compiler profile: MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`. Source:
[`AnimationParticleGridEvent51.cpp`](../src/AnimationParticleGridEvent51.cpp),
[`NativeParticleGridGroup.hpp`](../src/NativeParticleGridGroup.hpp),
and [`AnimationParticleGridGroupCtor172.cpp`](../src/AnimationParticleGridGroupCtor172.cpp).
The full 51B function's original physical E8 and vtable pointer were
independently checked by
[`verify-animation-particle-grid-event51-native.py`](../scripts/verify-animation-particle-grid-event51-native.py)
before creating the canonical relocation entry; no target fields were
solved from the candidate.

The header and Timer constructor source change affected precisely **eight
previously exact units across six compiler objects**. All **8/8** were
cold-rebuilt and whole-relocation replayed successfully: both 78B array
constructors, the 172B group constructor, 49B deleting wrapper, 156B
factory, 47B create, 31B Timer config, and 92B Stop. The new 51B event
was then separately compiled and strictly replayed as its own unit.
The maintained **2,884B virtual Update** source was also independently
compiled; it remains **2,969B/763-i386, 99 REL32/25 DIR32, NONEXACT**.
None of that unfinished parent is credited from exact event, ctor or
leaf descendants. No full-graph cold replay was run.

Focused reproduction:

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationParticleGridArrays200.cpp \
  --source src/AnimationParticleGridGroupCtor172.cpp \
  --source src/AnimationParticleGridGroupFactory156.cpp \
  --source src/AnimationParticleGridCreate47.cpp \
  --source src/AnimationParticleGridConfig31.cpp \
  --source src/AnimationParticleGridStop92.cpp \
  --source src/AnimationParticleGridEvent51.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_particle_grid_event_51
```
