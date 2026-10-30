#pragma once
// Independently observed one-segment ribbon AnimationCallback group at
// original 0x56ECA4 vtable. Distinct from the three-segment 0x56EDDC group.
#include "NativeRibbonPolygonGroup.hpp"
namespace th20 {
struct NativeRibbonSoloGroupOptions;
// Non-owning receiver ABI view of the original distinct solo segment fan.
// This adds no constructed object or conflicting native segment storage.
struct NativeRibbonSoloSegmentDrawView {
    void draw_45dae0(const Vector3* position);
};
// Non-owning segment receiver for the genuine separate 697B dynamics. It
// shares the actual NativeRibbonSegment storage without a second allocation.
struct NativeRibbonSoloSegmentUpdateView : NativeRibbonSegment {
    void update_45d780(float limit);
};
static_assert(sizeof(NativeRibbonSoloSegmentUpdateView)==0x3C0);
struct NativeRibbonSoloSegmentArray {
    std::array<NativeRibbonSegment,1> elements;
    NativeRibbonSoloSegmentArray();
    NativeRibbonSegment* end_45dce0();
};
class NativeRibbonSoloGroup : public AnimationCallback {
public:
    std::array<NativeRibbonSegment,1> segments_08;
    union { std::uint32_t control_3c8; float control_3c8_float; };
    Timer timer_3cc;
    void* resource_token_3dc;
    explicit NativeRibbonSoloGroup(Animation* owner);
    std::int32_t configure_group_45db30(const NativeRibbonSoloGroupOptions& config, std::int32_t token);
    std::int32_t update() override;
    std::int32_t draw() override;
};
static_assert(sizeof(NativeRibbonSoloSegmentArray)==0x3C0);
static_assert(offsetof(NativeRibbonSoloGroup,segments_08)==8);
static_assert(offsetof(NativeRibbonSoloGroup,timer_3cc)==0x3CC);
static_assert(offsetof(NativeRibbonSoloGroup,resource_token_3dc)==0x3DC);
static_assert(sizeof(NativeRibbonSoloGroup)==0x3E0);
} // namespace th20
