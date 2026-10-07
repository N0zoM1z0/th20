#include "EclRuntime.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"

namespace th20 {
#define ECL_INTEGER_ARGUMENT(ins, index) (reinterpret_cast<std::int32_t*>((ins)+1)[index])
// Each stack expression owns its tagged operands and bypasses instruction-level
// dropping; arithmetic explicitly clears the shared instruction's drop count.
#define ECL_ARITHMETIC(type, tag, operation) { \
    type b,a; stack.pop(4,&b,tag); stack.pop(4,&a,tag); \
    a operation b; stack.push(4,&a,tag); ins->stack_drop=0; goto advance; \
}
#define ECL_COMPARISON(type, tag, operation) { \
    type b,a; stack.pop(4,&b,tag); stack.pop(4,&a,tag); \
    std::int32_t result=a operation b ? 1 : 0;stack.push(4,&result,'i');goto advance; \
}
#define ECL_LOGICAL(operation) { \
    std::int32_t b,a;stack.pop(4,&b,'i');stack.pop(4,&a,'i'); \
    std::int32_t result=a operation b;stack.push(4,&result,'i');goto advance; \
}
#define ECL_LOGICAL_NOT(type, tag) { \
    type a;stack.pop(4,&a,tag);std::int32_t result=a==0?1:0;stack.push(4,&result,'i');goto advance; \
}
#define ECL_UNARY(type, tag, operation) { \
    type value;stack.pop(4,&value,tag);value=operation value; \
    stack.push(4,&value,tag);goto advance; \
}
#define ECL_POST_DECREMENT() { \
    std::int32_t value=integer_argument(0);*integer_destination(0)=value-1; \
    stack.push(4,&value,'i');goto advance; \
}
int EclRuntime::tick(float delta) {
    if(position.offset==-1) return -1;
    if(position.subroutine==-1) return -1;
    EclInstruction* ins=current();
check_time:
    while(ins->time<=time) {
        if(!(ins->rank & rank)) goto advance;
        {
            switch(ins->opcode) {
            case 0: break;
            case 1: goto ended;
            case 10: {
                stack.leave_frame();
                if(!stack.pointer_value()) goto ended;
                {
                    stack.pop(4,&position.subroutine,0);
                    stack.pop(4,&position.offset,0);
                    stack.pop(4,&time,0);
                }
                {
                    std::int32_t pointer;
                    stack.pop(4,&pointer,0);
                    stack.set_pointer(pointer);
                }
                ins=current();
                if(position.offset<0) goto ended;
                break;
            }
            case 15: manager->spawn(-1,0); goto advance;
            case 21: manager->terminate_async(); goto advance;
            case 16:
                manager->spawn(consuming_integer_value(1,ECL_INTEGER_ARGUMENT(ins,(ECL_INTEGER_ARGUMENT(ins,0)+4u)/4)),1);
                goto advance;
            case 17: {
                auto* link=manager->find_runtime(integer_argument(0));
                if(link) link->node_value()->position.offset=-1;
                break;
            }
            case 18: {
                auto* link=manager->find_runtime(integer_argument(0));
                if(link) link->node_value()->flags.bits |= 1;
                break;
            }
            case 19: {
                auto* link=manager->find_runtime(integer_argument(0));
                if(link) link->node_value()->flags.bits &= ~1u;
                break;
            }
            case 20: {
                auto* link=manager->find_runtime(integer_argument(0));
                if(link) link->node_value()->signal=integer_argument(1);
                break;
            }
            case 11:
                ins->stack_drop=0;
                if(call_into(this,0,0)) goto ended;
                ins=current();
                goto check_time;
            case 22: break;
            case 14: {
                std::int32_t value;
                stack.pop(4,&value,'i');
                if(value) goto jump;
                break;
            }
            case 13: {
                std::int32_t value;
                stack.pop(4,&value,'i');
                if(value) break;
            }
                [[fallthrough]];
            case 12:
            jump:
                time=static_cast<float>(ECL_INTEGER_ARGUMENT(ins,1));
                position.offset+=ECL_INTEGER_ARGUMENT(ins,0);
                ins=reinterpret_cast<EclInstruction*>(reinterpret_cast<std::uint8_t*>(ins)+ECL_INTEGER_ARGUMENT(ins,0));
                goto check_time;
            case 23: time-=integer_argument(0); break;
            case 24: time-=float_argument(0); break;
            case 40: stack.enter_frame(integer_argument(0)); break;
            case 41: stack.leave_frame(); break;
            case 42: {std::int32_t value=consuming_integer(0);stack.push(4,&value,'i');goto advance;}
            case 44: {float value=consuming_float(0);stack.push(4,&value,'f');goto advance;}
            case 43: stack.pop(4,integer_destination(0),'i');goto advance;
            case 45: stack.pop(4,float_destination(0),'f');goto advance;
            case 50:ECL_ARITHMETIC(std::int32_t,'i',+=);break;
            case 52:ECL_ARITHMETIC(std::int32_t,'i',-=);break;
            case 54:ECL_ARITHMETIC(std::int32_t,'i',*=);break;
            case 56:ECL_ARITHMETIC(std::int32_t,'i',/=);break;
            case 58:ECL_ARITHMETIC(std::int32_t,'i',%=);break;
            case 51:ECL_ARITHMETIC(float,'f',+=);break;
            case 53:ECL_ARITHMETIC(float,'f',-=);break;
            case 55:ECL_ARITHMETIC(float,'f',*=);break;
            case 57:ECL_ARITHMETIC(float,'f',/=);break;
            case 59:ECL_COMPARISON(std::int32_t,'i',==);break;
            case 61:ECL_COMPARISON(std::int32_t,'i',!=);break;
            case 63:ECL_COMPARISON(std::int32_t,'i',<);break;
            case 65:ECL_COMPARISON(std::int32_t,'i',<=);break;
            case 67:ECL_COMPARISON(std::int32_t,'i',>);break;
            case 69:ECL_COMPARISON(std::int32_t,'i',>=);break;
            case 71:ECL_LOGICAL_NOT(std::int32_t,'i');break;
            case 60:ECL_COMPARISON(float,'f',==);break;
            case 62:ECL_COMPARISON(float,'f',!=);break;
            case 64:ECL_COMPARISON(float,'f',<);break;
            case 66:ECL_COMPARISON(float,'f',<=);break;
            case 68:ECL_COMPARISON(float,'f',>);break;
            case 70:ECL_COMPARISON(float,'f',>=);break;
            case 72:ECL_LOGICAL_NOT(float,'f');break;
            case 73:ECL_LOGICAL(||);break;
            case 74:ECL_LOGICAL(&&);break;
            case 75:ECL_LOGICAL(^);break;
            case 76:ECL_LOGICAL(|);break;
            case 77:ECL_LOGICAL(&);break;
            case 83:ECL_UNARY(std::int32_t,'i',-);break;
            case 84:ECL_UNARY(float,'f',-);break;
            case 78:ECL_POST_DECREMENT();break;
            case 79: {float value;stack.pop(4,&value,'f');float result=scalar_math::sine(value);stack.push(4,&result,'f');goto advance;}
            case 88: {float value;stack.pop(4,&value,'f');float result=scalar_math::square_root(value);stack.push(4,&result,'f');goto advance;}
            case 80: {float value;stack.pop(4,&value,'f');float result=scalar_math::cosine(value);stack.push(4,&result,'f');goto advance;}
            case 81: {Vector3 result;const float direction=normalize_angle(float_argument(2));const float length=float_argument(3);polar(result,direction,length);*float_destination(0)=result.x;*float_destination(1)=result.y;break;}
            case 85: {float x=float_argument(1),y=float_argument(2);*float_destination(0)=x*x+y*y;break;}
            case 86: {float x=float_argument(1),y=float_argument(2);*float_destination(0)=scalar_math::square_root(x*x+y*y);break;}
            case 82: *float_destination(0)=normalize_angle(float_argument(0));break;
            case 87: {
                float x0=float_argument(1),y0=float_argument(2),x1=float_argument(3),y1=float_argument(4);
                *float_destination(0)=scalar_math::arctangent(y1-y0,x1-x0);break;
            }
            case 89: {
                float first=float_argument(1),second=float_argument(2);
                *float_destination(0)=angle_difference(second,first);break;
            }
            case 90: {
                Vector3 input,result;input.x=float_argument(2);input.y=float_argument(3);
                float rotation=float_argument(4);
                rotate_xy(result,input,normalize_angle(rotation));
                *float_destination(0)=result.x;*float_destination(1)=result.y;break;
            }
            case 91: {
                std::int32_t index=integer_argument(0);
                if(interpolators.size()<index+1) interpolators.resize(index+1);
                if(integer_argument(2)<=0) {
                    interpolators[index].stop();
                    if(interpolators.size()==index+1)interpolators.pop_back();
                } else {
                    interpolators[index].position=position;
                    interpolators[index].sample();
                    interpolators[index].set_duration(integer_argument(2));
                    interpolators[index].set_mode(integer_argument(3));
                    float from=float_argument(4),to=float_argument(5);
                    interpolators[index].set_start(from);interpolators[index].set_end(to);
                    *float_destination(1)=from;
                    from=0;to=0;
                    interpolators[index].set_tangent_start(from);interpolators[index].set_tangent_end(to);
                    interpolators[index].reset_time();
                    interpolators[index].frame_base=stack.frame_value();
                }
                break;
            }
            case 92: {
                std::int32_t index=integer_argument(0);
                if(interpolators.size()<index+1) interpolators.resize(index+1);
                interpolators[index].position=position;
                interpolators[index].sample();
                interpolators[index].set_duration(integer_argument(2));
                interpolators[index].set_mode(integer_argument(3));
                float from=float_argument(4),to=float_argument(5);
                interpolators[index].set_start(from);interpolators[index].set_end(to);
                *float_destination(1)=from;
                from=float_argument(6);to=float_argument(7);
                interpolators[index].set_tangent_start(from);interpolators[index].set_tangent_end(to);
                interpolators[index].reset_time();
                interpolators[index].frame_base=stack.frame_value();break;
            }
            case 93: {
                Vector3 result;
                float low=float_argument(2);
                polar(result,script_random.radians(),(float_argument(3)-low)*script_random.signed_unit()+low);
                *float_destination(0)=result.x;*float_destination(1)=result.y;break;
            }
            case 94: {
                Vector3 input,result;
                float direction=float_argument(2),rotation=float_argument(4),length=float_argument(3);
                float direction_relative=normalize_angle(direction-rotation);
                polar(input,direction_relative,length);
                input.x=float_argument(5)*input.x;rotate_xy(result,input,rotation);result.z=0;
                *float_destination(0)=result.x;*float_destination(1)=result.y;break;
            }
            case 95: {Angle a(float_argument(1)),b(float_argument(2));*float_destination(0)=static_cast<float>(b)*2.0f-static_cast<float>(a);break;}
            case 96: {Angle value(float_argument(1));*float_destination(0)=static_cast<float>(value)>-3.1415927410125732421875f/2.0f && static_cast<float>(value)>3.1415927410125732421875f/2.0f?1.0f:-1.0f;break;}
            case 97: {Angle value(float_argument(1));*float_destination(0)=static_cast<float>(value)<0?-1.0f:1.0f;break;}
            case 46: *integer_destination(0)=integer_argument(2+integer_argument(1)*2);break;
            case 47: *float_destination(0)=float_argument(2+integer_argument(1)*2);break;
            case 30:break;
            case 31:break;
            default: {
                switch(manager->execute_opcode()) {
                case 0:goto drop;case -1:goto interpolate;case 1:goto check_time;
                }
                break;
            }
            }
        drop:
            if(ins->stack_drop) stack.set_pointer(stack.pointer_value()-ins->stack_drop);
        }
    advance:
        position.offset+=ins->length;
        ins=reinterpret_cast<EclInstruction*>(reinterpret_cast<std::uint8_t*>(ins)+ins->length);
    }
    time+=delta;
interpolate:
    for(auto& item:interpolators) {
        if(item.duration_value()) {
            auto* origin=manager->loader->instruction(item.position.subroutine,item.position.offset);
            *float_destination_at(origin,item.frame_base,1)=item.sample();
        }
    }
    return 0;
ended:
    position.offset=-1;position.subroutine=-1;return -1;
}
}
