# STL random-device and condition-broadcast leaf origins

Two pending candidates have reviewed library origins against complete installed
x86 `libcpmt.lib` contributions and original instructions. The target is Japanese
TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Code bytes | Archive member and symbol |
| --- | ---: | --- |
| 0x005423C1 | 33 | `xrngdev.obj`: `?_Random_device@std@@YAIXZ` |
| 0x005423E3 | 20 | `cond.obj`: `__Cnd_broadcast` |

The random-device method passes the address of a four-byte local to `rand_s`
at `0x00552355`. A zero result returns that unsigned integer. Failure passes
the complete `invalid random_device value` literal at `0x00597010` to the
nonreturning `_Xout_of_range` at `0x00540EF5`; there is no fabricated failure
return. The existing array range-error evidence independently uses the same
throw destination. The full archive contribution is 34 bytes: the 33-byte
control flow and one original INT3 at `0x005423E2`.

The condition method passes receiver+4 to `WakeAllConditionVariable` and returns
integer `_Thrd_result::_Success` (zero), using a cdecl interface. The pinned
`__msvc_threads_core.hpp` places the Windows condition pointer at +4 after an
unused former vptr; `primitives.hpp` and `cond.cpp` agree on the address and
result. Its complete 20-byte contribution has no padding or EH record.

`_Cnd_signal` has exactly the same ordinary bytes and size as `_Cnd_broadcast`
in the archive. Their relocation names differ. The original operand selects
IAT `0x0056C1CC`, independently identified by the PE import descriptor as
`KERNEL32.dll!WakeAllConditionVariable`. Ordinary opcode equality alone would
therefore assign the wrong origin name to this entry.

Private `.analysis/origin-boundary/stl-leaves/` retains the two archive members
from `VC/Tools/MSVC/14.44.35207/lib/x86/libcpmt.lib` and `reviewed.json`.
`review.py` compares both complete contributions, all ordinary bytes and
relocation roles, complete HIGHLOW sets and full instruction coverage from the
existing attested `.analysis/origin-boundary/ios-native.txt` listing. Both
selected functions have no owned EH or trailing tables. Corresponding sources
are `crt/src/stl/xrngdev.cpp`, `cond.cpp` and `primitives.hpp`.

Tracking and generated progress pass; 2,089 protected native inputs/products
retain their hashes. Source-present and exact credit are unchanged, and the
canonical replay scope is **zero units**. No new compiler or analyzer run was
needed; the original listing and installed archive evidence were reused.
