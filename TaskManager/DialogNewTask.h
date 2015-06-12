#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
#include <iostream>
using namespace std;

// DialogNewTask �Ի���

class DialogNewTask : public CDialogEx
{
	DECLARE_DYNAMIC(DialogNewTask)

public:
	DialogNewTask(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogNewTask();

// �Ի�������
	enum { IDD = Dialog_New_Task };
//pid����
	int pid;
//����pid����
	int tmpPid;
//������
	CString id;
//�û���
	CString userName;
//���ȼ�
	CString priority;
//����ʱ��
	CString allTime;
//����������
	LinkedList<PCB*> newTaskList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	// ��ʼ���½��̶����б�ѡ��
	void InitListNewTaskQ(CRect c);
	// ��������б�
	void AddItemToList();

	CListCtrl listNewTaskQCtrl;
	CEdit processNameCtrl;
	CEdit userNameCtrl;
	CEdit priorityCtrl;
	CEdit allTimeCtrl;
	
	afx_msg void OnBnClickedTaskButtonAddToList();
	afx_msg void OnBnClickedOk();

	// �ͷ���Դ��ֵ��ʼ��
	void ClearAll();
	virtual void OnCancel();
	afx_msg void OnNMRClickNewTaskQ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
};
