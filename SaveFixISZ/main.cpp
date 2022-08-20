#include <windows.h>
#include <cassert>
#include <iostream>
#include <string>

#include "RepairCrash.hpp"

#pragma warning(disable : 4996)

#define ButtonFix 100
#define ButtonCheck 101
#define listbox 200

HWND hList;
HWND TX1;


char error[100];
char SelectedData[6] = "Data0";

LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:

		
		if (SendMessage(hList, LB_GETSEL, 0, 0) > 0) {
			strcpy(SelectedData,"Data0");
		}
		if (SendMessage(hList, LB_GETSEL, 1, 0) > 0) {
			strcpy(SelectedData, "Data1");
		}
		if (SendMessage(hList, LB_GETSEL, 2, 0) > 0) {
			strcpy(SelectedData, "Data2");
		}

		if (LOWORD(wParam) == ButtonCheck) {
			SetWindowText(TX1, error);
			troubleshoot(SelectedData, error);
		}

		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main(){
	HINSTANCE hInstance = GetModuleHandle(0);

	HWND hWnd;

	HWND hButton;
	HWND cButton;

	WNDCLASS winw;
	MSG msg;

	winw = {};
	winw.style = CS_HREDRAW | CS_HREDRAW;
	winw.lpfnWndProc = MessageHandler;
	winw.hInstance = hInstance;
	winw.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	winw.lpszClassName = "CPPWINDOWZT";
	assert(RegisterClass(&winw));

	

	hWnd = CreateWindow("CPPWINDOWZT", "ZTool", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 350, 0, 0, hInstance, 0);

	/*Text fields*/
	TX1 = CreateWindow("STATIC", "Error: No Save Selected.", WS_VISIBLE | WS_CHILD | NULL, 250, 50, 150, 15, hWnd, NULL, hInstance, NULL);
	
	/*Button's*/
	hButton = CreateWindow("button", "Repair", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 30, 50, 100, 30, hWnd, (HMENU)ButtonFix, hInstance, 0);
	cButton = CreateWindow("button", "Checkfile", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 30, 95, 100, 25, hWnd, (HMENU)ButtonCheck, hInstance, 0);

	//ListBox (select your save here)
	hList = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 140, 50, 100, 60, hWnd, (HMENU)listbox, NULL, NULL);
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 1");
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 2");
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 3");

	//Main loop
	while (true) {
		BOOL result = GetMessage(&msg, 0, 0, 0);
		if (result > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			return result;
		}
	}
}