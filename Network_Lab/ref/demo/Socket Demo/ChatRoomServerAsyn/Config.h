#pragma once
#include <string>
#include <winsock2.h>

using namespace std;

//����������Ϣ
class Config
{
public:
	static const int MAXCONNECTION;		//���������
	static const int BUFFERLENGTH;		//��������С
    static const string SERVERADDRESS;  //��������ַ
	static const int PORT;				//�������˿�
	static const u_long BLOCKMODE;			//SOCKET����ģʽ
private:
	Config(void);
	~Config(void);
};
