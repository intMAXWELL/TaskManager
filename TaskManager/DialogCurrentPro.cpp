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
	currentProHead = PCB::GetCurrentProInfoHead();
	readyProHead = PCB::GetReadyProInfoHead();

	file.Open(strTime+".txt", CFile::modeCreate | CFile::modeReadWrite);
	unsigned short int feff = 0xfeff;
	file.Write(&feff, sizeof(short int));//д���ļ�ͷ
	file.Write(_T("���������־:\r\n"), 18);
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
	ListProQCtrl.SetRedraw(FALSE);
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
	ListProQCtrl.SetRedraw(TRUE);
	ListProQCtrl.Invalidate();
	ListProQCtrl.UpdateWindow();
}

// CPU��ʼģ����̵����㷨
PCB* DialogCurrentPro::Execute(int decPriority,int incPriority,int cpuRunTime)
{
	PCB *finishedPCB = NULL;
	if (ListCurrentProCtrl.GetItemCount() == 0){//��CPU����,ѡ�����ȼ���ߵĽ���ִ��
		int position = GetCandidatePos();
		if (mReadyProcess.get(0) == NULL || position < 0)  {
			tmp = continueRunTimeSlots;
			return finishedPCB;//�����б�Ϊ�գ���ǰ����������
		}
		mCurrentProcess = mReadyProcess.remove(position);
		mCurrentProcess->state = RUNNING;
	}

	if (tmp-- > 0){//����ִ��ʱ��Ƭû����,����ִ���¸�ʱ��Ƭ
		finishedPCB = UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		//������ͼ
		UpdateListCPRO();
		UpdateListReady();
	}
	else//����ʱ��Ƭ���꣬����Ҫѡ���½������� 
	{
		tmp = continueRunTimeSlots-1;
		if (mCurrentProcess == NULL) return finishedPCB;
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
			mCurrentProcess->runTime = 0;//��������ʱ����0
			mCurrentProcess->readyTime = 0;//����ʱ����0
		}
		finishedPCB =UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		//������ͼ
		UpdateListCPRO();
		UpdateListReady();
	}

	//�ļ���д
	if (mCurrentProcess != NULL){
		WriteCurrentProToFile(cpuRunTime);
		file.Write(_T("\r\n"), 4);
		WriteReadyProToFile();
		file.Write(_T("\r\n"), 4);
		file.Flush();
	}
	
	return finishedPCB;
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

// ���µ�ǰ����,������ɵĽ��������ޣ��򷵻�NULL
PCB* DialogCurrentPro::UpdateCurrentPro(int decPriority)
{
	PCB* pcb = NULL;
	if (mCurrentProcess == NULL) return pcb;
	if (--mCurrentProcess->allTime <= 0)//�������
	{
		mCurrentProcess->usedTime++;//������ʱ������ 
		mCurrentProcess->runTime++;//��������ʱ��
		mCurrentProcess->state = FINISHED;

		pcb = mCurrentProcess;

		//ѡ����һ������
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		if (mCurrentProcess == NULL) return pcb;
		mCurrentProcess->state = RUNNING;
	}
	else//δ�������,���½�����Ϣ
	{
		if (mCurrentProcess->priority - decPriority < 0)
		{
			mCurrentProcess->priority = 0;//���ȼ����ܵ���0
		}
		else
		{
			mCurrentProcess->priority -= decPriority;//�������н������ȼ�����
		}
		mCurrentProcess->usedTime++;//������ʱ������ 
		mCurrentProcess->runTime++;//��������ʱ��
	}
	return pcb;
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
	ListCurrentProCtrl.SetRedraw(FALSE);
	//��������
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
	ListCurrentProCtrl.SetRedraw(TRUE);
	ListCurrentProCtrl.Invalidate();
	ListCurrentProCtrl.UpdateWindow();
}


// ���¾����б�
void DialogCurrentPro::UpdateListReady()
{
	NotifyDataSetChange();
}

