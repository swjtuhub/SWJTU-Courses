#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"
#include "Curve.h"
#include "Polyline.h"
#include "Polygon.h"
#include "B_spline_curve.h"
#include "State_macros.h"
#include "Select_point.h"
#include "Select_circle.h"
#include "Fill_color.h"
#include "Show.h"
#include "Variables.h"
#include "GeometryRelations.h"

// #define DEBUG
#include "debug.h"
using namespace std;
typedef pair<int,int> pii;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow = SW_SHOWNORMAL)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = (LPSTR) "SimplePaint";

    RegisterClass(&wc);

    HWND hWnd = CreateWindow((LPSTR) "SimplePaint", (LPSTR) "Simple Paint", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // Draw_button(hWnd);
        Draw_menu(hWnd);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        
        // Draw_Title(hWnd, hdc);
        Show_graphics(hWnd,hdc);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        POINT bt;
        GetCursorPos(&bt);
        bt.y-=44;       // y轴调参
        arr.push_back(bt);

        if((state==State_macros::Bresenham_line || state==State_macros::Mid_point_line) && arr.size()==2)
            Draw_line(hWnd,arr,state);
        
        if((state==State_macros::Bresenham_circle || state==State_macros::Mid_point_circle) && arr.size()==2)
            Draw_circle(hWnd,arr);
        
        if(state==State_macros::Rect && arr.size()==2)
            Draw_rect(hWnd,arr);
        
        if(state==State_macros::Curve && arr.size()==3)
            Draw_curve(hWnd,arr);
        
        if(state==State_macros::Polyline && arr.size()==2)
            Draw_Polyline(hWnd,arr);
        
        if(state==State_macros::Polygon && arr.size()==2)
            Draw_polygon(hWnd,arr);
        
        if(state==State_macros::Select_point)   // 在交点附近
            Show_near_by_point(hWnd,bt);
        
        if(state==State_macros::Scanline_fill || state==State_macros::Flood_fill)
            Fill_color(hWnd,bt);


        string str="state = "+to_string(state)+"\n";
        str+="arr.size="+to_string(arr.size())+"\n";
        debug(str);
        
        break;
    }
    case WM_MOUSEMOVE:
        //
        break;
    case WM_COMMAND:
        //
        last_state=state;
        state=LOWORD(wParam);

        if(last_state==State_macros::Polygon)       // 最后一笔, 让多边形封闭
        {
            if(polygons.size() && polygons.back().size()<3)
                polygons.pop_back();
            if(polygons.size())
                polygons.back().Seal(hWnd);
        }

        if(last_state == State_macros::B_spline_curve && arr.size()>=4)
            Draw_B_spline_curve(hWnd);
        
        if(state==State_macros::Polyline)
            polylines.resize(polylines.size()+1);
        
        if(state==State_macros::Polygon)
            polygons.resize(polygons.size()+1);

        if(state==State_macros::Thickline)
            Thickline = ~Thickline;

        arr.clear();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
