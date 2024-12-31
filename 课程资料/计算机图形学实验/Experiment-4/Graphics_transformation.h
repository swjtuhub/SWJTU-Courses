#pragma once
#include<windows.h>
#include<bits/stdc++.h>
#include "Eigen/Dense"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include "Select.h"
#include "Variables.h"
#include "State_macros.h"
#include "GeometryRelations.h"
#include "debug.h"
using std::vector;
using std::string;
using namespace Eigen;

void Transform_point_by_matrix(POINT &P, const Matrix3f &T);


// 获取选择矩形
RECT Get_selected_rectangle(POINT P);

// 平移 (鼠标左键按下后, 移动鼠标至目标位置, 松开鼠标左键)
void Move_graphic(HWND hWnd, POINT P, POINT Q);

// 缩放 (鼠标左键点第一下选中图形, 出现选择矩形, 拖动该矩形的一个顶点)
void Scale_graphic(HWND hWnd, POINT Q);

// 旋转 (鼠标左键点第一下选中图形, 出现选择矩形, 鼠标滚轮转动即可旋转)
void rotate_graphic(HWND hWnd, int zDelta);

// 中点分割裁剪算法
pair<POINT, POINT> Mid_point_clip(POINT A, POINT B, int left, int top, int right, int bottom);

// 裁剪直线 (左键点击选择两个点(构成选择矩形))
void Clip_line(HWND hWnd, POINT P, POINT Q);

// Sutherland-Hodgman算法具体实现
vector<POINT> Sutherland_Hodgman(const vector<POINT> &points, const vector<POINT> &boundary);

// Sutherland-Hodgman算法裁剪多边形(同上)(只能对凸多边形进行裁剪, 并且要按顺时针绘制)
void Sutherland_Hodgman_clip_polygon(HWND hWnd, POINT P, POINT Q);


// Weiler_Atherton算法裁剪多边形
void Weiler_Atherton_clip_polygon(HWND hWnd, POINT P, POINT Q);