void DialogCurrentPro::WriteCurrentProToFile(int cpuRunTime){
	CString cpuState;
	cpuState.Format(_T("��%d��ʱ��Ƭ:\r\n"), cpuRunTime);
	file.Write(cpuState, cpuState.GetLength() << 1);
	file.Write(_T("CPU����:\r\n"), 16);
	file.Write(currentProHead, currentProHead.GetLength() << 1);
	int position = file.GetLength();//��ȡÿһ�еĿ�ͷλ��
	int length = currentProHead.GetLength();
	//file.Write(currentProHead, currentProHead.GetLength() << 1);
	for (int i = 0; i <length; i++){
		file.Write(_T(" "), 2);
	}
	//дpid
	position += 4 << 1;
	file.Seek(position, CFile::begin);
	CString pid = mCurrentProcess->GetFormatPid();
	file.Write(pid, pid.GetLength() << 1);
	//д������
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString id = mCurrentProcess->GetFormatId();
	file.Write(id, id.GetLength() << 1);
	//д�û���
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString userName = mCurrentProcess->GetFormatUserName();
	file.Write(userName, userName.GetLength() << 1);
	//д���ȼ�
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString priority = mCurrentProcess->GetFormatPriority();
	file.Write(priority, priority.GetLength() << 1);
	//д����ʱ��
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString enterTime = mCurrentProcess->GetFormatEnterTime();
	file.Write(enterTime, enterTime.GetLength() << 1);
	//д����ʱ��
	position += 7 << 1;
	file.Seek(position, CFile::begin);
	CString allTime = mCurrentProcess->GetFormatAllTime();
	file.Write(allTime, allTime.GetLength() << 1);
	//д������ʱ��
	position += 7 << 1;
	file.Seek(position, CFile::begin);
	CString usedTime = mCurrentProcess->GetFormatUsedTime();
	file.Write(usedTime, usedTime.GetLength() << 1);
	//д��������ʱ��
	position += 8 << 1;
	file.Seek(position, CFile::begin);
	CString runTime = mCurrentProcess->GetFormatRunTime();
	file.Write(runTime, runTime.GetLength() << 1);
}

void DialogCurrentPro::WriteReadyProToFile(){
	CString head = _T("�ȴ�����:\r\n");
	int b = file.GetLength();
	file.Write(head,head.GetLength()<<1);
	file.Write(readyProHead, readyProHead.GetLength() << 1);
	int length = readyProHead.GetLength();
	int size = mReadyProcess.size();
	for (int i = 0; i < size; i++){
		PCB* readyPro = mReadyProcess.get(i);
		int position = file.GetLength();//��ȡÿһ�еĿ�ͷλ��
		for (int j = 0; j<length; j++){
			file.Write(_T(" "), 2);
		}
		//дpid
		position += 4 << 1;
		file.Seek(position, CFile::begin);
		CString pid = readyPro->GetFormatPid();
		file.Write(pid, pid.GetLength() << 1);
		//д������
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString id = readyPro->GetFormatId();
		file.Write(id, id.GetLength() << 1);
		//д�û���
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString userName = readyPro->GetFormatUserName();
		file.Write(userName, userName.GetLength() << 1);
		//д���ȼ�
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString priority = readyPro->GetFormatPriority();
		file.Write(priority, priority.GetLength() << 1);
		//д����ʱ��
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString enterTime = readyPro->GetFormatEnterTime();
		file.Write(enterTime, enterTime.GetLength() << 1);
		//д����ʱ��
		position += 7 << 1;
		file.Seek(position, CFile::begin);
		CString allTime = readyPro->GetFormatAllTime();
		file.Write(allTime, allTime.GetLength() << 1);
		//д������ʱ��
		position += 7 << 1;
		file.Seek(position, CFile::begin);
		CString usedTime = readyPro->GetFormatUsedTime();
		file.Write(usedTime, usedTime.GetLength() << 1);
		//д�����ȴ�ʱ��
		position += 8 << 1;
		file.Seek(position, CFile::begin);
		CString readyTime = readyPro->GetFormatReadyTime();
		file.Write(readyTime, readyTime.GetLength() << 1);

		CString end = _T("\r\n");
		file.Write(end,end.GetLength()<<1);
	}
}


BOOL DialogCurrentPro::DestroyWindow()
{
	file.Close();
	return CDialogEx::DestroyWindow();
}

