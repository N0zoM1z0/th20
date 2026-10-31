// Native TH20 full GDI canvas object lifetime.
// The same real 0x124-byte allocated class is used by the exact constructor,
// 182B GDI surface release, and queued D3D9 glyph upload. The destructor
// releases the actual canvas GDI resources before the allocator locks
// slot 1 and invokes the original scalar object delete operation.
#include "NativeGlyphCanvasStorage.hpp"
#include "NativeGlyphCanvasView.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
NativeGlyphCanvasStorage::~NativeGlyphCanvasStorage() {
    reinterpret_cast<NativeGlyphCanvasView*>(this)->release_surface_416360();
}
// The original method has a distinct 97-byte physical templated body;
// this instantiation naturally emits its genuine lock-guard, destructor
// forwarding and security check as complete MSVC x86 code.
template void DiagnosticAllocator::release_object<NativeGlyphCanvasStorage>(NativeGlyphCanvasStorage*);
}
