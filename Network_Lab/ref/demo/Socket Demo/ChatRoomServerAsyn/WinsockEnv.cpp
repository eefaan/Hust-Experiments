#include "WinsockEnv.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;


#define MAJORVERSION 2  //Winsock���汾��
#define MINORVERSION 2	//Winsock�ΰ汾��

WinsockEnv::WinsockEnv(void)
{
}

WinsockEnv::~WinsockEnv(void)
{
}

int WinsockEnv::Startup(){

	WSADATA wsaData;//���ڷ���Winsock�Ļ�����Ϣ   
	int rtn;		//Winsock��ʼ�������ķ���ֵ
	WORD  wVersionRequested = MAKEWORD( MAJORVERSION, MINORVERSION ); //Winsock�汾�ţ����ֽڴΰ汾�����ֽ����汾��


	//��ʼ�� winsock
	rtn = WSAStartup(wVersionRequested, &wsaData);

	if(rtn){ //�������ֵ����0����Winsock��ʼ��ʧ��
		cout<< "Winsock startup error!\n";
		return -1;
	}

	//�жϷ��ص�Winsock�汾��
	if(LOBYTE(wsaData.wVersion) != MAJORVERSION || HIBYTE(wsaData.wVersion) != MINORVERSION){ //����汾����
		WSACleanup();  //���Winsock
		cout << "Winsock version error!\n";
		return -1;
	}

	cout << "Winsock startup ok!\n";
	return 0;
}
