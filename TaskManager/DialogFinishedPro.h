#pragma once


// DialogFinishedPro �Ի���

class DialogFinishedPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFinishedPro)

public:
	DialogFinishedPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogFinishedPro();

// �Ի�������
	enum { IDD = Dialog_Finished_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};
