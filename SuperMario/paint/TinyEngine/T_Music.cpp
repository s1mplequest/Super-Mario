//*******************************************************************
// WinEngine2017(�򻯰�)  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2017-06-21
// ����: 2020-12-20
// ��Ȩ���� 2007-2021 ������
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Music.h"

string T_Music::ALIAS_NAME = "MD";

T_Music::T_Music()
{
	isOpen = false;
	setMediaName("alarm_tone.mp3");
	getUniqueAlias();
}

T_Music::T_Music(string mediaName)
{
	isOpen = false;
	setMediaName(mediaName);
	getUniqueAlias();
}

void T_Music::getUniqueAlias()
{
	long val = GetTickCount();
	string val_string;
	stringstream buf;
	buf << val;
	val_string = buf.str();
	ALIAS_NAME = ALIAS_NAME+val_string;
}

//������Ϣ��MCI  
bool T_Music::SendMciCmd(string cmd)
{  
	if(!mciSendString(StringToWString(cmd).c_str(), NULL, 0, 0)) 
	{
		return true;  
	}
	return false;  
}  

//��MCI��ȡ��Ϣ  
string T_Music::GetMciStatus(string cmd)
{  
	 wchar_t message[20];  
	mciSendString(StringToWString(cmd).c_str(), message,20,0);
	string str;  
	Wchar_tToString(str, message);
	return str;  
}  

void T_Music::ClosePlayer()
{
	if (isOpen)
	{
		close_cmd ="CLOSE " + ALIAS_NAME;  
		SendMciCmd(close_cmd);
		isOpen = false;
	}
}


void T_Music::OpenMediaFile()
{
	ClosePlayer();
	
	open_cmd="OPEN " + mediaName + " TYPE MPEGVideo ALIAS " + ALIAS_NAME;  
	SendMciCmd(open_cmd);

	isOpen = true;
}

void T_Music::PlayMediaFile(bool loop)
{
	if(isOpen)
	{
		if(loop == false)
		{
			play_cmd="PLAY " + ALIAS_NAME + " FROM 0";
			SendMciCmd(play_cmd);
		}
		else
		{
			loop_play_cmd="PLAY " + ALIAS_NAME + " REPEAT"; 
			SendMciCmd(loop_play_cmd);
		}
	}
}

void T_Music::Play(bool loop)
{
	OpenMediaFile();
	PlayMediaFile(loop);
}

void T_Music::Stop()
{
	ClosePlayer();
}

void T_Music::StopAll()
{
	close_cmd ="CLOSE ALL";  
	SendMciCmd(close_cmd);
}

bool T_Music::isStopped()
{
	string result="";
	status_cmd="status " + ALIAS_NAME + " mode";
	result=GetMciStatus(status_cmd);  //��ȡ����״̬  
	if(result == "stopped")  
	{
		return true;
	}
	return false;
} 

wstring T_Music::StringToWString(const string & s)
{
	std::wstring wszStr;

	int nLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, NULL);
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength);
	wszStr = lpwszStr;
	delete[] lpwszStr;

	return wszStr;
}
void T_Music::Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte������
	char *psText;  // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete[]psText;// psText�����
}
