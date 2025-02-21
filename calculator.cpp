#include <windows.h>
#include <cstdlib>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND textf, box1, box2, buttonAdd, buttonSub, buttonMul, buttonDiv;
char text1[20], text2[20];

void PerformCalculation(HWND hwnd, char operation) {
    GetWindowText(box1, text1, 20);
    GetWindowText(box2, text2, 20);

    double num1 = atof(text1);
    double num2 = atof(text2);
    double result = 0;
    char buffer[100];

    if (operation == '/' && num2 == 0) {
        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK);
        return;
    }

    if (operation == '+') result = num1 + num2;
    if (operation == '-') result = num1 - num2;
    if (operation == '*') result = num1 * num2;
    if (operation == '/') result = num1 / num2;

    sprintf(buffer, "%f", result);
    MessageBox(hwnd, buffer, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_CREATE) {
        textf = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20, 20, 200, 20, hwnd, NULL, NULL, NULL);

        box1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 55, 100, 20, hwnd, NULL, NULL, NULL);
        box2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 85, 100, 20, hwnd, NULL, NULL, NULL);

        buttonAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 120, 20, 20, hwnd, (HMENU)1, NULL, NULL);
        buttonSub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 60, 120, 20, 20, hwnd, (HMENU)2, NULL, NULL);
        buttonMul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 120, 20, 20, hwnd, (HMENU)3, NULL, NULL);
        buttonDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 120, 20, 20, hwnd, (HMENU)4, NULL, NULL);
    }

    if (message == WM_COMMAND) {
        if ((HWND)lParam == buttonAdd) PerformCalculation(hwnd, '+');
        if ((HWND)lParam == buttonSub) PerformCalculation(hwnd, '-');
        if ((HWND)lParam == buttonMul) PerformCalculation(hwnd, '*');
        if ((HWND)lParam == buttonDiv) PerformCalculation(hwnd, '/');
    }

    if (message == WM_DESTROY) {
        PostQuitMessage(0);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 23);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindow("WindowClass", "My Calculator", WS_VISIBLE | WS_SYSMENU,
                             CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
