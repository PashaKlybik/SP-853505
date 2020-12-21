#include "stdafx.h"
#include "lab9.h"
#include <windows.h>
#include <tchar.h>

constexpr auto ID_TIMER = 3;;

const int WND_WIDTH = 700;
const int WND_HEIGHT = 500;
const int STEP = 10;
const int INTERV = 110;


const int LEFT = 11;
const int RIGHT = 12;
const int UP = 13;
const int DOWN = 14;
const int WAY = 0;

bool STEP_DONE = true;

static int IM_WIDTH = 54;
static int IM_HIGHT = 66;

typedef struct _step
{
	int step;
	_step* nextStep;
};

typedef struct _RuykCoords
{
	int x;
	int y;
	int last_step_im;
	_step* step;
	_step* last_step;
	
}RuykCoords;

RuykCoords ryukCoords, newCoords;
static int m = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void DrawBitmap(HWND hwnd, int x, int y, HBITMAP image);
void LoadBitmaps();
void MakeStep();
void GoLeft();
void GoRight();
void GoUp();
void GoDown();
void Stop(int ID_DIRECTION);



WNDCLASSEX wc;
HWND hwnd;
MSG Msg;
HDC hdc;
HBITMAP hStpLeft1, hStpLeft2, hStdLeft, hStpRight1,
hStpRight2, hStdRight, hStpFront1, hStpFront2,
hStdFront, hStpBack1, hStpBack2, hStdBack,
hStdLeftHUp, hBlankApple, hBlankRyuk, hApple;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
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
		L"Lab 8",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_WIDTH, WND_HEIGHT,
		NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	Stop(DOWN);
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
		LoadBitmaps();
		ryukCoords.x = 200;
		ryukCoords.y = 200; 
		ryukCoords.last_step_im = IDB_STDFRONT;
		ryukCoords.step = NULL;
		ryukCoords.last_step = NULL;
		break;
	}
	case WM_TIMER: {
		MakeStep();
		break;
	}
	case WM_LBUTTONDOWN: {

		if (STEP_DONE)
		{
			newCoords.x = (int)LOWORD(lParam);
			newCoords.y = (int)HIWORD(lParam);

			_step* nextStep1 = NULL;
			_step* nextStep2 =NULL;


			if (!(ryukCoords.x + (IM_WIDTH / 2) >= newCoords.x - 20 &&
				ryukCoords.x + (IM_WIDTH / 2) <= newCoords.x + 20))
			{
				if (newCoords.x > ryukCoords.x)
				{
					nextStep1 = new _step();
					nextStep1->step = RIGHT;
				}
				else {
					if (newCoords.x < ryukCoords.x)
					{
						nextStep1 = new _step();
						nextStep1->step = LEFT;
					}
				}
			}
			if (!(ryukCoords.y + (IM_HIGHT / 2) >= newCoords.y - 20 &&
				ryukCoords.y + (IM_HIGHT / 2) <= newCoords.y + 20))
			{
				if (newCoords.y > ryukCoords.y)
				{
					nextStep2 = new _step();
					nextStep2->step = DOWN;
				}
				else {
					if (newCoords.y < ryukCoords.y)
					{
						nextStep2 = new _step();
						nextStep2->step = UP;
					}
				}
			}


			if (nextStep1 != NULL && nextStep2 != NULL)
			{
				nextStep1->nextStep = nextStep2;
				nextStep2->nextStep = NULL;

				if (ryukCoords.step == NULL)
				{
					ryukCoords.step = nextStep1;
					ryukCoords.last_step = nextStep1;
				}
				else
					ryukCoords.last_step->nextStep = nextStep1;

				SetTimer(hwnd, ID_TIMER, INTERV, NULL);
			}
			else { 
				if (nextStep1 != NULL)
				{
					nextStep1->nextStep = NULL;

					if (ryukCoords.step == NULL)
					{
						ryukCoords.step = nextStep1;
						ryukCoords.last_step = nextStep1;
					}
					else
						ryukCoords.last_step->nextStep = nextStep1;

					SetTimer(hwnd, ID_TIMER, INTERV, NULL);
				}
				if (nextStep2 != NULL)
				{
					nextStep2->nextStep = NULL;

					if (ryukCoords.step == NULL)
					{
						ryukCoords.step = nextStep2;
						ryukCoords.last_step = nextStep2;
					}
					else
						ryukCoords.last_step->nextStep = nextStep2;

					SetTimer(hwnd, ID_TIMER, INTERV, NULL);
				}
			}

			if(nextStep1 != NULL || nextStep2 != NULL)
				STEP_DONE = false;
		}

		break;
	}
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

void DrawBitmap(HWND hwnd, int x, int y, HBITMAP image)
{
	HDC hCompDC;
	BITMAP bm;
	HBRUSH hCurBrush;

	hCompDC = CreateCompatibleDC(hdc);

	HBITMAP hOldbm = (HBITMAP) SelectObject(hCompDC, image);

	if (hOldbm) {
		GetObject(image, sizeof(bm), &bm);
		BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hCompDC, 0, 0, SRCCOPY);
		SelectObject(hCompDC, hOldbm);
	}
	DeleteDC(hCompDC);
}


