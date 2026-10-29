# CORE/RECON-641 — whole original Bullet emitter code and relocation-site recovery

**Original game-owned BulletController::emit at 0x004818E0 remains NONEXACT until strict whole-relocation replay is accepted.**
The immutable Japanese TH20 Steamless executable SHA-256 is
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Native source recovery

The original two consecutive Timer float setters at +0xF1 and +0x10D
immediately precede the row-speed decision at +0x112. Using ordinary
separate statement syntax caused pinned MSVC to insert a one-byte npad
after the second setter that the original game never had. A natural
C++17 if-initializer executes both real Timer side effects
unconditionally, in original call order, before selecting either row
branch:

    if (bullet->timer_4d8 = native_one,
        bullet->timer_4e8 = native_one; shot.rows > 1)

This reproduces the original contiguous code without artificial padding,
inert source, byte patches, fake calls or ASM. Both row cases preserve
the original semantics and the earlier game-authored mode-11 heading and
mode-12 sine/absolute floating-point order corrections.

## Independent full original PE / whole compiler COFF evidence

| Complete original owner | Original PE | Fresh maintained C++ |
| --- | ---: | ---: |
| Game-authored method length | 3,735 bytes | **3,735 bytes** |
| Complete method x86 instructions | 935 | **935/935 original mnemonic kinds** |
| Complete contribution including post-function NOP and 13+11 table entries | 3,832 bytes | **3,832 bytes** |
| Real E8 direct call fields | 60 | **60/60 matching locations and independently verified physical callees** |
| Original PE HIGHLOW / candidate DIR32 absolute fields | 69 | **69/69 locations and types** |
| All original physical E8+HIGHLOW field offsets/types | 129 | **129/129** |
| Original bytes outside those independently parsed relocation fields | 3,316 | **3,316/3,316 identical** |

The private audit independently parses original PE .reloc blocks,
original native E8 instructions, and the freshly compiled real COFF
relocation table. No virtual NOP deletion or target/comparison byte
editing is used. The complete contribution is 3,735 method bytes,
the original compiler NOP at +0xE97, then 96 bytes of genuine switch
tables (with all 24 of their original absolute fields).

**The matching relocation *positions* and non-relocated bytes do not
establish strict exactness.** All 69 original absolute destinations
(including old EH handler, constants, real global state and both
native switch jump tables) need independent symbol-backed anchors,
and the entire 3,832B contribution must pass a fresh canonical
relocation-aware replay. No game-linked runtime claim follows.

Original full-method private proofs:
- .analysis/core638-emitter-conditional-initializer-EH-probes.py/json:
  source variants including the true if-init, accepted only as diagnostic.
- .analysis/core641-emitter-original-full-3832-byte-audit.py/json:
  immutable original PE x86 and real COFF relocation+byte audit.
- .analysis/core641-emitter-native-60-call-proof.py/json:
  60 independent physical original E8 destinations checked in order.
- build/core641-probes/BulletEmitter.obj and receipt: pinned MSVC x86
  whole-source object; ignored, not an accepted canonical receipt.

**Affected existing canonical replay scope: zero.** This noncanonical
source had no previously accepted units; only the full original
Bullet emitter was built. No shared headers, unrelated exact sources
or native target changed, and no full cold replay was executed.
