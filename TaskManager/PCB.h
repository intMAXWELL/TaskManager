#pragma once
#ifndef PCB_H
#define PCB_H

#define READY 0//����
#define RUNNING 1//����
#define FINISHED 2//����

class PCB
{
public:
	PCB();
	PCB(int pid ,CString id,CString userName, int priority, int enterTime, int allTime);
	~PCB();
	int pid;//����id
	// ���̵ı�ʶ
	CString id;
	//�û���
	CString userName;
	// ������ ��Χ[0,40]
	int priority;
	// ����ʱ��
	int enterTime;
	// ������������ʱ��
	int allTime;
	// ��ʹ��CPU��ʱ��
	int usedTime;
	// ��������ʱ��
	int runTime;
	// ��������ʱ��
	int readyTime;
	// ����״̬
	int state;
	// ��Ȩ��תʱ��
	double rightTime;
	//����ʱ��
	int endTime;

	// �������������
	int static GeneratePriority();
	//���������������ʱ��
	int static GenerateNeedTime();
	//���н���������Ȩ��תʱ��
	void calRightTime();
	
	CString getState();
	//����Ϣͷ���
	CString static GetCurrentProInfoHead();
	CString static GetReadyProInfoHead();

	//��ȡ��ʽ���������
	CString GetCurrentProDetail();
	CString GetReadyProDetail();
};

#endif
