#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "State_macros.h"
#include "Variables.h"
#include "Show.h"
#include "debug.h"
using std::vector;
using std::string;
using std::pair;

POINT Near_by_cross_points(POINT P);

POINT Select_circle_center(POINT P);

void Show_point(HWND hWnd, POINT bt);

void Show_cross_points(HWND hWnd, POINT P);

void Show_circle_center(HWND hWnd, POINT P);

template<typename T>
int Point_in_graphic(POINT P, vector<T> &arr);

pair<int,int> Select_graphic(POINT P);