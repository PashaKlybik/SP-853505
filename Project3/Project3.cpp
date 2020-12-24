// Project3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project3.h"

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
    LoadStringW(hInstance, IDC_PROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT3);
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

   InitControls(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

#define BUTTON_DRAW_ID 1
#define BUTTON_CLEAR_ID 2

void InitControls(HWND hWnd) {
    HWND buttonAdd = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
        20, 480, 60, 60, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);
    HWND buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
        90, 480, 60, 60, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);
}

bool pictureVisible = false;

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
    int wmId, wmEvent, i;
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
        case BUTTON_DRAW_ID:
            pictureVisible = true;
            InvalidateRect(hWnd, NULL, true);
            break;
        case BUTTON_CLEAR_ID:
            pictureVisible = false;
            InvalidateRect(hWnd, NULL, true);
            break;
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
    case WM_DRAWITEM:
    {
        DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
        HBRUSH brush;
        HPEN pen;

        switch (draw->CtlID)
        {
        case BUTTON_DRAW_ID:
        {
            HDC hdc = draw->hDC;

            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(0, 0, 255));
            }
            else {
                brush = CreateSolidBrush(RGB(0, 255, 0));
            }


            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Ellipse(hdc, 0, 0, 60, 60);
            MoveToEx(hdc, 10, 30, NULL);
            LineTo(hdc, 50, 30);
            MoveToEx(hdc, 30, 10, NULL);
            LineTo(hdc, 30, 50);
        }
        break;
        case BUTTON_CLEAR_ID:
        {
            HDC hdc = draw->hDC;

            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(0, 0, 255));
            }
            else {
                brush = CreateSolidBrush(RGB(255, 0, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Ellipse(hdc, 0, 0, 60, 60);
            MoveToEx(hdc, 20, 20, NULL);
            LineTo(hdc, 40, 40);
            MoveToEx(hdc, 40, 20, NULL);
            LineTo(hdc, 20, 40);
        }
        break;
        default:
            break;
        }

    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        HBRUSH brush;
        HPEN pen;
        if (pictureVisible)
        {
                      
            brush = CreateSolidBrush(RGB(50, 50, 50));
            SelectObject(hdc, brush);
            Rectangle(hdc, 60, 400, 250, 240);

            pen = CreatePen(BS_SOLID, 7, RGB(255, 0, 4));
            SelectObject(hdc, pen);
            MoveToEx(hdc, 60, 240, NULL);
            LineTo(hdc, 160, 140);
            MoveToEx(hdc, 160, 140, NULL);
            LineTo(hdc, 250, 240);
            MoveToEx(hdc, 250, 240, NULL);
            LineTo(hdc, 60, 240);
               
            pen = CreatePen(BS_SOLID, 2, RGB(143, 93, 19));
            SelectObject(hdc, pen);
            POINT points[6]; 
            points[0].x = 260;
            points[0].y = 400;

            points[1].x = 260;
            points[1].y = 240;

            points[2].x = 290;
            points[2].y = 220;

            points[3].x = 430;
            points[3].y = 220;

            points[4].x = 460;
            points[4].y = 240;

            points[5].x = 460;
            points[5].y = 400;

            Polygon(hdc, points, 6);


            pen = CreatePen(BS_SOLID, 7, RGB(255, 255, 255));
            SelectObject(hdc, pen);
            MoveToEx(hdc, 360, 220, NULL);
            LineTo(hdc, 360, 400);
            
            POINT points2[6];
            points2[0].x = 460;
            points2[0].y = 400;

            points2[1].x = 460;
            points2[1].y = 240;

            points2[2].x = 470;
            points2[2].y = 200;

            points2[3].x = 680;
            points2[3].y = 200;

            points2[4].x = 690;
            points2[4].y = 240;
                                          
            points2[5].x = 690;
            points2[5].y = 400;

            Polygon(hdc, points2, 6);

            

            pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, pen);
            brush = CreateSolidBrush(RGB(143, 93, 19));
            SelectObject(hdc, brush);
            Rectangle(hdc, 510, 395, 620, 250);


            
            pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, pen);
            brush = CreateSolidBrush(RGB(149, 184, 242));
            SelectObject(hdc, brush);
            Rectangle(hdc, 470, 210, 680, 70);

            pen = CreatePen(BS_SOLID, 4, RGB(103, 66, 214));
            SelectObject(hdc, pen);
            Arc(hdc, 50, 50, 200, 200, 200, 100, 0, 100);
            Arc(hdc, 50, 55, 200, 250, 200, 150, 0, 100);
            Arc(hdc, 50, 40, 200, 190, 200, 80, 0, 100);

            pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, pen);

            Arc(hdc,470,0,680,140,680,70,430,70);

            brush = CreateSolidBrush(RGB(232, 235, 61));
            SelectObject(hdc, brush);
            Ellipse(hdc, 60, 60, 140, 140);

            brush = CreateSolidBrush(RGB(176, 179, 46));
            SelectObject(hdc, brush);
            Ellipse(hdc, 70, 70, 100, 100);

            Ellipse(hdc, 290, 250, 330, 290);
            Ellipse(hdc, 385, 250, 425, 290);

            brush = CreateSolidBrush(RGB(214, 56, 127));
            SelectObject(hdc, brush);
            Ellipse(hdc, 80, 280, 140, 340);

            brush = CreateSolidBrush(RGB(161, 111, 13));
            SelectObject(hdc, brush);
            Rectangle(hdc, 180, 400, 230, 300);
         
            pen = CreatePen(BS_SOLID, 2, RGB(103, 66, 214));
            SelectObject(hdc, pen);
            brush = CreateSolidBrush(RGB(103, 66, 214));
            SelectObject(hdc, brush);
            Rectangle(hdc, 500, 160, 630, 100);
        }
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
