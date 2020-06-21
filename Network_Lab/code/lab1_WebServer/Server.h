#pragma once
#include <winsock2.h>
#include <list>
#include <string>
#include <map>

using namespace std;

//������
class Server
{
private:
	string homeAddr;			//��������Ŀ¼
	SOCKET srvSocket;			//������socket
	char* recvBuf;				//���ܻ�����
	fd_set rfds;				//���ڼ��socket�Ƿ������ݵ����ĵ��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�������ݵ�����
	fd_set wfds;				//���ڼ��socket�Ƿ���Է��͵��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�����Է������ݣ�
	sockaddr_in srvAddr;		//��������IP��ַ
	int numOfSocketSignaled;	//�ɶ���д������������socket����
protected:
	virtual void sendMessage(SOCKET s, string msg);							//��SOCKET s������Ϣ
	virtual int AcceptRequestionFromClient();								//�ȴ��ͻ�����������
public:
	Server(void);
	Server(string home);
	virtual ~Server(void);
	virtual int WinsockStartup();		//��ʼ��Winsock
	virtual int ServerStartup();		//��ʼ��Server����������SOCKET���󶨵�IP��PORT
	virtual int ServerStartup(string str_ip, int port);
	virtual int ListenStartup();		//��ʼ�����ͻ�������
	virtual int Loop();					//ѭ��ִ��"�ȴ��ͻ�������"->���������ͻ�ת����Ϣ��->"�ȴ��ͻ�����Ϣ"
};