void LoadBitmaps()
{
	hStpLeft1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPLEFT1));
	hStpLeft2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPLEFT2));
	hStdLeft = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STDLEFT));
	hStdLeftHUp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STDLEFT_HUP));
	hStpRight1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPRIGHT1));
	hStpRight2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPRIGHT2));
	hStdRight = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STDRIGHT));
	hStpFront1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPFRONT1));
	hStpFront2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPFRONT2));
	hStdFront = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STDFRONT));
	hStpBack1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPBACK1));
	hStpBack2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STPBACK2));
	hStdBack = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STDBACK));
	hBlankRyuk = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BLANKRYUK));
}


void MakeStep()
{
	switch (ryukCoords.step->step)
	{
	case RIGHT: {

		if (ryukCoords.x + (IM_WIDTH / 2) >= newCoords.x - 20 && 
			ryukCoords.x + (IM_WIDTH / 2) <= newCoords.x + 20)
		{
			ryukCoords.step = ryukCoords.step->nextStep;
			if(ryukCoords.step == NULL)
			{
				STEP_DONE = true;
				KillTimer(hwnd, ID_TIMER);
			}
			Stop(RIGHT);
		}
		else GoRight();
		break;
	}
	case LEFT: {

		if (ryukCoords.x + (IM_WIDTH / 2) >= newCoords.x - 20 && 
			ryukCoords.x + (IM_WIDTH / 2) <= newCoords.x + 20)
		{
			ryukCoords.step = ryukCoords.step->nextStep;
			if (ryukCoords.step == NULL)
			{
				STEP_DONE = true;
				KillTimer(hwnd, ID_TIMER);
			}
			Stop(LEFT);
		}
		else GoLeft();
		break;
	}
	case UP: {

		if (ryukCoords.y + (IM_HIGHT / 2) >= newCoords.y - 20 &&
			ryukCoords.y + (IM_HIGHT / 2) <= newCoords.y + 20)
		{
			ryukCoords.step = ryukCoords.step->nextStep;
			if (ryukCoords.step == NULL)
			{
				STEP_DONE = true;
				KillTimer(hwnd, ID_TIMER);
			}
			Stop(UP);
		}
		else GoUp();
		break;
	}
	case DOWN: {
		if (ryukCoords.y + (IM_HIGHT / 2) >= newCoords.y - 20 &&
			ryukCoords.y + (IM_HIGHT / 2) <= newCoords.y + 20)
		{
			ryukCoords.step = ryukCoords.step->nextStep;
			if (ryukCoords.step == NULL)
			{
				STEP_DONE = true;
				KillTimer(hwnd, ID_TIMER);
			}
			Stop(DOWN);
		}
		else GoDown();
		break;
	}
	default:
		break;
	}
}

void GoLeft()
{
	hdc = GetDC(hwnd);
	DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
	ryukCoords.x = ryukCoords.x - STEP;
	if (ryukCoords.last_step_im != IDB_STPLEFT1) {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpLeft1);
		ryukCoords.last_step_im = IDB_STPLEFT1;
	}
	else { 
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpLeft2);
		ryukCoords.last_step_im = IDB_STPLEFT2;
	}

	DeleteDC(hdc);
}

void GoRight()
{
	hdc = GetDC(hwnd);
	DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
	ryukCoords.x = ryukCoords.x + STEP;
	if (ryukCoords.last_step_im != IDB_STPRIGHT1) {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpRight1);
		ryukCoords.last_step_im = IDB_STPRIGHT1;
	}
	else {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpRight2);
		ryukCoords.last_step_im = IDB_STPRIGHT2;
	}

	DeleteDC(hdc);
}

void GoUp()
{
	hdc = GetDC(hwnd);
	DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
	ryukCoords.y = ryukCoords.y - STEP;
	if (ryukCoords.last_step_im != IDB_STPBACK1) {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpBack1);
		ryukCoords.last_step_im = IDB_STPBACK1;
	}
	else {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpBack2);
		ryukCoords.last_step_im = IDB_STPBACK2;
	}

	DeleteDC(hdc);
}

void GoDown()
{
	hdc = GetDC(hwnd);
	DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
	ryukCoords.y = ryukCoords.y + STEP;
	if (ryukCoords.last_step_im != IDB_STPFRONT1) {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpFront1);
		ryukCoords.last_step_im = IDB_STPFRONT1;
	}
	else {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStpFront2);
		ryukCoords.last_step_im = IDB_STPFRONT2;
	}

	DeleteDC(hdc);
}

void Stop(int ID_DIRECTION)
{
	hdc = GetDC(hwnd);
	switch (ID_DIRECTION)
	{
	case DOWN: DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStdFront); break;
	case RIGHT: {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
		DrawBitmap(hwnd, ryukCoords.x + 5, ryukCoords.y, hStdRight); break;
	}
	case LEFT: {
		DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hBlankRyuk);
		DrawBitmap(hwnd, ryukCoords.x + 5, ryukCoords.y, hStdLeft); break;
	}
	case UP: DrawBitmap(hwnd, ryukCoords.x, ryukCoords.y, hStdBack); break;
	default:
		break;
	}
	DeleteDC(hdc);
}