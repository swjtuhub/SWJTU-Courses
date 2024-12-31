#include "Select_point.h"
#define DEBUG
extern vector<POINT> Cross_points;
RECT Select_point::rect={300,0,420,30};
COLORREF Select_point::color=RGB(245,85,211);

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

// 在窗口中显示该交点坐标
void Show_near_by_point(HWND hWnd, POINT bt)
{
    POINT P=Near_by_cross_points(bt);
    if(P.x<0)
        return;
    string str='('+to_string(P.x)+','+to_string(P.y)+')'+'\n';
    Show_text(hWnd,P.x,P.y,str);
    debug(str);
}