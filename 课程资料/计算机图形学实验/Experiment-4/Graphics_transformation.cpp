#include "Graphics_transformation.h"

void Transform_point_by_matrix(POINT &P, const Matrix3f &T)
{
    auto [x1,y1]=P;
    RowVector3f T0(x1,y1,1);
    RowVector3f res=T0 * T;
    P={res(0,0), res(0,1)};
}

RECT Get_selected_rectangle(POINT P)
{
    auto [f,pos]=Select_graphic(P);
    if(f<0)
        return {-1,-1,-1,-1};
    
    if(f==State_macros::Line)
        return lines[pos].rect;
    if(f==State_macros::Circle)
        return circles[pos].rect;
    if(f==State_macros::Rect)
        return rects[pos].rect;
    if(f==State_macros::Curve)
        return curves[pos].rect;
    if(f==State_macros::Polyline)
        return polylines[pos].rect;
    if(f==State_macros::Polygon)
        return polygons[pos].rect;
    if(f==State_macros::B_spline_curve)
        return B_spline_curves[pos].rect;
}

void Move_graphic(HWND hWnd, POINT P, POINT Q)
{
    string str="P="+to_string(P) + ", Q="+to_string(Q)+'\n';
    // debug(str);

    // calculate which graphic is selected
    auto [f,pos]=Select_graphic(P);
    Point m=Point(Q)-Point(P);

    if(f==State_macros::Line)
        lines[pos].move(m);
    if(f==State_macros::Circle)
        circles[pos].move(m);
    if(f==State_macros::Rect)
        rects[pos].move(m);
    if(f==State_macros::Curve)
        curves[pos].move(m);
    if(f==State_macros::Polyline)
        polylines[pos].move(m);
    if(f==State_macros::Polygon)
        polygons[pos].move(m);
    if(f==State_macros::B_spline_curve)
        B_spline_curves[pos].move(m);
    
    // refresh the window
    InvalidateRect(hWnd, NULL, true);
    UpdateWindow(hWnd);
}

void Scale_graphic(HWND hWnd, POINT P3)
{
    // P1是选择图形,  P2是选择矩形的一个顶点, P3是最终移动到的点
    POINT P1=arr[arr.size()-2], P2=arr[arr.size()-1];
    auto [f,pos]=Select_graphic(P1);
    RECT rect=Get_selected_rectangle(P1);
    if(dis_point_to_point(P2,P3)<=3 || f<0)
        return;

    POINT points[4]={{rect.left,rect.top}, {rect.right,rect.top}, {rect.right,rect.bottom}, {rect.left,rect.bottom}};
    int flag=0;
    double sx,sy,x0,y0;
    for(int i=0;i<4;i++)
    {
        if(dis_point_to_point(points[i],P2)<=3)
        {
            flag=1;
            sx=double(P3.x-points[(i+2)%4].x)/double(P2.x-points[(i+2)%4].x);
            sy=double(P3.y-points[(i+2)%4].y)/double(P2.y-points[(i+2)%4].y);
            x0=points[(i+2)%4].x, y0=points[(i+2)%4].y;
            break;
        }
    }
    if(!flag)
        return;
    Matrix3f T1,T2,S;
    T1 <<   1,  0,  0,
            0,  1,  0,
            -x0,-y0,1;

    S  <<   sx, 0,  0,
            0,  sy, 0,
            0,  0,  1;
            
    T2 <<   1,  0,  0,
            0,  1,  0,
            x0, y0, 1;
    
    Matrix3f T = T1 * S * T2;
    if(f==State_macros::Line)
        lines[pos].scale(T);
    if(f==State_macros::Circle)
        circles[pos].scale(T);
    if(f==State_macros::Rect)
        rects[pos].scale(T);
    if(f==State_macros::Curve)
        curves[pos].scale(T);
    if(f==State_macros::Polyline)
        polylines[pos].scale(T);
    if(f==State_macros::Polygon)
        polygons[pos].scale(T);
    if(f==State_macros::B_spline_curve)
        B_spline_curves[pos].scale(T);

    // refresh the window
    InvalidateRect(hWnd, NULL, true);
    UpdateWindow(hWnd);
}

void rotate_graphic(HWND hWnd, int angle)
{
    POINT P=arr[0], Q=arr[1];
    Matrix3f T1,T2,T3,T;
    T1 <<   1,  0,  0,
            0,  1,  0,
            -Q.x,-Q.y,1;
    
    T2 <<   cos(angle),     sin(angle), 0,
            -sin(angle),    cos(angle), 0,
            0,              0,          1;
    
    T3 <<   1,  0,  0,
            0,  1,  0,
            Q.x, Q.y, 1;
    
    T=T1 * T2 * T3; // 总转换矩阵

    // calculate which graphic is selected
    auto [f,pos]=Select_graphic(P);
    if(f==State_macros::Line)
        lines[pos].rotate(T);
    if(f==State_macros::Circle)
        circles[pos].rotate(T);
    if(f==State_macros::Rect)
        rects[pos].rotate(T);
    if(f==State_macros::Curve)
        curves[pos].rotate(T);
    if(f==State_macros::Polyline)
        polylines[pos].rotate(T);
    if(f==State_macros::Polygon)
        polygons[pos].rotate(T);
    if(f==State_macros::B_spline_curve)
        B_spline_curves[pos].rotate(T);

    // refresh the window
    InvalidateRect(hWnd, NULL, true);
    UpdateWindow(hWnd);
}

