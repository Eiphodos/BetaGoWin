// BetaGoWin.cpp
// Main file for the BetaGo application

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include "../Headers/go.h"
#include "../Headers/player.h"
#include "../Headers/intersection.h"
#include "../Headers/game.h"

// Handler for the main window and the buttons
HWND hwnd01;
HWND buttons[361];

// Background color for the main window
int color_brown = 0x002d52a0;

// Bitmaps for the buttons

HBITMAP hImg_white = (HBITMAP)LoadImage(NULL, L"bitmap_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_black = (HBITMAP)LoadImage(NULL, L"bitmap_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_tile = (HBITMAP)LoadImage(NULL, L"bitmap_tile.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_current = hImg_black;

// Width and height for the main window and size for the buttons.

int windowWidth = 590;
int windowHeight = 610;
int buttonSize = 30;

// Function declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// Creating a structure for our window class
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("BetaGo");
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	// Registering the class
	RegisterClass(&wc);
	// Creating the main window
	hwnd01 = CreateWindow(wc.lpszClassName, TEXT("BetaGo"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, 0, 0, hInstance, 0);
	// Message loop for handling messages from the OS
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Game* newgame = nullptr;
		newgame = new Game();
		if (newgame) 
			SetWindowLongPtr(hwnd, GWL_USERDATA, (long)newgame);
		else                                  
			return -1;
		//When the main window is created, all buttons are created as children.
		int x_buttonPlacement = 0;
		int y_buttonPlacement = 0;
		for (int i = 0; i < 361; i++)
		{
			if ((x_buttonPlacement + buttonSize) > windowWidth) {
				y_buttonPlacement += buttonSize;
				x_buttonPlacement = 0;
			}
			buttons[i] = CreateWindow(TEXT("button"), NULL,
				WS_VISIBLE | WS_CHILD | BS_BITMAP,
				x_buttonPlacement, y_buttonPlacement,
				buttonSize, buttonSize,
				hwnd, (HMENU)(i + 1), NULL, NULL);
			x_buttonPlacement += buttonSize;
			// Sets the background image for the button being created.
			SendMessageW(buttons[i], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_tile);
		}
		return 0;
	}

	case WM_COMMAND:
	{
		Game* newgame = nullptr;
		newgame = (Game*)GetWindowLongPtr(hwnd, GWL_USERDATA);
		// If a button is clicked, we change the background image.
		SendMessageW(buttons[(LOWORD(wParam))-1], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_current);
		if (newgame->getCurrentPlayer()->getColor() == Black)
			hImg_current = hImg_white;
		else
			hImg_current = hImg_black;
		newgame->nextPlayer();
		return 0;
	}
	case WM_PAINT:
	{
		// Sets the background for the main window.
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