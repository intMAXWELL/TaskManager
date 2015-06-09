// DialogSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogSettings.h"
#include "afxdialogex.h"


// DialogSettings �Ի���

IMPLEMENT_DYNAMIC(DialogSettings, CDialogEx)

DialogSettings::DialogSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSettings::IDD, pParent)
{

}

DialogSettings::~DialogSettings()
{
}

void DialogSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Settings_Dec_Pri, decPriEditCtrl);
	DDX_Control(pDX, Settings_Inc_Pri, incPriEditCtrl);
	DDX_Control(pDX, Settings_Exist_Time_Slot, continueRunTimeSlotsCtrl);
	DDX_Control(pDX, Settings_Time_Slot_MS_Num, mSNumEditCtrl);
}


BEGIN_MESSAGE_MAP(DialogSettings, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSettings::OnBnClickedOk)
END_MESSAGE_MAP()


//ȷ�ϼ����º�
void DialogSettings::OnBnClickedOk()
{
	//���ݱ�������Ӧ������
	decPriEditCtrl.GetWindowTextW(decPriority);
	incPriEditCtrl.GetWindowTextW(incPriority);
	continueRunTimeSlotsCtrl.GetWindowTextW(continueRunTimeSlots);
	mSNumEditCtrl.GetWindowTextW(mSNum);

	if (Util::CStringToInt(decPriority) < 0 || Util::CStringToInt(decPriority)>20 || Util::CStringToInt(incPriority) < 0 || Util::CStringToInt(incPriority)>20)
	{
		MessageBox(_T("���ӻ��߼����������ķ�Χ��[1,20]!"), _T("��ʾ"),0);
	}
	else if (decPriority == "" || incPriority == "" || continueRunTimeSlots == "" || mSNum == "")
	{
		MessageBox(_T("����д����!"), _T("��ʾ"), 0);
	}
	else
	{
		CDialogEx::OnOK();
	}
}


BOOL DialogSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	decPriEditCtrl.SetWindowTextW(_T("3"));
	incPriEditCtrl.SetWindowTextW(_T("1"));
	continueRunTimeSlotsCtrl.SetWindowTextW(_T("5"));
	mSNumEditCtrl.SetWindowTextW(_T("1000"));

	return TRUE;
}
