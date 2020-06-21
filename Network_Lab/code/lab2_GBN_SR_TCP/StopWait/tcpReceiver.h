#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include "RdtReceiver.h"
class tcpReceiver :public RdtReceiver
{
private:
	int windows_size;
	int expectSequenceNumberRcvd;	// �ڴ��յ�����һ���������
	Packet lastAckPkt;				// �ϴη��͵�ȷ�ϱ���

public:
	tcpReceiver();
	virtual ~tcpReceiver();

public:

	void receive(Packet &packet);	// ���ձ��ģ�����NetworkService����
};

#endif
