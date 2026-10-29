# CORE/RECON-800 — the original entire 5,993B Animation draw Boss now has one maintained 49-mode typed C++ parent source (NONEXACT)

Original immutable target: Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint moves the genuine **`0x00443880` `AnimationPoolOwner::draw(Animation*)`**
from **SOURCE-ABSENT** to **SOURCE-PRESENT `reconstructed`, NONEXACT**.
It is a substantive original 49-case and 31-nested-case C++ method with its
actual original game/Graphics/Animation types and direct call roles, not
merely a disassembly dump, jump-table note, source-only documentation or an
object-file stub. However **none of its 5,993 original .text bytes is newly
strict-matched**: its complete proposed compiled function remains different
from the original. This is **not** a whole-program link or game playability
claim.

## Independently locked original function and actual mode routing

The source-independent [original PE verifier](../scripts/verify-animation-draw-boss-native.py)
reads the true original `0x00443880..0x00444FE8` **5,993B /1,501 x86**
function, all **123 original direct E8 instruction sites /43 distinct
actual physical destinations**, all **32 in-function IMAGE_REL_BASED_HIGHLOW**
fields, all **49 +31 =80 real PE HIGHLOW jump-table pointers**, and their
real 3-byte after-function alignment. The primary table at `0x00444FEC`
has **17 distinct instruction entry addresses** and covers mode bytes
`0..48`. The real second nested jump at `0x00443D64` takes `mode-16`,
through the **31-pointer** second table at `0x004450B0` with **29
distinct** original instruction heads. Exactly **28** actual source modes
enter that second jump; main modes **24/25** use an independent mesh path
despite being in its numerical range. The original **47** rendering routes
use **43 distinct physical mode-specific E8** instruction sites and
**29 real renderer/action callee heads**; modes **10 and 23** do not
invoke a mode-specific render helper. In particular main modes
**9/12/13/14** share one physical E8, as do **24/25**; main modes
**1 and 3** each have their **own physical E8** even though both target
the same `0x0043F630` method. These distinctions are retained in the
[full 49-row original PE route map](../config/animation-draw-boss-mode-e8.csv).

## Maintained native C++ parent source, not an artificial opcode trampoline

`src/AnimationDrawBoss.cpp` is the **entire one-method** candidate
`std::int32_t AnimationPoolOwner::draw(Animation*)`. It contains
**49 distinct original mode labels** divided between the primary
and nested native switches. Its original root logic checks
`Animation+0x49C` bit 0, calls the optional real `AnimationCallback::draw`
virtual slot, checks original `Animation+0x49A` draw-enable bit and
`Animation+0x570` retirement field, and calls the existing strict exact
`graphics_disable_depth_writes(&process_graphics)` before dispatch.
It tests original alpha bytes at `Animation+0x493` and `+0x497` for modes
`0..8` and 15, returns the original signed `-1` failure value on the
corresponding paths, and respects original no-draw modes 10 and 23.

It faithfully preserves the original main mode groupings and real renderer
call-site roles: modes 0/1/2/3/4/5 use five separately whole strict exact
game renderer quad methods; mode 6 calls the native one-Animation receiver;
7/8 submit the original custom renderers; 9/12/13/14 and 11 submit
actual geometry and doubled primitive count; 15 enables and disables
real Graphics fog state around an original mode-8 render; 24/25 and 47
use the independent native mesh path; 48 similarly brackets a fixed
three-primitive mesh submission with real Graphics state transitions.

The shared nested C++ stage creates a real `Vector3`, reads the original
Animation rotation/width/height and transformed position methods, inherits
parent rotation only if the original +`0x49C` bit-12 flag permits it,
executes the original geometry preparation method, and applies the real
window scaling fields for `Animation+0x4A4` modes 1/5 or 2/6. Native
`0x005B8818` is specifically **`window_state.scale` at WindowState+0x20C0**,
not a guessed arbitrary float global. The original `0x0056E0EC` /`0x0056C8D0`
constants are physically 0.5f /2.0f. Mode-specific geometry/radius/color
calculations and all 28 legitimate nested renderer paths are written out
as normal C++ switch cases. The original EAX-only 20B packed color getters
are correctly typed **`uint32_t`** instead of accepting Ghidra's
misleading float casts; the original 93B inherited auxiliary-scale getter
is a real float-returning member protocol. The source preserves native
repeated *observable calls* even when a value is not otherwise used:
mode 33's extra alternate-color getter, modes 35/36's repeated inherited
scale reads, modes 1/3's separate native calls, and modes 24/25/47's
separate/merged native mesh call-sites. These are genuine call-role details
and not inert compiler-padding statements.

