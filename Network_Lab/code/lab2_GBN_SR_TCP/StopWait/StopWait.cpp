// StopWait.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include "GBNSender.h"
#include "GBNReceiver.h"
#include "SRSender.h"
#include "SRReceiver.h"
#include "tcpSender.h"
#include "tcpReceiver.h"


int main(int argc, char** argv[])
{
	// Rdt sender and receiver
	// RdtSender *ps = new StopWaitRdtSender();
	// RdtReceiver * pr = new StopWaitRdtReceiver();
	// GBN sender and receiver
	// RdtSender *ps = new GBNSender();
	// RdtReceiver * pr = new GBNReceiver();
	// SR sender and receiver
	RdtSender *ps = new SRSender();
	RdtReceiver * pr = new SRReceiver();
	// tcp sender and receiver
	// RdtSender *ps = new tcpSender();
	// RdtReceiver * pr = new tcpReceiver();

	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("C:\\Users\\leo\\source\\repos\\rdt_win_student\\input.txt");
	pns->setOutputFile("C:\\Users\\leo\\source\\repos\\rdt_win_student\\output.txt");
	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete

	return 0;
}
