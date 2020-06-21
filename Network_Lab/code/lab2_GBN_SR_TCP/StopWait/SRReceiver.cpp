#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"
#include <cmath>

using namespace std;

SRReceiver::SRReceiver():recv_base(0),recv_windows_size(4)
{
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


SRReceiver::~SRReceiver()
{
}


void SRReceiver::receive(Packet &packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);

	//���У�����ȷ
	if (checkSum == packet.checksum) {

		pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);

		int find=0;
		for(int i=0;i<recv_windows_size;i++){
			if(((this->recv_base+i)%(2*recv_windows_size))==packet.seqnum)find=1;
		}

		if(find){// ����recv_base~recv_base+N-1
			if(this->windows_packets.size() == 0){// �׸�����
				this->windows_packets.push_front(packet);
			}
			else{//����Ѱ�Һ���λ�ò���
				int flag=0;
				int repeat=0;
				// calculate the distance between packet and recv_base
				int dis_pak=0;
				int dis_it=0;
				if(packet.seqnum>=recv_base)dis_pak=packet.seqnum-recv_base;
				else dis_pak=2*recv_windows_size-recv_base+packet.seqnum+1;
				for(auto it = this->windows_packets.begin(); it != this->windows_packets.end(); ){//compare the distacen to recv_base
					if(it->seqnum>=recv_base)dis_it=it->seqnum-recv_base;
					else dis_it=2*recv_windows_size-recv_base+it->seqnum+1;

					if(dis_pak == dis_it){// �ظ���
						repeat=1;
						break;
					}
					else if(dis_it > dis_pak) {// �ҵ�ָ��λ�� �����°�
		                this->windows_packets.insert(it,packet);//TODO: test IF ture
						flag=1;
		                break;
		            }
		            else {
		                ++it;
		            }
				}
				if(flag==0 && repeat==0){//δ�������м�
					this->windows_packets.push_back(packet);
				}
			}

			cout<<endl<<this->recv_base<<endl;
			for(Packet packet_i : this->windows_packets){
				pUtils->printPacket("----- recv windows message -----", packet_i);
			}

		}

		// ��buffer�����������
		while(this->windows_packets.size()!=0){
			if(this->windows_packets.front().seqnum == this->recv_base){// ������������ͬ
				//ȡ��Message�����ϵݽ���Ӧ�ò�
				Message msg;
				memcpy(msg.data, this->windows_packets.front().payload, sizeof(this->windows_packets.front().payload));
				pns->delivertoAppLayer(RECEIVER, msg);
				//�����û���
				this->windows_packets.pop_front();
				this->recv_base = this->recv_base + 1; //�������
				if(this->recv_base == 2*this->recv_windows_size){
					this->recv_base=0;
				}
			}
			else{
				break;
			}
		}

		lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�

	}
	else {
		// �Դ������������
		if (checkSum != packet.checksum) {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		}
		else {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
		}
	}
}
