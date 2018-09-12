#pragma once
#include "resource.h"
#include "afxcmn.h"

// CDlgProresstest 对话框

class CDlgProresstest : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgProresstest)

public:
	CDlgProresstest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProresstest();

// 对话框数据
	enum { IDD = IDD_PRORESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_progress;
	void setpos(int nPos);
	virtual  BOOL Create(CWnd* pParentWnd = NULL);
};
