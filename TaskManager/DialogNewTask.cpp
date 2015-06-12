// DialogNewTask.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogNewTask.h"
#include "afxdialogex.h"


// DialogNewTask �Ի���

IMPLEMENT_DYNAMIC(DialogNewTask, CDialogEx)

DialogNewTask::DialogNewTask(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogNewTask::IDD, pParent)
{
	pid = 0;
	tmpPid = 0;
	newTaskList = LinkedList<PCB*>();
}

DialogNewTask::~DialogNewTask()
{
}

void DialogNewTask::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, List_New_Task_Q, listNewTaskQCtrl);
	DDX_Control(pDX, New_Task_EditText_Pro, processNameCtrl);
	DDX_Control(pDX, New_Task_EditText_User, userNameCtrl);
	DDX_Control(pDX, New_Task_EditText_Pri, priorityCtrl);
	DDX_Control(pDX, New_Task_EditText_NeedTime, allTimeCtrl);
}

BEGIN_MESSAGE_MAP(DialogNewTask, CDialogEx)
	ON_BN_CLICKED(New_Task_Button_Add_To_List, &DialogNewTask::OnBnClickedTaskButtonAddToList)
	ON_NOTIFY(NM_RCLICK, List_New_Task_Q, &DialogNewTask::OnNMRClickNewTaskQ)
	ON_COMMAND(ID_DELETE, &DialogNewTask::OnDelete)
END_MESSAGE_MAP()


BOOL DialogNewTask::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srand((unsigned)time(NULL));     //ÿ��ִ�����Ӳ�ͬ�����ɲ�ͬ�������
	CRect rect;
	InitListNewTaskQ(rect);
	return TRUE;  
}

// ��ʼ���½��̶����б�ѡ��
void DialogNewTask::InitListNewTaskQ(CRect rect)
{
	listNewTaskQCtrl.GetClientRect(&rect);
	listNewTaskQCtrl.SetExtendedStyle(listNewTaskQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	listNewTaskQCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 5, 0);
	listNewTaskQCtrl.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 5, 1);
	listNewTaskQCtrl.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect.Width() / 5, 2);
	listNewTaskQCtrl.InsertColumn(3, _T("���ȼ�"), LVCFMT_CENTER, rect.Width() / 5, 3);
	listNewTaskQCtrl.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect.Width() / 5, 4);

}

//��ӵ��б����¼�
void DialogNewTask::OnBnClickedTaskButtonAddToList()
{
	AddItemToList();
}

// ��������б�
void DialogNewTask::AddItemToList()
{

	processNameCtrl.GetWindowTextW(id);
	userNameCtrl.GetWindowTextW(userName);
	priorityCtrl.GetWindowTextW(priority);
	allTimeCtrl.GetWindowTextW(allTime);

	//Ĭ������
	if (userName == "") userName = CString("�û�")+Util::IntToCString(pid);
	if (id == "")  id = CString("����")+Util::IntToCString(pid);
	if (priority == "") {
		int a = PCB::GeneratePriority();
		priority = Util::IntToCString(a);
	}
	else if (Util::CStringToInt(priority) > 40 ||Util::CStringToInt(priority) < 0){
		MessageBox(_T("��������ΧΪ[0,40]!"), _T("��ʾ"));
		return;
	}
	if (allTime == ""){
		int a = PCB::GenerateNeedTime();
		allTime = Util::IntToCString(a);
	}
	
	int num = listNewTaskQCtrl.GetItemCount();

	listNewTaskQCtrl.InsertItem(num, Util::IntToCString(pid));
	listNewTaskQCtrl.SetItemText(num, 1, id);
	listNewTaskQCtrl.SetItemText(num, 2, userName);
	listNewTaskQCtrl.SetItemText(num, 3, priority);
	listNewTaskQCtrl.SetItemText(num, 4, allTime);
	
	PCB *pcb = new PCB(pid++,id, userName, Util::CStringToInt(priority), NULL, Util::CStringToInt(allTime));
	
	newTaskList.add(pcb);

}

//ĳ����Ҽ� 
void DialogNewTask::OnNMRClickNewTaskQ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu m, *pm;
	if (!m.LoadMenu(Menu_New_Task)) MessageBox(_T("err"));//IDR_MENU1����Ӧ����Դid
	pm = m.GetSubMenu(0); //��ȡ�ӶԻ���
	CPoint pot;
	GetCursorPos(&pot);//��ȡ��굱ǰλ��
	pm->TrackPopupMenu(TPM_LEFTALIGN, pot.x, pot.y, this);//�����λ�õ����˵�
	*pResult = 0;
}

//ɾ����� 
void DialogNewTask::OnDelete()
{
	for (int i = 0; i<listNewTaskQCtrl.GetItemCount(); i++)
	{
		if (listNewTaskQCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			newTaskList.remove( i);
			listNewTaskQCtrl.DeleteItem(i);
			listNewTaskQCtrl.Invalidate();
			i = 0;
		}
	}
}

// �ͷ���Դ��ֵ��ʼ��
void DialogNewTask::ClearAll()
{
	id = "";
	userName = "";
	priority = "";
	allTime = "";
	newTaskList.clear();
}

void DialogNewTask::OnCancel()
{
	id = "";
	userName = "";
	priority = "";
	allTime = "";
	//�ͷ���Դ
	if (newTaskList.size() != 0){
		delete(newTaskList.shift());
	}

	CDialogEx::OnCancel();
}


