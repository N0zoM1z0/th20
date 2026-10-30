// Actual native game 8B .rdata at 0x0056CD90: consecutive external
// float 16.0f stroke width and 32.0f palette radius, one real data owner.
// Keep a separate translation unit so the native callers preserve their
// genuine external symbol identity, not folded __real@... constants.
namespace th20 {
extern const float native_sixteen = 16.0f;
extern const float native_polygon_radius32 = 32.0f;
}
