#include"websocket.h"
#include <string>
websocket::websocket()
{
	hSocket = 0;
}
websocket::~websocket()
{
	closesocket(hSocket);
	WSACleanup();
}
bool websocket::TcpConnect()

{	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;
	//SOCKET
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) return false;

	/*初始化结构体*/
	memset(&servAdr,0,sizeof(servAdr));
	
	inet_pton(AF_INET, "47.94.142.251", &servAdr.sin_addr);
	servAdr.sin_port = htons(8001);
	servAdr.sin_family = AF_INET;

	if (connect(hSocket,(SOCKADDR*)&servAdr,sizeof(servAdr)) == SOCKET_ERROR) { return false; }
	return true;

}
void websocket::CloseConnect()
{
	closesocket(hSocket);
	WSACleanup();
}
string websocket::process_msg(string msgstr)
{
	vector<string> cmd = str_unpack(msgstr);
	return cmd[1];
}
string websocket::str_pack(vector<string> msglists)
{
	string cmd;
	for (int i = 0; i < msglists.size(); i++)
	{
		cmd.append(msglists[i]);
		if (i < msglists.size() - 1)
		{
			cmd += ',';
		}
	}
	cmd += '\r';
	cmd += '\n';
	return cmd;
}
vector<string> websocket::str_unpack(string msgstr)
{
	vector<string> msglist;
	int pos=msgstr.find(',');
	while (pos!= -1)
	{
		msglist.push_back(msgstr.substr(0, pos));
		msgstr = msgstr.substr(pos+1, msgstr.length()-1);
		pos = msgstr.find(',');
	}
	msglist.push_back(msgstr);
	return msglist;
}
string websocket::process_buff(string readbuff)
{
	while (true)
	{
		int pos = readbuff.find(separtor);
		if (pos == -1)
		{
			return readbuff;
		}
		else
		{
			string msg = readbuff.substr(0, pos);
			readbuff = readbuff.substr(pos + 2, readbuff.length() - pos - 2);
			process_msg(msg);
		}
	}
}
bool websocket::Login(string username, string pwd)
{
	vector<string> msg;
	string login = "login";
	msg.push_back(login);
	msg.push_back(username);
	msg.push_back(pwd);
	
	string cmd = str_pack(msg);


	send(hSocket, cmd.c_str(), cmd.length(), 0);
	char* recv_buf = new char[100];
	int i=0,leng=0;
	string msgs;

	Sleep(100);
	leng = recv(hSocket, recv_buf, 100, 0);
	while (i < leng)
	{
		msgs+=*(recv_buf+i);
		i++;
	}
	vector<string> info(str_unpack(msgs));
	
	if (info[1].compare("1")==0)
	{
		return true;
	}
	else
	{	
		reason = info[2];
	}
	
	return false;
}
bool websocket::Register(string username,string pwd)
{
	vector<string> msg;
	string login = "register";
	msg.push_back(login);
	msg.push_back(username);
	msg.push_back(pwd);

	string cmd = str_pack(msg);


	send(hSocket, cmd.c_str(), cmd.length(), 0);
	char* recv_buf = new char[100];
	int i = 0, leng = 0;
	string msgs;

	Sleep(100);
	leng = recv(hSocket, recv_buf, 100, 0);
	while (i < leng)
	{
		msgs += *(recv_buf + i);
		i++;
	}
	vector<string> info(str_unpack(msgs));

	if (info[1].compare("1") == 0)
	{
		return true;
	}
	else
	{
		reason = info[2];
	}

	return false;
}
bool websocket::CheckMsg(string Msg)
{
	int  flag = Msg.find("\r\n");
	if (flag !=-1)
	{
		return true;
	}
	else
	{
		return false;
	}

}
int websocket::Enter()
{
	int ans = -1;
	string cmd = "enter";
	cmd.append("\r\n");
	send(hSocket, cmd.c_str(), cmd.length(), 0);
	char* recv_buf = new char[100];
	int i = 0, leng = 0;
	string msgs;

	Sleep(100);
	leng = recv(hSocket, recv_buf, 100, 0);
	while (i < leng)
	{
		msgs += *(recv_buf + i);
		i++;
	}
	vector<string> info(str_unpack(msgs));

	if (info[1].compare("0") == 0)
	{
		ans = atoi(info[2].c_str());
	}
	else
	{
		ans = -1;
	}

	return ans;
}
bool websocket::Leave()
{
	string cmd = "leave";
	cmd.append("\r\n");
	send(hSocket, cmd.c_str(), cmd.length(), 0);
	char* recv_buf = new char[100];
	int i = 0, leng = 0;
	string msgs;

	Sleep(100);
	leng = recv(hSocket, recv_buf, 100, 0);
	while (i < leng)
	{
		msgs += *(recv_buf + i);
		i++;
	}
	vector<string> info(str_unpack(msgs));

	if (info[1].compare("1") == 0)
	{
		return true;
	}
	else
	{
		reason = info[2];
	}

	return false;
}
