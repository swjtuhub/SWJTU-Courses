#include "debug.h"

// #define DEBUG
#ifdef DEBUG
void debug(string str)
{
    AllocConsole();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(hConsole, LPSTR(str.c_str()), str.length(), NULL, NULL);
    system("pause");
    FreeConsole();
}
#endif

string to_string(POINT P)
{
    string str='('+to_string(P.x)+','+to_string(P.y)+')';
    return str;
}