// Lab6.cpp : Defines the entry point for the application.
//

//#include "framework.h"
#include "Lab10.h"

#define ID_BTN_TEST 1234

// Global Variables:
HINSTANCE hInst;
HFONT hFont;

//enums
enum Color {
	RED,
	BLUE,
	GREEN
};

enum Figure {
	CIRCLE,
	SQUARE
};

typedef struct tagMYREC
{
	Color _color;
	Figure _figure;
	bool _draw;
} MYREC;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void				Draw(MYREC* data, HDC hdc);



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
	wcex.hIcon = LoadIcon(hInstance, NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
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

	HWND hWnd = CreateWindowW(L"MAIN", L"LAB10", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 800, 800, nullptr, nullptr, hInstance, nullptr);

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




PCOPYDATASTRUCT pCDS;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	static int xOffset, yOffset;
	static bool timerStarted;
	static UINT msg;
	//static HWND hButtonTest;

	switch (message)
	{
	case WM_CREATE:
		/*hButtonTest = CreateWindow(
			L"BUTTON",
			L"Send Message",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			300, 600, 70, 50,
			hWnd, (HMENU)ID_BTN_TEST, hInst, nullptr
		);*/

		msg = RegisterWindowMessage(L"Message to another program");
		break;
	case WM_LBUTTONDOWN:
		SendMessage(HWND_BROADCAST, msg, 0, 0L);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		//case ID_BTN_TEST:
		//{
		//	
		//}
		//break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_COPYDATA:
	{
		// to clear main window immediately
		SendMessage(hWnd, WM_PAINT, 0, 0L);

		pCDS = (PCOPYDATASTRUCT)lParam;
		MYREC* data = (MYREC*)(pCDS->lpData);
		bool isChecked = data->_draw;

		if (isChecked)
		{
			HDC hdc = GetDC(hWnd);
			Draw(data, hdc);

			ReleaseDC(hWnd, hdc);
		}
		//MessageBox(hWnd, (LPCWSTR)isChecked, L"Data received", MB_OK);

	}
	break;
	case WM_PAINT:
	{
		/*PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);


		EndPaint(hWnd, &ps);*/
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(hFont);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Draw(MYREC* data, HDC hdc)
{
	HPEN hPen = NULL, hOldPen = NULL;
	COLORREF color = NULL;

	switch (data->_color)
	{
	case Color::GREEN:
		color = RGB(0, 255, 0);
		break;
	case Color::BLUE:
		color = RGB(0, 0, 255);
		break;
	case Color::RED:
		color = RGB(255, 0, 0);	
		break;
	}

	hPen = CreatePen(PS_SOLID, 10, color);
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	switch (data->_figure)
	{
	case Figure::CIRCLE:
		Ellipse(hdc, 50, 210, 150, 310);
		break;
	case Figure::SQUARE:
		Rectangle(hdc, 50, 210, 150, 310);
		break;
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}