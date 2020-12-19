#include "Lab8.h"

#define ID_BTN_DRAW      1
#define ID_BTN_CLEAR     2

// Global Variables:
HINSTANCE hInst;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawChords(const HDC& hdc);
void DrawRoundRects(const HDC& hdc);
void DrawEllipses(const HDC& hdc);
void DrawRectangles(const HDC& hdc);
void DrawLines(HDC hdc);
void DeletePen(const HDC& hdc, const HPEN& hOldPen, const HPEN& hGreenPen);
void CreatePen(HPEN& hGreenPen, HPEN& hOldPen, const HDC& hdc);
void DrawButton(LPDRAWITEMSTRUCT);
void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


  //  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  //  LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName = L"Main";//szWindowClass;
    wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(L"MAIN", L"LAB6", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1200, 1000, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    static HWND
        hButtonDraw,
        hButtonClear;

    switch (message)
    {
    case WM_CREATE:
    {
        int x = 100;
        
        hButtonDraw = CreateWindow(
            L"BUTTON",
            L"Add",
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            x, 800, 60, 55,
            hWnd, (HMENU)ID_BTN_DRAW, hInst, nullptr
        );

        hButtonClear = CreateWindow(
            L"BUTTON",
            L"Clear",
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            x + 100, 800, 60, 55,
            hWnd, (HMENU)ID_BTN_CLEAR, hInst, nullptr
        );


    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
           
        case ID_BTN_DRAW:
        {
            HDC hdc = GetDC(hWnd);

            DrawLines(hdc);
            DrawRectangles(hdc);
            DrawEllipses(hdc);
            DrawRoundRects(hdc);
            DrawChords(hdc);

            ReleaseDC(hWnd, hdc);
        }
        break;
        case ID_BTN_CLEAR:
            InvalidateRect(hWnd, NULL, true);
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

        //GetClientRect(hWnd, &rect);


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DRAWITEM:
    {
        // �������������� ������
        DrawButton((LPDRAWITEMSTRUCT)lParam);
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

void DrawChords(const HDC& hdc)
{
    Chord(hdc, 50, 440, 250, 600, 50, 460, 250, 460);

    HPEN hGreenPen, hOldPen;
    CreatePen(hGreenPen, hOldPen, hdc);

    Chord(hdc, 300, 440, 500, 600, 300, 460, 500, 460);

    DeletePen(hdc, hOldPen, hGreenPen);
}

void DrawRoundRects(const HDC& hdc)
{
    RoundRect(hdc, 50, 320, 250, 450, 30, 35);

    HPEN hGreenPen, hOldPen;
    CreatePen(hGreenPen, hOldPen, hdc);

    RoundRect(hdc, 300, 320, 500, 450, 30, 35);

    DeletePen(hdc, hOldPen, hGreenPen);
}

void DrawEllipses(const HDC& hdc)
{
    Ellipse(hdc, 50, 210, 150, 310);

    HPEN hGreenPen, hOldPen;
    CreatePen(hGreenPen, hOldPen, hdc);

    Ellipse(hdc, 300, 210, 400, 310);

    DeletePen(hdc, hOldPen, hGreenPen);
}

void DrawRectangles(const HDC& hdc)
{
    Rectangle(hdc, 50, 70, 250, 200);

    HPEN hGreenPen, hOldPen; 
    CreatePen(hGreenPen, hOldPen, hdc);

    Rectangle(hdc, 300, 70, 500, 200);

    DeletePen(hdc, hOldPen, hGreenPen);

}

void DrawLines(HDC hdc)
{

    MoveToEx(hdc, 50, 50, NULL);
    LineTo(hdc, 250, 50);

    HPEN hGreenPen, hOldPen;
    CreatePen(hGreenPen, hOldPen, hdc);

    MoveToEx(hdc, 300, 50, NULL);
    LineTo(hdc, 500, 50);

    DeletePen(hdc, hOldPen, hGreenPen);
}

void DeletePen(const HDC& hdc, const HPEN& hOldPen, const HPEN& hGreenPen)
{
    SelectObject(hdc, hOldPen);
    DeleteObject(hGreenPen);
}

void CreatePen(HPEN& hPen, HPEN& hOldPen, const HDC& hdc)
{
    hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
    hOldPen = (HPEN)SelectObject(hdc, hPen);
}

void DrawButton(LPDRAWITEMSTRUCT lpInfo)
{
    HBITMAP hbm;
    int ResourceID;

    // ������������ ��������� WM_DRAWITEM
    // ������ ���� ��� ��������� �� ������ 
    if (lpInfo->CtlType != ODT_BUTTON)
        return;

    // ��� ��� � ���������� ����� ���� ���������
    // ������, ���������� ��������� WM_DRAWITEM,
    // ��������� ������������� ������
    switch (lpInfo->CtlID)
    {
    case ID_BTN_DRAW:
    {
        // ��������� ������������� �����������
        // ������ � ���������� (�������) ���������
        ResourceID = IDB_BITMAP1;
        break;
    }
    case ID_BTN_CLEAR:
    {
 
        ResourceID = IDB_BITMAP3;
        break;
    }
    default:
        return;
    }

    // ���� ������ �������, ������ �� � �������
    // ���������
    if (lpInfo->itemState & ODS_SELECTED)
    {
        switch (lpInfo->CtlID)
        {
        case ID_BTN_DRAW:
        {
            // ��������� ������������� �����������
            // ������ � ���������� (�������) ���������
            ResourceID = IDB_BITMAP2;
            break;
        }
        case ID_BTN_CLEAR:
        {

            ResourceID = IDB_BITMAP4;
            break;
        }
        default:
            return;
        }
    }


    // ��������� ����������� ������ �� �������� ����������
    hbm = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceID));

    // ��� ������ ������ �� ������
    if (!hbm) return;

    // ���� ������ ������� � �� ���� �������
    // ������������, �������� ������� DrawBitmap
    if ((lpInfo->itemAction & ODA_DRAWENTIRE) ||
        (lpInfo->itemAction & ODA_SELECT))
    {
        // ������ ������
        DrawBitmap(lpInfo->hDC,
            (lpInfo->rcItem).left,
            (lpInfo->rcItem).top, hbm);
    }

    // ������� ����������� ������, ��� ��� ���
    // ��� ������ �� �����
    DeleteObject(hbm);
}

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
    HBITMAP hbm, hOldbm;
    HDC hMemDC;
    BITMAP bm;
    POINT  ptSize, ptOrg;

    // ������� �������� ������, �����������
    // � ���������� �����������
    hMemDC = CreateCompatibleDC(hDC);

    // �������� ����������� bitmap � �������� ������
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // ���� �� ���� ������, ���������� ������
    if (hOldbm)
    {
        // ��� ��������� ������ ������������� ��� ��
        // ����� �����������, ��� ������������ �
        // ��������� �����������
        SetMapMode(hMemDC, GetMapMode(hDC));

        // ���������� ������� �����������
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;   // ������
        ptSize.y = bm.bmHeight;  // ������

        // ����������� ���������� ���������� � ����������
        // ��� ���������� ������
        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;

        // ����������� ���������� ���������� � ����������
        // ��� ��������� ������
        DPtoLP(hMemDC, &ptOrg, 1);

        // ������ ����������� bitmap
        BitBlt(hDC, x, y, ptSize.x, ptSize.y,
            hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

        // ��������������� �������� ������
        SelectObject(hMemDC, hOldbm);
    }

    // ������� �������� ������
    DeleteDC(hMemDC);
}

