#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Show.h"
#include "debug.h"
using namespace std;

struct Select_point
{
    static RECT rect;
    static COLORREF color;
};

POINT Near_by_cross_points(POINT P);

void Show_near_by_point(HWND hWnd, POINT bt);