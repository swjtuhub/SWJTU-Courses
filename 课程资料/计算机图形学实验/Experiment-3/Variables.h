#pragma once
#include <windows.h>
#include <vector>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"
#include "Curve.h"
#include "Polyline.h"
#include "Polygon.h"
using std::vector;

struct Line;
struct Point;
struct Circle;
struct Rect;
struct Curve;
struct Poly_line;
struct polygon;

extern const int N;
extern const double eps;
extern int state, last_state;
extern bool Thickline;  // 是否绘制粗线条(修改线宽)

extern vector<POINT> arr;
extern vector<Line> lines;
extern vector<Circle> circles;
extern vector<Rect> rects;
extern vector<Curve> curves;
extern vector<Poly_line> polylines;
extern vector<polygon> polygons;
extern vector<POINT> Cross_points; // 交点