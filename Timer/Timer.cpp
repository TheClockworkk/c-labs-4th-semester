// lab3_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Timer.h"
#include <string>
#define MAX_LOADSTRING 100


bool CheckTime(SYSTEMTIME left, SYSTEMTIME right)
{
    return left.wYear == right.wYear && left.wMonth == right.wMonth &&
        left.wDay == right.wDay && left.wHour == right.wHour &&
        left.wMinute == right.wMinute && left.wSecond == right.wSecond &&
        left.wMilliseconds == right.wMilliseconds;
}



// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр (дискриптор приложения)
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB31, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB31));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB31));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB31);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
        100, 100, 415, 100, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

SYSTEMTIME upd_time(SYSTEMTIME s, unsigned long long mseconds)
{
    FILETIME f;
    SystemTimeToFileTime(&s, &f);

    ULARGE_INTEGER u;
    u.LowPart = f.dwLowDateTime;
    u.HighPart = f.dwHighDateTime;

    u.QuadPart += mseconds * 10000ull;

    f.dwLowDateTime = u.LowPart;
    f.dwHighDateTime = u.HighPart;

    FileTimeToSystemTime(&f, &s);

    return s;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static SYSTEMTIME st, puf;
    static HWND hDay, hMonth, hYear, hHour, hMinute, hSecond, hMsecond, hTimer, hApply, hStop, hError;
    static int RefreshTimer;
    static wchar_t buf[20];
    static int ref = 0;
    switch (message)
    {
    case WM_TIMER:
    {
        if (wParam == RefreshTimer)
        {
            puf = st;
            st = upd_time(st, ref);
            if (CheckTime(puf, st))
            {
                SetWindowText(hDay, L"00");
                SetWindowText(hMonth, L"00");
                SetWindowText(hYear, L"0000");
                SetWindowText(hHour, L"00");
                SetWindowText(hMinute, L"00");
                SetWindowText(hSecond, L"00");
                SetWindowText(hMsecond, L"0000");
                KillTimer(hWnd, 1);
                break;
            }
            else
            {
                wsprintf(buf, L"%d", st.wDay);
                SetWindowText(hDay, buf);
                wsprintf(buf, L"%d", st.wMonth);
                SetWindowText(hMonth, buf);
                wsprintf(buf, L"%d", st.wYear);
                SetWindowText(hYear, buf);
                wsprintf(buf, L"%d", st.wHour);
                SetWindowText(hHour, buf);
                wsprintf(buf, L"%d", st.wMinute);
                SetWindowText(hMinute, buf);
                wsprintf(buf, L"%d", st.wSecond);
                SetWindowText(hSecond, buf);
                wsprintf(buf, L"%d", st.wMilliseconds);
                SetWindowText(hMsecond, buf);
            }
        }
        break;
    }
    case WM_CREATE:
    {
        hDay = CreateWindow(L"edit", L"00",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 5, 20, 20, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hDay, EM_SETLIMITTEXT, 2, 0);
        ShowWindow(hDay, SW_SHOWNORMAL);
        hMonth = CreateWindow(L"edit", L"00",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 30, 20, 20, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hMonth, EM_SETLIMITTEXT, 2, 0);
        ShowWindow(hMonth, SW_SHOWNORMAL);
        hYear = CreateWindow(L"edit", L"0000",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 55, 20, 40, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hYear, EM_SETLIMITTEXT, 5, 0);
        ShowWindow(hYear, SW_SHOWNORMAL);
        hHour = CreateWindow(L"edit", L"00",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 100, 20, 20, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hHour, EM_SETLIMITTEXT, 2, 0);
        ShowWindow(hHour, SW_SHOWNORMAL);
        hMinute = CreateWindow(L"edit", L"00",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 125, 20, 20, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hMinute, EM_SETLIMITTEXT, 2, 0);
        ShowWindow(hMinute, SW_SHOWNORMAL);
        hSecond = CreateWindow(L"edit", L"00",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 150, 20, 20, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hSecond, EM_SETLIMITTEXT, 2, 0);
        ShowWindow(hSecond, SW_SHOWNORMAL);
        hMsecond = CreateWindow(L"edit", L"0000",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 175, 20, 35, 20,
            hWnd, 0, hInst, NULL);
        SendMessage(hMsecond, EM_SETLIMITTEXT, 4, 0);
        ShowWindow(hMsecond, SW_SHOWNORMAL);
        hTimer = CreateWindow(L"edit", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, 215, 20, 100, 20,
            hWnd, 0, hInst, NULL);
        ShowWindow(hTimer, SW_SHOWNORMAL);
        hApply = CreateWindow(L"button", L"Старт",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            320, 0, 70, 20, hWnd, 0, hInst, NULL);
        ShowWindow(hApply, SW_SHOWNORMAL);
        hStop = CreateWindow(L"button", L"Стоп",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            320, 20, 70, 20, hWnd, 0, hInst, NULL);
        ShowWindow(hApply, SW_SHOWNORMAL);
    }

    case WM_COMMAND:
    {
        if (lParam == (LPARAM)hApply)    // если нажали на кнопку
        {
            int cur;
            GetWindowText(hTimer, buf, 12);
            ref = _wtoi(buf);
            RefreshTimer = SetTimer(hWnd, 1, ref, NULL);
            GetWindowText(hDay, buf, 3);
            cur = _wtoi(buf);
            st.wDay = cur;
            GetWindowText(hMonth, buf, 3);
            cur = _wtoi(buf);
            st.wMonth = cur;
            GetWindowText(hYear, buf, 5);
            cur = _wtoi(buf);
            st.wYear = cur;
            GetWindowText(hHour, buf, 3);
            cur = _wtoi(buf);
            st.wHour = cur;
            GetWindowText(hMinute, buf, 3);
            cur = _wtoi(buf);
            st.wMinute = cur;
            GetWindowText(hSecond, buf, 3);
            cur = _wtoi(buf);
            st.wSecond = cur;
            GetWindowText(hMsecond, buf, 5);
            cur = _wtoi(buf);
            st.wMilliseconds = cur;
        }

        if (lParam == (LPARAM)hStop)    // если нажали на кнопку
        {
            KillTimer(hWnd, 1);
        }

        int wmId = LOWORD(wParam);

        // Разобрать выбор в меню:
        switch (wmId)
        {

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_32774:
        {
            GetLocalTime(&st);
            wsprintf(buf, L"%d", st.wDay);
            SetWindowText(hDay, buf);
            wsprintf(buf, L"%d", st.wMonth);
            SetWindowText(hMonth, buf);
            wsprintf(buf, L"%d", st.wYear);
            SetWindowText(hYear, buf);
            wsprintf(buf, L"%d", st.wHour);
            SetWindowText(hHour, buf);
            wsprintf(buf, L"%d", st.wMinute);
            SetWindowText(hMinute, buf);
            wsprintf(buf, L"%d", st.wSecond);
            SetWindowText(hSecond, buf);
            wsprintf(buf, L"%d", st.wMilliseconds);
            SetWindowText(hMsecond, buf);
            break;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        TextOut(hdc, 26, 21, L".", 1);
        TextOut(hdc, 51, 21, L".", 1);
        TextOut(hdc, 121, 21, L":", 1);
        TextOut(hdc, 146, 21, L":", 1);
        TextOut(hdc, 171, 21, L":", 1);
        TextOut(hdc, 10, 5, L"dd", 2);
        TextOut(hdc, 34, 5, L"mm", 2);
        TextOut(hdc, 62, 5, L"yyyy", 4);
        TextOut(hdc, 104, 5, L"h", 1);
        TextOut(hdc, 128, 5, L"m", 1);
        TextOut(hdc, 153, 5, L"s", 1);
        TextOut(hdc, 180, 5, L"ms", 2);
        TextOut(hdc, 240, 5, L"Интервал", 8);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}