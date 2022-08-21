/*
Ice Station Z Save Fix v0.4 by Yunix
this Application will fix your corrupted Ice Station Z saves!

Enjoy :D
*/

#include <windows.h>
#include <cassert>
#include <iostream>
#include <string>

#include "RepairCrash.hpp"
#include "types.h"

#pragma warning(disable : 4996)

extern std::string ErrorString = "";




HWND hList; //ListBox
HWND TX1;	//TextBox

//Variables
char error[100];
//char SelectedData[6] = "Data0";

Data *data = new Data;
LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		ErrorString = "";
		//Check the Saves
		if (LOWORD(wParam) == ButtonCheck)
		{
			if (SendMessage(hList, LB_GETSEL, 0, 0) > 0) {
				std::cout << "Slot 1 selected!\n";
				data->CheckData("Data0");	//Check Data0
			}
			if (SendMessage(hList, LB_GETSEL, 1, 0) > 0) {
				std::cout << "Slot 2 selected!\n";
				data->CheckData("Data1");	//Check Data1
			}
			if (SendMessage(hList, LB_GETSEL, 2, 0) > 0) {
				std::cout << "Slot 3 selected!\n";
				data->CheckData("Data2");	//Check Data2
			}
			SetWindowText(TX1, ErrorString.c_str());
		}

		//Repair the Crashed saves
		if (LOWORD(wParam) == ButtonRepair)
		{
			if (SendMessage(hList, LB_GETSEL, 0, 0) > 0) {
				data->RepairCrash("Data0");	//Repair Data0
			}
			if (SendMessage(hList, LB_GETSEL, 1, 0) > 0) {
				data->RepairCrash("Data1");	//Repair Data1
			}
			if (SendMessage(hList, LB_GETSEL, 2, 0) > 0) {
				data->RepairCrash("Data2");	//Repair Data2
			}
			SetWindowText(TX1, ErrorString.c_str());
		}

		if (LOWORD(wParam) == CreditsBox) {
			MessageBoxA(hWnd, "Ice Station Z Save Fix Tool v0.4\nby Yunix!","Credits", MB_ICONINFORMATION);
		}
		if (LOWORD(wParam) == ExitBox) {
			exit(0);
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

	HMENU hMenu = CreateMenu();

	HMENU hAbout = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hAbout, "About");
	AppendMenu(hAbout, MF_STRING, CreditsBox, "Credits");
	AppendMenu(hAbout, MF_STRING, ExitBox, "Exit");

	winw = {};
	winw.style = CS_HREDRAW | CS_HREDRAW;
	winw.lpfnWndProc = MessageHandler;
	winw.hInstance = hInstance;
	winw.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	winw.lpszClassName = "CPPWINDOWZT";
	assert(RegisterClass(&winw));

	
	//Window
	hWnd = CreateWindow("CPPWINDOWZT", "ZTool", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 540, 250, 0, 0, hInstance, 0);

	/*Text fields*/
	TX1 = CreateWindow("STATIC", "Please select a Save-Slot to continue.", WS_VISIBLE | WS_CHILD | NULL, 250, 50, 260, 150, hWnd, NULL, hInstance, NULL);
	
	/*Button's*/
	hButton = CreateWindow("button", "Repair", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 30, 50, 100, 30, hWnd, (HMENU)ButtonRepair, hInstance, 0);
	cButton = CreateWindow("button", "Checkfile", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 30, 95, 100, 25, hWnd, (HMENU)ButtonCheck, hInstance, 0);


	//ListBox (select your save here)
	hList = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 140, 50, 100, 60, hWnd, (HMENU)listbox, NULL, NULL);
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 1");
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 2");
	SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)"Slot 3");

	SetMenu(hWnd, hMenu);

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
	delete data;
}