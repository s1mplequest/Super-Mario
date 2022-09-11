#pragma once
#include "TinyEngine\T_Engine.h"
#include"TinyEngine\T_Graph.h"
#include"TinyEngine\T_Util.h"
//#include"T_enginetest.h"
class information
{
public :
private:
	static const int TOTAL_LEVEL = 5;			// ��Ϸ�ܹ���
	static const int NPC_NUM = 20;			// ̹������
	static const int NPC_LOAD_TIME = 1000;			// NPC���ؼ��ʱ��
	static const int SUPER_TIME = 5000;			// ��ҽ�ɫ�޵�ʱ��
	static const int PLAYER_LIFE = 3;			// ��ҳ�ʼ������
	static const int BONUS_TIME = 15000;		// �������ڵ�ʱ��
	static const int PLAYER_CHARGE = 20;			// ����ڵ���ʼֵ
	static const int BONUS_CHARGE = 20;			// �����ڵ���
	int score=0;
	int GameLevel;									// ��Ϸ����������
	int LifeCount;									// �������������
	
	bool looseBlood;								// �Ƿ�ʧѪ״̬
	bool upgradeGameLevel;							// �Ƿ��Ѿ�����
	//bool updateLifeCount;							// �Ƿ�������������
	//GAME_STATE GameState;
		int ChargeCount;								// ����ڵ�������
	int time;									// ʱ��
	int NpcLoadNum;									// �Ѿ����ص�NPC������
	T_Graph* lifeImg;								// ״̬�����СͼƬ

	T_Graph* npcNumImg;								// ״̬���з�СͼƬ
	T_Graph* flagImg;								// ״̬���ؿ�СͼƬ
	T_Graph* bmbImg;
	T_Graph* teamImg;                              //С��ͼƬ��
	// ״̬���ڵ���СͼƬ
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
	 int information::getTime();  //��ȡʱ��
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