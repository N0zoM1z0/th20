#include "Animation.hpp"
#include "ParticleEffectInfoLookup26.hpp"
#include "ItemResourceOwners.hpp"
#include "Vector2.hpp"
#include "AnimationVector2CoordinateNormalize95.hpp"
#include "NativeAnimationVector2ConfigView.hpp"
#include "NativeAnimationFadeConfig86.hpp"
#include "NativeAnimationColorConfigView.hpp"
#include "Color3.hpp"
#include "AnimationCallback.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "GraphicsCameraSqrtAdapter35.hpp"
#include "GameController.hpp"
#include "GameRandom.hpp"
#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationHandle.hpp"
#include "NativeAnimationLegacyFileView.hpp"
#include "NativeCardRendererFileView.hpp"
#include "Motion.hpp"
#include "Interpolation.hpp"
#include "ClockScalar.hpp"
#include "Timer.hpp"
#include "AnimationFile.hpp"
#include <cstdint>

namespace th20 {
using NativeVmEntryCallback=AnimationEntryCallback;
using NativeVmScriptCallback=AnimationScriptCallback;
struct NativeAnimationCornerProjectionDispatchView { void project_corners(Vector3* corners); };

extern "C" {
// Original external helpers are declared with their x86 receiver/stack ABI.
float __cdecl vm_004397f0(float,float);

extern std::uint8_t DAT_00435285;
extern float DAT_0056c8cc,DAT_0056c8d0,DAT_0056c8e0,DAT_0056e0e8,DAT_0056e0f0,DAT_0056e0f4;
extern float _DAT_0056e0e8;
extern float DAT_0056e058[3];
extern std::uint32_t DAT_005aefe4;
extern std::uint32_t DAT_005ba4c4;
extern void* DAT_005ba828;
extern float DAT_005c5540[3];
}

// The remaining original call sites are bound to real C++ owners or to the
// small set of still-unrecovered external helpers. There is no generic VM
// numeric-address call view left in this translation unit.
#define FUN_004397f0 vm_004397f0

// Replace already reconstructed dependencies with their real maintained C++
// owners. The remaining ABI view is restricted to helpers whose owner/signature
// is still being recovered; these calls no longer route through numeric stubs.
#undef FUN_00435520
#define FUN_00435520(self) (reinterpret_cast<Animation*>(self)->update_motion())
#undef FUN_004358d0
#define FUN_004358d0(self) (reinterpret_cast<Animation*>(self)->update_interpolations())
#undef FUN_00435c80
#define FUN_00435c80(self) (reinterpret_cast<Animation*>(self)->update_geometry())
#undef FUN_00437490
#define FUN_00437490(self,index) (reinterpret_cast<AnimationFile*>(self)->script(index))
#undef FUN_004374b0
#define FUN_004374b0(self) (reinterpret_cast<Animation*>(self)->slowdown())
#undef FUN_00437840
#define FUN_00437840(self,value,rotate,scale) (reinterpret_cast<Animation*>(self)->transform_direction(*reinterpret_cast<Vector3*>(value),rotate,scale))
#undef FUN_00437930
#define FUN_00437930(self) (reinterpret_cast<Animation*>(self)->rotation_z_value())
#undef FUN_00438620
#define FUN_00438620(self,animation_value,index) (reinterpret_cast<AnimationFile*>(self)->apply_sprite(reinterpret_cast<Animation*>(animation_value),index))
#undef FUN_00438bd0
#define FUN_00438bd0(self,frames,curve,start,end) (reinterpret_cast<NativeAnimationColorConfigView*>(self)->interpolate_secondary_alpha_438bd0(frames,curve,start,end))
#undef FUN_00438c60
#define FUN_00438c60(self,frames,curve,start,end) (reinterpret_cast<NativeAnimationFadeConfig86*>(self)->interpolate_channel_438c60(frames,curve,start,end))
#undef FUN_00438cc0
#define FUN_00438cc0(self,frames,curve,start,end) (reinterpret_cast<NativeAnimationColorConfigView*>(self)->interpolate_rgb_438cc0(frames,curve,start,end))
#undef FUN_00438d50
#define FUN_00438d50(self,frames,curve,start,end) (reinterpret_cast<NativeAnimationColorConfigView*>(self)->interpolate_primary_rgb_438d50(frames,curve,start,end))
#undef FUN_00438db0
#define FUN_00438db0(self,frames,curve,from,to) (reinterpret_cast<NativeAnimationVector2ConfigView*>(self)->interpolate_secondary_scale_438db0(frames,curve,*reinterpret_cast<const Vector2*>(from),*reinterpret_cast<const Vector2*>(to)))
#undef FUN_00438df0
#define FUN_00438df0(self,frames,curve,from,to) (reinterpret_cast<NativeAnimationVector2ConfigView*>(self)->interpolate_primary_scale_438df0(frames,curve,*reinterpret_cast<const Vector2*>(from),*reinterpret_cast<const Vector2*>(to)))
#undef FUN_00438e30
#define FUN_00438e30(self,frames,curve,from,to) (reinterpret_cast<NativeAnimationVector2ConfigView*>(self)->interpolate_uv_scale_438e30(frames,curve,*reinterpret_cast<const Vector2*>(from),*reinterpret_cast<const Vector2*>(to)))
#undef FUN_00439280
#define FUN_00439280(self,x,y,z) (reinterpret_cast<Animation*>(self)->set_rotation_speed(x,y,z))
#undef FUN_00439390
#define FUN_00439390(self,x,y) (reinterpret_cast<Animation*>(self)->set_scale_speed(x,y))
#undef FUN_004393f0
#define FUN_004393f0(self,value) (reinterpret_cast<Motion*>(self)->set_position(*reinterpret_cast<const Vector3*>(value)))
#undef FUN_0044ced0
#define FUN_0044ced0(handle) (reinterpret_cast<std::uintptr_t>(reinterpret_cast<AnimationHandle*>(handle)->resolve()))
#undef FUN_00450350
#define FUN_00450350(self,layer) (reinterpret_cast<Animation*>(self)->set_layer(layer))
#undef FUN_00438a70
#define FUN_00438a70(self,value) (reinterpret_cast<FloatInterpolation*>(self)->set_end(*reinterpret_cast<const float*>(value)))
#undef FUN_00438a90
#define FUN_00438a90(self,value) (reinterpret_cast<VectorInterpolation*>(self)->set_end(*reinterpret_cast<const Vector3*>(value)))
#undef FUN_00438ae0
#define FUN_00438ae0(self,value) (reinterpret_cast<AngleInterpolation*>(self)->set_end(*reinterpret_cast<const Angle*>(value)))
#undef FUN_00438b00
#define FUN_00438b00(self,value) (reinterpret_cast<FloatInterpolation*>(self)->set_tangent_end(*reinterpret_cast<const float*>(value)))
#undef FUN_00438b20
#define FUN_00438b20(self,value) (reinterpret_cast<VectorInterpolation*>(self)->set_tangent_end(*reinterpret_cast<const Vector3*>(value)))
#undef FUN_00438b50
#define FUN_00438b50(self,value) (reinterpret_cast<AngleInterpolation*>(self)->set_tangent_end(*reinterpret_cast<const Angle*>(value)))
#undef FUN_00438e70
#define FUN_00438e70(self,value) (reinterpret_cast<VectorInterpolation*>(self)->set_duration(value))
#undef FUN_004393d0
#define FUN_004393d0(self,value) (reinterpret_cast<FloatInterpolation*>(self)->set_start(*reinterpret_cast<const float*>(value)))
#undef FUN_00439440
#define FUN_00439440(self,value) (reinterpret_cast<AngleInterpolation*>(self)->set_start(*reinterpret_cast<const Angle*>(value)))
#undef FUN_00439460
#define FUN_00439460(self,value) (reinterpret_cast<FloatInterpolation*>(self)->set_tangent_start(*reinterpret_cast<const float*>(value)))
#undef FUN_00439480
#define FUN_00439480(self,value) (reinterpret_cast<VectorInterpolation*>(self)->set_tangent_start(*reinterpret_cast<const Vector3*>(value)))
#undef FUN_004394b0
#define FUN_004394b0(self,value) (reinterpret_cast<AngleInterpolation*>(self)->set_tangent_start(*reinterpret_cast<const Angle*>(value)))
#undef FUN_004394d0
#define FUN_004394d0(self,mode) (reinterpret_cast<FloatInterpolation*>(self)->set_mode(mode))
#undef FUN_004394f0
#define FUN_004394f0(self,mode) (reinterpret_cast<VectorInterpolation*>(self)->set_mode(mode))
#undef FUN_004395b0
#define FUN_004395b0(self) (reinterpret_cast<FloatInterpolation*>(self)->reset_timer())
#undef FUN_004396a0
#define FUN_004396a0(self) (reinterpret_cast<VectorInterpolation*>(self)->reset_timer())


// Native leaf owners recovered from the VM call graph.
#undef FUN_0040ff90
#define FUN_0040ff90(timer) (static_cast<std::int32_t>(*reinterpret_cast<Timer*>(timer)))
#undef FUN_00423520
#define FUN_00423520(timer,value) (*reinterpret_cast<Timer*>(timer)=static_cast<std::int32_t>(value))
#undef FUN_00423540
#define FUN_00423540(timer) ((*reinterpret_cast<Timer*>(timer))++)
#undef FUN_00423ea0
#define FUN_00423ea0(random,bound) (reinterpret_cast<GameRandom*>(random)->bounded(bound))
#undef FUN_00423ee0
#define FUN_00423ee0(random) (reinterpret_cast<GameRandom*>(random)->next())
#undef FUN_00424060
#define FUN_00424060(controller) (reinterpret_cast<GameController*>(controller)->animation_frozen())
#undef FUN_00429280
#define FUN_00429280(timer,source) (reinterpret_cast<Timer*>(timer)->set_from_current(*reinterpret_cast<const Timer*>(source)))
#undef FUN_004292a0
#define FUN_004292a0(clock,value) (reinterpret_cast<ClockScalar*>(clock)->set(value))
#undef FUN_004292e0
#define FUN_004292e0(clock) (static_cast<float>(*reinterpret_cast<ClockScalar*>(clock)))
#undef FUN_004296e0
#define FUN_004296e0(vector,other) (*reinterpret_cast<Vector3*>(vector)+=*reinterpret_cast<const Vector3*>(other))
#undef FUN_004297d0
#define FUN_004297d0(random) (reinterpret_cast<GameRandom*>(random)->radians())
#undef FUN_00429800
#define FUN_00429800(random,limit) (reinterpret_cast<GameRandom*>(random)->range(limit))
#undef FUN_004298e0
#define FUN_004298e0(random) (reinterpret_cast<GameRandom*>(random)->signed_unit())
#undef FUN_0042b590
#define FUN_0042b590(animation,bytes) (reinterpret_cast<Animation*>(animation)->allocate_geometry(bytes))
#undef FUN_00438600
#define FUN_00438600(left,right) (add_angles(left,right))
#undef FUN_00445770
#define FUN_00445770(animation,value) (reinterpret_cast<NativeAnimationCornerProjectionDispatchView*>(animation)->project_corners(reinterpret_cast<Vector3*>(value)))

std::int32_t Animation::update() {

  short sVar1;
  int iVar2;
  std::uint32_t uVar3;
  std::uint32_t uVar4;
  std::uint32_t *puVar5;
  float *pfVar6;
  int *piVar7;
  int *puVar8;
  void *extraout_ECX;
  void *this_local;
  short *extraout_ECX_00;
  short *extraout_ECX_01;
  short *extraout_ECX_02;
  short *extraout_ECX_03;
  short *extraout_ECX_04;
  void *this_00;
  void *this_01;
  std::uint32_t *puVar10;
  float fVar11;
  void *local_780;
  void *local_77c;
  int local_778;
  void *local_774;
  int local_770;
  std::uint32_t *local_76c;
  std::uint32_t *local_764;
  float *local_74c;
  float *local_748;
  void *local_70c;
  void *local_704;
  void *local_700;
  void *local_6fc;
  void *local_6f4;
  void *local_6ec;
  void *local_6e8;
  void *local_6e0;
  void *local_6dc;
  void *local_6d8;
  void *local_6d0;
  void *local_6c8;
  std::uint32_t *local_6c0;
  std::uint32_t *local_6b8;
  std::uint32_t *local_6b0;
  void *local_6ac;
  void *local_6a8;
  void *local_6a4;
  void *local_6a0;
  void *local_69c;
  void *local_698;
  void *local_694;
  void *local_690;
  void *local_68c;
  void *local_688;
  void *local_684;
  void *local_680;

  void *local_650;
  void *local_64c;
  void *local_648;
  void *local_644;
  void *local_640;
  void *local_63c;
  void *local_638;
  void *local_634;
  void *local_630;
  void *local_62c;
  void *local_628;
  void *local_624;
  void *local_620;
  void *local_61c;
  void *local_614;
  void *local_604;
  void *local_600;
  NativeVmEntryCallback local_5fc;
  void *local_5f8;
  void *local_5f4;
  void *local_5ec;
  void *local_5e8;
  std::uint32_t local_5c8;
  void *local_5bc;
  float local_5b8;
  void *local_5b0;
  void *local_5a8;
  void *local_5a0;
  void *local_598;
  float local_594;
  void *local_58c;
  float local_588;
  void *local_580;
  int *local_4b4;
  float *local_4ac;
  int *local_4a4;
  float *local_49c;
  int *local_494;
  float *local_48c;
  int *local_484;
  float *local_47c;
  int *local_474;


  int *local_180;
  short *local_f0;
  float initial_clock_value;
  std::uint32_t local_e0;
  std::int16_t *scan_instruction;
  std::int16_t *instruction;

  if ((*(std::uint32_t *)((int)this + 0x4b4) & 1) != 0) {
    return 0;
  }
  fVar11 = FUN_004292e0((float *)&DAT_005aefe4);
  initial_clock_value = (float)fVar11;
  if ((*(std::uint32_t *)((int)this + 0x49c) >> 8 & 1) != 0) {
    FUN_004292a0(&DAT_005aefe4,DAT_0056c8cc);
  }
  fVar11 = FUN_004374b0((int)this);
  local_588 = (float)fVar11;
  if (_DAT_0056e0e8 < local_588) {
    fVar11 = FUN_004374b0((int)this);
    local_594 = (float)fVar11;
    FUN_004292a0(&DAT_005aefe4,initial_clock_value - local_594 * initial_clock_value);
    fVar11 = FUN_004292e0((float *)&DAT_005aefe4);
    local_5b8 = (float)fVar11;
    if (local_5b8 < 0.0f) {
      FUN_004292a0(&DAT_005aefe4,0);
    }
  }
  if (reinterpret_cast<Animation*>(this)->callback &&
      (iVar2 = reinterpret_cast<Animation*>(this)->callback->update(), iVar2 != 0)) {
    goto LAB_00434fd1;
  }
  if (*(int *)((int)this + 0x5dc) != 0) {
    local_5fc = reinterpret_cast<Animation*>(this)->field_5dc;
    iVar2 = (*local_5fc)(reinterpret_cast<Animation*>(this));
    if (iVar2 != 0) goto LAB_00434fd1;
  }
  if ((-1 < *(int *)((int)this + 0x28)) && ((*(std::uint32_t *)((int)this + 0x49c) >> 0x19 & 1) == 0)
     ) {
    local_76c = (std::uint32_t *)((int)this + 0x4d8);
    FUN_00423540(local_76c);
    if (*(int *)((int)this + 0x438) != 0) {
      local_774 = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
      local_770 = *(int *)((int)this + 0x24);
      iVar2 = static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(FUN_00437490(local_774,local_770)));
      instruction = (short *)(iVar2 + *(int *)((int)this + 0x28));
      goto LAB_0042de0b;
    }
    if ((((*(std::uint8_t *)((int)this + 0x4a0) & 3) != 1) || (DAT_005ba828 == 0)) ||
       (uVar3 = FUN_00424060(DAT_005ba828), uVar3 == 0)) {
LAB_0042b831:
      local_77c = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
      local_778 = *(int *)((int)this + 0x24);
      iVar2 = static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(FUN_00437490(local_77c,local_778)));
      instruction = (short *)(iVar2 + *(int *)((int)this + 0x28));
      sVar1 = instruction[2];
      iVar2 = FUN_0040ff90((int)this + 0x4c8);
      if (iVar2 < sVar1) goto LAB_00434dce;
      local_e0 = (int)*instruction + 1;
      if (0x27b < local_e0) {
switchD_0042b8cc_caseD_a0:
        goto LAB_00434dad;
      }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      switch((&DAT_00435285)[*instruction]) {
      case 0xa0: {
        goto switchD_0042b8cc_caseD_a0;
      }
      case 0: {
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) & 0xfe;
        *(std::uint32_t *)((int)this + 0x28) = 0xffffffff;
        goto LAB_00434fd1;
      }
      case 1: {
        *(std::uint32_t *)((int)this + 0x28) = 0xffffffff;
        goto LAB_00434fb5;
      }
      case 0x68: {
        std::uint32_t local_554;
        if ((instruction[3] & 1U) == 0) {
          local_554 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_554 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xfffffeff | (local_554 & 1) << 8;
        break;
      }
      case 0x72: {
        void* local_57c;
        std::uint32_t local_558;
        local_57c = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_780 = this;
        if ((instruction[3] & 1U) == 0) {
          local_558 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_558 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_784 = reinterpret_cast<AnimationFile*>(local_57c)->spawn_child(local_558,reinterpret_cast<Animation*>(local_780),0);
        break;
      }
      case 0x77: {
        void* local_584;
        float local_56c;
        std::uintptr_t local_568;
        float local_564;
        std::uint32_t local_560;
        std::uint32_t local_55c;
        local_584 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 0x12 & 1) == 0) {
          local_55c = 0;
        }
        else {
          local_55c = 4;
        }
        local_580 = this;
        if ((instruction[3] & 1U) == 0) {
          local_560 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_560 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_7c = reinterpret_cast<AnimationFile*>(local_584)->spawn_child(local_560,reinterpret_cast<Animation*>(local_580),local_55c);
        local_568 = FUN_0044ced0(&local_7c);
        if ((instruction[3] & 2U) == 0) {
          local_564 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_564 = (float)fVar11;
        }
        *(float *)(local_568 + 0x484) = local_564;
        if ((instruction[3] & 4U) == 0) {
          local_56c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_56c = (float)fVar11;
        }
        *(float *)(local_568 + 0x488) = local_56c;
        break;
      }
      case 0x7c: {
        void* local_590;
        float local_578;
        std::uint32_t local_574;
        std::uint32_t local_570;
        float local_f8;
        std::uintptr_t local_f4;
        local_590 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 0x12 & 1) == 0) {
          local_570 = 2;
        }
        else {
          local_570 = 6;
        }
        local_58c = this;
        if ((instruction[3] & 1U) == 0) {
          local_574 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_574 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_80 = reinterpret_cast<AnimationFile*>(local_590)->spawn_child(local_574,reinterpret_cast<Animation*>(local_58c),local_570);
        local_f4 = FUN_0044ced0(&local_80);
        if ((instruction[3] & 2U) == 0) {
          local_578 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_578 = (float)fVar11;
        }
        *(float *)(local_f4 + 0x484) = local_578;
        if ((instruction[3] & 4U) == 0) {
          local_f8 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_f8 = (float)fVar11;
        }
        *(float *)(local_f4 + 0x488) = local_f8;
        break;
      }
      case 0x74: {
        void* local_59c;
        std::uint32_t local_fc;
        local_59c = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_598 = this;
        if ((instruction[3] & 1U) == 0) {
          local_fc = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_fc = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_7a8 = reinterpret_cast<AnimationFile*>(local_59c)->spawn_child(local_fc,reinterpret_cast<Animation*>(local_598),2);
        break;
      }
      case 0x73: {
        void* local_5a4;
        std::uint32_t local_100;
        local_5a4 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_5a0 = this;
        if ((instruction[3] & 1U) == 0) {
          local_100 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_100 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_7ac = reinterpret_cast<AnimationFile*>(local_5a4)->spawn_child(local_100,reinterpret_cast<Animation*>(local_5a0),4);
        break;
      }
      case 0x75: {
        void* local_5ac;
        std::uint32_t local_104;
        local_5ac = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_5a8 = this;
        if ((instruction[3] & 1U) == 0) {
          local_104 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_104 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_7b0 = reinterpret_cast<AnimationFile*>(local_5ac)->spawn_child(local_104,reinterpret_cast<Animation*>(local_5a8),6);
        break;
      }
      case 0x7b: {
        if (*(int *)((int)this + 0x55c) != 0) {
          puVar5 = (std::uint32_t *)(*(int *)((int)this + 0x55c) + 0x444);
          puVar10 = (std::uint32_t *)((int)this + 0x444);
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar10 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar10 = puVar10 + 1;
          }
        }
        break;
      }
      case 0x78: {
        void* local_5b4;
        std::uintptr_t local_114;
        float local_110;
        float local_10c;
        std::uint32_t local_108;
        local_5b4 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_5b0 = this;
        if ((instruction[3] & 1U) == 0) {
          local_108 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_108 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_84 = reinterpret_cast<AnimationFile*>(local_5b4)->spawn_child_and_update(local_108,reinterpret_cast<Animation*>(local_5b0),0);
        local_114 = FUN_0044ced0(&local_84);
        if ((instruction[3] & 2U) == 0) {
          local_110 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_110 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_10c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_10c = (float)fVar11;
        }
        Vector3 local_a8(local_110,local_10c,0.0f);
        reinterpret_cast<Animation*>(this)->transform_direction(local_a8,1,1);
        *reinterpret_cast<float*>(local_114 + 0x484) = local_a8.x;
        *reinterpret_cast<float*>(local_114 + 0x488) = local_a8.y;
        break;
      }
      case 0x76: {
        void* local_5c0;
        std::uint32_t local_118;
        local_5c0 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_5bc = this;
        if ((instruction[3] & 1U) == 0) {
          local_118 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_118 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        AnimationHandle local_7b4 = reinterpret_cast<AnimationFile*>(local_5c0)->spawn_child_and_update(local_118,reinterpret_cast<Animation*>(local_5bc),0);
        break;
      }
      case 0x7a: {
        std::uint32_t local_11c;
        EffectInfo* const effect_info=particle_effect_info_for_session_437520(0);
        if ((instruction[3] & 1U) == 0) {
          local_11c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_11c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        // The original VM forwards its Animation receiver as both the
        // opaque effect-parameter payload and the existing-animation owner.
        AnimationHandle local_7b8=effect_info->spawn_effect(
            local_11c,*reinterpret_cast<const EffectParameters*>(this),this);
        break;
      }
      case 0x47: {
        NativeVmScriptCallback local_5e4;
        float local_5e0;
        float local_5dc;
        float local_5d8;
        float local_5d4;
        float local_5d0;
        float local_5cc;
        std::uint32_t local_12c;
        std::uint32_t local_128;
        std::uint32_t local_124;
        std::uint32_t local_120;
        std::uint32_t local_d8;
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) | 1;
        fVar11 = FUN_00437930((int)this);
        local_5cc = (float)fVar11;
        if (local_5cc <= -(DAT_0056e0f0 / DAT_0056c8e0)) {
LAB_0042c32a:
          fVar11 = FUN_00437930((int)this);
          local_5d4 = (float)fVar11;
          if (DAT_0056e0f0 / DAT_0056c8e0 <= local_5d4) {
            fVar11 = FUN_00437930((int)this);
            local_5d8 = (float)fVar11;
            if (local_5d8 < DAT_0056e0f0 / DAT_0056c8d0 + DAT_0056e0f0 / DAT_0056c8e0) {
              if ((instruction[3] & 8U) == 0) {
                local_124 = *(std::uint32_t *)(instruction + 10);
              }
              else {
                local_124 = this->integer_value(*(std::uint32_t *)(instruction + 10));
              }
              local_d8 = local_124;
              goto LAB_0042c528;
            }
          }
          fVar11 = FUN_00437930((int)this);
          local_5dc = (float)fVar11;
          if (local_5dc <= -(DAT_0056e0f0 / DAT_0056c8e0)) {
            fVar11 = FUN_00437930((int)this);
            local_5e0 = (float)fVar11;
            if (DAT_0056e0f0 / DAT_0056c8d0 + DAT_0056e0f0 / DAT_0056c8e0 < local_5e0) {
              if ((instruction[3] & 4U) == 0) {
                local_128 = *(std::uint32_t *)(instruction + 8);
              }
              else {
                local_128 = this->integer_value(*(std::uint32_t *)(instruction + 8));
              }
              local_d8 = local_128;
              goto LAB_0042c528;
            }
          }
          if ((instruction[3] & 2U) == 0) {
            local_12c = *(std::uint32_t *)(instruction + 6);
          }
          else {
            local_12c = this->integer_value(*(std::uint32_t *)(instruction + 6));
          }
          local_d8 = local_12c;
        }
        else {
          fVar11 = FUN_00437930((int)this);
          local_5d0 = (float)fVar11;
          if (DAT_0056e0f0 / DAT_0056c8e0 <= local_5d0) goto LAB_0042c32a;
          if ((instruction[3] & 1U) == 0) {
            local_120 = *(std::uint32_t *)(instruction + 4);
          }
          else {
            local_120 = this->integer_value(*(std::uint32_t *)(instruction + 4));
          }
          local_d8 = local_120;
        }
LAB_0042c528:
        if (*(int *)((int)this + 0x5e0) != 0) {
          local_5e4 = reinterpret_cast<Animation*>(this)->field_5e0;
          local_d8 = (*local_5e4)(reinterpret_cast<Animation*>(this),local_d8);
        }
        if ((int)local_d8 < 0) {
          FUN_00438620(native_card_renderer_5c0698->current_file_437950(),this,0x120);
        }
        else {
          local_5ec = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          FUN_00438620(local_5ec,(int)this,local_d8);
        }
        uVar4 = FUN_0040ff90((int)this + 0x4c8);
        *(std::uint32_t *)((int)this + 0x43c) = uVar4;
        break;
      }
      case 0x34: {
        NativeVmScriptCallback local_5f0;
        std::uint32_t local_134;
        std::uint32_t local_130;
        std::uint32_t local_e8;
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) | 1;
        if (*(int *)((int)this + 0x5e0) == 0) {
          if ((instruction[3] & 1U) == 0) {
            local_134 = *(std::uint32_t *)(instruction + 4);
          }
          else {
            local_134 = this->integer_value(*(std::uint32_t *)(instruction + 4));
          }
          local_e8 = local_134;
        }
        else {
          local_5f0 = reinterpret_cast<Animation*>(this)->field_5e0;
          if ((instruction[3] & 1U) == 0) {
            local_130 = *(std::uint32_t *)(instruction + 4);
          }
          else {
            local_130 = this->integer_value(*(std::uint32_t *)(instruction + 4));
          }
          local_e8 = (*local_5f0)(reinterpret_cast<Animation*>(this),local_130);
        }
        if ((int)local_e8 < 0) {
          FUN_00438620(native_card_renderer_5c0698->current_file_437950(),this,0x120);
        }
        else {
          local_5f8 = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          FUN_00438620(local_5f8,(int)this,local_e8);
        }
        uVar4 = FUN_0040ff90((int)this + 0x4c8);
        *(std::uint32_t *)((int)this + 0x43c) = uVar4;
        break;
      }
      case 0x35: {
        NativeVmScriptCallback local_6e4;
        std::uint32_t local_144;
        std::uint32_t local_140;
        std::uint32_t local_13c;
        std::uint32_t local_138;
        int local_ec;
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) | 1;
        if (*(int *)((int)this + 0x5e0) == 0) {
          if ((instruction[3] & 1U) == 0) {
            local_144 = *(std::uint32_t *)(instruction + 4);
          }
          else {
            local_144 = this->integer_value(*(std::uint32_t *)(instruction + 4));
          }
          if ((instruction[3] & 2U) == 0) {
            local_140 = *(std::uint32_t *)(instruction + 6);
          }
          else {
            local_140 = this->integer_value(*(std::uint32_t *)(instruction + 6));
          }
          uVar3 = FUN_00423ee0(0x5ba4c4);
          local_ec = uVar3 % local_140 + local_144;
        }
        else {
          local_6e4 = reinterpret_cast<Animation*>(this)->field_5e0;
          if ((instruction[3] & 1U) == 0) {
            local_13c = *(std::uint32_t *)(instruction + 4);
          }
          else {
            local_13c = this->integer_value(*(std::uint32_t *)(instruction + 4));
          }
          if ((instruction[3] & 2U) == 0) {
            local_138 = *(std::uint32_t *)(instruction + 6);
          }
          else {
            local_138 = this->integer_value(*(std::uint32_t *)(instruction + 6));
          }
          uVar3 = FUN_00423ee0(0x5ba4c4);
          local_ec = (*local_6e4)(reinterpret_cast<Animation*>(this),uVar3 % local_138 + local_13c);
        }
        if (local_ec < 0) {
          FUN_00438620(native_card_renderer_5c0698->current_file_437950(),this,0x120);
        }
        else {
          local_604 = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          FUN_00438620(local_604,(int)this,local_ec);
        }
        uVar4 = FUN_0040ff90((int)this + 0x4c8);
        *(std::uint32_t *)((int)this + 0x43c) = uVar4;
        break;
      }
      case 0x4a: {
        float local_14c;
        float local_148;
        if ((instruction[3] & 1U) == 0) {
          local_148 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_148 = (float)fVar11;
        }
        *(float *)((int)this + 0x50) = local_148;
        if ((instruction[3] & 2U) == 0) {
          local_14c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_14c = (float)fVar11;
        }
        *(float *)((int)this + 0x54) = local_14c;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x6a: {
        float local_154;
        float local_150;
        if ((instruction[3] & 1U) == 0) {
          local_150 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_150 = (float)fVar11;
        }
        *(float *)((int)this + 0x58) = local_150;
        if ((instruction[3] & 2U) == 0) {
          local_154 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_154 = (float)fVar11;
        }
        *(float *)((int)this + 0x5c) = local_154;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x65: {
        float local_15c;
        float local_158;
        if ((instruction[3] & 1U) == 0) {
          local_158 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_158 = (float)fVar11;
        }
        *(float *)((int)this + 0x68) = local_158;
        if ((instruction[3] & 2U) == 0) {
          local_15c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_15c = (float)fVar11;
        }
        *(float *)((int)this + 0x6c) = local_15c;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 8;
        break;
      }
      case 0x4b: {
        std::uint32_t local_160;
        if ((instruction[3] & 1U) == 0) {
          local_160 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_160 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x493) = (std::uint8_t)local_160;
        break;
      }
      case 0x4c: {
        std::uint32_t local_16c;
        std::uint32_t local_168;
        std::uint32_t local_164;
        if ((instruction[3] & 1U) == 0) {
          local_164 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_164 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x492) = (std::uint8_t)local_164;
        if ((instruction[3] & 2U) == 0) {
          local_168 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_168 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint8_t *)((int)this + 0x491) = (std::uint8_t)local_168;
        if ((instruction[3] & 4U) == 0) {
          local_16c = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_16c = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint8_t *)((int)this + 0x490) = (std::uint8_t)local_16c;
        break;
      }
      case 0x4d: {
        std::uint32_t local_170;
        if ((instruction[3] & 1U) == 0) {
          local_170 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_170 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x497) = (std::uint8_t)local_170;
        break;
      }
      case 0x4e: {
        std::uint32_t local_17c;
        std::uint32_t local_178;
        std::uint32_t local_174;
        if ((instruction[3] & 1U) == 0) {
          local_174 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_174 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x496) = (std::uint8_t)local_174;
        if ((instruction[3] & 2U) == 0) {
          local_178 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_178 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint8_t *)((int)this + 0x495) = (std::uint8_t)local_178;
        if ((instruction[3] & 4U) == 0) {
          local_17c = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_17c = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint8_t *)((int)this + 0x494) = (std::uint8_t)local_17c;
        break;
      }
      case 0x26: {
        FUN_00423520((void *)((int)this + 0x4c8),*(int *)(instruction + 6));
        *(std::uint32_t *)((int)this + 0x28) = *(std::uint32_t *)(instruction + 4);
        goto LAB_0042b831;
      }
      case 0x27: {
        std::uint32_t local_184;
        local_180 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_180 = *local_180 + -1;
        if ((instruction[3] & 1U) == 0) {
          local_184 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_184 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if (0 < (int)local_184) {
          FUN_00423520((void *)((int)this + 0x4c8),*(int *)(instruction + 8));
          *(std::uint32_t *)((int)this + 0x28) = *(std::uint32_t *)(instruction + 6);
          goto LAB_0042b831;
        }
        break;
      }
      case 0x3c: {
        *(std::uint8_t *)((int)this + 0x4a0) =
             *(std::uint8_t *)((int)this + 0x4a0) & 0x3f |
             (*(std::uint8_t *)((int)this + 0x4a0) >> 6 ^ 1) << 6;
        *(float *)((int)this + 0x50) = *(float *)((int)this + 0x50) * DAT_0056e0f4;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x3d: {
        *(std::uint8_t *)((int)this + 0x4a0) =
             *(std::uint8_t *)((int)this + 0x4a0) & 0x3f |
             (*(std::uint8_t *)((int)this + 0x4a0) >> 6 ^ 2) << 6;
        *(float *)((int)this + 0x54) = *(float *)((int)this + 0x54) * DAT_0056e0f4;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x70: {
        if ((*(std::uint8_t *)((int)this + 0x4a0) >> 6 & 1) != 0) {
          *(float *)((int)this + 0x50) = *(float *)((int)this + 0x50) * DAT_0056e0f4;
        }
        if ((*(std::uint8_t *)((int)this + 0x4a0) >> 6 & 2) != 0) {
          *(float *)((int)this + 0x54) = *(float *)((int)this + 0x54) * DAT_0056e0f4;
        }
        *(std::uint8_t *)((int)this + 0x4a0) = *(std::uint8_t *)((int)this + 0x4a0) & 0x3f;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x43: {
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xfeffffff | (*(std::uint8_t *)(instruction + 4) & 1) << 0x18;
        break;
      }
      case 0x44: {
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 1;
        break;
      }
      case 0x45: {
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) & 0xfffffffe;
        break;
      }
      case 0x6f: {
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffefffff | (*(std::uint8_t *)(instruction + 4) & 1) << 0x14;
        *(std::uint32_t *)((int)this + 0x4b8) = *(std::uint32_t *)(instruction + 6);
        *(std::uint32_t *)((int)this + 0x4bc) = *(std::uint32_t *)(instruction + 8);
        break;
      }
      case 0x49: {
        float local_190;
        float local_18c;
        float local_188;
        if ((instruction[3] & 1U) == 0) {
          local_188 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_188 = (float)fVar11;
        }
        *(float *)((int)this + 0x38) = local_188;
        if ((instruction[3] & 2U) == 0) {
          local_18c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_18c = (float)fVar11;
        }
        *(float *)((int)this + 0x3c) = local_18c;
        if ((instruction[3] & 4U) == 0) {
          local_190 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_190 = (float)fVar11;
        }
        *(float *)((int)this + 0x40) = local_190;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 2;
        break;
      }
      case 0x57: {
        float local_19c;
        float local_198;
        float local_194;
        if ((instruction[3] & 4U) == 0) {
          local_194 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_194 = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_198 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_198 = (float)fVar11;
        }
        if ((instruction[3] & 1U) == 0) {
          local_19c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_19c = (float)fVar11;
        }
        FUN_00439280(this,local_19c,local_198,local_194);
        break;
      }
      case 0x58: {
        float local_1a4;
        float local_1a0;
        if ((instruction[3] & 2U) == 0) {
          local_1a0 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_1a0 = (float)fVar11;
        }
        if ((instruction[3] & 1U) == 0) {
          local_1a4 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_1a4 = (float)fVar11;
        }
        FUN_00439390(this,local_1a4,local_1a0);
        break;
      }
      case 0x59: {
        std::uint32_t local_1a8;
        std::uint8_t local_cf;
        std::uint8_t local_ce;
        local_ce = *(std::uint8_t *)(instruction + 4);
        local_cf = *(std::uint8_t *)((int)this + 0x493);
        if ((instruction[3] & 2U) == 0) {
          local_1a8 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_1a8 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        FUN_00438c60(this,local_1a8,0,local_cf,local_ce);
        break;
      }
      case 0x37: {
        *(char *)((int)this + 0x499) = (char)instruction[4];
        break;
      }
      case 0x48: {
        float local_1c0;
        float local_1bc;
        float local_1b8;
        float local_1b4;
        float local_1b0;
        float local_1ac;
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 6 & 1) == 0) {
          if ((instruction[3] & 4U) == 0) {
            local_1ac = *(float *)(instruction + 8);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 8));
            local_1ac = (float)fVar11;
          }
          if ((instruction[3] & 2U) == 0) {
            local_1b0 = *(float *)(instruction + 6);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 6));
            local_1b0 = (float)fVar11;
          }
          if ((instruction[3] & 1U) == 0) {
            local_1b4 = *(float *)(instruction + 4);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 4));
            local_1b4 = (float)fVar11;
          }
          Vector3 local_7f0(local_1b4,local_1b0,local_1ac);
          *reinterpret_cast<Vector3*>(reinterpret_cast<std::uint8_t*>(this) + 0x2c) = local_7f0;
        }
        else {
          if ((instruction[3] & 4U) == 0) {
            local_1b8 = *(float *)(instruction + 8);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 8));
            local_1b8 = (float)fVar11;
          }
          if ((instruction[3] & 2U) == 0) {
            local_1bc = *(float *)(instruction + 6);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 6));
            local_1bc = (float)fVar11;
          }
          if ((instruction[3] & 1U) == 0) {
            local_1c0 = *(float *)(instruction + 4);
          }
          else {
            fVar11 = this->float_value(*(float *)(instruction + 4));
            local_1c0 = (float)fVar11;
          }
          Vector3 local_7fc(local_1c0,local_1bc,local_1b8);
          *reinterpret_cast<Vector3*>(reinterpret_cast<std::uint8_t*>(this) + 0x484) = local_7fc;
        }
        break;
      }
      case 0x71: {
        float local_1cc;
        float local_1c8;
        float local_1c4;
        if ((instruction[3] & 4U) == 0) {
          local_1c4 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_1c4 = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_1c8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_1c8 = (float)fVar11;
        }
        if ((instruction[3] & 1U) == 0) {
          local_1cc = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_1cc = (float)fVar11;
        }
        Vector3 local_808(local_1cc,local_1c8,local_1c4);
        *reinterpret_cast<Vector3*>(reinterpret_cast<std::uint8_t*>(this) + 0x484) = local_808;
        break;
      }
      case 0x6c: {
        float local_1d4;
        float local_1d0;
        if ((instruction[3] & 1U) == 0) {
          local_1d0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_1d0 = (float)fVar11;
        }
        *(float *)((int)this + 0x80) = local_1d0;
        if ((instruction[3] & 2U) == 0) {
          local_1d4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_1d4 = (float)fVar11;
        }
        *(float *)((int)this + 0x84) = local_1d4;
        break;
      }
      case 0x6d: {
        std::uint32_t local_1d8;
        if ((instruction[3] & 1U) == 0) {
          local_1d8 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_1d8 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x4a2) =
             *(std::uint8_t *)((int)this + 0x4a2) & 0xe3 | ((std::uint8_t)local_1d8 & 7) << 2;
        break;
      }
      case 4: {
        std::uint32_t local_1dc;
        if ((instruction[3] & 1U) == 0) {
          local_1dc = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_1dc = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        timer_4c8.add_unscaled(static_cast<float>(-static_cast<std::int32_t>(local_1dc)));
        break;
      }
      case 3: {
        int local_610;
        int local_1e0;
        int local_dc;
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) & 0xfe;
switchD_0042b8cc_caseD_2:
        if (*(int *)((int)this + 0x438) == 0) {
          *(std::uint8_t *)((int)this + 0x4a1) = *(std::uint8_t *)((int)this + 0x4a1) | 1;
          timer_4c8--;
          goto LAB_00434dce;
        }
LAB_0042de0b:
        local_dc = 0;
        local_1e0 = 0;
        local_f0 = (short *)0x0;
        local_614 = (void *)reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_610 = *(int *)((int)this + 0x24);
        for (scan_instruction = reinterpret_cast<std::int16_t*>(FUN_00437490(local_614,local_610));
            ((*scan_instruction != 5 || (*(int *)((int)this + 0x438) != *(int *)(scan_instruction + 4))) &&
            (*scan_instruction != -1)); scan_instruction = (short *)((std::uint32_t)(std::uint16_t)scan_instruction[1] + (int)scan_instruction)) {
          if ((*scan_instruction == 5) && (*(int *)(scan_instruction + 4) == -1)) {
            local_f0 = scan_instruction;
            local_1e0 = local_dc;
          }
          local_dc = (std::uint32_t)(std::uint16_t)scan_instruction[1] + local_dc;
        }
        *(std::uint32_t *)((int)this + 0x438) = 0;
        *(std::uint8_t *)((int)this + 0x4a1) = *(std::uint8_t *)((int)this + 0x4a1) & 0xfe;
        if (*scan_instruction == 5) {
LAB_0042df8e:
          FUN_00429280(this,(int)this + 0x4c8);
          *(std::uint32_t *)((int)this + 0x10) = *(std::uint32_t *)((int)this + 0x28);
          local_dc = (std::uint32_t)(std::uint16_t)scan_instruction[1] + local_dc;
          FUN_00423520((void *)((int)this + 0x4c8),(int)scan_instruction[2]);
          scan_instruction = (short *)((std::uint32_t)(std::uint16_t)scan_instruction[1] + (int)scan_instruction);
          *(int *)((int)this + 0x28) = local_dc;
          *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) | 1;
          goto LAB_0042b831;
        }
        if (local_f0 != (short *)0x0) {
          scan_instruction = local_f0;
          local_dc = local_1e0;
          goto LAB_0042df8e;
        }
        if (*instruction == 3) goto code_r0x0042df46;
        goto LAB_0042b831;
      }
      case 2: {
        goto switchD_0042b8cc_caseD_2;
      }
      case 5: {
        FUN_00429280((void *)((int)this + 0x4c8),(int)this);
        *(std::uint32_t *)((int)this + 0x28) = *(std::uint32_t *)((int)this + 0x10);
        goto LAB_0042b831;
      }
      case 0x3e: {
        std::uint8_t local_cd;
        local_cd = (char)instruction[4] != '\0';
        *(std::uint8_t *)((int)this + 0x49a) = *(std::uint8_t *)((int)this + 0x49a) & 0xfe | local_cd;
        break;
      }
      case 0x5d: {
        *(std::uint32_t *)((int)this + 0x4a8) = (std::uint32_t)(std::uint16_t)instruction[4];
        *(std::uint32_t *)((int)this + 0x4ac) = (std::uint32_t)(std::uint16_t)instruction[5];
        break;
      }
      case 0x61: {
        float local_1e4;
        if ((instruction[3] & 1U) == 0) {
          local_1e4 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_1e4 = (float)fVar11;
        }
        *(float *)((int)this + 0x3a0) = local_1e4;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 0x80000;
        break;
      }
      case 0x62: {
        float local_1e8;
        if ((instruction[3] & 1U) == 0) {
          local_1e8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_1e8 = (float)fVar11;
        }
        *(float *)((int)this + 0x3a4) = local_1e8;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 0x80000;
        break;
      }
      case 0x39: {
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffffffef | (*(std::uint8_t *)(instruction + 4) & 1) << 4;
        break;
      }
      case 0x3a: {
        *(std::uint8_t *)((int)this + 0x4a1) =
             *(std::uint8_t *)((int)this + 0x4a1) & 0xfd | (*(std::uint8_t *)(instruction + 4) & 1) << 1;
        break;
      }
      case 0x3f: {
        *(std::uint8_t *)((int)this + 0x4a0) =
             *(std::uint8_t *)((int)this + 0x4a0) & 0xf3 | (*(std::uint8_t *)(instruction + 4) & 3) << 2;
        break;
      }
      case 0x4f: {
        float local_1f8;
        float local_1f4;
        float local_1f0;
        std::uint32_t local_1ec;
        local_61c = (void *)((int)this + 0x8c);
        if ((instruction[3] & 1U) == 0) {
          local_1ec = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_1ec = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438e70(local_61c,local_1ec);
        local_620 = (void *)((int)this + 0x8c);
        FUN_00439480(local_620,(std::uint32_t *)&DAT_0056e058);
        local_624 = (void *)((int)this + 0x8c);
        FUN_00438b20(local_624,(std::uint32_t *)&DAT_0056e058);
        local_628 = (void *)((int)this + 0x8c);
        FUN_004394f0(local_628,*(std::uint32_t *)(instruction + 6));
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 6 & 1) == 0) {
          local_62c = (void *)((int)this + 0x8c);
          FUN_004393f0(local_62c,(std::uint32_t *)((int)this + 0x2c));
        }
        else {
          local_630 = (void *)((int)this + 0x8c);
          FUN_004393f0(local_630,(std::uint32_t *)((int)this + 0x484));
        }
        local_634 = (void *)((int)this + 0x8c);
        if ((instruction[3] & 4U) == 0) {
          local_1f8 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_1f8 = (float)fVar11;
        }
        if ((instruction[3] & 8U) == 0) {
          local_1f4 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_1f4 = (float)fVar11;
        }
        if ((instruction[3] & 0x10U) == 0) {
          local_1f0 = *(float *)(instruction + 0xc);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0xc));
          local_1f0 = (float)fVar11;
        }
        Vector3 local_7cc(local_1f8,local_1f4,local_1f0);
        FUN_00438a90(local_634,&local_7cc);
        FUN_004396a0((int)this + 0x8c);
        break;
      }
      case 0x69: {
        float local_204;
        float local_200;
        std::uint32_t local_1fc;
        Vector3 local_b4;
        std::uint32_t local_ac;
        local_638 = (void *)((int)this + 0x8c);
        if ((instruction[3] & 1U) == 0) {
          local_1fc = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_1fc = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438e70(local_638,local_1fc);
        local_63c = (void *)((int)this + 0x8c);
        FUN_00439480(local_63c,(std::uint32_t *)&DAT_0056e058);
        local_640 = (void *)((int)this + 0x8c);
        FUN_00438b20(local_640,(std::uint32_t *)&DAT_0056e058);
        local_644 = (void *)((int)this + 0x8c);
        FUN_004394f0(local_644,*(std::uint32_t *)(instruction + 6));
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 6 & 1) == 0) {
          local_648 = (void *)((int)this + 0x8c);
          FUN_004393f0(local_648,(std::uint32_t *)((int)this + 0x2c));
        }
        else {
          local_64c = (void *)((int)this + 0x8c);
          FUN_004393f0(local_64c,(std::uint32_t *)((int)this + 0x484));
        }
        if ((instruction[3] & 8U) == 0) {
          local_200 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_200 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          this_local = (void *)0x8;
          local_204 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_204 = (float)fVar11;
          this_local = this;
        }
        polar(local_b4,local_204,local_200);
        local_ac = 0;
        local_650 = (void *)((int)this + 0x8c);
        FUN_00438a90(local_650,&local_b4);
        FUN_004396a0((int)this + 0x8c);
        break;
      }
      case 0x5c: {
        float local_21c;
        Vector3 local_90;
        Vector3 local_9c;
        float local_22c;
        float local_228;
        float local_224;
        std::uint32_t local_220;
        void* local_66c;
        void* local_668;
        void* local_664;
        void* local_660;
        void* local_65c;
        void* local_658;
        void* local_654;
        float local_218;
        float local_214;
        float local_210;
        float local_20c;
        float local_208;
        if ((instruction[3] & 2U) == 0) {
          local_208 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_208 = (float)fVar11;
        }
        local_90.x = local_208;
        if ((instruction[3] & 4U) == 0) {
          local_20c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_20c = (float)fVar11;
        }
        local_90.y = local_20c;
        if ((instruction[3] & 8U) == 0) {
          local_210 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_210 = (float)fVar11;
        }
        local_90.z = local_210;
        if ((instruction[3] & 0x80U) == 0) {
          local_214 = *(float *)(instruction + 0x12);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0x12));
          local_214 = (float)fVar11;
        }
        local_9c.x = local_214;
        if ((instruction[3] & 0x100U) == 0) {
          local_218 = *(float *)(instruction + 0x14);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0x14));
          local_218 = (float)fVar11;
        }
        local_9c.y = local_218;
        if ((instruction[3] & 0x200U) == 0) {
          local_21c = *(float *)(instruction + 0x16);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0x16));
          local_21c = (float)fVar11;
        }
        local_9c.z = local_21c;
        local_654 = (void *)((int)this + 0x8c);
        if ((instruction[3] & 1U) == 0) {
          local_220 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_220 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438e70(local_654,local_220);
        local_658 = (void *)((int)this + 0x8c);
        FUN_00439480(local_658,&local_90);
        local_65c = (void *)((int)this + 0x8c);
        FUN_00438b20(local_65c,&local_9c);
        local_660 = (void *)((int)this + 0x8c);
        FUN_004394f0(local_660,8);
        if ((*(std::uint32_t *)((int)this + 0x49c) >> 6 & 1) == 0) {
          local_664 = (void *)((int)this + 0x8c);
          FUN_004393f0(local_664,(std::uint32_t *)((int)this + 0x2c));
        }
        else {
          local_668 = (void *)((int)this + 0x8c);
          FUN_004393f0(local_668,(std::uint32_t *)((int)this + 0x484));
        }
        local_66c = (void *)((int)this + 0x8c);
        if ((instruction[3] & 0x10U) == 0) {
          local_22c = *(float *)(instruction + 0xc);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0xc));
          local_22c = (float)fVar11;
        }
        if ((instruction[3] & 0x20U) == 0) {
          local_228 = *(float *)(instruction + 0xe);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0xe));
          local_228 = (float)fVar11;
        }
        if ((instruction[3] & 0x40U) == 0) {
          local_224 = *(float *)(instruction + 0x10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0x10));
          local_224 = (float)fVar11;
        }
        Vector3 local_7d8(local_22c,local_228,local_224);
        FUN_00438a90(local_66c,&local_7d8);
        FUN_004396a0((int)this + 0x8c);
        break;
      }
      case 0x50: {
        std::uint32_t local_670;
        std::uint32_t local_23c;
        std::uint32_t local_238;
        std::uint32_t local_234;
        std::uint32_t local_230;
        Color3 local_70(*(std::uint8_t *)((int)this + 0x492),
                        *(std::uint8_t *)((int)this + 0x491),*(std::uint8_t *)((int)this + 0x490));
        if ((instruction[3] & 0x10U) == 0) {
          local_230 = *(std::uint32_t *)(instruction + 0xc);
        }
        else {
          local_230 = this->integer_value(*(std::uint32_t *)(instruction + 0xc));
        }
        if ((instruction[3] & 8U) == 0) {
          local_234 = *(std::uint32_t *)(instruction + 10);
        }
        else {
          local_234 = this->integer_value(*(std::uint32_t *)(instruction + 10));
        }
        if ((instruction[3] & 4U) == 0) {
          local_238 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_238 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        Color3 local_6c(static_cast<std::uint8_t>(local_238),static_cast<std::uint8_t>(local_234),
                        static_cast<std::uint8_t>(local_230));
        local_670 = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_23c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_23c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438d50(this,local_23c,local_670,local_70,local_6c);
        break;
      }
      case 0x51: {
        std::uint32_t local_674;
        std::uint32_t local_244;
        std::uint32_t local_240;
        std::uint8_t local_d0;
        if ((instruction[3] & 4U) == 0) {
          local_240 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_240 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        local_d0 = *(std::uint8_t *)((int)this + 0x493);
        local_674 = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_244 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_244 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438c60(this,local_244,local_674,local_d0,(std::uint8_t)local_240);
        break;
      }
      case 0x55: {
        std::uint32_t local_678;
        std::uint32_t local_254;
        std::uint32_t local_250;
        std::uint32_t local_24c;
        std::uint32_t local_248;
        Color3 local_78(*(std::uint8_t *)((int)this + 0x496),
                        *(std::uint8_t *)((int)this + 0x495),*(std::uint8_t *)((int)this + 0x494));
        if ((instruction[3] & 0x10U) == 0) {
          local_248 = *(std::uint32_t *)(instruction + 0xc);
        }
        else {
          local_248 = this->integer_value(*(std::uint32_t *)(instruction + 0xc));
        }
        if ((instruction[3] & 8U) == 0) {
          local_24c = *(std::uint32_t *)(instruction + 10);
        }
        else {
          local_24c = this->integer_value(*(std::uint32_t *)(instruction + 10));
        }
        if ((instruction[3] & 4U) == 0) {
          local_250 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_250 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        Color3 local_74(static_cast<std::uint8_t>(local_250),static_cast<std::uint8_t>(local_24c),
                        static_cast<std::uint8_t>(local_248));
        local_678 = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_254 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_254 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438cc0(this,local_254,local_678,local_78,local_74);
        break;
      }
      case 0x56: {
        std::uint32_t local_67c;
        std::uint32_t local_25c;
        std::uint32_t local_258;
        std::uint8_t local_d1;
        if ((instruction[3] & 4U) == 0) {
          local_258 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_258 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        local_d1 = *(std::uint8_t *)((int)this + 0x497);
        local_67c = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_25c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_25c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438bd0(this,local_25c,local_67c,local_d1,(std::uint8_t)local_258);
        break;
      }
      case 0x52: {
        float local_26c;
        float local_268;
        float local_264;
        std::uint32_t local_260;
        local_680 = (void *)((int)this + 0x160);
        if ((instruction[3] & 1U) == 0) {
          local_260 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_260 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438e70(local_680,local_260);
        local_684 = (void *)((int)this + 0x160);
        FUN_00439480(local_684,(std::uint32_t *)&DAT_0056e058);
        local_688 = (void *)((int)this + 0x160);
        FUN_00438b20(local_688,(std::uint32_t *)&DAT_0056e058);
        local_68c = (void *)((int)this + 0x160);
        FUN_004394f0(local_68c,*(std::uint32_t *)(instruction + 6));
        local_690 = (void *)((int)this + 0x160);
        FUN_004393f0(local_690,(std::uint32_t *)((int)this + 0x38));
        local_694 = (void *)((int)this + 0x160);
        if ((instruction[3] & 4U) == 0) {
          local_26c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_26c = (float)fVar11;
        }
        if ((instruction[3] & 8U) == 0) {
          local_268 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_268 = (float)fVar11;
        }
        if ((instruction[3] & 0x10U) == 0) {
          local_264 = *(float *)(instruction + 0xc);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 0xc));
          local_264 = (float)fVar11;
        }
        Vector3 local_7e4(local_26c,local_268,local_264);
        FUN_00438a90(local_694,&local_7e4);
        FUN_004396a0((int)this + 0x160);
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 2;
        break;
      }
      case 0x53: {
        float local_274;
        std::uint32_t local_270;
        local_698 = (void *)((int)this + 0x1b4);
        if ((instruction[3] & 1U) == 0) {
          local_270 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_270 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        base.interpolation_1b4.set_duration(local_270);
        local_69c = (void *)((int)this + 0x1b4);
        Angle local_7bc(0.0f);
        FUN_004394b0(local_69c,&local_7bc);
        local_6a0 = (void *)((int)this + 0x1b4);
        Angle local_7c0(0.0f);
        FUN_00438b50(local_6a0,&local_7c0);
        local_6a4 = (void *)((int)this + 0x1b4);
        FUN_004394d0(local_6a4,*(std::uint32_t *)(instruction + 6));
        local_6a8 = (void *)((int)this + 0x1b4);
        Angle local_788(*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0x40));
        FUN_00439440(local_6a8,&local_788);
        local_6ac = (void *)((int)this + 0x1b4);
        if ((instruction[3] & 4U) == 0) {
          local_274 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_274 = (float)fVar11;
        }
        Angle local_78c(local_274);
        FUN_00438ae0(local_6ac,&local_78c);
        FUN_004395b0((int)this + 0x1b4);
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 2;
        break;
      }
      case 0x54: {
        std::uint32_t local_6b4;
        std::uint32_t local_280;
        float local_27c;
        float local_278;
        if ((instruction[3] & 4U) == 0) {
          local_27c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_27c = (float)fVar11;
        }
        if ((instruction[3] & 8U) == 0) {
          local_278 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_278 = (float)fVar11;
        }
        Vector2 local_794(local_27c,local_278);
        local_6b0 = (std::uint32_t *)((int)this + 0x50);
        local_6b4 = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_280 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_280 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438df0(this,local_280,local_6b4,local_6b0,&local_794);
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x6b: {
        std::uint32_t local_6bc;
        std::uint32_t local_28c;
        float local_288;
        float local_284;
        if ((instruction[3] & 4U) == 0) {
          local_288 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_288 = (float)fVar11;
        }
        if ((instruction[3] & 8U) == 0) {
          local_284 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_284 = (float)fVar11;
        }
        Vector2 local_79c(local_288,local_284);
        local_6b8 = (std::uint32_t *)((int)this + 0x58);
        local_6bc = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_28c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_28c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438db0(this,local_28c,local_6bc,local_6b8,&local_79c);
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 4;
        break;
      }
      case 0x66: {
        std::uint32_t local_6c4;
        std::uint32_t local_298;
        float local_294;
        float local_290;
        if ((instruction[3] & 4U) == 0) {
          local_294 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_294 = (float)fVar11;
        }
        if ((instruction[3] & 8U) == 0) {
          local_290 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_290 = (float)fVar11;
        }
        Vector2 local_7a4(local_294,local_290);
        local_6c0 = (std::uint32_t *)((int)this + 0x68);
        local_6c4 = (std::uint32_t)*(std::uint8_t *)(instruction + 6);
        if ((instruction[3] & 1U) == 0) {
          local_298 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_298 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_00438e30(this,local_298,local_6c4,local_6c0,&local_7a4);
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 8;
        break;
      }
      case 99: {
        float local_768;
        std::uint32_t local_6d4;
        std::uint32_t local_6cc;
        float local_2a0;
        std::uint32_t local_29c;
        local_6c8 = (void *)((int)this + 800);
        if ((instruction[3] & 1U) == 0) {
          local_29c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_29c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        base.interpolation_320.set_duration(local_29c);
        local_6d0 = (void *)((int)this + 800);
        local_6cc = 0;
        FUN_00439460(local_6d0,&local_6cc);
        local_6d8 = (void *)((int)this + 800);
        local_6d4 = 0;
        FUN_00438b00(local_6d8,&local_6d4);
        local_6dc = (void *)((int)this + 800);
        FUN_004394d0(local_6dc,*(std::uint32_t *)(instruction + 6));
        local_6e0 = (void *)((int)this + 800);
        FUN_004393d0(local_6e0,(std::uint32_t *)((int)this + 0x3a0));
        local_6e8 = (void *)((int)this + 800);
        if ((instruction[3] & 4U) == 0) {
          local_2a0 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_2a0 = (float)fVar11;
        }
        local_768 = local_2a0;
        FUN_00438a70(local_6e8,&local_768);
        FUN_004395b0((int)this + 800);
        break;
      }
      case 100: {
        float local_708;
        std::uint32_t local_6f8;
        std::uint32_t local_6f0;
        float local_2a8;
        std::uint32_t local_2a4;
        local_6ec = (void *)((int)this + 0x34c);
        if ((instruction[3] & 1U) == 0) {
          local_2a4 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2a4 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        base.interpolation_34c.set_duration(local_2a4);
        local_6f4 = (void *)((int)this + 0x34c);
        local_6f0 = 0;
        FUN_00439460(local_6f4,&local_6f0);
        local_6fc = (void *)((int)this + 0x34c);
        local_6f8 = 0;
        FUN_00438b00(local_6fc,&local_6f8);
        local_700 = (void *)((int)this + 0x34c);
        FUN_004394d0(local_700,*(std::uint32_t *)(instruction + 6));
        local_704 = (void *)((int)this + 0x34c);
        FUN_004393d0(local_704,(std::uint32_t *)((int)this + 0x3a4));
        local_70c = (void *)((int)this + 0x34c);
        if ((instruction[3] & 4U) == 0) {
          local_2a8 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_2a8 = (float)fVar11;
        }
        local_708 = local_2a8;
        FUN_00438a70(local_70c,&local_708);
        FUN_004395b0((int)this + 0x34c);
        break;
      }
      case 0x36: {
        *(char *)((int)this + 0x498) = (char)instruction[4];
        *(std::uint8_t *)((int)this + 0x4a0) = *(std::uint8_t *)((int)this + 0x4a0) & 0xcf;
        break;
      }
      case 0x5e: {
        *(std::uint32_t *)((int)this + 0x2c) = *(std::uint32_t *)((int)this + 0x5bc);
        *(std::uint32_t *)((int)this + 0x30) = *(std::uint32_t *)((int)this + 0x5c0);
        *(std::uint32_t *)((int)this + 0x34) = *(std::uint32_t *)((int)this + 0x5c4);
        *(std::uint32_t *)((int)this + 0x5bc) = 0;
        *(std::uint32_t *)((int)this + 0x5c0) = 0;
        *(std::uint32_t *)((int)this + 0x5c4) = 0;
        break;
      }
      case 0x7d: {
        std::uint32_t local_2ac;
        *(std::uint8_t *)((int)this + 0x498) = 9;
        if ((instruction[3] & 1U) == 0) {
          local_2ac = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2ac = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2ac * 0x38);
        break;
      }
      case 0x9e: {
        std::uint32_t local_2b4;
        std::uint32_t local_2b0;
        *(std::uint8_t *)((int)this + 0x498) = 0x2f;
        if ((instruction[3] & 1U) == 0) {
          local_2b0 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2b0 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2b0 * 0x38);
        if ((instruction[3] & 1U) == 0) {
          local_2b4 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2b4 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_2b4;
        break;
      }
      case 0x9f: {
        float local_2b8;
        *(std::uint8_t *)((int)this + 0x498) = 0x30;
        FUN_0042b590(this,0x54);
        if ((instruction[3] & 1U) == 0) {
          local_2b8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2b8 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_2b8;
        break;
      }
      case 0x7e: {
        std::uint32_t local_2bc;
        *(std::uint8_t *)((int)this + 0x498) = 0xd;
        if ((instruction[3] & 1U) == 0) {
          local_2bc = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2bc = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2bc * 0x38);
        break;
      }
      case 0x7f: {
        std::uint32_t local_2c0;
        *(std::uint8_t *)((int)this + 0x498) = 0xe;
        if ((instruction[3] & 1U) == 0) {
          local_2c0 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2c0 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2c0 * 0x38);
        break;
      }
      case 0x86: {
        std::uint32_t local_2c4;
        *(std::uint8_t *)((int)this + 0x498) = 0x18;
        if ((instruction[3] & 1U) == 0) {
          local_2c4 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2c4 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2c4 * 0x30);
        break;
      }
      case 0x87: {
        std::uint32_t local_2c8;
        *(std::uint8_t *)((int)this + 0x498) = 0x19;
        if ((instruction[3] & 1U) == 0) {
          local_2c8 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2c8 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        FUN_0042b590(this,local_2c8 * 0x30);
        break;
      }
      case 0x5a: {
        Vector3 corners[4];
        FUN_00445770(this,corners);
        normalize_coordinates_438eb0(&base.vectors_378[0],reinterpret_cast<const Vector2*>(&corners[0]));
        normalize_coordinates_438eb0(&base.vectors_378[1],reinterpret_cast<const Vector2*>(&corners[1]));
        normalize_coordinates_438eb0(&base.vectors_378[2],reinterpret_cast<const Vector2*>(&corners[2]));
        normalize_coordinates_438eb0(&base.vectors_378[3],reinterpret_cast<const Vector2*>(&corners[3]));
        base.vector_398.x=base.vectors_378[1].x-base.vectors_378[0].x;
        base.vector_398.y=base.vectors_378[1].y-base.vectors_378[0].y;
        break;
      }
      case 0x5b: {
        std::uint32_t local_2cc;
        if ((instruction[3] & 1U) == 0) {
          local_2cc = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_2cc = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xfffff7ff | (local_2cc & 1) << 0xb;
        break;
      }
      case 0x80: {
        float local_2d4;
        float local_2d0;
        *(std::uint8_t *)((int)this + 0x498) = 0x10;
        if ((instruction[3] & 1U) == 0) {
          local_2d0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2d0 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2d0;
        if ((instruction[3] & 2U) == 0) {
          local_2d4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2d4 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2d4;
        break;
      }
      case 0x83: {
        float local_2dc;
        float local_2d8;
        *(std::uint8_t *)((int)this + 0x498) = 0x14;
        if ((instruction[3] & 1U) == 0) {
          local_2d8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2d8 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2d8;
        if ((instruction[3] & 2U) == 0) {
          local_2dc = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2dc = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2dc;
        break;
      }
      case 0x84: {
        float local_2e4;
        float local_2e0;
        *(std::uint8_t *)((int)this + 0x498) = 0x15;
        if ((instruction[3] & 1U) == 0) {
          local_2e0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2e0 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2e0;
        if ((instruction[3] & 2U) == 0) {
          local_2e4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2e4 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2e4;
        break;
      }
      case 0x85: {
        float local_2ec;
        float local_2e8;
        *(std::uint8_t *)((int)this + 0x498) = 0x16;
        if ((instruction[3] & 1U) == 0) {
          local_2e8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2e8 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2e8;
        if ((instruction[3] & 2U) == 0) {
          local_2ec = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2ec = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2ec;
        break;
      }
      case 0x8a: {
        float local_2f4;
        float local_2f0;
        *(std::uint8_t *)((int)this + 0x498) = 0x1a;
        if ((instruction[3] & 1U) == 0) {
          local_2f0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2f0 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2f0;
        if ((instruction[3] & 2U) == 0) {
          local_2f4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2f4 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2f4;
        break;
      }
      case 0x89: {
        float local_2fc;
        float local_2f8;
        *(std::uint8_t *)((int)this + 0x498) = 0x1b;
        if ((instruction[3] & 1U) == 0) {
          local_2f8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_2f8 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_2f8;
        if ((instruction[3] & 2U) == 0) {
          local_2fc = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_2fc = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_2fc;
        break;
      }
      case 0x81: {
        std::uint32_t local_304;
        float local_300;
        *(std::uint8_t *)((int)this + 0x498) = 0x11;
        if ((instruction[3] & 1U) == 0) {
          local_300 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_300 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_300;
        if ((instruction[3] & 2U) == 0) {
          local_304 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_304 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_304;
        break;
      }
      case 0x94: {
        std::uint32_t local_314;
        float local_310;
        float local_30c;
        float local_308;
        *(std::uint8_t *)((int)this + 0x498) = 0x25;
        if ((instruction[3] & 1U) == 0) {
          local_308 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_308 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_308;
        if ((instruction[3] & 2U) == 0) {
          local_30c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_30c = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_30c;
        if ((instruction[3] & 4U) == 0) {
          local_310 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_310 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_310;
        if ((instruction[3] & 8U) == 0) {
          local_314 = *(std::uint32_t *)(instruction + 10);
        }
        else {
          local_314 = this->integer_value(*(std::uint32_t *)(instruction + 10));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_314;
        break;
      }
      case 0x95: {
        std::uint32_t local_324;
        float local_320;
        float local_31c;
        float local_318;
        *(std::uint8_t *)((int)this + 0x498) = 0x26;
        if ((instruction[3] & 1U) == 0) {
          local_318 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_318 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_318;
        if ((instruction[3] & 2U) == 0) {
          local_31c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_31c = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_31c;
        if ((instruction[3] & 4U) == 0) {
          local_320 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_320 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_320;
        if ((instruction[3] & 8U) == 0) {
          local_324 = *(std::uint32_t *)(instruction + 10);
        }
        else {
          local_324 = this->integer_value(*(std::uint32_t *)(instruction + 10));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_324;
        break;
      }
      case 0x96: {
        std::uint32_t local_338;
        float local_334;
        float local_330;
        float local_32c;
        float local_328;
        *(std::uint8_t *)((int)this + 0x498) = 0x27;
        if ((instruction[3] & 1U) == 0) {
          local_328 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_328 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_328;
        if ((instruction[3] & 2U) == 0) {
          local_32c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_32c = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_32c;
        if ((instruction[3] & 4U) == 0) {
          local_330 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_330 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_330;
        if ((instruction[3] & 8U) == 0) {
          local_334 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_334 = (float)fVar11;
        }
        *(float *)((int)this + 0x458) = local_334;
        if ((instruction[3] & 0x10U) == 0) {
          local_338 = *(std::uint32_t *)(instruction + 0xc);
        }
        else {
          local_338 = this->integer_value(*(std::uint32_t *)(instruction + 0xc));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_338;
        break;
      }
      case 0x97: {
        std::uint32_t local_34c;
        float local_348;
        float local_344;
        float local_340;
        float local_33c;
        *(std::uint8_t *)((int)this + 0x498) = 0x28;
        if ((instruction[3] & 1U) == 0) {
          local_33c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_33c = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_33c;
        if ((instruction[3] & 2U) == 0) {
          local_340 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_340 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_340;
        if ((instruction[3] & 4U) == 0) {
          local_344 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_344 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_344;
        if ((instruction[3] & 8U) == 0) {
          local_348 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_348 = (float)fVar11;
        }
        *(float *)((int)this + 0x458) = local_348;
        if ((instruction[3] & 0x10U) == 0) {
          local_34c = *(std::uint32_t *)(instruction + 0xc);
        }
        else {
          local_34c = this->integer_value(*(std::uint32_t *)(instruction + 0xc));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_34c;
        break;
      }
      case 0x98: {
        std::uint32_t local_360;
        float local_35c;
        float local_358;
        float local_354;
        float local_350;
        *(std::uint8_t *)((int)this + 0x498) = 0x29;
        if ((instruction[3] & 1U) == 0) {
          local_350 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_350 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_350;
        if ((instruction[3] & 2U) == 0) {
          local_354 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_354 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_354;
        if ((instruction[3] & 4U) == 0) {
          local_358 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_358 = (float)fVar11;
        }
        *(float *)((int)this + 0x454) = local_358;
        if ((instruction[3] & 8U) == 0) {
          local_35c = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_35c = (float)fVar11;
        }
        *(float *)((int)this + 0x458) = local_35c;
        if ((instruction[3] & 0x10U) == 0) {
          local_360 = *(std::uint32_t *)(instruction + 0xc);
        }
        else {
          local_360 = this->integer_value(*(std::uint32_t *)(instruction + 0xc));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_360;
        break;
      }
      case 0x82: {
        std::uint32_t local_368;
        float local_364;
        *(std::uint8_t *)((int)this + 0x498) = 0x12;
        if ((instruction[3] & 1U) == 0) {
          local_364 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_364 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_364;
        if ((instruction[3] & 2U) == 0) {
          local_368 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_368 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_368;
        break;
      }
      case 0x88: {
        std::uint32_t local_374;
        float local_370;
        float local_36c;
        *(std::uint8_t *)((int)this + 0x498) = 0x13;
        if ((instruction[3] & 1U) == 0) {
          local_36c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_36c = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_36c;
        if ((instruction[3] & 2U) == 0) {
          local_370 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_370 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_370;
        if ((instruction[3] & 4U) == 0) {
          local_374 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_374 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_374;
        break;
      }
      case 0x8c: {
        std::uint32_t local_380;
        float local_37c;
        float local_378;
        *(std::uint8_t *)((int)this + 0x498) = 0x1d;
        if ((instruction[3] & 1U) == 0) {
          local_378 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_378 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_378;
        if ((instruction[3] & 2U) == 0) {
          local_37c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_37c = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_37c;
        if ((instruction[3] & 4U) == 0) {
          local_380 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_380 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_380;
        break;
      }
      case 0x8d: {
        std::uint32_t local_38c;
        float local_388;
        float local_384;
        *(std::uint8_t *)((int)this + 0x498) = 0x1e;
        if ((instruction[3] & 1U) == 0) {
          local_384 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_384 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_384;
        if ((instruction[3] & 2U) == 0) {
          local_388 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_388 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_388;
        if ((instruction[3] & 4U) == 0) {
          local_38c = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_38c = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_38c;
        break;
      }
      case 0x8e: {
        std::uint32_t local_394;
        float local_390;
        *(std::uint8_t *)((int)this + 0x498) = 0x1f;
        if ((instruction[3] & 1U) == 0) {
          local_390 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_390 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_390;
        if ((instruction[3] & 2U) == 0) {
          local_394 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_394 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_394;
        break;
      }
      case 0x90: {
        std::uint32_t local_39c;
        float local_398;
        *(std::uint8_t *)((int)this + 0x498) = 0x21;
        if ((instruction[3] & 1U) == 0) {
          local_398 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_398 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_398;
        if ((instruction[3] & 2U) == 0) {
          local_39c = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_39c = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_39c;
        break;
      }
      case 0x91: {
        std::uint32_t local_3a8;
        float local_3a4;
        float local_3a0;
        *(std::uint8_t *)((int)this + 0x498) = 0x22;
        if ((instruction[3] & 1U) == 0) {
          local_3a0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3a0 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3a0;
        if ((instruction[3] & 2U) == 0) {
          local_3a4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3a4 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3a4;
        if ((instruction[3] & 4U) == 0) {
          local_3a8 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3a8 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3a8;
        break;
      }
      case 0x92: {
        std::uint32_t local_3b4;
        float local_3b0;
        float local_3ac;
        *(std::uint8_t *)((int)this + 0x498) = 0x23;
        if ((instruction[3] & 1U) == 0) {
          local_3ac = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3ac = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3ac;
        if ((instruction[3] & 2U) == 0) {
          local_3b0 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3b0 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3b0;
        if ((instruction[3] & 4U) == 0) {
          local_3b4 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3b4 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3b4;
        break;
      }
      case 0x93: {
        std::uint32_t local_3c0;
        float local_3bc;
        float local_3b8;
        *(std::uint8_t *)((int)this + 0x498) = 0x24;
        if ((instruction[3] & 1U) == 0) {
          local_3b8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3b8 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3b8;
        if ((instruction[3] & 2U) == 0) {
          local_3bc = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3bc = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3bc;
        if ((instruction[3] & 4U) == 0) {
          local_3c0 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3c0 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3c0;
        break;
      }
      case 0x99: {
        std::uint32_t local_3c8;
        float local_3c4;
        *(std::uint8_t *)((int)this + 0x498) = 0x2a;
        if ((instruction[3] & 1U) == 0) {
          local_3c4 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3c4 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3c4;
        if ((instruction[3] & 2U) == 0) {
          local_3c8 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_3c8 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3c8 << 1;
        break;
      }
      case 0x9a: {
        std::uint32_t local_3d0;
        float local_3cc;
        *(std::uint8_t *)((int)this + 0x498) = 0x2b;
        if ((instruction[3] & 1U) == 0) {
          local_3cc = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3cc = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3cc;
        if ((instruction[3] & 2U) == 0) {
          local_3d0 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_3d0 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3d0 << 1;
        break;
      }
      case 0x9b: {
        std::uint32_t local_3dc;
        float local_3d8;
        float local_3d4;
        *(std::uint8_t *)((int)this + 0x498) = 0x2c;
        if ((instruction[3] & 1U) == 0) {
          local_3d4 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3d4 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3d4;
        if ((instruction[3] & 2U) == 0) {
          local_3d8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3d8 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3d8;
        if ((instruction[3] & 4U) == 0) {
          local_3dc = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3dc = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3dc << 1;
        break;
      }
      case 0x9c: {
        std::uint32_t local_3e8;
        float local_3e4;
        float local_3e0;
        *(std::uint8_t *)((int)this + 0x498) = 0x2d;
        if ((instruction[3] & 1U) == 0) {
          local_3e0 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3e0 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3e0;
        if ((instruction[3] & 2U) == 0) {
          local_3e4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3e4 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3e4;
        if ((instruction[3] & 4U) == 0) {
          local_3e8 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3e8 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3e8 << 1;
        break;
      }
      case 0x9d: {
        std::uint32_t local_3f4;
        float local_3f0;
        float local_3ec;
        *(std::uint8_t *)((int)this + 0x498) = 0x2e;
        if ((instruction[3] & 1U) == 0) {
          local_3ec = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3ec = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3ec;
        if ((instruction[3] & 2U) == 0) {
          local_3f0 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3f0 = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3f0;
        if ((instruction[3] & 4U) == 0) {
          local_3f4 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_3f4 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        *(std::uint32_t *)((int)this + 0x444) = local_3f4 << 1;
        break;
      }
      case 0x8b: {
        float local_3fc;
        float local_3f8;
        *(std::uint8_t *)((int)this + 0x498) = 0x1c;
        if ((instruction[3] & 1U) == 0) {
          local_3f8 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_3f8 = (float)fVar11;
        }
        *(float *)((int)this + 0x70) = local_3f8;
        if ((instruction[3] & 2U) == 0) {
          local_3fc = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_3fc = (float)fVar11;
        }
        *(float *)((int)this + 0x74) = local_3fc;
        break;
      }
      case 0x8f: {
        *(std::uint8_t *)((int)this + 0x498) = 0x20;
        break;
      }
      case 0x79: {
        std::uint32_t local_400;
        if ((instruction[3] & 1U) == 0) {
          local_400 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_400 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffffefff | (local_400 & 1) << 0xc;
        break;
      }
      case 0x40: {
        std::uint32_t local_408;
        std::uint32_t local_404;
        if ((instruction[3] & 1U) == 0) {
          local_404 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_404 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x4a2) =
             *(std::uint8_t *)((int)this + 0x4a2) & 0xfc | (std::uint8_t)local_404 & 3;
        if ((instruction[3] & 2U) == 0) {
          local_408 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_408 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        *(std::uint8_t *)((int)this + 0x4a1) =
             *(std::uint8_t *)((int)this + 0x4a1) & 0x9f | ((std::uint8_t)local_408 & 3) << 5;
        break;
      }
      case 0x41: {
        std::uint32_t local_40c;
        if ((instruction[3] & 1U) == 0) {
          local_40c = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_40c = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint8_t *)((int)this + 0x4a4) = (std::uint8_t)local_40c;
        *(std::uint32_t *)((int)this + 0x49c) = *(std::uint32_t *)((int)this + 0x49c) | 0x800000;
        break;
      }
      case 0x42: {
        std::uint32_t local_410;
        if ((instruction[3] & 1U) == 0) {
          local_410 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_410 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffffffdf | (local_410 & 1) << 5;
        break;
      }
      case 0x46: {
        std::uint32_t local_414;
        if ((instruction[3] & 1U) == 0) {
          local_414 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_414 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffbfffff | (local_414 & 1) << 0x16;
        break;
      }
      case 6: {
        std::uint32_t local_418;
        if ((instruction[3] & 2U) == 0) {
          local_418 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_418 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        puVar8 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *puVar8 = local_418;
        break;
      }
      case 7: {
        float local_41c;
        if ((instruction[3] & 2U) == 0) {
          local_41c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_41c = (float)fVar11;
        }
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_41c;
        break;
      }
      case 0x12: {
        std::uint32_t local_424;
        std::uint32_t local_420;
        if ((instruction[3] & 2U) == 0) {
          local_420 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_420 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((instruction[3] & 4U) == 0) {
          local_424 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_424 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        iVar2 = local_420 + local_424;
        piVar7 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *piVar7 = iVar2;
        break;
      }
      case 0x13: {
        float local_710;
        float local_42c;
        float local_428;
        if ((instruction[3] & 2U) == 0) {
          local_428 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_428 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_42c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_42c = (float)fVar11;
        }
        local_710 = local_428 + local_42c;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_710;
        break;
      }
      case 0x14: {
        std::uint32_t local_434;
        std::uint32_t local_430;
        if ((instruction[3] & 2U) == 0) {
          local_430 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_430 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((instruction[3] & 4U) == 0) {
          local_434 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_434 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        iVar2 = local_430 - local_434;
        piVar7 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *piVar7 = iVar2;
        break;
      }
      case 0x15: {
        float local_714;
        float local_43c;
        float local_438;
        if ((instruction[3] & 2U) == 0) {
          local_438 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_438 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_43c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_43c = (float)fVar11;
        }
        local_714 = local_438 - local_43c;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_714;
        break;
      }
      case 0x16: {
        std::uint32_t local_444;
        std::uint32_t local_440;
        if ((instruction[3] & 2U) == 0) {
          local_440 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_440 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((instruction[3] & 4U) == 0) {
          local_444 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_444 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        iVar2 = local_440 * local_444;
        piVar7 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *piVar7 = iVar2;
        break;
      }
      case 0x17: {
        float local_718;
        float local_44c;
        float local_448;
        if ((instruction[3] & 2U) == 0) {
          local_448 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_448 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_44c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_44c = (float)fVar11;
        }
        local_718 = local_448 * local_44c;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_718;
        break;
      }
      case 0x18: {
        std::uint32_t local_454;
        std::uint32_t local_450;
        if ((instruction[3] & 2U) == 0) {
          local_450 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_450 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((instruction[3] & 4U) == 0) {
          local_454 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_454 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        iVar2 = (int)local_450 / (int)local_454;
        piVar7 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *piVar7 = iVar2;
        break;
      }
      case 0x19: {
        float local_71c;
        float local_45c;
        float local_458;
        if ((instruction[3] & 2U) == 0) {
          local_458 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_458 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_45c = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_45c = (float)fVar11;
        }
        local_71c = local_458 / local_45c;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_71c;
        break;
      }
      case 0x1a: {
        std::uint32_t local_464;
        std::uint32_t local_460;
        if ((instruction[3] & 2U) == 0) {
          local_460 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_460 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((instruction[3] & 4U) == 0) {
          local_464 = *(std::uint32_t *)(instruction + 8);
        }
        else {
          local_464 = this->integer_value(*(std::uint32_t *)(instruction + 8));
        }
        iVar2 = (int)local_460 % (int)local_464;
        piVar7 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *piVar7 = iVar2;
        break;
      }
      case 0x1b: {
        float local_720;
        float local_46c;
        float local_468;
        if ((instruction[3] & 4U) == 0) {
          local_468 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_468 = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_46c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_46c = (float)fVar11;
        }
        fVar11 = FUN_004397f0(local_46c,local_468);
        local_720 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_720;
        break;
      }
      case 8: {
        std::uint32_t local_470;
        if ((instruction[3] & 2U) == 0) {
          local_470 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_470 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_474 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_474 = *local_474 + local_470;
        break;
      }
      case 9: {
        float local_478;
        if ((instruction[3] & 2U) == 0) {
          local_478 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_478 = (float)fVar11;
        }
        local_47c = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_47c = *local_47c + local_478;
        break;
      }
      case 10: {
        std::uint32_t local_480;
        if ((instruction[3] & 2U) == 0) {
          local_480 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_480 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_484 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_484 = *local_484 - local_480;
        break;
      }
      case 0xb: {
        float local_488;
        if ((instruction[3] & 2U) == 0) {
          local_488 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_488 = (float)fVar11;
        }
        local_48c = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_48c = *local_48c - local_488;
        break;
      }
      case 0xc: {
        std::uint32_t local_490;
        if ((instruction[3] & 2U) == 0) {
          local_490 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_490 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_494 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_494 = *local_494 * local_490;
        break;
      }
      case 0xd: {
        float local_498;
        if ((instruction[3] & 2U) == 0) {
          local_498 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_498 = (float)fVar11;
        }
        local_49c = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_49c = *local_49c * local_498;
        break;
      }
      case 0xe: {
        std::uint32_t local_4a0;
        if ((instruction[3] & 2U) == 0) {
          local_4a0 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_4a0 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_4a4 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_4a4 = *local_4a4 / (int)local_4a0;
        break;
      }
      case 0xf: {
        float local_4a8;
        if ((instruction[3] & 2U) == 0) {
          local_4a8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4a8 = (float)fVar11;
        }
        local_4ac = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_4ac = *local_4ac / local_4a8;
        break;
      }
      case 0x10: {
        std::uint32_t local_4b0;
        if ((instruction[3] & 2U) == 0) {
          local_4b0 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_4b0 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_4b4 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *local_4b4 = *local_4b4 % (int)local_4b0;
        break;
      }
      case 0x11: {
        float local_724;
        float local_4bc;
        float local_4b8;
        if ((instruction[3] & 2U) == 0) {
          local_4b8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4b8 = (float)fVar11;
        }
        if ((instruction[3] & 1U) == 0) {
          local_4bc = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_4bc = (float)fVar11;
        }
        fVar11 = FUN_004397f0(local_4bc,local_4b8);
        local_724 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_724;
        break;
      }
      case 0x1c: {
        std::uint32_t local_728;
        std::uint32_t local_4c0;
        if ((instruction[3] & 2U) == 0) {
          local_4c0 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_4c0 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        local_728 = FUN_00423ea0(&DAT_005ba4c4,local_4c0);
        puVar8 = this->integer_argument(reinterpret_cast<std::int32_t*>((std::uint32_t *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *puVar8 = local_728;
        break;
      }
      case 0x1d: {
        float local_72c;
        float local_4c4;
        if ((instruction[3] & 2U) == 0) {
          local_4c4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4c4 = (float)fVar11;
        }
        fVar11 = FUN_00429800(0x5ba4c4,local_4c4);
        local_72c = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_72c;
        break;
      }
      case 0x1e: {
        float local_730;
        float local_4c8;
        if ((instruction[3] & 2U) == 0) {
          local_4c8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4c8 = (float)fVar11;
        }
        fVar11 = scalar_math::sine(local_4c8);
        local_730 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_730;
        break;
      }
      case 0x1f: {
        float local_734;
        float local_4cc;
        if ((instruction[3] & 2U) == 0) {
          local_4cc = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4cc = (float)fVar11;
        }
        fVar11 = scalar_math::cosine(local_4cc);
        local_734 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_734;
        break;
      }
      case 0x20: {
        float local_738;
        float local_4d0;
        if ((instruction[3] & 2U) == 0) {
          local_4d0 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4d0 = (float)fVar11;
        }
        fVar11 = native_sqrt_439850(local_4d0);
        local_738 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_738;
        break;
      }
      case 0x21: {
        float local_73c;
        float local_4d4;
        if ((instruction[3] & 2U) == 0) {
          local_4d4 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4d4 = (float)fVar11;
        }
        fVar11 = scalar_math::arcsine(local_4d4);
        local_73c = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_73c;
        break;
      }
      case 0x22: {
        float local_740;
        float local_4d8;
        if ((instruction[3] & 2U) == 0) {
          local_4d8 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_4d8 = (float)fVar11;
        }
        fVar11 = scalar_math::arccosine(local_4d8);
        local_740 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_740;
        break;
      }
      case 0x23: {
        float local_744;
        float local_4dc;
        if ((instruction[3] & 1U) == 0) {
          local_4dc = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_4dc = (float)fVar11;
        }
        fVar11 = (float)FUN_00438600(local_4dc,0.0f);
        local_744 = (float)fVar11;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_744;
        break;
      }
      case 0x24: {
        float local_4e4;
        float local_4e0;
        if ((instruction[3] & 8U) == 0) {
          local_4e0 = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_4e0 = (float)fVar11;
        }
        if ((instruction[3] & 4U) == 0) {
          local_4e4 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_4e4 = (float)fVar11;
        }
        local_748 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 6)),static_cast<std::uint16_t>(instruction[3]),1);
        local_74c = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        polar_components(local_74c,local_748,local_4e4,local_4e0);
        break;
      }
      case 0x25: {
        float local_760;
        float local_75c;
        float local_758;
        float local_754;
        float local_750;
        float local_4f0;
        float local_4ec;
        float local_4e8;
        Vector3 local_c0;
        if ((instruction[3] & 4U) == 0) {
          local_4e8 = *(float *)(instruction + 8);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 8));
          local_4e8 = (float)fVar11;
        }
        local_4f0 = local_4e8;
        if ((instruction[3] & 8U) == 0) {
          local_4ec = *(float *)(instruction + 10);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 10));
          local_4ec = (float)fVar11;
        }
        local_750 = local_4ec;
        local_754 = local_4ec - local_4f0;
        fVar11 = FUN_004298e0(0x5ba4c4);
        local_758 = (float)fVar11;
        local_75c = local_754 * local_758 + local_4f0;
        fVar11 = FUN_004297d0(0x5ba4c4);
        local_760 = (float)fVar11;
        polar(*reinterpret_cast<Vector3*>(&local_c0),local_760,local_75c);
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 4)),static_cast<std::uint16_t>(instruction[3]),0);
        *pfVar6 = local_c0.x;
        pfVar6 = this->float_argument(reinterpret_cast<float*>((float *)(instruction + 6)),static_cast<std::uint16_t>(instruction[3]),1);
        *pfVar6 = local_c0.y;
        break;
      }
      case 0x6e: {
        *(std::uint8_t *)((int)this + 0x4a3) =
             *(std::uint8_t *)((int)this + 0x4a3) & 0xfc | *(std::uint8_t *)(instruction + 4) & 3;
        break;
      }
      case 0x67: {
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xffffff7f | (*(std::uint8_t *)(instruction + 4) & 1) << 7;
        break;
      }
      case 0x38: {
        FUN_00450350(this,(std::uint32_t)*(std::uint8_t *)(instruction + 4));
        break;
      }
      case 0x5f: {
        *(std::uint8_t *)((int)this + 0x4a1) =
             *(std::uint8_t *)((int)this + 0x4a1) & 0xe3 | (*(std::uint8_t *)(instruction + 4) & 7) << 2;
        break;
      }
      case 0x60: {
        *(std::uint8_t *)((int)this + 0x4a2) =
             *(std::uint8_t *)((int)this + 0x4a2) & 0x1f | (char)instruction[4] << 5;
        break;
      }
      case 0x3b: {
        *(std::uint32_t *)((int)this + 0x49c) =
             *(std::uint32_t *)((int)this + 0x49c) & 0xfffffdff | (*(std::uint8_t *)(instruction + 4) & 1) << 9;
        break;
      }
      case 0x28: {
        std::uint32_t local_4f8;
        std::uint32_t local_4f4;
        if ((instruction[3] & 1U) == 0) {
          local_4f4 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_4f4 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_4f8 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_4f8 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if (local_4f4 == local_4f8) {
LAB_00434d6a:
          FUN_00423520((void *)((int)this + 0x4c8),*(int *)(instruction + 10));
          *(std::uint32_t *)((int)this + 0x28) = *(std::uint32_t *)(instruction + 8);
          goto LAB_0042b831;
        }
        break;
      }
      case 0x29: {
        float local_500;
        float local_4fc;
        if ((instruction[3] & 1U) == 0) {
          local_4fc = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_4fc = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_500 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_500 = (float)fVar11;
        }
        if (local_4fc == local_500) goto LAB_00434d6a;
        break;
      }
      case 0x2a: {
        std::uint32_t local_508;
        std::uint32_t local_504;
        if ((instruction[3] & 1U) == 0) {
          local_504 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_504 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_508 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_508 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if (local_504 != local_508) goto LAB_00434d6a;
        break;
      }
      case 0x2b: {
        float local_510;
        float local_50c;
        if ((instruction[3] & 1U) == 0) {
          local_50c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_50c = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_510 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_510 = (float)fVar11;
        }
        if (local_50c != local_510) goto LAB_00434d6a;
        break;
      }
      case 0x2c: {
        std::uint32_t local_518;
        std::uint32_t local_514;
        if ((instruction[3] & 1U) == 0) {
          local_514 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_514 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_518 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_518 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((int)local_514 < (int)local_518) goto LAB_00434d6a;
        break;
      }
      case 0x2d: {
        float local_520;
        float local_51c;
        if ((instruction[3] & 1U) == 0) {
          local_520 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_520 = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_51c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_51c = (float)fVar11;
        }
        if (local_520 < local_51c) goto LAB_00434d6a;
        break;
      }
      case 0x2e: {
        std::uint32_t local_528;
        std::uint32_t local_524;
        if ((instruction[3] & 1U) == 0) {
          local_524 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_524 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_528 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_528 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((int)local_524 <= (int)local_528) goto LAB_00434d6a;
        break;
      }
      case 0x2f: {
        float local_530;
        float local_52c;
        if ((instruction[3] & 1U) == 0) {
          local_530 = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_530 = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_52c = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_52c = (float)fVar11;
        }
        if (local_530 <= local_52c) goto LAB_00434d6a;
        break;
      }
      case 0x30: {
        std::uint32_t local_538;
        std::uint32_t local_534;
        if ((instruction[3] & 1U) == 0) {
          local_534 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_534 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_538 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_538 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((int)local_538 < (int)local_534) goto LAB_00434d6a;
        break;
      }
      case 0x31: {
        float local_540;
        float local_53c;
        if ((instruction[3] & 1U) == 0) {
          local_53c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_53c = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_540 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_540 = (float)fVar11;
        }
        if (local_540 < local_53c) goto LAB_00434d6a;
        break;
      }
      case 0x32: {
        std::uint32_t local_548;
        std::uint32_t local_544;
        if ((instruction[3] & 1U) == 0) {
          local_544 = *(std::uint32_t *)(instruction + 4);
        }
        else {
          local_544 = this->integer_value(*(std::uint32_t *)(instruction + 4));
        }
        if ((instruction[3] & 2U) == 0) {
          local_548 = *(std::uint32_t *)(instruction + 6);
        }
        else {
          local_548 = this->integer_value(*(std::uint32_t *)(instruction + 6));
        }
        if ((int)local_548 <= (int)local_544) goto LAB_00434d6a;
        break;
      }
      case 0x33: {
        float local_550;
        float local_54c;
        if ((instruction[3] & 1U) == 0) {
          local_54c = *(float *)(instruction + 4);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 4));
          local_54c = (float)fVar11;
        }
        if ((instruction[3] & 2U) == 0) {
          local_550 = *(float *)(instruction + 6);
        }
        else {
          fVar11 = this->float_value(*(float *)(instruction + 6));
          local_550 = (float)fVar11;
        }
        if (local_550 <= local_54c) goto LAB_00434d6a;
        break;
      }
      }
LAB_00434dad:
      *(std::uint32_t *)((int)this + 0x28) = (std::uint32_t)(std::uint16_t)instruction[1] + *(int *)((int)this + 0x28);
      goto LAB_0042b831;
    }
  }
  goto LAB_00434fb5;
code_r0x0042df46:
  timer_4c8--;
LAB_00434dce:
  if ((*(std::uint32_t *)((int)this + 0x49c) >> 0x13 & 1) != 0) {
    FUN_00435520((int)this);
  }
  if ((*(std::uint8_t *)((int)this + 0x4a1) >> 1 & 1) != 0) {
    FUN_004296e0((void *)((int)this + 0x5bc),(float *)&DAT_005c5540);
  }
  if ((base.flags.word_04 >> 0xb & 1) != 0) {
    Vector3 corners[4];
    FUN_00445770(this,corners);
    normalize_coordinates_438eb0(&base.vectors_378[0],reinterpret_cast<const Vector2*>(&corners[0]));
    normalize_coordinates_438eb0(&base.vectors_378[1],reinterpret_cast<const Vector2*>(&corners[1]));
    normalize_coordinates_438eb0(&base.vectors_378[2],reinterpret_cast<const Vector2*>(&corners[2]));
    normalize_coordinates_438eb0(&base.vectors_378[3],reinterpret_cast<const Vector2*>(&corners[3]));
    base.vector_398.x=base.vectors_378[1].x-base.vectors_378[0].x;
    base.vector_398.y=base.vectors_378[1].y-base.vectors_378[0].y;
  }
  FUN_004358d0((int)this);
  FUN_00435c80(this);
  local_764 = (std::uint32_t *)((int)this + 0x4c8);
  FUN_00423540(local_764);
LAB_00434fb5:
  FUN_004292a0(&DAT_005aefe4,initial_clock_value);
  return 0;
LAB_00434fd1:
  FUN_004292a0(&DAT_005aefe4,initial_clock_value);
  return 1;
}

} // namespace th20
