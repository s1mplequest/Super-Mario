#pragma once
#include "TinyEngine\T_Engine.h"
#include"TinyEngine\T_Graph.h"
#include"TinyEngine\T_Util.h"
//#include"T_enginetest.h"
class information
{
public :
private:
	static const int TOTAL_LEVEL = 5;			// 游戏总关数
	static const int NPC_NUM = 20;			// 坦克总数
	static const int NPC_LOAD_TIME = 1000;			// NPC加载间隔时间
	static const int SUPER_TIME = 5000;			// 玩家角色无敌时间
	static const int PLAYER_LIFE = 3;			// 玩家初始生命数
	static const int BONUS_TIME = 15000;		// 奖励存在的时间
	static const int PLAYER_CHARGE = 20;			// 玩家炮弹初始值
	static const int BONUS_CHARGE = 20;			// 奖励炮弹数
	int score=0;
	int GameLevel;									// 游戏关数计数器
	int LifeCount;									// 玩家生命计数器
	
	bool looseBlood;								// 是否失血状态
	bool upgradeGameLevel;							// 是否已经升级
	//bool updateLifeCount;							// 是否更新玩家生命数
	//GAME_STATE GameState;
		int ChargeCount;								// 玩家炮弹计数器
	int time;									// 时间
	int NpcLoadNum;									// 已经加载的NPC计数器
	T_Graph* lifeImg;								// 状态栏玩家小图片

	T_Graph* npcNumImg;								// 状态栏敌方小图片
	T_Graph* flagImg;								// 状态栏关卡小图片
	T_Graph* bmbImg;
	T_Graph* teamImg;                              //小组图片；
	// 状态栏炮弹数小图片
	static const long T_LENGTH = 1000;
	long startTime;
public:
	information();
	~information();
	 void DisplayInfo(HDC hdc, int game_state);
	 void information::LoadImageRes();
	 void information::updateLevel();
	  int information::getBombNum() ;
	 void information::updateBobm();
	 void information::updatetime();
	 void information::init();
	 void information::updateScore(int type)
	 {
		 score = score + type;
	 }
	 int information::getTime();  //获取时间
	 void information::setTime() {
		 time=400;
	 };
	 void information::setLife( int a) {
		 LifeCount = LifeCount + a;
	 };
	  int information::getLife() {
		return LifeCount;
	 };

	  int getlevel() { return GameLevel; }
	  void setlevel(int level) { GameLevel = level; }
};