# Locale implementation origins, field ownership and guard cleanup

Seventeen complete entries are now classified as CRT library/compiler code:
868 code bytes, six original alignment bytes and a 44-byte EH section. Fifteen
were pending candidates; two omitted compiler cleanup/handler entries are added.
The target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Body bytes | CRT role | Origin |
| --- | ---: | --- | --- |
| 0x004FCD50 | 42 | `?_Tidy@?$_Yarn@D@std@@AAEXXZ` | library |
| 0x005419D0 | 65 | `??0_Locimp@locale@std@@AAE@_N@Z` | library |
| 0x00541A66 | 32 | `??1_Locimp@locale@std@@MAE@XZ` | library |
| 0x00541A86 | 73 | `??4?$_Yarn@D@std@@QAEAAV01@PBD@Z` | library |
| 0x00541ACF | 34 | `??_G_Locimp@locale@std@@MAEPAXI@Z` | compiler |
| 0x00541AF1 | 44 | `?_Facet_Register@std@@YAXPAV_Facet_base@1@@Z` | library |
| 0x00541B1E | 6 | `?_Getgloballocale@locale@std@@CAPAV_Locimp@12@XZ` | library |
| 0x00541B24 | 141 | `?_Init@locale@std@@CAPAV_Locimp@12@_N@Z` | library |
| 0x00541BB1 | 113 | `?_Locimp_dtor@_Locimp@locale@std@@CAXPAV123@@Z` | library |
| 0x00541C22 | 76 | `?_Locinfo_ctor@_Locinfo@std@@SAXPAV12@PBD@Z` | library |
| 0x00541C6E | 26 | `?_Locinfo_dtor@_Locinfo@std@@SAXPAV12@@Z` | library |
| 0x00541C88 | 35 | `?_New_Locimp@_Locimp@locale@std@@CAPAV123@_N@Z` | library |
| 0x00541CAB | 40 | `?_Setgloballocale@locale@std@@CAXPAX@Z` | library |
| 0x00541CD3 | 59 | `__Deletegloballocale` | library |
| 0x00541D0E | 45 | `_tidy_global` | library |
| 0x0056B248 | 8 | `__unwindfunclet$?_Init@locale@std@@CAPAV_Locimp@12@_N@Z$0` | compiler |
| 0x0056B255 | 29 | `__ehhandler$?_Init@locale@std@@CAPAV_Locimp@12@_N@Z` | compiler |

## The actual implementation object

The native `_Locimp` vtable at `0x0059600C` has a complete-object locator at
`0x005A692C`; its type descriptor at `0x005B6618` names
`.?AV_Locimp@locale@std@@`. The destructor also restores the `_Facet_base`
vtable at `0x0057268C`, whose independent RTTI names `std::_Facet_base`.
These original identities corroborate the installed `locale0.obj` symbols and
the pinned `xlocale` declarations.

The factory allocates 32 bytes, and the compiler scalar deleting destructor
conditionally releases the same size. The constructor initializes reference
count one at +4, null facet vector at +8, count zero at +0xC, category mask
zero at +0x10, the supplied transparency byte at +0x14 and the `_Yarn<char>`
name at +0x18. Its initial name is `"*"`. The deleting wrapper preserves the
ordinary destructor call before testing delete flag bit zero.

Ordinary destruction first installs the `_Locimp` vtable, invokes the locked
facet cleanup, retires the name, then installs the `_Facet_base` vtable. The
facet cleanup traverses the vector backward, skips null entries, calls each
facet's virtual `_Decref`, conditionally deletes the returned object and frees
the vector before releasing the locale lock. Original guarded indirect calls
and their receiver ordering remain in the complete bodies.

## Global and classic locale publication

Getter, setter, initializer and retirement independently agree on the global
pointer at `0x005E4E2C`. The setter registers `tidy_global` through the already
reviewed ten-entry `_Atexit` stack only once, using the flag at `0x005E4E30`,
and then publishes the supplied pointer. Retirement locks locale access,
releases the global locale through `_Deletegloballocale`, clears the pointer
and unlocks. The standalone six-byte getter is identified by these shared
roles, rather than by the generic load-and-return opcode shape alone.

