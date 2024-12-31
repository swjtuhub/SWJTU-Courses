#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon.h"
#include "Variables.h"
#include "debug.h"
using namespace std;

struct Line;
struct Point;
struct Rect;
struct Circle;
struct polygon;

// 两点之间的距离
double dis_point_to_point(POINT P, POINT Q);

// 点到直线的距离
double dis_point_to_line(POINT P, Line A);

Point rotleft(Point P);             // 将向量逆时针旋转 90 度
Point rotright(Point P);            // 将向量顺时针旋转 90 度
Point trunc(Point P, double r);     // 化为长度为r的向量
Point lineprog(POINT P, Line A);    // 求点P在直线A上的投影

// 直线和圆的关系
int relation_line_and_circle(Circle A, Line B);

// 两圆的关系
//5 相离; 4 外切; 3 相交; 2 内切; 1 内含
int relation_circle_and_circle(Circle a, Circle b);

// 两线段相交判断
// 2 规范相交; 1 非规范相交; 0 不相交
int seg_cross_seg(Line A, Line B);

// 点是否在多边形内
int is_point_in_polygon(POINT P, polygon A);

// 点是否在圆内
int is_point_in_circle(POINT P, Circle C);

// 点是否在矩形内
int is_point_in_rect(POINT P, Rect R);

// 求直线和圆的交点
pair<POINT,POINT> Circle_cross_line(Circle A, Line B);

// 求两个圆的交点
pair<POINT,POINT> Circle_cross_circle(Circle A, Circle B);

// 求直线和直线的交点
POINT Line_cross_line(Line l1, Line l2);