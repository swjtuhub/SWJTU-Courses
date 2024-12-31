#pragma once
#include <vector>
#include <future>
#include <stack>
#include "Point.h"
#include "Rect.h"
#include "Circle.h"
#include "polygon.h"
#include "debug.h"
using std::vector;

void Fill_color(HWND hWnd, POINT P);

void Scanline_fill_rect(HDC hdc, Rect R);

void Scanline_fill_circle(HDC hdc, Circle C);

void Scanline_fill_polygon(HDC hdc, polygon P);

template<typename T>
void Flood_fill(HDC hdc, POINT P, T t);