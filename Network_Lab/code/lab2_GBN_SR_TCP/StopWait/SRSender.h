#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include <list>

class SRSender :public RdtSender
{
private:
    bool waitingState;				// 是否处于等待Ack的状态

    int windows_size;// 窗口大小
	int nextseqnum;	 // 下一个发送序号
    int base;        //

    Packet packetWaitingAck;
	std::list<Packet> windows_packets;   //窗口缓存

public:

	bool getWaitingState();
	bool send(Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	SRSender();
	virtual ~SRSender();
};

#endif
