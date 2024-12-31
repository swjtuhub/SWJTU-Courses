#include "Show.h"

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
    draw(Poly_line::color,Poly_line::rect,"Poly_line");        // 多义线
    draw(Select_point::color,Select_point::rect,"Select_point.");  // 选点
    // draw()
}

void Draw_button(HWND hWnd)
{
    // 创建一个按钮控件
    CreateWindow("BUTTON", "Click Me", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 50, 50, 100, 30, hWnd, (HMENU)3, NULL, NULL);
}

void Draw_menu(HWND hWnd)
{
    // 创建菜单
    HMENU hMenu=CreateMenu();

    {
        // Line
        HMENU hMenu_line = CreateMenu();
        // append submenu to hMenu_line
        AppendMenu(hMenu_line, MF_STRING, State_macros::Mid_point_line, "Mid point line");
        AppendMenu(hMenu_line, MF_STRING, State_macros::Bresenham_line, "Bresenham line");

        // append submenu to hMenu
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_line,"Line");
    }
    {
        // Circle
        HMENU hMenu_circle = CreateMenu();
        AppendMenu(hMenu_circle, MF_STRING, State_macros::Mid_point_circle, "Mid point circle");
        AppendMenu(hMenu_circle, MF_STRING, State_macros::Bresenham_circle, "Bresenham circle");
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_circle,"Circle");
    }
    {
        // Rectangle
        HMENU hMenu_rect = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Rect,"Rectangle");
    }
    {
        // Curve
        HMENU hMenu_curve = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Curve,"Curve");
    }
    {
        // Poly line
        HMENU hMenu_polyline = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Polyline,"Polyline");
    }
    {
        // polygon
        HMENU hMenu_polygon = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Polygon,"Polygon");
    }
    {
        // Select point
        HMENU hMenu_select_point = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Select_point,"Select point");
    }
    {
        // B spline curve
        HMENU hMenu_b_spline_curve = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::B_spline_curve,"B spline curve");
    }
    {
        // Fill color
        HMENU hMenu_fill_color = CreateMenu();
        AppendMenu(hMenu_fill_color,MF_STRING,State_macros::Scanline_fill,"Scanline_fill");
        AppendMenu(hMenu_fill_color,MF_STRING,State_macros::Flood_fill,"Flood_fill");
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_fill_color,"Fill color");
    }
    {
        // Thickline
        HMENU hMenu_thickline = CreateMenu();
        AppendMenu(hMenu,MF_POPUP,State_macros::Thickline,"Thickline");
    }
    SetMenu(hWnd,hMenu);
}

void Show_graphics(HWND hWnd, HDC hdc)
{
    vector<POINT> arr;

    for(auto l:lines)
    {
        arr=vector<POINT>{l.s,l.e};
        Draw_line(hWnd,arr,State_macros::Bresenham_line);
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