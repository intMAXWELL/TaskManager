#pragma once
//������
#ifndef Util_h
#define Util_h

class Util
{
public:
	static CString strTime;//ʱ����ʽ�����ļ���

	Util();
	~Util();
	
	CString static IntToCString(int a);
	int static CStringToInt(CString str);
	CString static DoubleToCString(double a);
};

#endif

