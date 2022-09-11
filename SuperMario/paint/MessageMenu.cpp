#include"MessageMenu.h"
void MessageMenu::CreateEditWindow(HWND mh_WND,int x,int y,int nWidth,int nHeight)
{

	hwndEditbox = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,x,y,nWidth,nHeight,mh_WND, (HMENU)IDeditBox, NULL, NULL);

	if (!hwndEditbox) MessageBox(NULL, (LPCTSTR)TEXT("创建文本框失败"), (LPCTSTR)TEXT("Message"), MB_OK);
	else 
	{
		ShowWindow(hwndEditbox, SW_SHOW);

		UpdateWindow(hwndEditbox);
	}

};
void MessageMenu::ShowWIndow()
{
	ShowWindow(hwndEditbox, SW_SHOW);
	UpdateWindow(hwndEditbox);
}