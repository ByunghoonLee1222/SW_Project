
// cLBH.h : cLBH ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CcLBHApp:
// �� Ŭ������ ������ ���ؼ��� cLBH.cpp�� �����Ͻʽÿ�.
//

class CcLBHApp : public CWinApp
{
public:
	CcLBHApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CcLBHApp theApp;
