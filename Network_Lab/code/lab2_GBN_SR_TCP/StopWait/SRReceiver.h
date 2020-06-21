#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include "RdtReceiver.h"
#include <list>

class SRReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				// 上次发送的确认报文

	int recv_windows_size;// 窗口大小
	int nextseqnum;	 // 下一个发送序号
    int recv_base;   //

	std::list<Packet> windows_packets;   //窗口缓存

public:
	SRReceiver();
	virtual ~SRReceiver();

public:

	void receive(Packet &packet);	// 接收报文，将被NetworkService调用
};

#endif
