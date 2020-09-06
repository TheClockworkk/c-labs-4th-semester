// Interaction with the control objects.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Controls.h"
#include <vector>
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
std::vector<ControlObject*> objects;
ControlObject* cur = nullptr;

int object_type = -1;
int mouse_mode = MOUSE_MODE_NONE;
int x, y;
int button_counter = 1, spinbutton_counter = 1, combobox_counter = 1, editbox_counter = 1, label_counter = 1, angle = 0;
POINT click, size, old, spin_size, win_size;
RECT winRect;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Info(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Error(HWND, UINT, WPARAM, LPARAM);
HWND hRadio;



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
    LoadStringW(hInstance, IDC_INTERACTIONWITHTHECONTROLOBJECTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTERACTIONWITHTHECONTROLOBJECTS));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INTERACTIONWITHTHECONTROLOBJECTS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_INTERACTIONWITHTHECONTROLOBJECTS);
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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        click.x = LOWORD(lParam);
        click.y = HIWORD(lParam);
        if (mouse_mode == MOUSE_MODE_CREATING)
        {
            ControlObject* ptr;
            switch (object_type)
            {
            case IDC_BUTTON:
            {
                if (CheckCreat(objects, click, size))
                {
                    ptr = new ControlButton();
                    *ptr = ControlButton(hWnd, click.x, click.y, size.x, size.y, button_counter++);
                    objects.push_back(ptr);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_BUTTON, IDC_SPINBUTTON, 0);
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROR), hWnd, Error);
                    object_type = -1;
                }
                break;
            }
            case IDC_SPINBUTTON:
                if (CheckCreat(objects, click, spin_size))
                {
                    ptr = new ControlSpinButton();
                    *ptr = ControlSpinButton(hWnd, click.x, click.y, size.x, size.y, spinbutton_counter++);
                    objects.push_back(ptr);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_BUTTON, IDC_SPINBUTTON, 0);
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROR), hWnd, Error);
                    object_type = -1;
                }
                break;
            case IDC_EDITBOX:
                if (CheckCreat(objects, click, size))
                {
                    ptr = new ControlEdit();
                    *ptr = ControlEdit(hWnd, click.x, click.y, size.x, size.y, editbox_counter++);
                    objects.push_back(ptr);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_BUTTON, IDC_SPINBUTTON, 0);
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROR), hWnd, Error);
                    object_type = -1;
                }
                break;
            case IDC_COMBOBOX:
                if (CheckCreat(objects, click, size))
                {
                    ptr = new ControlComboBox();
                    *ptr = ControlComboBox(hWnd, click.x, click.y, size.x, size.y, combobox_counter++);
                    objects.push_back(ptr);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_BUTTON, IDC_SPINBUTTON, 0);
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROR), hWnd, Error);
                    object_type = -1;
                }
                break;
            case IDC_LABEL:
                if (CheckCreat(objects, click, size))
                {
                    ptr = new ControlLabel();
                    *ptr = ControlLabel(hWnd, click.x, click.y, size.x, size.y, label_counter++);
                    objects.push_back(ptr);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_BUTTON, IDC_SPINBUTTON, 0);
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROR), hWnd, Error);
                    object_type = -1;
                }
                break;
            default: break;
            }
            mouse_mode = MOUSE_MODE_NONE;
        }
        else if (mouse_mode != MOUSE_MODE_MOVING || mouse_mode != MOUSE_MODE_DEFORM)
        {
            for (size_t i = 0; i < objects.size(); i++)
            {
                angle = objects[i]->CheckAngle(click);
                if (angle)
                {
                    cur = objects[i];
                    mouse_mode = MOUSE_MODE_DEFORM;
                    old = click;
                    break;
                }
                if (objects[i]->isInside(click))
                {
                    cur = objects[i];
                    mouse_mode = MOUSE_MODE_MOVING;
                    old = click;
                    break;
                }
            }
        }
        break;
    }
    case WM_LBUTTONUP:
        if (mouse_mode == MOUSE_MODE_MOVING)
        {
            mouse_mode = MOUSE_MODE_NONE;
            cur = nullptr;
        }
        else if (mouse_mode == MOUSE_MODE_DEFORM)
        {
            mouse_mode = MOUSE_MODE_NONE;
            cur = nullptr;
        }
        break;
    case WM_MOUSEMOVE:
    {
        if (mouse_mode == MOUSE_MODE_MOVING)
        {
            click.x = LOWORD(lParam);
            click.y = HIWORD(lParam);
            bool check = true;
            POINT left, right;
            left.x = cur->left.x + click.x - old.x;
            left.y = cur->left.y + click.y - old.y;
            right.x = cur->right.x + click.x - old.x;
            right.y = cur->right.y + click.y - old.y;
            for (size_t i = 0; i < objects.size(); i++)
            {
                if (cur != objects[i] && objects[i]->CheckCrossing(left, right))
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                cur->Move(click.x - old.x, click.y - old.y);
                old = click;
            }
            else {
                POINT test = old;
                ClientToScreen(hWnd, &test);
                SetCursorPos(test.x, test.y);
            }
        }
        else if (mouse_mode == MOUSE_MODE_DEFORM)
        {
            click.x = LOWORD(lParam);
            click.y = HIWORD(lParam);
            bool check = true;
            POINT left, right;
            left.x = cur->left.x + click.x - old.x;
            left.y = cur->left.y + click.y - old.y;
            right.x = cur->right.x + click.x - old.x;
            right.y = cur->right.y + click.y - old.y;
            for (size_t i = 0; i < objects.size(); i++)
            {
                if (cur != objects[i] && objects[i]->CheckCrossing(left, right))
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                cur->Deform(click.x - old.x, click.y - old.y, angle);
                old = click;
            }
            else {
                POINT test = old;
                ClientToScreen(hWnd, &test);
                SetCursorPos(test.x, test.y);
            }
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        if (mouse_mode == MOUSE_MODE_CREATING)
        {
            mouse_mode = MOUSE_MODE_NONE;
        }

        break;
    }
    case WM_CREATE:
    {
        ShowWindow(hWnd, SW_SHOWMAXIMIZED);
        size.x = 90;
        size.y = 40;
        spin_size.x = 20;
        spin_size.y = 20;
        CreateWindow(L"button", L"BUTTON",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            500, 10, 120, 20, hWnd, (HMENU)IDC_BUTTON, GetModuleHandle(NULL), NULL);
        CreateWindow(L"button", L"EDIT BOX",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            660, 10, 120, 20, hWnd, (HMENU)IDC_EDITBOX, GetModuleHandle(NULL), NULL);
        CreateWindow(L"button", L"LABEL",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            820, 10, 120, 20, hWnd, (HMENU)IDC_LABEL, GetModuleHandle(NULL), NULL);
        CreateWindow(L"button", L"COMBO BOX",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            980, 10, 120, 20, hWnd, (HMENU)IDC_COMBOBOX, GetModuleHandle(NULL), NULL);
        CreateWindow(L"button", L"SPIN BUTTON",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            1140, 10, 120, 20, hWnd, (HMENU)IDC_SPINBUTTON, GetModuleHandle(NULL), NULL);
        CreateWindow(L"button", L"CREATE!",
            WS_CHILD | WS_VISIBLE,
            1300, 10, 120, 20, hWnd, (HMENU)IDC_CREATE_BTN, GetModuleHandle(NULL), NULL);
        GetClientRect(hWnd, &winRect);
        win_size.x = winRect.right - winRect.left;
        win_size.y = winRect.bottom - winRect.top;
        break;
    }
    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:

        switch (wmId)
        {
        case IDC_BUTTON:
            object_type = IDC_BUTTON;
            break;
        case IDC_EDITBOX:
            object_type = IDC_EDITBOX;
            break;
        case IDC_LABEL:
            object_type = IDC_LABEL;
            break;
        case IDC_COMBOBOX:
            object_type = IDC_COMBOBOX;
            break;
        case IDC_SPINBUTTON:
            object_type = IDC_SPINBUTTON;
            break;
        case (IDC_CREATE_BTN):
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_INFO_BOX), hWnd, Info);
            break;
        }
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        for (size_t i = 0; i < objects.size(); i++)
            delete objects[i];
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
    {

        return (INT_PTR)TRUE;
    }
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


INT_PTR CALLBACK Info(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static std::wstring name;
    std::wstring str = L"YOU CHOOSE <";
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:

        switch (object_type)
        {
        case IDC_BUTTON:
            name = L"BUTTON";
            break;
        case IDC_LABEL:
            name = L"LABEL";
            break;
        case IDC_EDITBOX:
            name = L"EDIT BOX";
            break;
        case IDC_COMBOBOX:
            name = L"COMBO BOX";
            break;
        case IDC_SPINBUTTON:
            name = L"SPIN BUTTON";
            break;
        }
        str += name;
        str += L">\n'OK' FOR DRAW";
        SetDlgItemText(hDlg, ID_NAME, str.c_str());
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            mouse_mode = MOUSE_MODE_CREATING;
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK Error(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (INT_PTR)TRUE;
    }
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