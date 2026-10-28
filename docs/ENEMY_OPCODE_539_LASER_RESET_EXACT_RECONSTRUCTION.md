# Enemy opcode 539: complete native LaserController reset and erase

CORE/EXACT-182. This document records independently reviewed native ownership,
complete compiler contributions and intentionally scoped verification. It does
**not** assert exactness of the 41,967-byte Enemy opcode dispatcher itself.

## Original owner and caller, checked against target bytes

The pinned Japanese Steamless 1.00a `resources/th20.exe` has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original Enemy root is at `0048C010` and is 41,967 bytes long. Its
opcode-539 head `0049579E` loads the state Context from `EnemyState+0x2EC`,
invokes the genuine Context LaserController getter at `0041CA90` (Context
pointer field +0x14), then calls `004D2430`. There are no opcode operands
on that path. The 263-byte callee ends with `xor eax,eax; ret` at `004D2536`.
The immediate following `004D2537..004D253F` INT3 fill is **not** counted
as function body or as source authored bytes.

This is a `LaserController` method, **not** an `EclManager` method. The
actual owner is the 0x58-byte TaskInfo-derived `LaserController`, whose
`IntrusiveList<Laser>` is at +0x10. Its list is non-owning. Each Laser
has native size 0x6F8, a link at +0x08, a Timer at +0x6AC and a scalar at
+0x6CC. These are checked by x86 compile-time offset assertions, with
real twenty-four 64-byte `ExtendedCommand` records, not a fake giant
padding field. The four target vtables at `00571148`, `00571214`,
`005712E8`, `00571374` each have 34 entries; their slot +0x44 entries
independently identify beam-specific `erase` implementations. The remaining
unresolved virtual slots are declared without fabricated implementations;
concrete beam lifetime and other operations remain open.

The native callee constructs an 8-byte `IntrusiveIterator<Laser>` using the
compiler's `__autoclassinit2` at `0040C080`, real typed list `begin` at
`00412280`, calls list `end` at `00412540` **once**, compares via `00411BB0`,
advances via `00411C30`, retrieves links via `0040C300`, and uses
`IntrusiveLink<Laser>::node_access` at `0040F160`. For **every** link,
including state==1, it calls `Timer::operator=(0)` at `00423520` on
`Laser+0x6AC`, clears `Laser+0x6CC`, and calls the virtual slot +0x44
with arguments `(1,0)`. The iterator is torn down by `00411B00` on the
normal and EH paths. It does not filter inactive beams or delegate to the
**distinct** `004C9490` owner routine (which filters state==1 and takes
caller arguments).

The native handler target at `005685FD` validates both stack-cookie locations
and dispatches MSVC C++ EH through the original FuncInfo at `005A9F84`.
The generated handler has the same `-0x2C` frame-cookie offset, and its
unwind funclet executes the real iterator destructor. EH/support bytes are
recorded as evidence, not awarded a second physical function unit.

## Original compiler and exact comparison

Original source spelling of `reset_all_lasers` and unexplained native local
zero-init are still inferred. No artificial code fragment, truncated
function prefix, patched target or target-byte copy is used. The maintained
`src/LaserParameters.cpp/.hpp` contains a natural whole-method source and a
partial typed Laser virtual interface; a separate local iterator scope is
necessary to reproduce normal destruction before the zero return. The local
iterator terminal is cached once, matching the actual native control flow.

Pinned MSVC 19.44.35211 x86, `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`, emits one complete **263-byte**
function. The source is structurally identical on all **207 of 207**
non-relocation bytes. The canonical `laser_reset_all_lasers` entry in
`config/match-units.toml` explicitly anchors all **14** original
relocations: SEH handler `5685FD`, cookie `5B25C0`, compiler
`__autoclassinit2`, list begin/end, iterator advance/differs/get/dtor,
three `node_access` calls, Timer assignment and security-cookie verifier
`5429EE`. Full replay is **263 / 263** bytes, zero differences.

## Only the affected dependency closure was cold rebuilt

To avoid a global cache invalidation, **no new `src` or `probes` path** was
introduced: the method and partial Laser declarations were added to the
existing LaserParameters provider. Its header reaches two distinct current
canonical TUs, `src/LaserParameters.cpp` (`/fp:precise`) and
`src/DialogueText.cpp` (`/fp:strict`). **Only these two** were cold built
into `build/core182-canonical`. Their **21/21 complete** old/new configured
units, **4,148/4,148 bytes** total, strictly replay. Their local `$SG`
string symbol numbers changed but the native destinations and full bytes
remain the same. The original CORE180 object/receipt hashes are not
silently overwritten. The other **162 canonical object receipts** pass
fresh attested input/header/object-hash verification **without recompilation**.
No whole-repository cold replay was run.

`tests/laser_reset_all_semantics.cpp` executes the real maintained
LaserController method, Timer assignment and intrusive iterator with
fixture-only virtual Laser implementations. The target's 4-byte packing
applies only on x86; host 64-bit objects use natural pointer alignment.
**601/601** scenarios pass independently under both GCC-13 and Clang-18
with ASan+UBSan. They cover empty/nonempty owners, timer flag preservation,
per-node `(1,0)` ordering, detach of current/next observer, throwing erase,
normal/EH iterator cleanup, and preservation of the controller count field.
The native beam allocator/destructor are intentionally not stubbed into
production and game-runtime equivalence is **not** claimed.

## Still open

Original source names, all unimplemented Laser virtual methods, beam
construction/retirement, session startup, rendering and the complete
41,967-byte Enemy dispatcher are separate targets. The 263-byte callee has
**one** new authenticated authored exact function; the Enemy root receives
**zero** partial function bytes. A subsequent private complete-root host may
integrate this real 539 callee but cannot confer root exactness without a
whole-function MSVC canonical replay.
