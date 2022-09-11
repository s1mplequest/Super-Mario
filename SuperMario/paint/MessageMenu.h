#pragma once
#include"TinyEngine/T_Menu.h"
class MessageMenu :public T_Menu
{
private:
	 HWND 	hwndEditbox;
	// int  	cxChar, cyChar;
	const int		IDeditBox = 2;

public:
	void CreateEditWindow(HWND mh_WND, int x, int y, int nWidth, int nHeight);
	void ShowWIndow();
};