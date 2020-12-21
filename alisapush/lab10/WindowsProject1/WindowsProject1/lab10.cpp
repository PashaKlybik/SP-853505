#include "stdafx.h"
#include "lab10.h"

#define MY_SHIT 1

constexpr auto ID_REDRAD = 1;;
constexpr auto ID_GREENRAD = 2;;
constexpr auto ID_BLUERAD = 3;;
constexpr auto ID_SQUARERAD = 4;;
constexpr auto ID_CIRCLERAD = 5;;
constexpr auto ID_DIAMONDRAD = 6;;
constexpr auto ID_STARRAD = 7;;
constexpr auto IDB_CHECKBOX = 8;;
const int WND_WIDTH = 300;
const int WND_HEIGHT = 300;
static bool flag = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void SetShape(HWND shape);
void SetColor(HWND color);

void ChangeState(int color, int shape, bool draw);



WNDCLASSEX wc;
HWND hwnd, hwDIspatch, greenRad, redRad, blueRad, squareRad, starRad, circleRad, diamondRad, checkBox;
MSG Msg;

struct figure_ {
	int color;
	int shape;
	bool draw;
};

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
	wc.lpszClassName = L"myClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"myClass",
		L"Lab 10 part 1",
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
		greenRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"GREEN",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			20, 0, 72, 20,
			hwnd, (HMENU)ID_GREENRAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		redRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"RED",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			20, 40, 72, 20,
			hwnd, (HMENU)ID_REDRAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		blueRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"BLUE",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			20, 80, 72, 20,
			hwnd, (HMENU)ID_BLUERAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL); 
		squareRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"SQUARE",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			120, 0, 72, 20,
			hwnd, (HMENU)ID_SQUARERAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL); 
		starRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"STAR",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			120, 40, 72, 20,
			hwnd, (HMENU)ID_STARRAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		circleRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"CIRCLE",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			120, 80, 72, 20,
			hwnd, (HMENU)ID_CIRCLERAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		diamondRad = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"DIAMOND",
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			120, 120, 72, 20,
			hwnd, (HMENU)ID_DIAMONDRAD,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		checkBox = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"DRAW",
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			120, 150, 72, 20,
			hwnd, (HMENU)IDB_CHECKBOX,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		break;
	}
	case WM_COMMAND:{

		switch (LOWORD(wParam)){

			case IDB_CHECKBOX:{
				if (!flag)
					SendMessage(checkBox, BM_SETCHECK, BST_CHECKED, 0);
				else 
					SendMessage(checkBox, BM_SETCHECK, BST_UNCHECKED, 0);
				flag = !flag;
				ChangeState(figure.color, figure.shape, flag);
			}break;
			
			case ID_DIAMONDRAD: {
				SetShape(diamondRad);
				ChangeState(figure.color, ID_DIAMONDRAD, figure.draw);
			}break;
			case ID_SQUARERAD: {
				SetShape(squareRad);
				ChangeState(figure.color, ID_SQUARERAD, figure.draw);
			}break;
			case ID_CIRCLERAD: {
				SetShape(circleRad);
				ChangeState(figure.color, ID_CIRCLERAD, figure.draw);
			}break;
			case ID_STARRAD: {
				SetShape(starRad);
				ChangeState(figure.color, ID_STARRAD, figure.draw);
			}break;
			case ID_GREENRAD: {
				SetColor(greenRad);
				ChangeState(ID_GREENRAD, figure.shape, figure.draw);
			}break;
			case ID_REDRAD: {
				SetColor(redRad);
				ChangeState(ID_REDRAD, figure.shape, figure.draw);
			}break;
			case ID_BLUERAD: {
				SetColor(blueRad);
				ChangeState(ID_BLUERAD, figure.shape, figure.draw);
			}break;
		}
		return 0;
	}break;
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

void SetShape(HWND shape)
{
	SendMessage(diamondRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(squareRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(starRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(circleRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(shape, BM_SETCHECK, BST_CHECKED, 0);
}

void SetColor(HWND color)
{
	SendMessage(greenRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(redRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(blueRad, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(color, BM_SETCHECK, BST_CHECKED, 0);
}

void ChangeState(int color, int shape, bool draw)
{
	figure.color = color;
	figure.shape = shape;
	figure.draw = draw;

	COPYDATASTRUCT cd;
	cd.dwData = MY_SHIT;
	cd.lpData = &figure;
	cd.cbData = sizeof(figure);
	
	hwDIspatch = FindWindow(L"myClass2", L"Lab 10 part 2");
	if(hwDIspatch != NULL)
		SendMessage(hwDIspatch, WM_COPYDATA, (WPARAM)(HWND) hwnd, (LPARAM)(LPVOID)&cd);
	else MessageBox(hwnd, L"FUUCK", L"DIE BITCH!", MB_OK);
}