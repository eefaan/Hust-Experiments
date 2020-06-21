#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include "RdtReceiver.h"
#include <list>

class SRReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				// �ϴη��͵�ȷ�ϱ���

	int recv_windows_size;// ���ڴ�С
	int nextseqnum;	 // ��һ���������
    int recv_base;   //

	std::list<Packet> windows_packets;   //���ڻ���

public:
	SRReceiver();
	virtual ~SRReceiver();

public:

	void receive(Packet &packet);	// ���ձ��ģ�����NetworkService����
};

#endif
