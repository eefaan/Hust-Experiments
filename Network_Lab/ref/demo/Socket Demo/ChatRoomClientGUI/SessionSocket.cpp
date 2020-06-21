// SessionSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRoomClientGUI.h"
#include "SessionSocket.h"
#include "ChatRoomClientGUIDlg.h"


// CSessionSocket

CSessionSocket::CSessionSocket()
{
}

CSessionSocket::~CSessionSocket()
{
}






void CSessionSocket::OnReceive(int nErrorCode)
{
	char recvBuf[1024];
	int rtn;

	rtn = this->Receive(recvBuf,1024);
	switch(rtn){
		case 0:
			this->Close();
			break;
		case SOCKET_ERROR:
			if(this->GetLastError() != WSAEWOULDBLOCK){
				this->Close();
			}
			break;
		default:
			recvBuf[rtn] = '\0';
	}

	//�ڶԻ�������ʾ
	CChatRoomClientGUIDlg *dlg =  (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	dlg->m_List.AddString(CString(recvBuf));

	CAsyncSocket::OnReceive(nErrorCode);
}

void CSessionSocket::OnClose(int nErrorCode)
{
	//�ڶԻ�������ʾ
	CChatRoomClientGUIDlg *dlg =  (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	dlg->m_List.AddString("�������ر� !");

	CAsyncSocket::OnClose(nErrorCode);
}