The existing five exact mode-method declarations were extracted from
`src/AnimationDrawQuadModes.cpp` into one small shared
`src/AnimationDrawModeOwner.hpp`, with no new instance/data field and no
public `AnimationPoolOwner.hpp` layout/ABI modification. That sole
pre-existing canonical source/object, containing all five exact
97/97/97/48/142B functions, was **strict replayed 5/5** after the
refactor. `src/AnimationDrawBoss.cpp` uses an empty ABI-compatible derived
receiver view for **locally declared, still-unimplemented original render
backends**. These declarations are explicit provisional method names and
parameter-type hypotheses linked to the real original E8 roles, **not**
claims to own original 29 renderer bodies or provide a linked implementation.
In particular **24 of the 29 renderer/action callees in the original
mode table remain independently source-absent or NONEXACT**. This
source-level receiver view and any remaining call signatures need eventual
coherent original ownership/ODR/linkage validation before playable claims.

## Whole-parent pinned compiler evidence: exact call graph, NONEXACT machine code

The new independently repeatable
`scripts/verify-animation-draw-boss-source-roles.py` performs a narrow
one-object pinned-MSVC x86 compile and then cross-checks **every actual
COFF `REL32` call reference** from the proposed entire parent against
**every original physical PE E8 instruction target**, including their
**per-target multiplicities**, rather than just comparing call counts.
The source now has **123/123 real direct-call roles matching the original
native E8 target histogram over all 43/43 actual original targets**,
and includes every one of the **29/29** physical renderer-action target
names selected by the original 49-mode matrix. Independently checked
high-multiplicity call roles include exactly **32** primary-color reads,
**22** alternate-color reads, **12** inherited-scale reads,
**2** different physical calls to quad renderer `0x0043F630`, and
**3** physical native mesh calls to `0x00443020`. The original
separate PE route verifier also continues checking all original branch
instruction heads and 49+31 genuine switch destinations.

The **same** pinned MSVC 19.44.35211 i386 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` nevertheless produces a structurally
different whole body. **Important corrected measurement**: the compiler
COFF contribution is **5,388B** total, but that contains the
**5,141-byte executable function body /1,358 genuine x86 instruction
heads**, followed by **247B of alignment and switch/index *data***.
A raw Capstone pass that counts data-table bytes as code yields invalid
instruction metrics and is not accepted. The original is a **5,993B /
1,501 genuine x86** body, followed by its two real 49- and 31-pointer
PE tables. The new compiler's first switch is a **compressed
17-pointer table +49-byte index array**, not the original **direct
49-pointer table**; its second switch has 31 pointer entries.
Both generated instruction ordering and data/table lowering remain
nonidentical. The candidate therefore has **852 fewer executable bytes
and 143 fewer actual x86 instructions** than the immutable original.
Its 123/43 role alignment does **not** demonstrate the 123 E8 fields
at the correct original instruction offsets, nor does it establish
correct argument evaluation, physical array liveness, exception/security
ABI or any unresolved renderer backend implementation.

The source is accordingly recorded in `config/functions.csv` as
**source-present, `reconstructed`, 0% strict match**, not a `matching`
unit. No `0x00443880` entry is added to `config/matches.csv` or
`config/match-units.toml`, and **zero new original strict bytes** are
awarded to this parent. The independent 5 whole strict child methods
retain their original native proofs and physical code credit.

## Bounded repeatable workflow and current results

Reproduce the true source coverage and the original executable separately:

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-draw-boss-native.py
    nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawQuadModes.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target

The one new parent source compiles to ignored
`build/core797-probe/AnimationDrawBoss.obj` and is **never** promoted
as a canonical exact object. For the shared renderer-method header refactor,
**only one previously accepted canonical source/object and its five
original game methods** required cold replay. The rest of the original
1,229 exact-unit graph was not touched; **no full/all-graph cold replay**.
The earlier private `core797` and `core798` candidate probes and actual
COFF mode-table details remain in ignored `.analysis` and `build`
without being falsely credited.

This checkpoint increases **source-present methods 1,227 →1,228**, while
original authored exact stays **582 distinct physical whole functions /
189,106 .text bytes**, **1,229** configured strict units from **253**
protected canonical object/receipt providers. The separate 12,140B
Bullet command, 41,967B Enemy ECL and 39,470B Animation VM remain
SOURCE-ABSENT/NONEXACT. The 5,993B Animation draw Boss is now
**SOURCE-PRESENT but NONEXACT**. These statuses are materially different.
