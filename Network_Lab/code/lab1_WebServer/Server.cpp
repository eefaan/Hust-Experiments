#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "Server.h"
#include "WinsockEnv.h"
#include "Config.h"
#include <winsock2.h>
#include <algorithm>
#pragma comment(lib, "Ws2_32.lib")

#include "ChatRoomClientGUI.h"
#include "ChatRoomClientGUIDlg.h"
#pragma warning(disable:4996)

Server::Server(void)
{
	this->recvBuf = new char[Config::BUFFERLENGTH]; //��ʼ�����ܻ�����
	memset(this->recvBuf, '\0', Config::BUFFERLENGTH);
}

Server::Server(string home)
{
	this->homeAddr = home;
	this->recvBuf = new char[Config::BUFFERLENGTH]; //��ʼ�����ܻ�����
	memset(this->recvBuf, '\0', Config::BUFFERLENGTH);
}

Server::~Server(void)
{
	//�ͷŽ��ܻ�����
	if (this->recvBuf != NULL) {
		delete this->recvBuf;
		this->recvBuf = NULL;
	}

	//�ر�server socket
	if (this->srvSocket != NULL) {
		closesocket(this->srvSocket);
		this->srvSocket = NULL;
	}

	WSACleanup(); //����winsock ���л���
}

//��ʼ��Winsock
int Server::WinsockStartup() {
	if (WinsockEnv::Startup() == -1) return -1;	//��ʼ��Winsock
	return 0;
}

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup() {
	//���� TCP socket
	this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->srvSocket == INVALID_SOCKET) {
		cout << "Server socket creare error !\n";
		WSACleanup();
		return -1;
	}
	cout << "Server socket create ok!\n";

	//���÷�����IP��ַ�Ͷ˿ں�
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port = htons(Config::PORT);
	this->srvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���Զ��ҵ����������ʵ�IP��ַ
//	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(Config::SERVERADDRESS.c_str()); //��������һ������IP��ַ�ķ���

	//�� socket to Server's IP and port
	int rtn = bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
	if (rtn == SOCKET_ERROR) {
		cout << "Server socket bind error!\n";
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	cout << "Server socket bind ok!\n";
	return 0;
}

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup(string str_ip, int port) {
	CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	//���� TCP socket
	this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->srvSocket == INVALID_SOCKET) {
		cout << "Server socket creare error !\n";
		string msg_e1("Server socket creare error !\n");
		dlg->m_List.AddString(CString(msg_e1.c_str()));
		WSACleanup();
		return -1;
	}
	cout << "Server socket create ok!\n";
	string msg_o1("Server socket create ok!\n");
	dlg->m_List.AddString(CString(msg_o1.c_str()));

	//���÷�����IP��ַ�Ͷ˿ں�
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port = htons(port);
	// this->srvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���Զ��ҵ����������ʵ�IP��ַ
	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(str_ip.c_str()); //��������һ������IP��ַ�ķ���

	//�� socket to Server's IP and port
	int rtn = bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
	if (rtn == SOCKET_ERROR) {
		cout << "Server socket bind error!\n";
		string msg_e2("Server socket bind error!\n");
		dlg->m_List.AddString(CString(msg_e2.c_str()));
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	cout << "Server socket bind ok!\n";
	string msg_o2("Server socket bind ok!\n");
	dlg->m_List.AddString(CString(msg_o2.c_str()));
	return 0;
}

