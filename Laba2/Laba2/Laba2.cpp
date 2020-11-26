// Laba2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Laba2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HWND hButtonAdd, hButtonClear, hButtonRight, hButtonDelete, hTextBox, hListBox_1, hListBox_2;


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
    LoadStringW(hInstance, IDC_LABA2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA2));
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
    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
        case WM_CREATE:
        {
            hTextBox = CreateWindow(L"EDIT", L"Text", WS_CHILD | WS_BORDER | WS_VISIBLE, 100, 50, 600, 50, hWnd, (HMENU)ID_TEXT_BOX, NULL, NULL);
            hListBox_1 = CreateWindow(L"LISTBOX", L"List_1", WS_CHILD | WS_BORDER | WS_VISIBLE, 100, 100, 300, 250, hWnd, (HMENU)ID_LIST_BOX_1, NULL, NULL);
            hListBox_2 = CreateWindow(L"LISTBOX", L"List_2", WS_CHILD | WS_BORDER | WS_VISIBLE, 400, 100, 300, 250, hWnd, (HMENU)ID_LIST_BOX_2, NULL, NULL);
            hButtonAdd = CreateWindow(L"Button", L"Add", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 350, 100, 50, hWnd, (HMENU)ID_ADD_BUTTON, NULL, NULL);
            hButtonRight = CreateWindow(L"Button", L"To Right", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 300, 350, 100, 50, hWnd, (HMENU)ID_TO_RIGHT_BUTTON, NULL, NULL);
            hButtonDelete = CreateWindow(L"Button", L"Delete", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 400, 350, 100, 50, hWnd, (HMENU)ID_DELETE_BUTTON, NULL, NULL);
            hButtonClear = CreateWindow(L"Button", L"Clear", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 600, 350, 100, 50, hWnd, (HMENU)ID_CLEAR_BUTTON, NULL, NULL);
        }break;

        case WM_COMMAND:
        {
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

                case ID_ADD_BUTTON:
                {
                    int len = GetWindowTextLength(GetDlgItem(hWnd, ID_TEXT_BOX));
                    if (len != NULL)
                    {
                        TCHAR* buf;
                        buf = (TCHAR*)GlobalAlloc(GPTR, sizeof(TCHAR) * (len + 1));
                        GetDlgItemText(hWnd, ID_TEXT_BOX, buf, len + 1);
                        if (SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_FINDSTRINGEXACT, NULL, (LPARAM)buf) == LB_ERR)
                            SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_ADDSTRING, NULL, LPARAM(buf));
                        SetDlgItemText(hWnd, ID_TEXT_BOX, L"");                        
                    }
                    else
                    {
                        MessageBox(hWnd, L"No Text!", L"Error", MB_OK);
                    }
                }break;

                case ID_TO_RIGHT_BUTTON:
                {
                    int item = SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_GETCURSEL, NULL, NULL);
                    if (item != LB_ERR)
                    {
                        int len = SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_GETTEXTLEN, item, NULL);
                        TCHAR* buf = (TCHAR*)GlobalAlloc(GPTR, sizeof(TCHAR) * (len + 1));
                        SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_GETTEXT, item, (LPARAM)buf);
                        if (SendDlgItemMessage(hWnd, ID_LIST_BOX_2, LB_FINDSTRINGEXACT, NULL, (LPARAM)buf) == LB_ERR)
                            SendDlgItemMessage(hWnd, ID_LIST_BOX_2, LB_ADDSTRING, NULL, (LPARAM)buf);                      
                    }
                    else
                    {
                        MessageBox(hWnd, L"No item selected in ListBox!", L"Error", MB_OK);                       
                    }
                }break;

                case ID_DELETE_BUTTON:
                {
                    int item_1 = SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_GETCURSEL, NULL, NULL);
                    int item_2 = SendDlgItemMessage(hWnd, ID_LIST_BOX_2, LB_GETCURSEL, NULL, NULL);
                    if (item_1 != LB_ERR)
                        SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_DELETESTRING, item_1, NULL);
                    if (item_2 != LB_ERR)
                        SendDlgItemMessage(hWnd, ID_LIST_BOX_2, LB_DELETESTRING, item_2, NULL);                  
                } break;

                case ID_CLEAR_BUTTON:
                {
                    SendDlgItemMessage(hWnd, ID_LIST_BOX_1, LB_RESETCONTENT, NULL, NULL);
                    SendDlgItemMessage(hWnd, ID_LIST_BOX_2, LB_RESETCONTENT, NULL, NULL);                   
                } break;

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
