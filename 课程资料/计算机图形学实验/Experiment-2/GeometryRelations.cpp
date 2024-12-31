#include "GeometryRelations.h"

double dis_point_to_line(POINT P, Line A)
{
    return fabs((P-A.s)^(A.e-A.s))/len(A.s,A.e);
}

//直线和圆的关系
int relation_line_and_circle(Circle A, Line B)
{
    double dst=dis_point_to_line(A.O,B);
    if(dst<A.r)   return 2;
    else if(fabs(dst-A.r)<=1e-6)  return 1;
    return 0;
}

//两圆的关系
//5 相离; 4 外切; 3 相交; 2 内切; 1 内含
int relation_circle_and_circle(Circle a, Circle b)
{
    double d=len(a.O,b.O);
    if(d>a.r+b.r)   return 5;
    if(fabs(d-a.r-b.r)<=1e-6)   return 4;
    double l=fabs(a.r-b.r);
    if(d-a.r-b.r<0 && d-l>0)    return 3;
    if(fabs(d-l)<=1e-6) return 2;
    if(d-l<0)   return 1;
}

//求直线和圆的交点
pair<POINT,POINT> Circle_cross_line(Circle A, Line B)
{
    if(!relation_line_and_circle(A,B)) return make_pair(POINT{-1,-1},POINT{-1,-1});
    Point a=lineprog(A.O,B);
    double d=dis_point_to_line(A.O,B);
    d=sqrt(A.r*A.r-d*d);
    if(fabs(d)<=1e-6)
        return make_pair(a.to_POINT(),POINT{-1,-1});
    Point P1=a+trunc(B.e-B.s,d);
    Point P2=a-trunc(B.e-B.s,d);
    P1.y+=20, P2.y+=20;
    return make_pair(P1.to_POINT(),P2.to_POINT());
}

//求两个圆的交点
pair<POINT,POINT> Circle_cross_circle(Circle A, Circle B)
{
    int rel=relation_circle_and_circle(A,B);
    if(rel==1 || rel==5)
        return make_pair(POINT{-1,-1},POINT{-1,-1});
    
    auto [x1,y1]=A.O;
    auto [x2,y2]=B.O;
    int r1=A.r, r2=B.r;
    double d=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    double l=(d*d+r1*r1-r2*r2)/(2*d);
    double h=sqrt(r1*r1-l*l);
    Point tmp=A.O+trunc((B.O-A.O),l);
    Point P1=tmp+trunc(rotleft(B.O-A.O),h);
    Point P2=tmp+trunc(rotright(B.O-A.O),h);
    if(rel==2 || rel==4)
        P2={-1,-1};
    return make_pair(P1.to_POINT(),P2.to_POINT());
}

/// 求直线和直线的交点
POINT Line_cross_line(Line l1, Line l2)
{
    double a1=l1.a, b1=l1.b, c1=l1.c;
    double a2=l2.a, b2=l2.b, c2=l2.c;
    int x=((b1*c2-b2*c1)/(a1*b2-a2*b1))+0.5;
    int y=-((a1*x+c1)/b1)+0.5;
    return {x,y};
}