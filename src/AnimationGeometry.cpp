#include "Animation.hpp"
#include "SpriteVertices.hpp"
#include "WindowState.hpp"
#include "MotionMath.hpp"
namespace th20 {
namespace { constexpr float pi = 3.1415927410125732f; }
float Animation::rotation_z_value() { return base.vector_38.z; }
float Animation::scale_x_value() { return base.vector_50.x; }
float Animation::scale_y_value() { return base.vector_50.y; }
Vector3& Animation::position(Vector3& output) {
    output = vector_5bc + base.vector_2c + base.vector_484;
    transform_position(output);
    return output;
}
Vector3& Animation::transform_position(Vector3& value) {
    if (base.flags.field_0c == 1 || base.flags.field_0c == 3) value *= window_state.scale_value();
    else if (base.flags.field_0c == 2 || base.flags.field_0c == 4) value *= window_state.scale_value() * 0.5f;
    if (parent_558 && !((base.flags.word_04 >> 12) & 1u)) {
        if ((base.flags.word_04 >> 5) & 1u) rotate_xy(value, value, parent_558->rotation_z_value());
        if ((base.flags.word_04 >> 22) & 1u) {
            value.x *= parent_558->scale_x_value();
            value.y *= parent_558->scale_y_value();
        }
        Vector3 parent_position;
        parent_558->position(parent_position);
        value += parent_position;
    } else {
        if (base.flags.layer_mode) {
            if (base.flags.layer_mode == 1) {
                value.x += float(window_state.field_0058_value());
                value.y += float(window_state.field_005c_value());
            } else {
                value.x += float(window_state.field_0060_value());
                value.y += float(window_state.field_0064_value());
            }
        }
    }
    return value;
}
void Animation::update_geometry() {
    switch (base.flags.bytes_00.field_00) {
    default: return;
    case 9: {
        std::int32_t count = base.variables.field_00;
        float angle = base.vector_38.z;
        float step = (pi * 2.0f) / float(count - 1);
        auto* vertex = static_cast<SpriteTexturedVertex*>(geometry);
        float uv = 0.0f;
        float uv_step = float(base.variables.field_04) / float(count - 1);
        Vector3 center;
        if (base.flags.bytes_00.field_00 == 9) position(center);
        else center = {0,0,0};
        base.flags.word_04 &= ~0x200000u;
        std::uint32_t first_color = base.color_490;
        std::uint32_t second_color = base.flags.color_mode ? base.color_494 : base.color_490;
        float first_radius = base.vector_50.x * 0.5f + base.vector_50.y;
        float second_radius = base.vector_50.y - base.vector_50.x * 0.5f;
        if (parent_55c && !((base.flags.word_04 >> 12) & 1u)) {
            first_radius = parent_55c->scale_x_value() * first_radius;
            second_radius = parent_55c->scale_y_value() * second_radius;
        }
        if (base.flags.field_0c == 1) { first_radius *= window_state.scale; second_radius *= window_state.scale; }
        else if (base.flags.field_0c == 2) { first_radius = (window_state.scale * 0.5f) * first_radius; second_radius = (window_state.scale * 0.5f) * second_radius; }
        for (std::int32_t i=0;i<count-1;++i) {
            vertex->reciprocal_w=1.0f;vertex->color=first_color;
            vertex->u=base.vectors_378[0].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,first_radius);vertex->position.z=0.0f;vertex->position+=center;++vertex;
            vertex->reciprocal_w=1.0f;vertex->color=second_color;
            vertex->u=base.vectors_378[1].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,second_radius);vertex->position.z=0.0f;vertex->position+=center;++vertex;
            uv+=uv_step;angle=add_angles(angle,step);
        }
        vertex[0]=static_cast<SpriteTexturedVertex*>(geometry)[0];vertex[0].v=uv+base.field_7c;
        vertex[1]=static_cast<SpriteTexturedVertex*>(geometry)[1];vertex[1].v=uv+base.field_7c;
        break;
    }
    case 47: {
        std::int32_t count=base.variables.field_00;
        float angle=base.vector_38.z;
        float step=(pi*2.0f)/float(count-1);
        auto* vertex=static_cast<SpriteWorldTexturedVertex*>(geometry);
        float uv=0.0f;
        float uv_step=float(base.variables.field_04)/float(count-1);
        Vector3 center;
        center={0,0,0};
        base.flags.word_04&=~0x200000u;
        std::uint32_t first_color=base.color_490;
        std::uint32_t second_color=base.flags.color_mode?base.color_494:base.color_490;
        float first_radius=base.variables.field_10*0.5f+base.variables.field_14;
        float second_radius=base.variables.field_14-base.variables.field_10*0.5f;
        if(parent_55c && !((base.flags.word_04>>12)&1u)) {
            first_radius=parent_55c->scale_x_value()*first_radius;
            second_radius=parent_55c->scale_y_value()*second_radius;
        }
        if(base.flags.field_0c==1) {first_radius*=window_state.scale;second_radius*=window_state.scale;}
        else if(base.flags.field_0c==2) {first_radius=(window_state.scale*0.5f)*first_radius;second_radius=(window_state.scale*0.5f)*second_radius;}
        for(std::int32_t i=0;i<count-1;++i) {
            vertex->color=first_color;vertex->u=base.vectors_378[0].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,first_radius);vertex->position.z=0;vertex->position+=center;++vertex;
            vertex->color=second_color;vertex->u=base.vectors_378[1].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,second_radius);vertex->position.z=0;vertex->position+=center;++vertex;
            uv+=uv_step;angle=add_angles(angle,step);
        }
        vertex[0]=static_cast<SpriteWorldTexturedVertex*>(geometry)[0];vertex[0].v=uv+base.field_7c;
        vertex[1]=static_cast<SpriteWorldTexturedVertex*>(geometry)[1];vertex[1].v=uv+base.field_7c;
        break;
    }
    case 48: {
        auto* vertices=static_cast<SpriteWorldTexturedVertex*>(geometry);
        base.flags.word_04&=~0x200000u;
        std::uint32_t first_color=base.color_490;
        std::uint32_t second_color=base.flags.color_mode?base.color_494:base.color_490;
        float radius=base.variables.field_10;
        if(parent_55c && !((base.flags.word_04>>12)&1u)) radius=parent_55c->scale_x_value()*radius;
        if(base.flags.field_0c==1)radius*=window_state.scale;
        else if(base.flags.field_0c==2)radius=(window_state.scale*0.5f)*radius;
        vertices[0].color=first_color;vertices[1].color=second_color;vertices[2].color=second_color;
        vertices[0].u=(base.vectors_378[1].x-base.vectors_378[0].x)/2.0f+base.vectors_378[0].x+base.field_78;
        vertices[0].v=base.vectors_378[0].y+base.field_7c;
        vertices[1].u=base.vectors_378[2].x+base.field_78;vertices[1].v=base.vectors_378[2].y+base.field_7c;
        vertices[2].u=base.vectors_378[3].x+base.field_78;vertices[2].v=base.vectors_378[3].y+base.field_7c;
        polar(vertices[0].position,-pi/2.0f,radius);
        polar(vertices[1].position,-pi/2.0f+(pi*2.0f)/3.0f*2.0f,radius);
        polar(vertices[2].position,-pi/2.0f+(pi*2.0f)/3.0f,radius);
        vertices[0].position.z=0;vertices[1].position.z=0;vertices[2].position.z=0;
        vertices[1].position-=vertices[0].position;vertices[2].position-=vertices[0].position;
        vertices[0].position=Vector3(0,0,0);
        break;
    }
    case 13:
    case 14: {
        std::int32_t count=base.variables.field_00;
        float angle=normalize_angle(base.vector_38.z-base.vector_38.x/2.0f);
        float step=base.vector_38.x/float(count-1);
        auto* vertex=static_cast<SpriteTexturedVertex*>(geometry);
        float uv=0.0f;
        float uv_step=float(base.variables.field_04)/float(count-1);
        Vector3 center;
        position(center);
        base.flags.word_04&=~0x200000u;
        if(base.flags.bytes_00.field_00==14)angle=normalize_angle(base.vector_38.z);
        std::uint32_t color=base.flags.color_mode?base.color_494:base.color_490;
        float first_radius=base.vector_50.x*0.5f+base.vector_50.y;
        float second_radius=base.vector_50.y-base.vector_50.x*0.5f;
        if(parent_55c && !((base.flags.word_04>>12)&1u)) {
            first_radius=parent_55c->scale_x_value()*first_radius;
            second_radius=parent_55c->scale_y_value()*second_radius;
        }
        if(base.flags.field_0c==1) {first_radius*=window_state.scale;second_radius*=window_state.scale;}
        else if(base.flags.field_0c==2) {first_radius=(window_state.scale*0.5f)*first_radius;second_radius=(window_state.scale*0.5f)*second_radius;}
        for(std::int32_t i=0;i<count;++i) {
            vertex->reciprocal_w=1.0f;vertex->color=color;
            vertex->u=base.vectors_378[0].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,first_radius);vertex->position.z=0;vertex->position+=center;++vertex;
            vertex->reciprocal_w=1.0f;vertex->color=color;
            vertex->u=base.vectors_378[1].x+base.field_78;vertex->v=uv+base.field_7c;
            polar(vertex->position,angle,second_radius);vertex->position.z=0;vertex->position+=center;++vertex;
            uv+=uv_step;angle=add_angles(angle,step);
        }
        break;
    }
    case 24:
    case 25: {
        std::int32_t count=base.variables.field_00;
        float angle=normalize_angle(base.variables.field_1c-base.variables.field_10/2.0f);
        float step=base.variables.field_10/float(count-1);
        auto* vertex=static_cast<SpriteWorldTexturedVertex*>(geometry);
        float uv=0.0f;
        float uv_step=float(base.variables.field_04)/float(count-1);
        base.flags.word_04&=~0x200000u;
        std::uint32_t color=base.flags.color_mode?base.color_494:base.color_490;
        Vector3 point;
        float half_height=base.variables.field_14/2.0f;
        float first_radius=base.variables.field_18;
        float second_radius=base.variables.field_18;
        if(base.flags.bytes_00.field_00==25) {
            half_height=0;first_radius-=base.variables.field_14/2.0f;second_radius+=base.variables.field_14/2.0f;
        }
        for(std::int32_t i=0;i<count;++i) {
            polar(point,angle,first_radius);
            vertex->color=color;vertex->u=base.vectors_378[0].x+base.field_78;vertex->v=uv+base.field_7c;
            vertex->position.x=point.x;vertex->position.y=half_height;vertex->position.z=point.y;++vertex;
            polar(point,angle,second_radius);
            vertex->color=color;vertex->u=base.vectors_378[1].x+base.field_78;vertex->v=uv+base.field_7c;
            vertex->position.x=point.x;vertex->position.y=-half_height;vertex->position.z=point.y;++vertex;
            uv+=uv_step;angle=add_angles(angle,step);
        }
        break;
    }
    }
}
}
