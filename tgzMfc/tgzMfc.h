
// tgzMfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtgzMfcApp:
// �йش����ʵ�֣������ tgzMfc.cpp
//

class CtgzMfcApp : public CWinApp
{
public:
	CtgzMfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtgzMfcApp theApp;