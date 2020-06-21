#ifndef TCP_SENDER_H
#define GBN_SENDER_H
#include "RdtSender.h"
#include <list>

using namespace std;

class tcpSender :public RdtSender
{
private:
    bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬

    int last_ack;
    int ack_count;
    
    int windows_size;// ���ڴ�С
	int nextseqnum;	 // ��һ���������
    int base;        //

    Packet packetWaitingAck;
	std::list<Packet> windows_packets;   //���ڻ���



public:

	bool getWaitingState();
	bool send(Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	tcpSender();
	virtual ~tcpSender();
};

#endif
