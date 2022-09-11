#include "T_enginetest.h"
#include"resource.h"
//重新定义帧序列

int T_enginetest::FRAME_BOMB[4] = { 0,1,2,3 };
int T_enginetest::FRAME_EXPLODE[3] = { 0,1,2 };
//WinMain函数
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"SuperMario";    //游戏窗口标题栏文字内容
	T_enginetest* test = new T_enginetest(h_instance, WIN_CLASS, WinTitle, IDI_ICON1, IDI_ICON1, 1024, 768);
	T_Engine::pEngine = test;
	test->SetFrame(24);
	test->StartEngine();
	return TRUE;
}
T_enginetest::T_enginetest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
	WORD icon, WORD sm_icon, int winwidth, int winheight, COLORREF bkColor)
	:T_Engine(h_instance, sz_winclass, sz_title, icon, sm_icon, winwidth, winheight, bkColor)
{


	wnd_width = winwidth;
	wnd_height = winheight;
}
//析构函数
T_enginetest::~T_enginetest(void) {}
void T_enginetest::ClearGameLevel()
{
	delete gameMenu;
	gameMenu = NULL;



	Npc_set.clear();
	Npc_set.swap(vector<Goomba*>());


	Mushroom.clear();
	Mushroom.swap(vector<MushRoom*>());


	player_bomb_set.clear();
	player_bomb_set.swap(vector<T_Sprite*>());


	explosion_set.clear();
	explosion_set.swap(vector<Fireball*>());
}
void T_enginetest::CheckClear()
{
	if (player->CollideWith(flag))
	{
		GameState = GAME_WIN;
		xinxi.updateLevel();
		ClearGameLevel();
		LoadGamelevel(xinxi.getlevel());
	}
}
void T_enginetest::BorderCheck()
{
	/*
	if (xinxi.getTime() <= 0)
	{
		xinxi.setLife(-1);

		//GameState = GAME_LOSE;
		if (xinxi.getLife() == 0)
		{
			delete player;
			player = NULL;
			music.setlose(true);
			GameState = GAME_OVER;
		}
		else {
			music.setlose(true);
		}
	}
	*/
	if (player->GetY() >= 580)
	{
		xinxi.setLife(-1);
		player->StatusChange(PLAYER_SMALL);
		//GameState = GAME_LOSE;
		if (xinxi.getLife() == 0)
		{
			//music.setlose(true);

			player->SetActive(true);
			t_scene.setScenceXY(0, 0);
			t_scene.SetScenePos(0, 0);
			player->SetPosition(12, wnd_height - 600 - player->GetRatioSize().cy);
			player->setFalling(false);
			GameState = GAME_OVER;

		}
		else
		{
			music.setlose(true);
			player->SetActive(true);
			player->SetPosition(12, wnd_height - 600 - player->GetRatioSize().cy);
			player->setFalling(false);
		}
		if (keyaction1 != NULL)
		{
			music.playmusic(GameState, T_Engine::keyaction1,isfold);
			keyaction1 = NULL;
			music.isboom = false;
		}
		if (player->CollideWith(flag))
		{
			GameState = GAME_NEXT;

		}
	}
}
void T_enginetest::LoadMap()
{
	SCENE_LAYERS::iterator p;
	int scn_x = 0, scn_y = 0;
	switch (xinxi.getlevel())
	{
	case 0:
		t_scene.LoadTxtMap("map\\FirstLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}

		LoadMushRoom(400, 400);
		LoadMushRoom(5280, 640);
		LoadNpc(1380, 544 - 96 + 200);
		LoadNpc(2430, 320 - 64 + 200);
		LoadNpc(4140, 510 + 200);
		LoadNpc(5248, 300 + 200);
		LoadNpc(6144, 160 + 200);

		LoadFlag(6630, 000);
		//	LoadFlag(1430, 50);
		break;
	case 1:
		t_scene.LoadTxtMap("map\\SecondLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		LoadMushRoom(400, 200);
		LoadNpc(2000, 200);
		LoadFlag(6912, 45);
		break;
	case 2:
		t_scene.LoadTxtMap("map\\ThirdLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		LoadMushRoom(400, 200);
		LoadNpc(2000, 200);
		LoadFlag(6928, 25);
		break;
	default:
		break;
	}
	/* 
	if (xinxi.getlevel() == 0)
	{
		t_scene.LoadTxtMap("map\\FirstLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		int scn_x = (wnd_width - scn_width) * 0;
		int scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		SCENE_LAYERS::iterator p;
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}

			加载每关蘑菇和板栗和旗子
			LoadMushRoom(400, 400);
			LoadMushRoom(5280, 640);
			LoadNpc(1380, 544 - 96 + 200);
			LoadNpc(2430, 320 - 64 + 200);
			LoadNpc(4140, 510 + 200);
			LoadNpc(5248, 300 + 200);
			LoadNpc(6144, 160 + 200);
	
		LoadFlag(6630,000);
	//	LoadFlag(1430, 50);
	}
	else if (xinxi.getlevel() == 1)
	{
		t_scene.LoadTxtMap("map\\SecondLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		int scn_x = (wnd_width - scn_width) * 0;
		int scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		SCENE_LAYERS::iterator p;
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		加载每关蘑菇和板栗
		LoadMushRoom(400, 200);
		LoadNpc(2000, 200);
		LoadFlag(6912, 45);
	}
	else if (xinxi.getlevel() == 2)
	{
		t_scene.LoadTxtMap("map\\ThirdLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		int scn_x = (wnd_width - scn_width) * 0;
		int scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		SCENE_LAYERS::iterator p;
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		加载每关蘑菇和板栗
		LoadMushRoom(400, 200);
		LoadNpc(2000, 200);
		LoadFlag(6928, 25);
	}
	*/
}
void T_enginetest::LoadOnLineMap()
{
	SCENE_LAYERS::iterator p;
	int scn_x = 0, scn_y = 0;
	switch (xinxi.getlevel())
	{
	case 0:
		t_scene.LoadTxtMap("map\\FirstLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		LoadFlag(6630, 000);
		//	LoadFlag(1430, 50);
		break;
	case 1:
		t_scene.LoadTxtMap("map\\SecondLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}
		LoadFlag(6912, 45);
		break;
	case 2:
		t_scene.LoadTxtMap("map\\ThirdLevelMap.txt");
		scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
		scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
		//scn_height = 512;
		//t_scene.Remove()
		scn_x = (wnd_width - scn_width) * 0;
		scn_y = (wnd_height - scn_height);
		t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
		for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
		{
			if (p->layer->ClassName() == "T_Map")
				p->layer->SetPosition(scn_x, scn_y);
		}

		LoadFlag(6928, 25);
		break;
	default:
		break;
	}
}
void T_enginetest::LoadNpc(int x, int y)
{
	GAMELAYER gameLayer;
	SPRITEINFO NPCINFO;

	NPCINFO.Active = true;
	NPCINFO.Dead = false;
	NPCINFO.Visible = true;
	NPCINFO.Rotation = TRANS_NONE;
	NPCINFO.Ratio = 1.0f;
	NPCINFO.Speed = 2;
	NPCINFO.Alpha = 255;
	NPCINFO.Level = 0;
	NPCINFO.Score = 0;
	NPCINFO.Dir = DIR_RIGHT;


	NPCINFO.X = x;
	NPCINFO.Y = y;

	Npc_set.push_back(new Goomba(L".\\res\\goomba.png", 32, 32));

	//初始化刚增加的项目
	Goomba *sp = Npc_set.back();
	sp->Initiate(NPCINFO);
	sp->SetSequence(Goomba::FRAME_RUN, 6);
	sp->SetLayerTypeID(LAYER_NPC);


	gameLayer.layer = sp;
	gameLayer.type_id = LAYER_NPC;
	gameLayer.z_order = t_scene.getBarrier()->getZorder() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);

	sp = NULL;
}
void T_enginetest::LoadPlayer()
{
	GAMELAYER gameLayer{};
	SPRITEINFO spInfo{};

	// 加载玩家角色
	player = new Mario(L".\\res\\sMario.png", 24, 32);

	spInfo.Active = true;
	spInfo.Dead = false;
	spInfo.Dir = DIR_DOWN;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 1.0f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 4;
	spInfo.Alpha = 255;
	spInfo.Visible = true;
	player->SetSequence(Mario::FRAME_RUN, 6);
	player->Initiate(spInfo);
	player->SetLayerTypeID(LAYER_PLY);
	//player->setFalling(false);
	int x = 10;
	int y = wnd_height - 160 - player->GetRatioSize().cy;
	player->SetPosition(x, y);
	player->setFalling(true);
	player->setJumping(false);
	player->SetDir(DIR_DOWN);
	player->fallingDown();
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
}
void T_enginetest::LoadOnlinePlayer(string name)
{
	GAMELAYER gameLayer{};
	SPRITEINFO spInfo{};

	// 加载玩家角色
	OnlinePlayers.push_back(new Mario(L".\\res\\sMario.png", 24, 32));

	spInfo.Active = true;
	spInfo.Dead = false;
	spInfo.Dir = DIR_RIGHT;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 1.0f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 4;
	spInfo.Alpha = 255;
	spInfo.Visible = true;
	player->SetName(name);
	player->SetSequence(Mario::FRAME_RUN, 6);
	player->Initiate(spInfo);
	player->SetLayerTypeID(LAYER_PLY);
	//player->setFalling(false);
	int x = 10;
	int y = wnd_height - 160 - player->GetRatioSize().cy;
	player->SetPosition(x, y);
	player->setFalling(true);
	player->setJumping(false);
	player->SetDir(DIR_DOWN);
	player->fallingDown();
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
}
void T_enginetest::LoadGamelevel(int level)
{
	t_scene.RemoveAll();
	

	LoadMap();         //加载地图、蘑菇、旗子、板栗
	LoadPlayer();
	LoadGameMenu(GameState);
	GameState = GAME_RUN;
}
void T_enginetest::LoadBomb(T_Sprite* sp,vBombSet& bombSet,	int iTime)
{
	// 发射炮弹的角色// 炮弹集合
	sp->SetEndTime(GetTickCount64());
	if (sp->GetEndTime() - sp->GetStartTime() >= (DWORD)iTime)
	{
		sp->SetStartTime(sp->GetEndTime());

		GAMELAYER gameLayer;
		SPRITEINFO bombInfo;
		int m_dir = sp->GetDir();


		bombSet.push_back(new T_Sprite(L".\\res\\bubble.png", 16, 16));

		//初始化刚增加的项目
		T_Sprite *bomb = bombSet.back();

		bombInfo.Active = true;
		bombInfo.Dead = false;
		bombInfo.Dir = m_dir;
		bombInfo.Rotation = TRANS_NONE;
		bombInfo.Ratio = 1;
		bombInfo.Level = 0;
		bombInfo.Score = 0;
		bombInfo.Speed = 12;
		bombInfo.Alpha = 255;

		switch (m_dir)
		{
		case DIR_LEFT:
			bombInfo.X = sp->GetX();
			bombInfo.Y = sp->GetY() + sp->GetRatioSize().cy / 2;
			break;
		case DIR_RIGHT:
			bombInfo.X = sp->GetX() + sp->GetRatioSize().cx;
			bombInfo.Y = sp->GetY() + sp->GetRatioSize().cy / 2;
			break;
		case DIR_UP:
		default:
			break;
		}

		bombInfo.Visible = true;
		bomb->Initiate(bombInfo);
		bomb->SetSequence(FRAME_BOMB, 4);
		gameLayer.layer = bomb;
		gameLayer.type_id = LAYER_PLY_BOMB;
		gameLayer.layer->SetLayerTypeID(LAYER_PLY_BOMB);
		gameLayer.z_order = t_scene.GetTotalLayers() + 1;
		gameLayer.layer->setZorder(gameLayer.z_order);
		t_scene.Append(gameLayer);
	}
}
void T_enginetest::LoadGameMenu(int type)
{
	if (gameMenu == NULL) gameMenu = new T_Menu();
	gameMenu->SetWinSize(wnd_width, wnd_height);
	gameMenu->SetMenuIndex(-1);
	//原来加载音乐
	//gameMenu->SetClickSound(&mousedown_buffer);
	//gameMenu->SetMoveSound(&mousemove_buffer);
	int btnwidth = 200, btnheight = 80;
	if (type == GAME_START)
	{
		wstring menuItems[] = { L"单人游戏", L"多人游戏", L"关于游戏", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 150));
		//gameMenu->SetMenuBkg(L".\\res\\game\\bk.png", 0, 0, 250);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 250);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 160, 70);
		SetMenuPara(menuItems, 4, 280, 60, 0);
		gameMenu->SetClickSound(&(music.mousedown_buffer));
		gameMenu->SetMoveSound(&(music.mousedown_buffer));
	}
	if ( type == GAME_ABOUT)
	{
		wstring menuItems[] = { L"返回菜单", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems, 2, 280, 60, 0);
		gameMenu->SetClickSound(&(music.mousedown_buffer));
		gameMenu->SetMoveSound(&(music.mousedown_buffer));
		
	}
	if (type == GAME_ONLINE)
	{
		wstring menuItems[] = { L"返回菜单", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems, 2, 280, 60, 2);
		
	}
	if (type == GAME_MULTI)
	{
		wstring menuItems[] = { L"登录", L"注册",L"返回"};
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems, 3, 280, 60, 0);
		gameMenu->SetClickSound(&(music.mousedown_buffer));
		gameMenu->SetMoveSound(&(music.mousedown_buffer));
	}
	if (type == GAME_OVER)
	{
		
		wstring menuItems[] = { L"重新开始", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems,2 , 280, 60, 2);
		gameMenu->SetClickSound(&(music.mousedown_buffer));
		gameMenu->SetMoveSound(&(music.mousedown_buffer));
		
	}
	if (type == GAME_WIN)
	{
		wstring menuItems[] = { L"返回菜单", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems, 2, 280, 60, 2);
		gameMenu->SetClickSound(&(music.mousedown_buffer));
		gameMenu->SetMoveSound(&(music.mousedown_buffer));

	}
	if (type == GAME_RUN)
	{
		wstring menuItems[] = { L"返回菜单", L"退出游戏" };
		gameMenu->SetMenuBkgColor(RGB(50, 50, 50), 0, 0, 150);
		gameMenu->SetMenuBkg(L".\\res\\12.png", 0, 0, 100);
		gameMenu->SetBtnBmp(L".\\res\\btn.png", 280, 60);
		SetMenuPara(menuItems, 2, 280, 60, 2);

	}


}
void T_enginetest::LoadExplosion(int x, int y)
{
	SPRITEINFO explInfo;
	GAMELAYER gameLayer;

	explosion_set.push_back(new Fireball(L".\\res\\bubble_explode.png", 32, 32));
	// 初始化刚增加的项目
	Fireball* sp_explosion = explosion_set.back();

	explInfo.Active = true;
	explInfo.Dead = false;
	explInfo.Dir = 0;
	explInfo.Rotation = TRANS_NONE;
	explInfo.Ratio = 1;
	explInfo.Level = 0;
	explInfo.Score = 0;
	explInfo.Speed = 5;
	explInfo.Alpha = 255;
	explInfo.X = x;
	explInfo.Y = y;
	explInfo.Visible = true;

	sp_explosion->Initiate(explInfo);
	sp_explosion->SetSequence(FRAME_EXPLODE, 3);
	sp_explosion->SetLayerTypeID(LAYER_EXPLOSION);

	gameLayer.layer = sp_explosion;
	gameLayer.type_id = LAYER_EXPLOSION;
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
	music.setBoom(true);
}
void T_enginetest::LoadMushRoom(int x, int y)
{
	GAMELAYER gameLayer;
	SPRITEINFO bonusInfo;

	bonusInfo.Active = true;
	bonusInfo.Dead = false;
	bonusInfo.Visible = true;
	bonusInfo.Rotation = TRANS_NONE;
	bonusInfo.Ratio = 1.0f;
	bonusInfo.Speed = 5;
	bonusInfo.Alpha = 255;
	bonusInfo.Level = 0;
	bonusInfo.Score = 0;
	bonusInfo.Dir = DIR_LEFT;


	bonusInfo.X = x;
	bonusInfo.Y = y;

	Mushroom.push_back(new MushRoom(L".\\res\\mushroom.png", 32, 32));

	//初始化刚增加的项目
	MushRoom *sp = Mushroom.back();
	sp->Initiate(bonusInfo);
	sp->SetSequence(MushRoom::FRAME_STAND, 1);
	sp->SetLayerTypeID(LAYER_BONUS);
	sp->SetStartTime(GetTickCount64());
	//flag->SetPosition(x, y);

	gameLayer.layer = sp;
	gameLayer.type_id = LAYER_BONUS;
	gameLayer.z_order = t_scene.getBarrier()->getZorder() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);

	sp = NULL;
}
void T_enginetest::LoadFlag(int x,int y)
{
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;

	// 加载玩家角色
	flag = new Flag(L".\\res\\flag1.png", 32, 295);

	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = -1;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 1.0f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 0;
	spInfo.Alpha = 255;
	spInfo.Visible = true;
	flag->Initiate(spInfo);
	flag->SetLayerTypeID(LAYER_TARGET);


	flag->SetPosition(x, y);

	gameLayer.layer = flag;
	gameLayer.type_id = LAYER_TARGET;
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
}
void T_enginetest::UpdateBombPos(vBombSet& bombSet)
{
	if (bombSet.size() == 0) return;

	vBombSet::iterator itp = bombSet.begin();
	for (; itp != bombSet.end();)
	{
		if ((*itp)->IsVisible() == true && (*itp)->IsActive() == true)
		{
			int SpeedX = 0, SpeedY = 0;
			switch ((*itp)->GetDir())
			{
			case DIR_LEFT:
				SpeedX = -(*itp)->GetSpeed();
				SpeedY = 0;
				break;

			case DIR_RIGHT:
				SpeedX = (*itp)->GetSpeed();
				SpeedY = 0;
				break;

			}
			(*itp)->Move(SpeedX, SpeedY);

			//检测炮弹是否击中目标
			BombCollide((*itp));
			if (GameState != GAME_RUN) return;
		}
		/*
		if ((*itp)->IsVisible() == false ||
		(*itp)->GetY() < 0 || (*itp)->GetX() < 0 ||
		(*itp)->GetY() > wnd_height || (*itp)->GetX() > wnd_width)
		{
		//删除场景中的对象
		SCENE_LAYERS::iterator p;
		for (p = t_scene.getSceneLayers()->begin();
		p != t_scene.getSceneLayers()->end(); p++)
		{
		if ((*p).layer == (*itp))
		{
		p = t_scene.getSceneLayers()->erase(p);
		break;
		}
		}
		delete (*itp);
		itp = bombSet.erase(itp);
		}
		*/
		if (itp == bombSet.end())
		{
			break;
		}

		itp++;
	}
}
void T_enginetest::UpdatePlayerPos()
{
	if (player == NULL) return;
	if (player->IsDead() == false && player->IsVisible() == true && player->IsActive() == true)
	{
		
		// 处理玩家的跳跃和左右移动	
		if (!player->getJumping())
		{
			if (player->GetDir() == DIR_LEFT)
			{
				player->updatePostion(DIR_LEFT, 0, 0, t_scene.getBarrier());
				t_scene.ScrollScene(player);//滚动背景
			}
			if (player->GetDir() == DIR_RIGHT)
			{
				player->updatePostion(DIR_RIGHT, 0, 0, t_scene.getBarrier());
				t_scene.ScrollScene(player);//滚动背景
			}
		}
		else
		{
			if (player->GetDir() == DIR_LEFT)
			{
				player->updatePostion(DIR_LEFT, 0, 0, t_scene.getBarrier());

				t_scene.ScrollScene(player);//滚动背景
			}
			if (player->GetDir() == DIR_RIGHT)
			{
				player->updatePostion(DIR_RIGHT, 0, 0, t_scene.getBarrier());

				t_scene.ScrollScene(player);//滚动背景
			}
			player->jumpUpDown(t_scene.getBarrier());
		}
		/*if (player->CollideWith(t_scene.getBarrier()) && !player->getJumping() && !player->getFalling())
		{
			player->setFalling(true);

		}
		*/


	}
}
void T_enginetest::UpdateAnimation()
{


	if (player != NULL)
	{
		if (player->IsVisible() == true && player->IsActive() == true)
		{
			if (player->GetDir() == DIR_LEFT)
			{
				player->SetRotation(TRANS_HFLIP_NOROT);
			}
			if (player->GetDir() == DIR_RIGHT)
			{
				player->SetRotation(TRANS_NONE);
			}
			player->LoopFrame();
		}
	}
	if (player_bomb_set.size()>0)
	{
		vBombSet::iterator e = player_bomb_set.begin();
		for (; e != player_bomb_set.end();)
		{
			(*e)->LoopFrame(true);
			if (e == player_bomb_set.end())
			{
				break;
			}
			e++;
		}
	}
	if (explosion_set.size()>0)
	{
		vExplodeSet::iterator e = explosion_set.begin();
		for (; e != explosion_set.end();)
		{
			if ((*e)->LoopFrameOnce() == true)
			{
				// 删除场景中已经失效的爆炸对象	
				SCENE_LAYERS::iterator lp;
				for (lp = t_scene.getSceneLayers()->begin(); lp != t_scene.getSceneLayers()->end(); lp++)
				{
					if ((*lp).layer == (*e))
					{
						lp = t_scene.getSceneLayers()->erase(lp);
						break;
					}
				}
				delete (*e);
				e = explosion_set.erase(e);
				continue;
			}
			else
			{
				++e;
			}
		}
	}
	vNpcSet::iterator p;

	if (Npc_set.size()>0)
	{
		for (p = Npc_set.begin(); p != Npc_set.end(); p++)
		{
			(*p)->LoopFrame();
		}
	}
}
void T_enginetest::updateMushRoom(vSpriteSet& bonusSet)
{
	if (bonusSet.size() == 0) return;
	vSpriteSet::iterator itp;
	if (bonusSet.size() > 0)
	{
		itp = bonusSet.begin();
		for (; itp != bonusSet.end();)
		{

			(*itp)->updatePosition((*itp)->GetDir(), t_scene.getBarrier());
			(*itp)->Gravityefect(t_scene.getBarrier());
			bool isPicked = player->CollideWith(*itp);
			if (isPicked)
			{
				music.seteat(true);
				player->StatusChange(PLAYER_BIG);
				xinxi.updateScore(20);
				//删除场景中的对象	
				SCENE_LAYERS::iterator p;
				for (p = t_scene.getSceneLayers()->begin();
					p != t_scene.getSceneLayers()->end(); p++)
				{
					if ((*p).layer == (*itp))
					{
						p = t_scene.getSceneLayers()->erase(p);
						break;
					}
				}
				delete (*itp);
				itp = bonusSet.erase(itp);
			}

			if (itp == bonusSet.end())
			{
				break;
			}
			itp++;
		}
	}

}
void T_enginetest::UpdateNpcPos(vNpcSet  &Npc_set)
{
	if (Npc_set.size() == 0) return;
	vNpcSet::iterator itp;
	if (Npc_set.size() > 0)
	{
		itp = Npc_set.begin();
		for (; itp != Npc_set.end();)
		{

			/*(*itp)->updatePosition((*itp)->GetDir(), t_scene.getBarrier());
			(*itp)->Gravityefect(t_scene.getBarrier());*/
			bool isPicked = player->CollideWith(*itp);
			if (isPicked)
			{
				player->damage();
				if (player->getStaStus() == PLAYER_SMALL) xinxi.setLife(-1);
				/*
				//删除场景中的对象	
				SCENE_LAYERS::iterator p;
				for (p = t_scene.getSceneLayers()->begin();
					p != t_scene.getSceneLayers()->end(); p++)
				{
					if ((*p).layer == (*itp))
					{
						p = t_scene.getSceneLayers()->erase(p);
						break;
					}
				}
				delete (*itp);
				itp = Npc_set.erase(itp);
				*/
			}

			if (itp == Npc_set.end())
			{
				break;
			}
			itp++;
		}
	}


}
void T_enginetest::SetMenuPara(wstring* menuItems, int itemSize, int m_w, int m_h, int posType)
{
	int y = 0, x = 0;
	for (int i = 0; i < itemSize; i++)
	{
		switch (posType)
		{
		case 0:
			x = (wndWidth - 296) - 100;
			y = i * (m_h + MENU_SPACE) + 150;
			break;
		case 1:
			x = i * (m_w + MENU_SPACE) + (wndWidth - 2 * m_w - MENU_SPACE) / 2;
			y = (wndHeight - m_h) / 2;
			break;
		case 2:
			x = i * (m_w + MENU_SPACE) + (wndWidth - m_w * itemSize - (itemSize - 1) * MENU_SPACE) / 2;
			y = wndHeight - 3 * m_h;
			break;
		}

		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];
		gameMenu->AddMenuItem(mItem);
	}

	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.space = MENU_SPACE;
	menuInfo.width = m_w;
	menuInfo.height = m_h;
	menuInfo.fontName = L"宋体";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = Color::White;
	menuInfo.focusTextColor = Color::Red;
	gameMenu->SetMenuInfo(menuInfo);
}
void T_enginetest::BombCollide(T_Sprite* bomb)
{
	if (bomb->IsActive() == true && bomb->IsVisible() == true)
	{
		// 如果碰到了地图障碍或遮罩
		T_Map* map = NULL;
		bool collideBarrier = bomb->CollideWith(t_scene.getBarrier());
		if (collideBarrier)
		{
			if (collideBarrier) map = t_scene.getBarrier();
			map->getTile(bomb->GetMapBlockPT().x, bomb->GetMapBlockPT().y);
			//map->setTile(bomb->GetMapBlockPT().x, bomb->GetMapBlockPT().y, );
			bomb->SetVisible(false);
			bomb->SetActive(false);
			bomb->SetVisible(false);
			bomb->SetActive(false);
			int x = bomb->GetX() - 8;
			int y = bomb->GetY() - 8;
			LoadExplosion(x, y);
			music.blast_buffer.Restore();
			music.blast_buffer.Play(false);
			
		}
		
		// 如果玩家炮弹碰到了NPC
		if (bomb->GetLayerTypeID() == LAYER_PLY_BOMB)
		{
			for (vNpcSet::iterator sp = Npc_set.begin(); sp != Npc_set.end(); sp++)
			{
				if (bomb->CollideWith((*sp)) && !((*sp)->IsDead()) &&
					((*sp)->IsVisible()) && ((*sp)->IsActive()))
				{
					(*sp)->SetActive(false);
					(*sp)->SetVisible(false);
					(*sp)->SetDead(true);
					bomb->SetActive(false);
					bomb->SetVisible(false);
					//NPC数目更新
					xinxi.updateScore(10);
					LoadExplosion((*sp)->GetX(), (*sp)->GetY());
				}

			}
		}
	}
}
void T_enginetest::GameInit()
{
	GameState = GAME_START;
	//xinxi.init();                                        //信息类初始化
	//xinxi.setlevel(0);
	//GameState = GAME_WIN;

	//加载游戏地图
	//LoadMap();

	//
	//LoadPlayer();


	//加载初始页面按钮
	LoadGameMenu(GameState);
	music.initResourse(m_hWnd);
	isfold = true;
	pause = false;
		
}
void T_enginetest::GameLogic()
{   
	
		frame = (frame + 1) % 24;
		

		if(GameState == GAME_RUN)
		{ 
			if (isfold==false)
			{
				gameMenu->SetClickSound(&(music.mousedown_buffer));
				gameMenu->SetMoveSound(&(music.mousedown_buffer));
			}
			else
			{
				gameMenu->SetClickSound(NULL);
				gameMenu->SetMoveSound(NULL);
			}
			if (!pause)
			{
				UpdatePlayerPos();                //移动玩家角色
		
				updateMushRoom(Mushroom);                      //更新蘑菇状态
				UpdateBombPos(player_bomb_set);                       //更新子弹位置
				UpdateNpcPos(Npc_set);                        //更新NPC位置

		
				xinxi.updatetime();                     //进行游戏信息的更新


				UpdateAnimation();                 //更新动画的
			}
		
			if (xinxi.getTime() <= 0)
			{
				xinxi.setLife(-1);

				//GameState = GAME_LOSE;
				if (xinxi.getLife() == 0)
				{
					delete player;
					player = NULL;
					music.setlose(true);
					GameState = GAME_OVER;

				}
				else {
					music.setlose(true);
				}
			}
		    if (player->GetY() >= 680)
			{
				xinxi.setLife(-1);
				player->StatusChange(PLAYER_SMALL);
				if (xinxi.getLife() == 0)
				{
					player->SetActive(true);
					player->SetPosition(30, wnd_height - 300 - player->GetRatioSize().cy);
					player->setFalling(false);
					GameState = GAME_OVER;

				}
				else
				{
					music.setlose(true);
					player->SetActive(true);
					player->SetPosition(30, wnd_height - 300 - player->GetRatioSize().cy);
					player->setFalling(false);
				}
			}
			if (keyaction1 != NULL)
			{
				music.playmusic(GameState, T_Engine::keyaction1,isfold);
				keyaction1 = NULL;
				music.isboom = false;
			}
			if (player->CollideWith(flag))
			{
				GameState = GAME_NEXT;

			}
		}
		else if (GameState == GAME_ONLINE)
		{
			if (isfold==false)
			{
				gameMenu->SetClickSound(&(music.mousedown_buffer));
				gameMenu->SetMoveSound(&(music.mousedown_buffer));
			}
			else
			{
				gameMenu->SetClickSound(NULL);
				gameMenu->SetMoveSound(NULL);
			}
			if (!pause)
			{
				UpdatePlayerPos();                //移动玩家角色

				/*
				updateMushRoom(Mushroom);                      //更新蘑菇状态
				UpdateBombPos(player_bomb_set);                       //更新子弹位置
				UpdateNpcPos(Npc_set);                        //更新NPC位置

				*/
				xinxi.updatetime();                     //进行游戏信息的更新

				
				UpdateAnimation();                 //更新动画的
			}

			if (xinxi.getTime() <= 0)
			{
				xinxi.setLife(-1);

				//GameState = GAME_LOSE;
				if (xinxi.getLife() == 0)
				{
					delete player;
					player = NULL;
					music.setlose(true);
					GameState = GAME_OVER;

				}
				else {
					music.setlose(true);
				}
			}
			if (player->GetY() >= 680)
			{
				xinxi.setLife(-1);
				player->StatusChange(PLAYER_SMALL);
				if (xinxi.getLife() == 0)
				{
					player->SetActive(true);
					player->SetPosition(30, wnd_height - 300 - player->GetRatioSize().cy);
					player->setFalling(false);
					GameState = GAME_OVER;

				}
				else
				{
					music.setlose(true);
					player->SetActive(true);
					player->SetPosition(30, wnd_height - 300 - player->GetRatioSize().cy);
					player->setFalling(false);
				}
			}
			if (keyaction1 != NULL)
			{
				music.playmusic(GameState, T_Engine::keyaction1, isfold);
				keyaction1 = NULL;
				music.isboom = false;
			}
			if (player->CollideWith(flag))
			{
				GameState = GAME_NEXT;

			}

		//CheckClear();                                    //更新关卡
		}
		else if (GameState == GAME_NEXT) {

			//music.setNext(true);

			music.playmusic(GameState, T_Engine::keyaction1,isfold);
			xinxi.updateLevel();
			xinxi.setTime();
			ClearGameLevel();
			LoadGamelevel(xinxi.getlevel());


			//
			if ((xinxi.getlevel()) >= 3) {
				GameState = GAME_WIN;
				LoadGameMenu(GameState);
			}
			else {

				GameState = GAME_RUN;
			}

		}
		else if (GameState == GAME_OVER) {
			LoadGameMenu(GameState);
		}
		music.playmusic(GameState, T_Engine::keyaction1, isfold);            //音乐播放 
		GameKeyAction();
}
void T_enginetest::GamePaint(HDC hdc)
{
	Gdiplus::RectF button;
	Gdiplus::RectF rect;
	int FontHeight = 0;
	switch(GameState)
	{
	case GAME_RUN:
		t_scene.Draw(hdc, 0, 0);



		button.X = 980;
		button.Y = 0;
		button.Width = 44;
		button.Height = 50;
		FontHeight = 10;
		Clik.PaintText(hdc, button, L"菜单", (REAL)FontHeight,
			L"黑体", Color(255, 255, 255, 0),
			FontStyleBold, StringAlignmentNear);

		if (isfold == false)
		{
			if (pause)
			{
				PauseRegion.PaintBlank(hdc, 0, 0, 1024, 768, Color::DarkGray, 125);
			}
			if (gameMenu != NULL)
			{

				gameMenu->DrawMenu(hdc);
			}

		}
		else
		{

		}
		break;
	case GAME_ABOUT:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	case GAME_MULTI:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
			rect.X = 220.00;
			rect.Y = 360.00;
			rect.Width = 200;
			rect.Height = 40;
			FontHeight = 20;
			T_Graph::PaintText(hdc, rect, L"账号", (REAL)FontHeight,
				L"黑体", Color(255, 255, 255, 255),
				FontStyleBold, StringAlignmentNear);

			rect.X = 220.00;
			rect.Y = 460.00;
			rect.Width = 200;
			rect.Height = 40;

			T_Graph::PaintText(hdc, rect, L"密码", (REAL)FontHeight,
				L"黑体", Color(255, 255, 255, 255),
				FontStyleBold, StringAlignmentNear);

			//	UpdateWindow(UserMenu);
			//	UpdateWindow(PwdMenu);
		break;
	case GAME_START:
		if (gameMenu != NULL) gameMenu->DrawMenu(hdc);
		break;
	case GAME_ONLINE:
		t_scene.Draw(hdc, 0, 0);
		button.X = 980;
		button.Y = 0;
		button.Width = 44;
		button.Height = 50;
		FontHeight = 10;
		Clik.PaintText(hdc, button, L"菜单", (REAL)FontHeight,
			L"黑体", Color(255, 255, 255, 0),
			FontStyleBold, StringAlignmentNear);

		if (isfold == false)
		{
			if (pause)
			{
				PauseRegion.PaintBlank(hdc, 0, 0, 1024, 768, Color::DarkGray, 125);
			}
			if (gameMenu != NULL)
			{

				gameMenu->DrawMenu(hdc);
			}

		}
		else{}
		break;
	case GAME_OVER:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	case GAME_LOSE:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	case GAME_NEXT:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	case GAME_PAUSE:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	case GAME_WIN:
		if (&t_scene != NULL && gameMenu != NULL)
		{
			gameMenu->DrawMenu(hdc);
		}
		break;
	default:
		break;
	}
	
	/*
	if (GameState != GAME_RUN)
	{
		
		if (GameState == GAME_START)
		{   
	
			if (gameMenu != NULL)
				gameMenu->DrawMenu(hdc);
			
		}
		else
		{
			if (&t_scene != NULL && gameMenu != NULL)
			{
				gameMenu->DrawMenu(hdc);
			}
			if (GameState == GAME_MULTI)
			{
				Gdiplus::RectF rect;
				rect.X = 220.00;
				rect.Y = 360.00;
				rect.Width = 200;
				rect.Height = 40;
				int FontHeight = 20;
				T_Graph::PaintText(hdc, rect, L"账号", (REAL)FontHeight,
					L"黑体", Color(255, 255, 255, 255),
					FontStyleBold, StringAlignmentNear);

				rect.X = 220.00;
				rect.Y = 460.00;
				rect.Width = 200;
				rect.Height = 40;

				T_Graph::PaintText(hdc, rect, L"密码", (REAL)FontHeight,
					L"黑体", Color(255, 255, 255, 255),
					FontStyleBold, StringAlignmentNear);

				//	UpdateWindow(UserMenu);
				//	UpdateWindow(PwdMenu);
			}
			if (GameState == GAME_ONLINE)
			{
				t_scene.Draw(hdc, 0, 0);

				Gdiplus::RectF button;

				button.X = 980;
				button.Y = 0;
				button.Width = 44;
				button.Height = 50;
				int FontHeight = 10;
				Clik.PaintText(hdc, button, L"菜单", (REAL)FontHeight,
					L"黑体", Color(255, 255, 255, 0),
					FontStyleBold, StringAlignmentNear);

				if (isfold == false)
				{
					if (pause)
					{
						PauseRegion.PaintBlank(hdc, 0, 0, 1024, 768, Color::DarkGray, 125);
					}
					if (gameMenu != NULL)
					{

						gameMenu->DrawMenu(hdc);
					}

				}
				else
				{

				}
			}
			
			
		}
	}
	else if(GameState== GAME_RUN)
	{

		t_scene.Draw(hdc, 0, 0);
		
		Gdiplus::RectF button;

		button.X =980 ;
		button.Y = 0;
		button.Width = 44;
		button.Height = 50;
		int FontHeight = 10;
		Clik.PaintText(hdc, button, L"菜单", (REAL)FontHeight,
			L"黑体", Color(255, 255, 255, 0),
			FontStyleBold, StringAlignmentNear);
		
		if (isfold == false)
		{
			if (pause)
			{
				PauseRegion.PaintBlank(hdc, 0, 0, 1024, 768, Color::DarkGray, 125);
			}
			if (gameMenu != NULL)
			{
				
				gameMenu->DrawMenu(hdc);
			}
			
		}
		else 
		{
			
		}
		
		
	}
	
	//if (GameState == GAME_OVER) {
		//gameMenu->DrawMenu(hdc);
	//}
	//information  xinxi;
	*/

	xinxi.DisplayInfo(hdc, GameState);

	//DisplayInfo(hdc, GameState);
}
void T_enginetest::GameKeyAction(int ActionType)
{


	//---------- 马里奥人物控制
	if (ActionType == KEY_SYS_NONE )
	{
			if (GameState == GAME_RUN)
			{

				if (CheckKey(VK_A))
				{
					player->SetActive(true);
					player->SetDir(DIR_LEFT);
					player->setFalling(false);

				}
				if (CheckKey(VK_D))
				{
					player->SetActive(true);
					player->setFalling(false);
					player->SetDir(DIR_RIGHT);
					//robot_buffer.Restore();
					//robot_buffer.Play(false);
					//t_music.StopAll();
					//t_music.setMediaName(".\\sound\\robot.wav");
					//t_music.Play(false);
				}
				if (CheckKey(VK_SPACE))
				{
					if (player->getJumping() == false)
					{
						player->SetDir(DIR_UP);
						player->SetActive(true);
						player->setJumping(true);
						player->setJumpSpeed(-16);
						player->SetSequence(Mario::FRAME_JUMP, 1);
					}

				}
				if (GetAsyncKeyState(VK_J) < 0)
				{
					if (player->IsDead() == false && player->IsVisible() == true)
					{
						if (player->getStaStus() == PLAYER_BIG)
						{
							LoadBomb(player, player_bomb_set, 400);
						}
					}
				}
				if (GetAsyncKeyState(VK_J) >= 0 && !CheckKey(VK_SPACE) && !CheckKey(VK_D) && !CheckKey(VK_A))
				{
					//无按键
					if (player->getJumping() == false)
					{
						player->SetActive(false);
						player->SetFrame(0);
					}
				}
			}
			if (GameState == GAME_ONLINE)
			{
				if (CheckKey(VK_A))
				{
					player->SetActive(true);
					player->SetDir(DIR_LEFT);
					player->setFalling(false);

				}
				if (CheckKey(VK_D))
				{
					player->SetActive(true);
					player->setFalling(false);
					player->SetDir(DIR_RIGHT);
					//robot_buffer.Restore();
					//robot_buffer.Play(false);
					//t_music.StopAll();
					//t_music.setMediaName(".\\sound\\robot.wav");
					//t_music.Play(false);
				}
				if (CheckKey(VK_SPACE))
				{
					if (player->getJumping() == false)
					{
						player->SetDir(DIR_UP);
						player->SetActive(true);
						player->setJumping(true);
						player->setJumpSpeed(-16);
						player->SetSequence(Mario::FRAME_JUMP, 1);
					}

				}
				if (GetAsyncKeyState(VK_J) < 0)
				{
					if (player->IsDead() == false && player->IsVisible() == true)
					{
						if (player->getStaStus() == PLAYER_BIG)
						{
							LoadBomb(player, player_bomb_set, 400);
						}
					}
				}
				if (GetAsyncKeyState(VK_J) >= 0 && !CheckKey(VK_SPACE) && !CheckKey(VK_D) && !CheckKey(VK_A))
				{
					//无按键
					if (player->getJumping() == false)
					{
						player->SetActive(false);
						player->SetFrame(0);
					}
				}
			}
		
	}	
	
	if (ActionType == KEY_DOWN)
	{
		
		if (GameState != GAME_RUN)
		{
			if (GameState == GAME_START)
			{
				if (GetAsyncKeyState(VK_UP) < 0) gameMenu->MenuKeyDown(VK_UP);
				if (GetAsyncKeyState(VK_DOWN) < 0) gameMenu->MenuKeyDown(VK_DOWN);
			}
			if (GameState == GAME_MULTI || GameState == GAME_ABOUT || GameState == GAME_RUN)
			{
				if (GetAsyncKeyState(VK_LEFT) < 0) gameMenu->MenuKeyDown(VK_LEFT);
				if (GetAsyncKeyState(VK_RIGHT) < 0) gameMenu->MenuKeyDown(VK_RIGHT);
			}

			if (GetAsyncKeyState(VK_RETURN) < 0)
			{
				if (gameMenu->GetMenuIndex() >= 0)
				{
					if (GameState == GAME_START)
					{
						switch (gameMenu->GetMenuIndex())
						{
						case 0:
							GameState = GAME_RUN;
							gameMenu->DestroyAll();
							delete gameMenu;
							gameMenu = NULL;
							//xinxi.setTime();
							LoadGameMenu(GAME_RUN);
							break;
						case 1:
							GameState = GAME_MULTI;
							gameMenu->DestroyAll();
							delete gameMenu;
							gameMenu = NULL;
							LoadGameMenu(GAME_MULTI);
							break;
						case 2:
							GameState = GAME_ABOUT;
							gameMenu->DestroyAll();
							delete gameMenu;
							gameMenu = NULL;
							LoadGameMenu(GAME_ABOUT);
							break;
						case 3:
							SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
							break;
						}
					}

					if (GameState == GAME_ABOUT || GameState == GAME_MULTI ||GameState == GAME_OVER)
					{
						switch (gameMenu->GetMenuIndex())
						{
						case 0:
							GameState = GAME_START;
							gameMenu->DestroyAll();
							//xinxi.init();
							delete gameMenu;
							gameMenu = NULL;
							LoadGameMenu(GAME_START);
							break;
						case 1:
							SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
							break;
						}
					}
											
				}
			}
		}
		
		
	}
	
}
void T_enginetest::GameMouseAction(int x, int y, int ActionType)
{
	if (ActionType == MOUSE_MOVE)
	{
		if (gameMenu != NULL && GameState != GAME_MULTI) gameMenu->MenuMouseMove(x, y);
		if (GameState == GAME_MULTI && gameMenu != NULL)
		{
			if (gameMenu->GetMenuIndex(x, y) != -1)
			{	
				SetSleep(false);
			}
			gameMenu->MenuMouseMove(x, y);
		}

	}
	if (ActionType == MOUSE_LCLICK)
	{	
		//初始菜单开始


		if (GameState == GAME_START)
		{
				int index = gameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (index)
					{
					case 0:
						t_scene.RemoveAll();
						delete gameMenu;
						//xinxi.setlevel(2);
						gameMenu = NULL;
						
						xinxi.init();
						xinxi.setlevel(0);
						LoadMap();
						LoadPlayer();
						//GameInit();
						GameState = GAME_RUN;
						LoadGameMenu(GAME_RUN);
						break;
					case 1:
						
						if (socket.TcpConnect())
						{
							
							t_scene.RemoveAll();
							delete gameMenu;
							gameMenu = NULL;
							GameState = GAME_MULTI;
							
							LoadGameMenu(GAME_MULTI);
							
							ShowWindow(UserMenu, SW_SHOWNORMAL);
							ShowWindow(PwdMenu, SW_SHOWNORMAL);
							SetFocus(m_hWnd);
						}
						else 
						{
							MessageBox(NULL, (LPCTSTR)TEXT("连接错误"), (LPCTSTR)TEXT("server"), MB_OK);
						}
						break;
					case 2:
						t_scene.RemoveAll();
						delete gameMenu;
						gameMenu = NULL;
						GameState = GAME_ABOUT;
						LoadGameMenu(GAME_ABOUT);
						break;
					case 3:
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						break;
					}
				}
			
		}
		else if (GameState == GAME_RUN)
		{
			RECT menuAreaRec{};
			menuAreaRec.left = 980;
			menuAreaRec.right = 1024;
			menuAreaRec.top = 0;
			menuAreaRec.bottom = 50;
			POINT mousePT{};
			mousePT.x = x;
			mousePT.y = y;
			if (isfold == false)
			{
				int index = gameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (index)
					{
					case 0:

						gameMenu->DestroyAll();
						delete gameMenu;
						gameMenu = NULL;
						GameState = GAME_START;
						LoadGameMenu(GAME_START);
						break;
					case 1:
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						break;
					}
				}
			}
			if (PtInRect(&menuAreaRec, mousePT))
			{
				isfold = false;
				pause = true;
				
			}
			else
			{
				isfold = true;
				pause = false;
			}

		}
		
		else if ( GameState == GAME_ABOUT || GameState == GAME_OVER )
		{
			int index = gameMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_START;
					gameMenu->DestroyAll();
					delete gameMenu;
					gameMenu = NULL;
					LoadGameMenu(GameState);
					

					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
		else if (GameState == GAME_MULTI) 
		{
			int ans = -1;
			string username, pwd;
			wchar_t *wname=new wchar_t(32);
			wchar_t *wpwd=new wchar_t(32);
			int leng;
			DWORD dwNum=0,dwNum1=0;
			char* psText=NULL;
			char* psText1=NULL;
			int index = gameMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:


					//获取用户名
					leng=SendMessage(UserMenu, WM_GETTEXT, 32, (LPARAM)wname);
					dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wname, -1, NULL, 0, NULL, FALSE);
					 // psText为char*的临时数组，作为赋值给std::string的中间变量
					psText = new char[dwNum];
					WideCharToMultiByte(CP_OEMCP, NULL, wname, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
					username = psText;
					psText=NULL;
					wname = NULL;

					//获取密码
					leng=SendMessage(PwdMenu, WM_GETTEXT, 32, (LPARAM)wpwd);
					dwNum1 = WideCharToMultiByte(CP_OEMCP, NULL, wpwd, -1, NULL, 0, NULL, FALSE);
					psText1 = new char[dwNum1];
					WideCharToMultiByte(CP_OEMCP, NULL, wpwd, -1, psText1, dwNum1, NULL, FALSE);// WideCharToMultiByte的再次运用
					pwd = psText1;
					psText1 = NULL;
					wpwd = NULL;
					
					if (socket.Login(username, pwd))
					{
						ans = socket.Enter();
						if (ans!=-1)
						{

							t_scene.RemoveAll();
							delete gameMenu;
							//xinxi.setlevel(2);
							gameMenu = NULL;

							xinxi.init();
							xinxi.setlevel(0);
							LoadOnLineMap();
							LoadPlayer();
							nextkeyframe = ans;
							GameState = GAME_ONLINE;
							LoadGameMenu(GAME_ONLINE);
							ShowWindow(UserMenu, SW_SHOWMINNOACTIVE);
							DestroyWindow(PwdMenu);
						}
						else
						{
							MessageBox(NULL, (LPCTSTR)TEXT("Server Failed"), (LPCTSTR)TEXT("Message"), MB_OK);
						}
					}
					else
					{
						MessageBox(NULL, (LPCTSTR)TEXT("Failed"), (LPCTSTR)TEXT("Message"), MB_OK);
					}

					
					break;
				case 1:
					//获取用户名
					leng = SendMessage(UserMenu, WM_GETTEXT, 32, (LPARAM)wname);
					dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wname, -1, NULL, 0, NULL, FALSE);
					// psText为char*的临时数组，作为赋值给std::string的中间变量
					psText = new char[dwNum];
					WideCharToMultiByte(CP_OEMCP, NULL, wname, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
					username = psText;
					psText = NULL;
					wname = NULL;

					//获取密码
					leng = SendMessage(PwdMenu, WM_GETTEXT, 32, (LPARAM)wpwd);
					dwNum1 = WideCharToMultiByte(CP_OEMCP, NULL, wpwd, -1, NULL, 0, NULL, FALSE);
					psText1 = new char[dwNum1];
					WideCharToMultiByte(CP_OEMCP, NULL, wpwd, -1, psText1, dwNum1, NULL, FALSE);// WideCharToMultiByte的再次运用
					pwd = psText1;
					psText1 = NULL;
					wpwd = NULL;

					if (socket.Register(username, pwd))
					{
						MessageBox(NULL, (LPCTSTR)TEXT("success"), (LPCTSTR)TEXT("Message"), MB_OK);

					}
					else
					{
						MessageBox(NULL, (LPCTSTR)socket.reason.c_str(), (LPCTSTR)TEXT("Message"), MB_OK);
					}

					//SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				case 2:
					GameState = GAME_START;
					gameMenu->DestroyAll();
					delete gameMenu;
					
					gameMenu = NULL;
					socket.CloseConnect();
					ShowWindow(UserMenu, SW_SHOWMINNOACTIVE);
					ShowWindow(PwdMenu, SW_SHOWMINNOACTIVE);
					LoadGameMenu(GameState);

					break;
				}
			}
		}
		else if (GameState == GAME_WIN)
		{
			int index = gameMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					t_scene.RemoveAll();
					gameMenu->DestroyAll();
					delete gameMenu;
					gameMenu = NULL;
					GameState = GAME_START;
					LoadGameMenu(GameState);
					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}

		}
		else if (GameState == GAME_ONLINE)
		{
			RECT menuAreaRec{};
			menuAreaRec.left = 980;
			menuAreaRec.right = 1024;
			menuAreaRec.top = 0;
			menuAreaRec.bottom = 50;
			POINT mousePT{};
			mousePT.x = x;
			mousePT.y = y;
			if (isfold == false)
			{
				int index = gameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (index)
					{
					case 0:

						gameMenu->DestroyAll();
						delete gameMenu;
						gameMenu = NULL;
						GameState = GAME_START;
						LoadGameMenu(GAME_START);
						break;
					case 1:
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						break;
					}
				}
			}
			if (PtInRect(&menuAreaRec, mousePT))
			{
				isfold = false;
				pause = true;
			}
			else
			{
				isfold = true;
				pause = false;
			}

		}
	}
}
void T_enginetest::GameEnd()
{
}

