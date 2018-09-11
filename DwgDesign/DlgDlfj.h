#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CDlgDlfj 对话框

class CDlgDlfj : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgDlfj)

public:
	CDlgDlfj(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDlfj();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DLFJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CString m_sFjmc;
	CAcUiComboBox m_cmb_Fjlx;
	virtual BOOL OnInitDialog();
};
