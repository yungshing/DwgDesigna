#pragma once
#include "resource.h"
#include "afxcmn.h"

// CDlgProresstest �Ի���

class CDlgProresstest : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgProresstest)

public:
	CDlgProresstest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProresstest();

// �Ի�������
	enum { IDD = IDD_PRORESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_progress;
	void setpos(int nPos);
	virtual  BOOL Create(CWnd* pParentWnd = NULL);
};
