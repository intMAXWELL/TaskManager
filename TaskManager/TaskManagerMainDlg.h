
// TaskManagerMainDlg.h : ͷ�ļ�

#pragma once
#include "afxcmn.h"
#include "DialogCurrentPro.h"
#include "DialogFinishedPro.h"
#include "DialogNewTask.h"
#include "DialogSettings.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxwin.h"

#define PERIOD_TASK  1

// TaskManagerMainDlg �Ի���
class TaskManagerMainDlg : public CDialogEx
{
// ����
public:
	TaskManagerMainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TASKMANAGER_DIALOG };
private:

	DialogCurrentPro mDialogCurrenPro;//��ǰ����
	DialogFinishedPro mDialogFinishedPro;//�Ѿ���������
	DialogNewTask mDialogNewTask;
	DialogSettings mDialogSettings;
	
	LinkedList<PCB*> mFinishedProcess;

	int CPURunTime = 0;//CPU����ʱ�䣬��ʱ��ƬΪ��λ
	int timeSlot = 1000;//ʱ��Ƭ
	int continueRunTimeSlots = 5;//�������е�ʱ��Ƭ�ĸ���
	int tmp;//��¼�������е�ʱ��Ƭ�ĸ���
	int decPriority = 3;//���н��̼��ٵ�������
	int incPriority = 1;//�����������ӵ�������

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
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonNewTask();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//Tab���л�����
	CTabCtrl tabControl;
	// �½�����ť�������
	CButton buttonNewTask;
	CStatic CPURunTimeTextCtrl;

};
