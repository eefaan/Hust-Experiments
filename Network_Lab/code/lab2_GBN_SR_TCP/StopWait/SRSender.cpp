#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"


SRSender::SRSender():nextseqnum(0),waitingState(false),windows_size(4),base(0){}
SRSender::~SRSender(){}
bool SRSender::getWaitingState() {
    if((this->base + this->windows_size)%(2*this->windows_size) == this->nextseqnum){
        //�����е��׸�packetδ��ȷ�Ͻ��ճɹ�
        waitingState=true;
    }
    else{
        waitingState=false;
    }
	return waitingState;
}

bool SRSender::send(Message &message) {
    if(this->getWaitingState()){
        //�����е��׸�packetδ��ȷ�Ͻ��ճɹ�
        return false;
    }
    this->packetWaitingAck.acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck.seqnum = this->nextseqnum;
	this->packetWaitingAck.checksum = 0;
    memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
    this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
    pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck);
    pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck.seqnum);			//�������ͷ���ʱ��
    pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
    this->windows_packets.push_back(this->packetWaitingAck);            //����δ��ȷ�ϵ�packet
    this->nextseqnum++;
    if(this->nextseqnum==2*this->windows_size){
        this->nextseqnum=0;
    }
    return true;
}

void SRSender::receive(Packet &ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum) {
        pUtils->printPacket("���ͷ��յ�ȷ��", ackPkt);
        pns->stopTimer(SENDER, ackPkt.acknum);// �رն�ʱ��
        // �Ӵ�����ɾ���ѱ�ȷ�ϵİ� ��֤ʣ��ľ�Ϊδȷ�ϰ�
        for (auto it = this->windows_packets.begin(); it != this->windows_packets.end(); it++) {
            if (it->seqnum == ackPkt.acknum) {// �ҵ���Ӧ��
                this->windows_packets.erase(it);
                break;
            }
        }

        // ��������
        if(this->windows_packets.size()==0){//��ɾ��������ް�
            this->base = this->nextseqnum;
        }
        else{//base=���������װ���δȷ�ϣ�
            this->base = this->windows_packets.front().seqnum;
        }

        // �����������
        std::cout<<"----- windows details -----: "<<"base: "<<this->base<<"   windows_size: "<<this->windows_size<<"   nextseqnum: "<<this->nextseqnum<<endl;
        for (Packet packet_i : this->windows_packets) {
            pUtils->printPacket("----- windows details -----", packet_i);
        }
    }
}

void SRSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	// pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��˱���", this->packetWaitingAck);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);			//�����������ͷ���ʱ��
    // Iterate and print values of the list
    for (Packet packet_i : this->windows_packets) {
        if(packet_i.seqnum == seqNum){//�ط���ʱ���ݰ�
            pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��˱���", packet_i);
            pns->sendToNetworkLayer(RECEIVER, packet_i);
            break;
        }
    }
}
