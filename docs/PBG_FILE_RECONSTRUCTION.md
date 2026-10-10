# Native Pbg file protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## CORE/EXACT-094 production update

All twelve complete File/IFile bodies are now maintained in PbgFile.hpp/.cpp
and formally canonical, including all five destructor alignment bytes. File
authorship remains unknown; vtable/RTTI identities do not prove it. Factory 129
versus native 67 and full original data/startup emission remain open. Actual
production checks and the frozen 646-unit graph pass. The prior private-only
state is historical. See [whole production evidence](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md).

CORE-093 closes twelve complete private File/IFile candidates: 1,148 function
bytes plus five compiler alignment bytes strictly replay 1,153 bytes and
35 independently established relocations. This is dependency evidence for the
whole archive/resource protocol, not production source, canonical registration,
authored-origin credit or a playable reconstruction. The accepted graph remains
625 units across 125 objects.

| Entry | Observed operation | Function bytes | Compared bytes |
| --- | --- | ---: | ---: |
| 539040 | IFile construction | 23 | 23 |
| 538A30 | IFile destruction | 20 | 20 |
| 539000 | File construction | 51 | 51 |
| 5389D0 | File destruction and close | 80 | 85 |
| 538C50 | Open and choose read/append mode | 346 | 346 |
| 538AB0 | Close and clear valid handle/access | 53 | 53 |
| 538DB0 | Read and return reported count | 88 | 88 |
| 538F90 | Write and compare reported count | 106 | 106 |
| 538BF0 | Return current position | 43 | 43 |
| 538C20 | Return file size | 39 | 39 |
| 538F10 | Seek a valid handle | 51 | 51 |
| 538E10 | Convert a name and select its prefix | 248 | 248 |

## Storage and independent identities

Native RTTI identifies the class tags and names Pbg::File and Pbg::IFile.
The complete-object locator, hierarchy and complete eight-slot tables establish
vptr identities independently of constructor fields. File contains its vptr,
four-byte HANDLE and four-byte access word, for twelve bytes on the native target.
The interface has seven pure operations and virtual destruction. Method and
field spellings and source access visibility remain inferred; Ghidra's unrelated
MFC/stringbuf automatic labels do not establish these owners.

Real PE import-name lookup tables establish the eight Win32 IAT anchors.
Separate full CRT exports and primary pinned SDK mutable wchar overloads
establish secure wide copying/concatenation and first/last character search.
The complete empty Unicode/seek/read constant pool independently identifies the
empty-prefix literal; no compared root field is solved to produce an anchor.
An initial dot-prefix hypothesis had identical non-relocation instructions and
was rejected before strict closure. The original value is an empty string.

The destructor's five trailing INT3 alignment bytes are retained and compared.
Its complete 29-byte EH handler agrees with the already established shared
handler of other canonical owners. Unique complete 36-byte funcinfo metadata
closes its data identity. Both scalar deleting destructors and both mutable
wchar wrappers strictly replay 136 bytes as support only. EH and these four
contributions receive no additional coverage. Full original RTTI emission and
class source ownership remain separate from vptr-anchor corroboration.

## Actual file behavior

Open first invokes virtual close, then scans until the first read or append
character. Other characters are skipped; an empty mode or one containing only
write does not open a handle. Read uses GENERIC_READ and OPEN_EXISTING; append
uses GENERIC_WRITE and OPEN_ALWAYS, followed by an ignored seek-to-end result.
Both share reads and request normal/sequential flags. Failure leaves the selected
access word while the handle is invalid. Close clears access only when a valid
handle was present, and repeated close does not close it twice.

Read returns the reported byte count even when ReadFile reports false. Write
compares the requested count with the reported count while ignoring WriteFile's
boolean result. Position returns the direct SetFilePointer result. Size returns
the direct GetFileSize result. Seek returns true for a valid handle even when
SetFilePointer reports an error. Destruction directly closes the File lifetime;
the open operation retains ordinary virtual dispatch.

Conversion zeroes a 260-wchar staging array and ignores the CP932 conversion
result. A converted colon selects the converted name directly. Otherwise the
module name supplies a prefix through its last backslash; absence of that
backslash selects the empty prefix. The converted name is concatenated as-is,
including a leading UNC-style backslash. Failed conversion leaves the zeroed
name and therefore selects the module directory. These observations are
preserved without path normalization or repaired return contracts.

## Checks, cleanup and remaining gates

Actual complete probe bodies pass O0/O2 and UBSan checks for mode ordering,
flags, virtual close, destruction/repeated close, access gating, short reads and
writes, ignored OS booleans, failed seek/size results, stale access after failed
open, colon/module/empty prefixes and conversion failure. Fixtures replace only
Win32 calls and valid-input secure wchar CRT calls. ASCII fixture names and
host four-byte wchar storage do not establish full native CP932/CRT behavior.

The native scalar File factory's pre-clear, array helper emission, production
partition and shared allocator instantiations remain open. Formal admission
still requires the shared real File/owner/resource bodies, complete codec and
allocator integration, fresh canonical builds and frozen graph replay. Archive
member failure ownership and native startup/disk/game runtime remain explicit
unfinished domains; this File closure does not absorb reference replacements.

Private proofs are core093-file-bindings.json, core093-file-host-results.json
and bounded core093-wide-*-native.asm exports. Only V3 remains active. Completed
binding, host-report and cleanup writers must never rerun; preserve the actual
sources and original SHA-bound historical inputs.

Protected cleanup retires six superseded/completed products: 449,414 bytes,
including two host binaries. Original receipts remain losslessly archived.
All 254 canonical/active hashes and 4,996 evidence files are protected. All
625 current canonical units and 21 active whole probe roots strictly replay
after cleanup using existing objects. Net savings after receipt/replay archives
are 348,238 bytes. No unchanged source graph is rebuilt for this cleanup.
