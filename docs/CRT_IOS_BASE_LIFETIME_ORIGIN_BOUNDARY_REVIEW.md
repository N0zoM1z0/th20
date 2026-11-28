# CRT ios_base lifetime, callbacks and complete cleanup range

Four pending `ios_base` candidates have reviewed library origins. The cleanup
method also owns a previously omitted 29-byte compiler handler, now inventoried
separately. The five bodies contain 344 code bytes; five additional INT3 bytes
and a full shared 36-byte EH record are retained in the comparison evidence.
The target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Code bytes | Independent `ios.obj` symbol | Origin |
| --- | ---: | --- | --- |
| 0x00542281 | 76 | `?_Addstd@ios_base@std@@SAXPAV12@@Z` | library |
| 0x005422CD | 51 | `?_Callfns@ios_base@std@@AAEXW4event@12@@Z` | library |
| 0x00542300 | 64 | `?_Ios_base_dtor@ios_base@std@@CAXPAV12@@Z` | library |
| 0x00542340 | 124 | `?_Tidy@ios_base@std@@AAEXXZ` | library |
| 0x005679A0 | 29 | `__ehhandler$?_Tidy@ios_base@std@@AAEXXZ` | compiler |

## Standard-stream registration and retirement

`_Addstd` acquires `_Lockit(2)`, scans stream slots from one while the index is
below eight, and selects a null slot or one already containing the same object.
Slot eight is the fallback. It stores the index at receiver+8, publishes the
pointer and increments the byte-sized open count before releasing the lock.
The original pointer table at `0x005E4E38` and count array at `0x005E4E60` have
the same 40-byte separation as the two ten-element arrays in `ios.cpp`/`ios.obj`.
Both lock calls reuse the previously reviewed stream-lock protocol.

`_Ios_base_dtor` decrements the selected byte count when the stored index is
nonzero and returns early while the signed result is positive. Otherwise it
calls `_Tidy`, then conditionally destroys and sized-deletes the locale pointer
at +0x30. The complete 80-byte locale destructor at `0x004F5600` and the existing
sized-delete destination are reused; the distinct shorter locale implementation
emitted inside this archive member is not substituted for the original.

## Callback order and storage ownership

`_Callfns` follows the callback chain at receiver+0x2C. Each 12-byte node contains
the next pointer, index and callback pointer at +0/+4/+8. It checks the callback
through the already established CFG pointer at `0x0056C37C`, then invokes it with
event, stream reference and node index. The next pointer is read after the call.
The method removes its event argument with `RET 4`.

`_Tidy` first reports `erase_event` (zero). It then walks the sparse-value chain
at +0x28, saving each next pointer before sized deletion with size 16, and clears
the head. It repeats that protocol for the callback chain with delete size 12
and clears +0x2C. The pinned `xiosbase` definitions corroborate the node layouts,
callback arguments and both deletion loops. No null/failure branches are added.

## Alignment, compiler handler and shared EH record

The complete `_Tidy` archive contribution is 129 bytes: its 124-byte body through
`0x005423BB`, followed by five original INT3 bytes through `0x005423C0`.
The ledger continues to count the code body, and the audit compares all 129 bytes.
The unrelated next entry at `0x005423C1` remains outside this owner.

The prologue explicitly references the handler at `0x005679A0`. Its complete
29-byte body includes two initial NOPs, reconstructs the parent-frame cookie
input, calls the established security check, loads FuncInfo and tail-transfers
to `__CxxFrameHandler3`. Every byte and relocation role agrees with the compiler
handler in `ios.obj`. The other masked handler locator hits are not classified.

The complete 36-byte FuncInfo at `0x005A91B8` equals the archive's entire
`.xdata$x` section: magic `0x19930522`, zero states/maps/catches and flags five.
It has no relocations or additional cleanup map. This read-only record is shared
with the previously reviewed global exit controller; it does not acquire a
duplicate code row. Original cookie and exception-frame setup/restoration remain
part of the method boundary.

## Evidence and validation

The installed `VC/Tools/MSVC/14.44.35207/lib/x86/libcpmt.lib` supplies `ios.obj`;
the corresponding source is `crt/src/stl/ios.cpp` and `include/xiosbase`.
Private evidence under `.analysis/origin-boundary/ios/` retains the extracted
object, symbols, bounded locator, handler listing and `reviewed.json`.
The full original method listing is `.analysis/origin-boundary/ios-native.txt`.
`review.py` verifies archive identity, complete contributions and instruction
coverage, all ordinary bytes, relocation roles, complete HIGHLOW sets, alignment,
the whole EH record and absence of ledger overlaps for the selected bodies.

These origin/boundary results add no maintained native owner or canonical exact
credit. Tracking and generated progress pass. All 2,089 protected native inputs
and canonical products retain their hashes. No compiler run is needed for this
archive-based review; the canonical exact replay scope is **zero units**.
