#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"
#include <cmath>

using namespace std;

SRReceiver::SRReceiver():recv_base(0),recv_windows_size(4)
{
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


SRReceiver::~SRReceiver()
{
}


void SRReceiver::receive(Packet &packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);

	//如果校验和正确
	if (checkSum == packet.checksum) {

		pUtils->printPacket("接收方正确收到发送方的报文", packet);

		int find=0;
		for(int i=0;i<recv_windows_size;i++){
			if(((this->recv_base+i)%(2*recv_windows_size))==packet.seqnum)find=1;
		}

		if(find){// 若在recv_base~recv_base+N-1
			if(this->windows_packets.size() == 0){// 首个缓存
				this->windows_packets.push_front(packet);
			}
			else{//否则寻找合适位置插入
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

					if(dis_pak == dis_it){// 重复包
						repeat=1;
						break;
					}
					else if(dis_it > dis_pak) {// 找到指定位置 插入新包
		                this->windows_packets.insert(it,packet);//TODO: test IF ture
						flag=1;
		                break;
		            }
		            else {
		                ++it;
		            }
				}
				if(flag==0 && repeat==0){//未插入在中间
					this->windows_packets.push_back(packet);
				}
			}

			cout<<endl<<this->recv_base<<endl;
			for(Packet packet_i : this->windows_packets){
				pUtils->printPacket("----- recv windows message -----", packet_i);
			}

		}

		// 从buffer中输出有序报文
		while(this->windows_packets.size()!=0){
			if(this->windows_packets.front().seqnum == this->recv_base){// 与待发送序号相同
				//取出Message，向上递交给应用层
				Message msg;
				memcpy(msg.data, this->windows_packets.front().payload, sizeof(this->windows_packets.front().payload));
				pns->delivertoAppLayer(RECEIVER, msg);
				//弹出该缓存
				this->windows_packets.pop_front();
				this->recv_base = this->recv_base + 1; //序号自增
				if(this->recv_base == 2*this->recv_windows_size){
					this->recv_base=0;
				}
			}
			else{
				break;
			}
		}

		lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方

	}
	else {
		// 对错误包不做处理
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		}
	}
}
