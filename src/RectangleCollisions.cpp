#include "CollisionGeometry.hpp"
#include "MotionMath.hpp"
#include "Angle.hpp"
namespace th20::geometry {
const int rectangle_edges[4][2] = {{0,1},{1,2},{2,3},{3,0}};
namespace { constexpr float pi = 3.1415927410125732f; }
#ifdef _MSC_VER
#pragma strict_gs_check(push, on)
#endif
int segment_intersection_point(float& x, float& y,
                              float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy) {
    if (!segment_intersection(ax,ay,bx,by,cx,cy,dx,dy)) return 0;
    float slope_a, intercept_a, slope_b, intercept_b;
    int vertical_a=line_parameters(slope_a,intercept_a,ax,ay,bx,by);
    int vertical_b=line_parameters(slope_b,intercept_b,cx,cy,dx,dy);
    if (!vertical_a && !vertical_b) {
        x=(intercept_b-intercept_a)/(slope_a-slope_b);
        y=(intercept_b-intercept_a)*slope_a/(slope_a-slope_b)+intercept_a;
    } else if (vertical_a && vertical_b) {
        if (absolute(ax-cx)<0.001f) { x=ax; y=ay; return 1; }
        return 0;
    } else if (vertical_a) {
        x=ax; y=slope_b*ax+intercept_b;
    } else {
        x=cx; y=slope_a*cx+intercept_a;
    }
    return 1;
}
int line_rectangle_intersections(Vector3& first,Vector3& second,const Vector3& point,
                                 float direction,float cx,float cy,float width,float height,float rectangle_direction) {
    Vector2 corners[4];
    Vector2 line[3];
    corners[0].x=-width/2.0f; corners[0].y=-height/2.0f;
    corners[1].x=-width/2.0f; corners[1].y= height/2.0f;
    corners[2].x= width/2.0f; corners[2].y= height/2.0f;
    corners[3].x= width/2.0f; corners[3].y=-height/2.0f;
    if (direction!=0.0f) rotate_xy_array(corners,corners,rectangle_direction,4);
    for (int i=0;i<4;++i) { corners[i].x+=cx; corners[i].y+=cy; }
    line[0].x=point.x; line[0].y=point.y;
    line[1].x=1000.0f; line[1].y=0.0f;
    rotate_xy(line[2],line[1],direction);
    line[1].x=line[0].x+line[2].x; line[1].y=line[0].y+line[2].y;
    line[0].x=line[0].x-line[2].x; line[0].y=line[0].y-line[2].y;
    Vector3 hits[2];
    int found=0;
    for (int i=0;i<4;++i) {
        if (segment_intersection_point(hits[found].x,hits[found].y,line[0].x,line[0].y,line[1].x,line[1].y,
              corners[rectangle_edges[i][0]].x,corners[rectangle_edges[i][0]].y,
              corners[rectangle_edges[i][1]].x,corners[rectangle_edges[i][1]].y)) {
            ++found;
            if (found>=2) break;
        }
    }
    if (found==0) return 0;
    if (found==2) {
        if (squared_norm_xy(line[0].x-hits[0].x,line[0].y-hits[0].y)<
            squared_norm_xy(line[0].x-hits[1].x,line[0].y-hits[1].y)) {
            first.x=hits[0].x; first.y=hits[0].y;
            second.x=hits[1].x; second.y=hits[1].y;
        } else {
            first.x=hits[1].x; first.y=hits[1].y;
            second.x=hits[0].x; second.y=hits[0].y;
        }
    } else {
        first.x=hits[0].x; first.y=hits[0].y;
        second.x=hits[0].x; second.y=hits[0].y;
    }
    return 1;
}
float nearest_width_segment(const Vector3& center,float width,float direction,const Vector3& point,Vector3& output) {
    Vector3 delta;
    Vector3 closest;
    delta=point-center;
    rotate_xy(delta,delta,-direction);
    if (delta.x>-width/2.0f && delta.x<width/2.0f) closest.x=delta.x;
    else if (delta.x>0.0f) closest.x=width/2.0f;
    else if (delta.x<0.0f) closest.x=-width/2.0f;
    closest.y=0.0f;
    closest.z=0.0f;
    float distance=distance_xy(closest,delta);
    rotate_xy(closest,closest,direction);
    output=center+closest;
    return distance;
}
bool segment_regular_polygon(float ax,float ay,float bx,float by,float cx,float cy,float radius,float direction,int sides) {
    Vector3 edge[2];
    Vector3 radial(radius,0.0f,0.0f);
    for (int i=0;i<sides;++i) {
        rotate_xy(edge[0],radial,direction);
        direction+=pi*2.0f/sides;
        direction=normalize_angle(direction);
        rotate_xy(edge[1],radial,direction);
        edge[0]+={cx,cy,0.0f}; edge[1]+={cx,cy,0.0f};
        if (segment_intersection(edge[0].x,edge[0].y,edge[1].x,edge[1].y,ax,ay,bx,by)) return true;
    }
    return false;
}
bool segment_star(float ax,float ay,float bx,float by,float cx,float cy,float ra,float rb,float direction,int sides) {
    Vector3 edge[2];
    Vector3 radial_a(ra,0.0f,0.0f);
    Vector3 radial_b(rb,0.0f,0.0f);
    for (int i=0;i<sides*2;++i) {
        rotate_xy(edge[0],*(i%2==0? &radial_a:&radial_b),direction);
        direction+=pi*2.0f/sides/2.0f;
        direction=normalize_angle(direction);
        rotate_xy(edge[1],*(i%2!=0? &radial_a:&radial_b),direction);
        edge[0]+={cx,cy,0.0f}; edge[1]+={cx,cy,0.0f};
        if (segment_intersection(edge[0].x,edge[0].y,edge[1].x,edge[1].y,ax,ay,bx,by)) return true;
    }
    return false;
}
bool rectangle_circle(float x,float y,float width,float height,float direction,float cx,float cy,float radius) {
    Vector3 delta;
    delta.x=cx-x; delta.y=cy-y;
    rotate_xy(delta,delta,-direction);
    if (absolute(delta.x)<=width/2.0f+radius && absolute(delta.y)<=height/2.0f) return true;
    if (absolute(delta.x)<=width/2.0f && absolute(delta.y)<=height/2.0f+radius) return true;
    x=delta.x-width/2.0f; y=delta.y-height/2.0f;
    if (x*x+y*y<radius*radius) return true;
    x=width/2.0f+delta.x; y=delta.y-height/2.0f;
    if (x*x+y*y<radius*radius) return true;
    x=delta.x-width/2.0f; y=height/2.0f+delta.y;
    if (x*x+y*y<radius*radius) return true;
    x=width/2.0f+delta.x; y=height/2.0f+delta.y;
    if (x*x+y*y<radius*radius) return true;
    return false;
}
bool rectangle_ellipse(float x,float y,float width,float height,float direction,
                       float cx,float cy,float axis_x,float axis_y,float ellipse_direction) {
    float maximum_axis=axis_x>axis_y?axis_x:axis_y;
    float maximum_extent=width>height?width:height;
    Vector3 delta;
    Vector3 sample;
    delta.x=x-cx; delta.y=y-cy;
    rotate_xy(delta,delta,-ellipse_direction);
    Vector3 extents(width,height,0.0f);
    rotate_xy(extents,extents,normalize_angle(direction-ellipse_direction));
    if (maximum_extent>maximum_axis) {
        int count=static_cast<int>(axis_x+axis_y)/4;
        if (count<8) count=8;
        for (int i=0;i<count;++i) {
            ellipse_polar(sample,direction,axis_x,axis_y);
            direction+=pi*2.0f/count;
            if (rectangle_point(sample.x,sample.y,delta.x,delta.y,extents.x,extents.y)) return true;
        }
    } else {
        int count=static_cast<int>(maximum_extent/8.0f);
        if (count<3) count=3;
        sample.y=-extents.y/2.0f;
        for (int row=0;row<count;++row) {
            sample.x=-extents.x/2.0f;
            for (int column=0;column<count;++column) {
                if (ellipse_point(sample.x+delta.x,sample.y+delta.y,0.0f,0.0f,axis_x,axis_y,0.0f)) return true;
                sample.x+=extents.x/(count-1);
            }
            sample.y+=extents.y/(count-1);
        }
    }
    return false;
}
bool rectangle_regular_polygon(float x,float y,float width,float height,float direction,
                               float cx,float cy,float radius,float shape_direction,int sides) {
    if (rectangle_point(cx,cy,x,y,width,height)) return true;
    if (regular_polygon_point(x,y,cx,cy,radius,shape_direction,sides)) return true;
    Vector3 corners[4];
    corners[0].x=-width/2.0f; corners[0].y=-height/2.0f;
    corners[1].x=-width/2.0f; corners[1].y= height/2.0f;
    corners[2].x= width/2.0f; corners[2].y= height/2.0f;
    corners[3].x= width/2.0f; corners[3].y=-height/2.0f;
    if (direction!=0.0f) rotate_xy_array(corners,corners,direction,4);
    for (int i=0;i<4;++i) corners[i]+={x,y,0.0f};
    if (segment_regular_polygon(corners[0].x,corners[0].y,corners[1].x,corners[1].y,cx,cy,radius,shape_direction,sides)) return true;
    if (segment_regular_polygon(corners[1].x,corners[1].y,corners[2].x,corners[2].y,cx,cy,radius,shape_direction,sides)) return true;
    if (segment_regular_polygon(corners[2].x,corners[2].y,corners[3].x,corners[3].y,cx,cy,radius,shape_direction,sides)) return true;
    if (segment_regular_polygon(corners[3].x,corners[3].y,corners[0].x,corners[0].y,cx,cy,radius,shape_direction,sides)) return true;
    return false;
}
bool rectangle_rectangle(float x,float y,float width,float height,float direction,
                         float cx,float cy,float other_width,float other_height,float other_direction) {
    Vector2 first[4];
    Vector2 second[4];
    if (distance_xy(x,cx,y,cy)>=norm_xy(width/2.0f,height/2.0f)+norm_xy(other_width/2.0f,other_height/2.0f)) return false;
    first[0].x=-width/2.0f; first[0].y=-height/2.0f;
    first[1].x=-width/2.0f; first[1].y= height/2.0f;
    first[2].x= width/2.0f; first[2].y= height/2.0f;
    first[3].x= width/2.0f; first[3].y=-height/2.0f;
    if (direction!=0.0f) rotate_xy_array(first,first,direction,4);
    second[0].x=-other_width/2.0f; second[0].y=-other_height/2.0f;
    second[1].x=-other_width/2.0f; second[1].y= other_height/2.0f;
    second[2].x= other_width/2.0f; second[2].y= other_height/2.0f;
    second[3].x= other_width/2.0f; second[3].y=-other_height/2.0f;
    if (other_direction!=0.0f) rotate_xy_array(second,second,other_direction,4);
    for (int i=0;i<4;++i) {
        first[i].x+=x; first[i].y+=y; second[i].x+=cx; second[i].y+=cy;
    }
    if (rectangle_contains_any_four(x,y,width,height,direction,second)) return true;
    if (rectangle_contains_any_four(cx,cy,other_width,other_height,other_direction,first)) return true;
    for (int i=0;i<4;++i) {
        for (int j=0;j<4;++j) {
            if (segment_intersection(first[rectangle_edges[i][0]].x,first[rectangle_edges[i][0]].y,
                                     first[rectangle_edges[i][1]].x,first[rectangle_edges[i][1]].y,
                                     second[rectangle_edges[j][0]].x,second[rectangle_edges[j][0]].y,
                                     second[rectangle_edges[j][1]].x,second[rectangle_edges[j][1]].y)) return true;
        }
    }
    return false;
}
bool rectangle_star(float x,float y,float width,float height,float direction,
                    float cx,float cy,float ra,float rb,float shape_direction,int sides) {
    if (rectangle_point(cx,cy,x,y,width,height)) return true;
    if (star_point(x,y,cx,cy,ra,rb,shape_direction,sides)) return true;
    Vector3 corners[4];
    corners[0].x=-width/2.0f; corners[0].y=-height/2.0f;
    corners[1].x=-width/2.0f; corners[1].y= height/2.0f;
    corners[2].x= width/2.0f; corners[2].y= height/2.0f;
    corners[3].x= width/2.0f; corners[3].y=-height/2.0f;
    if (direction!=0.0f) rotate_xy_array(corners,corners,direction,4);
    for (int i=0;i<4;++i) corners[i]+={x,y,0.0f};
    if (segment_star(corners[0].x,corners[0].y,corners[1].x,corners[1].y,cx,cy,ra,rb,shape_direction,sides)) return true;
    if (segment_star(corners[1].x,corners[1].y,corners[2].x,corners[2].y,cx,cy,ra,rb,shape_direction,sides)) return true;
    if (segment_star(corners[2].x,corners[2].y,corners[3].x,corners[3].y,cx,cy,ra,rb,shape_direction,sides)) return true;
    if (segment_star(corners[3].x,corners[3].y,corners[0].x,corners[0].y,cx,cy,ra,rb,shape_direction,sides)) return true;
    return false;
}
bool rectangle_contains_any_four(float x,float y,float width,float height,float direction,const Vector2* points) {
    Vector2 relative[4];
    relative[0].x=points[0].x-x; relative[0].y=points[0].y-y;
    relative[1].x=points[1].x-x; relative[1].y=points[1].y-y;
    relative[2].x=points[2].x-x; relative[2].y=points[2].y-y;
    relative[3].x=points[3].x-x; relative[3].y=points[3].y-y;
    if (direction!=0.0f) rotate_xy_array(relative,relative,-direction,4);
    if (absolute(relative[0].x)<=width/2.0f && absolute(relative[0].y)<=height/2.0f) return true;
    if (absolute(relative[1].x)<=width/2.0f && absolute(relative[1].y)<=height/2.0f) return true;
    if (absolute(relative[2].x)<=width/2.0f && absolute(relative[2].y)<=height/2.0f) return true;
    if (absolute(relative[3].x)<=width/2.0f && absolute(relative[3].y)<=height/2.0f) return true;
    return false;
}
bool rotated_rectangle_point(float x,float y,float width,float height,float direction,float px,float py) {
    Vector3 delta;
    delta.x=px-x; delta.y=py-y;
    if (direction!=0.0f) rotate_xy(delta,delta,-direction);
    return absolute(delta.x)<=width/2.0f && absolute(delta.y)<=height/2.0f ? 1 : 0;
}
#ifdef _MSC_VER
#pragma strict_gs_check(pop)
#endif
}
