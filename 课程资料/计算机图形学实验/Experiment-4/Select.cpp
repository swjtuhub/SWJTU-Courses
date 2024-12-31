#include "Select.h"

// 选取目标点附近的交点(有多个就取最近的)
POINT Near_by_cross_points(POINT P)
{
    auto [x0,y0]=P;
    double mn=1e9;
    POINT Q;
    for(auto [x,y]:Cross_points)
    {
        double dis=pow(x0-x,2) + pow(y0-y,2);
        if(dis<mn)
        {
            mn=dis;
            Q={x,y};
        }
    }
    if(mn<=10000)
        return Q;
    return {-1,-1};     // 附近没有交点
}

// 选取目标点附近的圆心(有多个就取最近的)
POINT Select_circle_center(POINT P)
{
    int idx=-1;
    double dis=1e9;
    for(int i=circles.size()-1; i>=0; i--)
        if(circles[i].contain_point(P) && dis>dis_point_to_point(P,circles[i].O))
        {
            idx=i;
            dis=dis_point_to_point(P,circles[i].O);
        }
    if(idx<0)
        return {-1,-1};
    return circles[idx].O;
}

// 在窗口中显示该交点坐标
void Show_point(HWND hWnd, POINT P)
{
    string str='('+to_string(P.x)+','+to_string(P.y)+')'+'\n';
    Show_text(hWnd,P.x,P.y,str);
    // debug(str);
}

void Show_cross_points(HWND hWnd, POINT P)
{
    auto Q=Near_by_cross_points(P);
    if(Q.x!=-1)
        Show_point(hWnd,Q);
}

void Show_circle_center(HWND hWnd, POINT P)
{
    auto Q=Select_circle_center(P);
    if(Q.x!=-1)
        Show_point(hWnd,Q);
}

template<typename T>
int Point_in_graphic(POINT P, vector<T> &arr)
{
    for(int i=arr.size()-1;i>=0;i--)
        if(arr[i].contain_point(P))
            return i;
    return -1;
}

// Line, Cricle, Rectangle, Polyline, Polygon, B_spline_curve
pair<int,int> Select_graphic(POINT P)
{
    string str="Select a graphic\n";
    // debug(str);
    int pos=-1;

    pos=Point_in_graphic(P,B_spline_curves);
    if(pos>=0)      return make_pair(State_macros::B_spline_curve,pos);

    pos=Point_in_graphic(P,polygons);
    if(pos>=0)     return make_pair(State_macros::Polygon,pos);

    pos=Point_in_graphic(P,polylines);
    if(pos>=0)     return make_pair(State_macros::Polyline,pos);

    pos=Point_in_graphic(P,curves);
    if(pos>=0) return make_pair(State_macros::Curve,pos);

    pos=Point_in_graphic(P,rects);
    if(pos>=0)     return make_pair(State_macros::Rect,pos);

    pos=Point_in_graphic(P,circles);
    if(pos>=0)     return make_pair(State_macros::Circle,pos);

    pos=Point_in_graphic(P,lines);
    if(pos>=0)     return make_pair(State_macros::Line,pos);

    return make_pair(-1,-1);
}