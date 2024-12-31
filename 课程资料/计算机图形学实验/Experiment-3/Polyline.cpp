#include "Polyline.h"
RECT Poly_line::rect={240,0,300,30};
COLORREF Poly_line::color=RGB(136,15,255);

void Draw_Polyline(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,Poly_line::color);
    SelectObject(hdc,hPen);

    auto A=arr[0], B=arr[1];
    MoveToEx(hdc,A.x,A.y,nullptr);
    LineTo(hdc,B.x,B.y);
    arr.erase(arr.begin());
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    debug("Polylines.size="+to_string(polylines.size()));
    if(polylines.back().size()==0)
        polylines.back().push_back(A);
    polylines.back().push_back(B);
}