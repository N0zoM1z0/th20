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

extern "C" {
// Original external helpers are declared with their x86 receiver/stack ABI.

}

extern GameController* current_game_controller;
extern GameRandom native_polygon_random_5ba4c4;
extern const Vector3 native_zero_position;
extern const float native_zero, native_one, native_two, native_four;
extern const float native_half, native_pi, native_negative_one;
extern const Vector3 native_vector_5c5540;
// The 636-byte native map includes a sentinel for signed opcode -1 at index 0.
extern const std::uint8_t native_animation_opcode_dispatch_435284[0x27c];

// Every original VM helper call below is expressed through a maintained C++
// owner. No numeric-address call adapters or generic call views remain.

std::int32_t Animation::update() {

  float initial_clock_value;
  AnmInstruction *instruction;

  if ((base.flags.word_1c & 1) != 0) {
    return 0;
  }
  initial_clock_value = static_cast<float>(default_timer_clock);
  if ((base.flags.word_04 >> 8 & 1) != 0) {
    default_timer_clock.set(native_one);
  }
  if (native_zero < this->slowdown()) {
    const float slowdown = this->slowdown();
    default_timer_clock.set(initial_clock_value - slowdown * initial_clock_value);
    if (static_cast<float>(default_timer_clock) < 0.0f) {
      default_timer_clock.set(0);
    }
  }
  if (this->callback && this->callback->update() != 0) {
    goto LAB_00434fd1;
  }
  if (field_5dc != nullptr && this->field_5dc(this) != 0) {
    goto LAB_00434fd1;
  }
  // Preserve the two native early-out gates as distinct control-flow tests.
  if (base.field_28 < 0) goto LAB_00434fb5;
  if ((base.flags.word_04 >> 0x19 & 1) != 0) goto LAB_00434fb5;
  {
    timer_4d8++;
    if (base.field_438 != 0) {
      AnimationFile* local_774;
      int local_770;
      local_774 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
      local_770 = base.field_24;
      instruction = reinterpret_cast<AnmInstruction*>(
          reinterpret_cast<std::uintptr_t>(local_774->script(local_770)) + base.field_28);
      goto LAB_0042de0b;
    }
    if (base.flags.bits_08.mode == 1 && current_game_controller != nullptr &&
        current_game_controller->animation_frozen() != 0) goto LAB_00434fb5;
    {
      AnimationFile* local_77c;
      int local_778;
      std::uint32_t local_e0;
LAB_0042b831:
      local_77c = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
      local_778 = base.field_24;
      instruction = reinterpret_cast<AnmInstruction*>(
          reinterpret_cast<std::uintptr_t>(local_77c->script(local_778)) + base.field_28);
      if (instruction->frame <= static_cast<std::int32_t>(timer_4c8)) goto LAB_vm_frame_ready;
      goto LAB_00434dce;
LAB_vm_frame_ready:
      local_e0 = (int)instruction->opcode + 1;
      if (0x27b < local_e0) {
switchD_0042b8cc_caseD_a0:
        goto LAB_00434dad;
      }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      // local_e0 is the checked opcode+1 index; this keeps -1 on the sentinel.
      switch(native_animation_opcode_dispatch_435284[local_e0]) {
      case 0xa0: {
        goto switchD_0042b8cc_caseD_a0;
      }
      case 0: {
        base.flags.bits_02.bit_10 = 0;
        base.field_28 = 0xffffffff;
        goto LAB_00434fd1;
      }
      case 1: {
        base.field_28 = 0xffffffff;
        goto LAB_00434fb5;
      }
      case 0x68: {
        std::uint32_t local_554;
        if ((instruction->operand_flags & 1U) != 0) {
          local_554 = this->integer_value((&instruction->first_operand)[0]);
        }
        else {
          local_554 = (&instruction->first_operand)[0];
        }
        base.flags.word_04 =
             base.flags.word_04 & 0xfffffeff | (local_554 & 1) << 8;
        break;
      }
      case 0x72: {
        AnimationFile* local_57c;
        std::uint32_t local_558;
        local_57c = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_558 = (&instruction->first_operand)[0];
        }
        else {
          local_558 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_57c->spawn_child(local_558,this,0);
        break;
      }
      case 0x77: {
        AnimationFile* local_584;
        Animation* local_568;
        std::uint32_t local_560;
        std::uint32_t local_55c;
        if ((base.flags.word_04 >> 0x12 & 1) == 0) {
          local_55c = 0;
        }
        else {
          local_55c = 4;
        }
        local_584 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_560 = (&instruction->first_operand)[0];
        }
        else {
          local_560 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_568 = local_584->spawn_child(local_560,this,local_55c).resolve();
        local_568->base.vector_484.x = (instruction->operand_flags & 2U) == 0
            ? (reinterpret_cast<float*>(&instruction->first_operand)[1])
            : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        local_568->base.vector_484.y = (instruction->operand_flags & 4U) == 0
            ? (reinterpret_cast<float*>(&instruction->first_operand)[2])
            : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        break;
      }
      case 0x7c: {
        AnimationFile* local_590;
        std::uint32_t local_574;
        std::uint32_t local_570;
        Animation* local_f4;
        if ((base.flags.word_04 >> 0x12 & 1) == 0) {
          local_570 = 2;
        }
        else {
          local_570 = 6;
        }
        local_590 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_574 = (&instruction->first_operand)[0];
        }
        else {
          local_574 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_f4 = local_590->spawn_child(local_574,this,local_570).resolve();
        local_f4->base.vector_484.x = (instruction->operand_flags & 2U) == 0
            ? (reinterpret_cast<float*>(&instruction->first_operand)[1])
            : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        local_f4->base.vector_484.y = (instruction->operand_flags & 4U) == 0
            ? (reinterpret_cast<float*>(&instruction->first_operand)[2])
            : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        break;
      }
      case 0x74: {
        AnimationFile* local_59c;
        std::uint32_t local_fc;
        local_59c = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_fc = (&instruction->first_operand)[0];
        }
        else {
          local_fc = this->integer_value((&instruction->first_operand)[0]);
        }
        local_59c->spawn_child(local_fc,this,2);
        break;
      }
      case 0x73: {
        AnimationFile* local_5a4;
        std::uint32_t local_100;
        local_5a4 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_100 = (&instruction->first_operand)[0];
        }
        else {
          local_100 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_5a4->spawn_child(local_100,this,4);
        break;
      }
      case 0x75: {
        AnimationFile* local_5ac;
        std::uint32_t local_104;
        local_5ac = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_104 = (&instruction->first_operand)[0];
        }
        else {
          local_104 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_5ac->spawn_child(local_104,this,6);
        break;
      }
      case 0x7b: {
        std::uint32_t *puVar5;
        std::uint32_t *puVar10;
        if (parent_55c != nullptr) {
          base.variables = parent_55c->base.variables;
        }
        break;
      }
      case 0x78: {
        AnimationFile* local_5b4;
        Animation* local_114;
        std::uint32_t local_108;
        local_5b4 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_108 = (&instruction->first_operand)[0];
        }
        else {
          local_108 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_114 = local_5b4->spawn_child_and_update(local_108,this,0).resolve();
        Vector3 local_a8{
            (instruction->operand_flags & 2U) == 0 ? (reinterpret_cast<float*>(&instruction->first_operand)[1]) : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1])),
            (instruction->operand_flags & 4U) == 0 ? (reinterpret_cast<float*>(&instruction->first_operand)[2]) : this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2])),
            0.0f};
        this->transform_direction(local_a8,1,1);
        local_114->base.vector_484.x = local_a8.x;
        local_114->base.vector_484.y = local_a8.y;
        break;
      }
      case 0x76: {
        AnimationFile* local_5c0;
        std::uint32_t local_118;
        local_5c0 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        if ((instruction->operand_flags & 1U) == 0) {
          local_118 = (&instruction->first_operand)[0];
        }
        else {
          local_118 = this->integer_value((&instruction->first_operand)[0]);
        }
        local_5c0->spawn_child_and_update(local_118,this,0);
        break;
      }
      case 0x7a: {
        std::uint32_t local_11c;
        EffectInfo* const effect_info=particle_effect_info_for_session_437520(0);
        if ((instruction->operand_flags & 1U) == 0) {
          local_11c = (&instruction->first_operand)[0];
        }
        else {
          local_11c = this->integer_value((&instruction->first_operand)[0]);
        }
        // The original VM forwards its Animation receiver as both the
        // opaque effect-parameter payload and the existing-animation owner.
        effect_info->spawn_effect(
            local_11c,*reinterpret_cast<const EffectParameters*>(this),this);
        break;
      }
      case 0x47: {
        AnimationFile* local_5ec;
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
        base.flags.byte_02 = base.flags.byte_02 | 1;
        local_5cc = this->rotation_z_value();
        if (local_5cc <= -(native_pi / native_four)) {
LAB_0042c32a:
          local_5d4 = this->rotation_z_value();
          if (native_pi / native_four <= local_5d4) {
            local_5d8 = this->rotation_z_value();
            if (local_5d8 < native_pi / native_two + native_pi / native_four) {
              if ((instruction->operand_flags & 8U) == 0) {
                local_124 = (&instruction->first_operand)[3];
              }
              else {
                local_124 = this->integer_value((&instruction->first_operand)[3]);
              }
              local_d8 = local_124;
              goto LAB_0042c528;
            }
          }
          local_5dc = this->rotation_z_value();
          if (local_5dc <= -(native_pi / native_four)) {
            local_5e0 = this->rotation_z_value();
            if (native_pi / native_two + native_pi / native_four < local_5e0) {
              if ((instruction->operand_flags & 4U) == 0) {
                local_128 = (&instruction->first_operand)[2];
              }
              else {
                local_128 = this->integer_value((&instruction->first_operand)[2]);
              }
              local_d8 = local_128;
              goto LAB_0042c528;
            }
          }
          if ((instruction->operand_flags & 2U) == 0) {
            local_12c = (&instruction->first_operand)[1];
          }
          else {
            local_12c = this->integer_value((&instruction->first_operand)[1]);
          }
          local_d8 = local_12c;
        }
        else {
          local_5d0 = this->rotation_z_value();
          if (native_pi / native_four <= local_5d0) goto LAB_0042c32a;
          if ((instruction->operand_flags & 1U) == 0) {
            local_120 = (&instruction->first_operand)[0];
          }
          else {
            local_120 = this->integer_value((&instruction->first_operand)[0]);
          }
          local_d8 = local_120;
        }
LAB_0042c528:
        if (field_5e0 != nullptr) {
          local_5e4 = this->field_5e0;
          local_d8 = (*local_5e4)(this,local_d8);
        }
        if ((int)local_d8 < 0) {
          reinterpret_cast<AnimationFile*>(native_card_renderer_5c0698->current_file_437950())->apply_sprite(this, 0x120);
        }
        else {
          local_5ec = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          local_5ec->apply_sprite(this, local_d8);
        }
        base.field_43c = static_cast<std::int32_t>(timer_4c8);
        break;
      }
      case 0x34: {
        AnimationFile* local_5f8;
        NativeVmScriptCallback local_5f0;
        std::uint32_t local_134;
        std::uint32_t local_130;
        std::uint32_t local_e8;
        base.flags.byte_02 = base.flags.byte_02 | 1;
        if (field_5e0 == nullptr) {
          if ((instruction->operand_flags & 1U) == 0) {
            local_134 = (&instruction->first_operand)[0];
          }
          else {
            local_134 = this->integer_value((&instruction->first_operand)[0]);
          }
          local_e8 = local_134;
        }
        else {
          local_5f0 = this->field_5e0;
          if ((instruction->operand_flags & 1U) == 0) {
            local_130 = (&instruction->first_operand)[0];
          }
          else {
            local_130 = this->integer_value((&instruction->first_operand)[0]);
          }
          local_e8 = (*local_5f0)(this,local_130);
        }
        if ((int)local_e8 < 0) {
          reinterpret_cast<AnimationFile*>(native_card_renderer_5c0698->current_file_437950())->apply_sprite(this, 0x120);
        }
        else {
          local_5f8 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          local_5f8->apply_sprite(this, local_e8);
        }
        base.field_43c = static_cast<std::int32_t>(timer_4c8);
        break;
      }
      case 0x35: {
        std::uint32_t random_value;
        AnimationFile* local_604;
        NativeVmScriptCallback local_6e4;
        std::uint32_t local_144;
        std::uint32_t local_140;
        std::uint32_t local_13c;
        std::uint32_t local_138;
        int local_ec;
        base.flags.byte_02 = base.flags.byte_02 | 1;
        if (field_5e0 == nullptr) {
          if ((instruction->operand_flags & 1U) == 0) {
            local_144 = (&instruction->first_operand)[0];
          }
          else {
            local_144 = this->integer_value((&instruction->first_operand)[0]);
          }
          if ((instruction->operand_flags & 2U) == 0) {
            local_140 = (&instruction->first_operand)[1];
          }
          else {
            local_140 = this->integer_value((&instruction->first_operand)[1]);
          }
          random_value = native_polygon_random_5ba4c4.next();
          local_ec = random_value % local_140 + local_144;
        }
        else {
          local_6e4 = this->field_5e0;
          if ((instruction->operand_flags & 1U) == 0) {
            local_13c = (&instruction->first_operand)[0];
          }
          else {
            local_13c = this->integer_value((&instruction->first_operand)[0]);
          }
          if ((instruction->operand_flags & 2U) == 0) {
            local_138 = (&instruction->first_operand)[1];
          }
          else {
            local_138 = this->integer_value((&instruction->first_operand)[1]);
          }
          random_value = native_polygon_random_5ba4c4.next();
          local_ec = (*local_6e4)(this,random_value % local_138 + local_13c);
        }
        if (local_ec < 0) {
          reinterpret_cast<AnimationFile*>(native_card_renderer_5c0698->current_file_437950())->apply_sprite(this, 0x120);
        }
        else {
          local_604 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
          local_604->apply_sprite(this, local_ec);
        }
        base.field_43c = static_cast<std::int32_t>(timer_4c8);
        break;
      }
      case 0x4a: {
        float local_14c;
        float local_148;
        if ((instruction->operand_flags & 1U) == 0) {
          local_148 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_148 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_50.x = local_148;
        if ((instruction->operand_flags & 2U) == 0) {
          local_14c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_14c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_50.y = local_14c;
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x6a: {
        float local_154;
        float local_150;
        if ((instruction->operand_flags & 1U) == 0) {
          local_150 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_150 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_58.x = local_150;
        if ((instruction->operand_flags & 2U) == 0) {
          local_154 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_154 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_58.y = local_154;
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x65: {
        float local_15c;
        float local_158;
        if ((instruction->operand_flags & 1U) == 0) {
          local_158 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_158 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_68.x = local_158;
        if ((instruction->operand_flags & 2U) == 0) {
          local_15c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_15c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_68.y = local_15c;
        base.flags.word_04 = base.flags.word_04 | 8;
        break;
      }
      case 0x4b: {
        std::uint32_t local_160;
        if ((instruction->operand_flags & 1U) == 0) {
          local_160 = (&instruction->first_operand)[0];
        }
        else {
          local_160 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.channels_490.alpha = (std::uint8_t)local_160;
        break;
      }
      case 0x4c: {
        std::uint32_t local_16c;
        std::uint32_t local_168;
        std::uint32_t local_164;
        if ((instruction->operand_flags & 1U) == 0) {
          local_164 = (&instruction->first_operand)[0];
        }
        else {
          local_164 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.channels_490.red = (std::uint8_t)local_164;
        if ((instruction->operand_flags & 2U) == 0) {
          local_168 = (&instruction->first_operand)[1];
        }
        else {
          local_168 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.channels_490.green = (std::uint8_t)local_168;
        if ((instruction->operand_flags & 4U) == 0) {
          local_16c = (&instruction->first_operand)[2];
        }
        else {
          local_16c = this->integer_value((&instruction->first_operand)[2]);
        }
        base.channels_490.blue = (std::uint8_t)local_16c;
        break;
      }
      case 0x4d: {
        std::uint32_t local_170;
        if ((instruction->operand_flags & 1U) == 0) {
          local_170 = (&instruction->first_operand)[0];
        }
        else {
          local_170 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.channels_494.alpha = (std::uint8_t)local_170;
        break;
      }
      case 0x4e: {
        std::uint32_t local_17c;
        std::uint32_t local_178;
        std::uint32_t local_174;
        if ((instruction->operand_flags & 1U) == 0) {
          local_174 = (&instruction->first_operand)[0];
        }
        else {
          local_174 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.channels_494.red = (std::uint8_t)local_174;
        if ((instruction->operand_flags & 2U) == 0) {
          local_178 = (&instruction->first_operand)[1];
        }
        else {
          local_178 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.channels_494.green = (std::uint8_t)local_178;
        if ((instruction->operand_flags & 4U) == 0) {
          local_17c = (&instruction->first_operand)[2];
        }
        else {
          local_17c = this->integer_value((&instruction->first_operand)[2]);
        }
        base.channels_494.blue = (std::uint8_t)local_17c;
        break;
      }
      case 0x26: {
        (timer_4c8=static_cast<std::int32_t>((reinterpret_cast<std::int32_t*>(&instruction->first_operand)[1])));
        base.field_28 = (&instruction->first_operand)[0];
        goto LAB_0042b831;
      }
      case 0x27: {
        int *local_180;
        std::uint32_t local_184;
        local_180 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_180 = *local_180 + -1;
        if ((instruction->operand_flags & 1U) == 0) {
          local_184 = (&instruction->first_operand)[0];
        }
        else {
          local_184 = this->integer_value((&instruction->first_operand)[0]);
        }
        if (0 < (int)local_184) {
          (timer_4c8=static_cast<std::int32_t>((reinterpret_cast<std::int32_t*>(&instruction->first_operand)[2])));
          base.field_28 = (&instruction->first_operand)[1];
          goto LAB_0042b831;
        }
        break;
      }
      case 0x3c: {
        base.flags.byte_08 =
             base.flags.byte_08 & 0x3f |
             (base.flags.byte_08 >> 6 ^ 1) << 6;
        base.vector_50.x = base.vector_50.x * native_negative_one;
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x3d: {
        base.flags.byte_08 =
             base.flags.byte_08 & 0x3f |
             (base.flags.byte_08 >> 6 ^ 2) << 6;
        base.vector_50.y = base.vector_50.y * native_negative_one;
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x70: {
        if ((base.flags.byte_08 >> 6 & 1) != 0) {
          base.vector_50.x = base.vector_50.x * native_negative_one;
        }
        if ((base.flags.byte_08 >> 6 & 2) != 0) {
          base.vector_50.y = base.vector_50.y * native_negative_one;
        }
        base.flags.byte_08 = base.flags.byte_08 & 0x3f;
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x43: {
        base.flags.word_04 =
             base.flags.word_04 & 0xfeffffff | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 0x18;
        break;
      }
      case 0x44: {
        base.flags.word_04 = base.flags.word_04 | 1;
        break;
      }
      case 0x45: {
        base.flags.word_04 = base.flags.word_04 & 0xfffffffe;
        break;
      }
      case 0x6f: {
        base.flags.word_04 =
             base.flags.word_04 & 0xffefffff | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 0x14;
        base.field_4b8 = (reinterpret_cast<const float*>(&instruction->first_operand)[1]);
        base.field_4bc = (reinterpret_cast<const float*>(&instruction->first_operand)[2]);
        break;
      }
      case 0x49: {
        float local_190;
        float local_18c;
        float local_188;
        if ((instruction->operand_flags & 1U) == 0) {
          local_188 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_188 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_38.x = local_188;
        if ((instruction->operand_flags & 2U) == 0) {
          local_18c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_18c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_38.y = local_18c;
        if ((instruction->operand_flags & 4U) == 0) {
          local_190 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_190 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.vector_38.z = local_190;
        base.flags.word_04 = base.flags.word_04 | 2;
        break;
      }
      case 0x57: {
        float local_19c;
        float local_198;
        float local_194;
        if ((instruction->operand_flags & 4U) == 0) {
          local_194 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_194 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_198 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_198 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 1U) == 0) {
          local_19c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_19c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        this->set_rotation_speed(local_19c, local_198, local_194);
        break;
      }
      case 0x58: {
        float local_1a4;
        float local_1a0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_1a0 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_1a0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 1U) == 0) {
          local_1a4 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_1a4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        this->set_scale_speed(local_1a4, local_1a0);
        break;
      }
      case 0x59: {
        std::uint32_t local_1a8;
        std::uint8_t local_cf;
        std::uint8_t local_ce;
        local_ce = (reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]);
        local_cf = base.channels_490.alpha;
        if ((instruction->operand_flags & 2U) == 0) {
          local_1a8 = (&instruction->first_operand)[1];
        }
        else {
          local_1a8 = this->integer_value((&instruction->first_operand)[1]);
        }
        reinterpret_cast<NativeAnimationFadeConfig86*>(this)->interpolate_channel_438c60(local_1a8, 0, local_cf, local_ce);
        break;
      }
      case 0x37: {
        base.flags.bytes_00.flag_byte_01 = (char)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[0];
        break;
      }
      case 0x48: {
        float local_1c0;
        float local_1bc;
        float local_1b8;
        float local_1b4;
        float local_1b0;
        float local_1ac;
        if ((base.flags.word_04 >> 6 & 1) == 0) {
          if ((instruction->operand_flags & 4U) == 0) {
            local_1ac = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
          }
          else {
            local_1ac = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
          }
          if ((instruction->operand_flags & 2U) == 0) {
            local_1b0 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
          }
          else {
            local_1b0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
          }
          if ((instruction->operand_flags & 1U) == 0) {
            local_1b4 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
          }
          else {
            local_1b4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
          }
          base.vector_2c = Vector3(local_1b4,local_1b0,local_1ac);
        }
        else {
          if ((instruction->operand_flags & 4U) == 0) {
            local_1b8 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
          }
          else {
            local_1b8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
          }
          if ((instruction->operand_flags & 2U) == 0) {
            local_1bc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
          }
          else {
            local_1bc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
          }
          if ((instruction->operand_flags & 1U) == 0) {
            local_1c0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
          }
          else {
            local_1c0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
          }
          base.vector_484 = Vector3(local_1c0,local_1bc,local_1b8);
        }
        break;
      }
      case 0x71: {
        float local_1cc;
        float local_1c8;
        float local_1c4;
        if ((instruction->operand_flags & 4U) == 0) {
          local_1c4 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_1c4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_1c8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_1c8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 1U) == 0) {
          local_1cc = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_1cc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_484 = Vector3(local_1cc,local_1c8,local_1c4);
        break;
      }
      case 0x6c: {
        float local_1d4;
        float local_1d0;
        if ((instruction->operand_flags & 1U) == 0) {
          local_1d0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_1d0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_80.x = local_1d0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_1d4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_1d4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_80.y = local_1d4;
        break;
      }
      case 0x6d: {
        std::uint32_t local_1d8;
        if ((instruction->operand_flags & 1U) == 0) {
          local_1d8 = (&instruction->first_operand)[0];
        }
        else {
          local_1d8 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.field_0a = base.flags.field_0a & 0xe3 | ((std::uint8_t)local_1d8 & 7) << 2;
        break;
      }
      case 4: {
        std::uint32_t local_1dc;
        if ((instruction->operand_flags & 1U) == 0) {
          local_1dc = (&instruction->first_operand)[0];
        }
        else {
          local_1dc = this->integer_value((&instruction->first_operand)[0]);
        }
        timer_4c8.add_unscaled(static_cast<float>(-static_cast<std::int32_t>(local_1dc)));
        break;
      }
      case 3: {
        AnmInstruction *local_f0;
        AnmInstruction *scan_instruction;
        AnimationFile* local_614;
        int local_610;
        int local_1e0;
        int local_dc;
        base.flags.byte_02 = base.flags.byte_02 & 0xfe;
switchD_0042b8cc_caseD_2:
        if (base.field_438 == 0) {
          base.flags.byte_09 = base.flags.byte_09 | 1;
          timer_4c8--;
          goto LAB_00434dce;
        }
LAB_0042de0b:
        local_dc = 0;
        local_1e0 = 0;
        local_f0 = nullptr;
        local_614 = reinterpret_cast<NativeAnimationLegacyFileView*>(this)->previous_file_437470();
        local_610 = base.field_24;
        for (scan_instruction = local_614->script(local_610);
            ((scan_instruction->opcode != 5 || (base.field_438 != (reinterpret_cast<std::int32_t*>(&scan_instruction->first_operand)[0]))) &&
            (scan_instruction->opcode != -1)); scan_instruction = reinterpret_cast<AnmInstruction*>(
                reinterpret_cast<std::uintptr_t>(scan_instruction) + scan_instruction->byte_advance)) {
          if ((scan_instruction->opcode == 5) && ((reinterpret_cast<std::int32_t*>(&scan_instruction->first_operand)[0]) == -1)) {
            local_f0 = scan_instruction;
            local_1e0 = local_dc;
          }
          local_dc = (std::uint32_t)(std::uint16_t)scan_instruction->byte_advance + local_dc;
        }
        base.field_438 = 0;
        base.flags.byte_09 = base.flags.byte_09 & 0xfe;
        if (scan_instruction->opcode == 5) {
LAB_0042df8e:
          base.timer.set_from_current(timer_4c8);
          base.field_10 = base.field_28;
          local_dc = (std::uint32_t)(std::uint16_t)scan_instruction->byte_advance + local_dc;
          (timer_4c8=static_cast<std::int32_t>((int)scan_instruction->frame));
          scan_instruction = reinterpret_cast<AnmInstruction*>(
                reinterpret_cast<std::uintptr_t>(scan_instruction) + scan_instruction->byte_advance);
          base.field_28 = local_dc;
          base.flags.byte_02 = base.flags.byte_02 | 1;
          goto LAB_0042b831;
        }
        if (local_f0 != nullptr) {
          scan_instruction = local_f0;
          local_dc = local_1e0;
          goto LAB_0042df8e;
        }
        if (instruction->opcode == 3) goto code_r0x0042df46;
        goto LAB_0042b831;
      }
      case 2: {
        goto switchD_0042b8cc_caseD_2;
      }
      case 5: {
        timer_4c8.set_from_current(base.timer);
        base.field_28 = base.field_10;
        goto LAB_0042b831;
      }
      case 0x3e: {
        std::uint8_t local_cd;
        local_cd = (char)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[0] != '\0';
        base.flags.byte_02 = base.flags.byte_02 & 0xfe | local_cd;
        break;
      }
      case 0x5d: {
        base.flags.word_10 = (std::uint32_t)(std::uint16_t)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[0];
        base.flags.word_14 = (std::uint32_t)(std::uint16_t)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[1];
        break;
      }
      case 0x61: {
        float local_1e4;
        if ((instruction->operand_flags & 1U) == 0) {
          local_1e4 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_1e4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.field_3a0 = local_1e4;
        base.flags.word_04 = base.flags.word_04 | 0x80000;
        break;
      }
      case 0x62: {
        float local_1e8;
        if ((instruction->operand_flags & 1U) == 0) {
          local_1e8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_1e8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.field_3a4 = local_1e8;
        base.flags.word_04 = base.flags.word_04 | 0x80000;
        break;
      }
      case 0x39: {
        base.flags.word_04 =
             base.flags.word_04 & 0xffffffef | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 4;
        break;
      }
      case 0x3a: {
        base.flags.byte_09 = base.flags.byte_09 & 0xfd | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 1;
        break;
      }
      case 0x3f: {
        base.flags.byte_08 =
             base.flags.byte_08 & 0xf3 | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 3) << 2;
        break;
      }
      case 0x4f: {

        float local_1f8;
        float local_1f4;
        float local_1f0;
        std::uint32_t local_1ec;

        if ((instruction->operand_flags & 1U) == 0) {
          local_1ec = (&instruction->first_operand)[0];
        }
        else {
          local_1ec = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_8c.set_duration(local_1ec);

        base.interpolation_8c.set_tangent_start(native_zero_position);

        base.interpolation_8c.set_tangent_end(native_zero_position);

        base.interpolation_8c.set_mode((&instruction->first_operand)[1]);
        if ((base.flags.word_04 >> 6 & 1) == 0) {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_2c);
        }
        else {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_484);
        }

        if ((instruction->operand_flags & 4U) == 0) {
          local_1f8 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_1f8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_1f4 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_1f4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_1f0 = (reinterpret_cast<float*>(&instruction->first_operand)[4]);
        }
        else {
          local_1f0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[4]));
        }
        base.interpolation_8c.set_end(Vector3(local_1f8,local_1f4,local_1f0));
        base.interpolation_8c.reset_timer();
        break;
      }
      case 0x69: {

        float local_204;
        float local_200;
        std::uint32_t local_1fc;
        Vector3 local_b4;

        if ((instruction->operand_flags & 1U) == 0) {
          local_1fc = (&instruction->first_operand)[0];
        }
        else {
          local_1fc = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_8c.set_duration(local_1fc);

        base.interpolation_8c.set_tangent_start(native_zero_position);

        base.interpolation_8c.set_tangent_end(native_zero_position);

        base.interpolation_8c.set_mode((&instruction->first_operand)[1]);
        if ((base.flags.word_04 >> 6 & 1) == 0) {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_2c);
        }
        else {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_484);
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_200 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_200 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_204 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_204 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        polar(local_b4,local_204,local_200);

        base.interpolation_8c.set_end(*reinterpret_cast<const Vector3*>(&local_b4));
        base.interpolation_8c.reset_timer();
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

        float local_218;
        float local_214;
        float local_210;
        float local_20c;
        float local_208;
        if ((instruction->operand_flags & 2U) == 0) {
          local_208 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_208 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_90.x = local_208;
        if ((instruction->operand_flags & 4U) == 0) {
          local_20c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_20c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_90.y = local_20c;
        if ((instruction->operand_flags & 8U) == 0) {
          local_210 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_210 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        local_90.z = local_210;
        if ((instruction->operand_flags & 0x80U) == 0) {
          local_214 = (reinterpret_cast<float*>(&instruction->first_operand)[7]);
        }
        else {
          local_214 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[7]));
        }
        local_9c.x = local_214;
        if ((instruction->operand_flags & 0x100U) == 0) {
          local_218 = (reinterpret_cast<float*>(&instruction->first_operand)[8]);
        }
        else {
          local_218 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[8]));
        }
        local_9c.y = local_218;
        if ((instruction->operand_flags & 0x200U) == 0) {
          local_21c = (reinterpret_cast<float*>(&instruction->first_operand)[9]);
        }
        else {
          local_21c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[9]));
        }
        local_9c.z = local_21c;

        if ((instruction->operand_flags & 1U) == 0) {
          local_220 = (&instruction->first_operand)[0];
        }
        else {
          local_220 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_8c.set_duration(local_220);

        base.interpolation_8c.set_tangent_start(*reinterpret_cast<const Vector3*>(&local_90));

        base.interpolation_8c.set_tangent_end(*reinterpret_cast<const Vector3*>(&local_9c));

        base.interpolation_8c.set_mode(8);
        if ((base.flags.word_04 >> 6 & 1) == 0) {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_2c);
        }
        else {

          reinterpret_cast<Motion*>(&base.interpolation_8c.start)->set_position(base.vector_484);
        }

        if ((instruction->operand_flags & 0x10U) == 0) {
          local_22c = (reinterpret_cast<float*>(&instruction->first_operand)[4]);
        }
        else {
          local_22c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[4]));
        }
        if ((instruction->operand_flags & 0x20U) == 0) {
          local_228 = (reinterpret_cast<float*>(&instruction->first_operand)[5]);
        }
        else {
          local_228 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[5]));
        }
        if ((instruction->operand_flags & 0x40U) == 0) {
          local_224 = (reinterpret_cast<float*>(&instruction->first_operand)[6]);
        }
        else {
          local_224 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[6]));
        }
        base.interpolation_8c.set_end(Vector3(local_22c,local_228,local_224));
        base.interpolation_8c.reset_timer();
        break;
      }
      case 0x50: {
        std::uint32_t local_670;
        std::uint32_t local_23c;
        std::uint32_t local_238;
        std::uint32_t local_234;
        std::uint32_t local_230;
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_230 = (&instruction->first_operand)[4];
        }
        else {
          local_230 = this->integer_value((&instruction->first_operand)[4]);
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_234 = (&instruction->first_operand)[3];
        }
        else {
          local_234 = this->integer_value((&instruction->first_operand)[3]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_238 = (&instruction->first_operand)[2];
        }
        else {
          local_238 = this->integer_value((&instruction->first_operand)[2]);
        }
        local_670 = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_23c = (&instruction->first_operand)[0];
        }
        else {
          local_23c = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationColorConfigView*>(this)->interpolate_primary_rgb_438d50(
            local_23c,local_670,
            Color3(base.channels_490.red,base.channels_490.green,base.channels_490.blue),
            Color3(static_cast<std::uint8_t>(local_238),static_cast<std::uint8_t>(local_234),static_cast<std::uint8_t>(local_230)));
        break;
      }
      case 0x51: {
        std::uint32_t local_674;
        std::uint32_t local_244;
        std::uint32_t local_240;
        std::uint8_t local_d0;
        if ((instruction->operand_flags & 4U) == 0) {
          local_240 = (&instruction->first_operand)[2];
        }
        else {
          local_240 = this->integer_value((&instruction->first_operand)[2]);
        }
        local_d0 = base.channels_490.alpha;
        local_674 = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_244 = (&instruction->first_operand)[0];
        }
        else {
          local_244 = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationFadeConfig86*>(this)->interpolate_channel_438c60(local_244, local_674, local_d0, (std::uint8_t)local_240);
        break;
      }
      case 0x55: {
        std::uint32_t local_678;
        std::uint32_t local_254;
        std::uint32_t local_250;
        std::uint32_t local_24c;
        std::uint32_t local_248;
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_248 = (&instruction->first_operand)[4];
        }
        else {
          local_248 = this->integer_value((&instruction->first_operand)[4]);
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_24c = (&instruction->first_operand)[3];
        }
        else {
          local_24c = this->integer_value((&instruction->first_operand)[3]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_250 = (&instruction->first_operand)[2];
        }
        else {
          local_250 = this->integer_value((&instruction->first_operand)[2]);
        }
        local_678 = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_254 = (&instruction->first_operand)[0];
        }
        else {
          local_254 = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationColorConfigView*>(this)->interpolate_rgb_438cc0(
            local_254,local_678,
            Color3(base.channels_494.red,base.channels_494.green,base.channels_494.blue),
            Color3(static_cast<std::uint8_t>(local_250),static_cast<std::uint8_t>(local_24c),static_cast<std::uint8_t>(local_248)));
        break;
      }
      case 0x56: {
        std::uint32_t local_67c;
        std::uint32_t local_25c;
        std::uint32_t local_258;
        std::uint8_t local_d1;
        if ((instruction->operand_flags & 4U) == 0) {
          local_258 = (&instruction->first_operand)[2];
        }
        else {
          local_258 = this->integer_value((&instruction->first_operand)[2]);
        }
        local_d1 = base.channels_494.alpha;
        local_67c = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_25c = (&instruction->first_operand)[0];
        }
        else {
          local_25c = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationColorConfigView*>(this)->interpolate_secondary_alpha_438bd0(local_25c, local_67c, local_d1, (std::uint8_t)local_258);
        break;
      }
      case 0x52: {

        float local_26c;
        float local_268;
        float local_264;
        std::uint32_t local_260;

        if ((instruction->operand_flags & 1U) == 0) {
          local_260 = (&instruction->first_operand)[0];
        }
        else {
          local_260 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_160.set_duration(local_260);

        base.interpolation_160.set_tangent_start(native_zero_position);

        base.interpolation_160.set_tangent_end(native_zero_position);

        base.interpolation_160.set_mode((&instruction->first_operand)[1]);

        reinterpret_cast<Motion*>(&base.interpolation_160.start)->set_position(base.vector_38);

        if ((instruction->operand_flags & 4U) == 0) {
          local_26c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_26c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_268 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_268 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_264 = (reinterpret_cast<float*>(&instruction->first_operand)[4]);
        }
        else {
          local_264 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[4]));
        }
        base.interpolation_160.set_end(Vector3(local_26c,local_268,local_264));
        base.interpolation_160.reset_timer();
        base.flags.word_04 = base.flags.word_04 | 2;
        break;
      }
      case 0x53: {

        float local_274;
        std::uint32_t local_270;

        if ((instruction->operand_flags & 1U) == 0) {
          local_270 = (&instruction->first_operand)[0];
        }
        else {
          local_270 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_1b4.set_duration(local_270);

        base.interpolation_1b4.set_tangent_start(Angle(0.0f));
        base.interpolation_1b4.set_tangent_end(Angle(0.0f));

        reinterpret_cast<FloatInterpolation*>(&base.interpolation_1b4)->set_mode((&instruction->first_operand)[1]);

        base.interpolation_1b4.set_start(Angle(base.vector_38.z));

        if ((instruction->operand_flags & 4U) == 0) {
          local_274 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_274 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.interpolation_1b4.set_end(Angle(local_274));
        reinterpret_cast<FloatInterpolation*>(&base.interpolation_1b4)->reset_timer();
        base.flags.word_04 = base.flags.word_04 | 2;
        break;
      }
      case 0x54: {

        std::uint32_t local_6b4;
        std::uint32_t local_280;
        float local_27c;
        float local_278;
        if ((instruction->operand_flags & 4U) == 0) {
          local_27c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_27c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_278 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_278 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        local_6b4 = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_280 = (&instruction->first_operand)[0];
        }
        else {
          local_280 = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationVector2ConfigView*>(this)->interpolate_primary_scale_438df0(local_280,local_6b4,base.vector_50,Vector2(local_27c,local_278));
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x6b: {

        std::uint32_t local_6bc;
        std::uint32_t local_28c;
        float local_288;
        float local_284;
        if ((instruction->operand_flags & 4U) == 0) {
          local_288 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_288 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_284 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_284 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        local_6bc = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_28c = (&instruction->first_operand)[0];
        }
        else {
          local_28c = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationVector2ConfigView*>(this)->interpolate_secondary_scale_438db0(local_28c,local_6bc,base.vector_58,Vector2(local_288,local_284));
        base.flags.word_04 = base.flags.word_04 | 4;
        break;
      }
      case 0x66: {

        std::uint32_t local_6c4;
        std::uint32_t local_298;
        float local_294;
        float local_290;
        if ((instruction->operand_flags & 4U) == 0) {
          local_294 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_294 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 8U) == 0) {
          local_290 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_290 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        local_6c4 = (std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[4]);
        if ((instruction->operand_flags & 1U) == 0) {
          local_298 = (&instruction->first_operand)[0];
        }
        else {
          local_298 = this->integer_value((&instruction->first_operand)[0]);
        }
        reinterpret_cast<NativeAnimationVector2ConfigView*>(this)->interpolate_uv_scale_438e30(local_298,local_6c4,base.vector_68,Vector2(local_294,local_290));
        base.flags.word_04 = base.flags.word_04 | 8;
        break;
      }
      case 99: {

        float local_768;
        std::uint32_t local_6d4;
        std::uint32_t local_6cc;
        float local_2a0;
        std::uint32_t local_29c;

        if ((instruction->operand_flags & 1U) == 0) {
          local_29c = (&instruction->first_operand)[0];
        }
        else {
          local_29c = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_320.set_duration(local_29c);

        local_6cc = 0;
        base.interpolation_320.set_tangent_start(*reinterpret_cast<const float*>(&local_6cc));

        local_6d4 = 0;
        base.interpolation_320.set_tangent_end(*reinterpret_cast<const float*>(&local_6d4));

        base.interpolation_320.set_mode((&instruction->first_operand)[1]);

        base.interpolation_320.set_start(*&base.field_3a0);

        if ((instruction->operand_flags & 4U) == 0) {
          local_2a0 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_2a0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_768 = local_2a0;
        base.interpolation_320.set_end(*reinterpret_cast<const float*>(&local_768));
        base.interpolation_320.reset_timer();
        break;
      }
      case 100: {

        float local_708;
        std::uint32_t local_6f8;
        std::uint32_t local_6f0;
        float local_2a8;
        std::uint32_t local_2a4;

        if ((instruction->operand_flags & 1U) == 0) {
          local_2a4 = (&instruction->first_operand)[0];
        }
        else {
          local_2a4 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.interpolation_34c.set_duration(local_2a4);

        local_6f0 = 0;
        base.interpolation_34c.set_tangent_start(*reinterpret_cast<const float*>(&local_6f0));

        local_6f8 = 0;
        base.interpolation_34c.set_tangent_end(*reinterpret_cast<const float*>(&local_6f8));

        base.interpolation_34c.set_mode((&instruction->first_operand)[1]);

        base.interpolation_34c.set_start(*&base.field_3a4);

        if ((instruction->operand_flags & 4U) == 0) {
          local_2a8 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_2a8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_708 = local_2a8;
        base.interpolation_34c.set_end(*reinterpret_cast<const float*>(&local_708));
        base.interpolation_34c.reset_timer();
        break;
      }
      case 0x36: {
        base.flags.bytes_00.animation_mode = (char)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[0];
        base.flags.byte_08 = base.flags.byte_08 & 0xcf;
        break;
      }
      case 0x5e: {
        base.vector_2c = vector_5bc;
        vector_5bc.x = 0.0f;
        vector_5bc.y = 0.0f;
        vector_5bc.z = 0.0f;
        break;
      }
      case 0x7d: {
        std::uint32_t local_2ac;
        base.flags.bytes_00.animation_mode = 9;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2ac = (&instruction->first_operand)[0];
        }
        else {
          local_2ac = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2ac * 0x38);
        break;
      }
      case 0x9e: {
        std::uint32_t local_2b4;
        std::uint32_t local_2b0;
        base.flags.bytes_00.animation_mode = 0x2f;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2b0 = (&instruction->first_operand)[0];
        }
        else {
          local_2b0 = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2b0 * 0x38);
        if ((instruction->operand_flags & 1U) == 0) {
          local_2b4 = (&instruction->first_operand)[0];
        }
        else {
          local_2b4 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.variables.field_00 = local_2b4;
        break;
      }
      case 0x9f: {
        float local_2b8;
        base.flags.bytes_00.animation_mode = 0x30;
        this->allocate_geometry(0x54);
        if ((instruction->operand_flags & 1U) == 0) {
          local_2b8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2b8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.variables.field_10 = local_2b8;
        break;
      }
      case 0x7e: {
        std::uint32_t local_2bc;
        base.flags.bytes_00.animation_mode = 0xd;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2bc = (&instruction->first_operand)[0];
        }
        else {
          local_2bc = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2bc * 0x38);
        break;
      }
      case 0x7f: {
        std::uint32_t local_2c0;
        base.flags.bytes_00.animation_mode = 0xe;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2c0 = (&instruction->first_operand)[0];
        }
        else {
          local_2c0 = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2c0 * 0x38);
        break;
      }
      case 0x86: {
        std::uint32_t local_2c4;
        base.flags.bytes_00.animation_mode = 0x18;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2c4 = (&instruction->first_operand)[0];
        }
        else {
          local_2c4 = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2c4 * 0x30);
        break;
      }
      case 0x87: {
        std::uint32_t local_2c8;
        base.flags.bytes_00.animation_mode = 0x19;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2c8 = (&instruction->first_operand)[0];
        }
        else {
          local_2c8 = this->integer_value((&instruction->first_operand)[0]);
        }
        this->allocate_geometry(local_2c8 * 0x30);
        break;
      }
      case 0x5a: {
        Vector3 corners[4];
        this->project_corners(corners);
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
        if ((instruction->operand_flags & 1U) == 0) {
          local_2cc = (&instruction->first_operand)[0];
        }
        else {
          local_2cc = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.word_04 =
             base.flags.word_04 & 0xfffff7ff | (local_2cc & 1) << 0xb;
        break;
      }
      case 0x80: {
        float local_2d4;
        float local_2d0;
        base.flags.bytes_00.animation_mode = 0x10;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2d0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2d0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2d0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2d4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2d4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2d4;
        break;
      }
      case 0x83: {
        float local_2dc;
        float local_2d8;
        base.flags.bytes_00.animation_mode = 0x14;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2d8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2d8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2d8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2dc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2dc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2dc;
        break;
      }
      case 0x84: {
        float local_2e4;
        float local_2e0;
        base.flags.bytes_00.animation_mode = 0x15;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2e0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2e0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2e0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2e4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2e4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2e4;
        break;
      }
      case 0x85: {
        float local_2ec;
        float local_2e8;
        base.flags.bytes_00.animation_mode = 0x16;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2e8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2e8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2e8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2ec = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2ec = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2ec;
        break;
      }
      case 0x8a: {
        float local_2f4;
        float local_2f0;
        base.flags.bytes_00.animation_mode = 0x1a;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2f0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2f0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2f0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2f4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2f4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2f4;
        break;
      }
      case 0x89: {
        float local_2fc;
        float local_2f8;
        base.flags.bytes_00.animation_mode = 0x1b;
        if ((instruction->operand_flags & 1U) == 0) {
          local_2f8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_2f8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_2f8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_2fc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_2fc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_2fc;
        break;
      }
      case 0x81: {
        std::uint32_t local_304;
        float local_300;
        base.flags.bytes_00.animation_mode = 0x11;
        if ((instruction->operand_flags & 1U) == 0) {
          local_300 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_300 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_300;
        if ((instruction->operand_flags & 2U) == 0) {
          local_304 = (&instruction->first_operand)[1];
        }
        else {
          local_304 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_304;
        break;
      }
      case 0x94: {
        std::uint32_t local_314;
        float local_310;
        float local_30c;
        float local_308;
        base.flags.bytes_00.animation_mode = 0x25;
        if ((instruction->operand_flags & 1U) == 0) {
          local_308 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_308 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_308;
        if ((instruction->operand_flags & 2U) == 0) {
          local_30c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_30c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_30c;
        if ((instruction->operand_flags & 4U) == 0) {
          local_310 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_310 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.variables.field_10 = local_310;
        if ((instruction->operand_flags & 8U) == 0) {
          local_314 = (&instruction->first_operand)[3];
        }
        else {
          local_314 = this->integer_value((&instruction->first_operand)[3]);
        }
        base.variables.field_00 = local_314;
        break;
      }
      case 0x95: {
        std::uint32_t local_324;
        float local_320;
        float local_31c;
        float local_318;
        base.flags.bytes_00.animation_mode = 0x26;
        if ((instruction->operand_flags & 1U) == 0) {
          local_318 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_318 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_318;
        if ((instruction->operand_flags & 2U) == 0) {
          local_31c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_31c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_31c;
        if ((instruction->operand_flags & 4U) == 0) {
          local_320 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_320 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.variables.field_10 = local_320;
        if ((instruction->operand_flags & 8U) == 0) {
          local_324 = (&instruction->first_operand)[3];
        }
        else {
          local_324 = this->integer_value((&instruction->first_operand)[3]);
        }
        base.variables.field_00 = local_324;
        break;
      }
      case 0x96: {
        std::uint32_t local_338;
        float local_334;
        float local_330;
        float local_32c;
        float local_328;
        base.flags.bytes_00.animation_mode = 0x27;
        if ((instruction->operand_flags & 1U) == 0) {
          local_328 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_328 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_328;
        if ((instruction->operand_flags & 2U) == 0) {
          local_32c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_32c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_32c;
        if ((instruction->operand_flags & 4U) == 0) {
          local_330 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_330 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.variables.field_10 = local_330;
        if ((instruction->operand_flags & 8U) == 0) {
          local_334 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_334 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        base.variables.field_14 = local_334;
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_338 = (&instruction->first_operand)[4];
        }
        else {
          local_338 = this->integer_value((&instruction->first_operand)[4]);
        }
        base.variables.field_00 = local_338;
        break;
      }
      case 0x97: {
        std::uint32_t local_34c;
        float local_348;
        float local_344;
        float local_340;
        float local_33c;
        base.flags.bytes_00.animation_mode = 0x28;
        if ((instruction->operand_flags & 1U) == 0) {
          local_33c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_33c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_33c;
        if ((instruction->operand_flags & 2U) == 0) {
          local_340 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_340 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_340;
        if ((instruction->operand_flags & 4U) == 0) {
          local_344 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_344 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.variables.field_10 = local_344;
        if ((instruction->operand_flags & 8U) == 0) {
          local_348 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_348 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        base.variables.field_14 = local_348;
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_34c = (&instruction->first_operand)[4];
        }
        else {
          local_34c = this->integer_value((&instruction->first_operand)[4]);
        }
        base.variables.field_00 = local_34c;
        break;
      }
      case 0x98: {
        std::uint32_t local_360;
        float local_35c;
        float local_358;
        float local_354;
        float local_350;
        base.flags.bytes_00.animation_mode = 0x29;
        if ((instruction->operand_flags & 1U) == 0) {
          local_350 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_350 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_350;
        if ((instruction->operand_flags & 2U) == 0) {
          local_354 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_354 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_354;
        if ((instruction->operand_flags & 4U) == 0) {
          local_358 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_358 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        base.variables.field_10 = local_358;
        if ((instruction->operand_flags & 8U) == 0) {
          local_35c = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_35c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        base.variables.field_14 = local_35c;
        if ((instruction->operand_flags & 0x10U) == 0) {
          local_360 = (&instruction->first_operand)[4];
        }
        else {
          local_360 = this->integer_value((&instruction->first_operand)[4]);
        }
        base.variables.field_00 = local_360;
        break;
      }
      case 0x82: {
        std::uint32_t local_368;
        float local_364;
        base.flags.bytes_00.animation_mode = 0x12;
        if ((instruction->operand_flags & 1U) == 0) {
          local_364 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_364 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_364;
        if ((instruction->operand_flags & 2U) == 0) {
          local_368 = (&instruction->first_operand)[1];
        }
        else {
          local_368 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_368;
        break;
      }
      case 0x88: {
        std::uint32_t local_374;
        float local_370;
        float local_36c;
        base.flags.bytes_00.animation_mode = 0x13;
        if ((instruction->operand_flags & 1U) == 0) {
          local_36c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_36c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_36c;
        if ((instruction->operand_flags & 2U) == 0) {
          local_370 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_370 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_370;
        if ((instruction->operand_flags & 4U) == 0) {
          local_374 = (&instruction->first_operand)[2];
        }
        else {
          local_374 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_374;
        break;
      }
      case 0x8c: {
        std::uint32_t local_380;
        float local_37c;
        float local_378;
        base.flags.bytes_00.animation_mode = 0x1d;
        if ((instruction->operand_flags & 1U) == 0) {
          local_378 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_378 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_378;
        if ((instruction->operand_flags & 2U) == 0) {
          local_37c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_37c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_37c;
        if ((instruction->operand_flags & 4U) == 0) {
          local_380 = (&instruction->first_operand)[2];
        }
        else {
          local_380 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_380;
        break;
      }
      case 0x8d: {
        std::uint32_t local_38c;
        float local_388;
        float local_384;
        base.flags.bytes_00.animation_mode = 0x1e;
        if ((instruction->operand_flags & 1U) == 0) {
          local_384 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_384 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_384;
        if ((instruction->operand_flags & 2U) == 0) {
          local_388 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_388 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_388;
        if ((instruction->operand_flags & 4U) == 0) {
          local_38c = (&instruction->first_operand)[2];
        }
        else {
          local_38c = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_38c;
        break;
      }
      case 0x8e: {
        std::uint32_t local_394;
        float local_390;
        base.flags.bytes_00.animation_mode = 0x1f;
        if ((instruction->operand_flags & 1U) == 0) {
          local_390 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_390 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_390;
        if ((instruction->operand_flags & 2U) == 0) {
          local_394 = (&instruction->first_operand)[1];
        }
        else {
          local_394 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_394;
        break;
      }
      case 0x90: {
        std::uint32_t local_39c;
        float local_398;
        base.flags.bytes_00.animation_mode = 0x21;
        if ((instruction->operand_flags & 1U) == 0) {
          local_398 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_398 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_398;
        if ((instruction->operand_flags & 2U) == 0) {
          local_39c = (&instruction->first_operand)[1];
        }
        else {
          local_39c = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_39c;
        break;
      }
      case 0x91: {
        std::uint32_t local_3a8;
        float local_3a4;
        float local_3a0;
        base.flags.bytes_00.animation_mode = 0x22;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3a0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3a0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3a0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3a4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3a4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3a4;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3a8 = (&instruction->first_operand)[2];
        }
        else {
          local_3a8 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3a8;
        break;
      }
      case 0x92: {
        std::uint32_t local_3b4;
        float local_3b0;
        float local_3ac;
        base.flags.bytes_00.animation_mode = 0x23;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3ac = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3ac = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3ac;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3b0 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3b0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3b0;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3b4 = (&instruction->first_operand)[2];
        }
        else {
          local_3b4 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3b4;
        break;
      }
      case 0x93: {
        std::uint32_t local_3c0;
        float local_3bc;
        float local_3b8;
        base.flags.bytes_00.animation_mode = 0x24;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3b8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3b8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3b8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3bc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3bc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3bc;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3c0 = (&instruction->first_operand)[2];
        }
        else {
          local_3c0 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3c0;
        break;
      }
      case 0x99: {
        std::uint32_t local_3c8;
        float local_3c4;
        base.flags.bytes_00.animation_mode = 0x2a;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3c4 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3c4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3c4;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3c8 = (&instruction->first_operand)[1];
        }
        else {
          local_3c8 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_3c8 << 1;
        break;
      }
      case 0x9a: {
        std::uint32_t local_3d0;
        float local_3cc;
        base.flags.bytes_00.animation_mode = 0x2b;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3cc = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3cc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3cc;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3d0 = (&instruction->first_operand)[1];
        }
        else {
          local_3d0 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.variables.field_00 = local_3d0 << 1;
        break;
      }
      case 0x9b: {
        std::uint32_t local_3dc;
        float local_3d8;
        float local_3d4;
        base.flags.bytes_00.animation_mode = 0x2c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3d4 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3d4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3d4;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3d8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3d8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3d8;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3dc = (&instruction->first_operand)[2];
        }
        else {
          local_3dc = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3dc << 1;
        break;
      }
      case 0x9c: {
        std::uint32_t local_3e8;
        float local_3e4;
        float local_3e0;
        base.flags.bytes_00.animation_mode = 0x2d;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3e0 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3e0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3e0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3e4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3e4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3e4;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3e8 = (&instruction->first_operand)[2];
        }
        else {
          local_3e8 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3e8 << 1;
        break;
      }
      case 0x9d: {
        std::uint32_t local_3f4;
        float local_3f0;
        float local_3ec;
        base.flags.bytes_00.animation_mode = 0x2e;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3ec = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3ec = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3ec;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3f0 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3f0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3f0;
        if ((instruction->operand_flags & 4U) == 0) {
          local_3f4 = (&instruction->first_operand)[2];
        }
        else {
          local_3f4 = this->integer_value((&instruction->first_operand)[2]);
        }
        base.variables.field_00 = local_3f4 << 1;
        break;
      }
      case 0x8b: {
        float local_3fc;
        float local_3f8;
        base.flags.bytes_00.animation_mode = 0x1c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_3f8 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_3f8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        base.vector_70.x = local_3f8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_3fc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_3fc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        base.vector_70.y = local_3fc;
        break;
      }
      case 0x8f: {
        base.flags.bytes_00.animation_mode = 0x20;
        break;
      }
      case 0x79: {
        std::uint32_t local_400;
        if ((instruction->operand_flags & 1U) == 0) {
          local_400 = (&instruction->first_operand)[0];
        }
        else {
          local_400 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.word_04 =
             base.flags.word_04 & 0xffffefff | (local_400 & 1) << 0xc;
        break;
      }
      case 0x40: {
        std::uint32_t local_408;
        std::uint32_t local_404;
        if ((instruction->operand_flags & 1U) == 0) {
          local_404 = (&instruction->first_operand)[0];
        }
        else {
          local_404 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.field_0a = base.flags.field_0a & 0xfc | (std::uint8_t)local_404 & 3;
        if ((instruction->operand_flags & 2U) == 0) {
          local_408 = (&instruction->first_operand)[1];
        }
        else {
          local_408 = this->integer_value((&instruction->first_operand)[1]);
        }
        base.flags.byte_09 = base.flags.byte_09 & 0x9f | ((std::uint8_t)local_408 & 3) << 5;
        break;
      }
      case 0x41: {
        std::uint32_t local_40c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_40c = (&instruction->first_operand)[0];
        }
        else {
          local_40c = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.scale_mode = (std::uint8_t)local_40c;
        base.flags.word_04 = base.flags.word_04 | 0x800000;
        break;
      }
      case 0x42: {
        std::uint32_t local_410;
        if ((instruction->operand_flags & 1U) == 0) {
          local_410 = (&instruction->first_operand)[0];
        }
        else {
          local_410 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.word_04 =
             base.flags.word_04 & 0xffffffdf | (local_410 & 1) << 5;
        break;
      }
      case 0x46: {
        std::uint32_t local_414;
        if ((instruction->operand_flags & 1U) == 0) {
          local_414 = (&instruction->first_operand)[0];
        }
        else {
          local_414 = this->integer_value((&instruction->first_operand)[0]);
        }
        base.flags.word_04 =
             base.flags.word_04 & 0xffbfffff | (local_414 & 1) << 0x16;
        break;
      }
      case 6: {
        std::uint32_t local_418;
        if ((instruction->operand_flags & 2U) == 0) {
          local_418 = (&instruction->first_operand)[1];
        }
        else {
          local_418 = this->integer_value((&instruction->first_operand)[1]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_418;
        break;
      }
      case 7: {
        float local_41c;
        if ((instruction->operand_flags & 2U) == 0) {
          local_41c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_41c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_41c;
        break;
      }
      case 0x12: {
        std::uint32_t local_424;
        std::uint32_t local_420;
        if ((instruction->operand_flags & 2U) == 0) {
          local_420 = (&instruction->first_operand)[1];
        }
        else {
          local_420 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_424 = (&instruction->first_operand)[2];
        }
        else {
          local_424 = this->integer_value((&instruction->first_operand)[2]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_420 + local_424;
        break;
      }
      case 0x13: {
        float local_710;
        float local_42c;
        float local_428;
        if ((instruction->operand_flags & 2U) == 0) {
          local_428 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_428 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_42c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_42c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_710 = local_428 + local_42c;
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_710;
        break;
      }
      case 0x14: {
        std::uint32_t local_434;
        std::uint32_t local_430;
        if ((instruction->operand_flags & 2U) == 0) {
          local_430 = (&instruction->first_operand)[1];
        }
        else {
          local_430 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_434 = (&instruction->first_operand)[2];
        }
        else {
          local_434 = this->integer_value((&instruction->first_operand)[2]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_430 - local_434;
        break;
      }
      case 0x15: {
        float local_714;
        float local_43c;
        float local_438;
        if ((instruction->operand_flags & 2U) == 0) {
          local_438 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_438 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_43c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_43c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_714 = local_438 - local_43c;
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_714;
        break;
      }
      case 0x16: {
        std::uint32_t local_444;
        std::uint32_t local_440;
        if ((instruction->operand_flags & 2U) == 0) {
          local_440 = (&instruction->first_operand)[1];
        }
        else {
          local_440 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_444 = (&instruction->first_operand)[2];
        }
        else {
          local_444 = this->integer_value((&instruction->first_operand)[2]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_440 * local_444;
        break;
      }
      case 0x17: {
        float local_718;
        float local_44c;
        float local_448;
        if ((instruction->operand_flags & 2U) == 0) {
          local_448 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_448 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_44c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_44c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_718 = local_448 * local_44c;
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_718;
        break;
      }
      case 0x18: {
        std::uint32_t local_454;
        std::uint32_t local_450;
        if ((instruction->operand_flags & 2U) == 0) {
          local_450 = (&instruction->first_operand)[1];
        }
        else {
          local_450 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_454 = (&instruction->first_operand)[2];
        }
        else {
          local_454 = this->integer_value((&instruction->first_operand)[2]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = (int)local_450 / (int)local_454;
        break;
      }
      case 0x19: {
        float local_71c;
        float local_45c;
        float local_458;
        if ((instruction->operand_flags & 2U) == 0) {
          local_458 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_458 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_45c = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_45c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_71c = local_458 / local_45c;
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_71c;
        break;
      }
      case 0x1a: {
        std::uint32_t local_464;
        std::uint32_t local_460;
        if ((instruction->operand_flags & 2U) == 0) {
          local_460 = (&instruction->first_operand)[1];
        }
        else {
          local_460 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_464 = (&instruction->first_operand)[2];
        }
        else {
          local_464 = this->integer_value((&instruction->first_operand)[2]);
        }
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = (int)local_460 % (int)local_464;
        break;
      }
      case 0x1b: {
        float local_720;
        float local_46c;
        float local_468;
        if ((instruction->operand_flags & 4U) == 0) {
          local_468 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_468 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_46c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_46c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_720 = scalar_math::floating_remainder(local_46c,local_468);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_720;
        break;
      }
      case 8: {
        int *local_474;
        std::uint32_t local_470;
        if ((instruction->operand_flags & 2U) == 0) {
          local_470 = (&instruction->first_operand)[1];
        }
        else {
          local_470 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_474 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_474 = *local_474 + local_470;
        break;
      }
      case 9: {
        float *local_47c;
        float local_478;
        if ((instruction->operand_flags & 2U) == 0) {
          local_478 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_478 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_47c = this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_47c = *local_47c + local_478;
        break;
      }
      case 10: {
        int *local_484;
        std::uint32_t local_480;
        if ((instruction->operand_flags & 2U) == 0) {
          local_480 = (&instruction->first_operand)[1];
        }
        else {
          local_480 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_484 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_484 = *local_484 - local_480;
        break;
      }
      case 0xb: {
        float *local_48c;
        float local_488;
        if ((instruction->operand_flags & 2U) == 0) {
          local_488 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_488 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_48c = this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_48c = *local_48c - local_488;
        break;
      }
      case 0xc: {
        int *local_494;
        std::uint32_t local_490;
        if ((instruction->operand_flags & 2U) == 0) {
          local_490 = (&instruction->first_operand)[1];
        }
        else {
          local_490 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_494 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_494 = *local_494 * local_490;
        break;
      }
      case 0xd: {
        float *local_49c;
        float local_498;
        if ((instruction->operand_flags & 2U) == 0) {
          local_498 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_498 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_49c = this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_49c = *local_49c * local_498;
        break;
      }
      case 0xe: {
        int *local_4a4;
        std::uint32_t local_4a0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4a0 = (&instruction->first_operand)[1];
        }
        else {
          local_4a0 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_4a4 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_4a4 = *local_4a4 / (int)local_4a0;
        break;
      }
      case 0xf: {
        float *local_4ac;
        float local_4a8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4a8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4a8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_4ac = this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_4ac = *local_4ac / local_4a8;
        break;
      }
      case 0x10: {
        int *local_4b4;
        std::uint32_t local_4b0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4b0 = (&instruction->first_operand)[1];
        }
        else {
          local_4b0 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_4b4 = this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0);
        *local_4b4 = *local_4b4 % (int)local_4b0;
        break;
      }
      case 0x11: {
        float local_724;
        float local_4bc;
        float local_4b8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4b8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4b8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if ((instruction->operand_flags & 1U) == 0) {
          local_4bc = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_4bc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        local_724 = scalar_math::floating_remainder(local_4bc,local_4b8);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_724;
        break;
      }
      case 0x1c: {
        std::uint32_t local_728;
        std::uint32_t local_4c0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4c0 = (&instruction->first_operand)[1];
        }
        else {
          local_4c0 = this->integer_value((&instruction->first_operand)[1]);
        }
        local_728 = native_polygon_random_5ba4c4.bounded(local_4c0);
        *this->integer_argument(reinterpret_cast<std::int32_t*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_728;
        break;
      }
      case 0x1d: {
        float local_72c;
        float local_4c4;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4c4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4c4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_72c = native_polygon_random_5ba4c4.range(local_4c4);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_72c;
        break;
      }
      case 0x1e: {
        float local_730;
        float local_4c8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4c8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4c8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_730 = scalar_math::sine(local_4c8);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_730;
        break;
      }
      case 0x1f: {
        float local_734;
        float local_4cc;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4cc = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4cc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_734 = scalar_math::cosine(local_4cc);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_734;
        break;
      }
      case 0x20: {
        float local_738;
        float local_4d0;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4d0 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4d0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_738 = native_sqrt_439850(local_4d0);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_738;
        break;
      }
      case 0x21: {
        float local_73c;
        float local_4d4;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4d4 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4d4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_73c = scalar_math::arcsine(local_4d4);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_73c;
        break;
      }
      case 0x22: {
        float local_740;
        float local_4d8;
        if ((instruction->operand_flags & 2U) == 0) {
          local_4d8 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_4d8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        local_740 = scalar_math::arccosine(local_4d8);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_740;
        break;
      }
      case 0x23: {
        float local_744;
        float local_4dc;
        if ((instruction->operand_flags & 1U) == 0) {
          local_4dc = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_4dc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        local_744 = (float)add_angles(local_4dc, 0.0f);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_744;
        break;
      }
      case 0x24: {
        float *local_74c;
        float *local_748;
        float local_4e4;
        float local_4e0;
        if ((instruction->operand_flags & 8U) == 0) {
          local_4e0 = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_4e0 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        if ((instruction->operand_flags & 4U) == 0) {
          local_4e4 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_4e4 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        polar_components(
            this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0),
            this->float_argument(reinterpret_cast<float*>(&instruction->first_operand) + 1,static_cast<std::uint16_t>(instruction->operand_flags),1),
            local_4e4,local_4e0);
        break;
      }
      case 0x25: {
        float local_760;
        float local_75c;
        float local_758;
        float local_754;
        float local_4f0;
        float local_4ec;
        float local_4e8;
        Vector3 local_c0;
        if ((instruction->operand_flags & 4U) == 0) {
          local_4e8 = (reinterpret_cast<float*>(&instruction->first_operand)[2]);
        }
        else {
          local_4e8 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[2]));
        }
        local_4f0 = local_4e8;
        if ((instruction->operand_flags & 8U) == 0) {
          local_4ec = (reinterpret_cast<float*>(&instruction->first_operand)[3]);
        }
        else {
          local_4ec = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[3]));
        }
        local_754 = local_4ec - local_4f0;
        local_758 = native_polygon_random_5ba4c4.signed_unit();
        local_75c = local_754 * local_758 + local_4f0;
        local_760 = native_polygon_random_5ba4c4.radians();
        polar(*reinterpret_cast<Vector3*>(&local_c0),local_760,local_75c);
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand),static_cast<std::uint16_t>(instruction->operand_flags),0) = local_c0.x;
        *this->float_argument(reinterpret_cast<float*>(&instruction->first_operand) + 1,static_cast<std::uint16_t>(instruction->operand_flags),1) = local_c0.y;
        break;
      }
      case 0x6e: {
        base.flags.byte_0b = base.flags.byte_0b & 0xfc | (reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 3;
        break;
      }
      case 0x67: {
        base.flags.word_04 =
             base.flags.word_04 & 0xffffff7f | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 7;
        break;
      }
      case 0x38: {
        this->set_layer((std::uint32_t)(reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]));
        break;
      }
      case 0x5f: {
        base.flags.byte_09 = base.flags.byte_09 & 0xe3 | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 7) << 2;
        break;
      }
      case 0x60: {
        base.flags.field_0a = base.flags.field_0a & 0x1f | (char)reinterpret_cast<std::uint16_t*>(&instruction->first_operand)[0] << 5;
        break;
      }
      case 0x3b: {
        base.flags.word_04 =
             base.flags.word_04 & 0xfffffdff | ((reinterpret_cast<std::uint8_t*>(&instruction->first_operand)[0]) & 1) << 9;
        break;
      }
      case 0x28: {
        std::uint32_t local_4f8;
        std::uint32_t local_4f4;
        if ((instruction->operand_flags & 1U) == 0) {
          local_4f4 = (&instruction->first_operand)[0];
        }
        else {
          local_4f4 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_4f8 = (&instruction->first_operand)[1];
        }
        else {
          local_4f8 = this->integer_value((&instruction->first_operand)[1]);
        }
        if (local_4f4 == local_4f8) {
LAB_00434d6a:
          (timer_4c8=static_cast<std::int32_t>((reinterpret_cast<std::int32_t*>(&instruction->first_operand)[3])));
          base.field_28 = (&instruction->first_operand)[2];
          goto LAB_0042b831;
        }
        break;
      }
      case 0x29: {
        float local_500;
        float local_4fc;
        if ((instruction->operand_flags & 1U) == 0) {
          local_4fc = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_4fc = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_500 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_500 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_4fc == local_500) goto LAB_00434d6a;
        break;
      }
      case 0x2a: {
        std::uint32_t local_508;
        std::uint32_t local_504;
        if ((instruction->operand_flags & 1U) == 0) {
          local_504 = (&instruction->first_operand)[0];
        }
        else {
          local_504 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_508 = (&instruction->first_operand)[1];
        }
        else {
          local_508 = this->integer_value((&instruction->first_operand)[1]);
        }
        if (local_504 != local_508) goto LAB_00434d6a;
        break;
      }
      case 0x2b: {
        float local_510;
        float local_50c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_50c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_50c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_510 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_510 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_50c != local_510) goto LAB_00434d6a;
        break;
      }
      case 0x2c: {
        std::uint32_t local_518;
        std::uint32_t local_514;
        if ((instruction->operand_flags & 1U) == 0) {
          local_514 = (&instruction->first_operand)[0];
        }
        else {
          local_514 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_518 = (&instruction->first_operand)[1];
        }
        else {
          local_518 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((int)local_514 < (int)local_518) goto LAB_00434d6a;
        break;
      }
      case 0x2d: {
        float local_520;
        float local_51c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_520 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_520 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_51c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_51c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_520 < local_51c) goto LAB_00434d6a;
        break;
      }
      case 0x2e: {
        std::uint32_t local_528;
        std::uint32_t local_524;
        if ((instruction->operand_flags & 1U) == 0) {
          local_524 = (&instruction->first_operand)[0];
        }
        else {
          local_524 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_528 = (&instruction->first_operand)[1];
        }
        else {
          local_528 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((int)local_524 <= (int)local_528) goto LAB_00434d6a;
        break;
      }
      case 0x2f: {
        float local_530;
        float local_52c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_530 = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_530 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_52c = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_52c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_530 <= local_52c) goto LAB_00434d6a;
        break;
      }
      case 0x30: {
        std::uint32_t local_538;
        std::uint32_t local_534;
        if ((instruction->operand_flags & 1U) == 0) {
          local_534 = (&instruction->first_operand)[0];
        }
        else {
          local_534 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_538 = (&instruction->first_operand)[1];
        }
        else {
          local_538 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((int)local_538 < (int)local_534) goto LAB_00434d6a;
        break;
      }
      case 0x31: {
        float local_540;
        float local_53c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_53c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_53c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_540 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_540 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_540 < local_53c) goto LAB_00434d6a;
        break;
      }
      case 0x32: {
        std::uint32_t local_548;
        std::uint32_t local_544;
        if ((instruction->operand_flags & 1U) == 0) {
          local_544 = (&instruction->first_operand)[0];
        }
        else {
          local_544 = this->integer_value((&instruction->first_operand)[0]);
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_548 = (&instruction->first_operand)[1];
        }
        else {
          local_548 = this->integer_value((&instruction->first_operand)[1]);
        }
        if ((int)local_548 <= (int)local_544) goto LAB_00434d6a;
        break;
      }
      case 0x33: {
        float local_550;
        float local_54c;
        if ((instruction->operand_flags & 1U) == 0) {
          local_54c = (reinterpret_cast<float*>(&instruction->first_operand)[0]);
        }
        else {
          local_54c = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[0]));
        }
        if ((instruction->operand_flags & 2U) == 0) {
          local_550 = (reinterpret_cast<float*>(&instruction->first_operand)[1]);
        }
        else {
          local_550 = this->float_value((reinterpret_cast<float*>(&instruction->first_operand)[1]));
        }
        if (local_550 <= local_54c) goto LAB_00434d6a;
        break;
      }
      }
LAB_00434dad:
      base.field_28 = (std::uint32_t)(std::uint16_t)instruction->byte_advance + base.field_28;
      goto LAB_0042b831;
    }
  }
  goto LAB_00434fb5;
code_r0x0042df46:
  timer_4c8--;
LAB_00434dce:
  if ((base.flags.word_04 >> 0x13 & 1) != 0) {
    this->update_motion();
  }
  if ((base.flags.byte_09 >> 1 & 1) != 0) {
    vector_5bc += native_vector_5c5540;
  }
  if ((base.flags.word_04 >> 0xb & 1) != 0) {
    Vector3 corners[4];
    this->project_corners(corners);
    normalize_coordinates_438eb0(&base.vectors_378[0],reinterpret_cast<const Vector2*>(&corners[0]));
    normalize_coordinates_438eb0(&base.vectors_378[1],reinterpret_cast<const Vector2*>(&corners[1]));
    normalize_coordinates_438eb0(&base.vectors_378[2],reinterpret_cast<const Vector2*>(&corners[2]));
    normalize_coordinates_438eb0(&base.vectors_378[3],reinterpret_cast<const Vector2*>(&corners[3]));
    base.vector_398.x=base.vectors_378[1].x-base.vectors_378[0].x;
    base.vector_398.y=base.vectors_378[1].y-base.vectors_378[0].y;
  }
  this->update_interpolations();
  this->update_geometry();
  timer_4c8++;
LAB_00434fb5:
  default_timer_clock.set(initial_clock_value);
  return 0;
LAB_00434fd1:
  default_timer_clock.set(initial_clock_value);
  return 1;
}

} // namespace th20
