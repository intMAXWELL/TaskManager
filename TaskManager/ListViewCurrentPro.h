#pragma once
#include "afxcmn.h"

// ListViewCurrentPro �Ի���

class ListViewCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(ListViewCurrentPro)

public:
	ListViewCurrentPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ListViewCurrentPro();

// �Ի�������
	enum { IDD = Dialog_Current_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedCurrentPro(NMHDR *pNMHDR, LRESULT *pResult);
};
