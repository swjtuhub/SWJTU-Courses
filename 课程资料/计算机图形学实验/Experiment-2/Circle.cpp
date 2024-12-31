#include "Circle.h"
#define DEBUG
extern vector<Line> lines;
extern vector<Circle> circles;
extern vector<POINT> Cross_points;
RECT Circle::rect={60,0,120,30};
COLORREF Circle::color=RGB(255,242,45);

void Draw_circle(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HBRUSH hBrush=CreateSolidBrush(Circle::color);
    SelectObject(hdc,hBrush);
    SetBkMode(hdc,TRANSPARENT);

    auto [x1,y1]=arr[0];
    auto [x2,y2]=arr[1];
    int r=sqrt(pow(x1-x2,2)+pow(y1-y2,2))+0.5;
    Ellipse(hdc,x1-r,y1-r,x1+r,y1+r);
    arr.clear();
    DeleteObject(hBrush);
    ReleaseDC(hWnd,hdc);

    string str;
    str+="O: "+to_string(POINT{x1,y1})+",  r="+to_string(r)+'\n';
    auto Add_point=[&](pair<POINT,POINT> t)
    {
        auto [P,Q]=t;
        if(0<P.x && 0<P.y)
            str+="Cross Points: "+to_string(P)+'\n',
            Cross_points.push_back(P);
        if(0<Q.x && 0<Q.y)
            str+="Cross Points: "+to_string(Q)+'\n',
            Cross_points.push_back(Q);
    };
    Circle A(POINT{x1,y1},r);
    str+="Circle cross line:\n";
    for(auto B:lines)
        Add_point(Circle_cross_line(A,B));
        
    str+="\nCircle_cross_circle: \n";
    for(auto B:circles)
        Add_point(Circle_cross_circle(A,B));
    debug(str);
    circles.push_back(A);
}

