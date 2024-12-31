#include "Curve.h"
COLORREF Curve::color=RGB(23,205,255);

/*
二次项系数：
 a=[x1*(y3-y2)+x2*(y1-y3)+x3*(y2-y1)]/[(x1-x2)*(x1-x3)*(x2-x3)];

一次项系数：
 b=[x1*x1*(y2-y3)+x2*x2*(y3-y1)+x3*x3*(y1-y2)]/[(x1-x2)*(x1-x3)*(x2-x3)];

常数项：
 c=[x2*x3*y1*(x2-x3)+x1*x3*y2*(x3-x1)+x1*x2*y3*(x1-x2)]/[(x1-x2)*(x1-x3)*(x2-x3)];
*/

int Curve::fun(int x)
{
    auto [x1,y1]=A;
    auto [x2,y2]=B;
    auto [x3,y3]=C;
    double res=((x-x2)*(x-x3)/(x1-x2)/(x1-x3))*y1
                + ((x-x1)*(x-x3)/(x2-x1)/(x2-x3))*y2
                + ((x-x1)*(x-x2)/(x3-x1)/(x3-x2))*y3;
    return int(res+0.5);
}

Curve::Curve(POINT _A, POINT _B, POINT _C)
{
    A=_A, B=_B, C=_C;
    auto [x1,y1]=A;
    auto [x2,y2]=B;
    auto [x3,y3]=C;
    double a=double(x1*(y3-y2)+x2*(y1-y3)+x3*(y2-y1))/double((x1-x2)*(x1-x3)*(x2-x3));
    double b=double(x1*x1*(y2-y3)+x2*x2*(y3-y1)+x3*x3*(y1-y2))/double((x1-x2)*(x1-x3)*(x2-x3));
    double c=double(x2*x3*y1*(x2-x3)+x1*x3*y2*(x3-x1)+x1*x2*y3*(x1-x2))/double((x1-x2)*(x1-x3)*(x2-x3));

    int left, top, right, bottom;
    left=min({x1,x2,x3}), right=max({x1,x2,x3});
    top=min({y1,y2,y3}), bottom=max({y1,y2,y3});
    
    int m=-b/(2*a);     // 对称轴
    if(left<=m && m<=right)
        top=min(top,fun(m)), bottom=max(bottom,fun(m));
    rect={left,top,right,bottom};
}

bool Curve::contain_point(POINT P)
{
    auto [x1,y1]=A;
    auto [x2,y2]=B;
    auto [x3,y3]=C;
    if(P.x<min({x1,x2,x3})-3 || P.x>max({x1,x2,x3})+3)
        return false;
    int y=fun(P.x);
    if(abs(y-P.y)<=3)
        return true;
    return false;
}

void Curve::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,Curve::color);
    SelectObject(hdc,hPen);

    int l=rect.left;
    int r=rect.right;
    MoveToEx(hdc,l,fun(l),nullptr);
    for(int x=l;x<=r;x++)
    {
        int y=fun(x);
        LineTo(hdc,x,y);
    }
    DeleteObject(hPen);
}

void Curve::move(Point P)
{
    Point PA=Point(A)+P, PB=Point(B)+P, PC=Point(C)+P;
    *this=Curve(PA.to_POINT(),PB.to_POINT(),PC.to_POINT());
}

void Curve::scale(Matrix3f &T)
{
    Transform_point_by_matrix(A,T);
    Transform_point_by_matrix(B,T);
    Transform_point_by_matrix(C,T);
    *this=Curve(A,B,C);
}

void Curve::rotate(Matrix3f &T)
{
    Transform_point_by_matrix(A,T);
    Transform_point_by_matrix(B,T);
    Transform_point_by_matrix(C,T);
    *this=Curve(A,B,C);
}

void Draw_curve(HWND hWnd, vector<POINT> &arr)
{
    Curve cur(arr[0],arr[1],arr[2]);
    curves.push_back(cur);
    arr.clear();

    HDC hdc=GetDC(hWnd);
    cur.Draw(hdc,Curve::color);
    ReleaseDC(hWnd,hdc);
}