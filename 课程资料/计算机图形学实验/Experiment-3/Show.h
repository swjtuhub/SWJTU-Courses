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
#include "State_macros.h"
#include "Select_point.h"
#include "Variables.h"
using namespace std;

void Show_text(HWND hWnd, int x, int y, string str);

void Draw_Title(HWND hWnd, HDC hdc);

void Draw_button(HWND hWnd);

void Draw_menu(HWND hWnd);


////////////////////////// 添加每个封闭图形是否填充的标记
// 显示所有图案
void Show_graphics(HWND hWnd, HDC hdc);