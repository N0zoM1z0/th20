# LaserType2Parameters copy constructor — exact native PMR copy

The native 256-byte constructor at 0x004C84B0 copies the complete Type2
parameter block used by Curve Laser segment splitting. It copies the eleven
leading scalar/vector words, invokes the original MSVC PMR
vector<BulletCommand> copy constructor at 0x0048B2F0 for the command vector,
then copies the remaining fields from offsets +0x3C through +0x58. The vector
copy uses the native polymorphic allocator semantics rather than copying the
vector's internal pointers.

The natural C++ copy constructor in src/LaserType2ParametersCopy.cpp strictly
replays 256/256 bytes under the pinned MSVC x86 /Od profile. All 252 ordinary
bytes and the one original PMR vector-constructor relocation match. The PMR
vector helper is a separately identified standard-library support function;
this constructor remains the game-authored caller. No assembly or padding is
used.
