// ListViewCurrentPro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "ListViewCurrentPro.h"
#include "afxdialogex.h"


// ListViewCurrentPro �Ի���

IMPLEMENT_DYNAMIC(ListViewCurrentPro, CDialogEx)

ListViewCurrentPro::ListViewCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(ListViewCurrentPro::IDD, pParent)
{

}

ListViewCurrentPro::~ListViewCurrentPro()
{
}

void ListViewCurrentPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ListViewCurrentPro, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, List_Current_Pro, &ListViewCurrentPro::OnLvnItemchangedCurrentPro)
END_MESSAGE_MAP()


// ListViewCurrentPro ��Ϣ�������
void ListViewCurrentPro::OnLvnItemchangedCurrentPro(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

