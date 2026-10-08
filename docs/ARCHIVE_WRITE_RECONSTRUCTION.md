# Whole compression and encryption protocol

CORE/EXACT-088 maintains encryption at 004103C0 and compression at 00539550. The cipher
strictly replays all 446 bytes and six independent relocations. The compressor
is 964 candidate/native 1036 bytes: source-present and executed, with no canonical
unit, partial extent or reference absorption. Original source-local diagnostics
independently establish both authored origins. Names and the compressor sum's
source/helper identity remain unresolved.

## Ownership and cipher

Encryption preserves six cdecl arguments: caller-owned pointer, signed size,
byte key/step, signed block and limit; the returned value is the input pointer.
Signed remainder and the quarter-block threshold retain short tails, together
with the odd byte. The scratch copy has min(size,limit) bytes, allocated and
released through the existing real DiagnosticAllocator new[]/delete[] methods.
Each block reads descending odd/even scratch positions, writes sequential
output and wraps the byte key. This inverses the existing exact decryption
entry without a new guarded Bytes interface.

The complete filectrl.cpp:131 diagnostic at 0056C5B8, allocator pointer, array
specializations and memcpy are independently anchored by prior producer/consumer
and target evidence. ArchiveCrypt.cpp owns both operations under its existing
C++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise /Gd recipe. This is a local
compiler observation, not global original flags or recovered source spelling.

## Complete compression flow and disagreement

Compression preserves the signed three-argument cdecl contract and returns
malloc-owned output with a signed byte-count out parameter. Allocation uses
the native wrapped twice-input length. Failure returns null before changing
the count or shared storage. Success zeroes the count, resets the actual 8192-byte
dictionary and 8193-node tree, and preloads up to eighteen bytes at ring index one.
Existing exact root/insertion/removal bodies perform all tree operations.

The loop clamps matches to available lookahead. Lengths zero through two emit
one literal: flag one and eight MSB-first bits. Longer matches emit flag zero,
thirteen offset bits and four bits of length minus three. Each consumed position
removes the ring-plus-eighteen node, refills that slot or shrinks available input
at EOF, advances modulo 8192 and searches while input remains. Flag zero and
thirteen zero offset bits terminate the stream. Only complete bytes are flushed;
the final partial byte is dropped. The native decoder synthesizes exhausted
zero bits and requires a readable guard byte, supplied explicitly by tests.

ArchiveLzssEncode.cpp shares the bit-writing body under an explicit C++20 /Od
/Ob0 /GS /sdl /Gy /Zl /arch:SSE2 /fp:precise /Gd observation. Its full native
LzssUtil.cpp:57 literal at 005767EC is independently checked. The boundary audit
retains all 315 native instructions over 1036 bytes, every branch and exit, and
the otherwise unreachable zero-bit branch omitted by simplified decompilation.

Native stack offset -1C is initialized once and updated in seven byte-flush
read/add/write chains. The complete instruction audit finds no other direct
reference, returned result or established escape/consumer. These chains sum
emitted bytes; their protocol/source identity is unproven. No unobserved scalar
is added solely for emission. The full body remains nonexact, including stack
and expression differences. The 72-byte extent difference is not asserted to
be fully explained by the scalar's 70 instruction bytes. There is no fake
checksum return, ABI change, assembly, target byte array or shortened extent.

Zero input can write a terminator beyond the native zero-byte allocation.
Invalid pointers, negative/wrapped extents and insufficient input are not newly
accepted safe domains. Failure tests use an allocation that returns null before
pointer arithmetic/reset. No extra source guard changes native failure policy.

## Executed integration

O2/UBSan checks execute actual compression/tree/allocator, encryption/decryption
and decoding. Independent token and permutation models cover four patterns
across fourteen positive sizes from one through 20000 bytes: lookahead boundaries,
repeated/overlapping matches and ring wrapping. Checks include complete-byte
count, dropped partial bytes, reset of poisoned storage, readable decoder guards,
output boundaries, return pointers, retained tails and failure-state preservation.

Complete SaveManager CR/ST records now run real compression -> encryption ->
decryption -> decoding -> checksum/parser -> current/backup copy-back for all
eighteen Profiles, fallback and Metadata. Independent literal-token/encryption
fixtures remain for malformed record cases. Only native startup and load/save
disk boundaries are fixtures. Parser 813/native 824 and lifecycle 198/199, 68/70,
304/299 remain whole nonexact, with their contracts and oracle gates unchanged.

This proves tested external protocol, not compressor byte identity, general
malformed-input behavior, filesystem writes, process startup or playable game.
Continue whole SaveManager load 562/write 1198/save 174 with original path, I/O and
initialization owners. Keep the unused-sum investigation open; do not repeat
unchanged probes or add inert shaping for an exact claim.

## Verification and protected retirement

The frozen maintained source strictly replays 615/615 canonical units across
120 fresh objects and 120303 disjoint bytes. Encryption contributes 446 new
authored exact bytes; compression contributes none. There are 622 source
mappings and seven complete nonexact bodies. All 58 public tests pass in
127.297 seconds, including the real complete-record codec roundtrip.

Six completed probe products (144787 bytes) are retired after
their original receipts and three historical input versions are losslessly
archived. All 240 current canonical hashes and retained native/probe evidence
remain unchanged. Post-cleanup 615/615 strict replay reuses 120 objects;
net savings after archives and verification are 31538 bytes. No cleanup-only
cold compilation is performed. Raw evidence stays in ignored .analysis/.
