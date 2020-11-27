#include <windows.h>
#include <unordered_map>


static int sec = 0;
int x, y, buttonStopID = 322, buttonContinueID = 132;
std::unordered_map<int, HWND> buttons;

LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

struct Moving
{
	const int dXperS = 100;

	int dX, dY;
	int prevX = 0;
	bool is_stopped = true;
} moving;

struct TextStr
{
	int width;
	int height;
	HDC HdC;
} textStr;

inline void CheckCoordinates(HWND hWnd)
{
	RECT rect = { 0 };
	GetWindowRect(hWnd, &rect);

	int curX = x + rect.left;

	if (curX + textStr.width >= rect.right)
		moving.dX = (-1) * abs(moving.dX);

	if (curX <= rect.left)
		moving.dX = abs(moving.dX);
}

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR pCommandLine,
	int nCommandShow) {
	TCHAR className[] = "Мой класс";
	HWND hWindow;
	MSG message;
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.cbWndExtra = NULL;
	windowClass.cbClsExtra = NULL;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hInstance = hInst;

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Не получилось зарегистрировать класс!", "Ошибка", MB_OK);
		return NULL;
	}
	hWindow = CreateWindow(className,
		"SP6",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		NULL,
		CW_USEDEFAULT,
		NULL,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL
	);
	if (!hWindow) {
		MessageBox(NULL, "Не получилось создать окно!", "Ошибка", MB_OK);
		return NULL;
	}
	ShowWindow(hWindow, nCommandShow);

	buttons[buttonStopID] = CreateWindow("BUTTON", "Stop",
		WS_VISIBLE | WS_CHILD, 5, 40, 105, 20, hWindow, (HMENU)buttonStopID,
		hInst, NULL);

	buttons[buttonContinueID] = CreateWindow("BUTTON", "Start",
		WS_VISIBLE | WS_CHILD, 5, 75, 105, 20, hWindow, (HMENU)buttonContinueID,
		hInst, NULL);

	ShowWindow(buttons[buttonStopID], SW_HIDE);
	UpdateWindow(hWindow);
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

LRESULT CALLBACK WindowProcess(HWND hWindow, UINT uMessage,
    WPARAM wParameter, LPARAM lParameter)
{
    HDC hDeviceContext;
    PAINTSTRUCT paintStruct;
    RECT rectPlace;
    HFONT hFont;
	BITMAP bm;
	SIZE szsz;

    LPCSTR text = "Some text";
    static int size = 9;

    switch (uMessage)
    {
	case WM_CREATE: {
		SetTimer(hWindow, 1, 1000/30, NULL);
		GetClientRect(hWindow, &rectPlace);
		y = rectPlace.bottom / 2;
		moving.dX = moving.dXperS / 30;
		text = (PTCHAR)GlobalAlloc(GPTR, 50000 * sizeof(TCHAR));
		break;
	}
	case WM_COMMAND:
	{

		if (wParameter == buttonStopID) {
			moving.is_stopped = true;
			ShowWindow(buttons[buttonStopID], SW_HIDE);
			ShowWindow(buttons[buttonContinueID], SW_SHOW);
		}

		if (wParameter == buttonContinueID) {
			moving.is_stopped = false;
			ShowWindow(buttons[buttonContinueID], SW_HIDE);
			ShowWindow(buttons[buttonStopID], SW_SHOW);
		}

		break;
	}
    case WM_PAINT:
	{
		hDeviceContext = BeginPaint(hWindow, &paintStruct);
		textStr.HdC = CreateCompatibleDC(hDeviceContext);
		GetClientRect(hWindow, &rectPlace);
		TextOut(hDeviceContext, x, y, text, size);
		GetTextExtentPoint32(hDeviceContext, text, size, &szsz);
		textStr.width = szsz.cx * 2;
		textStr.height = szsz.cy;
		EndPaint(hWindow, &paintStruct);
		ReleaseDC(hWindow, hDeviceContext);
		break;
	}
	case WM_TIMER:
	{
		sec++;
		CheckCoordinates(hWindow);
		moving.prevX = x;
		if (!moving.is_stopped) {
			x += moving.dX;
		}
		InvalidateRect(hWindow, NULL, true);
		break;
	}
	case WM_SIZE:
	{
		GetClientRect(hWindow, &rectPlace);
		y = rectPlace.bottom / 2;
		break;
	}
    case WM_DESTROY:
	{
		KillTimer(hWindow, 1);
		PostQuitMessage(NULL);
		break;
	}
    default:
        return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
    }
    return NULL;
}