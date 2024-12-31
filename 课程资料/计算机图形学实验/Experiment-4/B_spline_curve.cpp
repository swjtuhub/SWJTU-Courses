#include "B_spline_curve.h"
COLORREF B_spline_curve::color=RGB(182,215,255);

bool B_spline_curve::contain_point(const POINT P) const
{
	for(int i=0; i<points.size()-1; i++)
		if(Line(points[i],points[i+1]).contain_point(P))
			return true;
	return false;
}

void B_spline_curve::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,color);
    SelectObject(hdc,hPen);
    MoveToEx(hdc,points[0].x,points[0].y,nullptr);
	for(int i=1;i<points.size();i++)
		LineTo(hdc,points[i].x,points[i].y);
    DeleteObject(hPen);
}

void B_spline_curve::move(Point P)
{
    for(auto &Q:points)
        Q=(Point(Q)+P).to_POINT();
	rect={rect.left+P.x, rect.top+P.y, rect.right+P.x, rect.bottom+P.y};
}

void B_spline_curve::scale(Matrix3f &T)
{
	for(auto &P:points)
		Transform_point_by_matrix(P,T);
    *this=B_spline_curve(points);
}

void B_spline_curve::rotate(Matrix3f &T)
{
    for(auto &P:points)
		Transform_point_by_matrix(P,T);
    *this=B_spline_curve(points);
}

// 绘制三次B样条拟合曲线
void Draw_B_spline_curve(HWND hWnd, const vector<POINT> &control_points)
{
    B_spline_curve bsc(control_points);
    B_spline_curves.push_back(bsc);
	// vector<POINT> curvePoints = bsc.points;
    HDC hdc = GetDC(hWnd);
	bsc.Draw(hdc,B_spline_curve::color);
    ReleaseDC(hWnd,hdc);
}

/*
以下代码参考自 https://www.cnblogs.com/kongbursi-2292702937/p/15330359.html
****************************       BSpline       *********************************** 
 包含功能：二次B样条平滑，三次B样条平滑；二次B样条平滑后节点插值

 作者：    蒋锦朋   1034378054@qq.com
 单位：    中国地质大学（武汉） 地球物理与空间信息学院
 日期：    2014/12/03
*************************************************************************************
*/

// 三次样条基函数
double F03(double t)
{
	return 1.0/6*(-t*t*t+3*t*t-3*t+1);
}
double F13(double t)
{
	return 1.0/6*(3*t*t*t-6*t*t+4);
}
double F23(double t)
{
	return 1.0/6*(-3*t*t*t+3*t*t+3*t+1);
}
double F33(double t)
{
	return 1.0/6*t*t*t;
}


// 三次B样条拟合曲线
vector<Point> B_spline_curve::ComputeBSplineCurve(const vector<POINT> &control_points)
{
    if(control_points.size()==0)
        return vector<Point>();

    int num=control_points.size();
	int insert_num_sum=0;                               //  计算需要插入的点总数
    vector<int> insert_num(num-1);
    for(int i=0;i<num-1;i++)
    {
        insert_num[i]=(dis_point_to_point(control_points[i],control_points[i+1])/10.0);
        insert_num_sum+=insert_num[i];
    }

    vector<Point> temp(num+2);
	for(int i=0;i<num;i++)
		temp[i+1]=control_points[i];

	temp[0].x=2*temp[1].x-temp[2].x;                  //  将折线延长线上两点加入作为首点和尾点
	temp[0].y=2*temp[1].y-temp[2].y;

	temp[num+1].x=2*temp[num].x-temp[num-1].x;
	temp[num+1].y=2*temp[num].y-temp[num-1].y;

	double t;
	Point NodePt1,NodePt2,NodePt3,NodePt4;
    vector<Point> res(num+insert_num_sum);

	int totalnum=0;
	for(int i=0;i<num-1;i++)                          //  每条线段均匀插入点
	{
		NodePt1=temp[i]; NodePt2=temp[i+1]; NodePt3=temp[i+2]; NodePt4=temp[i+3];
		double dt=1.0/(insert_num[i]+1);

		for(int j=0;j<insert_num[i]+1;j++)
		{
			t=dt*j;
			res[totalnum].x=F03(t)*NodePt1.x+F13(t)*NodePt2.x+F23(t)*NodePt3.x+F33(t)*NodePt4.x;
			res[totalnum].y=F03(t)*NodePt1.y+F13(t)*NodePt2.y+F23(t)*NodePt3.y+F33(t)*NodePt4.y;
			totalnum++;
		}

		if(i==num-2){              //  最后一个尾点
			t=1;
			res[totalnum].x=F03(t)*NodePt1.x+F13(t)*NodePt2.x+F23(t)*NodePt3.x+F33(t)*NodePt4.x;
			res[totalnum].y=F03(t)*NodePt1.y+F13(t)*NodePt2.y+F23(t)*NodePt3.y+F33(t)*NodePt4.y;
			totalnum++;
		}
	}
    return res;
}
