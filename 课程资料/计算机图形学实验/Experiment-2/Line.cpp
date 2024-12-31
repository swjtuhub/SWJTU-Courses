#include "Line.h"
extern vector<Line> lines;
extern vector<Circle> circles;
extern vector<POINT> Cross_points; // 交点
RECT Line::rect={0,0,60,30};
COLORREF Line::color=RGB(212,73,30);

void Draw_line(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,Line::color);
    SelectObject(hdc,hPen);

    auto A=arr[0], B=arr[1];
    MoveToEx(hdc,A.x,A.y,nullptr);
    LineTo(hdc,B.x,B.y);
    arr.clear();
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);

    string str;
    Line l1=Line(A,B);
    str+=to_string(A)+"  "+to_string(B)+'\n';
    auto Add_point=[&](pair<POINT,POINT> t)
    {
        auto [P,Q]=t;
        if(l1.left<=P.x && P.x<=l1.right)
            str+="Cross Points: "+to_string(P)+'\n',
            Cross_points.push_back(P);
        if(l1.left<=P.x && P.x<=l1.right)
            str+="Cross Points: "+to_string(Q)+'\n',
            Cross_points.push_back(Q);
    };
    for(auto l2:lines)
        Add_point(make_pair(Line_cross_line(l1,l2),POINT{-1,-1}));
    for(auto C:circles)
        Add_point(Circle_cross_line(C,l1));
    lines.push_back(l1);

    str+="lines :\n";
    for(auto l:lines)
        str+="a="+to_string(l.a)+", b="+to_string(l.b)+", c="+to_string(l.c)+'\n';
    debug(str);
}

Point lineprog(POINT P, Line A)
{
    return A.s + ( ((A.e-A.s)*(A.e-A.s)*(P-A.s))/(pow(len(A.e,A.s),2)) );
}