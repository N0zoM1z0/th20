# CORE/RECON-952 — original 51B particle-grid virtual event and folded 26B Timer call ABI frontier (NOT exact)

Locked Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045D060` is a genuine **51B/18-i386** virtual event
method, physically attached to slot 4 of the six-entry original
`0x0056EC14` particle-grid vtable. Its ABI and behavior are verified,
but **a single ODR-correct C++ source matching its genuine folded call
AND the independently accepted 172B group constructor has not been
proven**. This report deliberately creates **no canonical match unit,
no game exact-byte credit and no source-present mapping** for this event.

## Real original code and physical addresses

[`scripts/verify-animation-particle-grid-event51-native.py`](../scripts/verify-animation-particle-grid-event51-native.py)
reads only the original PE and checks the complete 51B/18-i386 function,
real `ret 4`, original vtable slot/physical PE relocation, **one genuine
E8 instruction `+0x25 -> 0x0045C300`**, zero HIGHLOW, event==1, native
Timer member offset `+0x1930`, literal delta 300 and native NOP. The
**26B** original physical `0x0045C300` body itself calls the actual
`Timer::operator+=(int)` at `0x004297A0` and has its own original NOP.
That physical 26B wrapper was already independently whole-exact under
the original `PlayerFeedback::operator+=(int)` source (possible native
COMDAT folding); it must **not** be counted twice.

The original [172B particle-grid constructor](ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md)
contains E8 **`+0x9D -> 0x00422D90`**, the *actual* original
`Timer::Timer()` constructor. This separate original call target is the
critical constraint that disallows simply replacing the group's Timer
with a new subclass and relabeling its constructor in the manifest.

## Rejected natural C++ hypotheses and exact regression blocker

Complete isolated pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` probes were performed:

| Candidate | Whole event code | Why it is not canonical |
| --- | --- | --- |
| Direct `timer_1930 += 300` using real `Timer` | **51B/18 i386; 47/47 nonrelocated bytes** | COFF E8 points to `Timer::operator+=(int)` original `0x004297A0`, **not** native wrapper `0x0045C300` |
| Member cast to a separate Timer-derived ABI view | **57B** | Adds an original-absent saved pointer and wrong stack frame |
| Replace actual group member with `struct NativeGridTimedDelta : Timer` and define forwarding `operator+=` | **51B/18 event**, plus independently structural-exact **26B** wrapper | Ordinary derived construction changes the whole original **172B** group ctor to **194B**, invalidating prior acceptance |
| Add explicit `__forceinline` derived default constructor | **51B event and 172B group body structurally exact**, factory remains 156B | The group ctor's actual E8 relocation now references the newly generated **23B `NativeGridTimedDelta()` wrapper**, not original **54B `Timer::Timer()` at `0x00422D90`**; manifest target identity cannot be falsified |

These are real source experiments, not artificial instruction padding or
modified target bytes. The source, derived-view header, and two
rejected-input hashes were retained under ignored
`.analysis/gptweb-grid-event51-20261031/rejected-derived-layout/`.
Their full object contributions remain available at
`build/gptweb-grid-event51-20261031/` for independent review.

After the contradiction was confirmed, the authoritative
[`src/NativeParticleGridGroup.hpp`](../src/NativeParticleGridGroup.hpp)
was restored byte-for-byte from the saved pre-experiment class declaration;
the separate unaccepted `src/AnimationParticleGridEvent51.cpp` was
preserved privately and withdrawn, rather than leaving a duplicate
physical method or unreviewed shared header change. All **eight existing
strict particle-grid units across six affected source providers** were
cold rebuilt and **8/8 remained exact**, including the entire 172B ctor,
49B deleting wrapper, 156B factory, two 78B arrays, 47B create,
31B Timer configuration and 92B stop. No global replay ran.

This establishes a useful original **folded-function identity and
constructor ABI constraint**, not exact source admission. The larger
virtual update at original vtable slot 1 `0x0045C360` also remains
outside this scoped proof. Exact game totals are unchanged by this
frontier record.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-event51-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridArrays200.cpp --source src/AnimationParticleGridGroupCtor172.cpp --source src/AnimationParticleGridGroupFactory156.cpp --source src/AnimationParticleGridConfig31.cpp --source src/AnimationParticleGridCreate47.cpp --source src/AnimationParticleGridStop92.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
