#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

struct  Configuration{

	/**
	�������Э��Payload���ݵĴ�С���ֽ�Ϊ��λ��
	*/
	static const int PAYLOAD_SIZE = 21;

	/**
	��ʱ��ʱ��
	*/
	static const int TIME_OUT =20;

};



/**
	�����Ӧ�ò����Ϣ
*/
struct  Message {
	char data[Configuration::PAYLOAD_SIZE];		//payload

	Message();
	Message(const Message &msg);
	Message & operator=(const Message &msg);
	~Message();

	void print();
};

/**
	���Ĳ�����㱨�Ķ�
*/
struct  Packet {
	int seqnum;										//���
	int acknum;										//ȷ�Ϻ�
	int checksum;									//У���
	char payload[Configuration::PAYLOAD_SIZE];		//payload
	
	Packet();
	Packet(const Packet& pkt);
	Packet & operator=(const Packet& pkt);
	bool operator==(const Packet& pkt) const;
	~Packet();

	void print();
};
#endif

