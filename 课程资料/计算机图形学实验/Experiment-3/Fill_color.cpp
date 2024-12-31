#include "Fill_color.h"


void Fill_color(HWND hWnd, POINT P)
{
    int f=0, pos=-1;
    for(int i=rects.size()-1;i>=0;i--)
        if(is_point_in_rect(P,rects[i]))
        {
            pos=i;
            f=State_macros::Rect;
            break;
        }
    for(int i=circles.size()-1;i>=0;i--)
        if(is_point_in_circle(P,circles[i]))
        {
            pos=i;
            f=State_macros::Circle;
            break;
        }
    for(int i=polygons.size()-1;i>=0;i--)
        if(is_point_in_polygon(P,polygons[i]))
        {
            pos=i;
            f=State_macros::Polygon;
            break;
        }
    HDC hdc=GetDC(hWnd);
    
    if(f==State_macros::Rect && state==State_macros::Scanline_fill)
        Scanline_fill_rect(hdc, rects[pos]);
    if(f==State_macros::Circle && state==State_macros::Scanline_fill)
        Scanline_fill_circle(hdc,circles[pos]);
    if(f==State_macros::Polygon && state==State_macros::Scanline_fill)
        Scanline_fill_polygon(hdc, polygons[pos]);
    
    if(state==State_macros::Flood_fill)
        if(f==State_macros::Rect)
            Flood_fill(hdc,P,rects[pos]);
        else if(f==State_macros::Circle)
            Flood_fill(hdc,P,circles[pos]);
        else if(f==State_macros::Polygon)
            Flood_fill(hdc,P,polygons[pos]);
}

// 扫描线算法填充矩形
void Scanline_fill_rect(HDC hdc, Rect R)
{
    for(int x=R.left;x<=R.right;x++)
        Bresenham_Line(hdc,POINT{x,R.bottom},POINT{x,R.top},Rect::color);
}

// 扫描线算法填充圆
void Scanline_fill_circle(HDC hdc, Circle C)
{
    int mn=C.O.y-C.r, mx=C.O.y+C.r;
    int i,j;
    for(int y=mn;y<=mx;y++)
    {
        auto [A,B]=Circle_cross_line(C,Line(POINT{0,y},POINT{N,y}));
        Bresenham_Line(hdc,A,B,Circle::color);
    }
}

// 扫描线算法填充多边形
void Scanline_fill_polygon(HDC hdc, polygon P)
{
    int mn=1e9, mx=0;
    int i,j, n=P.size();
    for(i=0;i<n;i++)
        mn=min(mn,int(P[i].y)), mx=max(mx,int(P[i].y));
    for(int y=mn;y<=mx;y++)
    {
        set<POINT> S;
        for(i=0;i<n;i++)
            if(seg_cross_seg(Line(POINT{0,y},POINT{N,y}), Line(P[i],P[(i+1)%n])))
                S.insert(Line_cross_line(Line(POINT{0,y},POINT{N,y}), Line(P[i],P[(i+1)%n])));
        if(S.size()<2)
            continue;
        auto it1=S.begin();
        auto it2=S.begin();
        while(it2!=S.end())
        {
            it1=it2;
            it2++;
            if(dis_point_to_point(*it1,*it2)<=2)
                S.erase(it1);
        }
        vector<POINT> s(S.begin(),S.end());
        for(i=0;i<s.size()-1;i+=2)
            Bresenham_Line(hdc,s[i],s[i+1],polygon::color);
    }
}

// Flood fill(种子填充)算法 填充 矩形 / 圆 / (简单)多边形
template<typename T>
void Flood_fill(HDC hdc, POINT P, T t)
{
    std::stack<POINT> s;
    s.push(P);
    while(!s.empty())
    {
        auto [x,y]=s.top();     s.pop();
        auto check=[&](int x, int y)
        {
            if(GetPixel(hdc,x,y)!=T::color && t.contain_point(POINT{x,y}))
            {
                SetPixel(hdc,x,y,T::color);
                s.push(POINT{x,y});
            }
        };
        SetPixel(hdc,x,y,T::color);
        check(x+1,y);
        check(x-1,y);
        check(x,y+1);
        check(x,y-1);
    }
}
