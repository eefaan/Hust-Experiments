#include "stdafx.h"
#include "Config.h"
#include <string>

using namespace std;

Config::Config(void)
{
}

Config::~Config(void)
{
}

const string Config::SERVERADDRESS = "0.0.0.0";	//������IP��ַ
const int Config::MAXCONNECTION = 50;				//���������5
const int Config::BUFFERLENGTH = 1024;				//��������С256�ֽ�
const int Config::PORT = 80;						//�������˿�80
const u_long Config::BLOCKMODE = 1;					//SOCKETΪ������ģʽ
