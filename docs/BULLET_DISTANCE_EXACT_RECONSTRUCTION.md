# CORE/EXACT-228 — complete 122-byte original Bullet radial distance predicate

Original immutable Japanese TH20 v1.00a Steamless PE SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire native 122-byte function `0x00485A60..0x00485AD9`
(original function interval SHA-256
`0ed9429239c9122d0d960b7f4a4ae81c1a79b0c3260c25ba523ab76c50f987a5`)
is now `th20::bullet_distance_within(const Vector3&, const Vector3&, float)`
in `src/BulletDistance.cpp`. Original spelling remains inferred.
This complete function is the real distance-predicate callee at `0x0047D1D7`
inside the separately exact **320-byte** radial BulletController cancellation
boss, not an invented helper.

The original method constructs a real 12-byte `Vector3`, subtracts the two
supplied 3-lane position vectors through the original game-owned
`Vector3::operator-` at `0x00429440`, and computes **XY-only squared distance**
through the original `th20::squared_norm_xy(const Vector3&)` at `0x00456130`.
It compares that squared distance to the original `radius * radius` with
native `comiss` and ordered/NaN behavior. Its native return is a **full-EAX
32-bit integer zero or one**, a detail confirmed independently by the real
`BulletController::cancel_near` caller. It is not safe to follow Ghidra's
inferred AL-only `bool` return for this ABI.

The natural source
`Vector3 delta; delta = first - second; return squared_norm_xy(delta) <=
radius * radius;` compiled using locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc`. Full strict replay verifies
**122/122 exact native bytes**, including all **five** original relocation
fields: native security cookie `0x005B25C0`, Vector3 default constructor
`0x00422E10`, Vector3 subtraction `0x00429440`, XY squared norm
`0x00456130`, and security check `0x005429EE`. Non-relocation code is
**102/102 original bytes**.

A separate small typed interface `src/BulletDistance.hpp` replaces the
previous private forward declaration in `src/BulletSpatialCancellation.cpp`.
That entire **320-byte parent** is freshly rebuilt and retains full
**320/320** strict byte and relocation identity. Both complete affected units
replay exactly: **2/2 across two freshly compiled MSVC objects**, with no
other source/header include dependents and no whole-graph cold replay.
Focused proof: `.analysis/core228-bullet-distance-and-radial-scope-replay.log`.

The genuine 662-byte `Bullet::cancel` downstream of the 320B controller
and the native 3,735-byte Bullet emitter and 41,967-byte Enemy ECL boss
remain open original-function targets. A successful scoped exact replay
is not a full-game native link or runtime completeness claim.
