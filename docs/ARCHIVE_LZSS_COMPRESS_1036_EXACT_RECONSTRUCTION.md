# CORE/EXACT-540 — exact complete original 1,036-byte Archive LZSS compressor boss

Immutable Japanese TH20 v1.00a Steamless executable:
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The entire original `0x00539550..0x0053995B` game-authored LZSS
compressor is now reproduced by genuine maintained C++20 source:
1,036/1,036 native bytes exact, all 315 complete x86 instructions,
all six original direct E8 calls, all six original PE HIGHLOW fields,
and all remaining 988/988 nonrelocated original bytes.** Complete
original body SHA-256:
`b3178dfaff6a641e127510f10f12bcc246cec9c3b19ea5844952d89f95f3bb58`.
This is a new **whole game-authored boss** added to native strict
canonical units, not a truncated body, artificial NOP pad, hidden
relocation, copied executable data, or prefix-matching claim.

The existing original 706B LZSS decoder (`0x005391F0`), whole exact
ArchiveOwner catalog/read and Progress SaveManager parser already
establish the bespoke original game archive and save-file consumers.
The encoder has a real cdecl signature
`uint8_t* archive_compress(const uint8_t* data, int32_t length,
int32_t* compressed_size)` in `src/ArchiveLzssEncode.cpp` and writes
the same native original MSB-first tokens, dictionary and match-tree
protocol as before this last codegen correction. Neither original
malformed-input behavior nor whole-program archive linkage is inferred
from byte-exactness of this one codec function.

## Re-evaluating the old misleading "dead accumulator" hypothesis

The older [CORE/EXACT-088 historical source frontier](ARCHIVE_WRITE_RECONSTRUCTION.md)
reported a real **964-byte / 293-instruction** C++ candidate versus
original **1,036 bytes / 315 instructions**. Its author reasonably
refused to add an apparently unused checksum variable on the assumption
that it would only shape compiler emission. Reexamining the immutable
original and earlier exactness of unused-but-original `/Od` local
initializations shows that this blanket conclusion was incorrect.

The native function initializes a genuine **32-bit stack local at
`[EBP-0x1C]` to zero** at original `0x0053956B`. Every one of seven
native successful *complete encoded-byte flush* sites then:

1. Writes the current pending byte to the output buffer and advances
   its cursor.
2. Reads the same persistent local sum from `[EBP-0x1C]`.
3. Adds the exact 32-bit pending bits from `[EBP-0x10]`.
4. Writes the sum back into `[EBP-0x1C]` **before** clearing pending to
   zero and resetting the 0x80 bit mask.

| Original read | Original add | Original write |
| --- | --- | --- |
| `0x00539684` | `0x00539687` | `0x0053968A` |
| `0x005396DF` | `0x005396E2` | `0x005396E5` |
| `0x00539723` | `0x00539726` | `0x00539729` |
| `0x00539777` | `0x0053977A` | `0x0053977D` |
| `0x005397D8` | `0x005397DB` | `0x005397DE` |
| `0x005398CE` | `0x005398D1` | `0x005398D4` |
| `0x00539922` | `0x00539925` | `0x00539928` |

These are **22 original sum-specific instructions**: one zero
initialization plus seven complete three-instruction read/add/write
updates. The other original byte-flush, branch and reset instructions
are counted separately in the whole 315-instruction original body. No original
consumer or externally observable result for this local has yet been
found, and no API return/argument or checksum output has been added.
The local is nevertheless **not fabricated padding**: each read,
addition and write at the exact above seven original original machine
sites exists and needs a natural source-level counterpart. A single
`std::uint32_t emitted_sum = 0;` following the real pending-byte
initializer, and `emitted_sum += pending;` in the shared actual
`ARCHIVE_ADVANCE_OUTPUT()` byte-flush macro, reproduce all original
persistent local stores and the original 0x3C-byte stack frame.
The source uses ordinary unsigned arithmetic with native wrap, not a
fake volatile side effect, assembly shim, or a new observable game field.

This first correction recovered precisely **1,036 bytes and 315
instructions** from the previous 964B/293-instruction source,
matching **986 of 988** original nonrelocated bytes. The remaining
**two** differences were genuine operand ordering, not missing logic:

- At original `+0x1F4`, x86 loads the **current bit mask/weight** from
  `[EBP-0x18]` into EDX, then at `+0x1F7` performs
  `and edx,[ebp-0x08]` on the match offset value.
- The previous source wrote `(value) & weight` and the compiler
  reversed the two source memory operands at **two nonrelocated
  instruction displacement bytes**, although bitwise AND is
  commutative for the plain integer values.

