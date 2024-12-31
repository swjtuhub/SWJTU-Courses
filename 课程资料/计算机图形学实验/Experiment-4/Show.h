#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"
#include "Curve.h"
#include "Polyline.h"
#include "Polygon.h"
#include "B_spline_curve.h"
#include "State_macros.h"
#include "Select.h"
#include "Variables.h"
#include "Graphics_transformation.h"
using namespace std;

struct Rect;
// struct B_spl

void Show_text(HWND hWnd, int x, int y, string str);

// void Draw_Title(HWND hWnd, HDC hdc);

void Draw_button(HWND hWnd);

void Draw_menu(HWND hWnd);

// 绘制选择矩形(虚线矩形)
void Draw_dashed_rectangle(HWND hWnd, RECT R);

// 显示选中的点
void Show_selected_point(HWND hWnd, POINT P);

// 显示选中图形的矩形
bool Show_selected_rectangle(HWND hWnd, POINT P);

// 显示所有图案(窗口重绘)
void Show_graphics(HWND hWnd);