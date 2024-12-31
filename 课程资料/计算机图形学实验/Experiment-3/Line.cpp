#include "Line.h"
RECT Line::rect={0,0,60,30};
COLORREF Line::color=RGB(212,73,30);


// Bresenham 算法绘制直线
void Bresenham_Line(HDC hdc, POINT A, POINT B, COLORREF color)
{
    auto [x1, y1] = A;
    auto [x2, y2] = B;
    int dx = abs(x1 - x2), dy = abs(y1 - y2);
    int sx = (x1 < x2 ? 1 : -1);
    int sy = (y1 < y2 ? 1 : -1);
    int err = dx - dy;
    int x = x1, y = y1;

    while (1)
    {
        SetPixel(hdc,x,y,color);
        if (x == x2 && y == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

// 中点画线法绘制直线
void MidPoint_Line(HDC hdc, POINT A, POINT B, COLORREF color)
{
    auto [x1,y1]=A;
    auto [x2,y2]=B;
	int x = x1, y = y1;
	int a = -1*abs(y2 - y1), b = abs(x2 - x1);
    int sx=(x2>x1 ? 1 : -1);
    int sy=(y2>y1 ? 1 : -1);

	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while(x != x2)
		{
			if (d < 0)
				y += sy, d += d2;
			else
				d += d1;
			x += sx;
            SetPixel(hdc,x,y,color);
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a;
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while(y != y2)
		{
			if(d < 0)
				d += d1;
			else
				x += sx, d += d2;
			y += sy;
            SetPixel(hdc,x,y,color);
		}
	}
}


void Draw_line(HWND hWnd, vector<POINT> &arr, int state)
{
    HDC hdc=GetDC(hWnd);
    auto A=arr[0], B=arr[1];
    Line L(A,B);

    if(state == State_macros::Mid_point_line)
        MidPoint_Line(hdc,A,B,Line::color);
    if(state == State_macros::Bresenham_line)
        Bresenham_Line(hdc,A,B,Line::color);
    if(Thickline == true)
        if(state == State_macros::Mid_point_line)
            if(fabs(L.slolpe())>1)
                for(int i=-2;i<=2;i++)
                    MidPoint_Line(hdc,POINT{A.x+i,A.y},POINT{B.x+i,B.y},Line::color);
            else
                for(int i=-2;i<=2;i++)
                    MidPoint_Line(hdc,POINT{A.x,A.y+i},POINT{B.x,B.y+i},Line::color);
        else
            if(fabs(L.slolpe())>1)
                for(int i=-2;i<=2;i++)
                    Bresenham_Line(hdc,POINT{A.x+i,A.y},POINT{B.x+i,B.y},Line::color);
            else
                for(int i=-2;i<=2;i++)
                    Bresenham_Line(hdc,POINT{A.x,A.y+i},POINT{B.x,B.y+i},Line::color);
    arr.clear();

    string str;
    Line l1=Line(A,B);
    str+=to_string(A)+"  "+to_string(B)+'\n';
    auto Add_point=[&](pair<POINT,POINT> t)     // 把交点加入Cross_points中
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

