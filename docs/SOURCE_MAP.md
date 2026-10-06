# Source and build ownership

| Owner | Maintained source | Target component | Acceptance |
| --- | --- | --- | --- |
| RandomState | src/Random.hpp, src/Random.cpp | transition 0x00422CB0; invocation 0x004235F0 | Exact library equivalents; excluded from authored credit |
| Timer | src/Timer.hpp, src/Timer.cpp | reset/set/mode, add 0x004530F0, tick 0x004533B0 | Five complete exact functions |
| FunctionChain | src/FunctionChain.hpp, src/FunctionChain.cpp | link construction/insertion and eight node field operations | Eleven complete exact functions; allocator, iterator, dispatch and enclosing owner remain open |
| ClockScalar | src/ClockScalar.hpp, src/ClockScalar.cpp | float read 0x004292E0; multiply 0x00452F50; set 0x004292A0 | Exact four-byte float view; enclosing owner and origin pending |
| LockRegistry | src/LockRegistry.hpp, src/LockRegistry.cpp | enable 0x0041CCC0; disable 0x0041CA30 | Two exact flag assignments; tracked locking and original global lifetime pending |
| DebugMemoryResource | src/DebugMemoryResource.hpp, src/DebugMemoryResource.cpp | constructor 0x00418DB0; destructor 0x00418E90; equality 0x0041C9F0 | Three complete exact custom PMR functions; allocation/deallocation remain undefined and this is not a linked allocator |
| TaskInfo | src/TaskInfo.hpp, src/TaskInfo.cpp | TaskInf destructor and separate virtual/helper enable/disable entries | Five complete exact functions; native constructor and allocator-based deletion pending |
| Worker | src/Worker.hpp, src/Worker.cpp | constructor 0x0040B780 | Exact 44-byte construction; close/join/detach and destructor remain undefined/pending |
| ArchiveCrypt | src/ArchiveCrypt.hpp, src/ArchiveCrypt.cpp | counted filename byte sum 0x00456270 | Exact 71-byte helper; parameter table selection, decryption and native archive owner remain pending |
| InputState | src/InputState.hpp, src/InputState.cpp | Device initializers, byte binding, button update and two mask queries | Seven complete exact functions; constructor, OS polling and Controller owner remain pending |
| Configuration | src/Configuration.hpp, src/Configuration.cpp | binding construction 0x0041FB10; default slots 0x0041FC50; option flags 0x004B9B80 | Three complete exact functions; slots/flags origin pending; full configuration owner remains open |
| GameRandom | src/GameRandom.hpp, src/GameRandom.cpp | construction 0x00422C50; bounded 0x00423EA0; float wrappers 0x00429830/0x004298E0; engine helpers | Four authored and two library complete exact units; next/seed locking and global startup remain undefined |
| WindowState | src/WindowState.hpp, src/WindowState.cpp, src/WindowApi.cpp | five field methods, system restoration, repeat reset and flags construction | Seven authored and one origin-pending complete exact units; original construction/global startup remain undefined |
| WindowApi | src/WindowApi.cpp | foreground wrapper 0x0041B480; locale detection 0x0041D0C0 | Two complete exact units; foreground source/origin identity pending |
| FontDetection | src/FontDetection.hpp, src/FontDetection.cpp | font enumeration callback 0x00414820 | Authored complete exact callback; initialization/global pointer storage remain undefined |
| SceneResources | src/SceneResources.hpp, src/SceneResources.cpp | initialization 0x004D82C0; release 0x004D8560 | Two authored complete exact orchestration functions; dependency owners remain undefined |

RandomState represents the four-byte STL engine subobject. It does not replace
its enclosing 28-byte game RNG, distribution state, four streams or locking.
Timer is a checked 16-byte value record with a raw-word/bit-field flag view.
Add/tick use the independently anchored default global clock slot and repeated
float receiver calls. Other timer modes and the enclosing clock protocol remain
open; the shared float view does not establish the full clock-controller owner.

