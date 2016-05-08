// BetaGoWin.cpp
// Main file for the BetaGo application

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>

//variables
HWND hwnd01;
HWND buttons[361];

int color_brown = 0x002d52a0;
int color_black = 0x00000000;
int color_white = 0x00ffffff;

HBITMAP hImg_white = (HBITMAP)LoadImage(NULL, L"bitmap_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_black = (HBITMAP)LoadImage(NULL, L"bitmap_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

int windowWidth = 590;
int windowHeight = 610;
int buttonSize = 30;

//functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("BetaGo");
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);


	RegisterClass(&wc);
	hwnd01 = CreateWindow(wc.lpszClassName, TEXT("BetaGo"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int x_buttonPlacement = 0;
	int y_buttonPlacement = 0;
	switch (msg)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < 361; i++) {
			if ((x_buttonPlacement + buttonSize) > windowWidth) {
				y_buttonPlacement += buttonSize;
				x_buttonPlacement = 0;
			}
			buttons[i] = CreateWindow(TEXT("button"), NULL,
						WS_VISIBLE | WS_CHILD | BS_BITMAP,
						x_buttonPlacement, y_buttonPlacement, 
						buttonSize, buttonSize,
						hwnd, (HMENU)1, NULL, NULL);
			x_buttonPlacement += buttonSize;
			
		}
		break;
	}

	case WM_COMMAND:
	{
		SendMessageW(buttons[LOWORD(wParam)], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_white);
		break;
	}
	case WM_SHOWWINDOW:
	{
		SendMessage(buttons[1], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_black);
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rc;
		HDC hdc01 = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		SetBkColor(hdc01, color_brown); 
		ExtTextOut(hdc01, 0, 0, ETO_OPAQUE, &rc, 0, 0, 0);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}