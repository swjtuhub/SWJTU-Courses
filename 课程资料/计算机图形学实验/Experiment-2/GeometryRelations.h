#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
using namespace std;

struct Line;
struct Point;
struct Circle;

// 点到直线的距离
double dis_point_to_line(POINT P, Line A);

//直线和圆的关系
int relation_line_and_circle(Circle A, Line B);

//两圆的关系
//5 相离; 4 外切; 3 相交; 2 内切; 1 内含
int relation_circle_and_circle(Circle a, Circle b);

//求直线和圆的交点
pair<POINT,POINT> Circle_cross_line(Circle A, Line B);

//求两个圆的交点
pair<POINT,POINT> Circle_cross_circle(Circle A, Circle B);

// 求直线和直线的交点
POINT Line_cross_line(Line l1, Line l2);