`config/match-units.toml` owns sixteen objects and one canonical profile per source.
Sixty-two units cover complete COFF function contributions. Library units and units
with pending origin review can be replayed without becoming authored progress.

TaskInfo's observed RTTI is TaskInf. Its three-slot vtable contains deleting
destructor, enable and disable; reference callback-owner naming does not change
this identity. Separate callback helpers preserve the original virtual-wrapper
partition. The constructor's observed flags=2 and null pointers are represented
in member defaults, but its full original contribution is not accepted.

DebugMemoryResource's RTTI is debug_memory_resource. Its four-slot PMR interface
and pointer-sized receiver are independently observed. An always-true equality
override belongs to this custom class, unlike standard identity-equal resources.
The std base constructor/destructor helpers have shared empty code; their
anchors do not establish a unique owner for each shared target address.

Worker owns a real std::jthread and atomic<bool>. Its user-provided constructor
initializes those members while preserving tail padding; no matching-only body
or explicit padding is used. Do not instantiate/destroy it as a complete linked
worker until its native lifetime and synchronization protocol are reconstructed.

`probes/` remains infrastructure-only. Production currently builds objects for
component comparison; no whole-game linker or runtime acceptance is available.
Future owners must close storage, initialization, ABI and lifetime protocols.
Reference module names do not prescribe our directories or translation units.

InputButtonState retains all 704 observed bytes, including state outside the
update routine copied by native aggregate frames. InputDevice has its observed
x86 980-byte layout and a real forward-declared COM pointer. Its three partial
initializers preserve history and other header fields. No original constructor,
device polling, ownership or enlarged reference Controller is imported. Portable
tests initialize these records explicitly and do not prove game-global lifetime.

InputBindings owns three real 16-byte records of eight signed int16 fields.
Default slot initialization precedes the twenty-four binding assignments.
ConfigurationFlags represents nine observed low option bits and retains the
other twenty-three; native consumers identify six named graphics options.
The default-slot and flag contributions may be compiler generated, so exact
replay does not add authored credit. These declarations do not replace the
original 176-byte configuration, its raw-copy/load/save lifetime or fixed globals.

GameRandom closes the observed 28-byte object storage using the actual uint32
standard engine. Its default range differs from the explicitly seeded range.
Bounded and floating wrappers preserve original calls, arithmetic and return
ABI, but next and seed require the native tracked slot-10 locking protocol.
They remain undefined. Portable wrapper tests explicitly supply a deterministic
next observation and establish no linked game sampler/global startup.

WindowState's x860x2138 storage follows independently observed global clearing,
complete native construction and frame/path consumers. It contains real typed
pairs, paths, clock values, flags and repeat counters with natural alignment.
Five field members, repeat-counter reset and fixed-global system restoration are authored exact;
flags default construction is origin pending. The original constructor and
window_state storage are undefined. Portable fixture{} initialization is test
setup and does not supply original startup. WindowApi compiles Windows imports
separately; no test invokes foreground/system-setting APIs. Its exact foreground
wrapper has pending source/origin identity because the observed caller ignores
its result. Locale detection preserves the original full-width int result.
No linked window or whole-frame runtime is accepted.

Input mask queries retain uint32 bit31 and leave all 704 bytes unchanged.
The repeat query calls the actual pressed method and inspects repeat8 only.
Window repeat reset updates first/second/elapsed in a real twelve-byte record;
native window creation supplies four separate threshold values.

FontDetection preserves the stdcall/RET16 enumeration callback. The original
initializer selects availability bytes through a global pointer at 0x5B6748;
only its declaration is maintained. The full font table, indexed slot methods,
fallback selection and OS resource lifetime are not reconstructed by this unit.

SceneResources closes the two observed free cdecl orchestration routines,
including eight ordered calls per routine, early failure returns, three optional
zero-helper calls and the unused zero argument passed to stone-menu release.
The forward-declared resource pointer types define no owner layout or storage.
All dependency functions remain undefined; independent original caller/callee
observations establish their anchors and ABI. Test-only observations check
failure stopping and teardown order without original OS/resource execution.