The natural source `weight & (value)` corrects the actual operand
read order at that exact native site, without changing the game
integer operation. A second source alternative only changed the
single match-encoding call and reproduced the same full native bytes.
The complete macro is now consistently mask-first. Unlike artificial
local byte copying, both changes correspond to actual original
machine instructions and original arithmetic state.

## Independent immutable PE relocation and whole-body proof

An independent original PE reader decoded **all 315 instruction
heads through the physical native return** and recovered **six real
direct E8 calls** from the original opcode displacements. Separately
parsing its genuine PE `.reloc` blocks recovered **six HIGHLOW
absolute fields** inside the whole original 1,036B. Every field's
original offset, type and absolute target was compared against the
new real compiler COFF symbol identity/previously known original
function or data address plus natural COFF addend, not derived from
the candidate's bytes.

| Original operand field | Type | Independently original PE destination |
| --- | --- | --- |
| `0x00539557` | HIGHLOW | `0x005B25C0` native security cookie |
| `0x00539573` | HIGHLOW | `0x005767EC` original `LzssUtil.cpp:57 BYTE` source diagnostic |
| `0x0053957F` | HIGHLOW | `0x005B8894` actual process DiagnosticAllocator pointer |
| `0x00539584` | E8 | `0x0041F610` true DiagnosticAllocator::allocate_bytes |
| `0x005395AE` | E8 | `0x005399A0` original dictionary/tree reset |
| `0x0053960A` | HIGHLOW | `0x005C6B38` native 8192-byte archive dictionary |
| `0x0053961B` | E8 | `0x005399D0` tree root initialization |
| `0x005396AB` | HIGHLOW | `0x005C6B38` same real shared dictionary |
| `0x00539828` | E8 | `0x005394C0` remove match-tree node |
| `0x00539877` | HIGHLOW | `0x005C6B38` same real shared dictionary |
| `0x00539899` | E8 | `0x00539060` insert/search match-tree node |
| `0x00539954` | E8 | `0x005429EE` native security-cookie check |

The complete original diagnostic literal at `0x005767EC` was separately
read from the PE and agrees with the maintained code, rather than
trusting a linker candidate to select its destination. All
**12/12 original reference sites/targets** and the entire
**988/988 remaining bytes** match from the genuine newly built
C++ compiler object. The native original 1,036B body has no overlap
with any previously accepted authored original function extent.

Complete private native-original evidence:
`.analysis/core540-lzss-maintained-1036-original-relocation-proof.json`,
`.analysis/core540-lzss-maintained-original-audit.log`,
`.analysis/core539-lzss-original-1036-whole-relocation-proof.json`
and the C++ compiler-variant results
`.analysis/core537-lzss-byte-sum-probes.json` and
`.analysis/core538-lzss-final-operands-results.json`.

## Full strict canonical replay and change scope

The real maintained source file is still
`src/ArchiveLzssEncode.cpp`, now with the genuine seven accumulator
write chains and original mask-first expression. The new
`archive_lzss_compress_whole` canonical unit uses
`build/core540-canonical/ArchiveLzssEncode.obj`, its strict
input-hash receipt and the existing locked MSVC 19.44.35211 x86
C++20 flags `/Od /Ob0 /GS /sdl /Gy /Zl /arch:SSE2 /fp:precise /Gd`.
Formal `scripts/compare-coff-function.py --unit
archive_lzss_compress_whole --json` returns **`exact`** for the
**entire 1,036/1,036 bytes**, not just `structural-exact`.

There are **no public header or unrelated source edits**. The encoder
source previously had **zero native canonical units**, so only this
one actual source/object provider was cold rebuilt, and the focused
existing-object strict replay reports **1/1 original complete unit
exact**. No unfiltered whole-repository cold replay was executed.
The prior decoder, original crypt, tree and SaveManager components
remain untouched; prior codec semantic test observations are unchanged
as historical evidence, not claimed to have been rerun in this commit.

Fresh canonical evidence:
`.analysis/core540-lzss-canonical-native-build.log`,
`.analysis/core540-lzss-canonical-native-compare.json` and
`.analysis/core540-lzss-1036-scoped-native-replay.log`.

**Authored original exact code increases from 475 complete functions /
167,819 bytes to 476 complete functions / 168,855 disjoint original
bytes. Canonical units rise from 1,181 to 1,182 and unique compiler
object providers from 241 to 242.** Source-present functions remain
**1,181** because the complete encoder source was already tracked,
but had not previously been strictly exact.

The 39,470B Animation VM, 41,967B Enemy ECL dispatcher, 3,735B Bullet
emitter, 555B Player movement, 3,111B Player main frame and the
archive SaveManager load/write/save and user filesystem/state consumers
remain separate unfinished originals. A byte-exact compressor does not
establish a complete linked game or unlimited malformed-input safety.
