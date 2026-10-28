# CORE/EXACT-226 — complete 242-byte Bullet cancel-all traversal

The immutable native target is Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Independent native Ghidra/Capstone inspection, original direct caller
`0x004AF310` and the existing game-owned `BulletController` layout identify
the entire **242-byte** original method at `0x0047CB90` as the owner of the
active-list cancel-all protocol. Original C++ spelling is inferred, not assumed
from previous documents. Its full original interval SHA-256 is
`30b0181ce40faae692b396f3868d90cbc5832627bfbab8a53b939b6ff594c8e3`.

| Complete native game method | Address | Size | Relocations | Canonical original comparison |
| --- | --- | ---: | ---: | ---: |
| `BulletController::cancel_all(int)` | `0x0047CB90` | 242 B | 13 | **242/242 B** |
| `BulletController::active_list()` | `0x00485970` | 19 B | 0 | **19/19 B** |

The new maintained `src/BulletCancellation.cpp` reuses the real
`IntrusiveList<Bullet>` and `IntrusiveIterator<Bullet>` types and accesses
the actual active sentinel at Controller+`0x286D64` through the **full 19B**
`active_list()` reference method, not a synthetic list or a raw offset facade.
The source performs the native complete `begin`, `end`, `differs`, `get`,
`node_value`, `advance` and iterator destructor EH protocol. For each
Bullet it **skips state 0 or state 3**, else invokes the original
`Bullet::cancel(int)` at **`0x0047C8F0`** and increments the cancelled count.
The native loop has the real iterator advance on every skipped branch and
returns the integer total. The whole function, including its SEH scope,
security cookie, frame handler, complete return and all **13** original
relocation types/values, strictly compares byte-for-byte. These relocation
anchors are supported by independently verified original PE callees,
shared iterator identities and the original game caller, not solved merely
from a compared field. Original `Bullet::cancel(int)` is **662 bytes** and
still not itself source/COFF exact; it is declared as a real external member
ABI, without falsely granting credit for its body.

The initial natural C++ attempt accessed `active` directly and compiled to
**240 bytes**, because the compiler replaced original `active_list()` call
`0x00485970` by a local `add` expression. Explicitly calling the native 19B
member fixes that error. Reexpressing the two excluded states as one natural
`if (state == 0 || state == 3) continue;` reproduces the native alternate
branch shape; the resulting whole source achieves **190/190 matching
non-relocation bytes** and **242/242 bytes** after strict replay. The
original native 19B getter independently reproduces all 19 bytes without
relocations. No truncation, assembly patching or tolerance was used.

## Actual shared-header include closure, including an earlier omission

Two declarations were added to typed `src/Bullet.hpp`: original
`Bullet::cancel(int)` and `BulletController::active_list()`. The canonical
receipt-based include graph presently has **twelve** affected source files
and **49 complete strict units**: **47 previous + two new**, across **12
fresh locked-MSVC objects**. All **49/49** replayed byte-exact with full
original relocation checks; no unfiltered whole-graph cold replay. In
particular, the old **832-byte** `Bullet::handle_boundary` from
`src/BulletBoundary.cpp`, full **339-byte** `BulletController::fire`, **291B**
`Bullet::deactivate`, all four reflection functions and the previously
admitted **81B** six-group draw orchestration were recompiled and strictly
verified.

An independent audit found the prior CORE/EXACT-225 documentation's
"complete" **45/45 previously affected units** mistakenly omitted the
already accepted 832-byte `src/BulletBoundary.cpp` provider, and therefore
understated the actual pre-CORE225 include closure (46 old units over ten
source providers, not 45 over nine). The historical 45/45 initial subset
really did pass, but it was **not exhaustive**. This checkpoint preserves that
historical result, explicitly corrects the claim, and provides the new
**complete 49/49** result covering the formerly omitted root. The locked
compiler's COFF-private diagnostic-string labels shifted from `$SG79853`
to `$SG79856` and `$SG117789..117792` to `$SG117792..117795`;
original target data addresses and full relocated code were invariant.

Focused proof logs: `.analysis/core226-bullet-cancellation-native-replay.log`
and `.analysis/core226-bullet-full-include-closure-replay.log`. Verified original
19B active-list getter interval SHA-256:
`9e9cb96e4ffc33d9db960dc256f38a2f7ae5a9a1f49b96d4c20c8f3f27515f4a`.

Still open: the separately original **662-byte** Bullet individual cancel
function `0x0047C8F0`, **273-byte** per-group draw `0x0047DB70`,
**3,735-byte** single-bullet emission `0x004818E0`, **1,846/2,018-byte**
Bullet movement/interaction bosses and the **41,967-byte** Enemy ECL root.
These full native bodies are not partial-match credit or proved by an
already exact calling function; full-game linking remains unproven.
