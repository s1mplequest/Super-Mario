//*******************************************************************
// WinEngine2017(简化版)  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2017-06-21
// 更新: 2020-12-20
// 版权所有 2007-2021 万立中
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#ifndef _T_MUSIC_H
#define _T_MUSIC_H

#include "T_Util.h"
#pragma comment(lib,"winmm.lib") 

class T_Music
{
private:
	bool isOpen;
	string mediaName;
	string open_cmd;  
	string status_cmd;  
	string play_cmd;  
	string loop_play_cmd;
	string close_cmd;  
	static string ALIAS_NAME;

	void getUniqueAlias();

	bool SendMciCmd(string cmd);
	string GetMciStatus(string cmd);

	void ClosePlayer();
	void OpenMediaFile();
	void PlayMediaFile(bool loop = false);

	wstring  StringToWString(const string& s);
	void Wchar_tToString(std::string& szDst, wchar_t *wchar);

public:
	T_Music();
	T_Music(string mediaName);

	~T_Music(){};

	void setMediaName(string mediaName){this->mediaName = mediaName; }
	bool isStopped();
	void Play(bool loop = false);
	void Stop();
	void StopAll();
};

#endif

