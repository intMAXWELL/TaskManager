#pragma once

#include "ListViewCurrentPro.h"
// DialogCurrentPro �Ի���

class DialogCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCurrentPro)

public:
	DialogCurrentPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCurrentPro();

// �Ի�������
	enum { IDD = Dialog_Finished_Pro };

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
};
