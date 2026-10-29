// Entire original native 0x00447800..0x00447848 Animation allocation factory.
// Original uses one 0x5E4-byte allocation, compiler class zero-init
// helper and genuine 498B Animation constructor; no manual memset.
// MSVC /sdl and the canonical class Animation declaration naturally emit
// the real 73-byte method with its three physical E8 relocations.
// The non-/sdl 298B pool boss declares extern template so the factory
// has exactly one canonical definition and linker-decorated type.
#include "Animation.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template Animation* DiagnosticAllocator::allocate_object<Animation>(const char*);
}
