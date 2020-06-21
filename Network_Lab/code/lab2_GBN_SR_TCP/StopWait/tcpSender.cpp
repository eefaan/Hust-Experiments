#include "stdafx.h"
#include "Global.h"
#include "tcpSender.h"


tcpSender::tcpSender():nextseqnum(0),waitingState(false),windows_size(3),base(0),last_ack(-1),ack_count(0){}
tcpSender::~tcpSender(){}
bool tcpSender::getWaitingState() {
    if((this->base+this->windows_size)%(this->windows_size+1) == this->nextseqnum){
        //窗口中的packet均未被确认接收成功
        waitingState=true;
    }
    else{
        waitingState=false;
    }
	return waitingState;
}

bool tcpSender::send(Message &message) {
    if(this->getWaitingState()){
        //窗口中的packet均未被确认接收成功
        return false;
    }

    this->packetWaitingAck.acknum = -1; //忽略该字段
	this->packetWaitingAck.seqnum = this->nextseqnum;
	this->packetWaitingAck.checksum = 0;
    memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
    this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
    pUtils->printPacket("发送方发送报文", this->packetWaitingAck);
    if(this->base == this->nextseqnum){
        pns->startTimer(SENDER, Configuration::TIME_OUT, 0);			//启动发送方定时器
    }
    pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
    this->windows_packets.push_back(this->packetWaitingAck);             //缓存未被确认的packet
    this->nextseqnum++;
    if(this->nextseqnum==this->windows_size+1){
        this->nextseqnum=0;
    }

    return true;
}

void tcpSender::receive(Packet &ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum){
        // 3*ack计数
        if(this->last_ack==ackPkt.acknum){
            this->ack_count++;
            if(this->ack_count==2){// 3*ack 快速重传
                // 输出提示
                pUtils->printPacket("-- 3*ack! -- 收到该包后进行快速重传", ackPkt);
                this->ack_count=0;

                // 快速重传
                for (Packet packet_i : this->windows_packets) {
                    pns->sendToNetworkLayer(RECEIVER, packet_i);			//重新发送数据包
                }

                return;
            }
        }
        else{
            this->last_ack=ackPkt.acknum;
            this->ack_count=0;
        }


        // 输出包信息
        pUtils->printPacket("发送方收到确认", ackPkt);
        // 循环更新窗口中元素，弹出已被确认的包
        int flag=0;
        for (Packet packet_i : this->windows_packets) {// search for packet
            if (packet_i.seqnum == ackPkt.acknum){
                flag=1;
                break;
            }
        }
        if(flag){// 若找到，开始更新窗口元素
            while(this->windows_packets.size()>0){// 窗口中有数据时
                if(this->windows_packets.front().seqnum != ackPkt.acknum){
                    this->windows_packets.pop_front();
                }
                else{
                    this->windows_packets.pop_front();
                    break;
                }
            }
        }
        // 滑动窗口
        this->base = (ackPkt.acknum + 1)%(this->windows_size + 1);
        // 输出窗口详情
        std::cout<<"----- windows details -----: "<<"base: "<<this->base<<"   windows_size: "<<this->windows_size<<"   nextseqnum: "<<this->nextseqnum<<endl;
        for (Packet packet_i : this->windows_packets) {
            pUtils->printPacket("----- windows details -----", packet_i);
        }

        // 窗口中所有数据均被确认
        if(this->base == this->nextseqnum){
            pUtils->printPacket("窗口中数据已全部确认，最后的ack", ackPkt);
    		pns->stopTimer(SENDER, 0);		//关闭定时器
        }
        else{
            //给当前分组更多的等待时间
            pns->stopTimer(SENDER, 0);		//关闭定时器
            pns->startTimer(SENDER, Configuration::TIME_OUT, 0);    //重新启动定时器
        }
    }

}

void tcpSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发此报文及窗口内后续报文", this->packetWaitingAck);
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);			//重新启动发送方定时器
    // Iterate and print values of the list
    for (Packet packet_i : this->windows_packets) {
        pns->sendToNetworkLayer(RECEIVER, packet_i);			//重新发送数据包
    }

}
