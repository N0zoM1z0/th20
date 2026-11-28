# Facet virtual methods, base lifetime and compiler deleting entries

Eight pending candidates, totaling 260 bytes, have reviewed SDK/library or
compiler origins. One natural pinned-header probe emits their complete native
bodies. The original target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Bytes | SDK role | Origin |
| --- | ---: | --- | --- |
| 0x00484700 | 20 | `?_Incref@facet@locale@std@@UAEXXZ` | library |
| 0x004F4E50 | 23 | `??0_Facet_base@std@@QAE@XZ` | compiler |
| 0x004F5080 | 42 | `??0facet@locale@std@@IAE@I@Z` | library |
| 0x004F54F0 | 20 | `??1_Facet_base@std@@UAE@XZ` | library |
| 0x004F55E0 | 29 | `??1facet@locale@std@@MAE@XZ` | library |
| 0x004F71B0 | 46 | `??_G_Facet_base@std@@UAEPAXI@Z` | compiler |
| 0x004F71E0 | 46 | `??_Gfacet@locale@std@@MAEPAXI@Z` | compiler |
| 0x004FBD80 | 34 | `?_Decref@facet@locale@std@@UAEPAV_Facet_base@3@XZ` | library |

## Original vtables and reference results

The `_Locimp` vtable at `0x0059600C` and `locale::facet` vtable at `0x005726BC`
share the increment/decrement entries at `0x00484700` and `0x004FBD80`.
Independent original complete-object locators identify the types as
`.?AV_Locimp@locale@std@@` and `.?AVfacet@locale@std@@`. The base vtable at
`0x0057268C` has `_Facet_base` RTTI, its deleting entry at `0x004F71B0` and two
pure virtual slots. The pinned `xfacet` and `xlocale` declarations independently
agree on this order and inheritance.

Increment locks and increments the 32-bit reference count at this+4. Decrement
uses a locked XADD of -1 and returns this only when the resulting count is zero;
otherwise it returns null. The SDK declaration gives increment a void result
and decrement a `_Facet_base*` result. Retirement remains with the existing
callers that conditionally invoke scalar deletion on that pointer.

## Construction and deletion phases

The facet constructor calls the implicit `_Facet_base` constructor, installs
the facet vtable and stores the supplied initial count at +4. The base constructor
is compiler-generated: `xfacet` supplies no written default constructor.
Both ordinary destructors have explicit SDK definitions. Facet destruction
installs its own vtable before invoking base destruction; the base destructor
installs the `_Facet_base` vtable. Their native ordinary bodies remain distinct
from the generated deleting entries.

Each 46-byte deleting entry calls the corresponding ordinary destructor first,
tests flag bit zero and conditionally invokes sized operator delete. The base
entry supplies size four; the facet entry supplies size eight. Both return the
original receiver and remove the flag argument. These complete compiler bodies
are emitted from the SDK classes without a maintained handwritten wrapper.

Several unrelated native constructors and deleting entries have the same
ordinary opcode shape after masking relocations. The actual vtable operands,
RTTI names, destructor destinations and delete sizes select these entries.
The classification does not extend to the other locator hits.

## Reproduction and validation

The private probe `.analysis/origin-boundary/facet/sdk-facet.cpp` includes
`<locale>` and defines an ordinary derived facet. That type causes the compiler
to emit the SDK parent contributions; every reviewed symbol belongs to the SDK
classes. It builds serially with the locked MSVC 19.44.35211 and
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc`.
The object and full include/command receipt are retained in
`build/gpt61-origin-locale/Facet.obj` and `Facet.receipt.json`.

All 260 bytes agree after applying the independently observed vtable, destructor
and previously established sized-delete targets. The two reference-count bodies
have no relocations. Original DIR32 fields have PE HIGHLOW entries. Full attested
Ghidra listings cover every instruction through the ledger ends, including all
returns and flag branches. These functions have no owned EH records or tables.
Private `facet/reviewed.json` captures object identity, original class records,
complete sizes and relocation roles; the bounded locator and audit remain beside
it. Existing locale RTTI and deleting-caller evidence is reused unchanged.

Tracking and generated progress pass; protected native inputs and canonical
products retain their hashes. No maintained native input or canonical unit is
changed. The exact replay scope is **zero units**, and source-present and exact
credit remain unchanged. The single private compiler probe answers the specific
SDK-origin question for these eight bodies.
