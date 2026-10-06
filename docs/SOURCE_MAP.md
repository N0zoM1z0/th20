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
| InputState | src/InputState.hpp, src/InputState.cpp | Device header reset/keyboard/XInput initialization, byte binding and button update | Five complete exact functions; constructor, OS polling and Controller owner remain pending |
| Configuration | src/Configuration.hpp, src/Configuration.cpp | binding construction 0x0041FB10; default slots 0x0041FC50; option flags 0x004B9B80 | Three complete exact functions; slots/flags origin pending; full configuration owner remains open |
| GameRandom | src/GameRandom.hpp, src/GameRandom.cpp | construction 0x00422C50; bounded 0x00423EA0; float wrappers 0x00429830/0x004298E0; engine helpers | Four authored and two library complete exact units; next/seed locking and global startup remain undefined |

RandomState represents the four-byte STL engine subobject. It does not replace
its enclosing 28-byte game RNG, distribution state, four streams or locking.
Timer is a checked 16-byte value record with a raw-word/bit-field flag view.
Add/tick use the independently anchored default global clock slot and repeated
float receiver calls. Other timer modes and the enclosing clock protocol remain
open; the shared float view does not establish the full clock-controller owner.

`config/match-units.toml` owns twelve objects and one canonical profile per source.
Forty-seven units cover complete COFF function contributions. Library units and units
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
