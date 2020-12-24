// Project2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void				InitControls(HWND);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND hWnd;

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
    LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT2);
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
      CW_USEDEFAULT, 0, 390, 380, nullptr, nullptr, hInstance, nullptr);

   InitControls(hWnd);

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
#define EDIT_ID 1
#define BUTTON_ADD_ID 2
#define BUTTON_CLEAR_ID 3
#define BUTTON_TORIGHT_ID 4
#define BUTTON_DELETE_ID 5
#define LISTBOX1_ID 6
#define LISTBOX2_ID 7

HWND hEdit, hButtonAdd, hButtonClear, hButtonToRight, hButtonDelete, hListBox1, hListBox2;

void InitControls(HWND hWnd) {
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Edit", WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        40, 40, 200, 20, hWnd, (HMENU)EDIT_ID, hInst, NULL);

    hButtonAdd = CreateWindow(L"BUTTON", L"Add", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        260, 35, 80, 30, hWnd, (HMENU)BUTTON_ADD_ID, hInst, NULL);

    hButtonClear = CreateWindow(L"BUTTON", L"Clear", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        40, 260, 80, 30, hWnd, (HMENU)BUTTON_CLEAR_ID, hInst, NULL);

    hButtonToRight = CreateWindow(L"BUTTON", L"ToRight", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        140, 260, 80, 30, hWnd, (HMENU)BUTTON_TORIGHT_ID, hInst, NULL);

    hButtonDelete = CreateWindow(L"BUTTON", L"Delete", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        240, 260, 80, 30, hWnd, (HMENU)BUTTON_DELETE_ID, hInst, NULL);

    hListBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | LBS_MULTIPLESEL,
        40, 80, 140, 160, hWnd, (HMENU)LISTBOX1_ID, hInst, NULL);

    hListBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | LBS_MULTIPLESEL,
        200, 80, 140, 160, hWnd, (HMENU)LISTBOX2_ID, hInst, NULL);

    SendDlgItemMessage(hWnd, EDIT_ID, (UINT)LB_SETHORIZONTALEXTENT, (WPARAM)1024, (LPARAM)0);
}

bool ContainsString(HWND hListBox, TCHAR* s) {
    int count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
    for (int i = 0; i < count; i++) {
        TCHAR buffer[256];
        //захватывает каждую ячейку(строку)  списка
        SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)buffer);
        //сравниеваем на повторение
        if (!_tcscmp(s, buffer))
            return true;
    }

    return false;
}

void AddToListBox(HWND hListBox, TCHAR* s) {
    if (!ContainsString(hListBox, s)) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)s);
       
    }
}

bool DeleteSelectedItem(HWND hListBox) {
    int selCount = SendMessage(hListBox1, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox1, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    for (int i = selCount - 1; i >= 0; --i) {
        int itemId = countBuffer[i];
        SendMessage(hListBox, LB_DELETESTRING, itemId, 0);
    }

    return true;
}

bool DeleteSelectedItem2(HWND hListBox) {
    int selCount = SendMessage(hListBox2, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox2, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    for (int i = selCount - 1; i >= 0; --i) {
        int itemId = countBuffer[i];
        SendMessage(hListBox, LB_DELETESTRING, itemId, 0);
    }

    return true;
}

void ToRight() {
    int selCount = SendMessage(hListBox1, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox1, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    if (selCount == 0) {
        MessageBox(hWnd, L"Select item in first ListBox", L"Error", MB_OK);
    }
    else {
        for (int i = selCount - 1; i >= 0; --i) {
            int itemId = countBuffer[i];
            TCHAR buffer[256];
            SendMessage(hListBox1, LB_GETTEXT, itemId, (LPARAM)buffer);
            AddToListBox(hListBox2, buffer);
        }

        DeleteSelectedItem(hListBox1);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmEvent)
        {
        case BN_CLICKED:
            switch (wmId)
            {
            case BUTTON_ADD_ID:
                int len;
                len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                if (len == 0)
                    MessageBox(hWnd, L"Fill the text field", L"Error", MB_OK);
                else {
                    TCHAR* buffer = new TCHAR[len];
                    SendMessage(hEdit, WM_GETTEXT, len + 1, (LPARAM)buffer);

                    AddToListBox(hListBox1, buffer);
                    SetWindowText(GetDlgItem(hWnd, EDIT_ID), L"");
                }
                break;
            case BUTTON_CLEAR_ID:
                SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);
                SendMessage(hListBox2, LB_RESETCONTENT, 0, 0);
                break;
            case BUTTON_TORIGHT_ID:
                ToRight();

                break;
            case BUTTON_DELETE_ID:
                DeleteSelectedItem(hListBox1);
                DeleteSelectedItem2(hListBox2);
                break;
            default:
                break;
            }
            break;
        default:
            switch (wmId)
            {
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
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
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