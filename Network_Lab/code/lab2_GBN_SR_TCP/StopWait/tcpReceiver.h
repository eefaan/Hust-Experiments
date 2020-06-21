#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include "RdtReceiver.h"
class tcpReceiver :public RdtReceiver
{
private:
	int windows_size;
	int expectSequenceNumberRcvd;	// 期待收到的下一个报文序号
	Packet lastAckPkt;				// 上次发送的确认报文

public:
	tcpReceiver();
	virtual ~tcpReceiver();

public:

	void receive(Packet &packet);	// 接收报文，将被NetworkService调用
};

#endif
