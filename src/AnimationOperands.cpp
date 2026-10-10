#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "GameRandom.hpp"
#include "Graphics.hpp"
#include "MotionMath.hpp"
namespace th20 {
extern GameRandom progress_random;
std::int32_t* Animation::integer_argument(std::int32_t* value, std::uint16_t mask, std::int32_t index) {
    if (!(mask & (1u << index))) return value;
    switch(value[0]) {
    default: break;
    case 10000:return &base.variables.field_00;
    case 10001:return &base.variables.field_04;
    case 10002:return &base.variables.field_08;
    case 10003:return &base.variables.field_0c;
    case 10008:return &base.variables.field_2c;
    case 10009:return &base.variables.field_30;
    case 10029:return &base.variables.field_3c;
    }
    return value;
}
float* Animation::float_argument(float* value, std::uint16_t mask, std::int32_t index) {
    if (!(mask & (1u << index))) return value;
    switch(static_cast<std::int32_t>(value[0])) {
    default:break;
    case 10004:return &base.variables.field_10;
    case 10005:return &base.variables.field_14;
    case 10006:return &base.variables.field_18;
    case 10007:return &base.variables.field_1c;
    case 10013:return &base.vector_2c.x;
    case 10014:return &base.vector_2c.y;
    case 10015:return &base.vector_2c.z;
    case 10023:return &base.vector_38.x;
    case 10024:return &base.vector_38.y;
    case 10025:return &base.vector_38.z;
    case 10033:return &base.variables.field_20;
    case 10034:return &base.variables.field_24;
    case 10035:return &base.variables.field_28;
    case 10027:return &base.variables.field_34;
    case 10028:return &base.variables.field_38;
    }
    return value;
}
std::int32_t Animation::integer_value(std::int32_t value) {
    switch(value) {
    default:break;
    case 10000:return base.variables.field_00;
    case 10001:return base.variables.field_04;
    case 10002:return base.variables.field_08;
    case 10003:return base.variables.field_0c;
    case 10004:return static_cast<std::int32_t>(base.variables.field_10);
    case 10005:return static_cast<std::int32_t>(base.variables.field_14);
    case 10006:return static_cast<std::int32_t>(base.variables.field_18);
    case 10007:return static_cast<std::int32_t>(base.variables.field_1c);
    case 10033:return static_cast<std::int32_t>(base.variables.field_20);
    case 10034:return static_cast<std::int32_t>(base.variables.field_24);
    case 10035:return static_cast<std::int32_t>(base.variables.field_28);
    case 10008:return base.variables.field_2c;
    case 10009:return base.variables.field_30;
    case 10027:return static_cast<std::int32_t>(base.variables.field_34);
    case 10028:return static_cast<std::int32_t>(base.variables.field_38);
    case 10029:return base.variables.field_3c;
    case 10022:return progress_random.bounded(base.variables.field_3c);
    }
    return value;
}
float Animation::float_value(float value) {
    switch(static_cast<std::int32_t>(value)) {
    default:break;
    case 10000:return static_cast<float>(base.variables.field_00);
    case 10001:return static_cast<float>(base.variables.field_04);
    case 10002:return static_cast<float>(base.variables.field_08);
    case 10003:return static_cast<float>(base.variables.field_0c);
    case 10004:return base.variables.field_10;
    case 10005:return base.variables.field_14;
    case 10006:return base.variables.field_18;
    case 10007:return base.variables.field_1c;
    case 10033:return base.variables.field_20;
    case 10034:return base.variables.field_24;
    case 10035:return base.variables.field_28;
    case 10008:return static_cast<float>(base.variables.field_2c);
    case 10009:return static_cast<float>(base.variables.field_30);
    case 10011:return progress_random.range(base.variables.field_34);
    case 10012:return progress_random.signed_range(base.variables.field_34);
    case 10010:return progress_random.signed_range(base.variables.field_38);
    case 10013:return base.vector_2c.x;
    case 10014:return base.vector_2c.y;
    case 10015:return base.vector_2c.z;
    case 10023:return base.vector_38.x;
    case 10024:return base.vector_38.y;
    case 10025:return base.vector_38.z;
    case 10026:return rotation_sum().z;
    case 10016:return process_graphics.viewports[3].vector_00.x+process_graphics.viewports[3].vector_3c.x;
    case 10017:return process_graphics.viewports[3].vector_00.y+process_graphics.viewports[3].vector_3c.y;
    case 10018:return process_graphics.viewports[3].vector_00.z+process_graphics.viewports[3].vector_3c.z;
    case 10019:return process_graphics.viewports[3].vector_24.x;
    case 10020:return process_graphics.viewports[3].vector_24.y;
    case 10021:return process_graphics.viewports[3].vector_24.z;
    case 10027:return base.variables.field_34;
    case 10028:return base.variables.field_38;
    case 10029:return static_cast<float>(base.variables.field_3c);
    case 10022:return static_cast<float>(progress_random.next());
    case 10031:return progress_random.range(base.variables.field_34);
    case 10032:return progress_random.signed_range(base.variables.field_34);
    case 10030:return progress_random.signed_range(base.variables.field_38);
    }
    return value;
}
Vector3& Animation::rotation_sum() {
    vector_5d0=base.vector_38;
    if(parent_558 && !((base.flags.word_04>>12)&1u)) {
        vector_5d0+=parent_558->rotation_sum();
        base.vector_38.x=normalize_angle(base.vector_38.x);
        base.vector_38.y=normalize_angle(base.vector_38.y);
        base.vector_38.z=normalize_angle(base.vector_38.z);
    }
    return vector_5d0;
}
Vector3& Animation::transform_direction(Vector3& value, std::int32_t rotate, std::int32_t scale) {
    if(parent_558 && !((base.flags.word_04>>12)&1u)) {
        Animation* parent=parent_558;
        parent->transform_direction(value,(base.flags.word_04>>5)&1u,(base.flags.word_04>>22)&1u);
    }
    if(rotate) rotate_xy(value,value,rotation_z_value());
    if(scale) {value.x*=scale_x_value();value.y*=scale_y_value();}
    return value;
}
AnmInstruction* AnimationFile::script(std::int32_t index) { return scripts[index]; }
float GameRandom::range(float limit) { return unit()*limit; }
} // namespace th20
