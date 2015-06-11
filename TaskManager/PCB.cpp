#include "stdafx.h"
#include "PCB.h"


PCB::PCB()
: id("�½���")
, userName("Ĭ���û�")
, priority(GeneratePriority())
, enterTime(0)
, allTime(GenerateNeedTime())
, usedTime(0)
, runTime(0)
, readyTime(0)
, state(READY)
, rightTime(0)
, endTime(0)
{
}

PCB::PCB(int pid ,CString id, CString userName, int priority, int enterTime, int allTime){
	this->pid = pid;
	this->id = id;
	this->userName = userName;
	this->usedTime = 0;
	this->runTime = 0;
	this->readyTime = 0;
	this->rightTime = 0;
	this->endTime = 0;
	this->state = READY;
	this->priority = priority;
	this->enterTime = enterTime;
	this->allTime = allTime;
}

PCB::~PCB()
{
}

// �������������
int PCB::GeneratePriority()
{
	return rand() % 40;	
}

//���������Ҫʱ��
int PCB::GenerateNeedTime()
{
	return rand() % 40+1;
}


CString PCB::getState()
{
	switch (this->state)
	{
	case READY:
		return  _T("����");
	case RUNNING:
		return _T("����");
	case FINISHED:
		return _T("����");
	default:
		break;
	}
	return _T("δ֪");
}

CString PCB::GetCurrentProDetail(){
	CString str;
	str.Format(_T("    %-3d   %-6s   %-6s   %-6d   %-8d   %-8d   %-10d   %-12d\r\n"), pid, id, userName, priority, enterTime, allTime, usedTime, runTime);
	return str;
}

CString PCB::GetReadyProDetail(){
	CString str;
	str.Format(_T("    %-3d   %-6s   %-6s   %-6d   %-8d   %-8d   %-10d   %-12d\r\n"), pid, id, userName, priority, enterTime, allTime, usedTime, readyTime);
	return str;
}

void PCB::calRightTime(){
	this->rightTime = (double)(endTime - enterTime) / usedTime;
}

CString PCB::GetCurrentProInfoHead(){
	CString str;
	str = "    PID   ������   �û���   ���ȼ�   ����ʱ��   ����ʱ��   ������ʱ��   ��������ʱ��\r\n";
	return str;
}

CString PCB::GetReadyProInfoHead(){
	CString str;
	str = "    PID   ������   �û���   ���ȼ�   ����ʱ��   ����ʱ��   ������ʱ��   ��������ʱ��\r\n";
	return str;
}

CString PCB::GetFormatPid(){
	CString pid;
	pid.Format(_T("%3d"), this->pid);
	return pid;
}

CString PCB::GetFormatId(){
	CString id;
	id.Format(_T("%6s"), this->id);
	return id;
}

CString PCB::GetFormatUserName(){
	CString userName;
	userName.Format(_T("%6s"), this->userName);
	return userName;
}

CString PCB::GetFormatPriority(){
	CString priority;
	priority.Format(_T("%6d"), this->priority);
	return priority;
}

CString PCB::GetFormatEnterTime(){
	CString enterTime;
	enterTime.Format(_T("%8d"), this->enterTime);
	return enterTime;
}

CString PCB::GetFormatAllTime(){
	CString allTime;
	allTime.Format(_T("%8d"), this->allTime);
	return allTime;
}

CString PCB::GetFormatRunTime(){
	CString runTime;
	runTime.Format(_T("%10d"), this->runTime);
	return runTime;
}

CString PCB::GetFormatUsedTime(){
	CString usedTime;
	usedTime.Format(_T("%12d"), this->usedTime);
	return usedTime;
}

CString PCB::GetFormatReadyTime(){
	CString readyTime;
	readyTime.Format(__T("%5d"), this->readyTime);
	return readyTime;
}

