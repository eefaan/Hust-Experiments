#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"


SRSender::SRSender():nextseqnum(0),waitingState(false),windows_size(4),base(0){}
SRSender::~SRSender(){}
bool SRSender::getWaitingState() {
    if((this->base + this->windows_size)%(2*this->windows_size) == this->nextseqnum){
        //窗口中的首个packet未被确认接收成功
        waitingState=true;
    }
    else{
        waitingState=false;
    }
	return waitingState;
}

bool SRSender::send(Message &message) {
    if(this->getWaitingState()){
        //窗口中的首个packet未被确认接收成功
        return false;
    }
    this->packetWaitingAck.acknum = -1; //忽略该字段
	this->packetWaitingAck.seqnum = this->nextseqnum;
	this->packetWaitingAck.checksum = 0;
    memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
    this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
    pUtils->printPacket("发送方发送报文", this->packetWaitingAck);
    pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck.seqnum);			//启动发送方定时器
    pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
    this->windows_packets.push_back(this->packetWaitingAck);            //缓存未被确认的packet
    this->nextseqnum++;
    if(this->nextseqnum==2*this->windows_size){
        this->nextseqnum=0;
    }
    return true;
}

void SRSender::receive(Packet &ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum) {
        pUtils->printPacket("发送方收到确认", ackPkt);
        pns->stopTimer(SENDER, ackPkt.acknum);// 关闭定时器
        // 从窗口中删除已被确认的包 保证剩余的均为未确认包
        for (auto it = this->windows_packets.begin(); it != this->windows_packets.end(); it++) {
            if (it->seqnum == ackPkt.acknum) {// 找到对应包
                this->windows_packets.erase(it);
                break;
            }
        }

        // 滑动窗口
        if(this->windows_packets.size()==0){//若删除缓存后无包
            this->base = this->nextseqnum;
        }
        else{//base=缓冲区中首包（未确认）
            this->base = this->windows_packets.front().seqnum;
        }

        // 输出窗口详情
        std::cout<<"----- windows details -----: "<<"base: "<<this->base<<"   windows_size: "<<this->windows_size<<"   nextseqnum: "<<this->nextseqnum<<endl;
        for (Packet packet_i : this->windows_packets) {
            pUtils->printPacket("----- windows details -----", packet_i);
        }
    }
}

void SRSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	// pUtils->printPacket("发送方定时器时间到，重发此报文", this->packetWaitingAck);
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);			//重新启动发送方定时器
    // Iterate and print values of the list
    for (Packet packet_i : this->windows_packets) {
        if(packet_i.seqnum == seqNum){//重发超时数据包
            pUtils->printPacket("发送方定时器时间到，重发此报文", packet_i);
            pns->sendToNetworkLayer(RECEIVER, packet_i);
            break;
        }
    }
}
