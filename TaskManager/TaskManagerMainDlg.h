
// TaskManagerMainDlg.h : ͷ�ļ�

#pragma once
#ifndef TASK_MANAGER_MAIN_DLG_H
#define TASK_MANAGER_MAIN_DLG_H

#include "DialogCurrentPro.h"
#include "afxcmn.h"
#include "DialogFinishedPro.h"
#include "DialogNewTask.h"
#include "DialogSettings.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxwin.h"

#define PERIOD_TASK  1
class DialogCurrentPro;

// TaskManagerMainDlg �Ի���
class TaskManagerMainDlg : public CDialogEx
{
// ����
public:
	TaskManagerMainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TASKMANAGER_DIALOG };

	DialogCurrentPro mDialogCurrenPro;//��ǰ����
	DialogFinishedPro mDialogFinishedPro;//�Ѿ���������
	DialogNewTask mDialogNewTask;
	DialogSettings mDialogSettings;

	int CPURunTime;//CPU����ʱ�䣬��ʱ��ƬΪ��λ
	int timeSlot = 1000;//ʱ��Ƭ
	int continueRunTimeSlots = 5;//�������е�ʱ��Ƭ�ĸ���
	
	int decPriority = 3;//���н��̼��ٵ�������
	int incPriority = 1;//�����������ӵ�������

	int clickTimes = 0;//cpu���Ƽ��ĵ������


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

	void Execute();

	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonNewTask();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStopCpu();
	afx_msg void OnBnClickedButtonStepIn();

	//Tab���л�����
	CTabCtrl tabControl;
	// �½�����ť�������
	CButton buttonNewTask;
	CStatic CPURunTimeTextCtrl;
	CButton buttonCPUCtrl;
	CButton buttonStepInCtrl;
};

#endif
