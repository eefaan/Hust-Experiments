#ifndef GBN_RECEIVER_H
#define GBN_RECEIVER_H
#include "RdtReceiver.h"
class GBNReceiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	// 期待收到的下一个报文序号
	int windows_size;
	Packet lastAckPkt;				// 上次发送的确认报文

public:
	GBNReceiver();
	virtual ~GBNReceiver();

public:

	void receive(Packet &packet);	// 接收报文，将被NetworkService调用
};

#endif
