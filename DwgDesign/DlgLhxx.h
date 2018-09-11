#pragma once
#include "resource.h"

// CDlgLhxx 对话框

class CDlgLhxx : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgLhxx)

public:
	CDlgLhxx(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLhxx();

// 对话框数据
	enum { IDD = IDD_DLG_LHXX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CButton *btn;
	CEdit *Edit;
public:
	virtual BOOL OnInitDialog();
	afx_msg void bnclick();
	afx_msg void OnBnClickedOk();
};
