#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"
#include "Curve.h"
#include "Poly.h"
#include "Select_point.h"
#include "Select_circle.h"
#include "Show.h"

// #define DEBUG
#include "debug.h"
using namespace std;
typedef pair<int,int> pii;
const int N = 4000;
const double eps = 1e-6;
int state=0;

vector<POINT> arr;
vector<Line> lines;
vector<Circle> circles;
vector<Rect> rects;
vector<Curve> curves;
vector<Poly> polylines;
vector<POINT> Cross_points; // 交点
// 求交：求直线和直线，直线和圆，圆和圆之间的交点，并给出交点的坐标。
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
        //
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        
        Draw_Title(hWnd, hdc);
        Show_graphics(hWnd,hdc);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        POINT bt;
        GetCursorPos(&bt);
        bt.y-=25;
        auto note=[&](int s, string str)
        {
            state=s;
            arr.clear();
            MessageBox(hWnd,LPSTR(str.c_str()),LPSTR("Note"),MB_OK);
        };
        arr.push_back(bt);

        if(PtInRect(&Line::rect,bt))
            note(0,"Line");
        else if(PtInRect(&Circle::rect,bt))
            note(1,"Circle");
        else if(PtInRect(&Rect::rect,bt))
            note(2,"Rect");
        else if(PtInRect(&Curve::rect,bt))
            note(3,"Curve");
        else if(PtInRect(&Poly::rect,bt))
            note(4,"Poly");
        else if(PtInRect(&Select_point::rect,bt))
            note(5,"Select_point");
        else
        {
            if(arr.size()==2 && state==0)
                Draw_line(hWnd,arr);
            if(arr.size()==2 && state==1)
                Draw_circle(hWnd,arr);
            if(arr.size()==2 && state==2)
                Draw_rect(hWnd,arr);
            if(arr.size()==3 && state==3)
                Draw_curve(hWnd,arr);
            if(arr.size()==2 && state==4)
                Draw_Poly(hWnd,arr);
            if(state==5)   // 在交点附近
                Show_near_by_point(hWnd,bt);
            // string str="Cross points:\n";
            // for(auto P:Cross_points)
            //     str+=to_string(P)+"\n";
            // debug(str);
        }
        break;
    }
    case WM_MOUSEMOVE:
        //
        break;
    case WM_COMMAND:
        //
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
