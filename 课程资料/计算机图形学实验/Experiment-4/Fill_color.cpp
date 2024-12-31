#include "Fill_color.h"

void Fill_color(HWND hWnd, POINT P)
{
    auto [f,pos]=Select_graphic(P);
    HDC hdc=GetDC(hWnd);
    
    string str="f,pos="+to_string(f)+", "+to_string(pos)+'\n';
    // debug(str);
    if(state==State_macros::Scanline_fill)
    {
        if(f==State_macros::Rect)
            Scanline_fill_rect(hdc, rects[pos]);
        if(f==State_macros::Circle)
            Scanline_fill_circle(hdc,circles[pos]), circles[pos].is_filled=true;
        if(f==State_macros::Polygon)
            Scanline_fill_polygon(hdc, polygons[pos]);
    }
    else // state==State_macros::Flood_fill
    {
        if(f==State_macros::Rect)
            Flood_fill(hWnd,hdc,P,rects[pos]);
        if(f==State_macros::Circle)
            Flood_fill(hWnd,hdc,P,circles[pos]);
        if(f==State_macros::Polygon)
            Flood_fill(hWnd,hdc,P,polygons[pos]);
    }
    ReleaseDC(hWnd,hdc);
}

// 扫描线算法填充矩形
void Scanline_fill_rect(HDC hdc, Rect &R)
{
    R.is_filled=true;
    for(int x=R.left;x<=R.right;x++)
        Bresenham_Line(hdc,POINT{x,R.bottom},POINT{x,R.top},Rect::color);
}

// 扫描线算法填充圆
void Scanline_fill_circle(HDC hdc, Circle &C)
{
    C.is_filled=true;
    int mn=C.O.y-C.r, mx=C.O.y+C.r;
    int i,j;
    for(int y=mn;y<=mx;y++)
    {
        auto [A,B]=Circle_cross_line(C,Line(POINT{0,y},POINT{N,y}));
        Bresenham_Line(hdc,A,B,Circle::color);
    }
}

// 扫描线算法填充多边形
void Scanline_fill_polygon(HDC hdc, polygon &P)
{
    P.is_filled=true;
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

// Scanning line seed filling algorithm(扫描线种子填充)算法 填充 矩形 / 圆 / (简单)多边形
template<typename T>
void Flood_fill(HWND hWnd, HDC hdc, POINT P, T &t)
{
    string str="flood fill\n";
    // debug(str);
    HDC memDC=CreateCompatibleDC(hdc);
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    HBITMAP hBitmap=CreateCompatibleBitmap(hdc,rcClient.right,rcClient.bottom);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(memDC, &rcClient, hBrush);
    DeleteObject(hBrush);
    t.Draw(memDC,T::color);
    t.is_filled = true;
    // debug(str);

    stack<POINT> s;
    s.push(P);
    while(!s.empty())
    {
        auto [x,y]=s.top();     s.pop();
        int l=x,r=x+1;
        while(GetPixel(memDC,l,y)!=T::color)
            l--;
        while(GetPixel(memDC,r,y)!=T::color)
            r++;
        l++, r=max(l,r-1);

        bool reach_up=false, reach_down=false;
        for(int i=l;i<=r;i++)
        {
            SetPixel(memDC,i,y,T::color);
            if(!reach_down && GetPixel(memDC,i,y-1)!=T::color)
            {
                reach_down=true, s.push(POINT{i,y-1});
                str+="s.push"+to_string(POINT{i,y-1})+'\n';
                // debug(str);
            }
            if(GetPixel(memDC,i,y-1)==T::color)
                reach_down=false;
            if(!reach_up && GetPixel(memDC,i,y+1)!=T::color)
            {
                reach_up=true, s.push(POINT{i,y+1});
                str+="s.push"+to_string(POINT{i,y+1})+'\n';
                // debug(str);
            }
            if(GetPixel(memDC,i,y+1)==T::color)
                reach_up=false;
        }
    }
    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, memDC, 0, 0, SRCCOPY);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    // debug(str);
}
