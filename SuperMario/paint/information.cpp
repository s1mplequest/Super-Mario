#include "information.h"
information::information() 
{
	if (npcNumImg == NULL)	npcNumImg = new T_Graph(L".\\res\\time.png");
	if (lifeImg == NULL)		lifeImg = new T_Graph(L".\\res\\samllmaliao.png");
	if (flagImg == NULL)		flagImg = new T_Graph(L".\\res\\flag.png");
	if (bmbImg == NULL)		bmbImg = new T_Graph(L".\\res\\diren.png");
	ChargeCount = PLAYER_CHARGE;
	LifeCount = PLAYER_LIFE;
	time = 400;
};
information::~information() {

};
void information::DisplayInfo(HDC hdc, int game_state) {

	int FontHeight = 0;//�ֺ�
	Gdiplus::RectF rect;
	int i = 0;
	int x = 25;
	int y = 12;
	int fy = 15;
	int iconW = 30;
	int textW = 150;
	int textH = 30;
	wstring Content = L"";
	wstring EnemyNum = L"";
	wstring lifeleft = L"";
	wstring ScoreNum = L"";
	wstring ChargeNum = L"";
	switch (game_state)
	{
		case GAME_START:
		{
			wchar_t* GameName = L"���������";
	


			rect.X = 50.00;
			rect.Y = 80.00;
			rect.Width = 768.00;
			rect.Height = 100.00;

			FontHeight = 32;//�ֺ�

			T_Graph::PaintText(hdc,rect, L"���������", (REAL)FontHeight, L"����",Color::Black, FontStyleBold, StringAlignmentNear);

		


		}
		break;
	
		case GAME_RUN:

			i = 0;
			x = 25;
			y = 12;
			fy = 15;
			iconW = 30;
			textW = 150;
			textH = 30;
			FontHeight = 18; // �ֺ�

						 //������Ϸ״̬��Ϣ
			if (GameLevel <= TOTAL_LEVEL)
			{
				npcNumImg->PaintRegion(
				npcNumImg->GetBmpHandle(), hdc, x, y, 0, 0,
				npcNumImg->GetImageWidth(), npcNumImg->GetImageHeight(), 1);
			
				x = x + iconW;
				EnemyNum = L"ʱ��: ";
				EnemyNum.append(T_Util::int_to_wstring(time));
				rect.X = (float)x;
				rect.Y = (float)fy;
				rect.Width = (float)textW;
				rect.Height = (float)textH;
				T_Graph::PaintText(hdc, rect, EnemyNum.c_str(), (REAL)FontHeight,L"����", Color(255, 255, 255, 0),FontStyleBold, StringAlignmentNear);

				x = x + textW;
				lifeImg->PaintRegion(
					lifeImg->GetBmpHandle(), hdc, x, y, 0, 0,
					lifeImg->GetImageWidth(), lifeImg->GetImageHeight(), 1);

				lifeleft = L"����: ";
				lifeleft.append(T_Util::int_to_wstring(LifeCount));
				x = x + iconW;
				rect.X = (float)x;
				rect.Y = (float)fy;
				rect.Width = (float)textW;
				rect.Height = (float)textH;
				T_Graph::PaintText(
				hdc, rect, lifeleft.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0),
				FontStyleBold, StringAlignmentNear);

				x = x + textW;
				bmbImg->PaintRegion(
					bmbImg->GetBmpHandle(), hdc, x, y, 0, 0,
					bmbImg->GetImageWidth(), bmbImg->GetImageHeight(), 1);

				wstring ChargeNum = L"����: ";
				ChargeNum.append(T_Util::int_to_wstring(score));
				x = x + iconW;
				rect.X = (float)x;
				rect.Y = (float)fy;
				rect.Width = (float)textW;
				rect.Height = (float)textH;
				T_Graph::PaintText(
					hdc, rect, ChargeNum.c_str(), (REAL)FontHeight,
					L"����", Color(255, 255, 255, 0), FontStyleBold, StringAlignmentNear);


				x = x + textW;
				flagImg->PaintRegion(
					flagImg->GetBmpHandle(), hdc, x, y, 0, 0,
					flagImg->GetImageWidth(), flagImg->GetImageHeight(), 1);


				ScoreNum = L"�ؿ�: ";
				ScoreNum.append(T_Util::int_to_wstring(GameLevel + 1));
				x = x + iconW;
				rect.X = (float)x;
				rect.Y = (float)fy;
				rect.Width = (float)textW;
				rect.Height = (float)textH;
				T_Graph::PaintText(hdc, rect, ScoreNum.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0), FontStyleBold, StringAlignmentNear);
			}
	break;
	case GAME_OVER:
		rect.X = 0.00;
		rect.Y = 0.00;
		rect.Width = float(WIN_WIDTH);
		rect.Height = float(WIN_HEIGHT / 2);
		FontHeight = 48;
		T_Graph::PaintText(hdc, rect, L"��Ϸ����!", (REAL)FontHeight, L"����");
		break;
	case GAME_WIN:
		rect.X = 0.00;
		rect.Y = 0.00;
		rect.Width = float(WIN_WIDTH);
		rect.Height = float(WIN_HEIGHT / 2);
		FontHeight = 48;
		T_Graph::PaintText(hdc, rect, L"��ϲͨ�أ�", (REAL)FontHeight, L"����");

		break;
	case GAME_MULTI:

		//
		rect.X = 70.00;
		rect.Y = 130.00;
		rect.Width = float(WIN_WIDTH - 120);
		rect.Height = 80;
		FontHeight = 40;
		T_Graph::PaintText(hdc, rect, L"������Ϸ", (REAL)FontHeight, L"����", Color::White, FontStyleRegular, StringAlignmentNear);

		rect.X = 60.00;
		rect.Y = 220.00;
		rect.Width = float(WIN_WIDTH - 120);
		rect.Height = WIN_HEIGHT - 450;
		FontHeight = 26;

		
		T_Graph::PaintText(
			hdc, rect, Content.c_str(), (REAL)FontHeight, L"����",
			Color::White, FontStyleRegular, StringAlignmentNear);
		break;
	case GAME_ABOUT:
		rect.X = 60.00;
		rect.Y = 130.00;
		rect.Width = float(WIN_WIDTH - 120);
		rect.Height = 80;
		FontHeight = 40;
		T_Graph::PaintText(hdc, rect, L"��  ��", (REAL)FontHeight, L"����", Color::White, FontStyleRegular, StringAlignmentNear);

		rect.X = 80.00;
		rect.Y = 180.00;
		rect.Width = float(WIN_WIDTH - 120);
		rect.Height = WIN_HEIGHT - 450;
		FontHeight = 18;
		Content = L"���������\n";
		Content.append(L"AD�ƶ��ո���Ծ��Ģ�������ӵ�\n");

		T_Graph::PaintText(
			hdc, rect, Content.c_str(), (REAL)FontHeight, L"����",
			Color::White, FontStyleRegular, StringAlignmentNear);
	case GAME_ONLINE:
		i = 0;
		x = 25;
		y = 12;
		fy = 15;
		iconW = 30;
		textW = 150;
		textH = 30;
		FontHeight = 18; // �ֺ�

						 //������Ϸ״̬��Ϣ
		if (GameLevel <= TOTAL_LEVEL)
		{
			npcNumImg->PaintRegion(
				npcNumImg->GetBmpHandle(), hdc, x, y, 0, 0,
				npcNumImg->GetImageWidth(), npcNumImg->GetImageHeight(), 1);

			x = x + iconW;
			EnemyNum = L"ʱ��: ";
			EnemyNum.append(T_Util::int_to_wstring(time));
			rect.X = (float)x;
			rect.Y = (float)fy;
			rect.Width = (float)textW;
			rect.Height = (float)textH;
			T_Graph::PaintText(hdc, rect, EnemyNum.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0),
				FontStyleBold, StringAlignmentNear);

			x = x + textW;
			lifeImg->PaintRegion(
				lifeImg->GetBmpHandle(), hdc, x, y, 0, 0,
				lifeImg->GetImageWidth(), lifeImg->GetImageHeight(), 1);

			lifeleft = L"����: ";
			lifeleft.append(T_Util::int_to_wstring(LifeCount));
			x = x + iconW;
			rect.X = (float)x;
			rect.Y = (float)fy;
			rect.Width = (float)textW;
			rect.Height = (float)textH;
			T_Graph::PaintText(
				hdc, rect, lifeleft.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0),
				FontStyleBold, StringAlignmentNear);

			x = x + textW;
			bmbImg->PaintRegion(
				bmbImg->GetBmpHandle(), hdc, x, y, 0, 0,
				bmbImg->GetImageWidth(), bmbImg->GetImageHeight(), 1);

			ChargeNum = L"����: ";
			ChargeNum.append(T_Util::int_to_wstring(score));
			x = x + iconW;
			rect.X = (float)x;
			rect.Y = (float)fy;
			rect.Width = (float)textW;
			rect.Height = (float)textH;
			T_Graph::PaintText(
				hdc, rect, ChargeNum.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0), FontStyleBold, StringAlignmentNear);


			x = x + textW;
			flagImg->PaintRegion(
				flagImg->GetBmpHandle(), hdc, x, y, 0, 0,
				flagImg->GetImageWidth(), flagImg->GetImageHeight(), 1);


			ScoreNum = L"�ؿ�: ";
			ScoreNum.append(T_Util::int_to_wstring(GameLevel + 1));
			x = x + iconW;
			rect.X = (float)x;
			rect.Y = (float)fy;
			rect.Width = (float)textW;
			rect.Height = (float)textH;
			T_Graph::PaintText(hdc, rect, ScoreNum.c_str(), (REAL)FontHeight,
				L"����", Color(255, 255, 255, 0), FontStyleBold, StringAlignmentNear);
		}
		break;
	default:
		break;
		
	}
};
//void information::updateLevel() {
	//GameLevel = GameLevel + 1;
//}
void information::init() {

	LifeCount = PLAYER_LIFE;
	time = 400;
	GameLevel =0;
	score = 0;

}
void information::updateBobm()
{
	ChargeCount = ChargeCount - 1;
};
int information::getBombNum()
{ 
	return ChargeCount;
};
void information::updatetime() 
{
	
	;
	if (GetTickCount()-startTime>=T_LENGTH) {
		startTime = GetTickCount();
		time = time - 1;
		
	}
	
};
int information::getTime() {
	return time;
};
void information::updateLevel()
{
	GameLevel++;
}