// Seven complete original polygon counted-range C++ iterator helpers:
// dereference 19B, pointer steps 27B each, wrappers 22B each and
// begin/end wrappers 32B each; all source-verified whole strict exact.
// The first returns a live float* in EAX; treating it as void wrongly adds
// a compiler NOP. Whole strict acceptance is independent of authorship;
// original STL/template provenance is not yet proven for any wrapper.
#include <cstdint>
#include "Vector2.hpp"
namespace th20 {
extern float* __fastcall polygon_iterator_deref_40c300(void*);
extern void __fastcall polygon_iterator_angle_step_45f440(void*);
extern void __fastcall polygon_iterator_vertex_step_45f460(void*);

extern void __cdecl polygon_iterator_begin_45ef10(void* destination,void* range_owner);
extern void __cdecl polygon_iterator_end_45ef90(void* destination,void* range_owner);
// The two underlying iterator state objects really hold one pointer.
// Native x86 increments them by exactly one 4B float or one 8B Vector2.
struct NativePolygonScalarCursorStorage {
    float* cursor;
    NativePolygonScalarCursorStorage* step_45f440();
};
struct NativePolygonVertexCursorStorage {
    Vector2* cursor;
    NativePolygonVertexCursorStorage* step_45f460();
};
static_assert(sizeof(NativePolygonScalarCursorStorage)==4);
static_assert(sizeof(NativePolygonVertexCursorStorage)==4);
struct NativePolygonScalarRange {
    void* begin_45ff00(void* destination);
};
struct NativePolygonVertexRange {
    void* end_45ff20(void* destination);
};
struct NativePolygonRangeAngleCursor {
    float* dereference_45f420();
};
struct NativePolygonRangeScalarIterator {
    NativePolygonRangeScalarIterator* next_45f480();
};
struct NativePolygonRangeVertexIterator {
    NativePolygonRangeVertexIterator* next_45f4a0();
};

NativePolygonScalarCursorStorage* NativePolygonScalarCursorStorage::step_45f440() {
    ++cursor;
    return this;
}
NativePolygonVertexCursorStorage* NativePolygonVertexCursorStorage::step_45f460() {
    ++cursor;
    return this;
}
void* NativePolygonScalarRange::begin_45ff00(void* destination) {
    polygon_iterator_begin_45ef10(destination,this);
    return destination;
}
void* NativePolygonVertexRange::end_45ff20(void* destination) {
    polygon_iterator_end_45ef90(destination,this);
    return destination;
}
float* NativePolygonRangeAngleCursor::dereference_45f420() {
    return polygon_iterator_deref_40c300(this);
}
NativePolygonRangeScalarIterator* NativePolygonRangeScalarIterator::next_45f480() {
    polygon_iterator_angle_step_45f440(this);
    return this;
}
NativePolygonRangeVertexIterator* NativePolygonRangeVertexIterator::next_45f4a0() {
    polygon_iterator_vertex_step_45f460(this);
    return this;
}
}
