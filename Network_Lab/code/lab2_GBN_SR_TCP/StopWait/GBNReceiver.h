#ifndef GBN_RECEIVER_H
#define GBN_RECEIVER_H
#include "RdtReceiver.h"
class GBNReceiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	// �ڴ��յ�����һ���������
	int windows_size;
	Packet lastAckPkt;				// �ϴη��͵�ȷ�ϱ���

public:
	GBNReceiver();
	virtual ~GBNReceiver();

public:

	void receive(Packet &packet);	// ���ձ��ģ�����NetworkService����
};

#endif
