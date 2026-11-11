# Window screenshot scene Boss 574B — whole native strict exact

The Japanese Steamless TH20 v1.00a original at 0x00419760 is
**574B /132 native i386 instructions**, SHA-256
12c08490acf889b9d6ef21f67e6f85051f7eeb7bc00bb7b576450899b48ead57.
The independently attested PE contains **20 E8 calls and 12 HIGHLOW
fields**, all reproduced in the source at the native offsets and with
the original callee/data target identities. The remaining **446/446
ordinary bytes** match as well: the entire original function is exact.

The maintained src/WindowSnapshotScene574.cpp implements the actual
game's screenshot workflow. It first prepares the Renderer pending
surface queue (previously whole-exact 88B method at 0x0041BFC0),
queries the third screenshot InputButtonState binding through the
real byte-index +8, then checks the packed screenshot-disable bit 6.
When allowed, it creates the snapshot folder from the WindowState
user-data directory and the original narrow "snapshot" name,
formats "th20_%.3d.png" for up to 10,000 candidates,
tests game-file existence and sends the first unused path to the
real Graphics screenshot writer.

The first typed C++20 source was 551B /125 instructions and had
matching callee/data target roles but only 1/20 E8 and 3/12 data
**physical sites**. Real source experiments exposed two original
c_str() results that must be preserved in separately used const char*
locals before filesystem existence testing and Graphics writing.
Recovering these meaningful data lifetimes increased the candidate
to 575B, with all but a single branch displacement byte identical.

The final difference was the actual input mode short circuit:
the even binding channel 4 is not the disallowed mode, and the
third pointer must be non-null. Expressing the original rejection
test as a negated OR restores the real **JNE at +0x3F and its
original +0x3B displacement** without synthetic padding, NOPs,
unused variables or assembly. The genuine packed field test
uses (flags >> 6) & 1. The resulting source naturally compiles
to **574B /132 instructions** with the pinned MSVC 19.44 x86
C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.

Two original data references to WindowState user_data_directory
are **symbol base 0x005B6758 plus the real COFF +0x89 addend**.
The native PE stores the effective 0x005B67E1 pointer. The
canonical manifest explicitly uses the base 0x005B6758 to avoid
double-addend replay. All 32 original relocation targets are
strictly covered, not treated as masked-byte credit.

Reproduction (only the modified exact source, no full cold replay):

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowSnapshotScene574.cpp
    scripts/repo-python scripts/verify-window-snapshot-scene574-native-frontier.py

One distinct new game-authored exact head and **574 original bytes**.
The 884B Window scheduler at 0x004193E0 still requires its own
whole exact source; exact children do not close it.
