// ChatRoomClientGUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatRoomClientGUIApp:
// �йش����ʵ�֣������ ChatRoomClientGUI.cpp
//

class CChatRoomClientGUIApp : public CWinApp
{
public:
	CChatRoomClientGUIApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatRoomClientGUIApp theApp;