`locale::_Init` locks before reading the global pointer. On first use it creates
a nontransparent implementation, publishes it, selects category mask 0x3F and
name `"C"`, takes the classic-locale reference and stores the classic object
pointer at `0x005E4E20` and `_Clocptr` at `0x005E4E04`. Its bool argument controls
a further reference increment. The independent classic-locale receiver from
the prior retirement review is `0x005E4E1C`, placing that pointer at +4 as
required by the actual locale destructor.

## Narrow names and temporary C locale state

The 73-byte `_Yarn<char>` assignment preserves source-pointer identity checks.
For a new source it first retires its old buffer, scans through the terminating
byte, allocates that full count and copies only when allocation succeeds. A null
source or failed allocation leaves the owning pointer null. This path differs
from facet registration, whose failed eight-byte node allocation invokes the
nonreturning `_Xbad_alloc` function. The registration's 44-byte instruction body
and following INT3 byte form the complete 45-byte archive contribution.

The native `_Yarn::_Tidy` at `0x004FCD50` is 42 bytes; the optimized archive
version is 24. A bounded private probe includes the pinned `xlocinfo` header and
normally destroys a `_Yarn<char>`. MSVC 19.44.35211 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc` emits the full
42-byte body. All ordinary bytes agree, and its sole `_free` relocation uses
the independently established original function at `0x0054A540`. The conditional
free precedes unconditional pointer clearing. The compiler profile is evidence
for this helper; the original game-wide build configuration remains unresolved.

`_Locinfo_ctor` queries the old C locale through `setlocale(LC_ALL, nullptr)`,
copies its name before attempting a change and records the selected/new name.
A failed old-name query uses an empty string; a failed or absent new-name change
uses `"*"`. Cleanup tests whether the saved owning pointer exists and restores
the old locale through `setlocale`. That test is pointer emptiness, not string
length; the two `_Yarn` fields are at +0x24 and +0x2C.

## Complete exception cleanup and boundary evidence

The 141-byte `_Init` body references its compiler handler at `0x0056B255`.
The handler is 29 bytes and retains the cookie check, FuncInfo load and tail
transfer to `__CxxFrameHandler3`. Its complete 44-byte `.xdata$x` section begins
at `0x005AC028`: one eight-byte unwind-map entry followed by 36-byte FuncInfo
at `0x005AC030`. The record has magic `0x19930522`, one state and flags 1.
The unwind entry transitions to -1 and invokes `0x0056B248`.

That cleanup restores the `_Lockit` receiver from the original frame at
EBP-0x10 and tail-transfers to the reviewed destructor at `0x005419AC`, retaining
the separate UCRT locale-unlock path. The cleanup has **eight code bytes plus
five INT3 bytes**, all thirteen compared against the complete source contribution.
Ghidra's existing listing omits that undefined range. A bounded pinned Capstone
decode of the attested original bytes supplies its two instructions; no database
bytes or function bodies are edited.

## Evidence and verification

Private evidence is retained in `.analysis/origin-boundary/locale/`: complete
Ghidra listings, the independently decoded cleanup, full archive contribution
comparisons, RTTI observations and the 44-byte EH-section comparison.
`reviewed.json` binds entry sizes, object hashes and original relocation roles.
The installed `stl/locale0.cpp`, `include/xlocale` and `include/xlocinfo` supply
the independent source relationships. Masked locator hits remain navigation
leads; consistent symbol roles, literals, original HIGHLOW fields, allocation
widths and control flow establish the reviewed entries.

The probe source is `yarn-tidy.cpp`; its serial reduced-priority build is retained
in `build/gpt61-origin-locale/Yarn.obj` and `Yarn.receipt.json`, including the
captured header closure. No canonical provider, profile, source or relocation
anchor changed. Tracking, generated progress and protected native input/product
hashes pass. The affected canonical exact replay scope is **zero units**;
source-present and exact totals remain unchanged.
