// Actual original TH20 0x124B GDI glyph canvas object allocation factory.
// The genuine DiagnosticAllocator::allocate_object<T> template and native
// class constructor generate the original three E8 sites, including MSVC's
// implicit 31B class-zeroing helper. No fabricated allocator wrapper.
#include "NativeGlyphCanvasStorage.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template NativeGlyphCanvasStorage* DiagnosticAllocator::allocate_object<NativeGlyphCanvasStorage>(const char*);
}
