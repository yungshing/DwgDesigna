#pragma once
#include "resource.h"

// CDlgLhxx �Ի���

class CDlgLhxx : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgLhxx)

public:
	CDlgLhxx(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLhxx();

// �Ի�������
	enum { IDD = IDD_DLG_LHXX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CButton *btn;
	CEdit *Edit;
public:
	virtual BOOL OnInitDialog();
	afx_msg void bnclick();
	afx_msg void OnBnClickedOk();
};
