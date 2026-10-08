# SaveManager ownership, member tasks and record merge

CORE/EXACT-087 supersedes this historical checkpoint's array-delete fixture and
heap-family acceptance: file/decoded buffers use real malloc/free. The current
destructor is304/native299 and remains nonexact. Parsing now has a complete
production body with actual codec/allocator tests, but remains813/native824.
See [current parser and correction evidence](PROGRESS_FILE_PARSE_RECONSTRUCTION.md).

CORE/EXACT-086 reconstructs the actual SaveManager owner and its whole
construction, commit, destruction and merge bodies. Five complete contributions
strictly replay 463 bytes and nineteen independently anchored relocations.
The three lifecycle roots remain nonexact; they receive source presence only.

| Address | Complete bytes | Maintained operation | Exact |
| --- | ---: | --- | --- |
| 0046A570 | 48 | MemberTask copies receiver, member operation and argument | Yes |
| 0050AB10 | 189 | Worker starts a captured member task under slot 6 | Yes |
| 0050EAC0 | 44 | MemberTask invokes its receiver with the captured argument | Yes |
| 0050EEB0 | 75 | Copy current records and Metadata to backup | Yes |
| 0050F5F0 | 107 | Seed current from backup, parse current, copy back, return parse result | Yes |
| 0050E5D0 | 199 native /198 candidate | Construct two Snapshots and Worker, join, start load | No |
| 0050F660 | 70 native /68 candidate | Join, start save, return zero | No |
| 0050E990 | 299 native /262 candidate | Commit, join, release four buffers, destroy Worker | No |

## Actual storage and callback protocol

ProgressSaveManager composes two existing real ProgressSnapshots, each native
size 92140, followed by a zero word at 124280, a zeroed 64-byte interval at
124284 and the existing 16-byte Worker at 1242C4. The allocation producer at
0050ADC0 and complete deleting destructor at 0050EB30 independently corroborate
the native size 1242D8. Natural alignment accounts for the final four bytes.
The interval's role and element widths remain unknown; it has a neutral byte
representation rather than the reference review's speculative queue label.
There is no raw receiver facade or explicit padding member.

The native constructor and commit pass the receiver, a four-byte member-function
pointer and a reference to a local null argument word. Load at 0050F3B0 and save
at 0050FB60 both consume one stack word and return with RET 4. The reference
rewrites this as a no-argument lambda, changing the callable and library ABI.
The maintained member task instead owns three real copied values: receiver at
zero, member operation at four, argument at eight. Its 48-byte construction and
44-byte indirect invocation agree completely. The independently inspected
0050AC70 ->0050AEB0/0050ABD0 ->0050AEA0 ->0050EAC0 chain allocates the twelve-byte
decayed thread tuple and invokes that owned callable. It is not a std::bind
layout or a borrowed reference to the launcher's local argument.

Original class/template spelling and callback source types are not recovered.
The maintained void(void*) member contract is an inference consistent with the
one-word producers, unused arguments, ignored results and complete native
invocation. No invented integer result is added for code emission. Receivers
must outlive tasks, including detached tasks. The existing replacement behavior
still detaches an old task; SaveManager's explicit join before every launch
establishes its stronger owned lifecycle.

## Record merge and buffer ownership

Both copy directions cover 91F38 bytes: all eighteen selectable Profiles and
the separate fallback, nineteen real 7AE8 records total. The following Metadata
copy covers its complete 1F8 bytes. The maintained spans derive from the real
typed members' sizes. They preserve the native byte copies, including record
padding; neither file size nor either buffer pointer is copied.

Merge first seeds the current record region and Metadata from backup, passes
the actual current Snapshot to the native parser dependency, copies the resulting
records back to backup and returns the parser's full signed result. Copy-back
occurs for both successful and failing results; no rollback is invented.
Parse at 0050EB70 remains a genuine undefined production dependency. Its member
receiver plus Snapshot-pointer ABI is independently observed in the complete
824-byte native body and callers, rather than inferred from a compared field.

Construction starts load after joining the initially empty Worker. Commit waits
for any preceding task, launches save with a copied null argument and returns
zero. Destruction commits, joins that save, releases current file/decoded and
backup file/decoded buffers in order through the real DiagnosticAllocator,
clears their owning pointers and then performs normal Worker destruction.
The actual pending load, save and parse declarations receive no source mapping,
canonical unit or runtime claim from these callers.

## Compiler, support and disagreements

The Worker specialization belongs to src/Worker.cpp under its established
C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc /Gd /sdl profile.
An extern template declaration prevents an alternative instantiation in the
SaveManager TU. SaveManager uses the same explicit recipe without /sdl;
the whole copy and merge functions agree under that independent profile.
Existing Snapshot/Metadata/Profile constructors retain their out-of-line C++17
ownership. These are per-TU observations, not a global game build identification.

The complete member-start EH handler at 0056A85D strictly replays 39 bytes.
Its raw native MOV EAX selects FuncInfo 005AB6F0, which independently identifies
the one-state unwind table at 005AB6E8 and cleanup at 0056A850. The complete
44-byte table/info contribution has flags one; the cleanup contribution is
13 bytes including its alignment. All support bytes replay without solving
relocation fields and receive no additional coverage credit.

The member jthread constructor has the established real standard-library ABI,
but its complete emission differs from native 123 bytes because the installed
headers eliminate named forwarding helpers. As with the earlier free-function
Worker specialization, that library body receives no exact credit. The headers
and compiler remain unchanged.

Under /sdl the SaveManager constructor emits 211 bytes and commit emits 88.
Without /sdl, the complete constructor is 198/native 199 bytes and commit is
68/native 70: native post-call NOPs are absent. A separate private observation
moves the identical close-and-join body into the class definition; it leaves
both results unchanged. The destructor is 262/native 299 bytes: native has
additional caller-side null checks and a post-join NOP. The shared maintained
release method already implements null handling; its semantic behavior is
tested, but the original caller/macro partition is unresolved. No duplicate
conditions, fake returns, assembly, inert locals or shortened extents are used
to force these roots. Original source spelling and authored attribution remain
pending for all new exact contributions.

## Executed scope

O2/UBSan checks execute real threads, shared LockRegistry, complete SaveManager
and all thirty-eight real Profile constructors. Member-task checks mutate the
caller's receiver/operation/argument variables after capture, select different
operations, replace a still-running task and wait for both real task lifetimes.
The actual bound callable is also invoked after its original values change.

SaveManager tests block loading and successive saves with explicit gates:
commit waits for load, replacement waits for the preceding save, and destruction
waits for its final save before the actual allocator deletes four arrays in
native ownership order. Null-buffer destruction also runs with a null process
allocator. Whole record/Metadata images, the final fallback byte, preserved file
sizes and live buffer identities are checked in both merge directions. Parser
fixtures observe the actual current receiver, mutate its records and return
positive/negative full-width results; the maintained merge performs every copy.

Only the pending load/save/parse bodies and allocator startup are fixtures.
They are explicitly defined in the test, not substituted production services.
Disk I/O, record checksums/initialization, malformed file behavior, serialization,
the complete parser and playable game remain open. Full native layout and byte
identity are verified separately by the locked x86 compiler and complete oracle.

Final checkpoint: 56 public tests pass (174.781 seconds); the frozen
graph strictly replays613/613 units /119 fresh objects /119777 disjoint
bytes. Protected retirement removes10 probe products, saves 254260 net
bytes after original receipt/input and replay archives, preserves all238
canonical hashes and replays613/613 using119 existing objects without rebuilding.