//��ʼ����,�ȴ��ͻ�����������
int Server::ListenStartup() {
	CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
	if (rtn == SOCKET_ERROR) {
		cout << "Server socket listen error!\n";
		string msg_e("Server socket listen error!\n");
		dlg->m_List.AddString(CString(msg_e.c_str()));
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	cout << "Server socket listen ok!\n";
	string msg_o("Server socket listen ok!\n");
	dlg->m_List.AddString(CString(msg_o.c_str()));
	return 0;
}

//��SOCKET s������Ϣ
void Server::sendMessage(SOCKET socket, string msg) {
	// cout<<(this->numOfSocketSignaled);
	int rtn = send(socket, msg.c_str(), msg.length(), 0);
	if (rtn == SOCKET_ERROR) {//�������ݴ���
		cout << "Send to client failed!" << endl;
	}
}

int Server::AcceptRequestionFromClient() {
	sockaddr_in clientAddr;		//�ͻ���IP��ַ
	int nAddrLen = sizeof(clientAddr);
	u_long blockMode = Config::BLOCKMODE;//��session socket��Ϊ������ģʽ�Լ����ͻ���������
	u_long n_blockMode = 0;

	//���srvSocket�Ƿ��յ��û���������
	if (this->numOfSocketSignaled > 0) {
		if (FD_ISSET(this->srvSocket, &rfds)) {  //�пͻ�����������
			//�����Ựsocket
			SOCKET newSession = accept(this->srvSocket, (LPSOCKADDR)&(clientAddr), &nAddrLen);
			this->numOfSocketSignaled--;
			CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());

			if (newSession == INVALID_SOCKET) {
				cout << "Server accept connection request error!\n";
				string msg_e1("Server accept connection request error!\n");
				dlg->m_List.AddString(CString(msg_e1.c_str()));
				return -1;
			}

			//cout << "New client connection request arrived and new session created\n";

			//���µĻỰsocket��Ϊ������ģʽ��
			if (ioctlsocket(newSession, FIONBIO, &n_blockMode) == SOCKET_ERROR) {
				cout << "ioctlsocket() for new session failed with error!\n";
				string msg_e2("ioctlsocket() for new session failed with error!\n");
				dlg->m_List.AddString(CString(msg_e2.c_str()));
				return -1;
			}

			//client address
			cout << "\nrequest header from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port << " :\n";

			//recv request
			char m_recv[1000];				//���ܻ�����
			int receivedBytes = recv(newSession, m_recv, Config::BUFFERLENGTH, 0);
			int error_i = WSAGetLastError();
			cout<<error_i<<endl;
			// dlg->m_List.AddString(CString(to_string(error_i).c_str()));
			//�������ݴ��󣬰Ѳ�������ĻỰsocekt�����ɾ��
			if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {
				closesocket(newSession);
				return 1;
			}

			m_recv[receivedBytes] = '\0';
			string s(m_recv);
			cout << s;

			string msg_request("\nrequest header from " + string(inet_ntoa(clientAddr.sin_addr)) + ":" + to_string(clientAddr.sin_port) + " :\n" + s);
			dlg->m_List.AddString(CString(msg_request.c_str()));

			//new way to get file name
			string m_buf(m_recv);
			int x=0;
			int y=0;
			x = m_buf.find("GET ") + 4;
			y = m_buf.find(" HTTP") - 4;
			string request_filename(m_buf.substr(x, y));
			request_filename = this->homeAddr + request_filename;

			//read file
			ifstream in;
			in.open(request_filename, ios::in | ios::out | ios::binary);                 //�����Լ���Ҫ�����ʵ���ѡȡ
			if (!in) {
				cout << "do not exist this file: " << request_filename;
				string msg_file_e("do not exist this file: " + request_filename);
				dlg->m_List.AddString(CString(msg_file_e.c_str()));

				//send 404 not found
				string response_404("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: Keep-Alive\r\n\r\n<html><body>404 not found!</body></html>");
				this->sendMessage(newSession, response_404);
				closesocket(newSession);
				return 0;
			}
			else{
				//make response
				string resp_type("Content-Type: text/html\r\n");
				if (request_filename.find(".jpg") != string::npos || request_filename.find(".jpeg") != string::npos) {
					resp_type = "Content-type: image/jpg\r\n";
				}
				else if (request_filename.find(".pdf") != string::npos) {
					resp_type = "Content-type: application/pdf\r\n";
				}
				else if (request_filename.find(".mp4") != string::npos) {
					resp_type = "Content-type: video/mpeg4\r\n";
				}

				//response's body;
				string resp_body;
				int con_len = 0;
				if (in.is_open())
				{
					istreambuf_iterator<char> beg(in), end;
					resp_body = string(beg, end);
					con_len = resp_body.length();
				}
				string resp_length("Content-Length: " + to_string(con_len) + "\r\n");
				string response("HTTP/1.1 200 OK\r\n" + resp_type + "Connection: Keep-Alive\r\n\r\n" + resp_body);

				this->sendMessage(newSession, response);
				closesocket(newSession);
			}
		}
	}
	return 0;
}

//���ܿͻ��˷�������������ݲ�ת��
int Server::Loop() {
	CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	u_long blockMode = Config::BLOCKMODE;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������
	int rtn;

	if ((rtn = ioctlsocket(this->srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		cout << "ioctlsocket() failed with error!\n";
		string msg_e1("ioctlsocket() failed with error!\n");
		dlg->m_List.AddString(CString(msg_e1.c_str()));
		return -1;
	}
	cout << "ioctlsocket() for server socket ok! Waiting for client connection and data\n";
	string msg_o1("ioctlsocket() for server socket ok! Waiting for client connection and data\n");
	dlg->m_List.AddString(CString(msg_o1.c_str()));

	while (true) { //�ȴ��ͻ�����������
		//Prepare the read and write socket sets for network I/O notification.
		FD_ZERO(&this->rfds);

		//��srvSocket���뵽rfds���ȴ��û���������
		FD_SET(this->srvSocket, &this->rfds);

		//�ȴ��û�����������û����ݵ�����Ựsocke�ɷ�������
		if ((this->numOfSocketSignaled = select(0, &this->rfds, NULL, NULL, NULL)) == SOCKET_ERROR) {
			//select���������пɶ����д��socket��������������rtn��.���һ�������趨�ȴ�ʱ�䣬��ΪNULL��Ϊ����ģʽ
			cout << "select() failed with error!\n";
			string msg_e2("select() failed with error!\n");
			dlg->m_List.AddString(CString(msg_e2.c_str()));
			return -1;
		}

		//���������е������ζ�����û������������������û����ݵ��������лỰsocket���Է�������
		//����Ƿ��пͻ��������ӵ���
		if (this->AcceptRequestionFromClient() != 0) return -1;
	}

	return 0;
}
