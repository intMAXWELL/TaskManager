
// TaskManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// TaskManagerMain: 
// �йش����ʵ�֣������ TaskManager.cpp
//

class TaskManagerMain : public CWinApp
{
public:
	TaskManagerMain();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern TaskManagerMain theApp;