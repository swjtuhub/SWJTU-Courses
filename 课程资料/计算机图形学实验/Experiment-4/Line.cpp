#include "Line.h"
COLORREF Line::color=RGB(212,73,30);

Line::Line(POINT A, POINT B)
{
    s=A, e=B;
    auto [x1,y1]=A;
    auto [x2,y2]=B;
    rect={min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2)};
    a=y1-y2, b=x2-x1, c=x1*y2 - x2*y1;
}

Line::Line(Point A, Point B)
{
    *this=Line(A.to_POINT(),B.to_POINT());
}

void Line::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,color);
    SelectObject(hdc,hPen);
    MoveToEx(hdc,s.x,s.y,nullptr);
    LineTo(hdc,e.x,e.y);
    DeleteObject(hPen);
}

void Line::move(Point P)
{
    string str="P="+to_string(P.to_POINT())+'\n';
    // debug(str);
    Point ss=Point(s)+Point(P);
    Point ee=Point(e)+Point(P);
    *this=Line(ss,ee);
}

void Line::scale(Matrix3f &T)
{
    Transform_point_by_matrix(s,T);
    Transform_point_by_matrix(e,T);
    *this=Line(s,e);
}


void Line::rotate(Matrix3f &T)
{
    Transform_point_by_matrix(s,T);
    Transform_point_by_matrix(e,T);
    *this=Line(s,e);
}

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

    string str;
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
            str+="1";
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
            str+="      2";
        }
        str+="\n\n";
    }
    debug(str);
}


// 中点画线法绘制直线
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1); // 计算x方向上的增量
    int dy = abs(y2 - y1); // 计算y方向上的增量
    int sx = x1 < x2 ? 1 : -1; // x方向上的步长
    int sy = y1 < y2 ? 1 : -1; // y方向上的步长
    int err = dx - dy, e2; // 误差值

    std::cout << "(" << x1 << ", " << y1 << "), ";

    while ((x1 != x2) || (y1 != y2)) {
        if (x1 == x2 || y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 >= -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
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

void Draw_thick_line(HDC hdc, Line L, POINT A, POINT B)
{
    if(state == State_macros::Mid_point_line)
        if(fabs(L.slope())>1)
            for(int i=-2;i<=2;i++)
                MidPoint_Line(hdc,POINT{A.x+i,A.y},POINT{B.x+i,B.y},Line::color);
        else
            for(int i=-2;i<=2;i++)
                MidPoint_Line(hdc,POINT{A.x,A.y+i},POINT{B.x,B.y+i},Line::color);
    else
        if(fabs(L.slope())>1)
            for(int i=-2;i<=2;i++)
                Bresenham_Line(hdc,POINT{A.x+i,A.y},POINT{B.x+i,B.y},Line::color);
        else
            for(int i=-2;i<=2;i++)
                Bresenham_Line(hdc,POINT{A.x,A.y+i},POINT{B.x,B.y+i},Line::color);
}


void  Draw_line(HWND hWnd, vector<POINT> &arr, int state)
{
    HDC hdc=GetDC(hWnd);
    auto A=arr[0], B=arr[1];
    Line L(A,B);

    if(state == State_macros::Mid_point_line)
        MidPoint_Line(hdc,A,B,Line::color);
    if(state == State_macros::Bresenham_line)
        Bresenham_Line(hdc,A,B,Line::color);
    
    if(Thickline == true)
        Draw_thick_line(hdc,L,A,B);
    ReleaseDC(hWnd,hdc);
    arr.clear();

    string str;
    Line l1=Line(A,B);
    str+=to_string(A)+"  "+to_string(B)+'\n';
    auto Add_point=[&](pair<POINT,POINT> t)     // 把交点加入Cross_points中
    {
        auto [P,Q]=t;
        if(l1.rect.left<=P.x && P.x<=l1.rect.right)
            str+="Cross Points: "+to_string(P)+'\n',
            Cross_points.push_back(P);
        if(l1.rect.left<=P.x && P.x<=l1.rect.right)
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
    // debug(str);
}

