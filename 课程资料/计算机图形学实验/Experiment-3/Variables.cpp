#include "Variables.h"

const int N = 4000;
const double eps = 1e-6;
int state, last_state;
bool Thickline = false;     // 是否绘制粗线条(修改线宽)

vector<POINT> arr;
vector<Line> lines;
vector<Circle> circles;
vector<Rect> rects;
vector<Curve> curves;
vector<Poly_line> polylines;
vector<polygon> polygons;
vector<POINT> Cross_points; // 交点