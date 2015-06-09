#pragma once

#include "ListViewCurrentPro.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	// ��ʼ���������еĽ���
	void IninListCurrentPro(CRect crect);
	// ��ʼ�����̶���
	void InitListProQ(CRect crect);

	CListCtrl ListCurrentProCtrl;
	CListCtrl ListProQCtrl;

	//����ˢ��
	void NotifyDataSetChange();
	
	// CPU��ʼģ����̵����㷨
	void Execute(int decPriority,int incPriority,int runTimeSlots);
	// ��ȡ�Ӿ������н������ж��еĺ�ѡ����λ��
	int GetCandidatePos();
	// ���µ�ǰ����
	void UpdateCurrentPro(int decPriority);
	// ���¾�������
	void UpdateReadyPro(int incPriority);
	// ���µ�ǰ�����б�
	void UpdateListCPRO();
	// ���¾����б�
	void UpdateListReady();
};