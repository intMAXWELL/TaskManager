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
	case INTERUPT:
		return _T("ǿ�н���");
	case WAITING_FINISHED:
		return _T("�ȴ��˳�");
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
	if (this->usedTime == 0) this->rightTime = 0;//������ʱ��Ϊ0�����Ȩ��תʱ��Ϊ0
	else this->rightTime = (double)(endTime - enterTime) / usedTime;
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


