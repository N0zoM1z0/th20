# Player construction and SHT consumer evidence

CORE-101 is a private evidence checkpoint for the actual Player owner and its
shot-data consumer. It adds no canonical units, source mappings, authored or
reference credit. The maintained CORE/EXACT-100 graph remains 706 units across
137 objects and 135,568 disjoint bytes. All comparisons use the locked Japanese
Steamless target; no original resource bytes enter the public repository.

## Whole native contributions

| Native entry | Complete private contribution | Compared bytes |
| --- | --- | --- |
| `4F46A0` | Player construction | 794 body + 5 compiler alignment |
| `4F4110` | Ten PlayerOption values | 78 body + 5 compiler alignment |
| `4F4170` | Twelve PlayerOption values | 78 body + 5 compiler alignment |
| `4F40C0` | Thirty-three IntPoint values | 75 body + 5 compiler alignment |
| `4F9B80` | Load SHT and relocate its offset table | 164 |
| `4FF4E0` | Complete damage limit selection | 241 |
| `4FF5E0` | Focus predicate | 47 |
| `4FF840` | WeaponStoneInfo phase-one predicate | 42 |

Fresh locked-compiler objects and independent relocation replay establish each
complete contribution. Constructor roots total 1,045 bytes with 46 relocations;
all four 29-byte EH handlers, four 36-byte FuncInfo records and the complete
56-byte array construction helper also replay as support. The SHT loader's
8-byte signed conversion and 11-byte integer address addition replay as support.
The cap's two 17-byte PlayerRecord getters alias existing physical heads and
receive no duplicate credit. Original class, template and RTTI spelling remain
separate unknowns. Private byte agreement alone does not establish admission.

The SHT loader's independently decoded extent is **164 bytes**, including the
`ret 8` at `4F9C21` through `4F9C23`. Earlier probe labels saying 162 were wrong;
no comparison truncates the function to that size. Every branch and exit is
included in the loader and cap replay.

## Actual storage and resource evidence

The complete x86 Player candidate has native extent `0x1485C`, real Animation,
ten and twelve Option arrays, 33 IntPoint values, Feedback and a controller
containing 256 actual Shot values. The constructor leaves `+14850` untouched.
Its direction member at `+18` has a native floating-angle consumer: frame code
at `4F7FDF` calls `4FF710`, which reads the float and invokes the shared polar
calculation. This supersedes a handle interpretation. The value at `+1484C`
shares a floating-zero producer, but its gameplay role remains unknown.
A linear instruction scan found no explicit `+14850` displacement; this does
not exclude computed accesses or establish an original declaration.

Both original `pl00.sht` and `pl01.sht` were extracted through actual maintained
ArchiveOwner, PbgFile, resource I/O, allocator, cipher and LZSS bodies with
read-only host file bindings. The source archive, resource hashes and consumed
native cipher fields are recorded privately. Their sizes are 57,012 and
51,252 bytes; both contain 160 offset entries.

The serialized prefix is `0x5D4` bytes. Entry count is a 16-bit value at `+2`;
121 rows of three signed damage caps start at `+28`. Nine intervening words
are actual serialized header fields whose individual roles remain open.
The variable tail contains `entry_count` four-byte offset words. A private
flexible-array declaration uses the MSVC/GCC extension and the allocation
extent supplied by resource I/O; it adds no one-element surrogate or padding.

Loading writes the output pointer, returns -1 when resource loading fails,
and otherwise converts each nonnegative signed offset into a 32-bit address
word by adding the loaded base. Negative sentinel words remain untouched.
Portable checks validate the serialized words without dereferencing truncated
addresses on a 64-bit host.

The complete damage limit always queries global Context zero, including for a
Player bound to Context one. WeaponStoneInfo phase one selects Record zero's
`field_10` row and column two; otherwise focus selects that row and column one;
normal mode selects its `field_14` row and column zero. Typed 240-byte records
and actual table dimensions replace the reference's raw offset assumptions.

## Semantic checks and remaining owner boundaries

O2/ASan/UBSan checks pass complete private Player construction in dirty storage,
both original SHT load/relocation paths and 384 damage-cap selections covering
both assets, multiple rows, phases and focus byte values. Synthetic resources
through the same actual archive pipeline exercise signed sentinels and an empty
table; the missing-resource exit writes null and returns -1. Temporary host
binaries are removed automatically.

Player and WeaponStoneInfo destruction/activation fixture definitions abort if
called. This scope manually closes accepted Animation and TaskInfo child
lifetimes before releasing enclosing storage. Overlay publication, ANM callback
retirement and startup identity-matrix placement remain explicit host bindings.
These checks establish neither native game startup nor original gameplay.

The private `0x84` WeaponStoneInfo constructor remains nonexact: ordinary
candidate emission is 264 bytes and a nonthrowing candidate is 255, versus the
complete native 208. Making the class final changes no emission. Original
class finalness, exception annotations and the constructor's EH profile remain
unknown; the predicates' byte agreement does not settle them.

The whole 449-byte Player ordinary destructor depends on original ANM ownership
and resource retirement. Its actual owner declaration and lifetime must be
closed without an empty receiver class, ABI casts or fabricated service fields.
Player frame/activation, Overlay publication/lifetime and the whole 1,707-byte
damage query remain open. Production migration requires maintained owners,
fresh frozen-source builds and canonical registration/replay.

Private evidence: `core101-final-player-proof.json`,
`core101-final-shot-proof.json`, `core101-cap-proof.json`,
`core101-sht-native-assets.json`, `core101-semantics.json` and attested
`core101-player-protocol.asm`, `core101-player-value-consumers.asm`,
`core101-cap-support.asm`. Earlier completed probes and their SHA-bound inputs
are preserved in lossless archives before superseded objects are retired.
