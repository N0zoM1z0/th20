#include "CollisionGeometry.hpp"
#include "MotionMath.hpp"
#include <cassert>
#include <cmath>
#include <initializer_list>
using namespace th20;
using namespace th20::geometry;
namespace {
constexpr float quarter_turn = 1.5707963705062866f;
bool near(float a, float b) { return std::abs(a-b)<0.0002f; }
}
int main() {
    assert(squared_norm_xy(3,4)==25 && norm_xy(3,4)==5);
    assert(squared_distance_xy(1,4,2,6)==25 && distance_xy(1,4,2,6)==5);
    Vector3 a{1,2,-100}, b{4,6,999};
    assert(squared_distance_xy(a,b)==25 && distance_xy(a,b)==5);
    float slope=99, intercept=99;
    assert(line_parameters(slope,intercept,2,3,2.009f,7)==1);
    assert(slope==0 && intercept==2);
    assert(line_parameters(slope,intercept,0,3,0.01f,7)==0);
    assert(near(slope,400) && intercept==3);
    float x=91,y=92;
    assert(!segment_intersection_point(x,y,0,0,1,1,2,0,3,1));
    assert(x==91 && y==92);
    assert(segment_intersection_point(x,y,0,0,4,4,0,4,4,0));
    assert(x==2 && y==2);
    assert(segment_intersection_point(x,y,2,0,2,4,0,2,4,2));
    assert(x==2 && y==2);
    assert(segment_intersection_point(x,y,0,2,4,2,2,0,2,4));
    assert(x==2 && y==2);
    assert(segment_intersection_point(x,y,0,0,0,4,0,1,0,3));
    assert(x==0 && y==0); // Native vertical overlap selects the first endpoint.
    x=91; y=92;
    assert(!segment_intersection_point(x,y,0,4,0,0,0,1,0,3));
    assert(x==91 && y==92);
    Vector3 first{91,92,123},second{93,94,456},point{0,0,789};
    assert(line_rectangle_intersections(first,second,point,0,0,0,8,2,quarter_turn));
    assert(first.x==-4 && first.y==0 && second.x==4 && second.y==0);
    assert(first.z==123 && second.z==456 && point.z==789);
    assert(line_rectangle_intersections(first,second,point,0.001f,0,0,8,2,quarter_turn));
    assert(near(first.x,-1) && near(second.x,1));
    first={91,92,123}; second={93,94,456};
    assert(!line_rectangle_intersections(first,second,point,0,2001,0,8,2,0));
    assert(first.x==91 && first.y==92 && second.x==93 && second.y==94);
    assert(first.z==123 && second.z==456);
    Vector3 nearest;
    Vector3 center{10,20,30},target{13,24,999};
    assert(nearest_width_segment(center,4,0,target,nearest)==std::sqrt(17.0f));
    assert(nearest.x==12 && nearest.y==20 && nearest.z==30);
    target={13,24,999};
    assert(near(nearest_width_segment(center,4,quarter_turn,target,target),std::sqrt(13.0f)));
    assert(near(target.x,10) && near(target.y,22) && target.z==30);
    Vector2 pair[2]={{3,4},{-2,5}},rotated[2];
    rotate_xy_array(rotated,pair,quarter_turn,2);
    assert(near(rotated[0].x,-4) && near(rotated[0].y,3));
    assert(near(rotated[1].x,-5) && near(rotated[1].y,-2));
    rotate_xy(pair[0],pair[0],quarter_turn);
    assert(near(pair[0].x,-4) && near(pair[0].y,3));
    Vector3 three[2]={{3,4,11},{-2,5,22}};
    rotate_xy_array(three,three,quarter_turn,2);
    assert(near(three[0].x,-4) && near(three[0].y,3) && three[0].z==11);
    assert(near(three[1].x,-5) && near(three[1].y,-2) && three[1].z==22);
    rotate_xy_array<Vector2>(nullptr,nullptr,0,0);
    rotate_xy_array<Vector3>(nullptr,nullptr,0,0);
    // Forward overlap reads the preceding write on the next iteration.
    Vector2 overlap[3]={{1,2},{3,4},{5,6}};
    rotate_xy_array(overlap+1,overlap,0,2);
    assert(overlap[1].x==1 && overlap[2].x==1 && overlap[2].y==2);
    assert(rectangle_circle(0,0,2,2,0,2,0,1)); // Inclusive straight strip.
    assert(!rectangle_circle(0,0,2,2,0,4,5,5)); // Strict corner at distance 5.
    assert(rectangle_circle(0,0,2,2,0,3.99f,4.99f,5));
    assert(rectangle_circle(0,0,8,2,quarter_turn,0,4,0.5f));
    assert(!rectangle_circle(0,0,8,2,quarter_turn,4,0,0.5f));
    for (int sides : {3,4,5,8}) {
        assert(segment_regular_polygon(-20,0,20,0,0,0,10,0,sides));
        assert(!segment_regular_polygon(-1,0,1,0,0,0,10,0,sides));
        assert(segment_star(-20,0,20,0,0,0,10,5,0,sides));
        assert(!segment_star(-1,0,1,0,0,0,10,5,0,sides));
        assert(rectangle_regular_polygon(0,0,2,2,0,0,0,10,0,sides));
        assert(!rectangle_regular_polygon(100,100,2,2,0,0,0,10,0,sides));
        assert(rectangle_star(0,0,2,2,0,0,0,10,5,0,sides));
        assert(!rectangle_star(100,100,2,2,0,0,0,10,5,0,sides));
    }
    assert(!segment_regular_polygon(-20,0,20,0,0,0,10,0,0));
    assert(!segment_star(-20,0,20,0,0,0,10,5,0,-1));
    // Native center shortcuts still use the unrotated rectangle.
    assert(rectangle_regular_polygon(0,0,20,2,quarter_turn,8,0,0.1f,0,4));
    assert(rectangle_star(0,0,20,2,quarter_turn,8,0,0.1f,0.05f,0,4));
    assert(rectangle_ellipse(0,0,4,2,0,0,0,10,5,0)); // Grid branch.
    assert(rectangle_ellipse(0,0,20,12,0,0,0,5,3,0)); // Perimeter branch.
    assert(!rectangle_ellipse(100,100,4,2,0,0,0,10,5,0));
    assert(!rectangle_ellipse(0,0,20,12,quarter_turn,0,0,5,3,0)); // Signed rotated extent.
    Vector2 points[4]={{20,20},{21,20},{21,21},{20,21}};
    assert(!rectangle_contains_any_four(0,0,4,2,0,points));
    for (int i=0;i<4;++i) {
        Vector2 saved=points[i];
        points[i]={2,1};
        assert(rectangle_contains_any_four(0,0,4,2,0,points));
        points[i]={0,1.9f};
        assert(rectangle_contains_any_four(0,0,4,2,quarter_turn,points));
        points[i]=saved;
    }
    assert(rotated_rectangle_point(0,0,4,2,0,2,1));
    assert(!rectangle_point(2,1,0,0,4,2));
    assert(rotated_rectangle_point(0,0,4,2,quarter_turn,0,1.9f));
    assert(!rotated_rectangle_point(0,0,4,2,quarter_turn,1.9f,0));
    assert(rectangle_rectangle(0,0,10,10,0,0,0,2,2,0)); // Containment.
    assert(!rectangle_rectangle(0,0,10,10,0,100,0,2,2,0)); // Radius rejection.
    assert(rectangle_rectangle(0,0,8,1,0,0,0,8,1,quarter_turn)); // Edge-only crossing.
    assert(!rectangle_rectangle(0,0,4,2,0,4,2,4,2,0)); // Bounding circles touch.
}
