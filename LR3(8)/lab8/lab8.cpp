#include "framework.h"
#include "lab8.h"
#define MAX_LOADSTRING 100
#define BUTTON_DRAW_ID 1
#define BUTTON_CLEAR_ID 2


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            
bool pictureVisible = false;
HWND buttonAdd, buttonClear;

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

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

	MSG msg;

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB8);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	buttonAdd = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		420, 350, 50, 50, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);
	buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		500, 350, 50, 50, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
				brush = CreateSolidBrush(RGB(0, 150, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(0, 255, 150));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 50, 50);
			MoveToEx(hdc, 10, 25, NULL);
			LineTo(hdc, 40, 25);
			MoveToEx(hdc, 25, 10, NULL);
			LineTo(hdc, 25, 40);
		}
		break;
		case BUTTON_CLEAR_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 150, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(255, 0, 150));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 50, 50);
			MoveToEx(hdc, 15, 15, NULL);
			LineTo(hdc, 35, 35);
			MoveToEx(hdc, 35, 15, NULL);
			LineTo(hdc, 15, 35);
		}
		break;
		default:
			break;
		}

	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH brush;
		HPEN pen;
		if (pictureVisible)
		{
			//parus i osnovanie
			brush = CreateSolidBrush(RGB(221, 0, 111));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, pen);

			POINT p[8] = { 270, 200, 580, 200, 525, 290, 340, 290 };
			Polygon(hdc, p, 4);

			POINT p2[3] = { 450, 50, 380, 120, 450, 160 };
			Polygon(hdc, p2, 3);

			//windows
			pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			brush = CreateSolidBrush(RGB(149, 184, 242));
			SelectObject(hdc, brush);

			Ellipse(hdc, 340, 220, 375, 255);
			Ellipse(hdc, 412, 220, 447, 255);
			Ellipse(hdc, 484, 220, 519, 255);

			pen = CreatePen(BS_SOLID, 5, RGB(0, 0, 0));
			SelectObject(hdc, pen);

			Arc(hdc, 550, 60, 590, 100, 570, 60, 550, 80);
			Arc(hdc, 510, 60, 550, 100, 550, 80, 530, 60);

			pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			brush = CreateSolidBrush(RGB(100, 100, 100));
			SelectObject(hdc, brush);
			Rectangle(hdc, 450, 30, 465, 200);

			pen = CreatePen(BS_SOLID, 1, RGB(255, 255, 0));
			SelectObject(hdc, pen);
			brush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, brush);
			Ellipse(hdc, 270, 30, 330, 90);
		}
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