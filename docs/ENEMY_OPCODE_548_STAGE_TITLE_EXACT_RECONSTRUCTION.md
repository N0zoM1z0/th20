# Enemy opcode 548 and original FrontInf stage-title owner (CORE/EXACT-180)

The fixed comparison target is Japanese TH20 v1.00a Steamless PE32,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The whole original `EnemyState::execute_opcode` body at `0x0048C010` remains
**41,967 bytes and nonexact**. This checkpoint reconstructs three complete,
independently accepted real member functions beneath opcode **548**. No portion
of that original Enemy case is misreported as an independently exact root.

## Real native control flow and true owners

The original Enemy opcode 548 entry at `0x0048C5C1` loads the genuine
process `FrontInf*` publication slot **`0x005C06A4`**, calls the original
`0x004B96F0`, then jumps to the common Enemy dispatch exit. The published
FrontInf pointer is independently established by the original FrontInf
constructor and destructor; it is **not** a fabricated graphics/service
facade.

`0x004B96F0` is a complete **75-byte thiscall** operating on this FrontInf.
It first calls a getter on genuine global **Graphics** at `0x005C4D40`:
`Graphics::field_b0c_value()` at `0x004AC0C0`. This accessor is an **entire
20-byte** method and reads the real Graphics field at +`0xB0C` with its exact
32-bit width. If the result equals **8**, the original function returns
without evaluating the Session flag or dereferencing its AnimationFile.

Otherwise it calls `Session::flag5_value()` at `0x004B8390` on the genuine
process Session at **`0x005BA568`**. This complete **23-byte** native method
returns bit 5 of `Session.flags.bits` at +`0x6C`, preserving all unrelated
state. If that bit is set, the stage-title method returns without spawning.
Only if **Graphics mode != 8 and Session bit 5 == 0**, it loads
`FrontInf::message_file` at native +`0x170` and calls the already accepted
native `AnimationFile::spawn(const char*,int,int,Animation**)` entry at
**`0x00450C70`**. The argument tuple is **`(nullptr, 0, -1, nullptr)`**.
The original compiler reserves a four-byte hidden AnimationHandle return
object on the stack; this value is intentionally unused. There is no
invented layer, Front-file alias, stage-service vtable or redundant global.

| Entire native function | Address | Exact bytes | Relocations |
| --- | --- | ---: | ---: |
| `Graphics::field_b0c_value` | `0x004AC0C0` | **20/20** | 0 |
| `Session::flag5_value` | `0x004B8390` | **23/23** | 0 |
| `FrontInf::show_stage_title` | `0x004B96F0` | **75/75** | 5 |

The stage-title function's five independently established relocation
identities are process Graphics at `0x005C4D40`, its now exact getter at
`0x004AC0C0`, process Session at `0x005BA568`, its now exact getter at
`0x004B8390`, and the earlier exact AnimationFile spawn wrapper at
`0x00450C70`. The natural method source compiles **all 75 original native
bytes**, including return-temporary handling, condition order and unused
handle lifetime, under the established pinned x86 MSVC 19.44.35211
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
profile. The getter contributions use their corresponding authentic source
profiles. Original method spellings remain inferred, not fabricated ABI
assumptions.

## Exact dependency closure and live-owner tests

Adding the three correctly typed methods to existing `Graphics`, `Session`,
and `FrontInf` source/header owners changes **29** translation-unit providers
from authentic compiler include closures, containing **196** previously
accepted complete strict units. All 29 are cold rebuilt into
`build/core180-canonical/` without overwriting their old object/receipt
products. All **199/199** whole units, old 196 and new 3, replay strictly
exact across **33,658 original compared bytes**. Thirty compiler-local C-string
symbols shifted while existing source files compiled; old/new **complete
COFF literal extents** agree for every relocation, and all thirty original
native C-strings agree through their terminating NUL. Twenty-eight complete
native constant extents also agree, with two native string-pool padded extents
differing only after NUL. None of the five true function relocations or other
old reference targets was rewritten to force a match.

All **58** original object/receipt SHA-256 hashes remain intact; the other
**135** canonical objects retain valid build receipts. The complete replay,
affected scope and original literal evidence are privately reproducible in
`.analysis/core180-stage-title-final-proof.json`,
`core180-original-owner-scope.json`, `core180-native-string-reconciliation.json`
and `core180-strict-final-replay.json`. The original EXE and private native
analysis inputs are untouched.

The actual C++ owner host executes the production stage-title function with
the real initialized Graphics, Session, FrontInf and AnimationFile types.
The pending Renderer/Animation VM spawn is the **only explicit test boundary**;
it captures the real AnimationFile member call and its full argument tuple.
The host covers **112 graphics-mode/Session-flag/failure scenarios**, of which
**48** perform an actual spawn-boundary call. It checks both short-circuit
gates, propagation of underlying spawn errors, and **complete byte images**
of all three actual owners before and after each call. The prior 1,706 FrontInf
storage cases, 73,728 Graphics format cases, and Session lifetime/state suite
also pass. These are portable O2/UBSan checks, **not** proof of actual native
Windows/Renderer startup or a playable game.

## Remaining whole-root work

The Enemy 41,967-byte main root still needs its full primary routing tables,
shared control exits, nested rank tables, compiler-owned EH/data, complete
VM/Animation resource dependencies and missing long opcode paths. The
corresponding original opcode548 case was subsequently [integrated and tested
in the complete CORE181 whole-root host](ENEMY_WHOLE_ROOT_548_STAGE_TITLE_INTEGRATION.md)
with 256 new native receiver/guard/Renderer-boundary scenarios, without
claiming any exact root bytes. Other high-value unresolved native
paths include 539 and 555. The three complete real methods add **118**
nonoverlapping authored native bytes; they do **not** credit any fragment of
Enemy's main root.
