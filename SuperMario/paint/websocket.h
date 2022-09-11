#pragma once

#include <string>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include <WS2tcpip.h>

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


using namespace std;
#define BUF_SIZE 1024

class websocket
{
private:

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;
	const string separtor="\r\n";
	const string cmd_separtor = ",";
	string process_buff(string readbuff);
	vector<string> str_unpack(string msgstr);
	string str_pack(vector<string> msglists);
	string process_msg(string msgstr);
	bool CheckMsg(string msg);

public:

	
	websocket();
	~websocket();
	int Send();
	int Recv();


	void CloseConnect();
	bool TcpConnect();

	bool Login(string username,string pwd);
	bool Register(string username,string pwd);
	int Enter();
	bool Leave();
	string reason;


};