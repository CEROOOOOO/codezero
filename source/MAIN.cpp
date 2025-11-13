#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE previnst, PWSTR pcmdline, INT ncmdshow) {
    const wchar_t class_name[] = L"sample";

    WNDCLASS wc = { 0 };
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = instance;
    wc.lpszClassName = class_name;
    wc.lpfnWndProc = WindowProc;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        class_name,
        L"hi",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1000, 1000,
        NULL, NULL,
        instance,
        NULL
    );

    if (hwnd == NULL) {
        return -1;
    }

    ShowWindow(hwnd, ncmdshow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wp == 'A') {
            MessageBox(hwnd, L"You pressed A", L"ok", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    return 0;
}
