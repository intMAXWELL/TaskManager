#pragma once

#ifndef DIALOG_CURRENT_PRO_H
#define DIALOG_CURRENT_PRO_H

#include "ListViewCurrentPro.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxcmn.h"
#include "afxwin.h"

// DialogCurrentPro �Ի���

class DialogCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCurrentPro)

public:
	DialogCurrentPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCurrentPro();

// �Ի�������
	enum { IDD = Dialog_Finished_Pro };

	PCB* mCurrentProcess;
	LinkedList<PCB*> mReadyProcess;

	int continueRunTimeSlots;
	int tmp;//��¼�������е�ʱ��Ƭ�ĸ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	// ��ʼ���������еĽ���
	void IninListCurrentPro(CRect crect);
	// ��ʼ�����̶���
	void InitListProQ(CRect crect);
	virtual BOOL DestroyWindow();

	CListCtrl ListCurrentProCtrl;
	CListCtrl ListProQCtrl;

	//����ˢ��
	void NotifyDataSetChange();
	
	// CPU��ʼģ����̵����㷨
	PCB*  Execute(int decPriority, int incPriority, int cpuRunTime);
	// ��ȡ�Ӿ������н������ж��еĺ�ѡ����λ��
	int GetCandidatePos();
	// ���µ�ǰ����
	PCB* UpdateCurrentPro(int decPriority);
	// ���¾�������
	void UpdateReadyPro(int incPriority);
	// ���µ�ǰ�����б�
	void UpdateListCPRO();
	// ���¾����б�
	void UpdateListReady();
	//��ǰ����д���ļ� 
	void WriteCurrentProToFile(int cpuRunTime);
	//��������д���ļ�
	void WriteReadyProToFile();

	// ��ȡ��ǰʱ�䲢���浽curTime   
	CTime curTime = CTime::GetCurrentTime();
	// ����ǰʱ��curTime�����ʽ��Ϊ�ַ���   
	CString strTime = curTime.Format(_T("%Y_%m_%d_%H_%M_%S"));

	CFile file;

	CString currentProHead;
	CString readyProHead;
	afx_msg void OnStnClickedAvgRightTime();
};

#endif 
