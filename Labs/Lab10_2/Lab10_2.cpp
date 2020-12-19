// Lab6.cpp : Defines the entry point for the application.
//

//#include "framework.h"
#include "Lab10_2.h"

#define IDC_CHECKBOX 123
#define IDR_BLUE	 1231
#define IDR_GREEN    1232
#define IDR_RED		 1233
#define IDR_CIRCLE   1331
#define IDR_SQUARE	 1332

// Global Variables:
HINSTANCE hInst;
HFONT hFont;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


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

	HWND hWnd = CreateWindowW(L"MAIN", L"LAB10_2", WS_OVERLAPPEDWINDOW,
		1000, 0, 800, 800, nullptr, nullptr, hInstance, nullptr);

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

// data
enum Color {
	RED,
	BLUE,
	GREEN,
};

enum Figure {
	CIRCLE,
	SQUARE,
};

typedef struct tagMYREC
{
	Color _color;
	Figure _figure;
	bool _draw;
} MYREC;

COPYDATASTRUCT CDS;
MYREC data;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	static int xOffset, yOffset;
	static bool timerStarted;
	static UINT msg;
	static HWND hCheckBox,
		hRadioBtnRed,
		hRadioBtnGreen,
		hRadioBtnBlue,
		hRadioBtnCircle,
		hRadioBtnSquare;

	switch (message)
	{
	case WM_CREATE:
	{
		int x = 100;
		msg = RegisterWindowMessage(L"Message to another program");
		hCheckBox = CreateWindow(L"button", L"Draw",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			x, 400,
			70, 30,
			hWnd,
			(HMENU)IDC_CHECKBOX,
			hInst, NULL
		);

		hRadioBtnBlue = CreateWindow(L"button", L"Blue",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			x, 200,
			70, 30,
			hWnd,
			(HMENU)IDR_BLUE,
			hInst, NULL
		);

		hRadioBtnGreen = CreateWindow(L"button", L"Green",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			x + 90, 200,
			70, 30,
			hWnd,
			(HMENU)IDR_GREEN,
			hInst, NULL
		);

		hRadioBtnRed = CreateWindow(L"button", L"Red",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			x + 180, 200,
			70, 30,
			hWnd,
			(HMENU)IDR_RED,
			hInst, NULL
		);

		hRadioBtnCircle = CreateWindow(L"button", L"Circle",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			x, 300,
			70, 30,
			hWnd,
			(HMENU)IDR_CIRCLE,
			hInst, NULL
		);

		hRadioBtnSquare = CreateWindow(L"button", L"Square",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			x + 90, 300,
			70, 30,
			hWnd,
			(HMENU)IDR_SQUARE,
			hInst, NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDR_BLUE:
			data._color = Color::BLUE;
			break;
		case IDR_GREEN:
			data._color = Color::GREEN;
			break;
		case IDR_RED:
			data._color = Color::RED;
			break;
		case IDR_CIRCLE:
			data._figure = Figure::CIRCLE;
			break;
		case IDR_SQUARE:
			data._figure = Figure::SQUARE;
			break;
		case IDC_CHECKBOX:
		{
			WORD state = (WORD)SendMessage(hCheckBox, BM_GETCHECK, 0, 0L);
			data._draw = state;
		}
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

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(hFont);
		break;
	default:
		if (message == msg)
		{
			CDS.cbData = sizeof(data);
			CDS.lpData = &data;

			SendMessage(HWND_BROADCAST, WM_COPYDATA, NULL, (LPARAM)(LPVOID)&CDS);

			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
