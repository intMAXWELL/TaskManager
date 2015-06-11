#pragma once

#include "PCB.h"
#include "LinkedList.h"

class DialogFinishedPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFinishedPro)

public:
	DialogFinishedPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogFinishedPro();

// �Ի�������
	enum { IDD = Dialog_Finished_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl listFinishedProCtrl;
	CStatic textAVGRightTimeCtrl;

	LinkedList<PCB*> mFinishedProcess;

	void InitFinishedProList(CRect rect);//��ʼ���ѽ����б�
	void NotifyDataSetChange();//�����б�
	double CalAVGRightTime();//����ƽ����Ȩ��תʱ��

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};


