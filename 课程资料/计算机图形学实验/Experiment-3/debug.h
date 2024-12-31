#pragma once
#include <windows.h>
#include <string>
using namespace std;

// #define DEBUG
#ifdef DEBUG
void debug(string str);
#else
#define debug(str)
#endif

string to_string(POINT P);