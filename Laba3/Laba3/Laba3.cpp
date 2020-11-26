// Laba3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Laba3.h"

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

HWND hButtonCreate, hButtonDelete;
bool activ_picture = false;
HBRUSH brush;
HPEN pen;
//HDC hdc;

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
    LoadStringW(hInstance, IDC_LABA3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA3);
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
            hButtonCreate = CreateWindow(L"Button", L"" , WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 50, 50, 100, 60,
                hWnd, (HMENU)ID_BUTTON_CREATE, NULL, NULL);
            
            hButtonDelete = CreateWindow(L"Button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 160, 50, 100, 60, 
                hWnd, (HMENU)ID_BUTTON_DELETE, NULL, NULL);
        }break;

        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
            FillRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(150, 150, 150)));
            SetBkMode(pdis->hDC, TRANSPARENT);
        
            switch (pdis->CtlID)
            {
                case ID_BUTTON_CREATE:
                {
                    SetTextColor(pdis->hDC, RGB(0, 255, 0));
                    DrawText(pdis->hDC, L"CREATE", -1, &pdis->rcItem, DT_CENTER);
                    Ellipse(pdis->hDC, 30, 20, 70, 60);          
                    HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(50, 205, 50));
                    MoveToEx(pdis->hDC, 35, 40, NULL);
                    LineTo(pdis->hDC, 65, 40);
                    MoveToEx(pdis->hDC, 50, 25, NULL);
                    LineTo(pdis->hDC, 50, 55);
                }break;
                case ID_BUTTON_DELETE:
                {
                    SetTextColor(pdis->hDC, RGB(255, 0, 0));
                    DrawText(pdis->hDC, L"DELETE", -1, &pdis->rcItem, DT_CENTER);
                    Ellipse(pdis->hDC, 30, 20, 70, 60);
                    HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    MoveToEx(pdis->hDC, 35, 40, NULL);
                    LineTo(pdis->hDC, 65, 40);
                } break;
            }
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

            case ID_BUTTON_CREATE:
                activ_picture = true;
                InvalidateRect(hWnd, NULL, true);
                break;

            case ID_BUTTON_DELETE:
                activ_picture = false;
                InvalidateRect(hWnd, NULL, true);
                break;


            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }break;


        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            HBRUSH brush;
            HPEN pen;
            if (activ_picture)
            {  
                brush = CreateSolidBrush(RGB(50, 50, 50));
                SelectObject(hdc, brush);
                Ellipse(hdc, 260, 360, 300, 400);
                Ellipse(hdc, 500, 360, 540, 400);
                brush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, brush);
                Ellipse(hdc, 140, 300, 170, 330);
                Ellipse(hdc, 630, 300, 660, 330);
                brush = CreateSolidBrush(RGB(255, 218, 185)); 
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                POINT poly1[13], poly2[9], poly3[5];
                poly1[0].x = 150;
                poly1[0].y = 370;
                poly1[1].x = 255;
                poly1[1].y = 370;
                poly1[2].x = 255;
                poly1[2].y = 350;
                poly1[3].x = 310;
                poly1[3].y = 350;
                poly1[4].x = 310;
                poly1[4].y = 370;
                poly1[5].x = 495;
                poly1[5].y = 370;
                poly1[6].x = 495;
                poly1[6].y = 350;
                poly1[7].x = 550;
                poly1[7].y = 350;
                poly1[8].x = 550;
                poly1[8].y = 370;
                poly1[9].x = 650;
                poly1[9].y = 370;
                poly1[10].x = 650;
                poly1[10].y = 300;
                poly1[11].x = 150;
                poly1[11].y = 300;
                poly1[12].x = 150;
                poly1[12].y = 370;
                Polygon(hdc, poly1, 13);
                brush = CreateSolidBrush(RGB(50, 50, 50)); 
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                poly2[0].x = 200;
                poly2[0].y = 300;
                poly2[1].x = 250;
                poly2[1].y = 200;
                poly2[2].x = 400;
                poly2[2].y = 200;
                poly2[3].x = 600;
                poly2[3].y = 300;
                poly2[4].x = 570;
                poly2[4].y = 300;
                poly2[5].x = 400;
                poly2[5].y = 220;
                poly2[6].x = 260;
                poly2[6].y = 220;
                poly2[7].x = 220;
                poly2[7].y = 300;
                poly2[8].x = 200;
                poly2[8].y = 300;
                Polygon(hdc, poly2, 9);
                brush = CreateSolidBrush(RGB(230, 230, 250)); 
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                poly3[0].x = 220;
                poly3[0].y = 300;
                poly3[1].x = 260;
                poly3[1].y = 220;
                poly3[2].x = 400;
                poly3[2].y = 220;
                poly3[3].x = 570;
                poly3[3].y = 300;
                poly3[4].x = 220;
                poly3[4].y = 300;           
                Polygon(hdc, poly3, 5);
                brush = CreateSolidBrush(RGB(255, 255, 0));
                SelectObject(hdc, brush);
                Rectangle(hdc, 140, 350, 200, 370); 
                Rectangle(hdc, 600, 350, 660, 370);
                brush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 3, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                Rectangle(hdc, 740, 330, 900, 350);
                Rectangle(hdc,740, 390, 900, 410);
                brush = CreateSolidBrush(RGB(255, 250, 250));
                SelectObject(hdc, brush);
                Rectangle(hdc, 740, 360, 900, 380);
                pen = CreatePen(BS_SOLID, 4, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                MoveToEx(hdc, 0, 325, NULL);
                LineTo(hdc, 150, 325);
                MoveToEx(hdc, 650, 325, NULL);
                LineTo(hdc, 960, 325);
                pen = CreatePen(BS_SOLID, 3, RGB(0, 128, 0));
                SelectObject(hdc, pen);
                Arc(hdc, -900, 200, 660, 760, 165, 280, 0, 200);
                Arc(hdc, 400, 230, 1200, 490, 960, 230, 360, 200);
                pen = CreatePen(BS_SOLID, 4, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                MoveToEx(hdc, 700, 325, NULL);
                LineTo(hdc, 700, 125);
                Arc(hdc, 700, 110, 950, 290, 750, 130, 260, 150);
                brush = CreateSolidBrush(RGB(255, 255, 0));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 3, RGB(255, 255, 0));
                SelectObject(hdc, pen);
                Ellipse(hdc, 740, 130, 780, 150);
                Ellipse(hdc, 680, 110, 720, 130);               
            }
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
