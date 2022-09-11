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
//定义vector容器类型的数据类型vSpriteSet
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
	//static int scn_width, scn_height;                    //场景宽高
	//static int wnd_width, wnd_height;
	 T_Menu* gameMenu;
private:
	//重新定义动画帧序列
										  //定义与地图数据有关的变量
/*	static  int NPC_NUM;               //NPC总数
	static int EXPLOSION_FRAME[8];					// 爆炸帧动画
	static const int TOTAL_LEVEL = 5;	*/		// 游戏总关数
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

	Mario* player;	 //定义要使用的类对象

	OnlineplayerSet OnlinePlayers;
	T_Scene t_scene;                              //游戏场景
	gameMusic music;                      
	GAMELAYER mapLayer;          //游戏玩家

	information  xinxi;
			
	// 游戏菜单
	Flag *flag;
 //information  xinxi;
	bool isfold;
	bool pause;
	T_Graph PauseRegion;
	T_Graph Clik;
	bool info;

	bool restart=false;
	vSpriteSet Mushroom;                         //蘑菇		
	vBombSet player_bomb_set;						// 玩家炮弹集合
	vExplodeSet explosion_set;                         //爆炸集合
	vNpcSet  Npc_set;                                 //Npc集合

	


	websocket socket;

	void MultimodeInit();

												  //定义全局性的变量
	int scn_width, scn_height;                    //场景宽高
	int wnd_width, wnd_height;                    //游戏窗口宽高

	void LoadExplosion(int x, int y);				// 加载游戏爆炸效果
	void LoadGameMenu(int type);
	void LoadBomb(									// 发射炮弹处理
		T_Sprite* sp,								// 发射炮弹的角色
		vBombSet& bombSet,						// 炮弹集合
		int iTime = 0);
	void LoadMushRoom(int x, int y);											  //定义功能函数
	void LoadMap();                               //加载游戏地图场景
	void LoadPlayer();                            //加载游戏玩家
	void LoadOnlinePlayer(string name);
	void LoadFlag(int x,int y);                              //加载旗子
	void LoadGamelevel(int level);
	void LoadNpc(int x, int y);
	//void T_enginetest::logicManage();
	void UpdateBombPos(vBombSet& bombSet);		// 更新炮弹的位置
	void updateMushRoom(vSpriteSet& MushRoomset);//游戏场景void UpdatePlayerPos();                //更新玩家位置
	void UpdateNpcPos(vNpcSet  &Npc_set);                          //更新NPC位置
	void UpdateAnimation();                       //更新游戏动画
	void UpdatePlayerPos();
	void LoadOnLineMap();
	void ClearGameLevel();

	void CheckClear();                                 //判断是否通关

	void BorderCheck();

	void BombCollide(T_Sprite* bomb);				// 炮弹碰撞处理
	void SetMenuPara(wstring* menuItems,			// 要设置的菜单项
		int itemSize,					// 菜单项个数
		int m_w, int m_h,				// 菜单项宽高
		int posType);					// 按钮布局方式
	//void DisplayInfo(HDC hdc, int game_state);

public:
	
	virtual ~T_enginetest(void);
	T_enginetest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = NULL, WORD sm_icon = NULL,
		int winwidth = 1024, int winheight = 568,
		COLORREF bkColor = WIN_BKCLR);

	//重载T_Engine类中的虚函数实现游戏功能
	void GameInit();                                 //游戏初始化
	void GameLogic();                                //游戏逻辑处理
	void GameEnd();                                  //游戏结束处理
	void GamePaint(HDC hdc);                         //游戏显示
	void GameKeyAction(int Action = KEY_SYS_NONE);   //按键行为处理
	void GameMouseAction(int x, int y, int Action);  //鼠标行为处理


	
};