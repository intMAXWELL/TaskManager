
// TaskManagerMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "TaskManagerMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// TaskManagerMainDlg �Ի���
TaskManagerMainDlg::TaskManagerMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TaskManagerMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//��ʼ������
	CPURunTime = 0;
	mDialogCurrenPro.continueRunTimeSlots = continueRunTimeSlots;
	mDialogCurrenPro.tmp = continueRunTimeSlots;

}

void TaskManagerMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Tab_Current_Pro, tabControl);
	DDX_Control(pDX, Main_Button_New_Task, buttonNewTask);
	DDX_Control(pDX, Main_Text_Cpu_Info, CPURunTimeTextCtrl);
	DDX_Control(pDX, Main_Button_Stop_CPU, buttonCPUCtrl);
	DDX_Control(pDX, Main_Button_Step_In, buttonStepInCtrl);
}

BEGIN_MESSAGE_MAP(TaskManagerMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, Tab_Current_Pro, &TaskManagerMainDlg::OnTcnSelchange)
	ON_BN_CLICKED(Main_Button_Settings, &TaskManagerMainDlg::OnBnClickedButtonSettings)
	ON_BN_CLICKED(Main_Button_New_Task, &TaskManagerMainDlg::OnBnClickedButtonNewTask)
	ON_BN_CLICKED(Main_Button_Stop_CPU, &TaskManagerMainDlg::OnBnClickedButtonStopCpu)
	ON_BN_CLICKED(Main_Button_Step_In, &TaskManagerMainDlg::OnBnClickedButtonStepIn)
END_MESSAGE_MAP()

// TaskManagerMainDlg ��Ϣ�������
BOOL TaskManagerMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect tabRect;//

	//���Tabѡ��
	tabControl.InsertItem(Dialog_Current_Pro, _T("��ǰ����"));
	tabControl.InsertItem(Dialog_Finished_Pro, _T("�ѽ���"));
	//����
	mDialogCurrenPro.Create(Dialog_Current_Pro, &tabControl);
	mDialogFinishedPro.Create(Dialog_Finished_Pro, &tabControl);
	//����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ
	tabControl.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//������ʾ
	mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	SetTimer(PERIOD_TASK, timeSlot, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void TaskManagerMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//��С����ť
void TaskManagerMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ
HCURSOR TaskManagerMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Tab�л��¼�����
void TaskManagerMainDlg::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;//
	tabControl.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//�л�
	switch (tabControl.GetCurSel())
	{
	case 0:
		mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}

//���ð�ť�����
void TaskManagerMainDlg::OnBnClickedButtonSettings()
{
	int nRet = mDialogSettings.DoModal();
	if (nRet == IDOK)
	{
		//������Ӧ�Ĳ���
		timeSlot = Util::CStringToInt(mDialogSettings.mSNum);
		continueRunTimeSlots = Util::CStringToInt(mDialogSettings.continueRunTimeSlots);
		decPriority = Util::CStringToInt(mDialogSettings.decPriority);
		incPriority = Util::CStringToInt(mDialogSettings.incPriority);
		mDialogCurrenPro.continueRunTimeSlots = continueRunTimeSlots;
		mDialogCurrenPro.tmp = continueRunTimeSlots;

		KillTimer(PERIOD_TASK);
		SetTimer(PERIOD_TASK, timeSlot, NULL);
	}
}

//�½�����ť�������
void TaskManagerMainDlg::OnBnClickedButtonNewTask()
{
	INT_PTR nRet = mDialogNewTask.DoModal();
	if (nRet == IDOK){
		int size = mDialogNewTask.newTaskList.size();
		for (int i = 0; i < size; i++){
			//���ݴ��ݣ����������������еȴ�
			mDialogNewTask.newTaskList.get(0)->enterTime = CPURunTime;
			mDialogCurrenPro.mReadyProcess.add(mDialogNewTask.newTaskList.shift());
		}
	}
	//����������Ϣ������ʼ��һЩ����
	mDialogNewTask.ClearAll();
	mDialogCurrenPro.NotifyDataSetChange();
}

//�����Ժ���
void TaskManagerMainDlg::OnTimer(UINT_PTR nIDEvent){
	if (nIDEvent == PERIOD_TASK){
		Execute();
	}
}

//cpu��ת����
void TaskManagerMainDlg::OnBnClickedButtonStopCpu()
{
	if (++clickTimes % 2 == 1)//��ֹ����
	{
		buttonCPUCtrl.SetWindowTextW(_T("����CPU"));
		buttonStepInCtrl.EnableWindow(TRUE);
		KillTimer(PERIOD_TASK);
	}
	else
	{
		buttonCPUCtrl.SetWindowTextW(_T("��ֹCPU"));
		buttonStepInCtrl.EnableWindow(FALSE);
		SetTimer(PERIOD_TASK, timeSlot, NULL);
	}
}

//������ť���
void TaskManagerMainDlg::OnBnClickedButtonStepIn()
{
	if (clickTimes % 2 == 1){
		Execute();
	}
}

void TaskManagerMainDlg::Execute(){
	CString str;
	str.Format(_T("CPU����������%d��ʱ��Ƭ"), CPURunTime++);
	CPURunTimeTextCtrl.SetWindowTextW(str);
	PCB * finishedPCB;
	finishedPCB = mDialogCurrenPro.Execute(decPriority, incPriority, CPURunTime);
	if (finishedPCB != NULL){
		finishedPCB->endTime = CPURunTime;
		finishedPCB->calRightTime();
		mDialogFinishedPro.mFinishedProcess.add(finishedPCB);
		mDialogFinishedPro.NotifyDataSetChange();
	}
}
