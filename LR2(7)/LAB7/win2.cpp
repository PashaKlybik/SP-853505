
#include "framework.h"
#include "win2.h"

#define MAX_LOADSTRING 100
#define EDIT_ID 1
#define BUTTON_ADD_ID 2
#define BUTTON_CLEAR_ID 3
#define BUTTON_TORIGHT_ID 4 
#define BUTTON_DELETE_ID 5
#define LISTBOX1_ID 6
#define LISTBOX2_ID 7



// Глобальные переменные
HINSTANCE hInst;                                // Экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Заголовок
WCHAR szWindowClass[MAX_LOADSTRING];            // Класс окна


HWND hEdit, hButtonAdd, hButtonClear, hButtonToRight, hButtonDelete, hListBox1, hListBox2;
HWND hWnd;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool ContainsString(HWND hListBox, TCHAR* s) {
    int count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
    for (int i = 0; i < count; i++) {
        TCHAR buffer[256];
        SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)buffer);

        if (!_tcscmp(s, buffer))//strcmp
            return true;
    }
    return false;
}

void AddStringInListBox(HWND hListBox, TCHAR* s) {
    if (!ContainsString(hListBox, s)) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)s);
    }
}

bool DeleteSelectedItem(HWND hListBox) {
    int selCount = SendMessage(hListBox, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    for (int i = selCount - 1; i >= 0; --i) {
        int itemId = countBuffer[i];
        SendMessage(hListBox, LB_DELETESTRING, itemId, 0);//удаление
    }

    return true;
}

void ToRight() {
    int selCount = SendMessage(hListBox1, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox1, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    if (selCount == 0) {
        MessageBox(hWnd, L"Item isn`t selected in ListBox1", L"Error", MB_OK);
    }
    else {
        for (int i = selCount - 1; i >= 0; --i) {
            int itemId = countBuffer[i];
            TCHAR buffer[256];
            SendMessage(hListBox1, LB_GETTEXT, itemId, (LPARAM)buffer);
            AddStringInListBox(hListBox2, buffer);
        }

        DeleteSelectedItem(hListBox1);
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB7));

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


// Регистрирация класса окна
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB7));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB7);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   Сохранение маркера экземпляра и создание главного окна
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; 

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 550, 330, NULL, NULL, hInstance, NULL);

    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"", WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        40, 40, 350, 35, hWnd, (HMENU)EDIT_ID, hInst, NULL);

    hButtonAdd = CreateWindow(L"BUTTON", L"Add", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        410, 40, 90, 35, hWnd, (HMENU)BUTTON_ADD_ID, hInst, NULL);

    hButtonClear = CreateWindow(L"BUTTON", L"Clear", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        410, 105, 90, 35, hWnd, (HMENU)BUTTON_CLEAR_ID, hInst, NULL);

    hButtonToRight = CreateWindow(L"BUTTON", L"To right", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        410, 163, 90, 35, hWnd, (HMENU)BUTTON_TORIGHT_ID, hInst, NULL);

    hButtonDelete = CreateWindow(L"BUTTON", L"Delete", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        410, 221, 90, 35, hWnd, (HMENU)BUTTON_DELETE_ID, hInst, NULL);

    hListBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | LBS_MULTIPLESEL,
        40, 105, 150, 151, hWnd, (HMENU)LISTBOX1_ID, hInst, NULL);

    hListBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | LBS_MULTIPLESEL,
        240, 105, 150, 151, hWnd, (HMENU)LISTBOX2_ID, hInst, NULL);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


// Обработка сообщений в главном окне.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{  

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);

            switch (wmEvent)
            {
            case BN_CLICKED:
                switch (wmId)
                {
                case BUTTON_ADD_ID:
                    int len;
                    len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                    if (len == 0)
                        MessageBox(hWnd, L"Textfield is empty!", L"Error", MB_OK);
                    else {
                        TCHAR* buffer = new TCHAR[len];
                        SendMessage(hEdit, WM_GETTEXT, len + 1, (LPARAM)buffer);

                        AddStringInListBox(hListBox1, buffer);
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
                    DeleteSelectedItem(hListBox2);
                    break;
                default:
                    break;
                }
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
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
