// Project4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project4.h"

#define MAX_LOADSTRING 100
#define MOV_STEP 10

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HANDLE bmp[6];
int currBmp = 0;

int currX = 0, currY = 0, targX = 0, targY = 0;
bool reverse = true;

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
    LoadStringW(hInstance, IDC_PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT4);
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

   bmp[0] = LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
   bmp[1] = LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
   bmp[2] = LoadImage(NULL, L"3.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
   bmp[3] = LoadImage(NULL, L"4.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
   bmp[4] = LoadImage(NULL, L"5.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
   bmp[5] = LoadImage(NULL, L"6.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);


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
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
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
        break;
    case WM_LBUTTONDOWN:
    {
        targX = LOWORD(lParam) - 50;
        targY = HIWORD(lParam) - 50;
        SetTimer(hWnd, NULL, 100, NULL);
    }
    break;
    case WM_TIMER:
    {
        bool needRedraw = false;
        if (abs(currX - targX) >= MOV_STEP) {
            needRedraw = true;
            if (targX > currX) {
                currX += MOV_STEP;
                reverse = true;
            }
            else {
                currX -= MOV_STEP;
                reverse = false;
            }
        }
        if (abs(currY - targY) >= MOV_STEP) {
            needRedraw = true;
            if (targY > currY)
                currY += MOV_STEP;
            else
                currY -= MOV_STEP;
        }
        if (needRedraw) {
            currBmp = (currBmp + 1) % 6;
            InvalidateRect(hWnd, NULL, true);
            SetTimer(hWnd, NULL, 100, NULL);
        }
    }
    case WM_PAINT:
        {hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        HDC hCompatibleDC;
        hCompatibleDC = CreateCompatibleDC(hdc);
        SelectObject(hCompatibleDC, bmp[currBmp]);
        if (reverse)
            StretchBlt(hdc, currX, currY, 100, 100, hCompatibleDC, 100, 0, -100, 100, SRCCOPY);
        else
            StretchBlt(hdc, currX, currY, 100, 100, hCompatibleDC, 0, 0, 100, 100, SRCCOPY);
        DeleteDC(hCompatibleDC);

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
