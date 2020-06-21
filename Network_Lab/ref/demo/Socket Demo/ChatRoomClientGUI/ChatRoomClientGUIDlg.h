// ChatRoomClientGUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SessionSocket.h"


// CChatRoomClientGUIDlg �Ի���
class CChatRoomClientGUIDlg : public CDialog
{
// ����
public:
	CChatRoomClientGUIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CChatRoomClientGUIDlg();

// �Ի�������
	enum { IDD = IDD_CHATROOMCLIENTGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
private:
	CIPAddressCtrl m_IPCtrl;
	UINT m_Port;
	CString m_SendMsg;
	CSessionSocket *m_Socket;
public:
	CListBox m_List;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedConn();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedQuit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
