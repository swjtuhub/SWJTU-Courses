#include "GeometryRelations.h"

int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    else return 1;
}

double dis_point_to_point(POINT P, POINT Q)
{
    return sqrt((P.x-Q.x)*(P.x-Q.x)+(P.y-Q.y)*(P.y-Q.y));
}

double dis_point_to_line(POINT P, Line A)
{
    return fabs((Point(P)-Point(A.s))^(Point(A.e)-Point(A.s)))/A.length();
}


// 将向量逆时针旋转 90 度
Point rotleft(Point P)
{
    return {-P.y,P.x};
}

// 将向量顺时针旋转 90 度
Point rotright(Point P)
{
    return {P.y,-P.x};
}

// 化为长度为r的向量
Point trunc(Point P, double r)
{
    double l=len({0,0},P);
    if(fabs(l)<=1e-6)
        return P;
    r/=l;
    return {P.x*r, P.y*r};
}

// 求点P在直线A上的投影
Point lineprog(POINT P, Line A)
{
    return A.s + ( (((A.e-A.s)*(P-A.s)) * (A.e-A.s)) / (pow(len(A.e,A.s),2)) );
}

// 直线和圆的关系
int relation_line_and_circle(Circle A, Line B)
{
    double dst=dis_point_to_line(A.O,B);
    if(dst<A.r)   return 2;
    else if(fabs(dst-A.r)<=eps)  return 1;
    return 0;
}

// 两圆的关系
// 5 相离; 4 外切; 3 相交; 2 内切; 1 内含
int relation_circle_and_circle(Circle a, Circle b)
{
    double d=len(a.O,b.O);
    if(d>a.r+b.r)   return 5;
    if(fabs(d-a.r-b.r)<=eps)   return 4;
    double l=fabs(a.r-b.r);
    if(d-a.r-b.r<0 && d-l>0)    return 3;
    if(fabs(d-l)<=eps) return 2;
    if(d-l<0)   return 1;
}

// 两线段相交判断
// 2 规范相交
// 1 非规范相交
// 0 不相交
int seg_cross_seg(Line A, Line B)
{
    POINT s1=A.s, e1=A.e, s2=B.s, e2=B.e;
    int d1=sgn((e1-s1)^(s2-s1));
    int d2=sgn((e1-s1)^(e2-s1));
    int d3=sgn((e2-s2)^(s1-s2));
    int d4=sgn((e2-s2)^(e1-s2));
    if((d1^d2)==-2 && (d3^d4)==-2)
        return 2;
    return  (d1==0 && sgn((s2-s1)*(s2-e1))<=0) ||
            (d2==0 && sgn((e2-s1)*(e2-e1))<=0) ||
            (d3==0 && sgn((s1-s2)*(s1-e2))<=0) ||
            (d4==0 && sgn((e1-s2)*(e1-e2))<=0);
}

// 点是否在多边形内
int is_point_in_polygon(POINT P, polygon A)
{
    return A.contain_point(P);
}

int is_point_in_circle(POINT P, Circle C)
{
    return C.contain_point(P);
}

int is_point_in_rect(POINT P, Rect R)
{
    return R.contain_point(P);
}


//求直线和圆的交点
pair<POINT,POINT> Circle_cross_line(Circle A, Line B)
{
    if(!relation_line_and_circle(A,B)) return make_pair(POINT{-1,-1},POINT{-1,-1});
    Point P=lineprog(A.O,B);
    double d1=dis_point_to_line(A.O,B);
    double d2=sqrt(A.r*A.r-d1*d1);
    Point a=P-A.O;
    Point b=trunc(rotright(a),d2);
    Point P1=P+b, P2=P-b;
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