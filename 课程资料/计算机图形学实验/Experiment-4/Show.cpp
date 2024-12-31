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


// void Draw_Title(HWND hWnd, HDC hdc)
// {
//     // 设置字体
//     HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
//     SelectObject(hdc, hFont);
//     // 设置文字颜色
//     SetTextColor(hdc, RGB(0,0,0));
//     // 设置背景为透明
//     SetBkMode(hdc,TRANSPARENT);
//     auto draw=[&](COLORREF color, RECT rect, string str)
//     {
//         HBRUSH hBtnBrush = CreateSolidBrush(color);
//         FillRect(hdc, &rect, hBtnBrush);
//         DeleteObject(hBtnBrush);
//         TextOut(hdc, rect.left,8,LPSTR(str.c_str()),str.length());
//     };
//     draw(Line::color,Line::rect,"Line");            // 直线
//     draw(Circle::color,Circle::rect,"Circle");      // 圆
//     draw(Rect::color,Rect::rect,"Rect");            // 矩形
//     draw(Curve::color,Curve::rect,"Curve");         // 曲线
//     draw(Poly_line::color,Poly_line::rect,"Poly_line");        // 多义线
//     // draw(Select_point::color,Select_point::rect,"Select_point.");  // 选点
//     // draw()
// }

void Draw_button(HWND hWnd)
{
    // 创建一个按钮控件
    CreateWindow("BUTTON", "Click Me", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 50, 50, 100, 30, hWnd, (HMENU)3, NULL, NULL);
}

void Draw_menu(HWND hWnd)
{
    // 创建菜单
    HMENU hMenu=CreateMenu();

    // Draw graphic
    {
        HMENU hMenu_draw_graphic=CreateMenu();
        {
            // Line
            HMENU hMenu_line = CreateMenu();
            // append submenu to hMenu_line
            AppendMenu(hMenu_line, MF_STRING, State_macros::Mid_point_line, "Mid point line");
            AppendMenu(hMenu_line, MF_STRING, State_macros::Bresenham_line, "Bresenham line");

            // append submenu to hMenu
            AppendMenu(hMenu_draw_graphic,MF_POPUP,(UINT_PTR)hMenu_line,"Line");
        }
        {
            // Circle
            HMENU hMenu_circle = CreateMenu();
            AppendMenu(hMenu_circle, MF_STRING, State_macros::Mid_point_circle, "Mid point circle");
            AppendMenu(hMenu_circle, MF_STRING, State_macros::Bresenham_circle, "Bresenham circle");
            AppendMenu(hMenu_draw_graphic,MF_POPUP,(UINT_PTR)hMenu_circle,"Circle");
        }
        {
            // Rectangle
            HMENU hMenu_rect = CreateMenu();
            AppendMenu(hMenu_draw_graphic,MF_POPUP,State_macros::Rect,"Rectangle");
        }
        {
            // Curve
            HMENU hMenu_curve = CreateMenu();
            AppendMenu(hMenu_draw_graphic,MF_POPUP,State_macros::Curve,"Curve");
        }
        {
            // Poly line
            HMENU hMenu_polyline = CreateMenu();
            AppendMenu(hMenu_draw_graphic,MF_POPUP,State_macros::Polyline,"Polyline");
        }
        {
            // polygon
            HMENU hMenu_polygon = CreateMenu();
            AppendMenu(hMenu_draw_graphic,MF_POPUP,State_macros::Polygon,"Polygon");
        }
        {
            // B spline curve
            HMENU hMenu_b_spline_curve = CreateMenu();
            AppendMenu(hMenu_draw_graphic,MF_POPUP,State_macros::B_spline_curve,"B spline curve");
        }
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_draw_graphic,"Draw graphic");
    }

    // Select
    {
        HMENU hMenu_select = CreateMenu();
        AppendMenu(hMenu_select,MF_STRING,State_macros::Cross_point,"cross point");
        AppendMenu(hMenu_select,MF_STRING,State_macros::Circle_center,"circle center");
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_select,"Select");
    }

    // Fill color
    {
        HMENU hMenu_fill_color = CreateMenu();
        AppendMenu(hMenu_fill_color,MF_STRING,State_macros::Scanline_fill,"Scanline_fill");
        AppendMenu(hMenu_fill_color,MF_STRING,State_macros::Flood_fill,"Flood_fill");
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_fill_color,"Fill color");
    }

    // Thickline
    {
        AppendMenu(hMenu,MF_POPUP,State_macros::Thickline,"Thickline");
    }
    
    // Graphic transformation
    {
        HMENU hMenu_transformation = CreateMenu();
        AppendMenu(hMenu_transformation,MF_STRING,State_macros::Move,"Move");        // 平移
        AppendMenu(hMenu_transformation,MF_STRING,State_macros::Scale,"Scale");      // 缩放
        AppendMenu(hMenu_transformation,MF_STRING,State_macros::Rotate,"Rotate");    // 旋转
        {
            // Clip
            HMENU hMenu_clip = CreateMenu();
            AppendMenu(hMenu_clip, MF_STRING, State_macros::Clip_line,"Clip line");
            {
                // Clip polygon
                HMENU hMenu_clip_polygon = CreateMenu();
                AppendMenu(hMenu_clip_polygon,MF_STRING,State_macros::Sutherland_Hodgman,"Sutherland-Hodgman");
                AppendMenu(hMenu_clip_polygon,MF_STRING,State_macros::Weiler_Atherton,"Weiler-Atherton");
                AppendMenu(hMenu_clip, MF_POPUP,(UINT_PTR)hMenu_clip_polygon,"Clip polygon");
            }
            AppendMenu(hMenu_transformation,MF_POPUP,(UINT_PTR)hMenu_clip,"Clip");        // 裁剪
        }
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu_transformation,"Graphic transformation");
    }

    SetMenu(hWnd,hMenu);
}

void Draw_dashed_rectangle(HWND hWnd, RECT rect)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0)); // 创建虚线画笔
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, rect.left, rect.top, nullptr);
    LineTo(hdc, rect.right, rect.top);
    LineTo(hdc, rect.right, rect.bottom);
    LineTo(hdc, rect.left, rect.bottom);
    LineTo(hdc, rect.left, rect.top);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

void Show_selected_point(HWND hWnd, POINT P)
{
    HDC hdc=GetDC(hWnd);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Ellipse(hdc,P.x-3,P.y-3,P.x+3,P.y+3);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

bool Show_selected_rectangle(HWND hWnd, POINT P)
{
    auto [f,pos]=Select_graphic(P);
    if(f<0)
        return false;

    RECT rect=Get_selected_rectangle(P);
    Draw_dashed_rectangle(hWnd,rect);
    return true;
}

void Show_graphics(HWND hWnd)
{
    string str;
    HDC hdc=GetDC(hWnd);
    
    for(auto l:lines)
        l.Draw(hdc,Line::color);
    for(auto cir:circles)
        cir.Draw(hdc,Circle::color);
    for(auto r:rects)
        r.Draw(hdc,Rect::color);
    for(auto cur:curves)
        cur.Draw(hdc,Curve::color);
    for(auto pl:polylines)
        pl.Draw(hdc,Poly_line::color);
    for(auto py:polygons)
        py.Draw(hdc,polygon::color);
    for(auto bsc:B_spline_curves)
        bsc.Draw(hdc,B_spline_curve::color);
    // str="rects.size="+to_string(rects.size());
    // str="Show graphics\n";
    // debug(str);
}