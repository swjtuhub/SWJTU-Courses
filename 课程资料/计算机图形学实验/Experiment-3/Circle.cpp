#include "Circle.h"
#define DEBUG
RECT Circle::rect={60,0,120,30};
COLORREF Circle::color=RGB(255,242,45);

void MidPoint_circle(HDC hdc, int xc, int yc, int radius, COLORREF color) 
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SetPixel(hdc, xc + x, yc + y, color);
        SetPixel(hdc, xc + y, yc + x, color);
        SetPixel(hdc, xc - y, yc + x, color);
        SetPixel(hdc, xc - x, yc + y, color);
        SetPixel(hdc, xc - x, yc - y, color);
        SetPixel(hdc, xc - y, yc - x, color);
        SetPixel(hdc, xc + y, yc - x, color);
        SetPixel(hdc, xc + x, yc - y, color);

        if (err <= 0) {
            y++;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x--;
            err -= 2 * x + 1;
        }
    }
}

void Bresenham_circle(HDC hdc, int xc, int yc, int radius, COLORREF color) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        SetPixel(hdc, xc + x, yc + y, color);
        SetPixel(hdc, xc - x, yc + y, color);
        SetPixel(hdc, xc + x, yc - y, color);
        SetPixel(hdc, xc - x, yc - y, color);
        SetPixel(hdc, xc + y, yc + x, color);
        SetPixel(hdc, xc - y, yc + x, color);
        SetPixel(hdc, xc + y, yc - x, color);
        SetPixel(hdc, xc - y, yc - x, color);

        if (d < 0)
            d = d + 4 * x + 6;
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Draw_circle(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    auto [x1,y1]=arr[0];
    auto [x2,y2]=arr[1];
    int r=sqrt(pow(x1-x2,2)+pow(y1-y2,2))+0.5;
    arr.clear();
    if(state == State_macros::Mid_point_circle)
        MidPoint_circle(hdc,x1,y1,r,Circle::color);
    if(state == State_macros::Bresenham_circle)
        Bresenham_circle(hdc,x1,y1,r,Circle::color);
    if(Thickline == true)
        if(state == State_macros::Mid_point_circle)
            for(int i=-2;i<=2;i++)
                MidPoint_circle(hdc,x1,y1,r+i,Circle::color);
        else
            for(int i=-2;i<=2;i++)
                Bresenham_circle(hdc,x1,y1,r+i,Circle::color);

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