// 区域码
int encode(POINT P, int left, int top, int right, int bottom)
{
    auto [x,y]=P;
    int res=0;
    if(x<left)      res|=(1<<0);
    if(x>right)     res|=(1<<1);
    if(y<top)       res|=(1<<2);
    if(y>bottom)    res|=(1<<3);
    return res;
}

// 中点分割裁剪算法
pair<POINT, POINT> Mid_point_clip(POINT A, POINT B, int left, int top, int right, int bottom)
{
    auto fun=[&](POINT A, POINT B)->POINT
    {
        int code1=encode(A,left,top,right,bottom), code2=encode(B,left,top,right,bottom), code3;
        while(true)
        {
            if(!code1 && !code2)    // A,B都在窗口内
                return B;
            if(code1&code2)          // 线段AB全在窗口外(线段AB与窗口无交点)
                return {-1,-1};
            
            // 线段AB与窗口可能有交点(至少有一个点在窗口外)
            if(code2)       // 保证A在窗口外
                swap(A,B), swap(code1,code2);
            if(!code2)      // 如果B在窗口内, 那么B就是距离最远A的可见点
                return B;
            POINT mid={A.x+B.x>>1, A.y+B.y>>1};
            code3=encode(mid,left,top,right,bottom);
            if(code2&code3)
                B=mid, code2=code3;
            else
                A=mid, code1=code3;
            
            if(dis_point_to_point(A,B)<=3)
                return mid;
        }
    };
    POINT P=fun(A,B), Q=fun(B,A);
    return make_pair(P,Q);
}

void Clip_line(HWND hWnd, POINT P, POINT Q)
{
    string str;
    int left=min(P.x,Q.x), top=min(P.y,Q.y);
    int right=max(P.x,Q.x), bottom=max(P.y,Q.y);

    vector<Line> _lines;
    for(auto L:lines)
    {
        auto [A,B]=Mid_point_clip(L.s,L.e,left,top,right,bottom);
        if(A.x!=-1) 
            _lines.emplace_back(A,B);
        str+="Clip "+to_string(L.s)+", "+to_string(L.e)+" -> "+to_string(A)+", "+to_string(B)+'\n';
    }
    lines=_lines;
    arr.clear();

    str+="lines.size="+to_string(lines.size())+'\n';
    for(auto L:lines)
        str+=to_string(L.s)+", "+to_string(L.e)+'\n';
    debug(str);

    // refresh the window
    InvalidateRect(hWnd, NULL, true);
    UpdateWindow(hWnd);
}

vector<POINT> Sutherland_Hodgman(const vector<POINT> &points, const vector<POINT> &boundary)
{
    int n=boundary.size(), m=points.size();
    vector<POINT> arr1=points, arr2;
    for(int i=0;i<n;i++)                        // 遍历每条边界
    {
        Line L1(boundary[i],boundary[(i+1)%n]);
        Point a=Point(L1.e)-Point(L1.s);        // 向量
        for(int j=0;j<m;j++)                    // 对多边形的每条边以当前边界进行裁剪
        {
            POINT P=points[j], Q=points[(j+1)%m];
            Point b=Point(P)-Point(L1.s), c=Point(Q)-Point(L1.s);   // 向量
            auto t=a^b;
            if((a^b)>0)                           // 当前点在边界外
            {
                if((a^c)<0)                       // 下一个点在边界内
                {
                    // 将交点加进去
                    POINT tp=Line_cross_line(L1,Line(P,Q));
                    arr2.push_back(tp);
                }
            }
            else                                // 当前点在边界内
            {
                // 加入当前点
                arr2.push_back(P);
                if((a^c)>0)                       // 下一个点在边界外
                {
                    // 将交点加进去
                    POINT tp=Line_cross_line(L1,Line(P,Q));
                    arr2.push_back(tp);
                }
            }
        }
        arr1=arr2;
        arr2.clear();
    }
    return arr2;
}


void Sutherland_Hodgman_clip_polygon(HWND hWnd, POINT P, POINT Q)
{
    Rect R(P,Q);
    vector<POINT> boundary={{R.left,R.top}, {R.left,R.bottom}, {R.right,R.bottom}, {R.right,R.top}};
    vector<polygon> _polygons;
    for(auto py:polygons)
    {
        auto points=Sutherland_Hodgman(py.points,boundary);
        _polygons.emplace_back(points);
    }
    arr.clear();
}

void Weiler_Atherton_clip_polygon(HWND hWnd, POINT P, POINT Q)
{

}