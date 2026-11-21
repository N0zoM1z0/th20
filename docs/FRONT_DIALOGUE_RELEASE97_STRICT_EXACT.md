# Front dialogue release wrapper — 97B strict exact

The original helper at `0x004AE830` releases a borrowed `Dialogue*`. It is
called by the 626-byte FrontInf dialogue-command method at `0x004B9740` when an
existing dialogue is replaced. The native wrapper preserves an unused ECX
receiver and accepts the Dialogue pointer as its sole stack argument; the
original source class/owner of that receiver remains unknown.

## Natural C++ source

`src/FrontDialogueRelease97.cpp` uses a narrow non-owning
`NativeFrontDialogueReleaseView` receiver. Its `release_dialogue` method:

1. Returns immediately for a null Dialogue pointer.
2. Destroys the Dialogue through `std::destroy_at`.
3. Acquires `process_locks.slot(1)` with the native recursive-mutex guard.
4. Releases the scalar allocation with `::operator delete`.

The same source object emits the 16-byte `std::destroy_at<Dialogue>` helper at
`0x004AE9F0`. That helper calls the existing Dialogue deleting-destructor entry
at `0x004B06E0` with the non-deleting flag; the 228-byte `Dialogue::~Dialogue`
body at `0x004AFC00` remains a separate previously accepted function.

## Strict native comparison

| Native entry | Size | Canonical unit | Result |
| --- | ---: | --- | ---: |
| `0x004AE830` release wrapper | 97B | `front_dialogue_release97` | **97/97** |
| `0x004AE9F0` destroy helper | 16B | `dialogue_destroy_at16` | **16/16** |

Both units cold-build from one pinned MSVC i386 object. The 97-byte wrapper
retains all eight original relocation positions and targets: security cookie,
`std::destroy_at`, the process lock registry, slot 1, lock-guard construction,
scalar delete, lock-guard destruction and the security-cookie check. The
16-byte helper retains its original call to `Dialogue`'s deleting-destructor
wrapper. No assembly, hand-authored padding, or post-return bytes are used.

The release receiver's original source class remains unproven. The generic
`std::destroy_at` helper receives no game-authored credit, and the 626-byte
FrontInf dialogue-command parent remains NONEXACT and open.
