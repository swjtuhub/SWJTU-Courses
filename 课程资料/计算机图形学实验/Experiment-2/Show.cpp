#include "Show.h"
extern vector<Line> lines;
extern vector<Circle> circles;
extern vector<Rect> rects;
extern vector<Curve> curves;
extern vector<Poly> polylines;

struct Select_point;

void Show_text(HWND hWnd, int x, int y, string str)
{
    PAINTSTRUCT ps;
    HDC hdc=GetDC(hWnd);
    SetBkMode(hdc,TRANSPARENT);
    TextOut(hdc,x+10,y+10,LPSTR(str.c_str()),str.length());
    EndPaint(hWnd,&ps);
}

void Draw_Title(HWND hWnd, HDC hdc)
{
    // 设置字体
    HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    SelectObject(hdc, hFont);
    // 设置文字颜色
    SetTextColor(hdc, RGB(0,0,0));
    // 设置背景为透明
    SetBkMode(hdc,TRANSPARENT);

    
    auto draw=[&](COLORREF color, RECT rect, string str)
    {
        HBRUSH hBtnBrush = CreateSolidBrush(color);
        FillRect(hdc, &rect, hBtnBrush);
        DeleteObject(hBtnBrush);
        TextOut(hdc, rect.left,8,LPSTR(str.c_str()),str.length());
    };

    draw(Line::color,Line::rect,"Line");            // 直线
    draw(Circle::color,Circle::rect,"Circle");      // 圆
    draw(Rect::color,Rect::rect,"Rect");            // 矩形
    draw(Curve::color,Curve::rect,"Curve");         // 曲线
    draw(Poly::color,Poly::rect,"Polyline");        // 多义线
    draw(Select_point::color,Select_point::rect,"Select_point.");  // 选点
    // draw()
}

void Show_graphics(HWND hWnd, HDC hdc)
{
    vector<POINT> arr;

    for(auto l:lines)
    {
        arr=vector<POINT>{l.s,l.e};
        Draw_line(hWnd,arr);
    }
    for(auto cir:circles)
    {
        arr.clear();
        arr.push_back(cir.O), arr.push_back({cir.O.x+cir.r, cir.O.y});
        Draw_circle(hWnd,arr);
    }
    for(auto r:rects)
    {
        arr=vector<POINT>{r.A,r.B};
        Draw_rect(hWnd,arr);
    }
    for(auto cur:curves)
    {
        arr=vector<POINT>{cur.A,cur.B,cur.C};
        Draw_curve(hWnd,arr);
    }
}