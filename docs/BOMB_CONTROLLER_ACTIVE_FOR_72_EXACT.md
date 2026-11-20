# BombController active-window predicate — complete native 72B

The original 0x004C4F00 helper is a real BombController member used by
the 4757B ItemInf update boss to test whether a bomb window remains active.

The natural C++ implementation checks the controller's active state for
exactly 1, then delegates the signed age comparison to the real Timer member
at +0x1C. The result is represented as a 32-bit local and returned as its
low byte, matching the native one-byte result ABI. The public declaration
uses std::uint8_t rather than assuming a C++ bool return; the original
Ghidra signature is only undefined1.

The pinned x86 MSVC profile compiles a 72-byte complete function. Its only
relocation is the Timer::less_than call at function offset +0x23 to
0x00423560. All 68 non-relocation bytes are identical. No assembly,
padding, inline byte copies, or inert locals are used.
