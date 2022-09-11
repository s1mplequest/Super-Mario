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
#include "T_Display.h"

class T_Engine
{
public:
	static HWND m_hWnd;					// ���ھ��
	static HWND 	UserMenu;
	static HWND 	PwdMenu;
	static HINSTANCE m_hInstance;		// ʵ�����
	static T_Engine* pEngine;			// ���ྲָ̬��(����ָ����̳���)
	 int wndWidth, wndHeight;			// ���ڿ��
	 int scrnWidth, scrnHeight;
	 int GameState;
	 WPARAM keyaction1;
protected:

	ULONG_PTR ptrGdiplusToken;			// ��GDI+������
	//WPARAM keyaction;
	LPCTSTR wndClass;					// ����������
	LPCTSTR wndTitle;					// ���ڱ���	
				// ��Ļ�ֱ��ʿ���
	WORD wIcon, wSmIcon;				// �����ͼ�꼰Сͼ��
	BOOL m_bFullScreen;					// �Ƿ�ȫ����ʾ��־;

	RECT m_rcOld;						// ��ǰ���ڳߴ�
	LONG style;							// ���ڻ������
	LONG ex_style;						// ������չ���
	T_Display* p_disp;					// ������ʾ��ָ��

	int IntervalTime;					// ��Ϸ֡ˢ�¼��ʱ��
	BOOL isAsleep;						// �����Ƿ��ڷǽ���״̬

	HBITMAP bufferBitmap;				// �ڴ滺��λͼ
	HDC bufferDC;						// �ڴ滺���豸

	bool keys[256];						// ��¼����״̬������
//	int GameState;						// ��Ϸ״̬(ΪGAME_STATE����ֵ)

	BOOL quickRender;

public:
	// ���캯��
	T_Engine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, 
		     WORD Icon = NULL, WORD SmIcon = NULL, 
		     int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		     COLORREF bkColor = WIN_BKCLR);
	// ��������
	virtual ~T_Engine();
	// ��ȡ��Ϸ֡ˢ�¼��ʱ��
	int GetInterval() { return IntervalTime; }
	// ������Ϸ֡ˢ�¼��ʱ��
	void SetFrame(int iTime) { IntervalTime = 1000 / iTime; }
	// ��ȡ�����Ƿ�Ϊ����״̬
	BOOL GetSleep() { return isAsleep; }
	// ���ô����Ƿ�Ϊ����״̬
	void SetSleep(BOOL asleep) { isAsleep = asleep; }
	// ���ô����Ƿ�ȫ��Ļ��ʾ
	void SetFullScreen(BOOL isFull){ m_bFullScreen = isFull; }


	// ��ȡ�����Ƿ�Ϊ����״̬
	BOOL GetQuickRender() { return quickRender; }
	// ���ô����Ƿ�Ϊ����״̬
	void SetQuickRender(BOOL quick) { quickRender = quick; }

	// ��ȡ��ǰ�İ���״̬
	 bool CheckKey(WPARAM wParam){ 
		
		 return keys[wParam]; }
	// ���Ӱ�����Ϊ����
	void SubKeyAction(WPARAM wParam);

	void SetBackColor(COLORREF bkcolor);// ����: 2019-10-11(�ı仺��λͼ����ɫ)
	HDC GetBufferDC(){ return bufferDC; }

	// ��ϵͳ�Զ����õĻص�����
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, 
		                         WPARAM wParam, LPARAM lParam );
	// ��ʼ������
	BOOL GameWinInit();
	// ��Ϣ�������������ص���������
	LRESULT GameEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// ������������
	void StartEngine();

public:
	// ����������(������ϷҪ������Щ������������Ϸ���ܴ���)
	// ��Ϸ��ʼ��
	virtual void GameInit()=0;		
	// ��Ϸ�߼�����
	virtual void GameLogic()=0;		
	// ��Ϸ��������
	virtual void GameEnd()=0;
	// ����GAME_STATEֵ��ʾ��Ϸ����
	virtual void GamePaint(HDC hdc)=0;
	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int ActionType=KEY_SYS_NONE)=0;
	// ����KM_ACTIONֵ���������Ϊ
	virtual void GameMouseAction(int x, int y, int ActionType)=0;	
};
