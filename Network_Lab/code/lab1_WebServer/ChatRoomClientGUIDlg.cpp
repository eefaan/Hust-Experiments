// ChatRoomClientGUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ChatRoomClientGUI.h"
#include "ChatRoomClientGUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChatRoomClientGUIDlg �Ի���




CChatRoomClientGUIDlg::CChatRoomClientGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatRoomClientGUIDlg::IDD, pParent)
	, m_Port(80)
	, m_SendMsg(".")
	, m_Socket(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Socket = new CSessionSocket(); //�����Ựsocket����
}

CChatRoomClientGUIDlg::~CChatRoomClientGUIDlg(){
	if(this->m_Socket != NULL){
		this->m_Socket->Close();
		delete this->m_Socket;
	}
}

void CChatRoomClientGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPCtrl);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Control(pDX, IDC_MSGLIST, m_List);
	DDX_Text(pDX, IDC_SENDMSG, m_SendMsg);
}

BEGIN_MESSAGE_MAP(CChatRoomClientGUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, &CChatRoomClientGUIDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CONN, &CChatRoomClientGUIDlg::OnBnClickedConn)
	ON_BN_CLICKED(IDC_QUIT, &CChatRoomClientGUIDlg::OnBnClickedQuit)
END_MESSAGE_MAP()


// CChatRoomClientGUIDlg ��Ϣ�������

BOOL CChatRoomClientGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// �����׽���
	this->m_Socket->Create(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatRoomClientGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomClientGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatRoomClientGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// �����û��������Ϣ
void CChatRoomClientGUIDlg::OnBnClickedSend()
{
	UpdateData(TRUE); //�õ��û�������༭����������ַ���

	this->m_Socket->Send(this->m_SendMsg,this->m_SendMsg.GetLength());

	//��ձ༭��
	this->m_SendMsg = "";
	UpdateData(FALSE);
}

//���ӷ�����
void CChatRoomClientGUIDlg::OnBnClickedConn()
{
	//�õ��û������IP��ַ
	BYTE f0,f1,f2,f3;
	CIPAddressCtrl *ipCtrl = (CIPAddressCtrl *)this->GetDlgItem(IDC_IPADDRESS);
	ipCtrl->GetAddress(f0,f1,f2,f3);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"),f0,f1,f2,f3);

	//�õ��û�����Ķ˿ں�
	UpdateData(TRUE);

	// this->m_Socket->Connect(ip,this->m_Port);
	//��ť״̬�仯
	(CButton *)(this->GetDlgItem(IDC_QUIT))->EnableWindow(TRUE);
	(CButton *)(this->GetDlgItem(IDC_CONN))->EnableWindow(FALSE);

	string str_ip(ip.GetBuffer(0));
	int port_int = this->m_Port;
	string home(this->m_SendMsg);
	//�򴰿ڷ���������Ϣ
	string msg;
	msg = "��������������: IP:" + str_ip + "  ,  Port:" + to_string(port_int) + "  ,  ��Ŀ¼Ϊ��" + home;
	CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	dlg->m_List.AddString(CString(msg.c_str()));

	//���ӷ�����
	this->m_server = new Server(home);
	if (this->m_server->WinsockStartup() == -1)return;
	if (this->m_server->ServerStartup(str_ip,port_int) == -1)return;
	if (this->m_server->ListenStartup() == -1)return;
	//if (srv.Loop() == -1)return;

	HANDLE thread = CreateThread(NULL, 0, server_running, (LPVOID)(this->m_server), 0, 0);
	this->m_thread = thread;
}

DWORD WINAPI server_running(LPVOID lpParameter) {
	Server *server = (Server *)lpParameter;
	if (server->Loop() == -1) return -1;
	return 0;
}

void CChatRoomClientGUIDlg::OnBnClickedQuit()
{
	(CButton *)(this->GetDlgItem(IDC_CONN))->EnableWindow(TRUE);
	(CButton *)(this->GetDlgItem(IDC_QUIT))->EnableWindow(FALSE);

	DWORD dwExitCode=0;
	TerminateThread(this->m_thread,dwExitCode);

	//�Ͽ�������
	if(this->m_server !=NULL){
		delete (this->m_server);
		this->m_server = NULL;
	}

	//�򴰿ڷ��ͶϿ�������Ϣ
	string msg;
	msg = "�������ѶϿ���";
	CChatRoomClientGUIDlg *dlg = (CChatRoomClientGUIDlg *)(AfxGetApp()->GetMainWnd());
	dlg->m_List.AddString(CString(msg.c_str()));
}

void CChatRoomClientGUIDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//����ʲô����������ֹ�û���Enter���رմ���
}

void CChatRoomClientGUIDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	//����ʲô����������ֹ�û���Esc���رմ���
	this->EndDialog(TRUE);//�رնԻ���
}

//����PreTranslateMessage��ʹ�� ��Ϣ�༭���ܴ���س��������û��������ݰ��س����ͷ�����Ϣ
BOOL CChatRoomClientGUIDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN){
		HWND hWnd = ::GetFocus();
		if(IDC_SENDMSG == ::GetDlgCtrlID(hWnd)){
			this->OnBnClickedSend();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
