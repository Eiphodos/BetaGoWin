// BetaGoWin.cpp
// Main file for the BetaGo application

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <vector>
#include "../Headers/go.h"
#include "../Headers/player.h"
#include "../Headers/intersection.h"
#include "../Headers/game.h"

// Handler for the main window and the buttons
HWND hwnd01, w_newgame, w_currentplayer, w_score;
HWND w_buttons[361];

// Background color for the main window
int color_white = 0x00ffffff;

// Bitmaps for the buttons

HBITMAP hImg_white = (HBITMAP)LoadImage(NULL, L"bitmap_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_black = (HBITMAP)LoadImage(NULL, L"bitmap_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_tile = (HBITMAP)LoadImage(NULL, L"bitmap_tile.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hImg_current = hImg_black; // Set the initial value to black since he is starting.

// Width and height for the main window and size for the buttons.

int windowWidth = 585;
int windowHeight = 630;
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdc01;
	TCHAR wtext_blackPlayer[] = _T("Current Player: Black");
	TCHAR wtext_whitePlayer[] = _T("Current Player: White");
	switch (msg)
	{
	case WM_CREATE:
	{
		// When our main window is created, we create a new game object and save a pointer to that on the heap
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
			w_buttons[i] = CreateWindow(TEXT("button"), NULL,
				WS_VISIBLE | WS_CHILD | BS_BITMAP,
				x_buttonPlacement, y_buttonPlacement,
				buttonSize, buttonSize,
				hwnd, (HMENU)(i), NULL, NULL);
			x_buttonPlacement += buttonSize;
			// Sets the background image for the button being created.
			SendMessageW(w_buttons[i], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_tile);
		}
		return 0;
	}

	case WM_COMMAND:
	{
		// Here we retrieve the pointer to our game object so we can use it.
		Game* newgame = nullptr;
		newgame = (Game*)GetWindowLongPtr(hwnd, GWL_USERDATA);
		int pressedButton = LOWORD(wParam);
		if (!(newgame->illegalPlacement(pressedButton))){
			// If a button is clicked, we change the background image.
			SendMessageW(w_buttons[pressedButton], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_current);
			if (newgame->currentPlayer->color == Black)
				hImg_current = hImg_white;
			else
				hImg_current = hImg_black;
			newgame->captureIntersections(pressedButton);
			vector<int> *captured = &newgame->index_capturedThisTurn;
			for (int i = 0; i < captured->size(); i++){
				SendMessageW(w_buttons[captured->at(i)], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImg_tile);
			}
			newgame->nextTurn();
			InvalidateRect(hwnd, &rc, FALSE);
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			return 0;
		}
		else{
			return 0;
		}
	}
	case WM_PAINT:
	{
		Game* newgame = nullptr;
		newgame = (Game*)GetWindowLongPtr(hwnd, GWL_USERDATA);
		if (newgame->currentPlayer->color == Black){
			hdc01 = BeginPaint(hwnd, &ps);
			SetBkColor(hdc01, color_white);
			TextOut(hdc01, 5, 570, wtext_blackPlayer, _tcslen(wtext_blackPlayer));
			EndPaint(hwnd, &ps);
		}
		else {
			hdc01 = BeginPaint(hwnd, &ps);
			SetBkColor(hdc01, color_white);
			TextOut(hdc01, 5, 570, wtext_whitePlayer, _tcslen(wtext_whitePlayer));
			EndPaint(hwnd, &ps);
		}
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