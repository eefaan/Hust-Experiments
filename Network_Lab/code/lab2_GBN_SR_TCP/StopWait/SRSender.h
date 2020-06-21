#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include <list>

class SRSender :public RdtSender
{
private:
    bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬

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
	SRSender();
	virtual ~SRSender();
};

#endif
