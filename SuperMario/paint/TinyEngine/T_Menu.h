//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ����: 2020-12-20
// ��Ȩ���� 2007-2021 ������
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include "T_Config.h"
#include "T_Graph.h"
#include "T_Audio.h"

//
// ���˵���֧�֣�
// ��ֱ���У������ְ�ť��ͼƬ��ť
// ˮƽ���У������ְ�ť��ͼƬ��ť
//
class T_Menu
{
protected:
	MENU_INFO menu_info;					// �˵���Ϣ
	
	int m_index;										// ��ǰ����˵�������
	bool isItemFocused;						// ��ǰ�˵��Ƿ�񽹵�
	
	int lastIndex;
	int key_index;
	int MaxMenuItemLen;						// ��˵����ֳ���

	int bkImageAlpha;							// ����ͼƬ͸����
	
	T_Graph gm_menuBkg;					// �˵�����
	T_Graph BtnDIB;								// �˵�ͼƬ					
	vector<MENUITEM> gm_menuItems;			// �˵���Ŀ

	
	StringAlignment GetAlignment();						
	FontStyle GetFontStyle();

	AudioDXBuffer* m_MoveSound;						// �˵�����ƹ�ʱ������
	AudioDXBuffer* m_ClickSound;						// �˵������ʱ������

	//+++++++++++++++++++++
	int wnd_width, wnd_height;
	int bkgX, bkgY;
	COLORREF backColor;
	int btnAlphaLevel;
	//+++++++++++++++++++++

public:
	T_Menu();
	virtual ~T_Menu(void);

	void SetMenuInfo(MENU_INFO menuInfo);
	void AddMenuItem(MENUITEM menuItem);	// ��Ӳ˵�������Ŀ

	//++++++++++++++++++++++++++++++++++++++++++++++
	// ���ò˵�����ͼƬ��͸���ȼ�������ɫ
	void SetMenuBkg(wstring img_path, int x =0, int y=0, int alphaLevel=255);	
	void SetMenuBkgColor(COLORREF bkgColor, int x = 0, int y = 0,int alphaLevel = 255);
	void SetBtnBmp(	wstring img_path,				// ���ò˵���ťͼƬ
								int btnWidth,						// ͼƬ��ť��
								int btnHeight,						// ͼƬ��ť��
								int btnAlpha = 255);			// ��ť��͸����
	void DrawMenu(HDC hdc);
	void SetWinSize(int width, int height) { wnd_width = width; wnd_height = height; }
	//++++++++++++++++++++++++++++++++++++++++++++++

	int MenuMouseClick(int x, int y);					// �˵�������¼�����
	void MenuMouseMove(int x, int y);				// �˵�����ƶ��¼�����
	int MenuKeyDown(WPARAM key);					// �˵������¼�����

	int GetMenuIndex(){ return m_index; }			// ���ص�ǰ��m_index
	void SetMenuIndex(int i){ m_index = i; }			// ���õ�ǰ��m_index

	void SetMoveSound(AudioDXBuffer* ms_buffer);
	void SetClickSound(AudioDXBuffer* mc_buffer);

	int GetMenuIndex(int x, int y);						// ���ݵ�ǰ����������˵���������

	void DestroyAll();
};
