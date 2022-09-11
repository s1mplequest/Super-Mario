//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 版权所有 2007-2013 万立中
// (C) 2007-2013 WanLizhong All Rights Reserved
//*******************************************************************

#include "Mymenu.h"

Mymenu::Mymenu()
{
	m_index = -1;
	key_index = 0;
	isItemFocused = false;
	//m_MoveSound = NULL;
	//m_ClickSound = NULL;

	bkImageAlpha = 255;
	bkColor = RGB(0, 0, 0);
}

Mymenu::~Mymenu(void)
{
	DestroyAll();
}

//void Mymenu::SetMoveSound(AudioDXBuffer* ms_buffer)
//{
//	m_MoveSound = ms_buffer;
//}
//
//void Mymenu::SetClickSound(AudioDXBuffer* mc_buffer)
//{
//	m_ClickSound = mc_buffer;
//}

//设置菜单背景图片
void Mymenu::SetMenuBkg(LPCTSTR img_path, int alphaLevel, COLORREF backColor)
{
	if (wcslen(img_path)>0)
	{
		gm_menuBkg.LoadImageFile(img_path);
		bkColor = backColor;
		bkImageAlpha = alphaLevel;
	}
}

//添加正常菜单图片
void Mymenu::SetBtnBmp(LPCTSTR img_path, int btnWidth, int btnHeight)
{
	if (wcslen(img_path)>0)
	{
		BtnDIB.LoadImageFile(img_path);
		if (&BtnDIB != NULL)
		{
			menu_info.width = btnWidth;
			menu_info.height = btnHeight;
		}
	}
}

//添加菜单文字项目
void Mymenu::AddMenuItem(MENUITEM menuItem)
{
	gm_menuItems.push_back(menuItem);
	int len = menuItem.ItemName.length();
	if (MaxMenuItemLen<len)
		MaxMenuItemLen = len;
}

//设置首菜单项的坐标及菜单间隔距离
void Mymenu::SetMenuInfo(MENU_INFO menuInfo)
{
	menu_info = menuInfo;
}

//菜单绘制
void Mymenu::DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans, bool startState)
{
	

	int w = menu_info.width;
	int h = menu_info.height;

	int FontHeight;
	int px = 0;
	int w_px = w / (MaxMenuItemLen + 1);	//计算每个字所占的像素
	int h_px = (int)((float)(h / 2.5));
	if (w_px > h_px)
	{
		px = h_px;
	}
	else
	{
		px = w_px;
	}
	FontHeight = (px * 72) / 96;		//根据每个字的像素计算字号

	if (isItemFocused == FALSE)
	{
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			// 绘制按钮图像
			if (&BtnDIB != NULL)
			{
				BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
			}
			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			// 绘制按钮文字
			LPCTSTR item = iter->ItemName.c_str();
			T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
				menu_info.normalTextColor, GetFontStyle(), GetAlignment());
		}
	}

	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			if (mIndex != m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
				}

				LPCTSTR item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.normalTextColor, GetFontStyle(), GetAlignment());
			}

			if (mIndex == m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnTrans);
				}

				LPCTSTR item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.focusTextColor, GetFontStyle(), GetAlignment());
			}

			mIndex = mIndex + 1;
		}
	}
}

//根据当前鼠标坐标计算菜单项索引号
int Mymenu::GetMenuIndex(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;
	int w = menu_info.width;
	int h = menu_info.height;
	RECT rec;

	int iCount = 0;
	vector<MENUITEM>::iterator iter;
	for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
	{
		rec.left = iter->pos.x;
		rec.top = iter->pos.y;
		rec.right = rec.left + w;
		rec.bottom = rec.top + h;

		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;
}

StringAlignment Mymenu::GetAlignment()
{
	StringAlignment sAlign;
	if (menu_info.align == 0)
	{
		sAlign = StringAlignmentNear;
	}
	if (menu_info.align == 1)
	{
		sAlign = StringAlignmentCenter;
	}
	if (menu_info.align == 2)
	{
		sAlign = StringAlignmentFar;
	}
	return sAlign;
}

FontStyle Mymenu::GetFontStyle()
{
	FontStyle fStyle;
	if (menu_info.isBold == true)
	{
		fStyle = FontStyleBold;
	}
	else
	{
		fStyle = FontStyleRegular;
	}
	return fStyle;
}

//菜单鼠标点击事件处理
int Mymenu::MenuMouseClick(int x, int y)
{
	m_index = GetMenuIndex(x, y);
	//if(m_index >= 0) 
	//{
	//	if(m_MoveSound && m_ClickSound)
	//	{
	//		m_MoveSound->Restore();
	//		m_ClickSound->Restore();
	//		m_ClickSound->Play(false);
	//	}
	//}
	return m_index;
}

//菜单鼠标移动事件处理
void Mymenu::MenuMouseMove(int x, int y)
{
	lastIndex = m_index;//记录前一次的索引值
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		isItemFocused = true;
		//保证鼠标移过按钮只播放一次声音
		//if(lastIndex != m_index) 
		//{
		//	if(m_MoveSound && m_ClickSound)
		//	{
		//		m_ClickSound->Restore();
		//		m_MoveSound->Restore();
		//		m_MoveSound->Play(false);
		//	}
		//}
	}
	else
	{
		isItemFocused = false;
	}
}

int Mymenu::MenuKeyDown(WPARAM key)
{
	if (key == VK_UP || key == VK_LEFT)
	{
		m_index = m_index - 1;
		if (m_index<0)
		{
			m_index = (int)(gm_menuItems.size() - 1);
		}

		isItemFocused = true;
		//if(m_MoveSound && m_ClickSound)
		//{
		//	m_ClickSound->Restore();
		//	m_MoveSound->Restore();
		//	m_MoveSound->Play(false);
		//}
	}
	if (key == VK_DOWN || key == VK_RIGHT)
	{
		m_index = m_index + 1;
		if (m_index>(int)(gm_menuItems.size() - 1))
		{
			m_index = 0;
		}

		isItemFocused = true;
		//if(m_MoveSound && m_ClickSound)
		//{
		//	m_ClickSound->Restore();
		//	m_MoveSound->Restore();
		//	m_MoveSound->Play(false);
		//}
	}
	return m_index;
}

void Mymenu::DestroyAll()
{
	gm_menuBkg.Destroy();
	BtnDIB.Destroy();
	gm_menuItems.clear();
	///使用swap,清除元素并回收内存
	//清除容器并最小化它的容量
	gm_menuItems.swap(vector<MENUITEM>());
}
