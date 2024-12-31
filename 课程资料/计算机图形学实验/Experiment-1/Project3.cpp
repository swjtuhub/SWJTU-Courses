#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 创建窗口
    const wchar_t CLASS_NAME[] = L"GDIExample";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0,                              // 扩展样式
        CLASS_NAME,                     // 窗口类名
        L"GDI Example",                 // 窗口标题
        WS_OVERLAPPEDWINDOW,            // 窗口样式
        0,0,                            // 窗口位置
        1200,900,                       // 窗口大小
        NULL,                           // 父窗口句柄
        NULL,                           // 菜单句柄
        hInstance,                      // 应用程序实例句柄
        NULL                            // 附加参数
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 清除背景
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // 绘制圆形
        Ellipse(hdc, 310, 90, 490, 270);     // O1 big
        Ellipse(hdc, 340, 120, 460, 240);    // O1 small
        Ellipse(hdc, 510, 0, 690, 180);     // O2 big
        Ellipse(hdc, 540, 30, 660, 150);    // O2 small
        Ellipse(hdc, 710, 90, 890, 270);     // O3 big
        Ellipse(hdc, 740, 120, 860,240);    // O3 small

        Arc(hdc, 423, 180, 777, 534, 733, 240, 467, 240);
        Arc(hdc, 190, -310, 590, 90, 400, 90, 533, 30);
        Arc(hdc, 610, -310, 1010, 90, 667, 30, 800, 90);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

