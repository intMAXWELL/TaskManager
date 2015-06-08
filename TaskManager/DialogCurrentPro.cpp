// DialogCurrentPro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogCurrentPro.h"
#include "afxdialogex.h"

// DialogCurrentPro �Ի���

IMPLEMENT_DYNAMIC(DialogCurrentPro, CDialogEx)

DialogCurrentPro::DialogCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCurrentPro::IDD, pParent)
{

}

DialogCurrentPro::~DialogCurrentPro()
{
}

void DialogCurrentPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//�˾仰�ǳ���Ҫ
	//Called by the framework to exchange and validate dialog data.�����ǿ�ܵ��ô˺�������д��ȷ�϶Ի������ݡ�
	DDX_Control(pDX, List_Current_Pro, ListCurrentProCtrl);
	DDX_Control(pDX, List_Pro_Queue, ListProQCtrl);
}


BEGIN_MESSAGE_MAP(DialogCurrentPro, CDialogEx)
END_MESSAGE_MAP()

void DialogCurrentPro::IninListCurrentPro(CRect rect){
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	ListCurrentProCtrl.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	ListCurrentProCtrl.SetExtendedStyle(ListCurrentProCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	ListCurrentProCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 9, 0);
	ListCurrentProCtrl.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 9, 1);
	ListCurrentProCtrl.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect.Width() / 9, 2);
	ListCurrentProCtrl.InsertColumn(3, _T("���ȼ�"), LVCFMT_CENTER, rect.Width() / 9, 3);
	ListCurrentProCtrl.InsertColumn(4, _T("����ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 4);
	ListCurrentProCtrl.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 5);
	ListCurrentProCtrl.InsertColumn(6, _T("������ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 6);
	ListCurrentProCtrl.InsertColumn(7, _T("��������ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 7);
	ListCurrentProCtrl.InsertColumn(8, _T("״̬"), LVCFMT_CENTER, rect.Width() / 9, 8);
}

void DialogCurrentPro::InitListProQ(CRect rect){
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	ListProQCtrl.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	ListProQCtrl.SetExtendedStyle(ListProQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	ListProQCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 9, 0);
	ListProQCtrl.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 9, 1);
	ListProQCtrl.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect.Width() / 9, 2);
	ListProQCtrl.InsertColumn(3, _T("���ȼ�"), LVCFMT_CENTER, rect.Width() / 9, 3);
	ListProQCtrl.InsertColumn(4, _T("����ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 4);
	ListProQCtrl.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 5);
	ListProQCtrl.InsertColumn(6, _T("������ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 6);
	ListProQCtrl.InsertColumn(7, _T("��������ʱ��"), LVCFMT_CENTER, rect.Width() / 9, 7);
	ListProQCtrl.InsertColumn(8, _T("״̬"), LVCFMT_CENTER, rect.Width() / 9, 8);
}
//��ʼ��
BOOL DialogCurrentPro::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	IninListCurrentPro(rect);
	InitListProQ(rect);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}


