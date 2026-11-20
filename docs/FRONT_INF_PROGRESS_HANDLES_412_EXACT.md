# FrontInf seven-marker progress animation — native 412B update pair

The original FrontInf owns two independent seven-pointer Animation arrays:
progress_handles_50 at +0x50 and progress_handles_6c at +0x6C. The x86
layout is retained with NativePointerArray<Animation, 7> and compile-time
offset/size assertions. The constructor zero-initializes both pointer arrays.

The two original 412-byte routines are now natural C++ members:

- 0x004B8BF0 — FrontInf::update_progress_handles_50
- 0x004B8650 — FrontInf::update_progress_handles_6c

Each routine first checks the first Animation slot. If present, it builds
the original zero vector, sets X to (7 - filled_count) * 28.0f, positions
all seven marker animations, interrupts the active prefix with mode 2,
uses the indexed script-frame table through the +7 event wrapper, marks
remaining filled entries with mode 3, and marks unused entries with mode 5.
The two routines have the same native control flow but retain their distinct
script-table addresses at 0x00570780 and 0x0057078C.

Both complete 412-byte C++ bodies have 348/348 identical non-relocation
bytes and all 16 native relocation sites independently solve to the original
PE targets. The 28.0f marker spacing is the original float at 0x0056FD48;
both three-element script tables contain signed values {0, 1, 2}.

Two direct animation state boundaries are also restored as ordinary C++:

- 0x004B85A0 — Animation::interrupt_offset_7(int), a complete 29-byte
  wrapper that adds seven before forwarding to Animation::interrupt
- 0x004B8580 — interrupt_animation_mode5(Animation*), a complete 22-byte
  fastcall wrapper that forwards event 5

The six repeated pointer-slot calls in the 412B functions use a typed
NativePointerArray::slot method. Its complete 22-byte body is the same
unrelocated pointer-slot arithmetic already independently verified at
Vector3::operator[] (0x00414580). It returns the address of the selected
four-byte slot, not the pointed-to Animation object.

No assembly, hand-authored bytes, padding, or instruction-shaped stubs are
used. The original Animation interrupt owner remains a separate callee.
