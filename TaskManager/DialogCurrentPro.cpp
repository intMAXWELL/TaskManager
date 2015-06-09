// DialogCurrentPro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogCurrentPro.h"
#include "afxdialogex.h"
#include "LinkedList.h"
#include "PCB.h"

// DialogCurrentPro �Ի���

IMPLEMENT_DYNAMIC(DialogCurrentPro, CDialogEx)

DialogCurrentPro::DialogCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCurrentPro::IDD, pParent)
{
	//��ʼ������ 
	mReadyProcess = LinkedList<PCB*>();
	
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
	ListCurrentProCtrl.GetClientRect(&rect);
	ListCurrentProCtrl.SetExtendedStyle(ListCurrentProCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
	ListProQCtrl.GetClientRect(&rect);
	ListProQCtrl.SetExtendedStyle(ListProQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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

void DialogCurrentPro::NotifyDataSetChange()
{
	int size = this->mReadyProcess.size();
	ListProQCtrl.DeleteAllItems();
	for (int i = 0;i<size ; i++){

		PCB *pcb = this->mReadyProcess.get(i);
		ListProQCtrl.InsertItem(i, Util::IntToCString(pcb->pid));
		ListProQCtrl.SetItemText(i, 1, pcb->id);
		ListProQCtrl.SetItemText(i, 2, pcb->userName);
		ListProQCtrl.SetItemText(i, 3, Util::IntToCString(pcb->priority));
		ListProQCtrl.SetItemText(i, 4,Util::IntToCString(pcb->enterTime));
		ListProQCtrl.SetItemText(i, 5, Util::IntToCString(pcb->allTime));
		ListProQCtrl.SetItemText(i, 6, Util::IntToCString(pcb->usedTime));
		ListProQCtrl.SetItemText(i, 7, Util::IntToCString(pcb->readyTime));
		ListProQCtrl.SetItemText(i, 8, pcb->getState());
	}
}

// CPU��ʼģ����̵����㷨
void DialogCurrentPro::Execute(int decPriority,int incPriority,int runSlots)
{
	
	if (ListCurrentProCtrl.GetItemCount() == 0){//��CPU����,ѡ�����ȼ���ߵĽ���ִ��
		int position = GetCandidatePos();
		if (mReadyProcess.get(0) == NULL||position < 0)  return;//�����б�Ϊ��
		mCurrentProcess = mReadyProcess.remove(position);
		mCurrentProcess->state = RUNNING;
	}
	//������ͼ
	UpdateListCPRO();
	UpdateListReady();

	if (runSlots >= 0){//����ִ��ʱ��Ƭû����
		UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		return;//����ִ���¸�ʱ��Ƭ
	}
	else//����ʱ��Ƭ���꣬����Ҫѡ���½������� 
	{
		if (mCurrentProcess == NULL) return;
		int tmpPid = mCurrentProcess->pid;//�����ϸ����н��̵�pid
		
		//�������н��̽����������
		mCurrentProcess->state = READY;
		mCurrentProcess->readyTime = 0;
		mReadyProcess.add(mCurrentProcess);

		//��ȡ�µ����н���
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		mCurrentProcess->state = RUNNING;
		if (mCurrentProcess->pid != tmpPid)//���¸����еĽ��̺��ϸ�һ��������������ʱ�䲻��
		{
			mCurrentProcess->runTime = 0;//��������ʱ������
			mCurrentProcess->readyTime = 0;//����ʱ����0
			UpdateCurrentPro(decPriority);
			UpdateReadyPro(incPriority);
		}
		
	}
	
}

// ��ȡ�Ӿ������н������ж��еĺ�ѡ����λ��
int DialogCurrentPro::GetCandidatePos()
{
	int size = mReadyProcess.size();
	if (size == 0) return -1;
	int target = mReadyProcess.get(0)->priority;
	int returnValue = 0;
	for (int i = 1; i < size; i++){
		if (mReadyProcess.get(i)->priority>target) {
			returnValue = i;
			target = mReadyProcess.get(i)->priority;
		}
	}
	return returnValue;
}

// ���µ�ǰ����
void DialogCurrentPro::UpdateCurrentPro(int decPriority)
{
	if (mCurrentProcess == NULL) return;
	//�������н�����Ϣ
	mCurrentProcess->usedTime++;//������ʱ������ 
	mCurrentProcess->runTime++;//��������ʱ��
	if (--mCurrentProcess->allTime == 0)//�������
	{
		mCurrentProcess->state = FINISHED;
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		if (mCurrentProcess == NULL) return;
	}
	if (mCurrentProcess->priority - decPriority < 0)
	{
		mCurrentProcess->priority = 0;//���ȼ����ܵ���0
	}
	else
	{
		mCurrentProcess->priority -= decPriority;//�������н������ȼ�����
	}
}

// ���¾�������
void DialogCurrentPro::UpdateReadyPro(int incPriority)
{
	int sizeA = mReadyProcess.size();
	for (int i = 0; i < sizeA; i++){
		if (mReadyProcess.get(i)->priority + incPriority>40){
			mReadyProcess.get(i)->priority = 40;//���ȼ����ӣ������ܴ���40 
		}
		else
		{
			mReadyProcess.get(i)->priority += incPriority;
		}
		mReadyProcess.get(i)->readyTime++;//��������ʱ������
	}
}

// ���µ�ǰ�����б�
void DialogCurrentPro::UpdateListCPRO()
{
	ListCurrentProCtrl.DeleteAllItems();
	if (mCurrentProcess == NULL) return;
	ListCurrentProCtrl.InsertItem(0, Util::IntToCString(mCurrentProcess->pid));
	ListCurrentProCtrl.SetItemText(0, 1, mCurrentProcess->id);
	ListCurrentProCtrl.SetItemText(0, 2, mCurrentProcess->userName);
	ListCurrentProCtrl.SetItemText(0, 3, Util::IntToCString(mCurrentProcess->priority));
	ListCurrentProCtrl.SetItemText(0, 4, Util::IntToCString(mCurrentProcess->enterTime));
	ListCurrentProCtrl.SetItemText(0, 5, Util::IntToCString(mCurrentProcess->allTime));
	ListCurrentProCtrl.SetItemText(0, 6, Util::IntToCString(mCurrentProcess->usedTime));
	ListCurrentProCtrl.SetItemText(0, 7, Util::IntToCString(mCurrentProcess->runTime));
	ListCurrentProCtrl.SetItemText(0, 8, mCurrentProcess->getState());
}


// ���¾����б�
void DialogCurrentPro::UpdateListReady()
{
	NotifyDataSetChange();
}
