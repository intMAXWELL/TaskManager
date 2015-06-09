#pragma once
#include "afxwin.h"
#include "Util.h"


// DialogSettings �Ի���
class DialogSettings : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSettings)

public:
	DialogSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSettings();

	CString  decPriority;
	CString incPriority;
	CString continueRunTimeSlots;//�������е�ʱ��Ƭ�ĸ���
	CString mSNum;

// �Ի�������
	enum { IDD = Dialog_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CEdit decPriEditCtrl;
	CEdit incPriEditCtrl;
	CEdit continueRunTimeSlotsCtrl;
	CEdit mSNumEditCtrl;

	afx_msg void OnBnClickedOk();
	
	virtual BOOL OnInitDialog();
};
