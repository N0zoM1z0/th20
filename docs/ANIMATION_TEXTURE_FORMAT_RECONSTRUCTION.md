# ANM texture-format selection and Graphics accessors

CORE/EXACT-134 accepts the complete 77-byte texture-format selection function at
`0044CFB0`. Its maintained C++ body retains the actual Graphics predicate call,
all conditional branches, the typed format table and the full input word.
Two complete Graphics accessor bodies fold to already-covered physical heads;
they receive no additional mapping, function or byte credit.

## Native behavior and typed API data

The selection function calls the process Graphics owner at `005C4D40`, through
the 13-byte function at `00412540`. The complete callee stores its receiver and
returns EAX zero without reading any member. Consequently the selection function
returns its original 32-bit argument on the locked target and does not read the
format table. This is an observed native constant result, not a replacement for
an unknown configuration option. The descriptive `texture_format_mode` name does
not establish the original spelling or intent of the disabled policy.

The retained branches would select index five for API UNKNOWN/A8R8G8B8 and index
three for R8G8B8. Native accesses use format base `0056E208`; the independently
used byte-size table starts at `0056E22C`. The intervening 36 bytes contain nine
four-byte format words: UNKNOWN followed by eight A8R8G8B8 entries. The next
36 bytes contain nine byte-size values, all four. The maintained nine-element
format view follows these observed bases and values; the original source
declaration is not recovered. No pixel conversion or input validation follows
from the tables.

Native builds use the installed SDK's actual D3DFORMAT type and named constants.
The portable API declaration retains the four-byte enum and the same three
values, independently checked against the installed SDK. The complete maintained
36-byte format array matches the native array as supporting data, without
additional physical exact credit. No table bytes are used as instruction source.

Three direct selection callers are observed at `0044D9EE`, `0044DC37` and
`0044E907`. The complete 562-byte last caller stores the selected word back into
its argument and later indexes the same table. Selection itself remains safe for
arbitrary input words because the actual predicate is zero. Downstream texture
creation still has the native unchecked table domain. The reference's added
out-of-range exception is not imported.

## Actual Graphics owner and physical folding

`Graphics::get_device` returns the actual +08 device pointer. The two independently
inspected texture creators call its native head at `00412730` and use SDK
IDirect3DDevice9 CreateTexture slot +5C. The whole 17-byte maintained method
strictly matches that head. Graphics storage, constructor, configuration and
Workers retain their existing canonical declarations and profiles.

The predicate's 13-byte body is physically shared with the canonical
IntrusiveList end function; the device getter's 17-byte body is shared with the
canonical IntrusiveLink previous-value function. Their original unit ownership,
source mappings and pending origin decisions remain unchanged. Actual Graphics
definitions are separately verified as complete aliases under the Graphics
profile. Folding alone cannot choose one source-level origin for a physical
implementation with different independently established roles.

## Texture-creator origin and boundary review

The complete 155-byte dynamic texture body at `0044C0B0` sets the low two record
flag bits to two, calls the actual Graphics device accessor and requests one
level with D3DUSAGE_DYNAMIC, the selected API format and D3DPOOL_DEFAULT. It stores
the table byte size and returns the low 32 bits of width times height times that
size. Native nonzero HRESULT handling includes positive results; it does not
change the final byte-size write or arithmetic return.

The complete 139-byte render-target body at `0044C150` sets the low two flag bits
to one and requests one level with D3DUSAGE_RENDERTARGET, A8R8G8B8 and the default
pool. Its stored byte size is four or two according to the actual Graphics
presentation format; its result is zero, including the diagnostic path. Existing
record bits outside the low two survive both operations.

Both diagnostic paths call the already-covered five-byte empty function at
`0040C6B0`, currently owned by EclDiagnostic.cpp as `ecl_diagnostic_hint`. The
native calls corroborate a shared diagnostic role beyond ECL; they do not change
that canonical owner or resolve its pending original authorship.

These two creators and the format selector are independently reviewed as authored
game code from their actual File/texture record publication, custom flag policy,
game-owned tables and Graphics/SDK consumers. SDK virtual calls do not make their
surrounding functions SDK implementations. Complete native decoding reconciles
five selected bodies, every direct branch and all returns. The native bodies and
the intervening alignment intervals are kept separate; compiler contributions
for the two creators are not yet established.

Both creators retain an unused thiscall receiver belonging to the unresolved
Renderer. No simplified receiver declaration or free-function ABI substitute is
introduced. They remain source-absent and nonexact; this batch adds only their
origin decisions. Renderer +6000DFC..+6000DFF and File +6C remain unresolved, and
File::clear remains source-absent.

## Verification and current source ownership

Graphics.hpp/cpp contain the actual accessor definitions, typed table and one
format-selection body. GraphicsApi.hpp binds the native SDK type and portable
API enum. A fresh full-owner MSVC probe reproduces all three complete function
bodies before admission. The production selection function has five independently
anchored relocations: the actual Graphics global, the complete predicate head
and three reads of the independently inspected table. No compared field is
solved to obtain an anchor.

All 163 original object/receipt pairs and their authentic input versions are
preserved before editing. Captured includes select eight affected objects; each
builds once and all 22 previous affected units remain strict exact. The other
155 objects retain their immutable receipts. Eleven full literal payload roles
independently identify eleven generated-label changes; all old targets, extents,
profiles, translation units and relocation meanings remain unchanged. The source
path set remains 278 entries.

The host fixture uses real Graphics construction, configuration and Workers,
with explicitly resource-absent startup/destruction bindings. It verifies
65,536 low-word inputs and 8,192 generated full words over 64 flag/configuration
states, plus six high/boundary words per state. Two live Graphics owners publish
distinct or null borrowed device pointers; getters must use the actual receiver.
Both fixture owners use static storage, giving untouched fields and padding
defined initial bytes before their actual constructors. Complete owner images
remain unchanged. The first strict-warning compile rejects
typed memcpy into constructed flag classes; typed bit_cast assignment resolves
that fixture issue without warning suppression or production changes.

All 81 public CI tests pass in 456.027 seconds. After finalizing the fixture's
static storage, the affected test passes UBSan in 3.624 seconds and ASan/UBSan
in 3.456 seconds. Production inputs remain frozen throughout that fixture-only
update. Private hashes bind both the CI fixture version and the final separately
verified fixture.

Retirement removes 18 replaced object/receipt products totaling 826,869 bytes.
The 379,186-byte lossless archive preserves nine original input closures and
immutable receipts. All 163 current pairs are protected before deletion; the
complete 869-unit existing-object replay remains strict exact afterward, with
all 326 product hashes and 278 source hashes unchanged and zero compiler calls.
The final audit checks source-absent creators/clear, unchanged folded origins,
authentic archived headers/inputs and final sanitizer input hashes.

The resulting graph has 869 units / 163 objects / 166,440 disjoint comparison
bytes and 877 source mappings, with eight mapped whole functions nonexact.
Reviewed origins are 175 authored and 40 excluded, with 6,713 pending. Authored
source coverage is 172 functions; exact coverage is 168 functions / 46,109 bytes.
The two creators and File::clear remain in the authored denominator without
source or exact credit. Reviewed-subset ratios do not measure the whole-game
95% byte-exact objective.

Portable checks corroborate this domain without creating a COM device, invoking
Renderer texture creation or proving startup, loaded-resource lifetime or whole
game linkage. Current product and proof paths are recorded in the
[handoff](RE_HANDOFF.md).
