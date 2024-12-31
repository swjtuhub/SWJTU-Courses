// To be continued...

#pragma once
#include<windows.h>
#include<bits/stdc++.h>
#include "Show.h"
using namespace std;

struct Select_circle
{
    static RECT rect;
    static COLORREF color;
};

Circle Near_by_Circle(POINT P);

void Show_near_by_circle(HWND hWnd, POINT bt);
