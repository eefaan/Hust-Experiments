#include "stdafx.h"
#include "Global.h"
#include "tcpSender.h"


tcpSender::tcpSender():nextseqnum(0),waitingState(false),windows_size(3),base(0),last_ack(-1),ack_count(0){}
tcpSender::~tcpSender(){}
bool tcpSender::getWaitingState() {
    if((this->base+this->windows_size)%(this->windows_size+1) == this->nextseqnum){
        //�����е�packet��δ��ȷ�Ͻ��ճɹ�
        waitingState=true;
    }
    else{
        waitingState=false;
    }
	return waitingState;
}

bool tcpSender::send(Message &message) {
    if(this->getWaitingState()){
        //�����е�packet��δ��ȷ�Ͻ��ճɹ�
        return false;
    }

    this->packetWaitingAck.acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck.seqnum = this->nextseqnum;
	this->packetWaitingAck.checksum = 0;
    memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
    this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
    pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck);
    if(this->base == this->nextseqnum){
        pns->startTimer(SENDER, Configuration::TIME_OUT, 0);			//�������ͷ���ʱ��
    }
    pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
    this->windows_packets.push_back(this->packetWaitingAck);             //����δ��ȷ�ϵ�packet
    this->nextseqnum++;
    if(this->nextseqnum==this->windows_size+1){
        this->nextseqnum=0;
    }

    return true;
}

void tcpSender::receive(Packet &ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum){
        // 3*ack����
        if(this->last_ack==ackPkt.acknum){
            this->ack_count++;
            if(this->ack_count==2){// 3*ack �����ش�
                // �����ʾ
                pUtils->printPacket("-- 3*ack! -- �յ��ð�����п����ش�", ackPkt);
                this->ack_count=0;

                // �����ش�
                for (Packet packet_i : this->windows_packets) {
                    pns->sendToNetworkLayer(RECEIVER, packet_i);			//���·������ݰ�
                }

                return;
            }
        }
        else{
            this->last_ack=ackPkt.acknum;
            this->ack_count=0;
        }


        // �������Ϣ
        pUtils->printPacket("���ͷ��յ�ȷ��", ackPkt);
        // ѭ�����´�����Ԫ�أ������ѱ�ȷ�ϵİ�
        int flag=0;
        for (Packet packet_i : this->windows_packets) {// search for packet
            if (packet_i.seqnum == ackPkt.acknum){
                flag=1;
                break;
            }
        }
        if(flag){// ���ҵ�����ʼ���´���Ԫ��
            while(this->windows_packets.size()>0){// ������������ʱ
                if(this->windows_packets.front().seqnum != ackPkt.acknum){
                    this->windows_packets.pop_front();
                }
                else{
                    this->windows_packets.pop_front();
                    break;
                }
            }
        }
        // ��������
        this->base = (ackPkt.acknum + 1)%(this->windows_size + 1);
        // �����������
        std::cout<<"----- windows details -----: "<<"base: "<<this->base<<"   windows_size: "<<this->windows_size<<"   nextseqnum: "<<this->nextseqnum<<endl;
        for (Packet packet_i : this->windows_packets) {
            pUtils->printPacket("----- windows details -----", packet_i);
        }

        // �������������ݾ���ȷ��
        if(this->base == this->nextseqnum){
            pUtils->printPacket("������������ȫ��ȷ�ϣ�����ack", ackPkt);
    		pns->stopTimer(SENDER, 0);		//�رն�ʱ��
        }
        else{
            //����ǰ�������ĵȴ�ʱ��
            pns->stopTimer(SENDER, 0);		//�رն�ʱ��
            pns->startTimer(SENDER, Configuration::TIME_OUT, 0);    //����������ʱ��
        }
    }

}

void tcpSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��˱��ļ������ں�������", this->packetWaitingAck);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);			//�����������ͷ���ʱ��
    // Iterate and print values of the list
    for (Packet packet_i : this->windows_packets) {
        pns->sendToNetworkLayer(RECEIVER, packet_i);			//���·������ݰ�
    }

}
