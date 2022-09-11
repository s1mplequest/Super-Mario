#pragma once
#include<WinSock2.h>
#include "TinyEngine\T_Engine.h"
#include "TinyEngine\T_Scene.h"
#include "TinyEngine\T_Sprite.h"
#include "TinyEngine\T_AI.h"
#include "TinyEngine\T_Menu.h"
#include"information.h"
#include"Mario.h"
#include "gameMusic.h"
#include"MushRoom.h"
#include"Fireball.h"
#include"flag.h"
#include"Goomba.h"
#include"websocket.h"
#include"OnlinePLayer.h"
#include"MessageMenu.h"
#include<iostream>
//#include "GameMenu.h"
//����vector�������͵���������vSpriteSet
typedef vector<MushRoom*> vSpriteSet;
typedef vector<T_Sprite*> vBombSet;
typedef vector<Fireball*> vExplodeSet;
typedef vector<Goomba*> vNpcSet;
typedef vector<Mario*> OnlineplayerSet;


class T_enginetest :public T_Engine
{
public:
	static int FRAME_BOMB[4];
	static int FRAME_EXPLODE[3];
	//static int scn_width, scn_height;                    //�������
	//static int wnd_width, wnd_height;
	 T_Menu* gameMenu;
private:
	//���¶��嶯��֡����
										  //�������ͼ�����йصı���
/*	static  int NPC_NUM;               //NPC����
	static int EXPLOSION_FRAME[8];					// ��ը֡����
	static const int TOTAL_LEVEL = 5;	*/		// ��Ϸ�ܹ���
	/*AudioDX ds;
	AudioDXBuffer backmusic_buffer;
	AudioDXBuffer robot_buffer;
	//AudioDXBuffer mousedown_buffer;
	//AudioDXBuffer mousemove_buffer;
	AudioDXBuffer blast_buffer;
	AudioDXBuffer jump_buffer;*/
		

	int frame;
	int nextkeyframe;
	int keyframe;

	Mario* player;	 //����Ҫʹ�õ������

	OnlineplayerSet OnlinePlayers;
	T_Scene t_scene;                              //��Ϸ����
	gameMusic music;                      
	GAMELAYER mapLayer;          //��Ϸ���

	information  xinxi;
			
	// ��Ϸ�˵�
	Flag *flag;
 //information  xinxi;
	bool isfold;
	bool pause;
	T_Graph PauseRegion;
	T_Graph Clik;
	bool info;

	bool restart=false;
	vSpriteSet Mushroom;                         //Ģ��		
	vBombSet player_bomb_set;						// ����ڵ�����
	vExplodeSet explosion_set;                         //��ը����
	vNpcSet  Npc_set;                                 //Npc����

	


	websocket socket;

	void MultimodeInit();

												  //����ȫ���Եı���
	int scn_width, scn_height;                    //�������
	int wnd_width, wnd_height;                    //��Ϸ���ڿ��

	void LoadExplosion(int x, int y);				// ������Ϸ��ըЧ��
	void LoadGameMenu(int type);
	void LoadBomb(									// �����ڵ�����
		T_Sprite* sp,								// �����ڵ��Ľ�ɫ
		vBombSet& bombSet,						// �ڵ�����
		int iTime = 0);
	void LoadMushRoom(int x, int y);											  //���幦�ܺ���
	void LoadMap();                               //������Ϸ��ͼ����
	void LoadPlayer();                            //������Ϸ���
	void LoadOnlinePlayer(string name);
	void LoadFlag(int x,int y);                              //��������
	void LoadGamelevel(int level);
	void LoadNpc(int x, int y);
	//void T_enginetest::logicManage();
	void UpdateBombPos(vBombSet& bombSet);		// �����ڵ���λ��
	void updateMushRoom(vSpriteSet& MushRoomset);//��Ϸ����void UpdatePlayerPos();                //�������λ��
	void UpdateNpcPos(vNpcSet  &Npc_set);                          //����NPCλ��
	void UpdateAnimation();                       //������Ϸ����
	void UpdatePlayerPos();
	void LoadOnLineMap();
	void ClearGameLevel();

	void CheckClear();                                 //�ж��Ƿ�ͨ��

	void BorderCheck();

	void BombCollide(T_Sprite* bomb);				// �ڵ���ײ����
	void SetMenuPara(wstring* menuItems,			// Ҫ���õĲ˵���
		int itemSize,					// �˵������
		int m_w, int m_h,				// �˵�����
		int posType);					// ��ť���ַ�ʽ
	//void DisplayInfo(HDC hdc, int game_state);

public:
	
	virtual ~T_enginetest(void);
	T_enginetest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = NULL, WORD sm_icon = NULL,
		int winwidth = 1024, int winheight = 568,
		COLORREF bkColor = WIN_BKCLR);

	//����T_Engine���е��麯��ʵ����Ϸ����
	void GameInit();                                 //��Ϸ��ʼ��
	void GameLogic();                                //��Ϸ�߼�����
	void GameEnd();                                  //��Ϸ��������
	void GamePaint(HDC hdc);                         //��Ϸ��ʾ
	void GameKeyAction(int Action = KEY_SYS_NONE);   //������Ϊ����
	void GameMouseAction(int x, int y, int Action);  //�����Ϊ����


	
};