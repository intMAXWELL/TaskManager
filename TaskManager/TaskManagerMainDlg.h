
// TaskManagerMainDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DialogCurrentPro.h"
#include "DialogFinishedPro.h"

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
	CTabCtrl tabControl;
	afx_msg void OnBnClickedButtonSettings();
};
