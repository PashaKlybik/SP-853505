#include "stdafx.h"
#include "lab10part2.h"

#define MY_SHIT 1

const int WND_WIDTH = 700;
const int WND_HEIGHT = 500;
constexpr auto ID_RED = 1;;
constexpr auto ID_GREEN = 2;;
constexpr auto ID_BLUE = 3;;
constexpr auto ID_SQUARE = 4;;
constexpr auto ID_CIRCLE = 5;;
constexpr auto ID_DIAMOND = 6;;
constexpr auto ID_STAR = 7;;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawFigure(int shape, int color, int X, int Y);

void ClearWorkspace(HWND hwnd);


WNDCLASSEX wc;
HWND hwnd;
MSG Msg;
HDC hdc;
COPYDATASTRUCT* pCD;

struct figure_ {
	int color;
	int shape;
	bool draw;
};

figure_* figurePointer;
figure_ figure;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	figure.color = 1;
	figure.shape = 4;
	figure.draw = false;


	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"myClass2";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"myClass2",
		L"Lab 10 part 2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_WIDTH, WND_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE: {

	}break;
	case WM_LBUTTONDOWN: {
		
		int x = (int)LOWORD(lParam);
		int y = (int)HIWORD(lParam);
		
		if(figure.draw)
			DrawFigure(figure.shape, figure.color, x, y);

	}break;
	case WM_COPYDATA:
		pCD = (COPYDATASTRUCT*)lParam;
		figurePointer = (figure_*)pCD->lpData;
		figure.color = figurePointer->color;
		figure.shape = figurePointer->shape;
		figure.draw = figurePointer->draw;
		break;
	case WM_CLOSE: {
		DestroyWindow(hwnd);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void DrawFigure(int shape, int color, int X, int Y) {

	hdc = GetDC(hwnd);

	HBRUSH  brush = NULL;
	switch (color) {
	case ID_RED: {
		brush = CreateSolidBrush(RGB(242, 44, 75));
	}break;
	case ID_GREEN: {
		brush = CreateSolidBrush(RGB(75, 242, 44));
	}break;
	case ID_BLUE: {
		brush = CreateSolidBrush(RGB(44, 75, 242));
	}break;
	}
	SelectObject(hdc, brush);
	
	switch (shape) {
	case ID_SQUARE: Rectangle(hdc, X - 70, Y - 70, X + 70, Y + 70); break;
	case ID_CIRCLE: Ellipse(hdc, X - 70, Y - 70, X + 70, Y + 70); break;
	case ID_DIAMOND: { 
		POINT poly[4] = { {X,Y - 70},{X + 50, Y},{X,Y + 70}, {X-50, Y} };
		Polygon(hdc, poly, 4); 	
	}break;
	case ID_STAR: {
		POINT poly[10] = { {X-18,Y-15},{X, Y-70},{X+18,Y - 15},
			 {X + 70,Y},{X + 25,Y + 15},{X + 50,Y + 70},
			 {X,Y + 37},{X - 50, Y + 70},{X - 25,Y + 15},
								{X - 70, Y} };
		Polygon(hdc, poly, 10);
	}break;
	}
	DeleteObject(brush);
	DeleteDC(hdc);
}

void ClearWorkspace(HWND hwnd)
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hwnd, &rect, true);
}